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

enum EntityType {PLAYER, PLATFORM, ENEMY, TEXT};
enum AIState {IDLE, MOVING};
enum AIType { FLYER, PATROLER, WAITANDGO, IGNORE }; // type of AI -> behavior/style
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
    
    bool jump = false;
    float jumpPower = 0;
    
    float speed;
    
    GLuint textureID;
    
    glm::mat4 modelMatrix;
    
    
    int *animRight = NULL;
    int *animLeft = NULL;

    int *animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;
    std::string direction;
    int rightIdleIndex = 0;
    int leftIdleIndex = 0;
    
    bool isActive = true;
    EntityType lastCollision;
    
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;
    
    Entity();
    
    bool CheckCollision(Entity *other);
    void CheckCollisionsY(Entity *objects, int objectCount, std::string &isWin);
    void CheckCollisionsX(Entity *objects, int objectCount, std::string &isWin);
    void Update(float deltaTime, Entity *player, Entity *enemies, int enemyCount, Entity *platforms, int platformCount, std::string &isWin);
    void Render(ShaderProgram *program);
    void DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index);
    
    void AI(Entity *player);
    void AIFlyer();
    void AIPatroler(); // handles AI's that are Walkers
    void AIWaitAndGo(Entity *player);

    
};



