#include "Scene.h"
class WinScene : public Scene {
public:
    void Initialize() override;
    void Update(float deltaTime, int &lives) override;
    void Render(ShaderProgram *program, GLuint fontTextureID) override;
};


