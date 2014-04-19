#pragma once
#include "Mesh.h"
class PlaneMesh :
	public Mesh
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	protected:
		float width; 
		float height; 
		int columns;
		int rows;
		D3DCOLOR color;
	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		PlaneMesh(math::Vector3D position, std::string shaderTechnique, float width, float height, int columns, int rows, D3DCOLOR color);
		~PlaneMesh();

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		void GenerateMesh();
		virtual void GenerateVertexes(float initial_x, float diff_x, float initial_z, float diff_z);
};

