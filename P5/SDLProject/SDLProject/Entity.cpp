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
    
    if (xdist < 0 && ydist < 0 ) {
        lastCollision = other->entityType;
        return true;
    }
    return false;
}


void Entity::CheckCollisionsY(Entity *objects, int objectCount)
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
                   this->isActive = false;
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

void Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
   for (int i = 0; i < objectCount; i++)
   {
       Entity *object = &objects[i];
       if (CheckCollision(object))
       {
           // correcting an error if player is still when horse/skeleton moves past them
           if (this->entityType == PLAYER && (object->aiType == WAITANDGO || object->aiType == PATROLER)) {
               this->isActive = false;
           }
           
           float xdist = fabs(position.x - object->position.x);
           float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
           if (velocity.x > 0) {
               position.x -= penetrationX;
               velocity.x = 0;
               collidedRight = true;
               if (this->entityType == PLAYER && object->entityType == ENEMY)  { // if player is touched by enemy, you lose game
                   this->isActive = false;
               }
           }
           else if (velocity.x < 0) {
               position.x += penetrationX;
               velocity.x = 0;
               collidedLeft = true;
               if (this->entityType == PLAYER && object->entityType == ENEMY) { // if player is touched by enemy, you lose game
                   this->isActive = false;
               }
           }
       }
   }
}
// can help check if an entity is partially on a ledge
void Entity::CheckCollisionsY(Map *map)
{
    // Probes for tiles
    glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
    glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
    glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);
    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    // check if each sensor position is colliding with something solid
    if (map->IsSolid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
}

// checks for side collisions (on middle of entity)
void Entity::CheckCollisionsX(Map *map)
{
    // Probes for tiles
    glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
    glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    // check if each sensor position is colliding with something solid
    if (map->IsSolid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
        position.x += penetration_x;
        velocity.x = 0;
        collidedLeft = true;
    }
    if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        collidedRight = true;
    }
}


// dealt with behavior of patroler
void Entity::AIPatroler(int leftBound, int rightBound) { 
    if (position.x >= rightBound) {
        movement.x = -1;
        direction = "left";
    } else if (position.x <= leftBound) {
        movement.x = 1;
        direction = "right";
    } else if (leftBound - 0.25f < position.x && position.x < rightBound + 0.25f) {
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
            if (glm::distance(position, player->position) < 2.0f) {
                aiState = MOVING;
            }
            break;
        case MOVING:  // AI will walk toward player
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
void Entity::AI(Entity *player, int leftBound, int rightBound) {
    switch(aiType) {
        case PATROLER:
            AIPatroler(leftBound, rightBound);
            break;
        case WAITANDGO:
            AIWaitAndGo(player);
            break;
    }
}



void Entity::Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map, int &lives, int leftBound, int rightBound)
{
    // object = AI or other things
    if (isActive == false) return;
    
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    
    if (entityType == ENEMY) {
        AI(player, leftBound, rightBound);
    }
    
    if (animIndices != NULL) {
        if (glm::length(movement) != 0) {
            animTime += deltaTime;

            if (animTime >= 0.25f)
            {
                animTime = 0.0f;
                animIndex++;
                if (animIndex >= animFrames)
                {
                    animIndex = 0;
                }
            }
        } else { // idle
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
    // HANDLING GAME PHYSICS
    velocity.x = movement.x * speed;
    
    // if we are accelerating, velocity increasing
    velocity += acceleration * deltaTime;
    // handle y and x parts individually
    position.y += velocity.y * deltaTime;  // Move on Y
    CheckCollisionsY(map); // check if collide w map first - fix if needed
    CheckCollisionsY(objects, objectCount); // then check if collided w any objects - fix if needed
    
    position.x += velocity.x * deltaTime; // Move on X
    CheckCollisionsX(map); // check if collide w map first - fix if needed
    CheckCollisionsX(objects, objectCount); // then check if collided w any obkects - fix if needed
    
    if (player->position.y <= -8) {
        player->isActive = false;
    }
    
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
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
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
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
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


