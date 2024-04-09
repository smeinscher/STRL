//
// Created by SterlingMeinscher on 2/15/2024.
//

#include "STRLScriptManager.h"

namespace strl
{
void STRLScriptManager::remove(STRLNativeScriptHandler* script_handler)
{
	script_handler->call_destroy_script();
	STRLManagerBase::remove(script_handler);
}
} // strl