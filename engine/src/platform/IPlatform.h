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

	virtual void process_input() = 0;
	// TODO: change the name of this to make functionality clearer
	virtual void update() = 0;

	virtual bool window_should_close() = 0;
	virtual void set_window_should_close(bool window_should_close) = 0;

	virtual double get_time() = 0;

};
} // strl
#endif //IPLATFORM_H
