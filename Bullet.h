#pragma once
#include "Engine\\GameObject.h"
class Bullet :public GameObject
{ 
public:
    Bullet(GameObject * parent);
    ~Bullet() {} //インライン定義
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
    void SetMoveVector(XMFLOAT3 move) { move_ = move; }//弾の進行方向をセットする関数
private:
    int  hModel_; //タンクヘッドのモデル
    XMFLOAT3 move_;//弾の進行方向
};