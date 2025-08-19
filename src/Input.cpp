/**
 * Input.cpp
 *
 * Implementation of the Input system.
 * 
 * Copyright (c) 2025 Mike Myers
 */
#include "Input.hpp"
#include "Events.hpp"
#include "EventBus.hpp"
using namespace Hijinks;

#include <SDL3/SDL.h>

bool Input::Initialize() {
   return true;
}

void Input::Update(double /*dt*/) {
   SDL_Event ev;

   while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_EVENT_QUIT:
         eventBus_->Publish(QuitEvent{});
         break;
      case SDL_EVENT_KEY_DOWN:
         if (ev.key.key == SDLK_ESCAPE) {
            // Publish a quit event when Escape is pressed.
            eventBus_->Publish(QuitEvent{});
         } else {
            // Handle other key down events if needed.
            SDL_Log("Key down: %s", SDL_GetKeyName(ev.key.key));
         }
         break;
      default:
         break;
      }
   }
}

void Input::Shutdown() {
   // Nothing to do currently.
}
