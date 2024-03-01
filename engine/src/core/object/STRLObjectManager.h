//
// Created by Sterling on 2/8/2024.
//

#ifndef STRLOBJECTMANAGER_H
#define STRLOBJECTMANAGER_H

#include <utility>

#include "STRLObject.h"
#include "../../util/manager/STRLManagerBase.h"
#include "../../renderer/opengl/OpenGLRenderDataManager.h"
#include "../../util/algorithm/RenderConversions.h"
#include "../../renderer/opengl/OpenGLRenderer.h"

namespace strl
{

class STRLObjectManager : public STRLManagerBase<STRLObject>, public ISTRLObserver<STRLObjectMessage>
{
public:
	explicit STRLObjectManager(OpenGLRenderDataManager& render_data_manager);
	~STRLObjectManager() override;

	STRLObject* create(STRLObjectDefinition definition);

	std::vector<STRLObject*> get_by_render_data_object_id(int object_id);

	void update(const STRLObjectMessage& message) override;

	void add_texture(std::string name,
		std::vector<std::string> tags,
		const std::string& path,
		OpenGLShader* shader,
		STRLCamera* camera);

	void assign_texture(std::string_view name, STRLObject* object);

private:
	OpenGLRenderDataManager& render_data_manager_;
};

} // strl

#endif //STRLOBJECTMANAGER_H
