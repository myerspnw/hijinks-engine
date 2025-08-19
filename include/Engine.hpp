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
#include <vector>

#include "System.hpp"
#include "EventBus.hpp"

#ifdef HIJINKS_ENGINE_EXPORTS
#define HIJINKS_API __declspec(dllexport)
#else
#define HIJINKS_API __declspec(dllimport)
#endif

namespace Hijinks {
   // Forward declarations
   class Input;
   class Graphics;

   class HIJINKS_API Engine {
   public:
      Engine();
      ~Engine();

      Engine(const Engine&) = delete;
      Engine& operator=(const Engine&) = delete;
      Engine(Engine&&) noexcept = default;
      Engine& operator=(Engine&&) noexcept = default;

      void Run();

      // Expose bus to external modules if needed
      std::shared_ptr<EventBus> bus() const noexcept { return eventBus_; }

      // Register a custom system owned and updated by the engine.
      template<class T, class... Args>
      T& AddSystem(Args&&... args) {
         static_assert(std::is_base_of_v<System, T>, "T must derive from System");

         auto ptr = std::make_unique<T>(eventBus_, std::forward<Args>(args)...);
         T& ref = *ptr;
         if (!ptr->Initialize()) {
            running_ = false; // or throw
         }
         externalSystems_.push_back(std::move(ptr));
         return ref;
      }

   private:
      bool running_ = true;

      std::shared_ptr<EventBus> eventBus_;
      std::unique_ptr<Input>    input_;
      std::unique_ptr<Graphics> graphics_;
      std::vector<std::unique_ptr<System>> externalSystems_;
   };
}
