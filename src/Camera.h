#pragma once
#include <d3dx9.h>
#include "math/Vector3D.h"

class Camera
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	private:
		float nearDistance;
		float farDistance;
		float verticalFov;
		math::Vector3D eye;
		math::Vector3D at;
		math::Vector3D up;

	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		Camera(float verticalFov, float nearDistance, float farDistance, float distanceFromCamera, float cameraHeight);
		~Camera();

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		void UpdateView(ID3DXEffect* shader);
};
