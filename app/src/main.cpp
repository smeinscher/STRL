#include <iostream>
#include <strl/strl.h>

int main()
{
	strl::STRLEngine engine{800, 600, "This is a test"};
	strl::ObjectManager& object_manager = engine.get_object_manager();
	strl::STRLObjectDefinition object_definition{strl::STRLObjectDefinition::ShapeType2D::OCTAGON};
	object_definition.position = {-0.5f, -0.5f, 0.0f};
	strl::STRLObject* object1 = object_manager.create(object_definition);

	engine.run();


	return 0;
}
