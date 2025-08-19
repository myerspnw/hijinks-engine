/**
 * Graphics.hpp
 *
 * The Graphics class implements the System interface to provide
 * rendering capabilities.
 *
 * Copyright (c) 2025 Mike Myers
 */
#pragma once

#include "System.hpp"

#include <SDL3/SDL.h>

namespace Hijinks {
   using WindowPtr = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;
   using RendererPtr = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>;

   class Graphics final : public System {
   public:
      using System::System;

      Graphics() = default;
      bool Initialize() override;
      void Update(double dt) override;
      void Shutdown() override;

   private:
      WindowPtr   window_{ nullptr, SDL_DestroyWindow };
      RendererPtr renderer_{ nullptr, SDL_DestroyRenderer };
   };
}
