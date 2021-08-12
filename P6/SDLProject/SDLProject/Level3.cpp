#include "Level3.h"
#define LEVEL3_WIDTH 21
#define LEVEL3_HEIGHT 39

#define LEVEL3_ENEMY_COUNT 7
unsigned int level3_data[] =
{ 
            //          //          //          //          //          //          //
    8,  8,  8,  8,  8,  8,  8,  8,  3,  4,  4,  4,  0,  8,  8,  8,  8,  8,  8,  8,  8,
    6,  6,  6,  6,  6,  6,  6,  6, 16,  8,  8,  1, 15,  6,  6,  6,  6,  6,  6,  6,  6,
   56,  4,  4, 56,  4, 56,  4,  4, 27,  6, 55, 12, 26, 56,  4, 70,  4, 70,  4,  4,  4, //
    4,  4, 56,  4, 70,  4, 46,  5, 28, 29, 17, 17, 29,  5, 48,  4, 56,  4, 70,  4, 56,
    4, 70,  4,  4,  4, 70, 46,  5,  5, 39,  5,  5, 24,  5, 48, 70,  4,  4,  4,  4,  4,
    4,  4,  4, 70,  4,  4, 46, 23,  5,  5,  5, 23,  5, 40, 48,  4,  4, 56,  4, 70,  4, //
   70,  4, 56,  4, 71, 70, 46, 47, 24, 41,  5,  5,  5,  5, 48, 70,  4,  4,  4,  4,  4,
    4, 56,  4,  4,  4,  4, 57, 63, 50,  5, 24,  5, 49, 61, 59,  4, 70,  5, 56,  4, 70,
   56,  4, 70,  4, 56,  4,  4, 70, 46, 23,  5,  5, 48, 56,  4,  4, 56,  4,  4,  4,  4, //
    4, 70,  4,  4,  4, 70,  4, 56, 46,  5, 40,  5, 48,  4,  4, 70,  4,  4, 70,  4, 56,
    4,  4,  4,  4, 56,  4, 70,  4, 46, 39,  5, 24,  5, 23,  5,  5, 40, 48,  4,  4,  4,
    4, 56,  4, 56,  4,  4,  4, 70, 46,  5,  5,  5,  5,  5, 40,  5, 41, 48,  4, 56,  4, //
   70,  4,  4,  4,  4, 56,  4,  4, 46,  5, 23,  5, 39,  5, 24,  5,  5, 48, 70,  4,  4,
    4,  4, 70,  4,  4,  4,  4, 56, 57, 60, 61, 61, 58, 50,  5,  5, 23, 48,  4,  4, 70,
   56,  4,  4,  4, 70, 56,  4,  4,  4, 56,  4,  4, 70, 46, 39,  5,  5, 48,  4, 71,  4, //
    4,  4, 56, 66, 69,  4, 56,  4,  4,  4, 70,  4,  4, 46,  5,  5, 40, 48, 56,  4, 70,
    4, 70,  4,  4, 56,  4,  4,  4, 70,  4,  4, 56,  4, 46,  5, 24,  5, 48,  4,  4,  4,
    4,  4,  4, 46, 23,  5, 40,  5, 41,  5, 24,  5, 23,  5,  5,  5, 41, 48, 56,  4,  4, //
    4,  4, 56, 46,  5, 39,  5, 23,  5,  5,  5,  5,  5, 39,  5,  5,  5, 48,  4, 70,  4,
   56,  4,  4, 46, 24,  5,  5,  5,  5, 23,  5, 39,  5,  5, 23, 40, 47, 48, 56,  4,  4,
    4,  4, 70, 46,  5,  5, 23, 49, 61, 61, 61, 58, 58, 61, 58, 61, 63, 59,  4,  4, 56, //
    4,  4,  4, 46, 39,  5,  5, 48, 56,  4,  4, 70,  4,  4, 56,  4,  4, 70,  4, 70,  4,
    4, 56,  4, 46,  5,  5,  5, 48,  4, 56,  4, 71,  4, 70,  4, 70,  4,  4,  4,  4,  4,
    4,  4, 56, 46,  5, 23,  5, 48,  4,  4, 70,  4,  4,  4, 56,  4, 70,  4, 56,  4,  4, //
    4,  4,  4, 46,  5,  5, 40,  5,  5,  5, 23,  5, 48, 56,  4,  4,  4, 70,  4,  4, 70,
    4,  4, 70, 46, 24, 47,  5,  5, 24,  5,  5, 24, 48,  4, 70,  4, 56,  4,  4,  4,  4,
    4,  4,  4, 46,  5,  5, 23,  5,  5,  5,  5,  5, 48,  4,  4,  4,  4,  4, 70,  4,  4, //
    4, 70,  4, 57, 60, 61, 58, 61, 50, 23,  5, 39, 48, 70,  4, 56,  4, 56,  4, 70,  4,
    4,  4,  4,  4,  4, 70,  4, 70, 46,  5, 24,  5, 48, 56, 66, 69, 70,  4,  4,  4,  4,
    4,  4,  4, 56,  4,  4,  4,  4, 46,  5,  5,  5, 48,  4,  4,  4,  4,  4,  4,  4, 70, //
    4,  4, 70,  4,  4,  4, 46,  5,  5, 40,  5, 23,  5,  5, 48,  4, 56,  4, 56,  4,  4,
    4,  4,  4, 70,  4, 56, 46,  5, 23,  5,  5,  5, 40,  5, 48, 70,  4,  4,  4,  4, 70,
    4, 56,  4,  4,  4,  4, 46,  5, 39,  5, 24,  5,  5, 23, 48,  4, 56,  4,  4, 56,  4,//
    4,  4,  4,  4, 56,  4, 46,  5,  5, 23,  5,  5,  5, 40, 48,  4,  4,  4, 70,  4,  4,
    9,  9,  9,  9,  9,  9,  9,  9, 38,  5,  5, 23, 37,  9,  9,  9,  9,  9,  9,  9,  9,
    4, 70,  4,  4, 56,  4, 70,  4, 22,  5,  5,  5, 25, 56,  4,  4, 56,  4, 70,  4,  4,//
    4,  4,  4, 70,  4,  4,  4,  4, 22, 23,  5,  5, 25,  4, 56,  4,  4,  4,  4,  4,  4,
    4, 56,  4,  4,  4, 56,  4,  4, 22,  5,  5, 24, 25,  4,  4, 70,  4,  4, 56,  4,  4,
    4,  4, 56,  4,  4,  4,  4, 70, 22,  5, 23,  5, 25, 56,  4,  4,  4, 70,  4,  4,  4,//
    4,  4, 56,  4,  4,  4,  4, 70, 33,  9,  9,  9, 36, 56, 56,  4,  4, 70,  4,  4,  4,//


};


