#include "FollowCamera.h"
#include "MATHEX.h"
#include <Input.h>
#include <Xinput.h>


void FollowCamera::Initialize() {

	viewProjection_.Initialize();

	viewProjection_.farZ = 1400.0f;

	viewProjection_.translation_.y = 40.0f;



}

void FollowCamera::Update() { 
	
	if (target_) {
	
	
		Vector3 offset = {0.0f, 2.0f, -20.0f};

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_.rotation_);
	
		offset = TransformNormal(offset, rotateMatrix);

		viewProjection_.translation_ = Add(target_->translation_, offset);
	
	}


	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		const float kradian = 0.02f;
		//viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kradian;
		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kradian;

	}

	viewProjection_.UpdateMatrix();

}
