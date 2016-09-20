#pragma once
#ifndef GAME_H
#define GAME_H

namespace Honeycomb::Mesh { class Mesh; }
namespace Honeycomb::Shader { class Shader; }

namespace Honeycomb::Base {
	class Game {
	public:
		Game();
		
		~Game();

		void input();

		void render();

		void update();

	private:
		Honeycomb::Mesh::Mesh* testMesh;
		Honeycomb::Shader::Shader* testShader;
	};
}

#endif