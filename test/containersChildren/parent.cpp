#include "parent.h"

Parent::Parent(QObject *parent)
    : QObject{parent}
{}

QList<Child *> Parent::children() const
{
    return m_children;
}

void Parent::setChildren(const QList<Child *> &newChildren)
{
    if (m_children == newChildren)
        return;
    m_children = newChildren;
    emit childrenChanged();
}
