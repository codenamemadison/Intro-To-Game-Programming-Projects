#pragma once
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
#include "Map.h"

enum EntityType {PLAYER, PLATFORM, ENEMY, KEY, FOOD, IGNORE};
enum AIState {IDLE, MOVING};
enum AIType {PATROLLER}; // type of AI -> behavior/style
class Entity {
public:
    EntityType entityType;
    AIType aiType;
    AIState aiState;
    
    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 acceleration;
    glm::vec3 velocity;
    
    // assuming width and height of entities in world is 1
    float width = 1;
    float height = 1;
    
    float speed;
    
    GLuint textureID;
    
    glm::mat4 modelMatrix;
    
    int *animRight = NULL;
    int *animLeft = NULL;
    int *animUp = NULL;
    int *animDown = NULL;
    
    std::string actionType; // can be "idle", "jump", "run"
    std::string direction;
    std::string patrollerType; // can be "vertical" (meaning y value changes) or "horizontal" (meaning x value changes)

    int *animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;
    
    int rightIdleIndex = 0;
    int leftIdleIndex = 0;
    
    bool isActive = true;
    
    EntityType lastCollision;
    
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;
    
    // for patrollers
    float lowerBound;
    float upperBound;
    bool detectBarriers;
    
    Entity();
    
    bool CheckCollision(Entity *other);
    // check with some kind of AI specifically (or something else specific in our world)
    void CheckCollisionsY(Entity *objects, int objectCount);
    void CheckCollisionsX(Entity *objects, int objectCount);
    // check with map
    void CheckCollisionsX(Map *map);
    void CheckCollisionsY(Map *map);
    
    //void Update(float deltaTime, Entity *player, Entity *platforms, int platformCount); - OLD
    void Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map, int &lives);
    void Render(ShaderProgram *program);
    void DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index);
    
    void AI(Entity *player);
    void AIPatroller(); // handles AI's that are Walkers
    
};

