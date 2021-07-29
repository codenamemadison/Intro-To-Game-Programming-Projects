#include "Level1.h"
#define LEVEL1_WIDTH 20
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMY_COUNT 2
unsigned int level1_data[] =
{
     23, 287, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  23,
     23, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  23,
     46, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  46,
     69, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  84,  69,
     69, 138, 138, 138, 138, 138, 138, 138, 138,   3,   3, 138, 138, 138, 138, 138, 138,   3,   3,  69,
     69, 138, 138, 138, 138, 138, 138, 138,   3,  25,  26, 138, 138,   3,   3,   3,   3,  25,  26,  69,
     92,   3,   3,   3,   3,   3,   3,   3,   3,  26,  26, 138, 138,  26,  26,  69,  26,  26,  26,  92,
    115,  26,  26,  92,  26,  26,  26,  92,  26,  26,  26, 138, 138,  26,  26,  92,  26,  26,  26,  115
};


void Level1::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    GLuint mapTextureID = Util::LoadTexture("Assets/Background/background_tileset.png");
    // 52 columns and 15 rows wo border
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 23, 14);
    // Move over all of the player and enemy code from initialization.
    // Initialize Game Objects
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1.5, -3, 0);
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
    
    // intializing horse properties (waitandgo)
    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    
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

    state.enemies[0].position = glm::vec3(6.5f, -5.0f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].direction = "left";
    
    
    // initiating flying eye properties
    GLuint enemyTextureID_2 = Util::LoadTexture("Assets/Enemies/flying_eye.png");
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID_2;
    
    state.enemies[1].animRight = new int[8] {0,1,2,6,7,8,12,13};
    state.enemies[1].animLeft = new int[8] {3,4,5,9,10,11,16,17};
    state.enemies[1].animIndices = state.enemies[2].animRight;
    state.enemies[1].animFrames = 8;
    state.enemies[1].animIndex = 0;
    state.enemies[1].animTime = 0;
    state.enemies[1].animCols = 6;
    state.enemies[1].animRows = 3;
    state.enemies[1].rightIdleIndex = 0;
    state.enemies[1].leftIdleIndex = 5;
    
    state.enemies[1].height = 1.0f;
    state.enemies[1].width = 1.0f;
    
    state.enemies[1].position = glm::vec3(13.0f, -3.0f, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = PATROLER;
    state.enemies[1].direction = "right";
    state.enemies[1].acceleration = glm::vec3(0, -9.81f, 0);
}
void Level1::Update(float deltaTime, int &lives) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map, lives, 0.0f, 0.0f);
    
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map, lives, 13.0f, 16.5f);
    }
    // if player moves far enough to right and comes to where the chest is,
    // they move onto the next level
    if (state.player->position.x > 17.5) {
        state.nextScene = 2;
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
void Level1::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
}
