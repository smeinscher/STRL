//
// Created by Sterling on 3/9/2024.
//

#include "scenes/SphereSandboxScene.h"
#include <strl/strl.h>

int main()
{
    strl::STRLDriver driver{800, 600, false, "Sphere Sandbox"};
    std::vector<std::string> tags = {"Sphere Sandbox Scene"};
    int scene_id = driver.create_scene<SphereSandboxScene>("Sphere Sandbox Scene", tags);
    driver.set_active_scene(scene_id);
    driver.run();

    return 0;
}
