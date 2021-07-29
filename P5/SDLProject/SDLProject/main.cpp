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


#include "Util.h"
#include "Entity.h"
#include "Map.h"
#include "Scene.h"
#include "MainMenu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "WinScene.h"
#include "LoseScene.h"


GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

Scene *currentScene;
Scene *sceneList[6]; // array of diff scenes
void SwitchToScene(Scene *scene) {
    currentScene = scene; 
    currentScene->Initialize();
}

int lives = 3;
int levelNum = 0;

Mix_Music *music;
Mix_Chunk *jump;

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Project 5 - Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    // initializing music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("Assets/Sounds/music.mp3");
    Mix_PlayMusic(music, -1); // -1 = endless loop
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    jump = Mix_LoadWAV("Assets/Sounds/jump_sound_effect.wav");
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    sceneList[0] = new MainMenu();
    sceneList[1] = new Level1();
    sceneList[2] = new Level2();
    sceneList[3] = new Level3();
    sceneList[4] = new WinScene();
    sceneList[5] = new LoseScene();
    // will set current scene to Main Menu
    SwitchToScene(sceneList[0]);
}

void ProcessInput() {
    
    if (currentScene != sceneList[0] && currentScene != sceneList[4] && currentScene != sceneList[5]) {
        currentScene->state.player->movement = glm::vec3(0);
    }
    
    
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
                        if (currentScene != sceneList[0] && currentScene != sceneList[4] && currentScene != sceneList[5]) {
                            if(currentScene->state.player->collidedBottom) {
                                Mix_PlayChannel(-1, jump, 0);
                                //Mix_VolumeMusic(MIX_MAX_VOLUME/32);
                                currentScene->state.player->jump = true;
                                
                            }
                        }

                        break;
                    case SDLK_RETURN:
                        if (currentScene == sceneList[0]) {
                            SwitchToScene(sceneList[1]);
                        }
                        break;
                }
                break; // SDL_KEYDOWN
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (currentScene != sceneList[0] && currentScene != sceneList[4] && currentScene != sceneList[5]) {
        if (keys[SDL_SCANCODE_LEFT]) {
            currentScene->state.player->movement.x = -1.0f;
            currentScene->state.player->animIndices = currentScene->state.player->animLeft;
        }
        else if (keys[SDL_SCANCODE_RIGHT]) {
            currentScene->state.player->movement.x = 1.0f;
            currentScene->state.player->animIndices = currentScene->state.player->animRight;
        }
        

        if (glm::length(currentScene->state.player->movement) > 1.0f) {
            currentScene->state.player->movement = glm::normalize(currentScene->state.player->movement);
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
       currentScene->Update(FIXED_TIMESTEP, lives);
       deltaTime -= FIXED_TIMESTEP;
       
   }
    accumulator = deltaTime;

    // update view matrix every new frame
    viewMatrix = glm::mat4(1.0f);
    // translate based on player's x position
    // only scroll if player is past a certain x point
    if (currentScene != sceneList[0] && currentScene != sceneList[4] && currentScene != sceneList[5]) {
        if (currentScene->state.player->position.x > 5) {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(-currentScene->state.player->position.x, 3.75, 0));
        } else { // otherwise, keep view in fixed position
            viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 3.75, 0));
            
        }
        
    }
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    program.SetViewMatrix(viewMatrix);
    
    currentScene->Render(&program);
    if (currentScene == sceneList[1]) {
        levelNum = 1;
    }  else if (currentScene == sceneList[2]) {
        levelNum = 2;
    }  else if (currentScene == sceneList[3]) {
        levelNum = 3;
    }
    if (currentScene != sceneList[0] && currentScene != sceneList[4] && currentScene != sceneList[5]) {
        if (currentScene->state.player->position.x <= 5) { // draw when still
            Util::DrawText(&program, Util::LoadTexture("Assets/pixel_font.png"), "Level " + std::to_string(levelNum),
                     0.2f, 0, glm::vec3(0.75, -0.5, 0));
            
            Util::DrawText(&program, Util::LoadTexture("Assets/pixel_font.png"), "Lives: " + std::to_string(lives),
                     0.2f, 0, glm::vec3(0.75, -1.0, 0));
        } else {
            Util::DrawText(&program, Util::LoadTexture("Assets/pixel_font.png"), "Level " + std::to_string(levelNum),
                     0.2f, 0, glm::vec3(currentScene->state.player->position.x - 4.25, -0.5, 0));
            
            Util::DrawText(&program, Util::LoadTexture("Assets/pixel_font.png"), "Lives: " + std::to_string(lives),
                     0.2f, 0, glm::vec3(currentScene->state.player->position.x - 4.25, -1.0, 0));
        }

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
        // if nextScene is changed to something else than -1, we will switch to that scene
        if (currentScene->state.nextScene >= 0) SwitchToScene(sceneList[currentScene->state.nextScene]);
        Render();
    }
    
    Shutdown();
    return 0;
}


