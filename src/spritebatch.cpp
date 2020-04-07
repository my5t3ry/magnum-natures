#include <Magnum/GL/Mesh.h>
#include "opengl/spritebatch.hpp"


SpriteBatch::SpriteBatch() {
    shader = GeoShader();

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
}

void SpriteBatch::draw(Rectangle r, DNA::Visuals v) {
    _gfx.emplace_back(std::make_pair(r, v));
}

void SpriteBatch::renderBatch() {
    Magnum::GL::Mesh mesh;
    createRenderBatches();
    createVertexArray();
    // Bind our VAO. This sets up the opengl state we need, including the
    // vertex attribute pointers and it binds the VBO

//    Magnum::Vector2 bindPos[pos.size()]{pos};
//    Magnum::Vector3 color[color.size()]{color};
//    glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
    Magnum::GL::Buffer posBuffer;
    posBuffer.setData(pos, Magnum::GL::BufferUsage::StaticDraw);
    Magnum::GL::Buffer colorBuffer;
    colorBuffer.setData(color, Magnum::GL::BufferUsage::StaticDraw);
    Magnum::GL::Buffer sidesBuffer;
    sidesBuffer.setData(sides, Magnum::GL::BufferUsage::StaticDraw);
    mesh.setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer(posBuffer, 0, GeoShader::pos{})
            .setCount(pos.size());
    mesh.setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer(posBuffer, 0, GeoShader::pos{})
            .setCount(color.size());
    mesh.setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer(posBuffer, 0, GeoShader::color{})
            .setCount(color.size());
    shader.draw(mesh);
}

void SpriteBatch::createRenderBatches() {
    // This will store all the vertices that we need to upload
    std::vector<float> vertices;
    // Resize the buffer to the exact size we need so we can treat
    // it like an array
    vertices.resize(_gfxPtr.size() * 6);

    if (_gfxPtr.empty()) {
        return;
    }

    int offset = 0; // current offset
    int cv = 0; // current vertex

    //Add the first batch
    _renderBatches.emplace_back(offset, 6);
    vertices[cv++] = _gfxPtr[0]->first.x;
    vertices[cv++] = _gfxPtr[0]->first.y;
    vertices[cv++] = _gfxPtr[0]->second.red;
    vertices[cv++] = _gfxPtr[0]->second.green;
    vertices[cv++] = _gfxPtr[0]->second.blue;
    vertices[cv++] = SIDES;

    offset += 6;

    //Add all the rest of the glyphs
    //std::cout << "ptr size = " <<  _gfxPtr.size() << std::endl;
    for (int cg = 1; cg < _gfxPtr.size(); cg++) {
        // Check if this glyph can be part of the current batch
        //if (_gfxPtr[cg]->texture != _gfxPtr[cg - 1]->texture) {
        // Make a new batch
        //    _renderBatches.emplace_back(offset, 6);
        //} else {
        // If its part of the current batch, just increase numVertices
        _renderBatches.back().numVertices += 6;
        //}
        vertices[cv++] = _gfxPtr[cg]->first.x;
        vertices[cv++] = _gfxPtr[cg]->first.y;
        vertices[cv++] = _gfxPtr[cg]->second.red;
        vertices[cv++] = _gfxPtr[cg]->second.green;
        vertices[cv++] = _gfxPtr[cg]->second.blue;
        vertices[cv++] = SIDES;

        offset += 6;
    }
}

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


    //Add all the rest of the glyphs
    //std::cout << "ptr size = " <<  _gfxPtr.size() << std::endl;
    for (int cg = 1; cg < _gfxPtr.size(); cg++) {
        // If its part of the current batcdh, just increase numVertices
        pos[cg++] = {_gfxPtr[0]->first.x, _gfxPtr[0]->first.y};
        color[cg++] = {_gfxPtr[0]->second.red, _gfxPtr[0]->second.green, _gfxPtr[0]->second.blue};
        sides[cg++] = SIDES;
    }

}
