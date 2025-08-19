/**
 * Engine.hpp
 *
 * The Engine class is the main driver of all systems. It handles their
 * initialization, updates, and shutdown events.
 *
 * Copyright (c) 2025 Mike Myers
 */
#pragma once

#include <memory>

namespace Hijinks {
   // Forward declarations
   class EventBus;
   class Input;
   class Graphics;

   class Engine {
   public:
      Engine();
      ~Engine();

      Engine(const Engine&) = delete;
      Engine& operator=(const Engine&) = delete;
      Engine(Engine&&) noexcept = default;
      Engine& operator=(Engine&&) noexcept = default;

      void Run();

   private:
      bool running_ = true;

      std::shared_ptr<EventBus> eventBus_;
      std::unique_ptr<Input>    input_;
      std::unique_ptr<Graphics> graphics_;
   };
}
