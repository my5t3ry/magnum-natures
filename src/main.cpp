#define GLM_ENABLE_EXPERIMENTAL

#include "main.hpp"
#include <opengl/geoshader.hpp>
#include <opengl/spritebatch.hpp>
#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_sdl.h>
#include <opengl/treespritebatch.hpp>

int main ()
{
    srand (time (NULL));

    Window main (WINDOW_X, WINDOW_Y, "natures");
    List L;

    Camera camera (glm::vec3 (0, 0, 800), 70.0f, (float) WINDOW_X / (float) WINDOW_Y, 0.31f, 1000.0f);
    GeoShader shader ("./inc/opengl/shaders/organism/theshader");
    SpriteBatch _spriteBatch (shader);
    shader.Update (camera);

    shader.Bind ();
    _spriteBatch.init ();
    GeoShader treeShader ("./inc/opengl/shaders/tree/theshader");
    TreeSpriteBatch _treeSpriteBatch (treeShader);
    treeShader.Update (camera);
    treeShader.Bind ();
    _treeSpriteBatch.init ();

    glEnable (GL_PROGRAM_POINT_SIZE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext ();
    ImGuiIO &io = ImGui::GetIO ();
    (void) io;

    float scaleFactor = 1.9f;
    io.Fonts->AddFontFromFileTTF ("inc/SourceSansPro-Regular.ttf", 18.0f * scaleFactor, NULL, NULL);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark ();
    ImGuiStyle &style = ImGui::GetStyle ();
    style.ScaleAllSizes (scaleFactor);
    style.Alpha = 0.8;

    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // contex is the SDL_GLContext
    ImGui_ImplSDL2_InitForOpenGL (main.main, main.glContext);
    ImGui_ImplOpenGL3_Init ();

    bool show_demo_window = true;

    Timer fps;
    int speed = 60;
    bool done = false;
    while (!done)
        {
            fps.Start ();

            SDL_Event event;
            while (SDL_PollEvent (&event))
                {
                    // Forward to Imgui
                    ImGui_ImplSDL2_ProcessEvent (&event);
                    if (event.type == SDL_QUIT
                        || (event.type == SDL_WINDOWEVENT
                            && event.window.event == SDL_WINDOWEVENT_CLOSE
                            && event.window.windowID == SDL_GetWindowID (main.main)))
                        {
                            done = true;
                        }
                    else if (event.type == SDL_KEYDOWN)
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:
                                    camera.MoveLeft ();
                                break;
                                case SDLK_RIGHT:
                                    camera.MoveRight ();
                                break;
                                case SDLK_UP:
                                    camera.MoveForward ();
                                break;
                                case SDLK_DOWN:
                                    camera.MoveBackward ();
                                default:
                                    break;
                            }
                    shader.Update (camera);
                    treeShader.Update (camera);
                }

// Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame ();
            ImGui_ImplSDL2_NewFrame (main.main);
            ImGui::NewFrame ();

            ImGui::SetNextWindowPos (ImVec2 (20, 20), ImGuiCond_FirstUseEver);
            {
                static float f = 0.0f;
                static int counter = 0;;
                ImGui::Begin (
                        "->");                          // Create a window called "Hello, world!" and append into it.
                ImGui::Text ("%.3f ms/frame", 1000.0f / ImGui::GetIO ().Framerate);
                ImGui::Text ("%.1f fps", ImGui::GetIO ().Framerate);
                ImGui::Text ("Total organisms (%d)", static_cast<int>(L.organisms.size ()));
                ImGui::Text ("Carnivors (%d)", static_cast<int>(L.GetCarnivors ().size ()));
                ImGui::Text ("Herbavors (%d)", static_cast<int>(L.GetHerbavors ().size ()));
                ImGui::Text ("Plants (%d)", static_cast<int>(L.GetPlants ().size ()));
                ImGui::Text ("Corpses (%d)", static_cast<int>(L.GetCorpses ().size ()));
//            ImGui::Text("Total organisms (%d)", static_cast<int>(L.organisms.size()));
//            ImGui::Text("Total organisms (%d)", static_cast<int>(L.organisms.size()));
                ImGui::End ();
            }

// Frame logic here...

            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Render other stuff...

            L.Remove ();
            L.Behavior ();
            L.Place ();

            std::vector<QuadtreeVertexData> trees = L.tree.Draw ();
            std::reverse (trees.begin (), trees.end ());
            _treeSpriteBatch.render (trees);
            _spriteBatch.render (L.organisms);
// Render imgui
            ImGui::Render ();
            ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData ());
            SDL_GL_SwapWindow (main.main);
            if (fps.getTicks () < (1000 / speed))
                SDL_Delay ((1000 / speed) - fps.getTicks ());

        }
    ImGui_ImplOpenGL3_Shutdown ();
    ImGui_ImplSDL2_Shutdown ();
    ImGui::DestroyContext ();

    // Other cleanup...

    return 0;
}
