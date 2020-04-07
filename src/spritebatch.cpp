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
    const bufferArrays &arrays = createVertexArray();
    // Bind our VAO. This sets up the opengl state we need, including the
    // vertex attribute pointers and it binds the VBO

    //glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
    Magnum::GL::Buffer posBuffer;
    posBuffer.setData(arrays.pos, Magnum::GL::BufferUsage::StaticDraw);
    Magnum::GL::Buffer colorBuffer;
    colorBuffer.setData(arrays.color, Magnum::GL::BufferUsage::StaticDraw);
    Magnum::GL::Buffer sidesBuffer;
    sidesBuffer.setData(arrays.sides, Magnum::GL::BufferUsage::StaticDraw);
    mesh.setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer(posBuffer, 0, GeoShader::pos{})
            .setCount(arrays.pos.size());
    mesh.setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer(posBuffer, 0, GeoShader::pos{})
            .setCount(arrays.color.size());
    mesh.setPrimitive(Magnum::GL::MeshPrimitive::Points)
            .addVertexBuffer(posBuffer, 0, GeoShader::color{})
            .setCount(arrays.color.size());
    shader.draw(mesh);
}

bufferArrays SpriteBatch::createVertexArray() {
    // This will store all the vertices that we need to upload
    // Resize the buffer to the exact size we need so we can treat
    // it like an array
    std::vector<glm::vec2> pos;
    std::vector<glm::vec3> color;
    std::vector<float> sides;
    pos.resize(_gfxPtr.size() * sizeof(glm::vec2));
    color.resize(_gfxPtr.size() * sizeof(glm::vec2));
    sides.resize(_gfxPtr.size() * sizeof(float));

    if (_gfxPtr.empty()) {
        return {pos,color,sides};
    }


    //Add all the rest of the glyphs
    //std::cout << "ptr size = " <<  _gfxPtr.size() << std::endl;
    for (int cg = 1; cg < _gfxPtr.size(); cg++) {
        // If its part of the current batcdh, just increase numVertices
        pos[cg++] = {_gfxPtr[0]->first.x, _gfxPtr[0]->first.y};
        color[cg++] = {_gfxPtr[0]->second.red, _gfxPtr[0]->second.green, _gfxPtr[0]->second.blue};
        sides[cg++] = SIDES;
    }
    return  {pos,color,sides};
}
