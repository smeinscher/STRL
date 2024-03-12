//
// Created by SterlingMeinscher on 2/15/2024.
//

#ifndef STRLEVENT_H
#define STRLEVENT_H

#include <functional>
#include <string>
#include "../../util/manager/STRLManagedItemBase.h"
#include "STRLEventListenerManager.h"
#include "../../config/STRLConfig.h"

namespace strl
{

enum class STRLEventType
{
	STRL_EVENT_IGNORE = STRL_IGNORE,
	STRL_EVENT_UNKNOWN = 0,
	STRL_EVENT_APP_QUIT = 1,
	STRL_EVENT_KEY_PRESSED = 2,
	STRL_EVENT_KEY_RELEASED = 3,
	STRL_EVENT_KEY_REPEATED = 4,
	STRL_EVENT_MOUSE_MOVED = 5,
	STRL_EVENT_MOUSE_BUTTON_PRESSED = 6,
	STRL_EVENT_MOUSE_BUTTON_RELEASED = 7,
	STRL_EVENT_MOUSE_BUTTON_REPEATED = 8,
	STRL_EVENT_MOUSE_WHEEL = 9,
	STRL_MAX_EVENT_TYPE = 255
};

struct STRLMouseScrollEventData
{
	double x_offset;
	double y_offset;
};

struct STRLMouseMoveEventData
{
	double x_pos;
	double y_pos;
};

struct STRLEventDefinition : public STRLManagedItemDefinitionBase
{
	STRLEventType event_type = STRLEventType::STRL_EVENT_UNKNOWN;
	unsigned int event_code = 0;
};

class STRLEvent : public STRLManagedItemBase
{
public:
	explicit STRLEvent(const STRLEventDefinition& definition);
	~STRLEvent();
	void fire_event(void* event_data = nullptr);
	STRLEventListenerManager& get_event_listener_manager();
	[[nodiscard]] STRLEventType get_event_type() const;
	[[nodiscard]] unsigned int get_event_code() const;
	void* get_event_data();

protected:
	STRLEventListenerManager event_listener_manager_;
	STRLEventType event_type_;
	unsigned int event_code_;
	void* event_data_ = nullptr;
};

} // strl

#endif //STRLEVENT_H
