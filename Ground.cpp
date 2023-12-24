#include "Ground.h"
#include <assert.h>

void Ground::Initialize(Model* model) {


	assert(model);
	model_ = model;

	worldtransform_.Initialize();

	worldtransform_.scale_ = {100.0f, 100.0f, 100.0f};
}

void Ground::Update() { worldtransform_.UpdateMatrix(); }

void Ground::Draw(ViewProjection& viewprojection_) {

	model_->Draw(worldtransform_, viewprojection_);

}
