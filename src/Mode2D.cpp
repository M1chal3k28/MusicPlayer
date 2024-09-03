#include <Mode2D.hpp>
#include <raylib.h>
#include <iostream>

#include <Config.hpp>

void Mode2D::Draw(float * output, float * lastHeights, MusicContainer & musicContainer, Mode2DType type) {
    // Drawing the FFT
    switch (type)
    {
        default:
        case DEFAULT: {
            for(int i = 0; i < SIZE / 2; i++) {
                // Offset and position
                Vector2 windowOffset = { GetScreenWidth() / 2 - SIZE / 2.0f, GetScreenHeight() / 2.0f - 0.001f};
                Vector2 pos = {i * SPACING_2D + windowOffset.x, windowOffset.y};

                // Height
                float height = lastHeights[i];
                if(musicContainer.IsPlaying()) {
                    height = output[i] * 200.0f + 1.0f;
                    height = std::max(lastHeights[i] - (0.1f * lastHeights[i]), height);
                } else 
                    height = std::max(1.0f, height - 0.1f * lastHeights[i]);

                lastHeights[i] = height;

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
        } break;

        case MODEL_1: {
            float colorOffset = 255.0f / SIZE / 2.0f * 2.0f; 
            for(int i = 0; i < SIZE / 2; i++) {
                // Offset and position
                Vector2 windowOffset = { GetScreenWidth() / 2 - SIZE / 2.0f, GetScreenHeight() / 2.0f - 0.001f};
                Vector2 pos = {i * SPACING_2D + windowOffset.x, windowOffset.y};

                // Height
                float height = lastHeights[i];
                if(musicContainer.IsPlaying()) {
                    height = output[i] * 200.0f + 1.0f;
                    height = std::max(lastHeights[i] - (0.1f * lastHeights[i]), height);
                } else 
                    height = std::max(1.0f, height - 0.1f * lastHeights[i]);

                lastHeights[i] = height;

                // Color
                Color color = { static_cast<unsigned char>(colorOffset * i), 0, static_cast<unsigned char>(colorOffset * i), 255};

                // Drawing
                DrawRectangle(pos.x, pos.y - height, SPACING_2D, height, color);
                DrawRectangle(pos.x, pos.y         , SPACING_2D, height, color);
            }
        } break;

        case MODEL_2: {
            float colorOffset = 255.0f / SIZE / 2.0f * 2.0f; 
            for(int i = 0; i < SIZE / 2; i++) {
                // Offset and position
                Vector2 windowOffset = { GetScreenWidth() / 2 - SIZE / 2.0f, GetScreenHeight() / 2.0f - 0.001f};
                Vector2 pos = {i * SPACING_2D + windowOffset.x, windowOffset.y};

                // Height
                float height = lastHeights[i];
                if(musicContainer.IsPlaying()) {
                    height = output[i] * 200.0f + 1.0f;
                    height = std::max(lastHeights[i] - (0.1f * lastHeights[i]), height);
                } else 
                    height = std::max(1.0f, height - 0.1f * lastHeights[i]);

                lastHeights[i] = height;

                // Color
                Color color = { static_cast<unsigned char>(colorOffset * i), static_cast<unsigned char>(colorOffset * i), 0, 255};

                // Drawing
                DrawRectangle(pos.x, pos.y - height, SPACING_2D, height, color);
                DrawRectangle(pos.x, pos.y         , SPACING_2D, height, color);
            }
        } break;

        case MODEL_3: { 
            int index = SIZE / 2 - 1;
            for(int i = 0; i < SIZE / 2; i++) {
                // Offset and position
                Vector2 windowOffset = { GetScreenWidth() / 2 - SIZE / 2.0f, GetScreenHeight() / 2.0f - 0.001f};
                Vector2 pos = {i * SPACING_2D + windowOffset.x, windowOffset.y};

                // Height
                float height = lastHeights[index];
                if(musicContainer.IsPlaying()) {
                    height = output[index] * 200.0f + 1.0f;
                    height = std::max(lastHeights[index] - (0.1f * lastHeights[index]), height);
                } else 
                    height = std::max(1.0f, height - 0.1f * lastHeights[index]);

                lastHeights[index] = height;

                // Color
                Color color = {0};
                if (height * 18 > 255.0f)
                    color = Color{ 255, static_cast<unsigned char>(std::min(std::max(255.0f - height * 2, 0.0f), 128.0f)), 0, 255};
                else
                    color = Color{ static_cast<unsigned char>(std::min(height * 18, 255.0f)), 128, 0, 255};

                // Drawing
                DrawRectangle(pos.x, pos.y - height, SPACING_2D, height, color);
                DrawRectangle(pos.x, pos.y         , SPACING_2D, height, color);

                index--;
            }
        } break;

        case MODEL_4: { 
            int index = SIZE / 2 - 1;
            for(int i = 0; i < SIZE / 2; i++) {
                // Offset and position
                Vector2 windowOffset = { GetScreenWidth() / 2 - SIZE / 2.0f, GetScreenHeight() / 2.0f + 2.0f};
                Vector2 pos =  {i * SPACING_2D + windowOffset.x, windowOffset.y};
                Vector2 pos2 = {SIZE - 2 - i * SPACING_2D + windowOffset.x, windowOffset.y};

                // Height
                float height = lastHeights[index];
                if(musicContainer.IsPlaying()) {
                    height = output[index] * 200.0f + 1.0f;
                    height = std::max(lastHeights[index] - (0.1f * lastHeights[index]), height);
                } else 
                    height = std::max(1.0f, height - 0.1f * lastHeights[index]);

                lastHeights[index] = height;

                // Color
                Color color = {0};
                if (height * 18 > 255.0f)
                    color = Color{ 255, static_cast<unsigned char>(std::min(std::max(255.0f - height * 2, 0.0f), 128.0f)), 0, 255};
                else
                    color = Color{ static_cast<unsigned char>(std::min(height * 18, 255.0f)), 128, 0, 255};

                // Drawing
                DrawRectangle(pos.x, pos.y - height, SPACING_2D, height, color);
                DrawRectangle(pos2.x, pos2.y         , SPACING_2D, height, color);

                index--;
            }
        } break;
    }
}