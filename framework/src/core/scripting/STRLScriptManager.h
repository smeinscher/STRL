//
// Created by SterlingMeinscher on 2/15/2024.
//

#ifndef STRLSCRIPTMANAGER_H
#define STRLSCRIPTMANAGER_H

#include "../../util/manager/STRLManagerBase.h"
#include "STRLNativeScriptHandler.h"

namespace strl
{

class STRLScriptManager : public STRLManagerBase<STRLNativeScriptHandler>
{
public:
	~STRLScriptManager() override = default;
};

} // strl

#endif //STRLSCRIPTMANAGER_H
