//
// Created by SterlingMeinscher on 2/13/2024.
//

#ifndef STRLMOVESCRIPT_H
#define STRLMOVESCRIPT_H

#include "../ISTRLScript.h"
#include "../../../core/object/STRLObject.h"

namespace strl
{

class STRLMoveScript : public ISTRLScript
{
public:
	explicit STRLMoveScript(STRLObject* object);
	~STRLMoveScript() override;
	void on_create() override;
	void on_update() override;
	void on_destroy() override;

private:
	STRLObject* object_;
};

} // strl

#endif //STRLMOVESCRIPT_H
