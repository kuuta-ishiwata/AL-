﻿#pragma once
#include "Input.h"
#include "MATHEX.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class FollowCamera {
public:

	void Initialize();

	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	const ViewProjection& GetViewProjection() { return viewProjection_; }

private:


	ViewProjection viewProjection_;

	const WorldTransform* target_ = nullptr;

};
