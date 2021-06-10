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
glm::mat4 viewMatrix, sonicMatrix, coin1Matrix, coin2Matrix, coin3Matrix, backgroundMatrix, projectionMatrix;

float sonic_x = 0;
float sonic_rotate = 0;

float coin_ub = -0.7f;
float coin_lb = -1.4f;

float coin_y13 = coin_ub - 0.5f;
float coin_y2 = coin_lb + 0.5f;

GLuint sonicTextureID;
GLuint coin1TextureID;
GLuint coin2TextureID;
GLuint coin3TextureID;
GLuint backgroundTextureID;

// loads texture onto video card
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

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    // create a window with these details
    displayWindow = SDL_CreateWindow("Project 1 - Madison Shimbo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context); // stating that following instructions will be for this window
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    // setting up shader program (to translate points and fill the shapes)
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    sonicMatrix = glm::mat4(1.0f);
    coin1Matrix = glm::mat4(1.0f);
    coin2Matrix = glm::mat4(1.0f);
    coin3Matrix = glm::mat4(1.0f);
    backgroundMatrix = glm::mat4(1.0f);
    // what part of world we see
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    // use the shader program mentioned
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // stating the background color of when you clear the window and what color to draw with
    
    glEnable(GL_BLEND);
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     
    sonicTextureID = LoadTexture("sonic_running.png");
    coin1TextureID = LoadTexture("sonic_gold_ring.png");
    coin2TextureID = LoadTexture("sonic_gold_ring.png");
    coin3TextureID = LoadTexture("sonic_gold_ring.png");
    backgroundTextureID = LoadTexture("sonic-background.png");
}

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            gameIsRunning = false;
        }
    }
}

