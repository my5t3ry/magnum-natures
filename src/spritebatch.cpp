#include <Magnum/GL/Mesh.h>
#include "opengl/spritebatch.hpp"
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/MatrixTransformation2D.h>


SpriteBatch::SpriteBatch() = default;


void SpriteBatch::init(Camera camera) {
    shader.emplace();
    (*shader).setViewProjectionMatrix(camera);
    posMesh.emplace();
    colorMesh.emplace();
    sidesMesh.emplace();
    posBuffer.emplace();
    colorBuffer.emplace();
    sidesBuffer.emplace();
    (*posBuffer).setData(vertex, Magnum::GL::BufferUsage::DynamicDraw);
    (*posMesh).setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer((*posBuffer), 0, GeoShader::pos{}, GeoShader::color{}, GeoShader::sides{})
            .setCount((*posBuffer).size());
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
SpriteBatch::drawShader() {
//    createRenderBatches();
    createVertexArray();

    (*posBuffer)
            .setData(vertex);
    (*posMesh).setCount(vertex.size());

    (*shader).draw((*posMesh));
//    (*shader)
//            .draw((*colorMesh));
//    (*shader)
//            .draw((*sidesMesh));
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

    vertex.resize(_gfxPtr.size());
    if (_gfxPtr.empty()) {
        return;
    }

    //std::cout << "ptr size = " <<  _gfxPtr.size() << std::endl;
    for (int cg = 0; cg < _gfxPtr.size(); cg++) {
        // If its part of the current batcdh, just increase numVertices
        Magnum::Vector2 a{_gfxPtr[cg]->first.x, _gfxPtr[cg]->first.y};
        Magnum::Vector3 b{_gfxPtr[cg]->second.red, _gfxPtr[cg]->second.green, _gfxPtr[cg]->second.blue};
        vertex[cg] = {a, b, SIDES};
    }

}
