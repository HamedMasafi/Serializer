#include "foo.h"
#include "boo.h"

#include <QtTest>

#include <QPoint>
#include <QtCore/QDebug>
#include <QtCore/QVector>

#include <binaryserializer.h>
#include <jsonserializer.h>
#include <stringserializer.h>

#ifdef QT_GUI_LIB
#include <QtGui/QPolygon>
#endif

class object : public QObject
{
    Q_OBJECT

public:
    object();
    ~object();

private Q_SLOTS:
    void initTestCase();
    void test();
    void cleanupTestCase();
};


object::object()
{
}

object::~object()
{

}

void object::initTestCase()
{
//    qDebug() << "#" << qRegisterMetaType<Foo::FooList>();
    qRegisterMetaType<Foo*>("Foo*");
    qRegisterMetaType<Foo::BooMap>("BooMap");
    qRegisterMetaType<QList<Boo*> >("QList<Foo*>");
}

void object::test()
{
    JsonSerializer s;
    QScopedPointer<Foo> p(new Foo);

    auto p2 = new Foo(p.data());
    p->setFoo(p2);

    QList<Boo*> booList;
    Foo::BooMap map;
    for (int i = 0; i < 3; ++i) {
        auto p3 = new Boo(p.data());
        p3->setName(QString("child #%1").arg(i));
        booList.append(p3);
        map.insert(p3->name(), p3);
    }
    p->setFooList(booList);
    p->setBooMap(map);
    qDebug() << "===================================";
    auto o1 = s.serialize(p.data());
    qDebug().noquote() << QJsonDocument(o1).toJson(QJsonDocument::Indented);

    auto pp2 = s.deserialize<Foo>(o1);
    auto o2 = s.serialize(pp2);

    qDebug().noquote() << QJsonDocument(o2).toJson(QJsonDocument::Indented);

    QTEST_ASSERT(o1 == o2);
}

void object::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(object)

#include "tst_object.moc"
