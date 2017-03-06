#pragma once
#include <SDL.h>
#include <glew.h>
#include <vector>
#include <stack>;
#include <iostream>
#include "Simulation.h"
#include "Body.h"

using namespace std;

class ThreeBody :
	public Simulation
{
private:
	void render(Renderer *r);
	void update();
	bool pollEvents(SDL_Event e);
	vector<Body> bodies;
	stack <int> colBodies;
	double dt;
public:
	ThreeBody();
	virtual ~ThreeBody();
	void init();
	void run(Renderer *r);
};

