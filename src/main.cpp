#define GLM_ENABLE_EXPERIMENTAL

#include "main.hpp"

int main(int argc, char **argv) {
    srand(time(NULL));
    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *const window = glfwCreateWindow(
            WINDOW_X, WINDOW_Y, "Magnum Plain GLFW Triangle Example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    {
        /* Create Magnum context in an isolated scope */
        List L;

        Magnum::Platform::GLContext ctx{argc, argv};
        Transform transform;
        Camera camera(glm::vec3(0, 0, 70), 70.0f, (float) 800 / (float) 600, 0.31f, 1000.0f);
        GeoShader shader("./inc/opengl/shaders/theshader");
        SpriteBatch _spriteBatch(shader);

        _spriteBatch.init();
        shader.Bind();

        int uniModel = glGetUniformLocation(shader.m_program, "MVP");
        glUniformMatrix4fv(uniModel, 1, false, &transform.GetMVP(camera)[0][0]);

        while (!glfwWindowShouldClose(window)) {
            Magnum::GL::defaultFramebuffer.clear(Magnum::GL::FramebufferClear::Color);

            L.Remove();
            L.Behavior();
            L.Place();

            shader.Bind();
            _spriteBatch.begin();

            for (std::list<Organism>::iterator it = L.organisms.begin(); it != L.organisms.end(); it++)
                _spriteBatch.draw(it->getRectangle(), it->getVisuals());

            _spriteBatch.end();
            _spriteBatch.renderBatch();
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    return 0;

}

