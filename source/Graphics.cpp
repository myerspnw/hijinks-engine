/**
 * Graphics.cpp
 *
 * Implementation of the Graphics system.
 * 
 * Copyright (c) 2025 Mike Myers
 */
#include "Graphics.hpp"
using namespace Hijinks;

#include <SDL3/SDL.h>

bool Graphics::Initialize() {
   SDL_Window* w{};
   SDL_Renderer* r{};

   if (!SDL_CreateWindowAndRenderer("Hijinks Demo", 800, 600, 0, &w, &r)) {
      SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
      return false;
   }

   window_.reset(w);
   renderer_.reset(r);

   return true;
}

void Graphics::Update() {
   if (!renderer_)
      return;

   // Simple clear/present each frame.
   SDL_SetRenderDrawColor(renderer_.get(), 28, 36, 48, 255);
   SDL_RenderClear(renderer_.get());
   
   // TODO: draw world, UI, etc.
   
   SDL_RenderPresent(renderer_.get());
}

void Graphics::Shutdown() {
}
