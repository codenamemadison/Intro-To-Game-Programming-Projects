#include "Instructions.h"

void Instructions::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    glClearColor(0.06f,0.02f,0.18f,1.0f);
}
void Instructions::Update(float deltaTime, int &lives) {
    
}
void Instructions::Render(ShaderProgram *program, GLuint fontTextureID) {
    float initial = 2.5;
    float spacing = 0.35;
    float align = -4.4;
    Util::DrawText(program, fontTextureID, "Instructions",
             0.65f, -0.1f, glm::vec3(-2.95, 2.8, 0));
    Util::DrawText(program, fontTextureID, "On a seemingly normal night like any other, you" ,
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 1,  0));
    Util::DrawText(program, fontTextureID, "wake up to find yourself in what you realize to" ,
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 2, 0));
    Util::DrawText(program, fontTextureID, "be a sewage system. You begin questioning how you" ,
             0.2f, -0.015f, glm::vec3(align, initial +-spacing * 3, 0));
    Util::DrawText(program, fontTextureID, "even got down here but then soon start to get a",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 4, 0));
    Util::DrawText(program, fontTextureID, "weird feeling about where you are; this isn't a",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 5, 0));
    Util::DrawText(program, fontTextureID, "normal sewage system... You realize you need to",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 6, 0));
    Util::DrawText(program, fontTextureID, "get out of here ASAP.",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 7, 0));
    Util::DrawText(program, fontTextureID, "In order to successfully escape, you need to" ,
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 9, 0));
    Util::DrawText(program, fontTextureID, "collect a key to escape each level. But watch out -",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 10, 0));
    Util::DrawText(program, fontTextureID, "enemies roam about! Unfortunately, you don't have",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 11, 0));
    Util::DrawText(program, fontTextureID, "any weapons on you, so try your best to not get in",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 12, 0));
    Util::DrawText(program, fontTextureID, "their way or else you will lose a life! Losing",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 13, 0));
    Util::DrawText(program, fontTextureID, "all three lives will cause you to lose the game.",
             0.2f, -0.015f, glm::vec3(align, initial + -spacing * 14, 0));
    Util::DrawText(program, fontTextureID, "Press Enter To Start",
             0.3f, -0.01f, glm::vec3(-2.7, initial + -spacing * 15.9, 0));
}

