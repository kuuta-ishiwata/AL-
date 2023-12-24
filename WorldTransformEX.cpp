#include "MATHEX.h"
#include "WorldTransform.h"

void WorldTransform::UpdateMatrix()
{
	//スケール、回転、平行行列を合成して計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	if (parent_)
	{

		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
		TransferMatrix();
	}

}