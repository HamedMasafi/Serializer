#include <QtTest>

#include <QPoint>
#include <QDebug>
#include <QVector>
#include <QPolygon>
#include <binaryserializer.h>

#ifdef QT_GUI_LIB
#include <QtGui/QFont>
#endif

#include <stringserializer.h>

class basic : public QObject
{
    Q_OBJECT

public:
    basic();
    ~basic();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

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

void basic::test_case1()
{
    StringSerializer ser;
    QVariant v;
    QString tmp;
    QVariant deserialized;

    TEST(QMetaType::Int, 5);
    TEST(QMetaType::UInt, 5);
    TEST(QMetaType::Short, 6);
    TEST(QMetaType::UShort, 6);
    TEST(QMetaType::Long, 6);
    TEST(QMetaType::ULong, 5u);
    TEST(QMetaType::LongLong, 6LL);
    TEST(QMetaType::ULongLong, 5ULL);
    TEST(QMetaType::Float, 3.14f);
    TEST(QMetaType::Double, 1024.2048);
    TEST(QMetaType::QString, "test");
    TEST(QMetaType::QChar, QChar('z'));
    TEST(QMetaType::Char, 'c');
    TEST(QMetaType::Char, 'ز');
    TEST(QMetaType::SChar, 255);
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
    TEST(QMetaType::QJsonDocument, QJsonDocument::fromJson("{\"x\": 1, \"y\": 2}"));
    TEST(QMetaType::QFont, QFont("Tahoma", 15, 5, true));
    TEST(QMetaType::QPolygon, QPolygon(QVector<QPoint>() << QPoint(1, 2) << QPoint(3, 4)));
    TEST(QMetaType::QPolygonF, QPolygonF(QVector<QPointF>() << QPointF(1.2, 2.5) << QPointF(3.4, 4.5)));
    TEST(QMetaType::QColor, QColor(Qt::blue));
    TEST(QMetaType::QVector2D, QVector2D(1.2f, 3.4f));
    TEST(QMetaType::QVector3D, QVector3D(1.2f, 3.4f, 5.6f));
    TEST(QMetaType::QVector4D, QVector4D(1.2f, 3.4f, 5.6f, 7.8f));
//    TEST(QMetaType::QImage, QImage(":/icon.png"));
}

QTEST_APPLESS_MAIN(basic)

#include "tst_basic.moc"
