//
// Created by SterlingMeinscher on 2/20/2024.
//

#ifndef MISC_H
#define MISC_H


#include "strl/strl.h"

class Misc : public strl::Script
{
public:
	explicit Misc(strl::STRLEngine* engine);
	~Misc() override = default;
	void on_create() override;
	void on_update() override;
	void on_destroy() override;

private:
	strl::STRLEngine* engine_;
	glm::vec4 color_ = { 0.25f, 0.0f, 0.0f, 1.0f};
	float mod_ = -1.0f;
};


#endif //MISC_H
