/**
 * ISystem.hpp
 *
 * The ISystem class defines a common contract for systems that participate
 * in the application lifecycle. Systems are expected to implement at least
 * the Update function, while optionally overriding initialization and
 * shutdown behavior.
 *
 * Typical usage:
 * - Create a class deriving from ISystem.
 * - Override Initialize to set up resources (optional).
 * - Override Update to perform per-frame work (required).
 * - Override Shutdown to release resources (optional).
 *
 * Copyright (c) 2025 Mike Myers
 */
class ISystem {
public:
	virtual ~ISystem() = default;

	virtual bool Initialize() {};
	virtual void Update() = 0;
	virtual void Shutdown() {};
};
