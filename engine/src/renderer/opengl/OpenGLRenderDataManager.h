//
// Created by SterlingMeinscher on 2/15/2024.
//

#ifndef OPENGLRENDERDATAMANAGER_H
#define OPENGLRENDERDATAMANAGER_H

#include "../../util/manager/STRLManagerBase.h"
#include "OpenGLRenderData.h"

namespace strl
{

class OpenGLRenderDataManager : public STRLManagerBase<OpenGLRenderData>
{
public:
	OpenGLRenderDataManager();
	~OpenGLRenderDataManager() override;

	OpenGLRenderData* create(std::string name,
		std::vector<std::string> tags,
		OpenGLShader* shader,
		STRLCamera* camera,
		std::function<void()> shader_update_function = nullptr);

	void remove(OpenGLRenderData* render_data) override;

};

} // strl

#endif //OPENGLRENDERDATAMANAGER_H
