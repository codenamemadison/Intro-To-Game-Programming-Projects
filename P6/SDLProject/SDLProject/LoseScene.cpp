#include "LoseScene.h"

void LoseScene::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
}
void LoseScene::Update(float deltaTime, int &lives) {
    
}
void LoseScene::Render(ShaderProgram *program, GLuint fontTextureID) {
    //state.background->Render(program);
    Util::DrawText(program, fontTextureID, "You Lose!",
             0.6f, -0.1f, glm::vec3(-1.65, 0, 0));
}




