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

#include "../../ThirdParty/ImGui/imgui.h"
#include "../../ThirdParty/ImGui/imgui_impl_sdl.h"
#include "../../ThirdParty/ImGui/imgui_impl_opengl2.h"

namespace Inanna {
    class Graphics {
    public:
        Graphics(unsigned int width, unsigned int height, SDL_WindowFlags flags);

        ~Graphics();

        void DrawTexture(ImageAsset image, Rectf clip, Rectf destination, float angle, Vecf scale);

        void Update(float dt);

    private:
        SDL sdl;
        SDLWindow window;
        SDLContext context;

        void InitResources();


        std::unordered_map<const char *, std::unique_ptr<SDLSurface>> spriteSheets;

        void InitImGui();

        void RenderImGui();
    };
}


#endif //INANNA_GRAPHICS_H
