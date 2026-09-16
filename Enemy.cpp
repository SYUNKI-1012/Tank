#include "Enemy.h"
#include "Engine\\Model.h"
#include"Engine//SphereCollider.h"
#include"Ground.h"

Enemy::Enemy(GameObject* parent):GameObject(parent, "Enemy"), hModel_(-1)
{

}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	Model::SetAnimFrame(hModel_, 1, 100, 1.0f);
	assert(hModel_ >= 0);
	SphereCollider* collider = new SphereCollider({ 0,0,0 }, 0.5); //コライダーを作る  
	AddCollider(collider); //コライダーをEnemyに追加する
	
	//float x = ();
}

void Enemy::Update()
{
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f; //地面は０より下に彫られて作られている。そうじゃないときは
	data.dir = { 0, -1, 0 }; //真下にレイを飛ばす

	Ground* pGround = (Ground*)FindObject("Ground"); //groundオブジェクト
	int hGroundModel = pGround->GetModelHandle(); //groundオブジェクトのモデルのハンドルを得る
	Model::RayCast(hGroundModel, &data); //レイキャストして、地面に当たったかどうか、当たった時の距離や

	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
		//レイの発射位置から、地面までの距離を引いて、地面にピッタリつける
	}
}

void Enemy::Draw()
{

	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{

}