#pragma once

#include <MusicContainer.hpp>

class Mode {
public:
    Mode() = default;
    virtual ~Mode() = default;
    virtual void Draw(float * output, float * lastHeights, MusicContainer & musicContainer, Camera3D & camera) = 0;
};