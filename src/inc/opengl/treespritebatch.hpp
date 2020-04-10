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

    void draw(glm::vec2 pos, glm::vec3 v);

    void renderBatch();

    void render(std::vector<QuadtreeVertexData> list);


private:
    void createRenderBatches();

    void createVertexArray();

    GLuint _vbo;
    GLuint _vao;

    std::vector<std::pair<glm::vec2, glm::vec3> *> _gfxPtr;
    std::vector<std::pair<glm::vec2, glm::vec3>> _gfx;
    std::vector<RenderBatch> _renderBatches;

    GeoShader shader;

};

#endif
