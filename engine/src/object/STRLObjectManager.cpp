//
// Created by Sterling on 2/8/2024.
//

#include <algorithm>
#include <optional>
#include "STRLObjectManager.h"
#include "../util/algorithm/Triangulation.h"
#include "../renderer/IRenderer.h"

namespace strl
{

STRLObjectManager::STRLObjectManager(IRenderer* renderer)
{
	// TODO: not this
	render_data_.emplace_back(std::make_unique<STRLObjectRenderData>(renderer));
	renderer->setup_render_data(*render_data_.back().get());
}

STRLObjectManager::~STRLObjectManager() = default;

STRLObject* STRLObjectManager::create(STRLObjectDefinition& object_definition)
{
	int render_data_index = !items_.empty() ?
		items_.back().first + Triangulation::triangulated_polygon(items_.back().second->get_points()).size() : 0;
	std::unique_ptr<STRLObject> object = std::make_unique<STRLObject>(object_definition, render_data_index);
	// TODO: check if std::move is even doing what I think it's doing
	items_.emplace_back(render_data_index, std::move(object));
	items_.back().second->attach(render_data_.back().get());

	render_data_.back()->update_positions(items_.back().second.get());

	//update_positions(objects_.back());
	return items_.back().second.get();
}

std::vector<STRLObject*> STRLObjectManager::get_by_name(const std::string& name)
{
	std::vector<STRLObject*> objects_with_name;
	for (const auto& object : items_)
	{
		if (name == object.second->get_name())
		{
			objects_with_name.emplace_back(object.second.get());
		}
	}
	return objects_with_name;
}

std::vector<STRLObject*> STRLObjectManager::get_by_tag(const std::string& tag)
{
	std::vector<STRLObject*> objects_with_tag;
	for (const auto& object : items_)
	{
		if (tag == object.second->get_name())
		{
			objects_with_tag.emplace_back(object.second.get());
		}
	}
	return objects_with_tag;
}

STRLObject* STRLObjectManager::get_by_id(int id)
{
	auto pred = [id](const std::pair<int&, std::unique_ptr<STRLObject>>& object)
	{
		return id == object.second->get_id();
	};
	auto it = std::find_if(items_.begin(), items_.end(), pred);
	if (it != items_.end())
	{
		return it->second.get();
	}
	return nullptr;
}

const std::vector<std::pair<int&, std::unique_ptr<STRLObject>>>& STRLObjectManager::get_all() const
{
	return items_;
}

void STRLObjectManager::remove(STRLObject* object)
{
	auto pred = [object](const std::pair<int&, std::unique_ptr<STRLObject>>& o)
	{
		return object == o.second.get();
	};
	auto it = std::find_if(items_.begin(), items_.end(), pred);
	if (it != items_.end())
	{
		int size = Triangulation::triangulated_polygon(it->second->get_points()).size();
		it = items_.erase(it);
		while (it != items_.end())
		{
			it->first -= size;
			it++;
		}
	}
}

void STRLObjectManager::remove_multiple(const std::vector<STRLObject*>& objects)
{
	for (auto object : objects)
	{
		remove(object);
	}
}

} // strl