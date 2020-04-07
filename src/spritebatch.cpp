#include <Magnum/GL/Mesh.h>
#include "opengl/spritebatch.hpp"
#include <natures.hpp>

SpriteBatch::SpriteBatch() {

    shader = Magnum::GeoShader();
}

void SpriteBatch::init() {
    createRenderBatches();
}

void SpriteBatch::begin() {
    glEnable(GL_PROGRAM_POINT_SIZE);
    _renderBatches.clear();
    // Makes _glpyhs.size() == 0, however it does not free internal memory.
    // So when we later call emplace_back it doesn't need to internally call new.
    _gfx.clear();
}

void SpriteBatch::end() {
    // Set up all pointers for fast sorting
    _gfxPtr.resize(_gfx.size());
    for (int i = 0; i < _gfx.size(); i++)
        _gfxPtr[i] = &_gfx[i];

    //sortGlyphs();
    createRenderBatches();
}

void SpriteBatch::draw(Rectangle r, DNA::Visuals v) {
    _gfx.emplace_back(std::make_pair(r, v));
}

void SpriteBatch::renderBatch() {
    Magnum::GL::Mesh mesh;

    // Bind our VAO. This sets up the opengl state we need, including the
    // vertex attribute pointers and it binds the VBO

    //glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
    Magnum::GL::Buffer posBuffer;
    posBuffer.setData(pos, Magnum::GL::BufferUsage::StaticDraw);
    Magnum::GL::Buffer colorBuffer;
    colorBuffer.setData(color, Magnum::GL::BufferUsage::StaticDraw);
    Magnum::GL::Buffer sidesBuffer;
    sidesBuffer.setData(sides, Magnum::GL::BufferUsage::StaticDraw);
    mesh.addVertexBuffer(posBuffer, 0, 0, 0);
    mesh.addVertexBuffer(colorBuffer, 0, 0, 1);
    mesh.addVertexBuffer(sidesBuffer, 0, 0, 2);
    shader.draw(mesh);
}

void SpriteBatch::createRenderBatches() {
    // This will store all the vertices that we need to upload
    pos.empty();
    color.empty();
    sides.empty();
    // Resize the buffer to the exact size we need so we can treat
    // it like an array
    pos.resize(_gfxPtr.size() * sizeof(glm::vec2));
    color.resize(_gfxPtr.size() * sizeof(glm::vec2));
    sides.resize(_gfxPtr.size() * sizeof(float));

    if (_gfxPtr.empty()) {
        return;
    }


    //Add all the rest of the glyphs
    //std::cout << "ptr size = " <<  _gfxPtr.size() << std::endl;
    for (int cg = 1; cg < _gfxPtr.size(); cg++) {
        // If its part of the current batcdh, just increase numVertices
        pos[cg++] = {_gfxPtr[0]->first.x, _gfxPtr[0]->first.y};
        color[cg++] = {_gfxPtr[0]->second.red, _gfxPtr[0]->second.green, _gfxPtr[0]->second.blue};
        sides[cg++] = SIDES;
    }

}
