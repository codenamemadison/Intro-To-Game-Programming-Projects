#include "Level1.h"
#include <vector>
#define LEVEL1_WIDTH 34
#define LEVEL1_HEIGHT 44

#define LEVEL1_ENEMY_COUNT 13
unsigned int level1_data[] =
{
    //           //          //          //          //         //          //           //         //           //         //
    0,  1,  2,  8,  8,  1,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    11, 12,  6,  6, 13,  6, 14,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 20, 17, 29, 73, 17, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    22, 30, 24, 39, 23,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5, 23, 23, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31, 23,  5, 41, 24, 16,  1,  8,  2,  1,  8,  8,  1,  2,  8,  8,  2,  1,  1,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    22, 31, 40, 47, 23,  5, 27, 12,  7,  6,  6, 13,  7, 12, 13,  6,  7,  6, 12,  6, 14,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 30, 39,  5,  5, 40, 28, 29, 18, 17, 17, 17, 18, 17, 17, 29, 18, 17, 17, 73, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5,  5,  5, 24,  5,  5,  5,  5, 39,  5,  5,  5,  5,  5, 39, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    22, 31,  5,  5, 39,  5,  5,  5,  5, 40,  5, 23,  5,  5,  5, 41,  5, 24,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5, 23,  5,  5,  5,  5,  5,  5, 24,  5,  5,  5,  5,  5, 23,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 62, 60, 58, 58, 61, 58, 61, 58, 58, 58, 58, 61, 58, 58,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 42, 23,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5, 41,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 30,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31, 39,  5,  5, 24, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5, 23,  5, 16,  8,  1,  8,  2,  8,  8,  3,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5,  5, 27,  6, 12,  6, 13,  6,  6, 14,  4,  4,  4,  4,  4,  4, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 30,  5, 40,  5,  5, 28, 29, 17, 17, 73, 17, 17, 25,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5, 39,  5,  5, 24,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 30,  5,  5, 24,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5,  5, 41,  5,  5, 39,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5, 23,  5,  5,  5,  5,  5,  5, 24,  5,  5, 25,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5,  5, 37, 38, 42,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5, 24,  5,  5, 14, 11, 31,  5,  5, 40,  5, 25,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5, 24, 14, 11, 30, 23,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 30, 23,  5,  5,  5, 14, 11, 31,  5, 40,  5,  5, 16,  1,  8,  8,  8,  8,  3, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5, 40,  5,  5, 14, 11, 31,  5,  5,  5, 39, 27, 12,  6, 55,  6,  6, 14,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5, 23, 14, 11, 31,  5,  5,  5,  5, 28, 17, 73, 17, 17, 17, 25,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5,  5, 14, 11, 31,  5, 23,  5, 24,  5,  5,  5,  5,  5, 40, 25, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5, 39,  5, 14, 11, 30, 24,  5,  5,  5, 40,  5, 39,  5,  5,  5, 25,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31, 24,  5,  5,  5, 14, 11, 31,  5,  5, 41,  5,  5,  5,  5,  5, 47,  5, 25,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5,  5, 14, 11, 31,  5,  5,  5,  5,  5, 23,  5,  5,  5,  5, 25, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 30,  5,  5, 23,  5, 14, 33,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 36,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5, 40,  5,  5, 14,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5,  5, 14,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5, 24,  5,  5, 16,  8,  2,  8,  8,  1,  3,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5, 23, 27,  6, 13,  6,  6, 12, 14,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5,  5, 28, 17, 17, 29, 17, 73, 25,  4,  4,  4,  4,  4,  4,  4, //
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31, 23,  5, 39,  5,  5,  5,  5,  5, 39,  5, 25,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 30,  5,  5,  5,  5, 39,  5, 24,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5, 47,  5, 23,  5,  5,  5,  5,  5, 23, 25,  4,  4,  4,  4,  4,  4,  4,//
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 22, 31,  5,  5,  5,  5,  5, 24,  5,  5, 23,  5, 25,  4,  4,  4,  4,  4,  4,  4,
    70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 56, 70, 56, 33,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 36,  4,  4,  4,  4,  4,  4,  4,
};


