#include "RailCamera.h"
#include "MATHEX.h"
#include "ImGuiManager.h"

void RailCamera::Initialize() { 
	
	
	worldTransform_.Initialize();

	viewProjection_.Initialize();


	viewProjection_.farZ = 3000.0f;

	worldTransform_.translation_.y = 15.0f;

}

void RailCamera::Update()
{

	worldTransform_.UpdateMatrix();

	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	viewProjection_.UpdateMatrix();

}