#pragma once
#include <SDL.h>
#include <glew.h>
#include <iostream>
#include "Renderer.h"
class SDLRenderer :
	public Renderer
{
private:
	SDL_GLContext glContext;
	SDL_Window *window;

	SDL_Window *setup(SDL_GLContext &context);
public:
	SDLRenderer();
	virtual ~SDLRenderer();
	void init();
	void renderCircle(glm::dvec3 pos, double radius, int numPoints, glm::vec3 color);
	void swap();
	void destroy();
};

