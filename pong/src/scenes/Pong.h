//
// Created by Sterling on 3/1/2024.
//

#ifndef PONG_H
#define PONG_H


#include "strl/strl.h"

class Pong : public strl::Scene
{
public:
	using strl::Scene::STRLSceneBase;
	bool init() override;
	void update() override;
	void render() override;
};


#endif //PONG_H
