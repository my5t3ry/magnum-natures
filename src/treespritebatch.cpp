#include "opengl/treespritebatch.hpp"

TreeSpriteBatch::TreeSpriteBatch(GeoShader theshader) : _vbo(0), _vao(0), shader(theshader) {}

void TreeSpriteBatch::init() {
    createVertexArray();
}

void TreeSpriteBatch::begin() {
    glEnable(GL_PROGRAM_POINT_SIZE);
    _renderBatches.clear();
    // Makes _glpyhs.size() == 0, however it does not free internal memory.
    // So when we later call emplace_back it doesn't need to internally call new.
    _gfx.clear();
}

void TreeSpriteBatch::end() {
    // Set up all pointers for fast sorting
    _gfxPtr.resize(_gfx.size());
    for (int i = 0; i < _gfx.size(); i++)
        _gfxPtr[i] = &_gfx[i];

    //sortGlyphs();
    createRenderBatches();
}

void TreeSpriteBatch::draw(glm::vec2 pos, glm::vec3 v) {
    _gfx.emplace_back(std::make_pair(pos, v));
}

void TreeSpriteBatch::renderBatch() {
    // Bind our VAO. This sets up the opengl state we need, including the
    // vertex attribute pointers and it binds the VBO
    shader.Bind();
    glBindVertexArray(_vao);
    //glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
    for (auto &_renderBatche : _renderBatches)
        glDrawArrays(GL_QUADS, _renderBatche.offset, _renderBatche.numVertices);

    glBindVertexArray(0);
}

void TreeSpriteBatch::createRenderBatches() {
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
    vertices[cv++] = _gfxPtr[0]->second.x;
    vertices[cv++] = _gfxPtr[0]->second.y;
    vertices[cv++] = _gfxPtr[0]->second.z;
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
        vertices[cv++] = _gfxPtr[cg]->second.x;
        vertices[cv++] = _gfxPtr[cg]->second.y;
        vertices[cv++] = _gfxPtr[cg]->second.z;
        vertices[cv++] = SIDES;

        offset += 6;
    }

    // Bind our VBO
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // Orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TreeSpriteBatch::createVertexArray() {
    // Generate the VAO if it isn't already generated
    if (_vao == 0)
        glGenVertexArrays(1, &_vao);

    // Bind the VAO. All subsequent opengl calls will modify it's state.
    glBindVertexArray(_vao);

    //G enerate the VBO if it isn't already generated
    if (_vbo == 0)
        glGenBuffers(1, &_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    //Tell opengl what attribute arrays we need
    GLint posAttrib = glGetAttribLocation(shader.m_program, "pos");
    glEnableVertexAttribArray(posAttrib);

    GLint colAttrib = glGetAttribLocation(shader.m_program, "color");
    glEnableVertexAttribArray(colAttrib);

    GLint sidesAttrib = glGetAttribLocation(shader.m_program, "sides");
    glEnableVertexAttribArray(sidesAttrib);

    //glEnableVertexAttribArray(2);                        L

    //This is the position attribute pointer

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    //This is the color attribute pointer
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (2 * sizeof(float)));
    //This is the UV attribute pointer
    glVertexAttribPointer(sidesAttrib, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (5 * sizeof(float)));
    glBindVertexArray(0);
}

void TreeSpriteBatch::render(std::vector<QuadtreeVertexData> list) {
    begin();

    for (auto &vertexData : list) {
//        float i = 4.0f;
        float i = vertexData.level / 100.0 * 25.0 + 1.4;
        glm::vec3 col = {0.03f * i, 0.05f * i, 0.03f * i};
        draw({vertexData.rectangle.x, vertexData.rectangle.y}, col);
        draw({vertexData.rectangle.x, vertexData.rectangle.y + vertexData.rectangle.h}, col);
        draw({vertexData.rectangle.x + vertexData.rectangle.w, vertexData.rectangle.y + vertexData.rectangle.h}, col);
        draw({vertexData.rectangle.x + vertexData.rectangle.w, vertexData.rectangle.y}, col);
//        draw(rectangle, {0.5f + i, 0.8f - 1, 0.2f + 1});
        i += 0.0005f;
    }

    end();
    renderBatch();
}

