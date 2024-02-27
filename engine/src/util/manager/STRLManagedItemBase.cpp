//
// Created by SterlingMeinscher on 2/15/2024.
//

#include <algorithm>
#include <iostream>
#include "STRLManagedItemBase.h"

namespace strl
{

int STRLManagedItemBase::id_accumulator_{ 0};

STRLManagedItemBase::STRLManagedItemBase(std::string name, std::vector<std::string> tags)
	: name_(std::move(name)), tags_(std::move(tags)), id_(id_accumulator_++)
{
}

std::string_view STRLManagedItemBase::get_name() const
{
	return name_;
}

void STRLManagedItemBase::set_name(std::string name)
{
	name_ = std::move(name);
}

const std::vector<std::string>& STRLManagedItemBase::get_tags() const
{
	return tags_;
}

void STRLManagedItemBase::add_tag(std::string tag)
{
	auto it = std::find(tags_.begin(), tags_.end(), tag);
	if (it == tags_.end())
	{
		tags_.emplace_back(std::move(tag));
		return;
	}
	// TODO: logging stuff
	std::cout << "Tag already present" << std::endl;
}

void STRLManagedItemBase::remove_tag(std::string_view tag)
{
	auto it = tags_.begin();
	while (it != tags_.end())
	{
		if (*it == tag)
		{
			tags_.erase(it);
			return;
		}
	}
	// TODO: logging stuff
	std::cout << "Tag not found" << std::endl;
}

int STRLManagedItemBase::get_id() const
{
	return id_;
}

} // strl