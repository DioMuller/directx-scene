#pragma once
#include "Mesh.h"
class CubeMesh :
	public Mesh
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	private:
		float width;
		float height;
		float depth;

	////////////////////////////////////
	// Constructor
	////////////////////////////////////
	public:
		CubeMesh(math::Vector3D position, std::string shaderTechnique, float width, float height, float depth);
		~CubeMesh();

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		void GenerateMesh();
};

