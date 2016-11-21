#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "..\..\Honeycomb GE\include\base\BaseMain.h"
#include "..\include\HoneycombTest.h"

using namespace Honeycomb::Base::BaseMain;
using Honeycomb::Base::BaseGame;

using HoneycombTest::TestGame;

int main(int argc, char** argv) {
	TestGame *game = new TestGame(); // Initialize a test game to run

	Honeycomb::Base::BaseMain::start(game);
	Honeycomb::Base::BaseMain::run();
	Honeycomb::Base::BaseMain::stop();

	return 0;
}