//
// Created by Sterling on 2/8/2024.
//

#include "STRLObjectManager.h"

namespace strl
{

STRLObjectManager::STRLObjectManager(OpenGLRenderDataManager& render_data_manager)
	: render_data_manager_(render_data_manager)
{
}

STRLObjectManager::~STRLObjectManager() = default;

STRLObject* STRLObjectManager::create(STRLObjectDefinition definition)
{
	STRLObject* object = STRLManagerBase<STRLObject>::create(std::move(definition));
	object->get_observer_subject().attach(this);

	std::vector<OpenGLRenderData*> render_data_vector = render_data_manager_.get_by_name("Engine Default");
	if (!render_data_vector.empty())
	{
		OpenGLRenderData* render_data = render_data_vector[0];
		int object_index = static_cast<int>(render_data->get_last_object_index());
		object->set_render_data_object_id(render_data->get_id());
		object->set_render_data_index(object_index);
		object->set_render_data_indices_location(static_cast<int>(render_data->get_indices().size()));
		object->set_render_data_position_location(static_cast<int>(render_data->get_positions().size()));
		render_data->set_last_object_index(object_index + 1);
		object->force_update_all();
	}

	return object;
}

std::vector<STRLObject*> STRLObjectManager::get_by_render_data_object_id(int object_id)
{
	std::vector<STRLObject*> objects_with_object_id;
	for (const auto& item : items_)
	{
		if (object_id == item->get_render_data_object_id())
		{
			objects_with_object_id.emplace_back(item.get());
		}
	}
	return objects_with_object_id;
}

void STRLObjectManager::update(const STRLObjectMessage& message)
{
	if (message.object->get_render_data_object_id() < 0)
	{
		// TODO: logging stuff
		std::cout << "STRLObject does not have associated Render Data" << std::endl;
		return;
	}
	OpenGLRenderData* render_data = render_data_manager_.get_by_id(
		message.object->get_render_data_object_id());
	switch (message.update_type)
	{
	case STRLObjectMessage::POINTS:
	{
		std::vector<STRLObject*> objects =
			get_by_render_data_object_id(message.object->get_render_data_object_id());
		render_data->add_points(message.object, message.points_change_count, objects);
		break;
	}
	case STRLObjectMessage::POSITION:
	case STRLObjectMessage::SIZE:
	case STRLObjectMessage::ROTATION:
		render_data->update_positions(message.object);
		break;
	case STRLObjectMessage::UV:
		render_data->update_uvs(message.object);
		break;
	case STRLObjectMessage::COLOR:
		render_data->update_colors(message.object);
		break;
	}

}

void STRLObjectManager::assign_render_data(std::string_view name, STRLObject* object)
{
	auto render_data_vector = render_data_manager_.get_by_name(name);
	if (render_data_vector.empty())
	{
		// TODO: logging stuff
		std::cout << "Invalid render data name" << std::endl;
		return;
	}
	if (object->get_render_data_object_id() >= 0)
	{
		OpenGLRenderData* old_render_data = render_data_manager_.get_by_id(object->get_render_data_object_id());
		std::vector<STRLObject*> objects =
			get_by_render_data_object_id(object->get_render_data_object_id());
		old_render_data->remove(object, objects);
	}
	OpenGLRenderData* render_data = render_data_vector[0];
	object->set_render_data_object_id(render_data->get_id());
	object->set_render_data_index(static_cast<int>(render_data->get_indices().size()));
	object->force_update_all();
}

void STRLObjectManager::remove(STRLObject* object)
{
	OpenGLRenderData* render_data = render_data_manager_.get_by_id(object->get_render_data_object_id());
	std::vector<STRLObject*> objects = get_by_render_data_object_id(object->get_render_data_object_id());
	render_data->remove(object, objects);
	STRLManagerBase::remove(object);
}

} // strl