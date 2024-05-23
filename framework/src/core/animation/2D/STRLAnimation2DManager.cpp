#include "STRLAnimation2DManager.h"

namespace strl
{

STRLAnimation2DData *STRLAnimation2DManager::get_by_object(STRLObject *object)
{
    for (const auto &item : items_)
    {
        if (object == item->object)
        {
            return item.get();
        }
    }
    return nullptr;
}

} // namespace strl
