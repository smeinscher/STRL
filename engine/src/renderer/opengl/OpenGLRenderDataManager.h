//
// Created by SterlingMeinscher on 2/15/2024.
//

#ifndef OPENGLRENDERDATAMANAGER_H
#define OPENGLRENDERDATAMANAGER_H

#include "../../util/manager/STRLManagerBase.h"
#include "OpenGLRenderData.h"
#include "OpenGLRenderer.h"

namespace strl
{

class OpenGLRenderDataManager : public STRLManagerBase<OpenGLRenderData>
{
public:
	explicit OpenGLRenderDataManager(OpenGLRenderer& renderer);
	~OpenGLRenderDataManager() override;

	OpenGLRenderData* create(std::string name,
		std::vector<std::string> tags,
		OpenGLShader* shader,
		STRLCamera* camera);

	void remove(OpenGLRenderData* render_data) override;

private:
	OpenGLRenderer& renderer_;

};

} // strl

#endif //OPENGLRENDERDATAMANAGER_H