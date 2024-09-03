#pragma once    

#include <raylib.h>
#include <MusicContainer.hpp>

class Mode3D {
public:
    Mode3D() = default;
    void Draw(float * output, float * lastHeights, MusicContainer & musicContainer, Camera3D & camera);
};