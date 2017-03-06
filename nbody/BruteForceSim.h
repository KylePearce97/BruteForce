#pragma once
#include <SDL.h>
#include <glew.h>
#include <vector>
#include <stack>;
#include <iostream>
#include "Simulation.h"
#include "Body.h"
#include "Rnd.h"

using namespace std;
class BruteForceSim :
	public Simulation
{
private:
	void render(Renderer *r);
	void update();
	bool pollEvents(SDL_Event e);
	vector<Body> bodies;
	stack <int> colBodies;
	double dt;
	int particleCount;
public:
	BruteForceSim();
	virtual ~BruteForceSim();
	void init();
	Body generateBody();
	void addBody(Body b);
	void run(Renderer *r);
};

