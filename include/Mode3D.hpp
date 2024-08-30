#pragma once    

#include <Mode.hpp>
#include <raylib.h>

class Mode3D : public Mode {
public:
    Mode3D() = default;
    virtual void Draw(float * output, float * lastHeights, MusicContainer & musicContainer, Camera3D & camera);
};