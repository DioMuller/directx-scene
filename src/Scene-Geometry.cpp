#include "Scene.h"

// TODO: Change to XZ instead of XY.
Mesh Scene::createPlaneMesh(float width, float height, int columns, int rows)
{
	Mesh result;

	// Distance difference between each vertex (x and Y)
	float diff_x = width / (float) columns;
	float diff_y = height / (float) rows;

	// Initial position where the mesh will be drawn. 
	float initial_x = -(width / 2);
	float initial_y = -(height / 2);

	// Vertex count
	result.vertexCount = columns * rows;

	// Create vertexes
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			result.vertexes.push_back({ D3DXVECTOR3(initial_x + i * diff_x, initial_y + j * diff_y, 0.0f), D3DCOLOR_XRGB(255, 255, 255) });
		}
	}

	// Create indexes
	for (int i = 0; i < rows - 1; ++i) // -1 because each triangle uses 2 rows.
	{
		for (int j = 0; j < columns - 1; ++j) // -1 because each triangle uses 2 columns.
		{
			// First Triangle
			// 1 2
			// 3
			result.indexes.push_back( (DWORD) (i * columns + j));
			result.indexes.push_back((DWORD) (i * columns + j + 1));
			result.indexes.push_back((DWORD) ((i + 1) * columns + j));

			// Second triangle
			//   2
			// 1 3
			result.indexes.push_back((DWORD)((i + 1) * columns + j));
			result.indexes.push_back((DWORD)(i * columns + j + 1));
			result.indexes.push_back((DWORD)((i + 1) * columns + j + 1));
		}
	}


	return result;
}