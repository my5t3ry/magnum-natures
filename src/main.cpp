#define GLM_ENABLE_EXPERIMENTAL

#include <Magnum/ImGuiIntegration/Context.hpp>
#include "main.hpp"


void showMenu();

int main() {
    srand(time(NULL));

    Window main(WINDOW_X, WINDOW_Y, "natures");
    List L;
    Event e;
    glEnable(GL_PROGRAM_POINT_SIZE);

    Transform transform;
    Camera camera(glm::vec3(0, 0, 70), 70.0f, (float) 800 / (float) 600, 0.31f, 1000.0f);
    GeoShader shader("./inc/opengl/shaders/theshader");
    SpriteBatch _spriteBatch(shader);

    _spriteBatch.init();
    shader.Bind();

//    int uniModel = glGetUniformLocation(shader.m_program, "MVP");
//    glUniformMatrix4fv(uniModel, 1, false, &transform.GetMVP(camera)[0][0]);

    Timer fps;
    int speed = 60;
    bool pause = false;
    while (e.gRun()) {
        fps.Start();
        while (e.Poll()) {
            if (e.gEventType() == SDL_QUIT)
                e.off();
            else if (e.gEventType() == SDL_KEYDOWN)
                switch (e.gEvent().key.keysym.sym) {
                    case SDLK_q:
                        e.off();
                        break;
                    case SDLK_EQUALS:
                        speed += 30;
                        break;
                    case SDLK_MINUS:
                        if (speed > 30) speed -= 30;
                        break;
                    case SDLK_SPACE:
                        pause = (pause) ? (0) : (1);
                        break;
                }
        }

        const Magnum::ImGuiIntegration::Context _imgui = Magnum::ImGuiIntegration::Context(
                Magnum::Vector2{WINDOW_Y, WINDOW_X},
                {WINDOW_Y, WINDOW_X}, {WINDOW_Y, WINDOW_X});


        if (!pause) {
            main.Clear();

            L.Remove();
            L.Behavior();
            L.Place();

            shader.Bind();
            _spriteBatch.begin();

            for (std::list<Organism>::iterator it = L.organisms.begin(); it != L.organisms.end(); it++)
                _spriteBatch.draw(it->getRectangle(), it->getVisuals());
            _spriteBatch.end();
            _spriteBatch.renderBatch();
//                        shader.update()
            main.swapBuffers();
        }

        bool _showMenu = true;
        if (_showMenu) showMenu();

        /* Update application cursor */
//        _imgui.updateApplicationCursor(window_h);

        if (fps.getTicks() < (1000 / speed))
            SDL_Delay((1000 / speed) - fps.getTicks());

    }
    return 0;
}

void showMenu() {

    ImGui::SetNextWindowPos({10.0f, 10.0f}, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowBgAlpha(0.5f);
    ImGui::Begin("Options", nullptr);

    /* General information */
    ImGui::Text("Hide/show menu: H");
//    ImGui::Text("Num. particles: %d",   Int(_fluidSolver->numParticles()));
//    ImGui::Text("Rendering: %3.2f FPS", Double(ImGui::GetIO().Framerate));
    ImGui::Spacing();

    /* Rendering parameters */
    if (ImGui::TreeNode("Particle Rendering")) {
        ImGui::PushID("Particle Rendering");
        {
            constexpr const char *items[] = {"Uniform", "Ramp by ID"};
//            static Int colorMode = 1;
            ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
//            if(ImGui::Combo("Color Mode", &colorMode, items, 2)) {
//                _drawableParticles->setColorMode(ParticleSphereShader2D::ColorMode(colorMode));
//            }
            ImGui::PopItemWidth();
//            if(colorMode == 0) { /* Uniform color */
//                static Color3 color = _drawableParticles->color();
//                if(ImGui::ColorEdit3("Color", color.data())) {
//                    _drawableParticles->setColor(color);
//                }
        }
    }
    ImGui::PopID();
    ImGui::TreePop();
}
