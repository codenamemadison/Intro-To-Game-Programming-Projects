#include "LoseScene.h"

void LoseScene::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    Mix_HaltMusic();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_PlayMusic(Mix_LoadMUS("Assets/Sounds/lose_life.wav"), 0); // -1 = endless loop
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}
void LoseScene::Update(float deltaTime, int &lives) {
    
}
void LoseScene::Render(ShaderProgram *program, GLuint fontTextureID) {
    //state.background->Render(program);
    Util::DrawText(program, fontTextureID, "You Lose!",
             0.6f, -0.1f, glm::vec3(-1.65, 0, 0));
}




