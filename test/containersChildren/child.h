#pragma once

#include <QObject>
#include <QPointF>

class Child : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QPointF point READ point WRITE setPoint NOTIFY pointChanged FINAL)

public:
    Q_INVOKABLE explicit Child(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    QPointF point() const;
    void setPoint(QPointF newPoint);

signals:
    void nameChanged();

    void pointChanged();

private:
    QString m_name;
    QPointF m_point;
};
