//
// Created by Sterling on 2/7/2024.
//

#ifndef IPLATFORM_H
#define IPLATFORM_H

#include <string>

namespace strl
{
class IPlatform
{
public:
	virtual ~IPlatform() = 0;

	virtual bool window_should_close() = 0;

	virtual void process_input() = 0;
	virtual void update() const = 0;

protected:
	IPlatform(int window_width, int window_height, std::string window_name)
		: window_width_(window_width), window_height_(window_height), window_name_(std::move(window_name))
	{
	}

	int window_width_, window_height_;
	std::string window_name_;

};
} // strl
#endif //IPLATFORM_H
