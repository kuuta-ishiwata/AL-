#pragma once
#include"Audio.h"
#include"DirectXCommon.h"
#include"Input.h"
#include"Sprite.h"
#include"ViewProjection.h"
#include"WorldTransform.h"
#include "Scene.h"
#include "TextureManager.h"
class Title {


	public:
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

	bool IsSceneEnd() { return isSceneEnd; }

	SceneType NextScene() { return SceneType::kGamePlay; }
	SceneType NextScene2() { return SceneType::kTitle; }

	void Reset();



private:
	DirectXCommon* dxCommom_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd = false;
	bool isSceneEnd2 = false;
	// bool isSceneEndGamePlay = false;



	bool isDead = false;

	ViewProjection viewProjection_;

	uint32_t Start = 0;
	uint32_t end = 0;

	Sprite* Sprite_ = nullptr;
	Sprite* GameoverSprite_ = nullptr;




};
