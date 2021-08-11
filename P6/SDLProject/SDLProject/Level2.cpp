#include "Level2.h"
#define LEVEL2_WIDTH 34
#define LEVEL2_HEIGHT 36

#define LEVEL2_ENEMY_COUNT 14
unsigned int level2_data[] =
{ // 23, 24, 39, 40, 41, 47 - regular tiles no shadow
    // 12, 13 - cracked walls; 6, 26, 27 - non-cracked
    //           //          //          //          //         //          //           //         //           //         //
    0,  1,  2,  8,  8,  1,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    11, 12,  6, 44, 13,  6, 14,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 20, 17, 29, 73, 17, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    22, 30, 24, 39, 23,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,//
    22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,//
    22, 31, 23,  5, 41, 24, 16,  1,  8,  2,  1,  8,  8,  1,  2,  8,  8,  2,  8,  1,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31, 40, 47, 23,  5, 27, 12,  7,  6,  6, 13,  7, 12, 13,  6,  6,  6, 55,  6, 14,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 30, 39,  5,  5, 40, 28, 29, 18, 17, 17, 17, 18, 17, 17, 29, 17, 29, 17, 17, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,//
    22, 31,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,//
    22, 31,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 37,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 36,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 14,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,//
    22, 31,  5,  5,  5,  5, 25,  4,  0,  8,  8,  8,  8,  3,  4,  4,  0,  1,  2,  2,  2,  2,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4, 11,  6,  7, 44,  7,  6, 14,  4, 11,  6,  6, 44,  6,  6, 14,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4, 22, 20, 18, 17, 18, 17, 25,  4, 22, 20, 17, 17, 17, 17, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4, 22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    22, 31,  5,  5,  5,  5, 25,  4, 33, 34,  9,  9,  9,  9, 36,  4, 22, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 16,  8,  8,  8,  8,  8,  8,  8,  8,  8, 15, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5, 27,  6,  6,  6,  6,  6,  6,  6,  6,  6, 26, 31,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  //
    22, 31,  5,  5,  5,  5, 28, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 19,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
    22, 31,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    22, 31,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 25,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    33,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, //
};


