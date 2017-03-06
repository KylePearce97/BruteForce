#include "BruteForceSim.h"

const double GRAV_CONST = 6.673E-11;
const double SOLAR_MASS = 1.98892e30;
const double EARTH_MASS = 5.972e24;
const double EPS = 3e4;
const double UNIVERSE_RADIUS = 1e18;
const double DEGREE_TO_RADIANS = 0.0174533;

void BruteForceSim::render(Renderer * r)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-UNIVERSE_RADIUS, UNIVERSE_RADIUS, -UNIVERSE_RADIUS, UNIVERSE_RADIUS, 0.0f, 1.0f); // Reference system of our simulation
	glColor3f(0.5, 1.0, 1.0);

	for (int i = 0; i < bodies.size(); i++) {
		glm::dvec2 p = this->bodies[i].getP0();
		this->bodies[i].render(r);
	}

	r->swap();
}

void BruteForceSim::update()
{
	//vector<Body>::iterator it = bodies.begin();
	//Brute Force for Calculating force and checks for collision
	for (int i = 0; i < this->bodies.size(); i++) {
		Body &iB = this->bodies[i];
		for (int j = 0; j < this->bodies.size(); j++) {
			Body &jB = this->bodies[j];
			if (i != j) {
				iB.calculateForce(jB);
				if (iB.checkCollision(jB)) {
					if (iB.getMass() >= jB.getMass()) {
						colBodies.push(j);
						iB.add(jB);
						iB.inelasticCollision(jB);
					}
					/*else {
						colBodies.push(j);
						//iB.add(jB);
						//iB.inelasticCollision(jB);
					}*/

				}
			}
		}
		iB.update(dt);
		iB.resetForce();
	}

	//Clear colliding Bodies from Simulation
	while (!colBodies.empty()) {
		cout << "Deleting" << endl;
		if (colBodies.top() < bodies.size())
		{
			bodies[colBodies.top()] = bodies.back();
			bodies.pop_back();
			
			//particleCount--;
		}
		colBodies.pop();
	}

	if (bodies.size() == 1)
		cout << "Last One" << endl;
}

bool BruteForceSim::pollEvents(SDL_Event e)
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

BruteForceSim::BruteForceSim()
{
}


BruteForceSim::~BruteForceSim()
{
}

void BruteForceSim::init()
{
	dt = 500;
	particleCount = 290;
	//bodies.push_back(Body(dvec2(500, 300), dvec2(0, 0), dvec2(0), 1, 10, vec3(1.0, 1.0, 1.0)));
	for (int i = 0; i < particleCount; i++)
	{
		bodies.push_back(generateBody());
	}
}

void BruteForceSim::run(Renderer * r)
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

Body BruteForceSim::generateBody()
{
	dvec2 p = dvec2(rnd(-UNIVERSE_RADIUS/2, UNIVERSE_RADIUS/2), rnd(-UNIVERSE_RADIUS/2, UNIVERSE_RADIUS/2));
	dvec2 v = dvec2(rnd(0, 0), rnd(0, 0));
	dvec2 a = dvec2(rnd(0,0), rnd(0,0));

	double maxValue = 1;
	double m = SOLAR_MASS * 10 + 1e20;
	double maxSize = maxValue * SOLAR_MASS * 10 + 1e20;
	double rad = 1e15;

	float r = m / maxSize + 0.3;
	float g = m / maxSize + 0.1;
	float b = m / maxSize + 0.3;

	vec3 c = vec3(1, 1, 1);

	return Body(p,v,a,m,rad,c);
}

void BruteForceSim::addBody(Body b)
{

}
