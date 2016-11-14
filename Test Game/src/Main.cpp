#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "..\..\Honeycomb GE\include\base\BaseMain.h"
#include "..\include\HoneycombTest.h"

using namespace Honeycomb::Base::BaseMain;
using Honeycomb::Base::BaseGame;

using HoneycombTest::TestGame;

#include "..\..\Honeycomb GE\include\conjuncture\Event.h"
#include "..\..\Honeycomb GE\include\conjuncture\EventHandler.h"
using Honeycomb::Conjuncture::Event;
using Honeycomb::Conjuncture::EventHandler;

void whenEventOccurs() {
	std::cout << "An event has occured!" << std::endl;
}

void whenEventOccurs1(int j) {
	std::cout << "An event has occured! " << j << std::endl;
}

void whenEventOccurs2(int j, int k) {
	std::cout << "An event has occured! " << (j + k) << std::endl;
}

int main(int argc, char** argv) {
	/*
	Event myEvent;
	EventHandler callWhenEventOccurs;

	callWhenEventOccurs.addAction(whenEventOccurs);
	callWhenEventOccurs.addAction(std::bind(whenEventOccurs1, 7));
	callWhenEventOccurs.addAction(std::bind(whenEventOccurs2, 7, 11));
	myEvent.addEventHandler(&callWhenEventOccurs);
	myEvent.onEvent();
	*/

	TestGame *game = new TestGame(); // Initialize a test game to run

	Honeycomb::Base::BaseMain::start(game);
	Honeycomb::Base::BaseMain::run();
	Honeycomb::Base::BaseMain::stop();

	return 0;
}