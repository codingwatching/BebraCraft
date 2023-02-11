#include <iostream>

#include <GL/glew.h>
#include "engine/core.h"

namespace bebra {

    int init(gapi GAPI) {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            std::cout << "[ERROR] SDL::INIT" << std::endl << SDL_GetError() << std::endl;
            return 1;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_GL_SetSwapInterval(0);

        return 0;
    }

    SDL_Window* window(std::string windowName, uint windowWidth, uint windowHeight, uint32_t properties_graphic_api) {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); 

        SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "1"); //Keep X11 compositor enable
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");

        SDL_Window *window = SDL_CreateWindow(windowName.c_str() , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            windowWidth, windowHeight, properties_graphic_api);
        
        if (window == NULL){
            std::cout << "ERROR::SDL::CREATE_WINDOW\n";
            //return 1;
        }

        SDL_SetWindowGrab(window, SDL_TRUE);
        SDL_SetWindowMouseGrab(window, SDL_TRUE);
        SDL_SetRelativeMouseMode(SDL_TRUE);

        return window;
    }
    
    void contextCreate(SDL_Window* window, uint windowWidth, uint windowHeight, bool debugVerticles) {
        //SDL_GLContext Context = 
            SDL_GL_CreateContext(window);
        glewInit();
        glViewport(0, 0, windowWidth, windowHeight);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if (debugVerticles)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}