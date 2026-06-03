#pragma once
#include "Engine\\GameObject.h"

class Ground :
	public GameObject
{
public:
	Ground(GameObject* parent);
	~Ground();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hModel_; //地面モデルのハンドル
	Transform tr_; //トランスフォーム
};