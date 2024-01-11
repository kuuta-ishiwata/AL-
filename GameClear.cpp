#include "GameClear.h"
#include "GameScene.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "Title.h"
#include "ViewProjection.h"
#include "WorldTransform.h"



GameClear::GameClear() {}

GameClear::~GameClear() { delete GameClearSprite_; }

void GameClear::Initialize() {

	dxCommom_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();

	Clear = TextureManager::Load("clear.png");

	GameClearSprite_ = Sprite::Create(Clear, {0, 0});

}

void GameClear::Update() 
{
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) 
		{

			isSceneEnd = true;
		}
	}
}

void GameClear::Reset() 
{
	isSceneEnd = false;
}

void GameClear::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommom_->GetCommandList();

	Sprite::PreDraw(commandList);

	GameClearSprite_->Draw();

	Sprite::PostDraw();

	dxCommom_->ClearDepthBuffer();
}