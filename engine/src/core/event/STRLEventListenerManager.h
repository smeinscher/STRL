//
// Created by SterlingMeinscher on 2/16/2024.
//

#ifndef STRLEVENTLISTENERMANAGER_H
#define STRLEVENTLISTENERMANAGER_H

#include "STRLEventListener.h"
#include "../manager/STRLManagerBase.h"

namespace strl
{

class STRLEventListenerManager : public STRLManagerBase<STRLEventListener>
{
public:
	~STRLEventListenerManager() override = default;

};

} // strl

#endif //STRLEVENTLISTENERMANAGER_H
