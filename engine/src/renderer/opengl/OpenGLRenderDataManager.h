//
// Created by SterlingMeinscher on 2/15/2024.
//

#ifndef OPENGLRENDERDATAMANAGER_H
#define OPENGLRENDERDATAMANAGER_H

#include "../../core/manager/STRLManagerBase.h"
#include "OpenGLRenderData.h"

namespace strl
{

class OpenGLRenderDataManager : public STRLManagerBase<OpenGLRenderData>
{
public:
	OpenGLRenderDataManager() = default;
	~OpenGLRenderDataManager() override = default;

};

} // strl

#endif //OPENGLRENDERDATAMANAGER_H