void Level1::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    
    Mix_HaltMusic();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_PlayMusic(Mix_LoadMUS("Assets/Sounds/background_music_1.mp3"), -1); // -1 = endless loop
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    
    GLuint mapTextureID = Util::LoadTexture("Assets/blue_sewer_tilesheet.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 11, 7);
    
    // --- INITIALIZE GAME OBJECTS --- 
    
    // CREATING PLAYER AND INITIATING PROPERTIES
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(2.9, -2.0, 0);
    state.player->movement = glm::vec3(0);
    //state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 3.0f;
    state.player->textureID = Util::LoadTexture("Assets/player_spritesheet_more.png");
    
    state.player->animRight = new int[3] {30, 31, 32};
    state.player->animLeft = new int[3] {15, 16, 17};
    state.player->animUp = new int[3] {45, 46, 47};
    state.player->animDown = new int[3] {0, 1, 2};

    state.player->animIndices = state.player->animDown;
    state.player->animFrames = 3;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 15;
    state.player->animRows = 8;
    
    state.player->height = 1.0f;
    state.player->width = 1.0f;
    
    // CREATING ENEMIES AND INITIATING PROPERTIES
    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("Assets/Enemies/slime_run_spritesheet.png");
    // bounds of an enemy -> {min, max, constant position level}
    //    type 1 -> {x min, x max, y constant position level}
    //    type 2 -> {y min, y max, x constant position level}
    std::vector<std::vector<float>> bounds {
        {-10.0, -7.0, 6.0},    // 0 - ver
        {-10.0, -7.0,  10.0},  // 1 - ver
        {-10.0, -7.0,  14.0},  // 2 - ver
        {15.0, 19.0,  -12.9},  // 3 - hor
        {15.0, 19.0,  -16.9},  // 4 - hor
        {15.0, 19.0,  -23.9},  // 5 - hor - left path
        {15.0, 19.0,  -27.9},  // 6 - hor - left path
        {15.0, 19.0,  -31.9},  // 7 - hor - left path
        {15.0, 19.0,  -35.9},  // 8 - hor - left path
        {-42.0, -38.0,  20.0}, // 9 - ver - left path
        {-22.0, -18.0,  20.9}, // 10 - ver - right path
        {22.0, 26.0,  -22.9},  // 11 - hor - right path
        {22.0, 26.0,  -26.9},  // 12 - hor - right path
    };
    // array of indices of enemies that are vertical partollers (move up and down)
    std::vector<int> ver = {0,1,2,9};
    // array of indices of enemies that are horizontal partollers (move left and right)
    std::vector<int> hor = {3,4,5,6,7,8};
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].textureID = enemyTextureID;
        
        state.enemies[i].animRight = new int[6] {6,7,8,9,10,11};
        state.enemies[i].animLeft = new int[6] {0,1,2,3,4,5};
        
        state.enemies[i].lowerBound = bounds[i][0];
        state.enemies[i].upperBound = bounds[i][1];
        
        if (std::find(ver.begin(), ver.end(), i) != ver.end()) { // if a vertical patroller
            state.enemies[i].patrollerType = "vertical";
            state.enemies[i].animIndices = state.enemies[i].animRight;
            if (i % 2 == 0) { // alternating starting points
                state.enemies[i].direction = "up";
                state.enemies[i].position = glm::vec3(bounds[i][2], state.enemies[i].lowerBound + 0.1, 0);
            } else {
                state.enemies[i].direction = "down";
                state.enemies[i].position = glm::vec3(bounds[i][2], state.enemies[i].upperBound - 0.1, 0);
            }
        } else {
            state.enemies[i].patrollerType = "horizontal";
            if (i % 2 == 0) { // alternating starting points
                state.enemies[i].animIndices = state.enemies[i].animRight;
                state.enemies[i].direction = "right";
                state.enemies[i].position = glm::vec3(state.enemies[i].lowerBound + 0.1, bounds[i][2], 0);
            } else {
                state.enemies[i].animIndices = state.enemies[i].animLeft;
                state.enemies[i].direction = "left";
                state.enemies[i].position = glm::vec3(state.enemies[i].upperBound - 0.1, bounds[i][2], 0);
            }
        }
        state.enemies[i].animFrames = 6;
        state.enemies[i].animIndex = 0;
        state.enemies[i].animTime = 0;
        state.enemies[i].animCols = 6;
        state.enemies[i].animRows = 2;
        
        state.enemies[i].height = 0.8f;
        state.enemies[i].width = 1.0f;

        state.enemies[i].speed = 1.2;
        state.enemies[i].aiType = PATROLLER;
        state.enemies[i].acceleration = glm::vec3(0, -9.81f, 0);
        state.enemies[i].detectBarriers = true;
    }

    // CREATING KEY OBJECT AND INITIALIZING PROPERTIES
    state.key = new Entity();
    state.key->entityType = KEY;
    state.key->position = glm::vec3(24.0, -39.8, 0);
    state.key->textureID = Util::LoadTexture("Assets/Loot/key-white.png");
    
    state.key->animRight = new int[12] {0,1,2,3,4,5,6,7,8,9,10,11};

    state.key->animIndices = state.player->animRight;
    state.key->animFrames = 12;
    state.key->animIndex = 0;
    state.key->animTime = 0;
    state.key->animCols = 12;
    state.key->animRows = 1;
    
    state.key->height = 1.0f;
    state.key->width = 0.8f;
    
    // INITIALIZING INVENTORY
    state.inventory = new Entity();
    state.inventory->entityType = IGNORE;
    state.inventory->position = glm::vec3(0, 0, 0);
    state.inventory->movement = glm::vec3(0);
    state.inventory->textureID = Util::LoadTexture("Assets/Loot/key-white.png");
    
    state.inventory->animRight = new int[1] {0};

    state.inventory->animIndices = state.player->animRight;
    state.inventory->animFrames = 1;
    state.inventory->animIndex = 0;
    state.inventory->animTime = 0;
    state.inventory->animCols = 12;
    state.inventory->animRows = 1;
    
    state.inventory->height = 1.0f;
    state.inventory->width = 1.0f;
    //state.inventory->modelMatrix = glm::scale(state.inventory->modelMatrix, glm::vec3(0.2, 0.2,1.0f));
    
    state.inventory->isActive = false;
    
    // INITIALIZING OBJECTIVE
    state.objective = "key";
    
    glClearColor(0.06f,0.02f,0.18f,1.0f);
    

}
void Level1::Update(float deltaTime, int &lives) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map, lives);
    state.player->Update(deltaTime, state.player, state.key,1, state.map, lives);
    state.key->Update(deltaTime, state.player, state.key, 1, state.map, lives);
    state.inventory->Update(deltaTime, state.player, state.inventory, 1, state.map, lives);
    state.inventory->modelMatrix = glm::scale(state.inventory->modelMatrix, glm::vec3(0.75, 0.75,1.0f));
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map, lives);
    }
    
    if (state.key->isActive == false) { // if player got key
        state.objective = "exit";

    }
    
    // if player gets to locked door
    if (state.player->position.x < 30.4 && state.player->position.x > 29.6 &&
        state.player->position.y == -28.0) {
        if (state.objective == "exit") { // goes to next level if has key
            // door opening sound effect
            Mix_PlayChannel(-1, doorOpenSound, 0);
            Mix_VolumeMusic(MIX_MAX_VOLUME/32);
            state.nextScene = 3;
        }
    }
    
    // HANDLING NUMBER OF LIVES
    
    if (lives == 0) { // if no lives left, then player loses
        state.nextScene = 6;
    }
    // if player was turned inactive, the player lost a life
    if (state.player->isActive == false) {
        state.player->isActive = true;
        lives = lives - 1;
        state.player->position = glm::vec3(2.9, -2.0, 0);
    }
    
}
void Level1::Render(ShaderProgram *program, GLuint fontTextureID) {
    state.map->Render(program);
    state.player->Render(program);
    state.key->Render(program);

    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    state.inventory->Render(program);
    if (state.objective == "key") {
        Util::DrawText(program, fontTextureID, "Objective: Find key to the exit",
                 0.2f, 0, glm::vec3(state.player->position.x - 1.5,state.player->position.y + 3.2, 0));
    } else if (state.objective == "exit") {
        Util::DrawText(program, fontTextureID, "Objective: Find the exit",
                 0.2f, 0, glm::vec3(state.player->position.x - 1.5,state.player->position.y + 3.2, 0));
    }
    if (state.player->position.x < 30.5 && state.player->position.x > 29.5 &&
        state.player->position.y == -28.0 && state.objective == "key") {
        Util::DrawText(program, fontTextureID, "Door is locked. Try finding the key first",
                 0.2f, 0, glm::vec3(state.player->position.x - 4.0,state.player->position.y - 2.0, 0));
    }
}
