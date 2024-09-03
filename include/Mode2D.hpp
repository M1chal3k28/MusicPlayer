#pragma once    

#include <MusicContainer.hpp>
#include <raylib.h>

enum Mode2DType {
    DEFAULT = 0,
    MODEL_1,
    MODEL_2,
    MODEL_3,
    MODEL_4
};

class Mode2D {
public:
    Mode2D() = default;
    void Draw(float * output, float * lastHeights, MusicContainer & musicContainer, Mode2DType type);
};