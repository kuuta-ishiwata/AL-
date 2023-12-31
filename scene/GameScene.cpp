#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <fstream>
#include <iostream>
#include <map>
#include <variant>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::CheckAllCollisions() 
{
	//対象Aと対象Bの座標
	Vector3 posA, posB;
	posA = player_->GetWorldPosition();
   

	//自キャラ武器と敵キャラのあたり判定
	for (std::unique_ptr<Enemy>& enemy : enemies)
	{
		posB = enemy->GetWorldPosition();




	}
	



}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	viewProjection_.farZ = 1400.0f;

	skydomeModel_.reset(Model::CreateFromOBJ("skydome", true));

	skydome_ = std::make_unique<Skydome>();

	skydome_->Initialize(skydomeModel_.get());

	// グラウンド
	groundModel_.reset(Model::CreateFromOBJ("ground", true));

	// グラウンド
	ground_ = std::make_unique<Ground>();

	ground_->Initialize(groundModel_.get());


	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));
	modelWeapon_.reset(Model::CreateFromOBJ("hammer", true));
	
	// 自キャラモデル
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(), modelWeapon_.get()};

	player_ = std::make_unique<Player>();

	player_->Initialize(playerModels);


	

	// 敵のモデル
	enemyFighterBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	enemyFighterL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	enemyFighterR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));

	// 敵のモデル
	//std::vector<Model*> enemyModels = {
	//    enemyFighterBody_.get(), enemyFighterL_arm_.get(), enemyFighterR_arm_.get()};
	//
	//// 敵の生成
	//enemies = std::make_unique<Enemy>();
	//
	//// 敵の初期化
	//enemies->Initialize(enemyModels);

	LoadEnemyPopData();

	UpdateEnemyPopCommands();

	

	// フォローカメラ
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();

	//// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	player_->SetViewProjection(&followCamera_->GetViewProjection());

	
	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {

	worldTransform_.TransferMatrix();
	viewProjection_.UpdateMatrix();

	if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;

	} else if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}

	// カメラ処理
	if (isDebugCameraActive_) {
		// followCamera_->Update();

		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// viewProjection_.matView = followCamera_->GetViewProjection().matView;
		// viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

	} 
	else {

		// 追従カメラの更新
		// debugCamera_->Update();

		followCamera_->Update();

		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		// viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		// viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の更新と転送
		viewProjection_.TransferMatrix();
	}

	// 天球
	skydome_->Update();

	// グラウンド
	ground_->Update();

	//player
	player_->Update();

	//enemy
	//enemies->Update();
	//  敵の発生と更新
	UpdateEnemyPopCommands();
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->Update();
	}
	// デスフラグの立った敵を削除
	enemies.remove_if([](std::unique_ptr<Enemy>& enemy) {
		if (enemy->IsDead()) {
			delete enemy.release();
			return true;
		}
		return false;
	});

	worldTransform_.UpdateMatrix();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	ground_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

	player_->Draw(viewProjection_);

	//enemies->Draw(viewProjection_);

	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::LoadEnemyPopData()
{

	// ファイルを開く
	std::ifstream file;
	file.open("./Resources/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
	
	
}

void GameScene::UpdateEnemyPopCommands()
{
	if (isWait)
	{
		waitTimer--;
		if (waitTimer <= 0)
		{
			isWait = false;

		}
		return;
    }
	std::string line;
	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行文分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// X座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// Y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// Z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			EnemyPop(Vector3(x, y, z));
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			isWait = true;
			waitTimer = waitTime;

			// コマンドループを抜ける
			break; // 重要
		}
	}



}

void GameScene::EnemyPop(Vector3 pos)
{
	//敵キャラ初期化
	std::vector<Model*> enemyModels = { 
		modelFighterBody_.get(),
	    modelFighterBody_.get(),
	    modelFighterBody_.get(),
	    modelFighterBody_.get(),

	};

	//敵の生成
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();

	//初期化
	newEnemy->Initialize(enemyModels);
	
	//リストに敵を登録
	enemies.push_back(std::move(newEnemy));

	//イテレータ
	for (std::unique_ptr<Enemy>& enemy : enemies)
	{

		//各セッターに値を代入
		SetEnemyPopPos(pos);
		enemy->GetViewProjection(&followCamera_->GetViewProjection());
		enemy->SetGameScene(this);

		//更新
		enemy->Update();



	}


}