#include "MainMenu.h"

#define MAINMENU_WIDTH 10
#define MAINMENU_HEIGHT 9

unsigned int MainMenu_data[] =
{
     8,  1,  8, 15,  4,  4,  4,  4, 56,  4,
     6, 55,  7, 26,  4,  4,  4,  4,  4,  4,
    17, 29, 18, 51,  4,  4,  4, 70,  4,  4,
     5, 40,  5, 48,  4,  4,  4,  4, 56, 70,
    24,  5, 47, 48,  4,  4, 56, 70,  4,  4,
     5,  5, 39, 48, 70,  4,  4,  4, 56, 70,
    58, 58, 60, 59,  4, 56,  4,  4,  4,  4,
    56,  4, 56, 70,  4,  4,  4, 56, 70,  4
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
    int centerline_x = 5.0;
    int centerline_y = -4;
    state.map->Render(program);
    Util::DrawText(program, fontTextureID, "Stuck in",
             0.58f, -0.1, glm::vec3(centerline_x - 0.45, centerline_y + 2.0, 0));
    Util::DrawText(program, fontTextureID, "the Sewers",
             0.58f, 0, glm::vec3(centerline_x - 1.3, centerline_y + 1.2, 0));
    Util::DrawText(program, fontTextureID, "Developed by",
             0.25f, 0, glm::vec3(centerline_x + -0.2f, centerline_y + 0.5, 0));
    Util::DrawText(program, fontTextureID, "Madison Shimbo",
             0.25f, 0, glm::vec3(centerline_x + -0.45f, centerline_y + 0.1, 0));
    Util::DrawText(program, fontTextureID, "Press Enter",
             0.3f, 0, glm::vec3(centerline_x + -0.35f, centerline_y + -1.1, 0));
    Util::DrawText(program, fontTextureID, "To Continue",
             0.3f, 0, glm::vec3(centerline_x + -0.35f, centerline_y + -1.6, 0));
}



