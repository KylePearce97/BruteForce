#pragma once
#include "Renderer.h"
class Simulation
{
public:
	Simulation() {};
	virtual~Simulation() {};
	virtual void init() = 0;
	virtual void run(Renderer *r) = 0;
private:
	virtual void render(Renderer *r) = 0;
	virtual void update() = 0;

};
