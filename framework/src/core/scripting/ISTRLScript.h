//
// Created by SterlingMeinscher on 2/13/2024.
//

#ifndef ISTRLSCRIPT_H
#define ISTRLSCRIPT_H

namespace strl
{

class ISTRLScript
{
public:
	virtual ~ISTRLScript() = default;

	virtual void on_create() = 0;
	virtual void on_update() = 0;
	virtual void on_destroy() = 0;
};

} // strl

#endif //ISTRLSCRIPT_H
