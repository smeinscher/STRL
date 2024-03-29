//
// Created by Sterling on 3/1/2024.
//

#ifndef GAMESCENE_H
#define GAMESCENE_H


#include "strl/strl.h"

class GameScene : public strl::Scene
{
public:
	using strl::Scene::STRLSceneBase;
	bool init() override;
	void update() override;
	void render() override;
};


#endif //GAMESCENE_H
