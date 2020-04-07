#ifndef spritebatch_h
#define spritebatch_h

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <Magnum/GL/Buffer.h>

#include "inc/shaders//geoshader/GeoShader.h"
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
    explicit SpriteBatch(Magnum::GeoShader theshader);

    void init();

    void begin();

    void end();

    void draw(Rectangle r, DNA::Visuals v);

    void renderBatch();

private:
    void createRenderBatches();

    void createVertexArray();

    Magnum::GL::Buffer buffer;

    std::vector<std::pair<Rectangle, DNA::Visuals> *> _gfxPtr;
    std::vector<std::pair<Rectangle, DNA::Visuals>> _gfx;
    std::vector<RenderBatch> _renderBatches;

    Magnum::GeoShader shader;
};

#endif
