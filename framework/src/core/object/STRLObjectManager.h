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

	// TODO: this might be redundant, determine if user will directly use this or RenderDataManager
	void add_render_data(std::string name,
		std::vector<std::string> tags,
		const std::string& texture_path,
		OpenGLShader* shader,
		STRLCamera* camera);

	void assign_render_data(std::string_view name, STRLObject* object);

private:
	OpenGLRenderDataManager& render_data_manager_;
};

} // strl

#endif //STRLOBJECTMANAGER_H
