#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>
#include  "DebugCamera.h"
#include "FollowCamera.h"
#include "Model.h"
#include "BaseCharacter.h"
#include "Skydome.h"
#include "Ground.h"
#include "Player.h"
#include "MATHEX.h"
#include "Enemy.h"
#include "Scene.h"
#include "GameOver.h"
#include "Title.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	
	// 敵発生関数
	/// </summary>

	void EnemyPop(Vector3 pos);
	void LoadEnemyPopData();
	void UpdateEnemyPopCommands();
	Vector3 GetEnemyPopPos() { return enemyPopPos; }
	void SetEnemyPopPos(Vector3 pos) { enemyPopPos = pos; }

	// 衝突判定
	void CheckAllCollisions();

	  void Restart();
	  
	  void Reset();
	  void Reset2();
	  bool IsSceneEnd() { return isSceneEnd; }
	  bool IsSceneEnd2() { return isSceneEnd2; }
	  
	  SceneType NextScene() {
	  
	  	// ゲームクリアとゲームオーバーどっちかに行く可能性があるので
	  	// if文で戻り値を変える
	  
	  	if (isSceneEnd == true) {
	  
	  		return SceneType::kGameOver;
	  	}
	  
	  	if (isSceneEnd2 == true) {
	  
	  		return SceneType::kGameClear;
	  	}
	  }

	
private: 


	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// 
	

	Model* model_;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;


	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	// デバッグカメラ
	bool isDebugCameraActive_ = false;

	// フォローカメラ
	std::unique_ptr<FollowCamera> followCamera_;

	// 天球
	std::unique_ptr<Skydome> skydome_;

	std::unique_ptr<Model> skydomeModel_;

	// グラウンド
	std::unique_ptr<Ground> ground_;

	std::unique_ptr<Model> groundModel_;

	std::unique_ptr<Player> player_;

	

	// 3Dモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;


	// 敵キャラ
	std::list<std::unique_ptr<Enemy>> enemies;
	//  エネミーモデルデータ
	std::unique_ptr<Model> modelEnemy_;
	// エネミーモデル
	std::unique_ptr<Model> enemyFighterBody_;
	std::unique_ptr<Model> enemyFighterHead_;
	std::unique_ptr<Model> enemyFighterL_arm_;
	std::unique_ptr<Model> enemyFighterR_arm_;

	//武器モデル
	//std::unique_ptr<Model> modelWeapon_;

	bool isWait = true;

	// 待機タイマ
	int32_t waitTimer = 0;
	std::stringstream enemyPopCommands;
	Vector3 enemyPopPos = {};


	bool isSceneEnd = false;
	bool isSceneEndGameClear = false;
	bool isSceneEndGameOver = false;

	bool isSceneEnd2 = false;
	Sprite* GameoverSprite_ = nullptr;

	Player* Restartplayer = nullptr;

	uint32_t count = 0;
	uint32_t count2 = 0;

	Enemy* enemy_ = nullptr;

	

};
