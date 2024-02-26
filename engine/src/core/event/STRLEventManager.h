//
// Created by SterlingMeinscher on 2/15/2024.
//

#ifndef STRLEVENTMANAGER_H
#define STRLEVENTMANAGER_H

#include "../manager/STRLManagerBase.h"
#include "STRLEvent.h"

namespace strl
{

class STRLEventManager : public STRLManagerBase<STRLEvent>
{
public:
	~STRLEventManager() override = default;

	STRLEvent* create(STRLEventDefinition definition);

	STRLEvent* get_by_event_code(STRLEventType event_type, unsigned int event_code);
	std::vector<STRLEvent*> get_by_event_type(STRLEventType event_type);

	void register_event_listener(STRLEventType event_type,
		unsigned int event_code,
		STRLEventListenerFunction event_listener_function,
		std::string_view name,
		std::vector<std::string> tags = {});

	// TODO: sort items by event type and event code?
};

} // strl

#endif //STRLEVENTMANAGER_H
