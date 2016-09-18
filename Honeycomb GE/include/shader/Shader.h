#pragma once
#ifndef SHADER_H
#define SHADER_H

class Shader {
public:
	/// Initializes the Shader instance.
	Shader();
	
	/// Default destructor.
	~Shader();

	/// Links the Shader from the specified file to this Shader instance.
	/// string file : The file path from which to read in the shader code.
	/// int type : The type of shader to be added (GL_FRAGMENT_SHADER,
	///			   GL_GEOMETRY_SHADER, GL_VERTEX_SHADER).
	void addShader(std::string file, int type);

	/// Binds the shader program so that it may be used.
	void bindProgram();

	/// After all of the shaders have been added and compiled, this links the
	/// program and validates that everything was done correctly.
	void finalizeProgram();
private:
	int programID; // "Pointer" ID to this shader program in the driver
};

#endif