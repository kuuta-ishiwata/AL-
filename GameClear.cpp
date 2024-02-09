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

	fadeTextureHandle = TextureManager::Load("fade.png");
	fadeSprite_ = Sprite::Create(fadeTextureHandle, {0, 0}, {1, 1, 1, 1});
}

void GameClear::Update() 
{

	
	fadeColor.w -= 0.020f;
	fadeSprite_->SetColor(fadeColor);
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
	fadeColor = {1.0f, 1.0f, 1.0f, 1.0f};
	fadeSprite_ = Sprite::Create(fadeTextureHandle, {0, 0}, {1, 1, 1, 1});
	isSceneEnd = false;
}

void GameClear::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommom_->GetCommandList();

	Sprite::PreDraw(commandList);

	GameClearSprite_->Draw();
	fadeSprite_->Draw();
	Sprite::PostDraw();

	dxCommom_->ClearDepthBuffer();
}