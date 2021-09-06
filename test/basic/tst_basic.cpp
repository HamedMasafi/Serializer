#include <QtTest>

#include <QtCore/QPoint>
#include <QtCore/QDebug>
#include <QtCore/QVector>
#include "binaryserializer.h"
#include "stringserializer.h"

#ifdef QT_GUI_LIB
#include <QtGui/QFont>
#include <QtGui/QPolygon>
#endif

#include <stringserializer.h>

class basic : public QObject
{
    Q_OBJECT

public:
    basic();
    ~basic();
    void types(AbstractSerializer &ser);

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testString();
    void testBinary();
    void getString();
    void doubleTest();
};

basic::basic()
{

}

basic::~basic()
{

}

void basic::initTestCase()
{

}

void basic::cleanupTestCase()
{

}

void basic::testString()
{
    StringSerializer s;
    types(s);
}

void basic::testBinary()
{
    BinarySerializer b;
    types(b);
}

#ifdef ENABLE_TEST_MACROS
#define TEST(type, value) \
    do{ \
    v = QVariant(value); \
    tmp = ser.toString(v); \
    qDebug() << #type " serialized as" << tmp; \
    deserialized = ser.fromString(tmp, type); \
    if (deserialized != v) \
        qDebug() << v << deserialized; \
    QVERIFY2(deserialized == v, "verfy faild for" #type); \
    } while (false)

#define TEST_NO_MSG(type, value) \
    do{ \
    v = QVariant(value); \
    tmp = ser.toString(v); \
    deserialized = ser.fromString(tmp, type); \
    if (deserialized != v) \
        qDebug() << v << deserialized; \
    QVERIFY2(deserialized == v, "verfy faild for" #type); \
    } while (false)
#else
#define TEST(type, value)
#define TEST_NO_MSG(type, value)
#endif

void basic::types(AbstractSerializer &ser)
{
    Q_UNUSED(ser)

    QVariant v;
    QString tmp;
    QVariant deserialized;

    QVariantMap map;
    map.insert("a", 1);
    map.insert("b", "aa\naa");
    map.insert("c", "Hi\"there");

    TEST(QMetaType::Int, 5);
    TEST(QMetaType::UInt, 5);
    TEST(QMetaType::Short, 6);
    TEST(QMetaType::UShort, 6);
    TEST(QMetaType::Long, 6);
    TEST(QMetaType::ULong, 5u);
    TEST(QMetaType::LongLong, 6ll);
    TEST(QMetaType::ULongLong, 5ull);
    TEST(QMetaType::Float, 3.14f);
    TEST(QMetaType::Double, 1024.2048);
    TEST(QMetaType::QString, "test \r text \n p");
    TEST(QMetaType::QChar, QChar('z'));
    TEST(QMetaType::Char, 'c');
    TEST(QMetaType::Char, 'ز');
    TEST(QMetaType::SChar, -120);
    TEST(QMetaType::UChar, 255);
    TEST(QMetaType::QDate, QDate::currentDate());
    TEST(QMetaType::QTime, QTime::currentTime());
    TEST(QMetaType::QDateTime, QDateTime::currentDateTime());
    TEST(QMetaType::QPoint, QPoint(12, 34));
    TEST(QMetaType::QSize, QSize(12, 34));
    TEST(QMetaType::QRect, QRect(3, 4, 6, 7));
    TEST(QMetaType::QPointF, QPointF(12.98, 34.87));
    TEST(QMetaType::QSizeF, QSizeF(12.98, 34.87));
    TEST(QMetaType::QRectF, QRectF(3.4, 4.5, 6.001, 7.54));
    TEST(QMetaType::QUuid, QUuid::createUuid());
    TEST(QMetaType::QByteArray, QByteArray("sample byte array"));
    TEST(QMetaType::QByteArray, QByteArray("رشته یونیکد"));
    TEST(QMetaType::QBitArray, QBitArray::fromBits("abc", 3 * 8));
    TEST(QMetaType::QStringList, QStringList() << "one" << "two" << "three");
    TEST(QMetaType::QUrl, QUrl("http://google.com"));
    TEST(QMetaType::QLine, QLine(1, 2, 3, 4));
    TEST(QMetaType::QLineF, QLineF(1.2, 2.3, 3.4, 4.5));
    QJsonObject jsonObj;
    jsonObj["a"] = 4;
//    TEST(QMetaType::QJsonObject, jsonObj);
    TEST(QMetaType::QJsonDocument, QJsonDocument::fromVariant(map));
    TEST(QMetaType::QFont, QFont("Tahoma", 15, 5, true));
    TEST(QMetaType::QPolygon, QPolygon(QVector<QPoint>() << QPoint(1, 2) << QPoint(3, 4)));
    TEST(QMetaType::QPolygonF, QPolygonF(QVector<QPointF>() << QPointF(1.2, 2.5) << QPointF(3.4, 4.5)));
    TEST(QMetaType::QColor, QColor(Qt::blue));
    TEST(QMetaType::QVector2D, QVector2D(1.2f, 3.4f));
    TEST(QMetaType::QVector3D, QVector3D(1.2f, 3.4f, 5.6f));
    TEST(QMetaType::QVector4D, QVector4D(1.2f, 3.4f, 5.6f, 7.8f));
//    TEST(QMetaType::QVariantMap, map);
    TEST_NO_MSG(QMetaType::QImage, QImage(":/icon.png"));
}

void basic::getString()
{
    StringSerializer s;
    QString text = "\"Hi this is \\\" sample\" text";
    QString out;
    s.readString(text, out);
    qDebug() << out;
    qDebug() << text;
    QVERIFY(out == "Hi this is \\\" sample");
}

void basic::doubleTest()
{
    StringSerializer s;
    double d1 = 0.1 + .2;
    double d2 = 1.0 / 7;
    QPointF pt{d1, d2};
    auto v = QVariant::fromValue(pt);
    auto serializedd1 = s.toString(d1);
    auto serializedd2 = s.toString(d2);
    auto serializedPoint = s.toString(v);
    qDebug() << serializedPoint;
    QCOMPARE(serializedd1, QVariant::fromValue(d1).toString());
    QCOMPARE(serializedd2, QVariant::fromValue(d2).toString());
    QCOMPARE(serializedPoint, serializedd1 + QStringLiteral(",") + serializedd2);
}

QTEST_APPLESS_MAIN(basic)

#include "tst_basic.moc"
