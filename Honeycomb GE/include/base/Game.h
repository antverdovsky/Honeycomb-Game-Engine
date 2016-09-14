#pragma once
#ifndef GAME_H
#define GAME_H

class Game {
public:
	Game();
	~Game();

	void input();

	void render();

	void update();
};

#endif