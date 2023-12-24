#pragma once
#include "ImGuiManager.h"
#include "Model.h"
#include "WorldTransform.h"
#include "FollowCamera.h"

class RailCamera {

public:


	void Initialize();

	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }


private:

	WorldTransform worldTransform_;

	ViewProjection viewProjection_;


};
