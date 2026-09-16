#include "Tank.h"
#include "Engine//Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Engine/Camera.h"
#include "TankHead.h"

namespace
{
	XMVECTOR vFront = { 0, 0, 1, 0 }; //タンクの前方向ベクトル
	const float movespeed = 0.1f;
	const float CAM_HEIGHT_BIAS = 0.2f; //カメラの高さのバイアス
	enum CAM_TYPE
	{
		FIXED_CAM,		//固定カメラ
		TPS_CAM,		//三人称視点
		TPS_CAMROT,		//三人称視点カメラ（回転）
		FPS_CAM,		//一人称視点カメラ
		CAM_TYPE_MAX
	};
}

//タンクのボディを表すクラス
Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1),camType_(FIXED_CAM)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	//assert(hNodel_ >= 0); //モデルの読み込み
	Instantiate<TankHead>(this); //親をタンクにして砲台を生成
}

void Tank::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //ロード：読み込み
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); //Y軸回転行列を作る
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
	if (Input::IsKey(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
		//0,1,2
	}
	switch (camType_)
	{
	case FIXED_CAM:
		//固定カメラの処理
		SetFixedcom();
		break;

	case TPS_CAM:
	{
		//三人称視点カメラの処理
		XMFLOAT3 camPos = transform_.position_; //タンクの位置をカメラの位置にする
		camPos.y = camPos.y + 5.0f; //カメラの高さをタンクの位置より少し高くする
		camPos.z = camPos.z - 13.0f; //カメラのタンクの位置より少し後ろにする
		Camera::SetPosition(camPos); //カメラの位置を設定
		Camera::SetTarget(transform_.position_); //カメラの注視点をタンクの位置にする	
	}
	break;

	case TPS_CAMROT:
	{
		//三人称視点カメラ（回転）の処理
		XMFLOAT3 camPos; //タンクの位置をカメラの位置にする
		XMVECTOR vCAM = { 0.0f, 3.0f, -7.0f, 0.0f }; //カメラの位置をタンク
		vCAM = XMVector3TransformCoord(vCAM, matRot); //タンクの回転をカメラの位置に反映させる
		XMStoreFloat3(&camPos, vPos + vCAM);
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
	}
	break;

	case FPS_CAM:
	{
		//一人称視点カメラの処理
		XMFLOAT3 camPos = transform_.position_; //タンクの位置をカメラの位置にする
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos); //カメラの位置をタンクの位置にする
		XMFLOAT3 camTarget; //カメラの注視点
		XMStoreFloat3(&camTarget, vPos + vMove); //カメラの注視点をタンクの前方にする
		Camera::SetTarget(camTarget);
	}
		break;

	}
	//Aキーを押している間、左に回転する
	if (Input::IsKey(DIK_LEFT) || Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.0f;
	}

	//Dキーを押している間、右に回転
	if (Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.0f;
	}
	Debug::Log("CAMTYPE =");
	Debug::Log(camType_, true); //後のtrueは改行するかどうか
	

	if (Input::IsKey(DIK_W))
	{
		
		vPos = vPos + movespeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos); //ストア：書き込み（格納）

	}


	//レイキャストして、浮いてたら、地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f; //地面は０より下に彫られて作られている。そうじゃないときは
	data.dir = { 0, -1, 0 }; //真下にレイを飛ばす

	Ground* pGround = (Ground*)FindObject("Ground"); //groundオブジェクト
	int hGroundModel = pGround->GetModelHandle(); //groundオブジェクトのモデルのハンドルを得る
	Model::RayCast(hGroundModel, &data); //レイキャストして、地面に当たったかどうか、当たった時の距離や

	if (data.hit == true)
	{
		transform_.position_.y = - data.dist;
		//レイの発射位置から、地面までの距離を引いて、地面にピッタリつける
	}
}

void Tank::Draw()
{
	//transform_.rotate_ = { 0.0f, 180.0f, 0.0f };
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}

void Tank::SetFixedcom()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}
