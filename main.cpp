#include <raylib.h>
#include <iostream>
#include <FFT.hpp>
#include <memory.h>
#include <MusicContainer.hpp>

#include <Mode2D.hpp>
#include <Mode3D.hpp>

#include <Config.hpp>
#include <Callback.hpp> // Contains the callback function, Output and LastHeights initialization

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
    int modeID = 0;

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = Vector3 (CAM_POS_3D);    // Camera position
    camera.target = Vector3 (CAM_TARG_3D);                  // Camera looking at point
    camera.up = Vector3 ({ 0.0f, 1.0f, 0.0f });                      // Camera up vector (rotation towards target)
    camera.fovy = 120.0f;                                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                         // Camera mode type

    // For text display
    int TextWidth = MeasureText(musicContainer.GetFileName(), 20);
    bool TextToLong = TextWidth > WIDTH_2D;
    int offset = 0;
    int targetOffset = 0;
    int TextDirection = 1.0f;

    if (TextToLong) {
        offset = 0;
        targetOffset = TextWidth - WIDTH_2D;
    }
    

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
            if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_N)) {
                if (IsKeyPressed(KEY_M)) 
                    musicContainer.NextMusic();
                if (IsKeyPressed(KEY_N))
                    musicContainer.PrevMusic();

                TextWidth = MeasureText(musicContainer.GetFileName(), 20);
                TextToLong = TextWidth > WIDTH_2D;
                offset = 0;
                targetOffset = TextWidth - WIDTH_2D;  
            }

            // Mode 
            if (IsKeyPressed(KEY_X)) {
                isMode3D = !isMode3D;
                if (isMode3D)
                    SetWindowSize(WIDTH_3D, HEIGHT_3D);
                else 
                    SetWindowSize(WIDTH_2D, HEIGHT_2D);
            }

            // ModeId 
            if (IsKeyPressed(KEY_ONE))   modeID = 0;
            if (IsKeyPressed(KEY_TWO))   modeID = 1;
            if (IsKeyPressed(KEY_THREE)) modeID = 2;
            if (IsKeyPressed(KEY_FOUR))  modeID = 3;
            if (IsKeyPressed(KEY_FIVE))  modeID = 4;

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
                mode2D.Draw(output, LastHeights, musicContainer, static_cast<Mode2DType>(modeID));
            }

            // Drawing info
            Color TextColor = { 255, 128, 0, 255 };

            DrawText((isMode3D ? "Mode: 3D" : "Mode: 2D"), 10, 10, 20, TextColor);
            DrawText(TextFormat("ModeId: %d", modeID), 10, 30, 20, TextColor);

            // Music name proper display
            if (TextToLong) {
                offset += TextDirection;
                if (offset >= targetOffset + 40 || offset <= -20)
                    TextDirection *= -1.0f;
            }
            DrawText(musicContainer.GetFileName(), GetScreenWidth() - TextWidth - 10 + offset, GetScreenHeight() - 30, 20, TextColor);

            DrawText(TextFormat("Volume: %.2f", musicContainer.MusicInfo()["volume"]), 10, 50, 20, TextColor);
            DrawText(TextFormat("Pitch: %.2f", musicContainer.MusicInfo()["pitch"]), 10, 70, 20, TextColor);
            DrawText(TextFormat("Pan: %.2f", musicContainer.MusicInfo()["pan"]), 10, 90, 20, TextColor);

            // PlayBack info
            DrawText(TextFormat("Playing: %s", musicContainer.IsPlaying() ? "Yes" : "No"), 10, 110, 20, TextColor);
            DrawText(TextFormat("Time: %.2f", musicContainer.SecsPlaying()), 10, 130, 20, TextColor);
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