// #include <raylib.h>
// #include <iostream>

// // #include <FFT.cpp>

// int main() {
//     // Initialization
//     //--------------------------------------------------------------------------------------
//     InitAudioDevice();
//     // Music music = LoadMusicStream("../CopyrightedMusic.mp3");
//     // std::cout << IsMusicReady(music);
//     // SetMusicVolume(music, 0.5f);

//     // PlayMusicStream(music);
//     const int screenWidth = 800;
//     const int screenHeight = 450;

//     InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

//     // Define the camera to look into our 3d world
//     Camera camera = { 0 };
//     camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
//     camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
//     camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
//     camera.fovy = 60.0f;                                // Camera field-of-view Y
//     camera.projection = CAMERA_PERSPECTIVE;            // Camera mode type

//     float cubeSize = 5.0f;
//     Vector3 cubePosition = { 0.0f, cubeSize / 2.0f, 0.0f };

//     DisableCursor();
//     SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//     //--------------------------------------------------------------------------------------

//     // Main game loop
//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         // Update
//         //----------------------------------------------------------------------------------
//         // UpdateMusicStream(music);
//         // std::cout << *(music.stream.buffer)->data[0] << std::endl;
        
//         UpdateCamera(&camera, CAMERA_FREE);
//         // SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2);
//         //----------------------------------------------------------------------------------

//         // Draw
//         //----------------------------------------------------------------------------------
//         BeginDrawing();

//             ClearBackground(RAYWHITE);

//             BeginMode3D(camera);

//                 DrawCube(cubePosition, 1.0, cubeSize, 1.0f, RED);

//                 DrawGrid(10, 1.0f);

//             EndMode3D();

//             DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

//             DrawFPS(10, 10);

//         EndDrawing();
//         //----------------------------------------------------------------------------------
//     }

//     // De-Initialization
//     //--------------------------------------------------------------------------------------
//     CloseWindow();        // Close window and OpenGL context
//     //--------------------------------------------------------------------------------------
//     return EXIT_SUCCESS;
// }

#include <raylib.h>
#include <iostream>
#include <FFT.hpp>
#include <memory.h>
#include <MusicContainer.hpp>

#ifdef _WIN32
    #define SIZE 480
    #define SPACING 2
#else
    #define SIZE 512
    #define SPACING 4
#endif

float output[SIZE / 2];
float LastHeights[SIZE / 2];

void callback(void * bufferData, unsigned int frames) {
    float * buffer = (float *)bufferData;
    computeFFT(buffer, frames, output);
}

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(800, 450, "Visualizer");
    SetTargetFPS(60);

    InitAudioDevice();

    // Sound Stuff
    MusicContainer musicContainer(callback);
    musicContainer.Play();

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

            musicContainer.Update();
        //----------------------------------------------------------------------------------    

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            Color TextColor = { 255, 128, 0, 255 };
            float Highest = 0;
            for(int i = 0; i < SIZE / 2; i++) {
                // Offset and position
                Vector2 windowOffset = { GetScreenWidth() / 2 - SIZE / 2.0f, GetScreenHeight() / 2.0f};
                Vector2 pos = {i * SPACING + windowOffset.x, windowOffset.y};

                // Height
                float height = LastHeights[i];
                if(musicContainer.IsPlaying()) {
                    height = output[i] * 200.0f + 1.0f;
                    height = max(LastHeights[i] - (0.1f * LastHeights[i]), height);
                } else 
                    height = max(1.0f, height - 0.1f * LastHeights[i]);

                LastHeights[i] = height;

                // Color
                Color color = Color{ static_cast<unsigned char>(min(height * 8, 255.0f)), 128, 0, 255};

                // Getting max vals
                if(height > Highest) Highest = height;

                // Drawing
                DrawRectangle(pos.x, pos.y - height, 2, height, color);
                DrawRectangle(pos.x, pos.y         , 2, height, color);
            }
            DrawText("2D Mode", 10, 10, 20, TextColor);
            DrawText(musicContainer.GetFileName(), GetScreenWidth() - 10 - MeasureText(musicContainer.GetFileName(), 20), GetScreenHeight() - 30, 20, TextColor);

            // Info
            DrawText(TextFormat("Volume: %.2f", musicContainer.MusicInfo()["volume"]), 10, 30, 20, TextColor);
            DrawText(TextFormat("Pitch: %.2f", musicContainer.MusicInfo()["pitch"]), 10, 50, 20, TextColor);
            DrawText(TextFormat("Pan: %.2f", musicContainer.MusicInfo()["pan"]), 10, 70, 20, TextColor);

            // PlayBack
            DrawText(TextFormat("Playing: %s", musicContainer.IsPlaying() ? "Yes" : "No"), 10, 90, 20, TextColor);
            DrawText(TextFormat("Time: %.2f", musicContainer.SecsPlaying()), 10, 110, 20, TextColor);

            ClearBackground(Color{18, 90, 128, 255});
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