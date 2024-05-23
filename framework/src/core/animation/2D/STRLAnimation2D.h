#ifndef STRLANIMATION2D_H
#define STRLANIMATION2D_H

#include "../../../core/object/STRLObject.h"
#include "STRLAnimation2DManager.h"

namespace strl
{

struct STRLAnimation2DState
{
    int start_segment_x;
    int end_segment_x;
    int selected_segment_y;
    float frame_update_time;
    bool repeat;
    std::vector<std::pair<int, std::vector<std::function<void()>>>> frame_events;
};

class STRLAnimation2D
{
  public:
    void update(float dt);

    void restart(STRLObject *object);
    void restart(std::string name);
    void restart(std::vector<std::string> tags);

    void stop(STRLObject *object, bool reset = false);
    void stop(std::string name, bool reset = false);
    void stop(std::vector<std::string> tags, bool reset = false);

    void change_state(STRLObject *object, STRLAnimation2DState &state);
    void change_state(std::string name, STRLAnimation2DState &state);
    void change_state(std::vector<std::string> tags, STRLAnimation2DState &state);

    void init_animation(STRLObject *object, glm::ivec2 total_segments, STRLAnimation2DState &state,
                        std::string name = "", std::vector<std::string> tags = {});
    void add_state(STRLObject *object, STRLAnimation2DState &state);

    void set_active(STRLObject *object, bool active);
    void set_active(std::string name, bool active);
    void set_active(std::vector<std::string> tags, bool active);

    STRLAnimation2DManager &get_animation_2d_manager();

  private:
    STRLAnimation2DManager animation_manager_;
};

} // namespace strl
#endif // STRLANIMATION2D_H
