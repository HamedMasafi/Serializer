#ifndef FOO_H
#define FOO_H

#include <QtCore/QObject>
#include <QtCore/QSet>
#include <QtCore/QVariantList>

class Foo : public QObject
{
    Q_OBJECT
public:
    enum Sample { One, Two, Three };
    Q_ENUM(Sample)

    enum SampleFlag {
        Four = 1,
        Five = 2,
        Six = 4,
        Seven = 8
    };
    Q_DECLARE_FLAGS(SampleFlags, SampleFlag)
    Q_FLAGS(SampleFlags)

private:
    Q_PROPERTY(Sample sampleEnum READ sampleEnum WRITE setSampleEnum NOTIFY
                   sampleEnumChanged)
    Q_PROPERTY(SampleFlags sampleFlag READ sampleFlag WRITE setSampleFlag NOTIFY sampleFlagChanged)

    Sample m_sampleEnum;
    SampleFlags m_sampleFlag;

public:
    explicit Foo(QObject *parent = nullptr);
    void init();
    Sample sampleEnum() const;
    SampleFlags sampleFlag() const;

public Q_SLOTS:
    void setSampleEnum(Sample sampleEnum);
    void setSampleFlag(SampleFlags sampleFlag);

Q_SIGNALS:
    void sampleEnumChanged(Sample sampleEnum);
    void sampleFlagChanged(SampleFlags sampleFlag);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Foo::SampleFlags)

#endif // FOO_H
