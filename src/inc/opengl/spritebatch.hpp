#ifndef spritebatch_h
#define spritebatch_h

#include <Magnum/GL/Buffer.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <shaders/geoshader/GeoShader.h>

#include "dna.hpp"

class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices) : offset(Offset),
                                                     numVertices(NumVertices) {}

    GLuint offset;
    GLuint numVertices;
};

class SpriteBatch {
public:
    SpriteBatch();

    void init();

    void begin();

    void end();

    void draw(Rectangle r, DNA::Visuals v);

    void renderBatch();

private:
    Magnum::GeoShader shader;
    void createRenderBatches();

    void createVertexArray();

    Magnum::GL::Buffer posPuffer;

    std::vector<std::pair<Rectangle, DNA::Visuals> *> _gfxPtr;
    std::vector<std::pair<Rectangle, DNA::Visuals>> _gfx;
    std::vector<RenderBatch> _renderBatches;

    std::vector<glm::vec2> pos;
    std::vector<glm::vec3> color;
    std::vector<float> sides;
};

#endif
