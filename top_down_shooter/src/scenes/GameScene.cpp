//
// Created by Sterling on 3/1/2024.
//

#include "GameScene.h"
#include "../scripts/Player.h"

bool Pong::init()
{
	if (!STRLSceneBase::init())
	{
		return false;
	}

	return true;
}

void Pong::update()
{
	STRLSceneBase::update();
}

void Pong::render()
{
	STRLSceneBase::render();
}
