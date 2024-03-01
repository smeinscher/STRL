//
// Created by SterlingMeinscher on 3/1/2024.
//

#ifndef STRLCAMERAMANAGER_H
#define STRLCAMERAMANAGER_H

#include "STRLCamera.h"
#include "../util/manager/STRLManagerBase.h"

namespace strl
{

class STRLCameraManager : public STRLManagerBase<STRLCamera>
{
public:
	~STRLCameraManager() override = default;
};

} // strl

#endif //STRLCAMERAMANAGER_H
