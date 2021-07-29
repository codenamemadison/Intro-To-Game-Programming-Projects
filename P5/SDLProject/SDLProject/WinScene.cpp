#include "WinScene.h"

void WinScene::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    
    // loading font sprite sheet
    //glClearColor(0,0,0,1.0f);
    state.background = new Entity();
    state.background->textureID = Util::LoadTexture("Assets/Background/background_back.png");
    state.background->entityType = BACKGROUND;
    state.background->position = glm::vec3(0,0,0);
    state.background->modelMatrix = glm::scale(state.background->modelMatrix, glm::vec3(40.0f, 15.0f, 1.0f));
}
void WinScene::Update(float deltaTime, int &lives) {
    
}
void WinScene::Render(ShaderProgram *program) {
    state.background->Render(program);
    Util::DrawText(program, Util::LoadTexture("Assets/pixel_font.png"), "You Win!",
             0.6f, -0.1f, glm::vec3(-1.5, 0, 0));
}



