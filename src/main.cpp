#define GLM_ENABLE_EXPERIMENTAL

#include "main.hpp"
#include <opengl/geoshader.hpp>
#include <opengl/spritebatch.hpp>
#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_sdl.h>


int main() {
    srand(time(NULL));

    Window main(WINDOW_X, WINDOW_Y, "natures");
    List L;
    glEnable(GL_PROGRAM_POINT_SIZE);

    Transform transform;
    Camera camera(glm::vec3(0, 0, 70), 70.0f, (float) 800 / (float) 600, 0.31f, 1000.0f);
    GeoShader shader("./inc/opengl/shaders/theshader");
    SpriteBatch _spriteBatch(shader);

    _spriteBatch.init();
    shader.Bind();

    int uniModel = glGetUniformLocation(shader.m_program, "MVP");
    glUniformMatrix4fv(uniModel, 1, false, &transform.GetMVP(camera)[0][0]);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // contex is the SDL_GLContext
    ImGui_ImplSDL2_InitForOpenGL(main.main, main.glContext);
    ImGui_ImplOpenGL3_Init();

    bool show_demo_window = true;

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Forward to Imgui
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT
                || (event.type == SDL_WINDOWEVENT
                    && event.window.event == SDL_WINDOWEVENT_CLOSE
                    && event.window.windowID == SDL_GetWindowID(main.main))) {
                done = true;
            }
        }

// Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(main.main);
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin(
                    "Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text(
                    "This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

            if (ImGui::Button(
                    "Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

// Frame logic here...

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Render other stuff...

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
// Render imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(main.main);

    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Other cleanup...

    return 0;
}
