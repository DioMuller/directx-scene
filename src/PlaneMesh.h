#pragma once
#include "Mesh.h"
class PlaneMesh :
	public Mesh
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	private:
		float width; 
		float height; 
		int columns;
		int rows;
	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		PlaneMesh(math::Vector3D position, std::string shaderTechnique, float width, float height, int columns, int rows);
		~PlaneMesh();

	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		void GenerateMesh();
};