void Level3::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    
    Mix_HaltMusic();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_PlayMusic(Mix_LoadMUS("Assets/Sounds/background_music_3.mp3"), -1); // -1 = endless loop
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    GLuint mapTextureID = Util::LoadTexture("Assets/blue_sewer_tilesheet.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 11, 7);
    
    // --- INITIALIZE GAME OBJECTS ---
    
    // CREATING PLAYER AND INITIATING PROPERTIES
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(9.9, -35.0, 0);
    state.player->movement = glm::vec3(0);
    //state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 3.0f;
    state.player->textureID = Util::LoadTexture("Assets/player_spritesheet_more.png");
    
    state.player->animRight = new int[3] {30, 31, 32};
    state.player->animLeft = new int[3] {15, 16, 17};
    state.player->animUp = new int[3] {45, 46, 47};
    state.player->animDown = new int[3] {0, 1, 2};

    state.player->animIndices = state.player->animUp;
    state.player->animFrames = 3;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 15;
    state.player->animRows = 8;
    
    state.player->height = 1.0f;
    state.player->width = 1.0f;
    
    // CREATING ENEMIES AND INITIATING PROPERTIES
    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("Assets/Enemies/fly_anim_spritesheet.png");
    // bounds of an enemy -> {min, max, constant position level}
    //    type 1 -> {x min, x max, y constant position level}
    //    type 2 -> {y min, y max, x constant position level}
    std::vector<std::vector<float>> bounds {
        {7.25, 12.25, -27.8}, // 0 - hor
        {-27.0, -23.0, 7.5},  // 1 - ver
        {2.75, 6.25, -21.8},  // 2 - hor
        {-20.0, -16.0, 7.9},  // 3 - ver
        {-20.0, -16.0, 11.9}, // 4 - ver
        {-20.0, -9.0, 14.5},  // 5 - ver
        {7.75, 12.25, -7.8},  // 6 - hor
        
    };
    // array of indices of enemies that are vertical partollers (move up and down)
    std::vector<int> ver = {1, 3, 4, 5};
    // array of indices of enemies that are horizontal partollers (move left and right)
    std::vector<int> hor = {0, 2, 6};
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].textureID = enemyTextureID;
        
        state.enemies[i].animRight = new int[4] {4,5,6,7};
        state.enemies[i].animLeft = new int[4] {0,1,2,3};
        
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
        state.enemies[i].animFrames = 4;
        state.enemies[i].animIndex = 0;
        state.enemies[i].animTime = 0;
        state.enemies[i].animCols = 4;
        state.enemies[i].animRows = 2;

        state.enemies[i].height = 1.0f;
        state.enemies[i].width = 1.0f;

        state.enemies[i].speed = 1.3;
        state.enemies[i].aiType = PATROLLER;
        state.enemies[i].acceleration = glm::vec3(0, -9.81f, 0);
        state.enemies[i].detectBarriers = false;
    }
    
    // CREATING KEY OBJECT AND INITIALIZING PROPERTIES
    state.key = new Entity();
    state.key->entityType = KEY;
    state.key->position = glm::vec3(9.9, -4.7, 0);
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
    
    state.inventory->isActive = false;
    
    
    state.objective = "key";
    glClearColor(0.06f,0.02f,0.18f,1.0f);
}
void Level3::Update(float deltaTime, int &lives) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map, lives);
    state.player->Update(deltaTime, state.player, state.key,1, state.map, lives);
    state.key->Update(deltaTime, state.player, state.key, 1, state.map, lives);
    state.inventory->Update(deltaTime, state.player, state.inventory, 1, state.map, lives);
    state.inventory->modelMatrix = glm::scale(state.inventory->modelMatrix, glm::vec3(0.75, 0.75,1.0f));
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map, lives);
    }
    
    if (state.key->isActive == false) { // if player got key
        state.objective = "exit";
    }
    
    if (state.player->position.y <= -37.5) { // stops scrolling
        state.player->position.y = -37.5;
    }

    // if player gets to final exit with key, then player wins game
    if (state.player->position.x < 10.4 && state.player->position.x > 9.6 &&
        state.player->position.y == -3.0) {
        if (state.objective == "exit") {
            // door opening sound effect
            Mix_PlayChannel(-1, doorOpenSound, 0);
            Mix_VolumeMusic(MIX_MAX_VOLUME/32);
            state.nextScene = 5;
        }
    }
    
    if (lives == 0) { // if no lives left, then player loses
        state.nextScene = 6;
    }
    
    // if player was turned inactive, the player lost a life
    if (state.player->isActive == false) {
        state.player->isActive = true;
        lives = lives - 1;
        state.player->position = glm::vec3(9.9, -35.0, 0);
    }
}
void Level3::Render(ShaderProgram *program, GLuint fontTextureID) {
    state.map->Render(program);
    state.player->Render(program);
    state.key->Render(program);

    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    state.inventory->Render(program);
    if (state.objective == "key") {
        if (state.player->position.y < -34.5) { // no vertical scrolling -> text adjustment
            Util::DrawText(program, fontTextureID, "Objective: Find key to the exit",
                     0.2f, 0, glm::vec3(state.player->position.x - 1.5, -34.5 + 3.28, 0));
        } else { // vertical scrolling -> text adjustment
            Util::DrawText(program, fontTextureID, "Objective: Find key to the exit",
                     0.2f, 0, glm::vec3(state.player->position.x - 1.5, state.player->position.y  + 3.24, 0));
        }
       
    } else if (state.objective == "exit") {
        if (state.player->position.y < -34.5) {   // no vertical scrolling -> text adjustment
            Util::DrawText(program, fontTextureID, "Objective: Find the exit",
                     0.2f, 0, glm::vec3(state.player->position.x - 1.5, -34.5 + 3.28, 0));
        } else {  // vertical scrolling -> text adjustment
            Util::DrawText(program, fontTextureID, "Objective: Find the exit",
                     0.2f, 0, glm::vec3(state.player->position.x - 1.5,state.player->position.y + 3.24, 0));
        }
    }
    if (state.player->position.x < 10.4 && state.player->position.x > 9.6 &&
        state.player->position.y == -3.0 && state.objective == "key") {
        Util::DrawText(program, fontTextureID, "Door is locked. Try finding the key first",
                 0.2f, 0, glm::vec3(state.player->position.x - 4.0,state.player->position.y - 2.0, 0));
    }
}
