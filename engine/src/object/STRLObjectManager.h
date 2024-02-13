//
// Created by Sterling on 2/8/2024.
//

#ifndef STRLOBJECTMANAGER_H
#define STRLOBJECTMANAGER_H

#include "../util/manager/ISTRLManager.h"
#include "STRLObject.h"
#include "STRLObjectRenderData.h"

namespace strl
{

class STRLObjectManager : public ISTRLManager<STRLObject, STRLObjectDefinition>
{
public:
	explicit STRLObjectManager(IRenderer* renderer);
	~STRLObjectManager() override;

	STRLObject* create(STRLObjectDefinition& object_definition) override;
	std::vector<STRLObject*> get_by_name(const std::string& name) override;
	std::vector<STRLObject*> get_by_tag(const std::string& tag) override;
	STRLObject* get_by_id(int id) override;
	[[nodiscard]] const std::vector<std::pair<int&, std::unique_ptr<STRLObject>>>& get_all() const override;
	void remove(STRLObject* object) override;
	void remove_multiple(const std::vector<STRLObject*>& objects) override;

private:
	std::vector<std::unique_ptr<STRLObjectRenderData>> render_data_;
};

} // strl

#endif //STRLOBJECTMANAGER_H
