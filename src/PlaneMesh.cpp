#include "PlaneMesh.h"


PlaneMesh::PlaneMesh(math::Vector3D position, std::string shaderTechnique, float width, float height, int columns, int rows, D3DCOLOR color) : Mesh(position, shaderTechnique)
{
	this->width = width;
	this->height = height;
	this->columns = columns;
	this->rows = rows;
	this->color = color;
}


PlaneMesh::~PlaneMesh()
{
}

void PlaneMesh::GenerateMesh()
{
	// Distance difference between each vertex (x and Z)
	float diff_x = width / (float)columns;
	float diff_z = height / (float)rows;

	// Initial position where the mesh will be drawn. 
	float initial_x = -(width / 2);
	float initial_z = -(height / 2);

	// Vertex count
	vertexCount = columns * rows;

	// Triangle count
	triangleCount = 0;

	// Create vertexes
	GenerateVertexes(initial_x, diff_x, initial_z, diff_z);

	// Create indexes
	for (int i = 0; i < rows - 1; ++i) // -1 because each triangle uses 2 rows.
	{
		for (int j = 0; j < columns - 1; ++j) // -1 because each triangle uses 2 columns.
		{
			// First Triangle
			// 1 2
			// 3
			indexes.push_back((DWORD)(i * columns + j));
			indexes.push_back((DWORD)(i * columns + j + 1));
			indexes.push_back((DWORD)((i + 1) * columns + j));
			triangleCount++;

			// Second triangle
			//   2
			// 1 3
			indexes.push_back((DWORD)((i + 1) * columns + j));
			indexes.push_back((DWORD)(i * columns + j + 1));
			indexes.push_back((DWORD)((i + 1) * columns + j + 1));
			triangleCount++;
		}
	}

	indexCount = indexes.size();
}

void PlaneMesh::GenerateVertexes(float initial_x, float diff_x, float initial_z, float diff_z)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			vertexes.push_back({ D3DXVECTOR3(initial_x + i * diff_x, 0.0f, initial_z + j * diff_z), color, D3DXVECTOR2(0, 0) });
		}
	}
}