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

// checking if entity collided with another type of entity
void Entity::Update(float deltaTime, Entity *tiles, int tileCount)
{
    if (isActive == false) return;
    
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    
    
    // HANDLING GAME PHYSICS
    velocity.x = movement.x * speed;
    // if we are accelerating, velocity increasing
    velocity += acceleration * deltaTime;
    
    // handle y and x parts individually
    position.y += velocity.y * deltaTime; // Move on Y
    CheckCollisionsY(tiles, tileCount);// Fix if needed
    
    position.x += velocity.x * deltaTime; // Move on X
    CheckCollisionsX(tiles, tileCount);// Fix if needed
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

void Entity::Render(ShaderProgram *program) {
    if (isActive == false) return;
    
    program->SetModelMatrix(modelMatrix);
    
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


