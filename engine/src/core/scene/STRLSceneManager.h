//
// Created by Sterling on 3/1/2024.
//

#ifndef STRLSCENEMANAGER_H
#define STRLSCENEMANAGER_H

#include "STRLSceneBase.h"

namespace strl
{

class STRLSceneManager : public STRLManagerBase<STRLSceneBase>
{
public:
	~STRLSceneManager() override = default;

	STRLSceneBase* get_active_scene();
	void set_active_scene(int id);
	void set_active_scene(std::string_view name);
	void set_active_scene(STRLSceneBase* scene);

private:
	STRLSceneBase* active_scene_;
};

} // strl

#endif //STRLSCENEMANAGER_H
