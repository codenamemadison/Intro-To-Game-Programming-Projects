#include "MainMenu.h"

#define MAINMENU_WIDTH 10
#define MAINMENU_HEIGHT 9

unsigned int MainMenu_data[] =
{
     0,  1,  8,  2,  8,  4, 70,  4, 56,  4,
    11, 12, 55,  7, 13,  4,  4,  4,  4,  4,
    22, 20, 29, 18, 17,  4,  4, 70,  4,  4,
    22, 30,  5, 40, 48, 70,  4,  4, 56, 70,
    22, 31, 47, 49, 59,  4, 56, 70,  4,  4,
    22, 30, 39, 48, 70,  4,  4,  4, 56, 70,
     4, 63, 58, 59,  4, 56,  4,  4, 71,  4,
     4,  4,  4, 70,  4,  4,  4, 56, 70,  4
};

void MainMenu::Initialize() {
    state.nextScene = -1; // -1 means to not change scenes
    GLuint mapTextureID = Util::LoadTexture("Assets/blue_sewer_tilesheet.png");
    state.map = new Map(MAINMENU_WIDTH, MAINMENU_HEIGHT, MainMenu_data, mapTextureID, 1.0f, 11, 7);
    glClearColor(0.06f,0.02f,0.18f,1.0f);
}
void MainMenu::Update(float deltaTime, int &lives) {
    
}
void MainMenu::Render(ShaderProgram *program, GLuint fontTextureID) {
    int centerline_x = 5.5;
    int centerline_y = -4;
    state.map->Render(program);
    Util::DrawText(program, fontTextureID, "Stuck in",
             0.6f, 0, glm::vec3(centerline_x + -1.0, centerline_y + 2.0, 0));
    Util::DrawText(program, fontTextureID, "the Sewers",
             0.6f, 0, glm::vec3(centerline_x + -1.7, centerline_y + 1.25, 0));
    Util::DrawText(program, fontTextureID, "Developed by",
             0.25f, 0, glm::vec3(centerline_x + -0.25f, centerline_y + 0.5, 0));
    Util::DrawText(program, fontTextureID, "Madison Shimbo",
             0.25f, 0, glm::vec3(centerline_x + -0.5f, centerline_y + 0.1, 0));
    Util::DrawText(program, fontTextureID, "Press Enter",
             0.3f, 0, glm::vec3(centerline_x + -0.65f, centerline_y + -1.8, 0));
    Util::DrawText(program, fontTextureID, "To Continue",
             0.3f, 0, glm::vec3(centerline_x + -0.65f, centerline_y + -2.3, 0));
}



