//
// Created by SterlingMeinscher on 2/16/2024.
//

#include "STRLEventListener.h"
#include "STRLEvent.h"

namespace strl
{

STRLEventListener::STRLEventListener(const STRLEventListenerDefinition& definition)
	: STRLManagedItemBase(definition.name, definition.tags), listener_function_(definition.listener_function)
{

}

void STRLEventListener::execute(STRLEvent* event_context)
{
	listener_function_(event_context);
}

} // strl