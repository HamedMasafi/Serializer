#include "foo.h"

#include <QtTest>

#include <QPoint>
#include <QDebug>
#include <QVector>
#include <QPolygon>
#include <binaryserializer.h>

#include <jsonserializer.h>
#include <stringserializer.h>

class enums : public QObject
{
    Q_OBJECT

public:
    enums();
    ~enums();

private slots:
    void initTestCase();
    void test();
    void cleanupTestCase();
};

enums::enums()
{
}

enums::~enums()
{

}

void enums::initTestCase()
{
    qRegisterMetaType<Foo*>("Foo*");
}

void enums::test()
{
    JsonSerializer s;
    QScopedPointer<Foo> p(new Foo);
    p->init();

    auto o1 = s.serialize(p.data());
    qDebug().noquote() << QJsonDocument(o1).toJson(QJsonDocument::Indented);

    auto ds = s.deserialize<Foo>(o1);
    auto o2 = s.serialize(ds);
    qDebug().noquote() << QJsonDocument(o2).toJson(QJsonDocument::Indented);

    foreach (QString key, o1.keys()) {
        if (o1.value(key) != o2.value(key))
            qDebug() << "Values are not equals" <<
                o1.value(key) << o2.value(key);

    }
    QTEST_ASSERT(o1 == o2);
}

void enums::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(enums)

#include "tst_enums.moc"
