#pragma once
#include "Engine\\GameObject.h"

class Enemy :  public GameObject
{ 
public:
    Enemy(GameObject * parent);
    ~Enemy() {} //インライン定義
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
    void OnCollision(GameObject* pTarget)
    {
        //衝突した相手がBulletだったら消える
        if (pTarget->GetObjectName() == "Bullet")
        {
            KillMe(); //自分を消す        }
        }
    }
    private:
    int  hModel_; //Enemyのモデル
};