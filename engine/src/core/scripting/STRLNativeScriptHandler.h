//
// Created by SterlingMeinscher on 2/13/2024.
//

#ifndef STRLNATIVESCRIPTHANDLER_H
#define STRLNATIVESCRIPTHANDLER_H

#include <memory>
#include <functional>
#include "ISTRLScript.h"
#include "../../util/manager/STRLManagedItemBase.h"
#include <iostream>

namespace strl
{

class STRLNativeScriptHandler : public STRLManagedItemBase
{
public:
	explicit STRLNativeScriptHandler(std::string name = "Script Handler", std::vector<std::string> tags = {});
	~STRLNativeScriptHandler();
	template <typename T, typename... ARGS>
	void bind(ARGS... args)
	{
		create_script_ = [this, args...]()
		{
			instance_ = std::make_unique<T>(args...);
			instance_->on_create();
		};

		destroy_script_ = [this]()
		{
			instance_->on_destroy();
			instance_.reset();
		};
	}

	void call_create_script();
	void call_destroy_script();
	ISTRLScript* get_instance();

private:
	std::unique_ptr<ISTRLScript> instance_ = nullptr;
	std::function<void()> create_script_;
	std::function<void()> destroy_script_;
};

} // strl

#endif //STRLNATIVESCRIPTHANDLER_H
