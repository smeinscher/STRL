#include "STRLAnimation2D.h"

namespace strl
{

void STRLAnimation2D::update(float dt)
{
    for (std::unique_ptr<STRLAnimation2DData> &data : animation_manager_)
    {
        if (!data->animate)
        {
            continue;
        }

        data->time += dt;

        if (data->time - data->previous_frame_time > data->frame_update_time)
        {
            data->selected_segment.x++;
            if (data->selected_segment.x > data->current_end_segment_x)
            {
                data->selected_segment.x = data->current_starting_segment_x;
                if (!data->repeat)
                {
                    data->animate = false;
                }
            }
            if (data->selected_segment.x > data->total_segments.x)
            {
                data->selected_segment.x = 0;
            }
            glm::vec2 start = {
                static_cast<float>(data->selected_segment.x) / static_cast<float>(data->total_segments.x),
                static_cast<float>(data->selected_segment.y) / static_cast<float>(data->total_segments.y)};
            glm::vec2 end = {
                static_cast<float>(data->selected_segment.x + 1) / static_cast<float>(data->total_segments.x),
                static_cast<float>(data->selected_segment.y + 1) / static_cast<float>(data->total_segments.y)};
            data->object->set_uv({{end.x, end.y}, {start.x, end.y}, {start.x, start.y}, {end.x, start.y}});
            data->time = 0.0f;
        }
    }
}

void reset_data(STRLAnimation2DData *data)
{
    data->animate = data->active;
    data->selected_segment.x = data->current_starting_segment_x;
    data->time = 0.0f;
    data->previous_frame_time = 0.0f;
}

void update_state(STRLAnimation2DData *data, STRLAnimation2DState &state)
{
    data->current_starting_segment_x = state.start_segment_x;
    data->current_end_segment_x = state.end_segment_x;
    data->frame_update_time = state.frame_update_time;
    data->repeat = state.repeat;
    data->selected_segment.y = state.selected_segment_y;
    reset_data(data);
}

void reset_object_uv(STRLAnimation2DData *data)
{
    glm::vec2 start, end;
    if (data->current_end_segment_x > -1)
    {
        start = {static_cast<float>(data->selected_segment.x) / static_cast<float>(data->total_segments.x),
                 static_cast<float>(data->selected_segment.y) / static_cast<float>(data->total_segments.y)};
        end = {static_cast<float>(data->selected_segment.x + 1) / static_cast<float>(data->total_segments.x),
               static_cast<float>(data->selected_segment.y + 1) / static_cast<float>(data->total_segments.y)};
    }
    else
    {
        start = {0.0f, 0.0f};
        end = {0.0f, 0.0f};
    }
    data->object->set_uv({{end.x, end.y}, {start.x, end.y}, {start.x, start.y}, {end.x, start.y}});
    data->time = 0.0f;
}

void STRLAnimation2D::restart(STRLObject *object)
{
    STRLAnimation2DData *data = animation_manager_.get_by_object(object);
    reset_data(data);
}

void STRLAnimation2D::restart(std::string name)
{
    std::vector<STRLAnimation2DData *> data_vector = animation_manager_.get_by_name(name);
    for (STRLAnimation2DData *data : data_vector)
    {
        reset_data(data);
    }
}

void STRLAnimation2D::restart(std::vector<std::string> tags)
{
    std::vector<STRLAnimation2DData *> data_vector = animation_manager_.get_by_tags(tags);
    for (STRLAnimation2DData *data : data_vector)
    {
        reset_data(data);
    }
}

void STRLAnimation2D::stop(STRLObject *object, bool reset)
{
    STRLAnimation2DData *data = animation_manager_.get_by_object(object);
    data->animate = false;
    if (reset)
    {
        reset_object_uv(data);
    }
}

void STRLAnimation2D::stop(std::string name, bool reset)
{
    std::vector<STRLAnimation2DData *> data_vector = animation_manager_.get_by_name(name);
    for (STRLAnimation2DData *data : data_vector)
    {
        data->animate = false;
        if (reset)
        {
            reset_object_uv(data);
        }
    }
}

void STRLAnimation2D::stop(std::vector<std::string> tags, bool reset)
{
    std::vector<STRLAnimation2DData *> data_vector = animation_manager_.get_by_tags(tags);
    for (STRLAnimation2DData *data : data_vector)
    {
        data->animate = false;
        if (reset)
        {
            reset_object_uv(data);
        }
    }
}

void STRLAnimation2D::change_state(STRLObject *object, STRLAnimation2DState &state)
{
    STRLAnimation2DData *data = animation_manager_.get_by_object(object);
    update_state(data, state);
}

void STRLAnimation2D::change_state(std::string name, STRLAnimation2DState &state)
{
    std::vector<STRLAnimation2DData *> data_vector = animation_manager_.get_by_name(name);
    for (STRLAnimation2DData *data : data_vector)
    {
        update_state(data, state);
    }
}

void STRLAnimation2D::change_state(std::vector<std::string> tags, STRLAnimation2DState &state)
{
    std::vector<STRLAnimation2DData *> data_vector = animation_manager_.get_by_tags(tags);
    for (STRLAnimation2DData *data : data_vector)
    {
        update_state(data, state);
    }
}

void STRLAnimation2D::init_animation(STRLObject *object, glm::ivec2 total_segments, STRLAnimation2DState &state,
                                     std::string name, std::vector<std::string> tags)
{
    if (name.empty())
    {
        name = object->get_name() + " Animation";
    }
    STRLAnimation2DData *data = animation_manager_.create(std::move(name), std::move(tags));
    data->object = object;
    data->total_segments = total_segments;
    update_state(data, state);
}

void STRLAnimation2D::add_state(STRLObject *object, STRLAnimation2DState &state)
{
    STRLAnimation2DData *data = animation_manager_.get_by_object(object);
    if (!data)
    {
        // TODO logging stuff
        std::cout << "Animation data is null" << std::endl;
        return;
    }
    update_state(data, state);
}

void STRLAnimation2D::set_active(STRLObject *object, bool active)
{
    STRLAnimation2DData *data = animation_manager_.get_by_object(object);
    data->active = active;
}

void STRLAnimation2D::set_active(std::string name, bool active)
{
    std::vector<STRLAnimation2DData *> data_vector = animation_manager_.get_by_name(name);
    for (STRLAnimation2DData *data : data_vector)
    {
        data->active = active;
    }
}

void STRLAnimation2D::set_active(std::vector<std::string> tags, bool active)
{
    std::vector<STRLAnimation2DData *> data_vector = animation_manager_.get_by_tags(tags);
    for (STRLAnimation2DData *data : data_vector)
    {
        data->active = active;
    }
}

} // namespace strl
