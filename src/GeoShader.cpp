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
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Matrix3.h>

Magnum::GeoShader::GeoShader() {
    Magnum::GL::Shader vert{Magnum::GL::Version::GLES320, Magnum::GL::Shader::Type::Vertex};
    Magnum::GL::Shader geo{Magnum::GL::Version::GLES320, Magnum::GL::Shader::Type::Geometry};
    Magnum::GL::Shader frag{Magnum::GL::Version::GLES320, Magnum::GL::Shader::Type::Fragment};
    vert.addSource(vertShader);
    geo.addSource(genomShader);
    frag.addSource(fragShader);

    CORRADE_INTERNAL_ASSERT_OUTPUT(GL::Shader::compile({vert}));
    CORRADE_INTERNAL_ASSERT_OUTPUT(GL::Shader::compile({geo}));
    CORRADE_INTERNAL_ASSERT_OUTPUT(GL::Shader::compile({frag}));
    attachShaders({vert, geo, frag});
    CORRADE_INTERNAL_ASSERT(link());
}




