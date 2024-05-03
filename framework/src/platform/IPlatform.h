//
// Created by Sterling on 2/7/2024.
//

#ifndef IPLATFORM_H
#define IPLATFORM_H

#include "../core/event/STRLEventManager.h"

namespace strl
{
class IPlatform
{
  public:
    virtual ~IPlatform() = 0;

    virtual void process_input() = 0;
    // TODO: change the name of this to make functionality clearer
    virtual void update() = 0;

    virtual int get_window_width() = 0;
    virtual void set_window_width(int width) = 0;
    virtual int get_window_height() = 0;
    virtual void set_window_height(int height) = 0;
    virtual void set_window_width_and_height(int width, int height) = 0;

    virtual bool window_should_close() = 0;
    virtual void set_window_should_close(bool window_should_close) = 0;

    virtual double get_time() = 0;

    virtual STRLEventManager &get_event_manager() = 0;

    virtual void toggle_fullscreen() = 0;
};
} // namespace strl
#endif // IPLATFORM_H
