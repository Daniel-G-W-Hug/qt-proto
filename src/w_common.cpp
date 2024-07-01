#include "w_common.hpp"

#include "w_active_bivec.hpp"
#include "w_active_pt.hpp"
#include "w_active_vec.hpp"

bool anyHovered(QList<QGraphicsItem*> const& items)
{

    // return true, if the mouse in hovering on any of the items in the list
    bool anyHover{false};
    foreach (QGraphicsItem* item, items) {
        if (item->type() == active_pt::Type)
            anyHover = anyHover || qgraphicsitem_cast<active_pt*>(item)->isHovered();
        if (item->type() == active_vec::Type)
            anyHover = anyHover || qgraphicsitem_cast<active_vec*>(item)->isHovered();
        if (item->type() == active_bivec::Type)
            anyHover = anyHover || qgraphicsitem_cast<active_bivec*>(item)->isHovered();
    }
    return anyHover;
}