#include <raylib.h>
#include <iostream>
#include <FFT.hpp>
#include <memory.h>
#include <MusicContainer.hpp>

#include <Mode2D.hpp>
#include <Mode3D.hpp>

#include <Config.hpp>

float output[SIZE / 2];
float LastHeights[SIZE / 2];

void callback(void * bufferData, unsigned int frames) {
    float * buffer = (float *)bufferData;
    computeFFT(buffer, frames, output);
}

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(WIDTH_2D, HEIGHT_2D, "Visualizer");
    SetTargetFPS(60);

    InitAudioDevice();

    // Sound Stuff
    MusicContainer musicContainer(callback);
    musicContainer.Play();

    // Rendering Stuff
    Mode2D mode2D;
    Mode3D mode3D;
    bool isMode3D = false;

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 8.21074f, 9.27036f, 25.5244f };    // Camera position
    camera.target = (Vector3){ 8.23829f, 17.103f, 0.261318f };                  // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };                      // Camera up vector (rotation towards target)
    camera.fovy = 120.0f;                                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                         // Camera mode type

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
            // PlayBack
            if (IsKeyPressed(KEY_SPACE)) 
                  musicContainer.ToggleMusic();
            
            if (IsKeyDown(KEY_LEFT)) 
                musicContainer.Seek(-10.0f);
            if (IsKeyDown(KEY_RIGHT)) 
                musicContainer.Seek(+1.0f);

            // Pan
            if (IsKeyPressed(KEY_O)) 
                musicContainer.AddPan();
            if (IsKeyPressed(KEY_P))
                musicContainer.SubPan();

            // Pitch
            if (IsKeyPressed(KEY_UP))
                musicContainer.AddPitch();
            if (IsKeyPressed(KEY_DOWN)) 
                musicContainer.SubPitch();

            // Volume
            if (IsKeyPressed(KEY_KP_ADD)) 
                musicContainer.AddVolume();
            if (IsKeyPressed(KEY_KP_SUBTRACT)) 
                musicContainer.SubVolume();

            // Music 
            if (IsKeyPressed(KEY_M)) 
                musicContainer.NextMusic();
            if (IsKeyPressed(KEY_N))
                musicContainer.PrevMusic();

            // Mode 
            if (IsKeyPressed(KEY_X)) {
                isMode3D = !isMode3D;
                if (isMode3D)
                    SetWindowSize(WIDTH_3D, HEIGHT_3D);
                else 
                    SetWindowSize(WIDTH_2D, HEIGHT_2D);
            }

            musicContainer.Update();
        //----------------------------------------------------------------------------------    

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing(); 
            ClearBackground(Color{18, 90, 128, 255});

            // Rendering Mode
            if(isMode3D) {
                mode3D.Draw(output, LastHeights, musicContainer, camera);
                DrawFPS(GetScreenWidth() - 30, 10);
            } else {
                mode2D.Draw(output, LastHeights, musicContainer, camera);
            }

            // Drawing info
            Color TextColor = { 255, 128, 0, 255 };

            DrawText((isMode3D ? "Mode: 3D" : "Mode: 2D"), 10, 10, 20, TextColor);
            DrawText(musicContainer.GetFileName(), GetScreenWidth() - 10 - MeasureText(musicContainer.GetFileName(), 20), GetScreenHeight() - 30, 20, TextColor);

            DrawText(TextFormat("Volume: %.2f", musicContainer.MusicInfo()["volume"]), 10, 30, 20, TextColor);
            DrawText(TextFormat("Pitch: %.2f", musicContainer.MusicInfo()["pitch"]), 10, 50, 20, TextColor);
            DrawText(TextFormat("Pan: %.2f", musicContainer.MusicInfo()["pan"]), 10, 70, 20, TextColor);

            // PlayBack info
            DrawText(TextFormat("Playing: %s", musicContainer.IsPlaying() ? "Yes" : "No"), 10, 90, 20, TextColor);
            DrawText(TextFormat("Time: %.2f", musicContainer.SecsPlaying()), 10, 110, 20, TextColor);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------    

    return EXIT_SUCCESS;
} 