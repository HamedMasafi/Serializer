#include "child.h"

Child::Child(QObject *parent)
    : QObject{parent}
{}

QString Child::name() const
{
    return m_name;
}

void Child::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

QPointF Child::point() const
{
    return m_point;
}

void Child::setPoint(QPointF newPoint)
{
    if (m_point == newPoint)
        return;
    m_point = newPoint;
    emit pointChanged();
}
