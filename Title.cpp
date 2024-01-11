#include "Title.h"

Title::Title() {}

Title::~Title() {

	delete Sprite_;
	delete GameoverSprite_;
}

void Title::Initialize() {

	dxCommom_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();

	Start = TextureManager::Load("start.png");

	
	end = TextureManager::Load("gameover.png");

	Sprite_ = Sprite::Create(Start, {0, 0});

	
}

void Title::Update() {

	XINPUT_STATE joyState;
	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState))
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {
			{
				isSceneEnd = true;
		}
	}
}

void Title::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommom_->GetCommandList();

	Sprite::PreDraw(commandList);

	Sprite_->Draw();

	Sprite::PostDraw();

	dxCommom_->ClearDepthBuffer();
}

void Title::Reset() { isSceneEnd = false; }