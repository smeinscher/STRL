//
// Created by Sterling on 2/7/2024.
//

#include "PlatformBase.h"

namespace strl
{

PlatformBase::PlatformBase(int window_width, int window_height, std::string window_name)
	: window_width_(window_width), window_height_(window_height), window_name_(std::move(window_name))
{
}

PlatformBase::~PlatformBase() = default;

} // strl