//
// Created by SterlingMeinscher on 2/15/2024.
//

#include "STRLEventManager.h"

#include <utility>
#include <format>
#include <iostream>

namespace strl
{

#define EVENT_NAME_FORMAT_STRING "type={},code={}"
#define EVENT_TYPE_TAG_FORMAT_STRING "type={}"
#define ENGINE_GENERATED_EVENT_TAG "Engine Generated Event"

STRLEvent* STRLEventManager::create(STRLEventDefinition definition)
{
	definition.tags.emplace_back(std::format(EVENT_TYPE_TAG_FORMAT_STRING,
		std::to_string(static_cast<int>(definition.event_type))));
	// TODO: check if performance hit with this
	STRLEvent* event = get_by_event_code(definition.event_type, definition.event_code);
	if (!event)
	{
		event = STRLManagerBase<STRLEvent>::create(std::move(definition));
	}
	else
	{
		// TODO: logging stuff
		std::cout << "Event with event_type=" << static_cast<int>(definition.event_type) << " and event_code="
			<< definition.event_code << " already exists" << std::endl;
	}
	return event;
}

STRLEvent* STRLEventManager::get_by_event_code(STRLEventType event_type, unsigned int event_code)
{
	auto it = std::find_if(items_.begin(), items_.end(), [&](const std::unique_ptr<STRLEvent>& item)
	{
		return item->get_event_type() == event_type && item->get_event_code() == event_code;
	});
	if (it != items_.end())
	{
		return (*it).get();
	}
	return nullptr;
}

std::vector<STRLEvent*> STRLEventManager::get_by_event_type(STRLEventType event_type)
{
	std::vector<STRLEvent*> events_with_type;
	for (const auto& item : items_)
	{
		if (item->get_event_type() == event_type)
		{
			events_with_type.push_back(item.get());
		}
	}
	return events_with_type;
}

void STRLEventManager::register_event_listener(STRLEventType event_type,
	unsigned int event_code,
	STRLEventListenerFunction event_listener_function,
	std::string_view name,
	std::vector<std::string> tags)
{
	if (event_type == STRLEventType::STRL_EVENT_IGNORE ||
		event_code == STRL_IGNORE)
	{
		return;
	}

	STRLEvent* event = get_by_event_code(event_type, event_code);
	if (!event)
	{
		STRLEventDefinition event_definition;
		event_definition.name = std::format(EVENT_NAME_FORMAT_STRING,
			std::to_string(static_cast<int>(event_type)), std::to_string(event_code));
		event_definition.tags.emplace_back(ENGINE_GENERATED_EVENT_TAG);
		event_definition.event_type = event_type;
		event_definition.event_code = event_code;
		event = create(event_definition);
	}
	STRLEventListenerDefinition event_listener_definition;
	event_listener_definition.name = name;
	event_listener_definition.tags = std::move(tags);
	event_listener_definition.listener_function = std::move(event_listener_function);
	event->get_event_listener_manager().create(event_listener_definition);
}

} // strl