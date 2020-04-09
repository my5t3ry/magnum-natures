#include <Magnum/GL/Mesh.h>
#include "opengl/spritebatch.hpp"
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/MatrixTransformation2D.h>

using Scene2D = Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation2D>;


SpriteBatch::SpriteBatch() = default;


void SpriteBatch::init() {
    shader.emplace();
    mesh.emplace();
    posBuffer.emplace();
    colorBuffer.emplace();
    sidesBuffer.emplace();
    (*mesh).setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer((*posBuffer), 0, GeoShader::pos{})
            .setCount((*posBuffer).size());
    (*mesh).setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer((*colorBuffer), 0, GeoShader::color{})
            .setCount((*colorBuffer).size());
    (*mesh).setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer((*sidesBuffer), 0, GeoShader::sides{})
            .setCount((*sidesBuffer).size());
}


void SpriteBatch::begin() {
    _renderBatches.clear();
    _gfx.clear();
}

void SpriteBatch::end() {
    // Set up all pointers for fast sorting
    _gfxPtr.resize(_gfx.size());
    for (int i = 0; i < _gfx.size(); i++)
        _gfxPtr[i] = &_gfx[i];

    //sortGlyphs();
}

void SpriteBatch::draw(Rectangle r, DNA::Visuals v) {
    _gfx.emplace_back(std::make_pair(r, v));
}

SpriteBatch &
SpriteBatch::drawShader(Corrade::Containers::Pointer<Magnum::SceneGraph::Camera2D> &camera, Magnum::Int screenHeight,
                        Magnum::Int projectionHeight) {
//    createRenderBatches();
    createVertexArray();
    (*colorBuffer)
            .setData(color, Magnum::GL::BufferUsage::StaticDraw);
    (*sidesBuffer)
            .setData(sides, Magnum::GL::BufferUsage::StaticDraw);
    (*posBuffer)
            .setData(pos, Magnum::GL::BufferUsage::StaticDraw);
    (*shader)
            .setViewProjectionMatrix(camera->projectionMatrix() * camera->cameraMatrix())
            .draw((*mesh));
    return *this;
}
//
//void SpriteBatch::createRenderBatches() {
//    // This will store all the vertices that we need to upload
//    std::vector<float> vertices;
//    // Resize the buffer to the exact size we need so we can treat
//    // it like an array
//    vertices.resize(_gfxPtr.size() * 6);
//
//    if (_gfxPtr.empty()) {
//        return;
//    }
//
//    int offset = 0; // current offset
//    int cv = 0; // current vertex
//
//    //Add the first batch
//    _renderBatches.emplace_back(offset, 6);
//    vertices[cv++] = _gfxPtr[0]->first.x;
//    vertices[cv++] = _gfxPtr[0]->first.y;
//    vertices[cv++] = _gfxPtr[0]->second.red;
//    vertices[cv++] = _gfxPtr[0]->second.green;
//    vertices[cv++] = _gfxPtr[0]->second.blue;
//    vertices[cv++] = SIDES;
//
//    offset += 6;
//
//    //Add all the rest of the glyphs
//    //std::cout << "ptr size = " <<  _gfxPtr.size() << std::endl;
//    for (int cg = 1; cg < _gfxPtr.size(); cg++) {
//        // Check if this glyph can be part of the current batch
//        //if (_gfxPtr[cg]->texture != _gfxPtr[cg - 1]->texture) {
//        // Make a new batch
//        //    _renderBatches.emplace_back(offset, 6);
//        //} else {
//        // If its part of the current batch, just increase numVertices
//        _renderBatches.back().numVertices += 6;
//        //}
//        vertices[cv++] = _gfxPtr[cg]->first.x;
//        vertices[cv++] = _gfxPtr[cg]->first.y;
//        vertices[cv++] = _gfxPtr[cg]->second.red;
//        vertices[cv++] = _gfxPtr[cg]->second.green;
//        vertices[cv++] = _gfxPtr[cg]->second.blue;
//        vertices[cv++] = SIDES;
//
//        offset += 6;
//    }
//}

void SpriteBatch::createVertexArray() {
    // This will store all the vertices that we need to upload
    // Resize the buffer to the exact size we need so we can treat
    // it like an array
    pos.empty();
    color.empty();
    sides.empty();

    pos.resize(_gfxPtr.size() * sizeof(glm::vec2));
    color.resize(_gfxPtr.size() * sizeof(glm::vec2));
    sides.resize(_gfxPtr.size() * sizeof(float));

    if (_gfxPtr.empty()) {
        return;
    }

    //std::cout << "ptr size = " <<  _gfxPtr.size() << std::endl;
    for (int cg = 1; cg < _gfxPtr.size(); cg++) {
        // If its part of the current batcdh, just increase numVertices
        Magnum::Vector2 a{_gfxPtr[0]->first.x, _gfxPtr[0]->first.y};
        Magnum::Vector3 b{_gfxPtr[0]->second.red, _gfxPtr[0]->second.green, _gfxPtr[0]->second.blue};
        pos[cg++] = a;
        color[cg++] = b;
        sides[cg++] = SIDES;
    }

}
