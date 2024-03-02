//
// Created by Sterling on 3/1/2024.
//

#include "GameScene.h"
#include "../scripts/Player.h"

bool GameScene::init()
{
	if (!STRLSceneBase::init())
	{
		return false;
	}

	return true;
}

void GameScene::update()
{
	STRLSceneBase::update();
}

void GameScene::render()
{
	STRLSceneBase::render();
}
