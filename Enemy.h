#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "BaseCharacter.h"
#include <vector>

#include <list>

//GameSceneの前方宣言

class GameScene;

class Enemy : public BaseCharacter{


public:
	Vector3 GetWorldPosition();

	
	void SetViewProjection(const ViewProjection* viewprojection) {
		viewprojection_ = viewprojection;
	}

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;
	// 敵死ぬ
	bool IsDead() const { return isDead_; }

	void GetViewProjection(const ViewProjection* viewProjection) {
		viewprojection_ = viewProjection;
	}
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

private:

	// ワールド変換データ
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	// カメラのビュープロジェクション
	const ViewProjection* viewprojection_ = nullptr;

	// 3Dモデル
	Model* enemyFighterBody_ = nullptr;
	Model* enemyFighterL_arm_ = nullptr;
	Model* enemyFighterR_arm_ = nullptr;

	bool isDead_ = false;

	
	GameScene* gameScene_ = nullptr;

};
