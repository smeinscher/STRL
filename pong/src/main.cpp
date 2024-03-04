#include <iostream>
#include <strl/strl.h>
#include "scenes/Pong.h"

int main()
{
	strl::STRLDriver driver{800, 600, "This is a test"};

	std::vector<std::string> tags = {"Pong Game"};
	int scene_id = driver.create_scene<Pong>("Pong Game Scene", tags);
	driver.set_active_scene(scene_id);
	driver.run();

	return 0;
}
