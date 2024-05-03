#include "scenes/GameScene.h"
#include <strl/strl.h>

int main()
{
    strl::STRLDriver driver{800, 600, false, "Top Down Shooter"};

    std::vector<std::string> tags = {"Main Game Scene"};
    int scene_id = driver.create_scene<GameScene>("TDS Main Game Scene", tags);
    driver.set_active_scene(scene_id);
    driver.run();

    return 0;
}
