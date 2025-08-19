/**
 * Engine.cpp
 *
 * Implementation of the Engine class
 * 
 * Copyright (c) 2025 Mike Myers
 */
#include "Engine.hpp"

#include <SDL3/SDL.h>

#include "EventBus.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include "Events.hpp"
using namespace Hijinks;

Engine::Engine()
   : eventBus_(std::make_shared<EventBus>())
   , input_(std::make_unique<Input>(eventBus_))
   , graphics_(std::make_unique<Graphics>(eventBus_)) {

   if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDL_Log("SDL_Init failed: %s", SDL_GetError());
   }

   SDL_SetAppMetadata("Hijinks Demo", "1.0.0", "mmyerspnw.hijinksdemo");

   // Subscribe to QuitEvent to stop the main loop.
   eventBus_->Subscribe<QuitEvent>([this](const QuitEvent&) {
      running_ = false;
   });

   if (!input_->Initialize() || !graphics_->Initialize()) {
      SDL_Log("Failed to initialize systems; exiting.");
      running_ = false;
   }
}

Engine::~Engine() {
   if (graphics_)
      graphics_->Shutdown();

   if (input_)
      input_->Shutdown();

   SDL_Quit();
}

void Engine::Run() {
   while (running_) {
      input_->Update();
      graphics_->Update();
      eventBus_->DispatchPending();
   }
}
