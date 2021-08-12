#include "WinScene.h"
#define WINSCENE_WIDTH 0
#define WINSCENE_HEIGHT 0
unsigned int WinScene_data[] =
{
};

void WinScene::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    
    Mix_HaltMusic();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_PlayMusic(Mix_LoadMUS("Assets/Sounds/win_game_music.wav"), 0); // -1 = endless loop
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    
    // loading font sprite sheet
    GLuint mapTextureID = Util::LoadTexture("Assets/blue_sewer_tilesheet.png");
    state.map = new Map(WINSCENE_WIDTH, WINSCENE_HEIGHT, WinScene_data, mapTextureID, 1.0f, 11, 7);
    
    glClearColor(0.06f,0.02f,0.18f,1.0f);
}
void WinScene::Update(float deltaTime, int &lives) {
    
}
void WinScene::Render(ShaderProgram *program, GLuint fontTextureID) {
    Util::DrawText(program, fontTextureID, "You Win!",
                   0.6f, -0.1f, glm::vec3(-1.55, 0, 0));
}



