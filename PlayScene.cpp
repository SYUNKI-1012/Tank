#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this); //親をPlaysceneにして地面を生成
	Instantiate<Tank>(this);
	//Instantiate<Enemy>();
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
