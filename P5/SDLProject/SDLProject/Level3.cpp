#include "Level3.h"
#define LEVEL3_WIDTH 20
#define LEVEL3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 2
unsigned int level3_data[] =
{
     23, 287, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  23,
     23, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  23,
     46, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  84,  46,
     69, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,   3,   3,   3,
     69, 138, 138,   3,   3,   3,   3,   3, 138, 138, 138, 138, 138, 138, 138,   3, 138,  26,  26,  69,
     69,   3,   3,  25,  26,  26,  26,  69, 138, 138, 138, 138, 138, 138,   3,  25, 138,  26,  26,  69,
     92,  26,  26,  69,  26,  26,  26,  92, 138,   3,   3,   3,   3, 138, 138, 138, 138,  26,  26,  92,
    115,  26,  26,  92,  26,  26,  26, 115, 138, 138, 138, 138, 138, 138, 138, 138, 138,  26,  26, 115
};



void Level3::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    
    GLuint mapTextureID = Util::LoadTexture("Assets/Background/background_tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 23, 14);
    // Move over all of the player and enemy code from initialization.
    // Initialize Game Objects
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1.0, -4, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("Assets/Player/player_run_spritesheet.png");
    
    state.player->leftIdleIndex = 9;
    state.player->rightIdleIndex = 0;
    
    state.player->animRight = new int[10] {0, 1, 2, 3, 4, 5, 6, 7,8,9};
    state.player->animLeft = new int[10] {10, 11, 12, 13, 14, 15,16,17,18,19};

    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 10;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 10;
    state.player->animRows = 2;
    
    state.player->height = 1.0f;
    state.player->width = 1.0f;
    
    state.player->jumpPower = 7.0f;
    

    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    
    // initiating horse properties
    GLuint enemyTextureID_1 = Util::LoadTexture("Assets/Enemies/horse.png");
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID_1;
    
    state.enemies[0].animRight = new int[4] {0,1,2,3};
    state.enemies[0].animLeft = new int[4] {4,5,6,7};
    state.enemies[0].animIndices = state.enemies[0].animLeft;
    state.enemies[0].animFrames = 4;
    state.enemies[0].animIndex = 0;
    state.enemies[0].animTime = 0;
    state.enemies[0].animCols = 4;
    state.enemies[0].animRows = 2;
    state.enemies[0].rightIdleIndex = 1;
    state.enemies[0].leftIdleIndex = 5;
    
    state.enemies[0].height = 1.0f;
    state.enemies[0].width = 1.0f;

    state.enemies[0].position = glm::vec3(7.0f, -3.0f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].direction = "left";
    
    // initiating skeleton warrior properties
    GLuint enemyTextureID_2 = Util::LoadTexture("Assets/Enemies/skeleton_warrior.png");
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID_2;
    
    state.enemies[1].animRight = new int[4] {0,1,3,4};
    state.enemies[1].animLeft = new int[4] {2,5,6,7};
    state.enemies[1].animIndices = state.enemies[0].animRight;
    state.enemies[1].animFrames = 4;
    state.enemies[1].animIndex = 0;
    state.enemies[1].animTime = 0;
    state.enemies[1].animCols = 3;
    state.enemies[1].animRows = 3;
    state.enemies[1].rightIdleIndex = 1;
    state.enemies[1].leftIdleIndex = 3;
    
    state.enemies[1].height = 1.0f;
    state.enemies[1].width = 1.0f;
    
    state.enemies[1].position = glm::vec3(9.0f, -5.0f, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = PATROLER;
    state.enemies[1].direction = "right";
    state.enemies[1].acceleration = glm::vec3(0, -9.81f, 0);
}
    
    
void Level3::Update(float deltaTime, int &lives) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map, lives, 0.0f, 0.0f);
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map, lives, 9.0f, 12.0f);
    }
    
    if (state.player->isActive == false) {
        state.player->isActive = true;
        lives = lives - 1;
        state.player->position = glm::vec3(1.5, -3, 0);
    }
    
    // if player moves far enough to right and comes to where the chest is,
    // they win the game
    if (state.player->position.x > 17.5) {
        state.nextScene = 4;
    }
    if (lives == 0) { // if no lives left, then player loses
        state.nextScene = 5;
    }
    
    // if player was turned inactive, the player lost a life
    if (state.player->isActive == false) {
        state.player->isActive = true;
        lives = lives - 1;
        state.player->position = glm::vec3(1.5, -3, 0);
    }
}
void Level3::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
}

