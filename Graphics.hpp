/**
 * Graphics.hpp	
 * 
 * The Graphics class implements the ISystem interface to provide
 * rendering capabilities. It manages initialization of the graphics
 * subsystem, per-frame rendering updates, and proper shutdown of
 * graphics resources.
 *
 * Copyright (c) 2025 Mike Myers
 */
#include "ISystem.hpp"

 // Forward declaration of SDL types
class SDL_Window;
class SDL_Renderer;

class Graphics : public ISystem{
public:
	bool Initialize() override;
	void Update() override;
	void Shutdown() override;

private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
};
