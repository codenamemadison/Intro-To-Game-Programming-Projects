#include "Entity.h"

Entity::Entity()
{
    position = glm::vec3(0);
    movement = glm::vec3(0);
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    speed = 0;
    
    modelMatrix = glm::mat4(1.0f);
}

// checking if entity collides with another entitiy
bool Entity::CheckCollision(Entity *other) {
    if (other == this) return false; // avoids colliding-self issue
    
    if (isActive == false || other->isActive == false) return false;
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    
    // if collision occurs
    if (xdist < 0 && ydist < 0 ) {
        lastCollision = other->entityType;
        return true;
    }
        
    return false;
}


void Entity::CheckCollisionsY(Entity *objects, int objectCount, std::string &isWin)
{
   for (int i = 0; i < objectCount; i++)
   {
       Entity *object = &objects[i];
       if (CheckCollision(object))
       {
           float ydist = fabs(position.y - object->position.y);
           // how much the entity is penetrating the platforms
           float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
           // if we are jumping up into a platform, we fix by moving down
           if (velocity.y > 0) {
               position.y -= penetrationY;
               // if we hit a platform, we stop moving
               velocity.y = 0;
               collidedTop = true;
               if (this->entityType == PLAYER && object->entityType == ENEMY) { // if player is touched by enemy, you lose game
                   isWin = "loss";
               }
           }
           // if we are falling into a platform, we fix by moving up
           else if (velocity.y < 0) {
               position.y += penetrationY;
               // if we hit a platform, we stop moving
               velocity.y = 0;
               collidedBottom = true;
               if (this->entityType == PLAYER && object->entityType == ENEMY)  { // if player jumps on enemy, enemy disappears
                   object->isActive = false;
               }
           }
       }
   }
}

void Entity::CheckCollisionsX(Entity *objects, int objectCount, std::string &isWin)
{
   for (int i = 0; i < objectCount; i++)
   {
       Entity *object = &objects[i];
       if (CheckCollision(object))
       {
           // correcting an error if player is still when horse/skeleton moves past them
           if (this->entityType == PLAYER && (object->aiType == WAITANDGO || object->aiType == PATROLER)) {
               isWin = "loss";
           }
           
           float xdist = fabs(position.x - object->position.x);
           float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
           if (velocity.x > 0) {
               position.x -= penetrationX;
               velocity.x = 0;
               collidedRight = true;
               if (this->entityType == PLAYER && object->entityType == ENEMY)  { // if player is touched by enemy, you lose game
                   isWin = "loss";
               }
           }
           else if (velocity.x < 0) {
               position.x += penetrationX;
               velocity.x = 0;
               collidedLeft = true;
               if (this->entityType == PLAYER && object->entityType == ENEMY) { // if player is touched by enemy, you lose game
                   isWin = "loss";
               }
           }
       }
   }
}

// dealt with behavior of flyer
void Entity::AIFlyer() {
    if (position.y >= 2.75f) {
        movement = glm::vec3(0,-1,0);
        direction = "down";
    } else if (position.y <= -1.0f) {
        movement = glm::vec3(0,1,0);
        direction = "up";
    } else if (position.y < 2.75f && position.y > -1.0f) {
        if (direction == "down") {
            movement = glm::vec3(0,-1,0);
            
        } else {
            movement = glm::vec3(0,1,0);
        }
    }
}
 
// dealt with behavior of patroler
void Entity::AIPatroler() {
    if (position.x >= 1.8f) {
        movement.x = -1;
        direction = "left";
    } else if (position.x <= -1.8f) {
        movement.x = 1;
        direction = "right";
    } else if (-2.2f < position.x && position.x < 2.3f) {
        if (direction == "left") {
            animIndices = animLeft;
            movement.x = -1;
        } else {
            animIndices = animRight;
            movement.x = 1;
        }
    }
     
}

void Entity::AIWaitAndGo(Entity *player) {
    switch(aiState) {
        case IDLE:
            /* checking if player gets "too close" and if so the
               AI will switch states ("wakes up") and start walking
               toward the player */
            if (glm::distance(position, player->position) < 3.0f) {
                aiState = MOVING;
            }
            break;
        case MOVING: // AI will walk toward player
            // if player is to the left of the AI, the AI will move to the left (toward the player)
            if (player->position.x < position.x) {
                animIndices = animLeft;
                movement = glm::vec3(-1,0,0); // AI moves to left
                
            } else {
                // if player is to the right of the AI, the AI will move to the right (toward the player)
                animIndices = animRight;
                movement = glm::vec3(1,0,0); // AI moves to right
            }
            break;
    }
}


// creating a sort of "library" for AI behaviors
void Entity::AI(Entity *player) {
    switch(aiType) {
        case FLYER:
            AIFlyer();
            break;
        case PATROLER:
            AIPatroler();
            break;
        case WAITANDGO:
            AIWaitAndGo(player);
            break;
    }
}


// checks if current entity has collided with "player" or whatever the other entity is
void Entity::Update(float deltaTime, Entity *player, Entity *enemies, int enemyCount, Entity *platforms, int platformCount, std::string &isWin)
{
    if (isActive == false) return;
    
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    
    if (entityType == ENEMY) {
        AI(player);
    }
    
    if (animIndices != NULL) {
        if (glm::length(movement) != 0) {
            animTime += deltaTime;

            if (animTime >= 0.15f)
            {
                animTime = 0.0f;
                animIndex++;
                if (animIndex >= animFrames) {
                    animIndex = 0;
                }
            }
        } else { //idle
            if (direction == "left") {
                animIndex = leftIdleIndex;
            } else {
                animIndex = rightIdleIndex;
            }
        }
    }
    
    if (jump) {
        jump = false;
        // jump gives instant amount of velocity for jump power
        velocity.y += jumpPower;
    }
    // HANDLING GAME PHYSICS AND CALCULATING NEW POSITION
    velocity.x = movement.x * speed;
    if (entityType == ENEMY && aiType == FLYER) {
        velocity.y = movement.y * speed;
    }
    
    // if we are accelerating, velocity increasing
    velocity += acceleration * deltaTime;
    // handle y and x parts individually
    position.y += velocity.y * deltaTime; // Move on Y
    CheckCollisionsY(platforms, platformCount, isWin);// Fix if needed
    
    position.x += velocity.x * deltaTime; // Move on X
    CheckCollisionsX(platforms, platformCount, isWin); // Fix if needed
    
    // checking to see if collided with enemy
    CheckCollisionsY(enemies, enemyCount, isWin);//  Fix if needed
    CheckCollisionsX(enemies, enemyCount, isWin);//  Fix if needed
    
    // current entity moves as needed
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index)
{
    float u = (float)(index % animCols) / (float)animCols;
    float v = (float)(index / animCols) / (float)animRows;
    
    float width = 1.0f / (float)animCols;
    float height = 1.0f / (float)animRows;
    
    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v};
    
    float vertices[]  = { -0.4, -0.4, 0.4, -0.4, 0.4, 0.4, -0.4, -0.4, 0.4, 0.4, -0.4, 0.4 };

    
    glBindTexture(GL_TEXTURE_2D, textureID);
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram *program) {
    if (isActive == false) return;
    
    program->SetModelMatrix(modelMatrix);
    
    
    if (animIndices != NULL) {
        DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
        return;
    }
    float vertices[]  = { -0.4, -0.4, 0.4, -0.4, 0.4, 0.4, -0.4, -0.4, 0.4, 0.4, -0.4, 0.4 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}




