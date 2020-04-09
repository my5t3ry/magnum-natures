#ifndef Magnum_Examples_FluidSimulation2D_ParticleSphereFlatShader_h
#define Magnum_Examples_FluidSimulation2D_ParticleSphereFlatShader_h
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


#include "constants.hpp"
#include "vert.h"
#include "frag.h"
#include "genom.h"
#include "constants.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/Magnum.h>
#include <Magnum/Types.h>


class GeoShader : public Magnum::GL::AbstractShaderProgram {
public:
    GeoShader();

    typedef Magnum::GL::Attribute<0, Magnum::Vector2> pos;
    typedef Magnum::GL::Attribute<1, Magnum::Vector3> color;
    typedef Magnum::GL::Attribute<2, float> sides;
    GeoShader &setViewProjectionMatrix(const Magnum::Matrix3 &matrix);

private:
    Magnum::Int _mvp;
    using Magnum::GL::AbstractShaderProgram::drawTransformFeedback;
    using Magnum::GL::AbstractShaderProgram::dispatchCompute;

//    GeoShader &setProjectionMatrix(const Magnum::Matrix4 &matrix);

};


#endif
