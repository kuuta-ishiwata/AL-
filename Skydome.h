#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Skydome {

public:

	//<summary>
	//初期化
	//<summary>
	void Initialize(Model* model);


	//<summary>
	// 更新
	//<summary>
	void Update();

	//<summary>
	// 更新
	//<summary>
	void Draw(ViewProjection& viewprojection_);





private:

	//ワールド行列変更データ
	WorldTransform workdtransform_;

	//モデル
	Model* model_ = nullptr;



};
