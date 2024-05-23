//
// Created by Sterling on 2/8/2024.
//

#ifndef STRLOBJECTMANAGER_H
#define STRLOBJECTMANAGER_H

#include "../../renderer/opengl/OpenGLRenderDataManager.h"
#include "../../util/manager/STRLManagerBase.h"
#include "STRLObject.h"

namespace strl
{

class STRLObjectManager : public STRLManagerBase<STRLObject>, public ISTRLObserver<STRLObjectMessage>
{
  public:
    explicit STRLObjectManager(OpenGLRenderDataManager &render_data_manager);
    ~STRLObjectManager() override;

    STRLObject *create(STRLObjectDefinition definition);

    std::vector<STRLObject *> get_by_render_data_object_id(int object_id);

    void update(const STRLObjectMessage &message) override;

    void assign_render_data(std::string_view name, STRLObject *object);

    void remove(STRLObject *object) override;

  private:
    OpenGLRenderDataManager &render_data_manager_;
};

} // namespace strl

#endif // STRLOBJECTMANAGER_H
