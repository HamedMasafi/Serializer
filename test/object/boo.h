#ifndef BOO_H
#define BOO_H

#include <QObject>

class Boo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    QString m_name;

public:
    Q_INVOKABLE Boo(QObject *parent = nullptr);

QString name() const;

signals:

void nameChanged(QString name);

public slots:
void setName(QString name);
};

#endif // BOO_H
