#pragma once
#include "Engine\\GameObject.h"

class Tank :
	public GameObject
{
public:
	Tank(GameObject* parent);
	~Tank();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hModel_; //地面モデルのハンドル
	int camType_; //カメラの種類
	Transform tr_; //トランスフォーム
};