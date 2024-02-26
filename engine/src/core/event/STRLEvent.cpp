//
// Created by SterlingMeinscher on 2/16/2024.
//

#include "STRLEvent.h"

namespace strl
{

STRLEvent::STRLEvent(const STRLEventDefinition& definition)
	: STRLManagedItemBase(definition.name, definition.tags), event_type_(definition.event_type),
	  event_code_(definition.event_code)
{}

STRLEvent::~STRLEvent() = default;

void STRLEvent::fire_event()
{
	for (auto& listener : event_listener_manager_)
	{
		listener->execute(this);
	}
}

STRLEventListenerManager& STRLEvent::get_event_listener_manager()
{
	return event_listener_manager_;
}

STRLEventType STRLEvent::get_event_type() const
{
	return event_type_;
}

unsigned int STRLEvent::get_event_code() const
{
	return event_code_;
}

} // strl