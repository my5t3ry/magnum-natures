#ifndef spritebatch_h
#define spritebatch_h

#include <iostream>
#include <vector>
#include <shaders/geoshader/GeoShader.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/SceneGraph/SceneGraph.h>
#include <Corrade/Containers/Pointer.h>
#include <Magnum/Math/Vector3.h>

#include "dna.hpp"
#include "opengl/camera.hpp"

struct OrganismVertex {
    Magnum::Vector2 pos;
    Magnum::Vector3 color;
    float sides;
};


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
    SpriteBatch& drawShader();
    void init(Camera camera);

private:
    Corrade::Containers::Pointer<GeoShader> shader;

    std::vector<std::pair<Rectangle, DNA::Visuals> *> _gfxPtr;
    std::vector<std::pair<Rectangle, DNA::Visuals>> _gfx;
    std::vector<RenderBatch> _renderBatches;

    std::vector<OrganismVertex> vertex;

    void createVertexArray();


    Corrade::Containers::Pointer<Magnum::GL::Buffer> posBuffer;
    Corrade::Containers::Pointer<Magnum::GL::Buffer> colorBuffer;
    Corrade::Containers::Pointer<Magnum::GL::Buffer> sidesBuffer;
    Corrade::Containers::Pointer<Magnum::GL::Mesh> posMesh;
    Corrade::Containers::Pointer<Magnum::GL::Mesh> colorMesh;
    Corrade::Containers::Pointer<Magnum::GL::Mesh> sidesMesh;

};

#endif
