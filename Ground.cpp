#include "Ground.h"
#include "Engine/Model.h"


Ground::Ground(GameObject* parent)
	:GameObject(parent, "Ground"), hModel_(-1)
{
}

/// <summary>
/// なんもしない
/// </summary>
Ground::~Ground()
{
	//デストラクタ（オブジェクトが削除されるときに呼ばれる関数）
}

void Ground::Initialize()
{
	//モデルの読み込み
	hModel_ = Model::Load("Ground.fbx");
}

void Ground::Update()
{
}

void Ground::Draw()
{
	//transform_.scale_{ 1,1,1 };
	//transform_.rotate_{ 1,1,1 };
	//tansform_.
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ground::Release()
{
}
