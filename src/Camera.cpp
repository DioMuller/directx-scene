#include "Camera.h"
#include "mage/GameWindow.h"
#include "mage/HandleError.h"

////////////////////////////////////
// Constructors
////////////////////////////////////
Camera::Camera(float verticalFov, float nearDistance, float farDistance, float distanceFromCamera, float cameraHeight)
{
	this->verticalFov = verticalFov;
	this->nearDistance = nearDistance;
	this->farDistance = farDistance;

	this->eye = math::Vector3D(0.0f, cameraHeight, distanceFromCamera);
	this->at = math::Vector3D(0.0f, 0.0f, 0.0f);
	this->up = math::Vector3D(0.0f, 1.0f, 0.0f);
}


Camera::~Camera()
{
}

////////////////////////////////////
// Methods
////////////////////////////////////
void Camera::UpdateView(ID3DXEffect* shader)
{
	// World Transform (We just "reset" the world, in case any of the meshes isn't using the world transform)
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	// Projection transform
	D3DXMATRIX projection;     // the projection transform matrix
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(verticalFov),
		mage::GameWindow::get().getAspect(), 
		nearDistance, farDistance);

	// View transform
	D3DXMATRIX view;
	//D3DXMatrixIdentity(&view);	
	D3DXMatrixLookAtLH(&view,
		&D3DXVECTOR3(eye.x, eye.y, eye.z), // Eye - Camera Position
		&D3DXVECTOR3(at.x, at.y, at.z),  // At - Position the camera is looking at.
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)); // Up - Direction of the top of the world.


	// Set shader properties.
	D3DXHANDLE hWorld = shader->GetParameterByName(0, "World");
	HR(shader->SetMatrix(hWorld, &world));

	D3DXHANDLE hProjection = shader->GetParameterByName(0, "Projection");
	HR(shader->SetMatrix(hProjection, &projection));

	D3DXHANDLE hView = shader->GetParameterByName(0, "View");
	HR(shader->SetMatrix(hView, &view));
}