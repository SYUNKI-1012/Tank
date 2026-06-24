#include "TankHead.h"
#include "Engine\\Model.h"
#include "Engine\\Input.h"
#include "Bullet.h"

TankHead::TankHead(GameObject* parent)
	:GameObject(parent, "TankHead"), hModel_(-1)
{

}

void TankHead::Initialize()
{
	hModel_ = Model::Load("Tankhead.fbx");
	assert(hModel_ >= 0);
}

void TankHead::Update()
{
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2.0f;
	}

	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2.0f;
	}

	if (Input::IsKey(DIK_SPACE))
	{
		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);
		XMVECTOR vMove = XMVectorSubtract(vTop, vRoot);
		//XMVECTOR vMove = vRoot - vTop;
		vMove = 0.2f * vMove;
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove); //XMFLOAT3に戻す
		//弾を生成する 
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent()); //親をタンクにして弾  
		pBullet->SetMoveVector(move);
		pBullet->SetPosition(cannonTop);
	}

}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{

}