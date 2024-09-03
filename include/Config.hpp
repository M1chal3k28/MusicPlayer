#pragma once

// Music settings
#define MUSIC_FOLDER "music"
#define MUSIC_VOLUME 0.00
#define MUSIC_PITCH  1.0
#define MUSIC_PAN    0.5

#define SPACING_2D 2
#define SPACING_3D 3

#define SIZE_3D   484

#define WIDTH_3D  800
#define HEIGHT_3D 800

#define WIDTH_2D  800
#define HEIGHT_2D 450

#ifdef _WIN32
    #define SIZE        480
    #define COLS_3D     15
    #define ROWS_3D     16
    #define CAM_POS_3D  { 7.69849, 9.62714, 23.7583 }
    #define CAM_TARG_3D { 7.80469, 14.691, -2.2017 }
#else
    #define COLS_3D     15
    #define ROWS_3D     17
    #define SIZE        512
    #define CAM_POS_3D  { 8.21074, 9.27036, 25.5244 }
    #define CAM_TARG_3D { 8.23829, 17.103 , 0.261318 }
#endif