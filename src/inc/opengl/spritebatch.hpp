#ifndef spritebatch_h
#define spritebatch_h

#include <iostream>
#include <vector>
#include <shaders/geoshader/GeoShader.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/SceneGraph/SceneGraph.h>
#include <Corrade/Containers/Pointer.h>

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
    SpriteBatch& drawShader(Corrade::Containers::Pointer<Magnum::SceneGraph::Camera2D> &camera, Magnum::Int screenHeight,
               Magnum::Int projectionHeight);
    void init();

private:
    Corrade::Containers::Pointer<GeoShader> shader;

    std::vector<std::pair<Rectangle, DNA::Visuals> *> _gfxPtr;
    std::vector<std::pair<Rectangle, DNA::Visuals>> _gfx;
    std::vector<RenderBatch> _renderBatches;

    std::vector<Magnum::Vector2> pos;
    std::vector<Magnum::Vector3> color;
    std::vector<float> sides;

    void createVertexArray();

    void createRenderBatches();

    Corrade::Containers::Pointer<Magnum::GL::Buffer> posBuffer;
    Corrade::Containers::Pointer<Magnum::GL::Buffer> colorBuffer;
    Corrade::Containers::Pointer<Magnum::GL::Buffer> sidesBuffer;
    Corrade::Containers::Pointer<Magnum::GL::Mesh> mesh;

};

#endif
