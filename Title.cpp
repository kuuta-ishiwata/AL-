#include "Title.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "GameScene.h"
#include "Title.h"
#include "player.h"


Title::Title() {}

Title::~Title()
{
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


void Title::Update() 
{

	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd = true;
	}
}

void Title::Draw() 
{

	ID3D12GraphicsCommandList* commandList = dxCommom_->GetCommandList();

	Sprite::PreDraw(commandList);

	Sprite_->Draw();

	Sprite::PostDraw();

	dxCommom_->ClearDepthBuffer();
}

void Title::Reset() { isSceneEnd = false; }