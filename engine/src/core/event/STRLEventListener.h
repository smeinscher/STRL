//
// Created by SterlingMeinscher on 2/16/2024.
//

#ifndef STRLEVENTLISTENER_H
#define STRLEVENTLISTENER_H

#include <functional>
#include "../manager/STRLManagedItemBase.h"

namespace strl
{

class STRLEvent;
using STRLEventListenerFunction = std::function<void(STRLEvent*)>;

struct STRLEventListenerDefinition : STRLManagedItemDefinitionBase
{
	STRLEventListenerFunction listener_function;
};

class STRLEventListener : public STRLManagedItemBase
{
public:
	explicit STRLEventListener(const STRLEventListenerDefinition& definition);
	void execute(STRLEvent* event_context);

private:
	STRLEventListenerFunction listener_function_;
};

} // strl

#endif //STRLEVENTLISTENER_H
