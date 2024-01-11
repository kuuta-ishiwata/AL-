#pragma once
#include"Audio.h"
#include"DirectXCommon.h"
#include"Input.h"
#include"Model.h"
#include"Sprite.h"
#include"ViewProjection.h"
#include"WorldTransform.h"
#include "Scene.h"


class Title {

	///< summary>
	/// コンストラクタ
	///< summary>
	Title();

	///< summary>
	/// デストラクタ
	///< summary>
	~Title();

	///< summary>
	/// 初期化
	///< summary>
	void Initialize();

	//////<summary>
	/// 毎フレーム
	///< summary>
	void Update();

	///< summary>
	/// 描画
	///< summary>

	void Draw();

	void Reset();

	bool IsSceneEnd() { return isSceneEnd; }

	SceneType NextScene() { return SceneType::kGamePlay; }
	SceneType NextScene2() { return SceneType::kTitle; }


private: 
	DirectXCommon* dxCommom_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd = false;
	bool isSceneEnd2 = false;

	Title* titleScene = nullptr;
	Title* sceneNo = nullptr;

	bool isDead = false;

	ViewProjection viewProjection_;

	uint32_t Start = 0;
	uint32_t end = 0;

	Sprite* Sprite_ = nullptr;
	Sprite* GameoverSprite_ = nullptr;




};
