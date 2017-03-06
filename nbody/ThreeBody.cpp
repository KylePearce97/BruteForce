#include "ThreeBody.h"



void ThreeBody::render(Renderer * r)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-2000, 2000, -2000, 2000, 0.0f, 1.0f); // Reference system of our simulation
	glColor3f(0.5, 1.0, 1.0);

	for (int i = 0; i < bodies.size(); i++) {
		glm::dvec2 p = this->bodies[i].getP0();
		this->bodies[i].render(r);
	}

	r->swap();
}

void ThreeBody::update()
{
	//Brute Force for Calculating force and checks for collision
	for (int i = 0; i < bodies.size(); i++) {
		Body &iB = this->bodies[i];
		for (int j = 0; j < bodies.size(); j++) {
			Body &jB = this->bodies[j];
			if (i != j) {
				iB.calculateForce(jB);
				if (iB.checkCollision(jB)) {
					cout << i << " is colliding with " << j << endl;
					if (iB.getMass() > jB.getMass()) {
						colBodies.push(j);
						iB.add(jB);
						iB.inelasticCollision(jB);
					}
					else if(iB.getMass() < jB.getMass()) {
						colBodies.push(i);
						jB.add(iB);
						jB.inelasticCollision(iB);
					}
					else {
						if (i < j) {
							colBodies.push(j);
							iB.add(jB);
							iB.inelasticCollision(jB);
						}
						else {
							colBodies.push(i);
							jB.add(iB);
							jB.inelasticCollision(iB);
						}
					}
						
				}
			}
		}
		iB.update(dt);
		iB.resetForce(); 
	}

	//Clear colliding Bodies from Simulation
	while (!colBodies.empty()) {
		bodies.erase(bodies.begin() + colBodies.top());
		colBodies.pop();
	}
}

bool ThreeBody::pollEvents(SDL_Event e)
{
	if (e.type == SDL_QUIT)
		return false;
	if (e.type == SDL_KEYDOWN)
	{
		// Can extend this to handle a wider range of keys
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return false;
		default:
			break;
		}
	}

	return true;
}

ThreeBody::ThreeBody()
{
}


ThreeBody::~ThreeBody()
{
}

void ThreeBody::init()
{
	dt = 1e4;
	bodies.push_back(Body(dvec2(500,300), dvec2(0,0), dvec2(0), 1, 10, vec3(1.0,1.0,1.0)));
	bodies.push_back(Body(dvec2(500, -500), dvec2(-0,0), dvec2(0), 1, 10, vec3(0.0, 1.0, 1.0)));
	bodies.push_back(Body(dvec2(-500, 500), dvec2(0), dvec2(0), 1, 10, vec3(1.0, 0.0, 0.0)));
}

void ThreeBody::run(Renderer * r)
{
	SDL_Event e;
	this->init();
	bool running = true;
	while (running) {
		SDL_PollEvent(&e);
		running = this->pollEvents(e);
		this->update();
		this->render(r);
	}
}