void Level2::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    GLuint mapTextureID = Util::LoadTexture("Assets/blue_sewer_tilesheet.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 11, 7);
    
    // --- INITIALIZE GAME OBJECTS ---
    
    // CREATING PLAYER AND INITIATING PROPERTIES
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(2.9, -2.0, 0);
    state.player->movement = glm::vec3(0);
    //state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 10.0f;
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
    state.enemies = new Entity[LEVEL2_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("Assets/Enemies/goblin_run_spritesheet.png");
    // bounds of an enemy -> {min, max, constant position level}
    //    type 1 -> {x min, x max, y constant position level}
    //    type 2 -> {y min, y max, x constant position level}
    std::vector<std::vector<float>> bounds {
        {1.0, 5.0, -5.9},    // 0 - hor
        {1.0, 5.0, -9.9},    // 1 - hor
        {1.0, 5.0, -16.9},   // 2 - hor - left path
        {1.0, 5.0, -20.9},   // 3 - hor - left path
        {1.0, 5.0, -24.9},   // 4 - hor - left path
        {1.0, 5.0, -28.9},   // 5 - hor - left path
        {-34.0,-30.0, 6.9},  // 6 - ver - left path
        {-34.0,-30.0, 10.9}, // 7 - ver - left path
        {-34.0, -30.0, 14.9},// 8 - ver - left path
        {17.0, 21.0, -27.9}, // 9 - hor - left path
        {17.0, 21.0, -23.9}, // 10 - hor - left path
        {-15.0,-11.0, 6.9},  // 11 - ver - right path
        {-15.0,-11.0, 10.9}, // 12 - ver - right path
        {-15.0,-11.0, 14.9}, // 13 - ver - right path
    };
    // array of indices of enemies that are vertical partollers (move up and down)
    std::vector<int> ver = {6,7,8,11,12,13};
    // array of indices of enemies that are horizontal partollers (move left and right)
    std::vector<int> hor = {0,1,2,3,4,5,9,10};
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
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

        state.enemies[i].height = 1.0f;
        state.enemies[i].width = 1.0f;

        state.enemies[i].speed = 1.2;
        state.enemies[i].aiType = PATROLLER;
        state.enemies[i].acceleration = glm::vec3(0, -9.81f, 0);
        state.enemies[i].detectBarriers = true;
    }

    
    // CREATING KEY OBJECT AND INITIALIZING PROPERTIES
    state.key = new Entity();
    state.key->entityType = KEY;
    state.key->position = glm::vec3(11.0,-24.6,0);
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
    state.inventory->width = 0.8f;
    
    state.inventory->isActive = false;
    
    state.objective = "key";
    glClearColor(0.06f,0.02f,0.18f,1.0f);
}
void Level2::Update(float deltaTime, int &lives) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map, lives);
    state.player->Update(deltaTime, state.player, state.key,1, state.map, lives);
    state.key->Update(deltaTime, state.player, state.key, 1, state.map, lives);
    state.inventory->Update(deltaTime, state.player, state.inventory, 1, state.map, lives);
    state.inventory->modelMatrix = glm::scale(state.inventory->modelMatrix, glm::vec3(0.75, 0.75,1.0f));
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map, lives);
    }

    if (state.key->isActive == false) { // if player got key
        state.objective = "exit";
    }
    
    // if player gets to Open Door A (A -> B)
    if (state.player->position.x < 19.5 && state.player->position.x > 18.5 &&
        state.player->position.y == -20.0) {
        state.player->position = glm::vec3(11.0, -21.5, 0);
        state.player->animIndices = state.player->animDown; // facing out from door
        state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map, lives); // update frame
    }
    // if player gets to Open Door B (B -> A)
    if (state.player->position.x < 11.5 && state.player->position.x > 10.5 &&
        state.player->position.y == -20.0) {
        state.player->position = glm::vec3(19.0, -21.5, 0);
        state.player->animIndices = state.player->animDown; // facing out from door
        state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map, lives);  // update frame
    }
    
    // if player gets to locked door
    if (state.player->position.x < 18.5 && state.player->position.x > 17.5 &&
        state.player->position.y == -11.0) {
        if (state.objective == "exit") {
            state.nextScene = 4;
        }
    }
    
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
void Level2::Render(ShaderProgram *program, GLuint fontTextureID) {
    state.map->Render(program);
    state.key->Render(program);
    state.player->Render(program);
    state.inventory->Render(program);
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    if (state.objective == "key") {
        Util::DrawText(program, fontTextureID, "Objective: Find key to the exit",
                 0.2f, 0, glm::vec3(state.player->position.x - 1.5,state.player->position.y + 3.2, 0));
    } else if (state.objective == "exit") {
        Util::DrawText(program, fontTextureID, "Objective: Find the exit",
                 0.2f, 0, glm::vec3(state.player->position.x - 1.5,state.player->position.y + 3.2, 0));
    }
    if (state.player->position.x < 18.5 && state.player->position.x > 17.5 &&
        state.player->position.y == -11.0 && state.objective == "key") {
        Util::DrawText(program, fontTextureID, "Door is locked. Try finding the key first",
                 0.2f, 0, glm::vec3(state.player->position.x - 4.0,state.player->position.y - 2.0, 0));
    }
    
    if (state.player->position.x <= 20.0 && state.player->position.x > 17.0 &&
        state.player->position.y > -23.0 && state.player->position.y < -17.0) {
        Util::DrawText(program, fontTextureID, "Hmmm. I wonder what this door leads to...",
                 0.2f, 0, glm::vec3(state.player->position.x - 4.0,state.player->position.y - 2.0, 0));
    }
    
    // for testing
    Util::DrawText(program, fontTextureID, "X = " + std::to_string(state.player->position.x),
             0.2f, 0, glm::vec3(state.player->position.x,state.player->position.y + 2.2, 0));
    Util::DrawText(program, fontTextureID, "Y = " + std::to_string(state.player->position.y),
             0.2f, 0, glm::vec3(state.player->position.x,state.player->position.y + 1.8, 0));
}
