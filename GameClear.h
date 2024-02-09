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

class GameClear {

public:
	GameClear();

	~GameClear();

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

	SceneType NextScene() { return SceneType::kGameClear; }

private:

	DirectXCommon* dxCommom_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd = false;

	ViewProjection viewProjection_;

	uint32_t Clear = 0;

	Sprite* GameClearSprite_ = nullptr;

	Sprite* fadeSprite_ = nullptr;
	Vector4 fadeColor = {1.0f, 1.0f, 1.0f, 1.0f};
	uint32_t fadeTextureHandle = 0u;


};
