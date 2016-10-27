//================================================================
//                     Camera3D.hpp
//================================================================

#pragma once
#ifndef  __included_CAMERA3D__
#define  __included_CAMERA3D__
#include <math.h>
#include "Engine/Math/3D/EulerAngles.hpp"
#include "Engine/Math/3D/Matrix4x4.hpp"
#include "Engine\Input\InputSystem.hpp"
class Camera3D
{
public: 
	void InitializeCamera(float initialRoll_X, float initialPitch_Y, float intialYaw_Z, InputSystem* inputSystem = nullptr);
	void UpdateCamera(double deltaSecond);
	const Vector3 GetForwardVector() const;
	void CreateViewMatrix(Matrix4x4& mOut);
	void CreateProjPers(Matrix4x4& m, float fovDegreesVertical, float aspect, float zNearDist, float zFarDist);
	Matrix4x4 CreateOrthoMatrix( float screenWidth, float screenHeight, float zFar, float zNear);


	Vector3 m_worldPosition;
	EulerAngles m_orientation;

	Matrix4x4 m_viewMatrix;
	Matrix4x4 m_orthoMatrix;
	Matrix4x4 m_projPersMatrix;
	InputSystem* m_inputSystem;
};

extern Camera3D* g_masterCamera;
#endif