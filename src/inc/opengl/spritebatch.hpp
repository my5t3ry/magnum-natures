#ifndef spritebatch_h
#define spritebatch_h

#include <iostream>
#include <vector>
#include <shaders/geoshader/GeoShader.h>
#include <Magnum/GL/Buffer.h>

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


    void begin();

    void end();

    void draw(Rectangle r, DNA::Visuals v);

    void renderBatch();


private:
    GeoShader shader;

    Magnum::GL::Buffer posPuffer;

    std::vector<std::pair<Rectangle, DNA::Visuals> *> _gfxPtr;
    std::vector<std::pair<Rectangle, DNA::Visuals>> _gfx;
    std::vector<RenderBatch> _renderBatches;

    std::vector<Magnum::Vector2> pos;
    std::vector<Magnum::Vector3> color;
    std::vector<float> sides;
    void createVertexArray();

    void createRenderBatches();
    Magnum::GL::Buffer posBuffer;
    Magnum::GL::Buffer colorBuffer;
    Magnum::GL::Buffer sidesBuffer;
    Magnum::GL::Mesh mesh;

};

#endif
