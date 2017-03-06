#include "SDLRenderer.h"
#include "ThreeBody.h"
#include"BruteForceSim.h"
int main(int argc, char *argv[])
{
	SDLRenderer renderer;
	renderer.init();
	BruteForceSim sim;
	sim.run(&renderer);
	renderer.destroy();
	return 0;
}