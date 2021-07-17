#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Entity.h"

#include <string>
#include <vector>

#define PLATFORM_COUNT 20
#define ENEMY_COUNT 3

struct GameState {
    Entity *player;
    Entity *enemies;
    Entity *platforms;
    Entity *text;
    std::string isWin = "ongoing";
};

GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix, eyeballMatrix;

Mix_Music *music;

// loads a texture so that it is usable
GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);
    
    if (image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    stbi_image_free(image);
    return textureID;
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    displayWindow = SDL_CreateWindow("Project 4 - Rise of the AI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    // initializing music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("Assets/music.mp3");
    Mix_PlayMusic(music, -1); // -1 = endless loop
    Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    glUseProgram(program.programID);
    
    glClearColor(0.5, 0.5, 0.5, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize Game Objects
    
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(-4, -1.5, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = LoadTexture("Assets/player.png");
    state.player->leftIdleIndex = 11;
    state.player->rightIdleIndex = 0;
    
    state.player->animRight = new int[12] {0,1,2,3,4,5,6,7,8,9,10,11};
    state.player->animLeft = new int[12] {12,13,14,15,16,17,18,19,20,21,22,23};

    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 12;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 12;
    state.player->animRows = 2;
    
    state.player->height = 0.8f;
    state.player->width = 0.5f;
    
    state.player->jumpPower = 6.5f;
    
    GLuint backgroundTextureID = LoadTexture("Assets/background_assets.png");
    // Initialize platforms
    state.platforms = new Entity[PLATFORM_COUNT];
    
    // creating floor and platforms
    
    for (int i = 0; i < PLATFORM_COUNT; i++) {
        state.platforms[i].entityType = PLATFORM;
        state.platforms[i].textureID = backgroundTextureID;
        state.platforms[i].animCols = 23;
        state.platforms[i].animRows = 14;
        state.platforms[i].animIndices = new int[1] {3};
        state.platforms[i].animIndex = 0;
        state.platforms[i].aiType = IGNORE;
        if (i < 13) {
            state.platforms[i].position =  glm::vec3(-4.6 + i*0.8, -3.25f, 0);
        } else if (i >= 13 && i < 15) {
            state.platforms[i].position =  glm::vec3(3.0 + (i-12)*0.8, -1.4f, 0);
        } else {
            state.platforms[i].position =  glm::vec3(-2.4 + (i-14)*0.8, 0.5f, 0);
        }

    }
    
    for (int i = 0; i < PLATFORM_COUNT; i++) {
        state.platforms[i].Update(0, NULL, NULL, 0, NULL, 0, state.isWin);
    }
    
    // initiating flying eye properties
    state.enemies = new Entity[ENEMY_COUNT];
    GLuint enemyTextureID_1 = LoadTexture("Assets/flying_eye.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID_1;
    
    state.enemies[0].animIndices = new int[8] {0,1,2,3,4,5,6,7} ;
    state.enemies[0].animFrames = 8;
    state.enemies[0].animIndex = 0;
    state.enemies[0].animTime = 0;
    state.enemies[0].animCols = 3;
    state.enemies[0].animRows = 3;
    state.enemies[0].rightIdleIndex = 0;
    
    state.enemies[0].height = 0.6f;
    state.enemies[0].width = 0.6f;
    
    
    state.enemies[0].position = glm::vec3(-3.75f, 1.5f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = FLYER;
    state.enemies[0].aiState = MOVING;
    state.enemies[0].direction = "up";
    
    // initiating horse properties
    GLuint enemyTextureID_2 = LoadTexture("Assets/horse.png");
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID_2;
    
    state.enemies[1].animRight = new int[4] {0,1,2,3};
    state.enemies[1].animLeft = new int[4] {4,5,6,7};
    state.enemies[1].animIndices = state.enemies[1].animLeft;
    state.enemies[1].animFrames = 4;
    state.enemies[1].animIndex = 0;
    state.enemies[1].animTime = 0;
    state.enemies[1].animCols = 4;
    state.enemies[1].animRows = 2;
    state.enemies[1].rightIdleIndex = 1;
    state.enemies[1].leftIdleIndex = 2;
    
    state.enemies[1].height = 0.6f;
    state.enemies[1].width = 0.6f;

    state.enemies[1].position = glm::vec3(4.35, -2.4f, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = IDLE;
    state.enemies[1].direction = "left";
    
    // initiating skeleton properties
    GLuint enemyTextureID_3 = LoadTexture("Assets/skeleton_warrior.png");
    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID_3;
    
    state.enemies[2].animRight = new int[4] {0,1,3,4};
    state.enemies[2].animLeft = new int[4] {2,5,6,7};
    state.enemies[2].animIndices = state.enemies[2].animRight;
    state.enemies[2].animFrames = 4;
    state.enemies[2].animIndex = 0;
    state.enemies[2].animTime = 0;
    state.enemies[2].animCols = 3;
    state.enemies[2].animRows = 3;
    state.enemies[2].rightIdleIndex = 1;
    state.enemies[2].leftIdleIndex = 3;
    
    state.enemies[2].height = 0.8f;
    state.enemies[2].width = 0.8f;
    
    state.enemies[2].position = glm::vec3(-1.7f, 1.0, 0);
    //state.enemies[2].movement = glm::vec3(1.0f, 0, 0);
    state.enemies[2].speed = 1;
    state.enemies[2].aiType = PATROLER;
    state.enemies[2].direction = "right";
    state.enemies[2].acceleration = glm::vec3(0, -9.81f, 0);
    
    // loading font sprite sheet
    state.text = new Entity();
    state.text->textureID = LoadTexture("Assets/font.png");
    state.text->entityType = TEXT;


}

void ProcessInput() {
    
    state.player->movement = glm::vec3(0);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        // Move the player left
                        break;
                        
                    case SDLK_RIGHT:
                        // Move the player right
                        break;
                        
                    case SDLK_SPACE:
                        // can only jump if player's feet touching ground
                        if(state.player->collidedBottom) {
                            state.player->jump = true;
                        }
                        break;
                }
                break; // SDL_KEYDOWN
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
     
    if (state.isWin == "ongoing") { // if the game didnt end yet
        if (keys[SDL_SCANCODE_LEFT]) {
            state.player->movement.x = -1.0f;
            state.player->direction = "left";
            state.player->animIndices = state.player->animLeft;
        }
        else if (keys[SDL_SCANCODE_RIGHT]) {
            state.player->movement.x = 1.0f;
            state.player->direction = "right";
            state.player->animIndices = state.player->animRight;
        }
        

        if (glm::length(state.player->movement) > 1.0f) {
            state.player->movement = glm::normalize(state.player->movement);
        }
    }

}


#define FIXED_TIMESTEP 0.0166666f // 60fps
float lastTicks = 0;
float accumulator = 0.0f;
void Update() {
   float ticks = (float)SDL_GetTicks() / 1000.0f;
   float deltaTime = ticks - lastTicks;
   lastTicks = ticks;
   deltaTime += accumulator;
    // if not enough time has gone by, we accumulate it
   if (deltaTime < FIXED_TIMESTEP) {
       accumulator = deltaTime;
       return;
   }
    // if we have enough time, we update in fixed intervals (good for if computer pauses)
   while (deltaTime >= FIXED_TIMESTEP) {
       // Update. Notice it's FIXED_TIMESTEP. Not deltaTime
    
       // if game was won, stop everything from moving
       if (state.isWin == "won") {
           state.player->velocity.x = 0;
           state.player->velocity.y = 0;
           state.player->movement.x = 0;
           state.player->movement.y = 0;
           state.player->acceleration.x = 0;
           state.player->acceleration.y = 0;
           return;
       } else if (state.isWin == "loss") { // if game was won, stop everything from moving
           
           state.player->velocity.x = 0;
           state.player->velocity.y = 0;
           state.player->movement.x = 0;
           state.player->movement.y = 0;
           state.player->acceleration.x = 0;
           state.player->acceleration.y = 0;
           for (int i = 0; i < ENEMY_COUNT; i++) {
               state.enemies[i].velocity.x = 0;
               state.enemies[i].velocity.y = 0;
           }
           return;
       } else {
           state.player->Update(FIXED_TIMESTEP, state.player, state.enemies, ENEMY_COUNT,state.platforms, PLATFORM_COUNT, state.isWin);
           int inactiveCount = 0;
           for (int i = 0; i < ENEMY_COUNT; i++) {
              state.enemies[i].Update(FIXED_TIMESTEP, state.player, state.enemies, ENEMY_COUNT, state.platforms, PLATFORM_COUNT, state.isWin);
               if (!(state.enemies[i].isActive)) { // if not active
                   inactiveCount++;
               }
               if (inactiveCount == ENEMY_COUNT) { // if all enemies are gotten rid of, you win
                   state.isWin = "won";
               }
           }
       }
       deltaTime -= FIXED_TIMESTEP;
   }
   accumulator = deltaTime;
}

void DrawText(ShaderProgram *program, GLuint fontTextureID, std::string text,
                                 float size, float spacing, glm::vec3 position)
{
    float width = 1.0f / 16.0f;
    float height = 1.0f / 16.0f;
    std::vector<float> vertices;
    std::vector<float> texCoords;
    for(int i = 0; i < text.size(); i++) {
        int index = (int)text[i];
        float offset = (size + spacing) * i;
        float u = (float)(index % 16) / 16.0f;
        float v = (float)(index / 16) / 16.0f;
        
        vertices.insert(vertices.end(), {
            offset + (-0.5f * size), 0.5f * size,
            offset + (-0.5f * size), -0.5f * size,
            offset + (0.5f * size), 0.5f * size,
            offset + (0.5f * size), -0.5f * size,
            offset + (0.5f * size), 0.5f * size,
            offset + (-0.5f * size), -0.5f * size,
        });
        texCoords.insert(texCoords.end(), {
            u, v,
            u, v + height,
            u + width, v,
            u + width, v + height,
            u + width, v,
            u, v + height,
        });
    } // end of for loop
    glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        program->SetModelMatrix(modelMatrix);
        glUseProgram(program->programID);
        glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices.data());
        glEnableVertexAttribArray(program->positionAttribute);
        glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.data());
        glEnableVertexAttribArray(program->texCoordAttribute);
        glBindTexture(GL_TEXTURE_2D, fontTextureID);
        glDrawArrays(GL_TRIANGLES, 0, (int)(text.size() * 6));
        glDisableVertexAttribArray(program->positionAttribute);
        glDisableVertexAttribArray(program->texCoordAttribute);
}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < PLATFORM_COUNT; i++) {
       state.platforms[i].Render(&program);
    }
    
    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].Render(&program);
    }
    state.player->Render(&program);
    
    if (state.isWin == "won") {
        DrawText(&program, state.text->textureID, "You Won",
                 1.0f, -0.5f, glm::vec3(-1.5, -0.5, 0));


    } else if (state.isWin == "loss") {
        DrawText(&program, state.text->textureID, "You Lose",
                 1.0f, -0.5f, glm::vec3(-1.5, -0.5, 0));
    }
    SDL_GL_SwapWindow(displayWindow);
}


void Shutdown() {
    SDL_Quit();
}


int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
    return 0;
}


