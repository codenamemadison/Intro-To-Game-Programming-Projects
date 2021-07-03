#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
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

#define LANDING_PLATFORM_COUNT 3
#define WALL_COUNT 32

struct GameState {
    Entity *player;
    Entity *walls;
    Entity *landing_platforms;
    Entity *text;
};

GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

bool isWin = NULL;

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
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Project 3 - Lunar Lander", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
   
    // Initialize Game Objects
    
    // Initialize Player
    state.player = new Entity();
    state.player->position = glm::vec3(3.0, 3.25f, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -0.02f, 0);
    state.player->speed = 0.75f;
    state.player->textureID = LoadTexture("player_ship.png");
    state.player->entityType = PLAYER;


    // is this useful?
    state.player->height = 0.8f;
    state.player->width = 0.8f;

    
    // CREATING WALL TILES FOR GAME WOLRD
    state.walls = new Entity[WALL_COUNT];
    GLuint wallTextureID = LoadTexture("wall_lose_tile.png");
    
    int base_index = -1;
    int floor_length = 7;
    // creating wall tiles for floor
    for (int i = 0; i < floor_length; i++) {
        if (i < floor_length - 2) {
            state.walls[i].textureID = wallTextureID;
            state.walls[i].position =  glm::vec3(-4.5 + float(i), -3.25f, 0);
            state.walls[i].entityType = WALL;
        } else {
            state.walls[i].textureID = wallTextureID;
            state.walls[i].position =  glm::vec3(3.5, -3.25, 0);
            state.walls[i].entityType = WALL;
        }
    }
    
    base_index += floor_length;
    int wall_height = 8;
    
    // creating wall tiles for left wall
    for (int i = 0; i < wall_height; i++) {
        state.walls[base_index+i].textureID = wallTextureID;
        state.walls[base_index+i].position =  glm::vec3(-4.5, 3.25 - float(i), 0);
        state.walls[base_index+i].entityType = WALL;
    }
    base_index += wall_height;
    
    // creating wall tiles for right wall
    for (int i = 0; i < wall_height; i++) {
        state.walls[base_index+i].textureID = wallTextureID;
        state.walls[base_index+i].position =  glm::vec3(4.5, 3.25 - float(i), 0);
        state.walls[base_index+i].entityType = WALL;
    }
    base_index += wall_height;
    
    int obstacle_1_length = 4;
    // creating wall tiles for platform/obstacle #1
    for (int i = 0; i < obstacle_1_length; i++) {
        state.walls[base_index+i].textureID = wallTextureID;
        state.walls[base_index+i].position =  glm::vec3(3.5 - float(i), 0.25, 0);
        state.walls[base_index+i].entityType = WALL;
    }
    base_index += obstacle_1_length;
    
    int obstacle_2_length = 3;
    // creating wall tiles for platform/obstacle #2
    
    for (int i = 0; i < obstacle_2_length; i++) {
        state.walls[base_index+i].textureID = wallTextureID;
        if (i < obstacle_2_length - 1) {
            state.walls[base_index+i].position =  glm::vec3(-2.5 - float(i), -2.25, 0);
        } else {
            state.walls[base_index+i].position =  glm::vec3(-3.5, -1.25, 0);
        }
        state.walls[base_index+i].entityType = WALL;
    }
        
    base_index += obstacle_2_length;
    
    int obstacle_3_length = 3;
    // creating wall tiles for platform/obstacle #3
    for (int i = 0; i < obstacle_3_length; i++) {
        state.walls[base_index+i].textureID = wallTextureID;
        if (i < obstacle_3_length - 1) {
            state.walls[base_index+i].position =  glm::vec3(-2.5 - float(i), 3.25, 0);
        } else {
            state.walls[base_index+i].position =  glm::vec3(-3.5, 2.25, 0);
        }
        state.walls[base_index+i].entityType = WALL;
    }

    base_index += obstacle_3_length;
    

    for (int i = 0; i < WALL_COUNT; i++) {
        state.walls[i].Update(0, NULL, 0);
    }
    

    // creating platform tiles for landing in game world
    state.landing_platforms = new Entity[LANDING_PLATFORM_COUNT];
    GLuint platformTextureID = LoadTexture("landing_win_tile.png");
    
    for (int i = 0; i < LANDING_PLATFORM_COUNT; i++) {
        state.landing_platforms[i].textureID = platformTextureID;
        state.landing_platforms[i].position =  glm::vec3(0.5 + float(i), -3.25f, 0);
        state.landing_platforms[i].entityType = LANDING_PLATFORM;
    }
    
     
    for (int i = 0; i < LANDING_PLATFORM_COUNT; i++) {
        state.landing_platforms[i].Update(0, NULL, 0);
    }
    
    // loading font sprite sheet
    state.text = new Entity();
    state.text->textureID = LoadTexture("font.png");
    state.text->entityType = TEXT;
}

void ProcessInput() {
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
                }
                break; // SDL_KEYDOWN
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        state.player->acceleration.x += -0.5f;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        state.player->acceleration.x += 0.5f;
    }
    
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
       if (state.player->lastCollision == WALL) {
           isWin = false;
           state.player->velocity.x = 0;
           state.player->velocity.y = 0;
           return;
       } else if (state.player->lastCollision == LANDING_PLATFORM) {
           isWin = true;
           state.player->velocity.x = 0;
           state.player->velocity.y = 0;
           return;
       } else {
           state.player->Update(FIXED_TIMESTEP, state.landing_platforms, LANDING_PLATFORM_COUNT);
           state.player->Update(FIXED_TIMESTEP, state.walls, WALL_COUNT);
           deltaTime -= FIXED_TIMESTEP;
       }
   }
   accumulator = deltaTime;

}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    

    for (int i = 0; i < LANDING_PLATFORM_COUNT; i++) {
        state.landing_platforms[i].Render(&program);
    }
    
    for (int i = 0; i < WALL_COUNT; i++) {
        state.walls[i].Render(&program);
    }
    
    if (state.player->lastCollision == WALL) {
        DrawText(&program, state.text->textureID, "Mission Failed",
                 1.0f, -0.5f, glm::vec3(-3.0, 0, 0));


    } else if (state.player->lastCollision == LANDING_PLATFORM) {
        DrawText(&program, state.text->textureID, "Mission Successful",
                 1.0f, -0.55f, glm::vec3(-3.75, 0, 0));
    }

    state.player->Render(&program);
    
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



