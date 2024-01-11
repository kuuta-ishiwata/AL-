#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include "Input.h"
#include "BaseCharacter.h"
#include <optional>
#include "Enemy.h"



class Player : public BaseCharacter {


public:

	Player();
	~Player();


	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransform() { return worldTransformBase_; }

	void SetViewProjection(const ViewProjection* viewprojection) {
		viewProjection_ = viewprojection;
	}

	void Initialize(const std::vector<Model*>& playermodels) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;

	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();
	// 浮遊ギミック更新
	void UpdateFloatingGimmick();

	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	// 通常行動初期化
	void BehaviorRootInitialize();
	// 通常行動更新
	void BehaviorRootUpdate();


	// 攻撃行動初期化
	//void BehaviorAttackInitialize();
	// 攻撃行動更新
	//void BehaviorAttackUpdate();

	//ジャンプ初期化
	void BehaviorJumpInitialize();

	//ジャンプ更新
	void BehaviorJumpUpdate();

	// 振る舞い
	enum class Behavior {
		kRoot,  // 通常攻撃
		//kAttack // 攻撃中
		jump
	};

	// 振る舞い
	Behavior behavior_ = Behavior::jump;

	std::optional<Behavior> behaviorRequest_ = std::nullopt;


	void OnCollision();



private:

	// 武器モデル
	//WorldTransform worldTransformWeapon_;

    WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	// 3Dモデル
	Model* modelFighterBody_ = nullptr;
	Model* modelFighterHead_ = nullptr;
	Model* modelFighterL_arm_ = nullptr;
	Model* modelFighterR_arm_ = nullptr;

	Model* playerModel_ = nullptr;


	Input* input_ = nullptr;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	bool isDead_ = false;

	Vector3 velocity_ = {};

};


