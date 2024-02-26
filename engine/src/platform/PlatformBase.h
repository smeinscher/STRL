//
// Created by Sterling on 2/7/2024.
//

#ifndef PLATFORMBASE_H
#define PLATFORMBASE_H

#include <string>

namespace strl
{
class PlatformBase
{
public:
	PlatformBase(int window_width, int window_height, std::string window_name);

	virtual ~PlatformBase() = 0;

	virtual void process_input() = 0;
	// TODO: change the name of this to make functionality clearer
	virtual void update() = 0;

	virtual bool window_should_close() = 0;
	virtual void set_window_should_close(bool window_should_close) = 0;

	virtual double get_time() = 0;

protected:
	int window_width_, window_height_;
	std::string window_name_;

};
} // strl
#endif //PLATFORMBASE_H
