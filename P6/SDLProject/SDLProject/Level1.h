#include "Scene.h"
class Level1 : public Scene {
public:
    bool gotKey = false;
    void Initialize() override;
    void Update(float deltaTime, int &lives) override;
    void Render(ShaderProgram *program, GLuint fontTextureID) override;
};

