//
// Created by Sterling on 3/9/2024.
//

#include <strl/strl.h>
#include "scenes/SphereSandboxScene.h"

int main()
{
	strl::STRLDriver driver{800, 600, "Sphere Sandbox"};

	std::vector<std::string> tags = {"Sphere Sandbox Scene"};
	int scene_id = driver.create_scene<SphereSandboxScene>("Sphere Sandbox Scene", tags);
	driver.set_active_scene(scene_id);
	driver.run();

	return 0;
}