#include "Tank.h"
#include "Engine//Model.h"
#include "Engine/Input.h"

Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	hModel_ = Model::Load("TankHead.fbx");
	//assert(hNodel_ >= 0); //モデルの読み込み

}

void Tank::Update()
{
	if (Input::IsKey(DIK_LEFT) || Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 2;
	}

	if (Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 2;
	}
}

void Tank::Draw()
{
	transform_.rotate_ = { 0.0f, 180.0f, 0.0f };
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
