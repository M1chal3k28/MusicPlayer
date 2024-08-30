#pragma once    

#include <Mode.hpp>

class Mode2D : public Mode {
public:
    Mode2D() = default;
    virtual void Draw(float * output, float * lastHeights, MusicContainer & musicContainer, Camera3D & camera);
};