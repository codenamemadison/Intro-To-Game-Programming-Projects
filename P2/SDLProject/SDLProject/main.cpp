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

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, paddleLeftMatrix, paddleRightMatrix, ballMatrix, projectionMatrix;


GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    // loads image into RAM
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);
    if (image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
}
    /* creates and bind texture ID so rest of commands are about the same texture then puts raw image data (image) onto video card with ID texture number we created
     */
    GLuint textureID;
    glGenTextures(1, &textureID); // creates texture ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    // sending image data to graphics card
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    // uses nearest neighbor filter (pixel-like)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // free up space image took up in main memory since a copy of image is now in video card memory
    stbi_image_free(image);
    return textureID;
}

// intialize player positions
glm::vec3 player_left_position = glm::vec3(-4.8f, 0.0f, 0.0f);
glm::vec3 player_right_position = glm::vec3(4.8f, 0.0f, 0.0f);
// Don’t go anywhere (yet).
glm::vec3 player_left_movement = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 player_right_movement = glm::vec3(0.0f, 0.0f, 0.0f);
 
// initialize ball position and movement
glm::vec3 ball_position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 ball_movement = glm::vec3(1.0f, 1.0f, 0.0f);
float ball_x = 0;
float ball_y = 0;

float player_speed = 0.0f;

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Project 2 - Madison Shimbo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex.glsl", "shaders/fragment.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    paddleLeftMatrix = glm::mat4(1.0f);
    paddleRightMatrix = glm::mat4(1.0f);
    ballMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    glEnable(GL_BLEND);
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ProcessInput() {
    // if nothing is pressed, player does not move
    player_left_movement = glm::vec3(0);
    player_right_movement = glm::vec3(0);
    
    // watch events to see if certain instances occur or if certain keys are pressed
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
       switch (event.type) {
           case SDL_QUIT:
           case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
           case SDL_KEYDOWN:
               switch (event.key.keysym.sym) {
                   case SDLK_SPACE:
                       player_speed = 2.0f;
                       break;
               }
               break; // SDL_KEYDOWN
               
       }
   }
    // not an event -> just seeing value of pointer
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    // handling Player One (movement of left paddle)
    if (keys[SDL_SCANCODE_W] && player_left_position.y <= 3.0f) {
        player_left_movement.y = 1.0f;
    }
    else if (keys[SDL_SCANCODE_S] && -3.0f <= player_left_position.y) {
        player_left_movement.y = -1.0f;
    }
    
    // if two keys are held down (diagonal), prevents faster movement (will just move at same speed)
    if (glm::length(player_left_movement) > 1.0f) {
        player_left_movement = glm::normalize(player_left_movement);
    }
    
    // handling Player Two (movement of right paddle)
    if (keys[SDL_SCANCODE_UP] && player_right_position.y <= 3.0f) {
        player_right_movement.y = 1.0f;
    }
    else if (keys[SDL_SCANCODE_DOWN] && -3.0f <= player_right_position.y) {
        player_right_movement.y = -1.0f;
    }
    
    // if two keys are held down (diagonal), prevents faster movement (will just move at same speed)
    if (glm::length(player_right_movement) > 1.0f) {
        player_right_movement = glm::normalize(player_right_movement);
    }
    
}

float lastTicks = 0.0f;
float w_paddle = 0.4f;
float h_paddle = 1.5f;
float w_ball = 0.4f;
float h_ball = 0.4f;
// checks if ball is colliding with given paddle
void iscollidingWithPaddle(glm::vec3 paddle_position) {
    float x1 = ball_position.x;
    float x2 = paddle_position.x;
    float y1 = ball_position.y;
    float y2 = paddle_position.y;
    // (displacement between centers of ball and paddle) - (smallest displacement between centers possible wo overlap)
    float xdist = fabs(x2 - x1) - ((w_paddle + w_ball) / 2.0f);
    float ydist = fabs(y2 - y1) - ((h_paddle + h_ball) / 2.0f);
    if (xdist <= 0 && ydist <= 0) { // collides with paddle
        ball_movement.x *= -1;
    }
}

void Update() {
    // every frame lets update position/scale - we will try to ignore z-values or at least not regard them as much
    
    // SDL_GetTicks = # of millisec since we initialized SDL
    float ticks = (float)SDL_GetTicks() / 1000.0f; // in sec

    // subtract what it was last frame to get time between two frames
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    
    // Add (direction * units per second * elapsed time)
    player_left_position += player_left_movement * player_speed * deltaTime;
    player_right_position += player_right_movement * player_speed * deltaTime;
    ball_position += ball_movement * player_speed * deltaTime;
    
    
    // intialize identity matrixes for two  paddles and ball
    paddleLeftMatrix = glm::mat4(1.0f);
    paddleRightMatrix = glm::mat4(1.0f);
    ballMatrix = glm::mat4(1.0f);

    // ball bounces off top and bottom of screen
    if (ball_position.y >= 3.55f || ball_position.y <= -3.55f) {
        ball_movement.y *= -1;
    }
    // if ball collides with wall (not paddle), then ball stops moving
    if (ball_position.x >= 4.8f || ball_position.x <= -4.8f) {
        ball_movement.x = 0.0f;
        ball_movement.y = 0.0f;
        ball_movement.z = 0.0f;
    } else { // checks if collides with right or left paddle
        // x and y distances of ball and left paddle
        iscollidingWithPaddle(player_left_position);
        iscollidingWithPaddle(player_right_position);
    }
    
    // update position of paddles and ball
    paddleLeftMatrix = glm::translate(paddleLeftMatrix, player_left_position);
    paddleRightMatrix = glm::translate(paddleRightMatrix, player_right_position);
    ballMatrix = glm::translate(ballMatrix, ball_position);
    
}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // set up paddles and ball
    program.SetModelMatrix(paddleLeftMatrix);
    float paddle_Left_Vertices[] = {0.2f, -0.75f, 0.2f, 0.75f, -0.2f, -0.75f, -0.2f, 0.75f};
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, paddle_Left_Vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    program.SetModelMatrix(paddleRightMatrix);
    float paddle_Right_Vertices[] = {0.2f, -0.75f, 0.2f, 0.75f, -0.2f, -0.75f, -0.2f, 0.75f};
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, paddle_Right_Vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    program.SetModelMatrix(ballMatrix);
    float ball_Vertices[] = {0.2f, -0.2f, 0.2f, 0.2f, -0.2f, -0.2f, -0.2f, 0.2f};
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, ball_Vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    

    glDisableVertexAttribArray(program.positionAttribute);
    
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
