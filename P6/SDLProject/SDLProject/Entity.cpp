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
        if (this->entityType == PLAYER && other->entityType == ENEMY) { // if player is touched by enemy, you lose a life
            this->isActive = false;
            Mix_PlayChannel(-1, lostLife, 0);
        } else if (this->entityType == PLAYER && other->entityType == KEY) { // if player touches key
            other->isActive = false;
            // key collecting sound effect
            Mix_PlayChannel(-1, keySound, 0);
        }
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
           }
           // if we are falling into a platform, we fix by moving up
           else if (velocity.y < 0) {
               position.y += penetrationY;
               // if we hit a platform, we stop moving
               velocity.y = 0;
               collidedBottom = true;
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
           float xdist = fabs(position.x - object->position.x);
           float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
           if (velocity.x > 0) {
               position.x -= penetrationX;
               velocity.x = 0;
               collidedRight = true;
           }
           else if (velocity.x < 0) {
               position.x += penetrationX;
               velocity.x = 0;
               collidedLeft = true;
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
void Entity::AIPatroller() {
    if (patrollerType == "horizontal") {
        if (position.x >= upperBound) {
            movement.x = -1;
            direction = "left";
        } else if (position.x <= lowerBound) {
            movement.x = 1;
            direction = "right";
        } else if (lowerBound - 0.25f < position.x && position.x < upperBound + 0.25f) {
            if (direction == "left") {
                animIndices = animLeft;
                movement.x = -1;
            } else {
                animIndices = animRight;
                movement.x = 1;
            }
        }
    } else { // vertical patroller
        if (position.y >= upperBound) {
            movement.y = -1;
            direction = "down";
        } else if (position.y <= lowerBound) {
            movement.y = 1;
            direction = "up";
        } else if (lowerBound - 0.25f < position.y && position.y < upperBound + 0.25f) {
            if (direction == "down") {
                movement.y = -1;
            } else {
                movement.y = 1;
            }
        }
    }

     
}

// creating a sort of "library" for AI behaviors
void Entity::AI(Entity *player) { 
    switch(aiType) {
        case PATROLLER:
            AIPatroller();
            break;
        case IGNORE:
            break;
    }
}



void Entity::Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map, int &lives)
{
    // object = AI or other things
    if (isActive == false) return;
    
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    
    if (entityType == ENEMY) {
        AI(player);
    }
    
    if (animIndices != NULL) {
        if (glm::length(movement) != 0 || this->entityType == KEY) {
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
            animIndex = 0;
        }
    }
    
    // HANDLING GAME PHYSICS
    velocity.x = movement.x * speed;
    velocity.y = movement.y * speed;
    
    position.y += movement.y * speed * deltaTime;
    if ((entityType == PLAYER) || (entityType == ENEMY && detectBarriers) || (entityType == KEY)) {
        CheckCollisionsY(map); // check if collide w map first - fix if needed
        CheckCollisionsY(objects, objectCount); // then check if collided w any objects - fix if needed
    }
    position.x += movement.x * speed * deltaTime;
    if ((entityType == PLAYER) || (entityType == ENEMY && detectBarriers) || (entityType == KEY)) {
        CheckCollisionsX(map); // check if collide w map first - fix if needed
        CheckCollisionsX(objects, objectCount); // then check if collided w any obkects - fix if needed
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


