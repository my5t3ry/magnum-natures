#define GLM_ENABLE_EXPERIMENTAL

#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/GLContext.h>
#include <Magnum/Shaders/VertexColor.h>
#include <GLFW/glfw3.h>
#include <natures.hpp>
#include <opengl/transform.hpp>

int main() {
    Window main(WINDOW_X, WINDOW_Y, "natures");
    List L;
    Event e;
    glEnable(GL_PROGRAM_POINT_SIZE);

    Transform transform;
    Camera camera(glm::vec3(0, 0, 70), 70.0f, (float) 800 / (float) 600, 0.31f, 1000.0f);


    SpriteBatch spriteBatch = SpriteBatch();
    spriteBatch.init(camera);

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

        if (!pause) {
            main.Clear();
            L.Remove();
            L.Behavior();
            L.Place();

            spriteBatch.begin();

            for (std::list<Organism>::iterator it = L.organisms.begin(); it != L.organisms.end(); it++)
                spriteBatch.draw(it->getRectangle(), it->getVisuals());

            spriteBatch.end();
            spriteBatch.drawShader();
//                        shader.update()
            main.swapBuffers();

            /* Poll for and process events */
//            glfwPollEvents();
        }

        if (fps.getTicks() < (1000 / speed))
            SDL_Delay((1000 / speed) - fps.getTicks());

    }
    glfwTerminate();
}
