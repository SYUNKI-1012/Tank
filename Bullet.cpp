#include "Bullet.h"
#include "Engine\\Model.h"
#include "Engine/SphereCollider.h"

Bullet::Bullet(GameObject* parent)
:GameObject(parent, "Bullet"), hModel_(-1), move_(XMFLOAT3(0, 0, 0))
{

}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);
	SphereCollider* collider = new SphereCollider({ 0,0,0 }, 0.5); //コライダーを作る
	AddCollider(collider);
}

void Bullet::Update()
{
	//transform_.position_ = transform_.position_ + move_;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //ロード：読み込み 
	move_.y -= 0.005f; //重力をつける
    XMVECTOR vMove = XMLoadFloat3(&move_); //ロード：読み込み
	vPos = vPos + vMove; //弾の進行方向に移動する
	XMStoreFloat3(&transform_.position_, vPos); //ストア：読み込み
	//transform_.position_.x += move_.x;
	//transform_.position_.y += move_.y;
	//transform_.position_.z += move_.z;
	if (transform_.position_.y > 50.0f )
	{
		KillMe(); //弾がある程度遠くに行ったら消す
	}

}
	//①弾の弾道を重力つける
	//②敵を配置（敵もレイキャストして、座標ランダムで置く
	//③当たり判定（コライダーの設置）
	void Bullet::Draw()
	{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}

	void Bullet::Release()
	{

	}