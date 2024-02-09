#include "Title.h"
#include "time.h"

Title::Title() {}

Title::~Title() {

	delete Sprite_;
	delete GameoverSprite_;
}

void Title::Initialize() {


	dxCommom_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();

	Start = TextureManager::Load("start.png");

	Dodge = TextureManager::Load("mozi.png");
	
	end = TextureManager::Load("gameover.png");


	Sprite_ = Sprite::Create(Start, {0, 0});

	Dodgeaprite = Sprite::Create(Dodge, {100, -200});


	Dodgeaprite->SetPosition(position_);

	position_ = {100, -200};

	fadeTextureHandle = TextureManager::Load("fade.png");
	fadeSprite_ = Sprite::Create(fadeTextureHandle, {0, 0}, {1, 1, 1, 1});
	
}

void Title::Update()
{
	fadeColor.w -= 0.020f;
	fadeSprite_->SetColor(fadeColor);

	if (position_.y <= 50)
	{
	
		position_.y += speed_;
		Dodgeaprite->SetPosition(position_);

	}


	XINPUT_STATE joyState;
	    // ゲームパッド状態取得
		if (Input::GetInstance()->GetJoystickState(0, joyState)) 
		{
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			 {

			if (position_.y >= 50)
			 
			 {
				isSceneEnd = true;
			 }

			}
		}
	

}

void Title::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommom_->GetCommandList();

	Sprite::PreDraw(commandList);

	Sprite_->Draw();

	Dodgeaprite->Draw();
	fadeSprite_->Draw();

	Sprite::PostDraw();

	dxCommom_->ClearDepthBuffer();

}


void Title::Reset() 
{  
	position_ = {100, -200};

	Dodgeaprite = Sprite::Create(Dodge, {100, -200});
	isSceneEnd = false;
	Dodgeaprite->SetPosition(position_);

	 fadeColor = {1.0f, 1.0f, 1.0f, 1.0f};
	fadeSprite_ = Sprite::Create(fadeTextureHandle, {0, 0}, {1, 1, 1, 1});
}