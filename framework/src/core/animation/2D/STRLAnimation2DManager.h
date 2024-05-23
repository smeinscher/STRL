#ifndef STRLANIMATION2DMANAGER_H
#define STRLANIMATION2DMANAGER_H

#include "../../../core/object/STRLObject.h"
#include "../../../util/manager/STRLManagerBase.h"
#include <glm/ext/vector_int2.hpp>

namespace strl
{

struct STRLAnimation2DData : STRLManagedItemBase
{
    STRLObject *object;
    bool active = true;
    bool animate;
    bool repeat;
    glm::ivec2 total_segments;
    glm::ivec2 selected_segment;
    int current_end_segment_x;
    int current_starting_segment_x;
    float time = 0.0f;
    float previous_frame_time = 0.0f;
    float frame_update_time = 0.025;

    std::vector<std::pair<int, std::vector<std::function<void()>>>> frame_events;

    STRLAnimation2DData(std::string name, std::vector<std::string> tags)
        : STRLManagedItemBase(std::move(name), std::move(tags))
    {
    }
};

class STRLAnimation2DManager : public STRLManagerBase<STRLAnimation2DData>
{
  public:
    STRLAnimation2DData *get_by_object(STRLObject *object);
};

} // namespace strl
#endif // STRLANIMATION2DMANAGER_H
