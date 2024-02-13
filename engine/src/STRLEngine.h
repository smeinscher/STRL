//
// Created by Sterling on 2/9/2024.
//

#ifndef STRLENGINE_H
#define STRLENGINE_H

#include <string>
#include <memory>
#include "platform/IPlatform.h"
#include "renderer/IRenderer.h"
#include "object/STRLObject.h"
#include "util/manager/ISTRLManager.h"

namespace strl
{

class STRLEngine
{
public:
	explicit STRLEngine(int window_width = 800, int window_height = 600, std::string window_name = "STRL Application");

	ISTRLManager<STRLObject, STRLObjectDefinition>& get_object_manager();

	void run();

private:
	int window_width_, window_height_;
	std::string window_name_;

	std::unique_ptr<IPlatform> platform_;
	std::unique_ptr<IRenderer> renderer_;
	std::unique_ptr<ISTRLManager<STRLObject, STRLObjectDefinition>> object_manager_;
};

} // strl

#endif //STRLENGINE_H
