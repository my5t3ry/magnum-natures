#define GLM_ENABLE_EXPERIMENTAL

#ifndef geoshader_h
#define geoshader_h

#include <string>
#include <GL/glew.h>
#include <Magnum/GL/Shader.h>

#include "constants.hpp"
#include "transform.hpp"

class GeoShader {
public:
    GeoShader(const std::string &fileName);
    typedef Magnum::GL::Attribute<0, glm::vec2> pos;
    typedef Magnum::GL::Attribute<1, glm::vec3> color;
    typedef Magnum::GL::Attribute<2, float> sides;

    void Bind();

    void Update(const Transform &transform, const Camera &camera);

    virtual         ~GeoShader();

    GLuint m_program;

private:
    std::string LoadShader(const std::string &fileName);

    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);

    Magnum::GL::Shader CreateShader(const std::string &text, Magnum::GL::Shader::Type shaderType);

    Magnum::GL::Shader m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif
