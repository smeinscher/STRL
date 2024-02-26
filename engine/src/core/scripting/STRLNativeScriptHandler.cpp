//
// Created by SterlingMeinscher on 2/13/2024.
//

#include <cstdarg>
#include "STRLNativeScriptHandler.h"

namespace strl
{

STRLNativeScriptHandler::STRLNativeScriptHandler(std::string name, std::vector<std::string> tags)
	: STRLManagedItemBase(std::move(name), std::move(tags))
{

}

STRLNativeScriptHandler::~STRLNativeScriptHandler() = default;

void STRLNativeScriptHandler::call_create_script()
{
	create_script_();
}

void STRLNativeScriptHandler::call_destroy_script()
{
	destroy_script_();
}

ISTRLScript* STRLNativeScriptHandler::get_instance()
{
	return instance_.get();
}

} // strl