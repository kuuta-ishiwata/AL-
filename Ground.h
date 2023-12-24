#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"


class Ground {

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewprojection_);

private:

	WorldTransform worldtransform_;

	Model* model_ = nullptr;



};
