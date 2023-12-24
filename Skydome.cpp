#include "Skydome.h"
#include <assert.h>


void Skydome::Initialize(Model* model)
{

	assert(model);

	model_ = model;
	
	workdtransform_.Initialize();

	workdtransform_.scale_ = {10.0f, 10.0f, 10.0f};


}

void Skydome::Update() { 
	
	workdtransform_.UpdateMatrix();

}

void Skydome::Draw(ViewProjection& viewprojection_)
{

	model_->Draw(workdtransform_, viewprojection_);

}