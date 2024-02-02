#include "GameOver.h"
#include "GameScene.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "Title.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "player.h"

GameOver::GameOver() {}

GameOver::~GameOver() { delete GameoverSprite_; }


void GameOver::Initialize() {



	dxCommom_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();

	end = TextureManager::Load("gameover.png");

	GameoverSprite_ = Sprite::Create(end, {0, 0});

	uint32_t fadeTextureHandle = TextureManager::Load("fade.png");
	fadeSprite_ = Sprite::Create(fadeTextureHandle, {0, 0}, {1, 1, 1, 1});

}

void GameOver::Update() 
{

	fadeColor.w -= 0.0020f;
	fadeSprite_->SetColor(fadeColor);
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			isSceneEnd = true;
		}
	}
}

void GameOver::Reset()
{

	isSceneEnd = false;

}

void GameOver::Draw() 
{

	ID3D12GraphicsCommandList* commandList = dxCommom_->GetCommandList();

	Sprite::PreDraw(commandList);

	GameoverSprite_->Draw();
	fadeSprite_->Draw();

	Sprite::PostDraw();

	dxCommom_->ClearDepthBuffer();
}