#ifndef TreeSpriteBatch_h
#define TreeSpriteBatch_h

#include "constants.hpp"
#include "renderbatch.h"
#include <iostream>
#include <vector>
#include <list.hpp>

#include "geoshader.hpp"
#include "dna.hpp"


class TreeSpriteBatch {
public:
    TreeSpriteBatch(GeoShader theshader);
    void init();
    void begin();
    void end();

    void draw(Rectangle r, DNA::Visuals v);

    void renderBatch();
    void render(std::vector<Rectangle> list);


private:
    void createRenderBatches();

    void createVertexArray();
    GLuint _vbo;
    GLuint _vao;

    std::vector<std::pair<Rectangle, DNA::Visuals> *> _gfxPtr;
    std::vector<std::pair<Rectangle, DNA::Visuals>> _gfx;
    std::vector<RenderBatch> _renderBatches;

    GeoShader shader;

};

#endif
