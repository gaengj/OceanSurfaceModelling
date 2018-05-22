#ifndef GLUT_cross_h
#define GLUT_cross_h

/* Definition des identificateures de plateformes */
#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_LINUX    3

/* Detection de la plateforme */
#if defined(_WIN32)
    #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define PLATFORM PLATFORM_MAC
#elif defined(__linux__)
    #define PLATFORM PLATFORM_LINUX
#endif

/* Inclusion des fichiers de définitions correspondants à la plateforme */
#if PLATFORM==PLATFORM_WINDOWS
    #include <windows.h>
    #include <GL/glut.h>
#elif PLATFORM==PLATFORM_MAC
    #include <GLUT/glut.h>
#elif PLATFORM==PLATFORM_LINUX
    #include <GL/glut.h>
#endif

#endif
