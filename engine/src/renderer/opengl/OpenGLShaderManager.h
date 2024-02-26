//
// Created by SterlingMeinscher on 2/21/2024.
//

#ifndef OPENGLSHADERMANAGER_H
#define OPENGLSHADERMANAGER_H

#include "OpenGLShader.h"
#include "../../core/manager/STRLManagerBase.h"

namespace strl
{

class OpenGLShaderManager : public STRLManagerBase<OpenGLShader>
{
public:
	~OpenGLShaderManager() override = default;
};

} // strl

#endif //OPENGLSHADERMANAGER_H
