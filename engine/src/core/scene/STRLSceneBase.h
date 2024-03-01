//
// Created by SterlingMeinscher on 3/1/2024.
//

#ifndef STRLSCENEBASE_H
#define STRLSCENEBASE_H

#include <memory>
#include "../../renderer/opengl/OpenGLRenderDataManager.h"
#include "../../renderer/STRLCameraManager.h"
#include "../scripting/STRLScriptManager.h"
#include "../event/STRLEventManager.h"
#include "../object/STRLObjectManager.h"
#include "../../platform/IPlatform.h"

namespace strl
{

class STRLSceneBase
{
public:
	STRLSceneBase(STRLObjectManager& object_manager,
		STRLCameraManager& camera_manager,
		STRLScriptManager& script_manager,
		STRLEventManager& event_manager,
		IPlatform* platform);
	virtual bool init();
	virtual void update();
	virtual void render();

protected:
	// New instance of each created per scene
	STRLObjectManager& object_manager_;
	STRLCameraManager& camera_manager_;
	STRLScriptManager& script_manager_;

	// Same instance for every scene
	// May want a new instance of this for each scene
	// Different key configs for each scene
	STRLEventManager& event_manager;

	// Platform functionality we want to give user
	double get_time();
	void quit_application();

	void set_background_color(float r, float g, float b, float a);
	void set_background_color(glm::vec4 color);

private:
	IPlatform* platform_;
	STRLRenderer* renderer_;


};

} // strl

#endif //STRLSCENEBASE_H
