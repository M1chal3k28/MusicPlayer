#include <Mode3D.hpp>
#include <raylib.h>
#include <iostream>

#include <Config.hpp>

void Mode3D::Draw(float * output, float * lastHeights, MusicContainer & musicContainer, Camera3D & camera)
{
    // Drawing the FFT
    BeginMode3D(camera);
        int ind = 0;  
        for(int i = 0; i < ROWS_3D; i++) {
            for(int j = 0; j < COLS_3D; j++) {
                // Height
                float height = lastHeights[ind];
                if(musicContainer.IsPlaying()) {
                    height = output[ind] * 200.0f;
                    height = std::max(lastHeights[ind] - (0.1f * lastHeights[ind]), height);
                } else 
                    height = std::max(0.0f, height - 0.1f * lastHeights[ind]);
                lastHeights[ind] = height;

                // Color
                Color color = {0};
                if (height * 18 > 255.0f)
                    color = Color{ 255, static_cast<unsigned char>(std::min(std::max(255.0f - height * 2, 0.0f), 128.0f)), 0, 255};
                else
                    color = Color{ static_cast<unsigned char>(std::min(height * 18, 255.0f)), 128, 0, 255};

                DrawCube({i * 1.0f, height / 2.0f, j*1.0f}, 1.0f, height, 1.0f, color);
                DrawCubeWires({i * 1.0f, height / 2.0f, j*1.0f},1.0f, height, 1.0f, BLACK);

                ind++;
            }
        }
    EndMode3D();
}