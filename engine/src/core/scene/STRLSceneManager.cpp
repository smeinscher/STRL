//
// Created by Sterling on 3/1/2024.
//

#include "STRLSceneManager.h"

namespace strl
{

STRLSceneBase* STRLSceneManager::get_active_scene()
{
	return active_scene_;
}

void STRLSceneManager::set_active_scene(int id)
{
	active_scene_ = get_by_id(id);
}

void STRLSceneManager::set_active_scene(std::string_view name)
{
	active_scene_ = get_by_name(name)[0];
}

void STRLSceneManager::set_active_scene(STRLSceneBase* scene)
{
	active_scene_ = scene;
}

} // strl