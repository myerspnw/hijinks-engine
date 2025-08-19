/**
 * Engine.cpp
 *
 * Implementation of the Engine class
 * 
 * Copyright (c) 2025 Mike Myers
 */
#include "Engine.hpp"

#include <SDL3/SDL.h>
#include <chrono>

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
   // Shutdown external systems in reverse order
   for (auto it = externalSystems_.rbegin(); it != externalSystems_.rend(); ++it) {
      if (*it) (*it)->Shutdown();
   }

   if (graphics_)
      graphics_->Shutdown();

   if (input_)
      input_->Shutdown();

   SDL_Quit();
}

void Engine::Run() {
   using clock = std::chrono::steady_clock;
   const double fixed_dt = 1.0 / 60.0; // 60 Hz
   auto prev = clock::now();
   double acc = 0.0;

   while (running_) {
      auto now = clock::now();
      std::chrono::duration<double> frame = now - prev;
      prev = now;
      double frame_dt = frame.count();
      acc += frame_dt;

      // Per-frame input polling
      input_->Update(frame_dt);

      // Fixed-step simulation for custom systems
      while (acc >= fixed_dt) {
         for (auto& s : externalSystems_) s->FixedUpdate(fixed_dt);
         acc -= fixed_dt;
      }

      // Per-frame update (render etc.)
      for (auto& s : externalSystems_) s->Update(frame_dt);
      graphics_->Update(frame_dt);

      // Deliver queued events
      eventBus_->DispatchPending();
   }
}

