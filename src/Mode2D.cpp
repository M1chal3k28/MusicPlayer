#include <Mode2D.hpp>
#include <raylib.h>
#include <iostream>

#include <Config.hpp>

void Mode2D::Draw(float * output, float * LastHeights, MusicContainer & musicContainer, Camera3D & camera) {
    // Drawing the FFT
    for(int i = 0; i < SIZE / 2; i++) {
        // Offset and position
        Vector2 windowOffset = { GetScreenWidth() / 2 - SIZE / 2.0f, GetScreenHeight() / 2.0f - 0.01f};
        Vector2 pos = {i * SPACING_2D + windowOffset.x, windowOffset.y};

        // Height
        float height = LastHeights[i];
        if(musicContainer.IsPlaying()) {
            height = output[i] * 200.0f + 1.0f;
            height = std::max(LastHeights[i] - (0.1f * LastHeights[i]), height);
        } else 
            height = std::max(1.0f, height - 0.1f * LastHeights[i]);

        LastHeights[i] = height;

        // Color
        Color color = {0};
        if (height * 18 > 255.0f)
            color = Color{ 255, static_cast<unsigned char>(std::min(std::max(255.0f - height * 2, 0.0f), 128.0f)), 0, 255};
        else
            color = Color{ static_cast<unsigned char>(std::min(height * 18, 255.0f)), 128, 0, 255};

        // Drawing
        DrawRectangle(pos.x, pos.y - height, SPACING_2D, height, color);
        DrawRectangle(pos.x, pos.y         , SPACING_2D, height, color);
    }
}