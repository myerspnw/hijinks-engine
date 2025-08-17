/**
 * Graphics.cpp
 * 
 * This file contains the implementation of the Graphics class, which provides methods
 * for rendering shapes and text on a graphical surface.
 * 
 * Copyright(c) 2025 Mike Myers
 */

#include "Graphics.hpp"

#include <SDL3/SDL.h>

bool Graphics::Initialize() {
	bool success = true;

	SDL_InitSubSystem(SDL_INIT_VIDEO);

	// Create the main window and renderer.
	if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, SDL_WINDOW_FULLSCREEN, &window_, &renderer_)) {
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
		success = false;
	}

	return success;
}

void Graphics::Update() {
}

void Graphics::Shutdown() {
	// Clean up the renderer and window.
	if (renderer_) {
		SDL_DestroyRenderer(renderer_);
		renderer_ = nullptr;
	}
	if (window_) {
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