bool goingUp13 = true;  // notes direction of coin 1 and 3
bool goingUp2 = false;  // notes direction of coin 2
float lastTicks = 0.0f;
void Update() {
    // every frame lets update position/scale - we will try to ignore z-values or at least not regard them as much
    
    // SDL_GetTicks = # of millisec since we initialized SDL
    float ticks = (float)SDL_GetTicks() / 1000.0f; // in sec

    // subtract what it was last frame to get time between two frames
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    // initializing info and positions for sonic
    sonic_x += 1.0f * deltaTime; // move one unit per sec
    sonic_rotate += -360.0f * deltaTime; // rotate 90 degrees per sec
    sonicMatrix = glm::mat4(1.0f); // initialize identity matrix for sonic
    sonicMatrix = glm::translate(sonicMatrix, glm::vec3(-4.0f, -1.0f, 0.0f)); // initialize original position
    sonicMatrix = glm::scale(sonicMatrix, glm::vec3(1.2f, 1.2f, 1.2f));
    
    // handling directions for coin 1 and 3 (should be matching)
    if (goingUp13) {
        coin_y13 += 0.5f * deltaTime; // move one unit per sec
    } else {
        coin_y13 -= 0.5f * deltaTime; // move one unit per sec
    }
    
    // handling directions for coin 2
    if (goingUp2) {
        coin_y2 += 0.5f * deltaTime; // move one unit per sec
    } else {
        coin_y2 -= 0.5f * deltaTime; // move one unit per sec
    }
    
    // initailizing identity matrixes for coins to start at certain positions
    coin1Matrix = glm::mat4(1.0f); // initialize identity matrix for coin
    coin1Matrix = glm::translate(coin1Matrix, glm::vec3(-1.0f, coin_y13, 0.0f)); // initialize original position

    coin2Matrix = glm::mat4(1.0f); // initialize identity matrix for coin
    coin2Matrix = glm::translate(coin2Matrix, glm::vec3(1.0f, coin_y2, 0.0f)); // initialize original position
    
    coin3Matrix = glm::mat4(1.0f); // initialize identity matrix for coin
    coin3Matrix = glm::translate(coin3Matrix, glm::vec3(3.0f, coin_y13, 0.0f)); // initialize original position
  
    // resizing coins
    coin1Matrix = glm::scale(coin1Matrix, glm::vec3(0.8f, 0.8f, 0.8f));
    coin2Matrix = glm::scale(coin2Matrix, glm::vec3(0.8f, 0.8f, 0.8f));
    coin3Matrix = glm::scale(coin3Matrix, glm::vec3(0.8f, 0.8f, 0.8f));

    // initializing identity matrix for background
    backgroundMatrix = glm::mat4(1.0f);
    backgroundMatrix = glm::translate(backgroundMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // initialize original position
    backgroundMatrix = glm::scale(backgroundMatrix, glm::vec3(7.5f, 7.5f, 0.0f));

    // handling transformations for sonic
    if (sonic_x < 6.5f) { // sonic rolls across screen
        sonicMatrix = glm::translate(sonicMatrix, glm::vec3(sonic_x, -1.0f, 0.0f));
        sonicMatrix = glm::rotate(sonicMatrix, glm::radians(sonic_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    } else { // if it reaches end of background then sonic restarts
        sonic_x = 0.0f;
        sonicMatrix = glm::translate(sonicMatrix, glm::vec3(sonic_x, -1.0f, 0.0f));
    }

    // handling transformations for coin 1 and 3 (should be matching)
    if (coin_y13 >= -0.7f) { // if too high out of height range, change direction to down
        goingUp13 = false;
        coin1Matrix = glm::translate(coin1Matrix, glm::vec3(0.0f, coin_y13 - 0.01f, 0.0f));
        coin3Matrix = glm::translate(coin3Matrix, glm::vec3(0.0f, coin_y13 - 0.01f, 0.0f));
    } else if (coin_y13 <= -1.4f)  { // if too low out of height range, change direction to up
        goingUp13 = true;
        coin1Matrix = glm::translate(coin1Matrix, glm::vec3(0.0f, coin_y13 + 0.01f, 0.0f));
        coin3Matrix = glm::translate(coin3Matrix, glm::vec3(0.0f, coin_y13 + 0.01f, 0.0f));
    } else { // if within height range
        coin1Matrix = glm::translate(coin1Matrix, glm::vec3(0.0f, coin_y13, 0.0f));
        coin3Matrix = glm::translate(coin3Matrix, glm::vec3(0.0f, coin_y13, 0.0f));
    }
     
    // handling transformations for coin 2
    if (coin_y2 >= -0.7f) { // if too high out of height range, change direction to down
        goingUp2 = false;
        coin2Matrix = glm::translate(coin2Matrix, glm::vec3(0.0f, coin_y2 - 0.01f, 0.0f));
    } else if (coin_y2 <= -1.4f)  { // if too low out of height range, change direction to up
        goingUp2 = true;
        coin2Matrix = glm::translate(coin2Matrix, glm::vec3(0.0f, coin_y2 + 0.01f, 0.0f));
    } else { // if within height range
        coin2Matrix = glm::translate(coin2Matrix, glm::vec3(0.0f, coin_y2, 0.0f));
    }
    
}


void Render() {
   glClear(GL_COLOR_BUFFER_BIT);
   
    // need to match vertices of two triangles of sprites with UV coordinates
   float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
   float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
   
    // use these vertices and texCooroords and the given texture to draw triangles with given vertices
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
   glEnableVertexAttribArray(program.positionAttribute);
   glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
   glEnableVertexAttribArray(program.texCoordAttribute);
    
    program.SetModelMatrix(backgroundMatrix);
    glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    
   program.SetModelMatrix(sonicMatrix);
   glBindTexture(GL_TEXTURE_2D, sonicTextureID);
   glDrawArrays(GL_TRIANGLES, 0, 6);
    
   program.SetModelMatrix(coin1Matrix);
   glBindTexture(GL_TEXTURE_2D, coin1TextureID);
   glDrawArrays(GL_TRIANGLES, 0, 6);
    
    program.SetModelMatrix(coin2Matrix);
    glBindTexture(GL_TEXTURE_2D, coin2TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    program.SetModelMatrix(coin3Matrix);
    glBindTexture(GL_TEXTURE_2D, coin3TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    
   glDisableVertexAttribArray(program.positionAttribute);
   glDisableVertexAttribArray(program.texCoordAttribute);
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

