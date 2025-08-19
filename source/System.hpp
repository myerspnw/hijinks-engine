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
      virtual void Update() = 0;
      virtual void Shutdown() {}

   protected:
      std::shared_ptr<EventBus> eventBus_;
   };
}

