#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../../Honeycomb GE/include/base/BaseMain.h"
#include "../include/HoneycombTest.h"

using Honeycomb::Base::BaseGame;

using HoneycombTest::TestGame;

int main(int argc, char** argv) {
	TestGame game; // Initialize a test game to run

	Honeycomb::Base::BaseMain::getBaseMain().runGame(game);

	return 0;
}