/*
    This file is part of Magnum.

    Original authors — credit is appreciated but not required:

        2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019 —
            Vladimír Vondruš <mosra@centrum.cz>
        2019 — Nghia Truong <nghiatruong.vn@gmail.com>

    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or distribute
    this software, either in source code form or as a compiled binary, for any
    purpose, commercial or non-commercial, and by any means.

    In jurisdictions that recognize copyright laws, the author or authors of
    this software dedicate any and all copyright interest in the software to
    the public domain. We make this dedication for the benefit of the public
    at large and to the detriment of our heirs and successors. We intend this
    dedication to be an overt act of relinquishment in perpetuity of all
    present and future rights to this software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "inc/shaders/geoshader/GeoShader.h"

#include <Corrade/Containers/Reference.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <opengl/camera.hpp>
#include <opengl/transform.hpp>

Magnum::GeoShader::GeoShader() {

    Magnum::GL::Shader m_shaders[NUM_SHADERS] = {
            CreateShader("inc/opengl/shader/theshader.vert", Magnum::GL::Shader::Type::Vertex),
            CreateShader("inc/opengl/shader/theshader.geom", Magnum::GL::Shader::Type::Geometry),
            CreateShader("inc/opengl/shader/theshader.frag", Magnum::GL::Shader::Type::Fragment)};

    CORRADE_INTERNAL_ASSERT_OUTPUT(Magnum::GL::Shader::compile({m_shaders[0], m_shaders[2], m_shaders[3]}));

    attachShaders({m_shaders[0], m_shaders[2], m_shaders[3]});


    CORRADE_INTERNAL_ASSERT(GL::Shader::compile({m_shaders[0], m_shaders[1], m_shaders[2]}));
    CORRADE_INTERNAL_ASSERT(link());

    _uNumParticles = uniformLocation("numParticles");
    _uParticleRadius = uniformLocation("particleRadius");

    _uColorMode = uniformLocation("colorMode");
    _uColor = uniformLocation("uniformColor");

    _uViewProjectionMatrix = uniformLocation("viewProjectionMatrix");
    _uScreenHeight = uniformLocation("screenHeight");
    _uDomainHeight = uniformLocation("domainHeight");

}


GeoShader &Magnum::GeoShader::setNumParticles(Int numParticles) {
    setUniform(_uNumParticles, numParticles);
    return *this;
}

GeoShader &Magnum::GeoShader::setParticleRadius(Float radius) {
    setUniform(_uParticleRadius, radius);
    return *this;
}

GeoShader &Magnum::GeoShader::setColorMode(Int colorMode) {
    setUniform(_uColorMode, colorMode);
    return *this;
}

GeoShader &Magnum::GeoShader::setColor(const Color3 &color) {
    setUniform(_uColor, color);
    return *this;
}

GeoShader &Magnum::GeoShader::setViewProjectionMatrix(const Matrix3 &matrix) {
    setUniform(_uViewProjectionMatrix, matrix);
    return *this;
}

GeoShader &Magnum::GeoShader::setScreenHeight(Int height) {
    setUniform(_uScreenHeight, height);
    return *this;
}

GeoShader &Magnum::GeoShader::setDomainHeight(Int height) {
    setUniform(_uDomainHeight, height);
    return *this;
}

}}

Magnum::GL::Shader Magnum::GeoShader::CreateShader(const std::string &fileName, Magnum::GL::Shader::Type shaderType) {
    Magnum::GL::Shader shader{Magnum::GL::Version::GL460, shaderType};
    shader.addFile(fileName);


    return shader;
}


void Magnum::GeoShader::Update(const Transform &transform, const Camera &camera) {
    glm::mat4 MVP = transform.GetMVP(camera);
    glm::mat4 Normal = transform.GetModel();

    glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
}



