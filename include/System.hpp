/**
 * System.hpp
 *
 * The System base class defines a common contract for systems that participate
 * in the application lifecycle.
 *
 * Copyright (c) 2025 Mike Myers
 */
#pragma once

#include <memory>
#include <utility>

namespace Hijinks {
   class EventBus;

   class System {
   public:
      explicit System(std::shared_ptr<EventBus> eventBus)
         : eventBus_(std::move(eventBus)) {
      }

      virtual ~System() = default;

      [[nodiscard]] virtual bool Initialize() { return true; }

      // Deterministic simulation step (e.g., physics, game logic) at a fixed dt.
      virtual void FixedUpdate(double /*dt*/) {}

      // Per-frame update (e.g., input polling, rendering).
      virtual void Update(double dt) {};

      virtual void Shutdown() {}

   protected:
      std::shared_ptr<EventBus> eventBus_;
   };
}

