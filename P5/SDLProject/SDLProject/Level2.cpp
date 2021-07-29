#include "Level2.h"
#define LEVEL2_WIDTH 20
#define LEVEL2_HEIGHT 8

#define LEVEL2_ENEMY_COUNT 1
unsigned int level2_data[] =
{
     23, 287, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  23,
     23, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  23,
     46, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  46,
     69, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  84,  69,
     69, 138, 138, 138, 138, 138, 138,   3,   3,   3,   3, 138, 138, 138, 138, 138, 138,   3,   3,  69,
     69, 138, 138, 138, 138,   3, 138, 138, 138, 138, 138, 138, 138, 138, 138,   3, 138,  26,  26,  69,
     92,   3,   3,   3, 138, 138, 138, 138, 138, 138, 138, 138,   3,   3, 138, 138, 138,  26,  26,  92,
    115,  26,  26,  92, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,  26,  26,  115
};




void Level2::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    
    GLuint mapTextureID = Util::LoadTexture("Assets/Background/background_tileset.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 23, 14);
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
    
    state.enemies = new Entity[LEVEL2_ENEMY_COUNT];
    // initiating skeleton warrior properties
    GLuint enemyTextureID_3 = Util::LoadTexture("Assets/Enemies/skeleton_warrior.png");
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID_3;
    
    state.enemies[0].animRight = new int[4] {0,1,3,4};
    state.enemies[0].animLeft = new int[4] {2,5,6,7};
    state.enemies[0].animIndices = state.enemies[0].animRight;
    state.enemies[0].animFrames = 4;
    state.enemies[0].animIndex = 0;
    state.enemies[0].animTime = 0;
    state.enemies[0].animCols = 3;
    state.enemies[0].animRows = 3;
    state.enemies[0].rightIdleIndex = 1;
    state.enemies[0].leftIdleIndex = 3;
    
    state.enemies[0].height = 1.0f;
    state.enemies[0].width = 1.0f;
    
    state.enemies[0].position = glm::vec3(7.0f, -1.0f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = PATROLER;
    state.enemies[0].direction = "right";
    state.enemies[0].acceleration = glm::vec3(0, -9.81f, 0);
}
void Level2::Update(float deltaTime, int &lives) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map, lives, 0.0f, 0.0f);
    
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map, lives, 7.0f, 10.0f);
    }
    
    if (state.player->isActive == false) {
        state.player->isActive = true;
        lives = lives - 1;
        state.player->position = glm::vec3(1.5, -3, 0);
    }
    
    // if player moves far enough to right and comes to where the chest is,
    // they move onto the next level
    if (state.player->position.x > 17.5) {
        state.nextScene = 3;
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
void Level2::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
}

