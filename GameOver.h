#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "TextureManager.h"



class GameOver {

	public:
	///< summary>
	/// コンストラクタ
	///< summary>
	GameOver();

	///< summary>
	/// デストラクタ
	///< summary>
	~GameOver();

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

	// 次のシーン
	SceneType NextScene() { return SceneType::kGameOver; }


private: // メンバ変数
	DirectXCommon* dxCommom_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd = false;

	bool isDead = false;

	ViewProjection viewProjection_;

	uint32_t end = 0;

	Sprite* GameoverSprite_ = nullptr;


};
