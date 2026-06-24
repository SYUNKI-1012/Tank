#pragma once
#include "Engine\\GameObject.h"
class TankHead : public GameObject
{ 
public:
    TankHead(GameObject * parent);
    ~TankHead() {} //インライン定義
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;private:
    int  hModel_; //タンクヘッドのモデル
    };