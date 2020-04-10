//
// Created by my5t3ry on 4/10/20.
//

#ifndef MAGNUM_NATURE_SIM_RENDERBATCH_H
#define MAGNUM_NATURE_SIM_RENDERBATCH_H

#include "constants.hpp"

class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices) : offset(Offset),
                                                     numVertices(NumVertices) {}

    GLuint offset;
    GLuint numVertices;
};


#endif //MAGNUM_NATURE_SIM_RENDERBATCH_H
