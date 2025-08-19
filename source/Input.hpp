/**
 * Input.hpp
 *
 * The Input system processes OS/window events (via SDL) and publishes
 * engine-level events to the EventBus.
 *
 * Copyright (c) 2025 Mike Myers
 */
#pragma once

#include "System.hpp"

namespace Hijinks {
   class Input final : public System {
   public:
      using System::System;

      Input() = default;
      bool Initialize() override;
      void Update() override;
      void Shutdown() override;
   };
}
