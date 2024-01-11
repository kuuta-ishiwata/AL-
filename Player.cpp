#include "Player.h"
#include <cassert>
#include "MATHEX.h"
#include "ImGuiManager.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <memory>



Player::Player() {}

Player::~Player() {}





void Player::Initialize(const std::vector<Model*>& playermodels) 
{ 
	
	input_ = Input::GetInstance();

		// 基底クラスの初期化
	BaseCharacter::Initialize(playermodels);
	
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	//worldTransformWeapon_.Initialize();

	worldTransformBody_.parent_ = &worldTransformBase_;
	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;
	//worldTransformWeapon_.parent_ = &worldTransformBody_;


	// ワールドトランスフォームの初期化
	worldTransformBase_.Initialize();

	// X,Y,Z方向のスケーリングを設定
	//worldTransformBase_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBase_.translation_ = {0.0f, 0.0f, -4.0f};

	#pragma region モデルの設定

	// 腕の座標指定

	worldTransformHead_.translation_.y = 1.5f;
	worldTransformL_arm_.translation_.x = -0.5f;
	worldTransformR_arm_.translation_.x = 0.5f;
	worldTransformL_arm_.translation_.y = 1.3f;
	worldTransformR_arm_.translation_.y = 1.3f;
	
#pragma endregion


	BehaviorRootInitialize();



}


Vector3 Player::GetWorldPosition() {

	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransformBase_.matWorld_.m[3][0];
	worldPos.y = worldTransformBase_.matWorld_.m[3][1];
	worldPos.z = worldTransformBase_.matWorld_.m[3][2];

	return worldPos;
}
void Player::Update() {

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// キャラクターの移動速さ
		const float speed = 0.3f;
		// 移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};

		// 移動量に速さを反映
		move = Normalize(move);
		move = Multiply3(speed, move);

		// 回転行列
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
		// 移動ベクトルをカメラの角度だけ回転
		move = TransformNormal(move, rotateMatrix);

		// 移動
		worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, move);

		// playerのY軸周り角度(θy)
		worldTransformBase_.rotation_.y = std::atan2(move.x, move.z);
	}


	BaseCharacter::Update();

//	UpdateFloatingGimmick();

	// 行列を定数バッファに転送
	worldTransformBody_.UpdateMatrix();
	worldTransformBase_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	//worldTransformWeapon_.UpdateMatrix();


	BehaviorJumpUpdate();

}

void Player::OnCollision()
{
	isDead_ = true;

}

void Player::Draw(const ViewProjection& viewProjection) 
{
	if (isDead_ == false) {
		models_[0]->Draw(worldTransformBody_, viewProjection);
		models_[1]->Draw(worldTransformHead_, viewProjection);
		models_[2]->Draw(worldTransformL_arm_, viewProjection);
		models_[3]->Draw(worldTransformR_arm_, viewProjection);

	
	}

}



void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }

void Player::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	const uint16_t period = 120;

	// 1フレームでのパラメーター加算値
	const float step = 2.0f * (float)M_PI / period;

	// パラメーターを1ステップ分加算
	floatingParameter_ += step;

	// 2πを超えたら0に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * M_PI);

	// 浮遊の振幅<m>
	//const float floatingAmplitude = 0.5f;
	//
	//// 浮遊を座標に反映
	//worldTransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude;

	// 腕の動き
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * 0.75f;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * 0.75f;
}


void Player::BehaviorRootInitialize() {

	worldTransformL_arm_.rotation_.x = 0.0f;
	worldTransformR_arm_.rotation_.x = 0.0f;
	//worldTransformWeapon_.rotation_.x = 0.0f;

	// 浮遊初期化
	//InitializeFloatingGimmick();

	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	//worldTransformWeapon_.Initialize();
}

void Player::BehaviorRootUpdate() {
	XINPUT_STATE joyState;
	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move{
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX};

		// 移動量の速さを反映
		move = Normalize(move);
		move = Multiply3(speed, move);

		// 回転行列
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);

		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {
			// 振る舞いリセット
			behaviorRequest_ = Behavior::jump;
			//worldTransformWeapon_.rotation_.x = 1.0f;
			//worldTransformWeapon_.translation_.y = 2.0f;
			//worldTransformL_arm_.rotation_.x = 1.0f;
			//worldTransformR_arm_.rotation_.x = 1.0f;
		}

		
	}


}

#pragma region ジャンプ

void Player::BehaviorJumpInitialize()
{
	
	worldTransformBase_.translation_.y = 0;
	worldTransformL_arm_.rotation_.x = 0;
	worldTransformL_arm_.rotation_.y = 0;

	//ジャンプ
	const float kJumpFirstSpeed = 1.0f;
	velocity_ = {0.0f, kJumpFirstSpeed, 0.0f};


}


void Player::BehaviorJumpUpdate() {

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {

			Add(worldTransform_.translation_, velocity_);

			const float kGravityAcceleration = 0.05f;

			Vector3 accelerarationVector = {0, -kGravityAcceleration, 0};

			Add(velocity_, accelerarationVector);
		}


		if (worldTransform_.translation_.x <= 0.0f) {
			worldTransform_.translation_.x = 0;
		}

		behaviorRequest_ = Behavior::kRoot;
	}

		
}

#pragma endregion

