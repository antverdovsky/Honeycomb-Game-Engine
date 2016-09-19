#pragma once
#ifndef GAME_H
#define GAME_H

class Mesh;
class Shader;

class Game {
public:
	Game();
	~Game();

	void input();

	void render();

	void update();
	
private:
	Mesh* testMesh;
	Shader* testShader;
};

#endif