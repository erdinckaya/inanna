//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_GRAPHICS_H
#define INANNA_GRAPHICS_H

#include <unordered_map>
#include "SDLWindow.h"
#include "SDLContext.h"
#include "SDL.h"
#include "SDLSurface.h"


#include <SDL_opengl.h>
#include "../../Assets/Resources.h"
#include "../Util/Math/Rect.h"
#include "../../ThirdParty/MonitorX/MonitorX.h"

namespace Inanna {
    class Graphics {
    public:
        Graphics(unsigned int width, unsigned int height, SDL_WindowFlags flags);

        ~Graphics();

        void Init();

        void DrawTexture(ImageAsset image, Rectf clip, Rectf destination, float angle, Vecf scale, bool flipY = false,
                         bool flipX = false);

        void DrawRect(Rectf rect, SDL_Color color, int width);

        void Update(float dt);

        void PassEvent(SDL_Event *event);

#ifdef MONITORX_DEBUG
        std::unique_ptr<monitorx::MonitorX> monitorX;
#endif

    private:
        SDL sdl;
        SDLWindow window;
        SDLContext context;

        void InitResources();


        std::unordered_map<const char *, std::unique_ptr<SDLSurface>> spriteSheets;
    };
}


#endif //INANNA_GRAPHICS_H
