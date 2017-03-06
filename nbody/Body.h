#pragma once
#include <iostream>
#include <glm.hpp>
#include "Renderer.h"
using namespace glm;
class Body
{
public:
	Body();
	Body(dvec2 p, dvec2 v, dvec2 a, double m, double r, vec3 c);
	virtual ~Body();
	void calculateForce(Body b);
	void verlettStep(double dt);
	void update(double dt);
	void resetForce();
	void render(Renderer *r);
	bool checkCollision(Body b);
	void inelasticCollision(Body b);
	void add(Body b);
	dvec2 getP0();
	dvec2 getP1();
	double getMass();
	double getRadius();
	vec3 getColor();
	dvec2 getCurrentAccleration();
	
	double GRAV_CONST = 6.673E-11; //Gravity Constant
	double EPS = 1; //Damapener to avoid infinites
private:
	dvec2 p0, p1; //Positions
	dvec2 v0, v1; //Velocity
	dvec2 a0, a1; //Acceleration
	dvec2 ta; //Total Accleration (Force)
	double mass;
	double radius;
	vec3 color;

};