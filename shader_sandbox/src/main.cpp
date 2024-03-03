//
// Created by Sterling on 3/2/2024.
//

#include <strl/strl.h>
#include "scenes/ShaderSandboxScene.h"

int main()
{
	strl::STRLDriver driver{800, 600, "Shader Sandbox"};
	int scene_id = driver.create_scene<ShaderSandboxScene>("Shader Sandbox Scene",
		std::vector<std::string>{});
	driver.set_active_scene(scene_id);
	driver.run();
	return 0;
}