#include "Scene.h"

Mesh Scene::createPlaneMesh(float width, float height, int columns, int rows)
{
	Mesh result;

	float diff_x = width / (float) columns;
	float diff_y = height / (float)rows;

	float initial_x = -(width / 2);
	float initial_y = -(height / 2);

	result.verticeCount = columns * rows;

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			result.vertices.push_back({ D3DXVECTOR3(initial_x + i * diff_x, initial_y + j * diff_y, 0.0f), D3DCOLOR_XRGB(255, 255, 255) });
		}
	}

	return result;
}