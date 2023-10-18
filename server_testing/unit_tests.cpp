#include <QtTest>

// add necessary includes here

QByteArray parse(QString request);

class unit_tests : public QObject
{
    Q_OBJECT

public:
    unit_tests();
    ~unit_tests();

private slots:
    void test_case1();
    void test_case2();
};

unit_tests::unit_tests()
{

}

unit_tests::~unit_tests()
{

}

void unit_tests::test_case1()
{
    QVERIFY2(parse("Wrong request") == QByteArray("0"), "Check parse");
}

void unit_tests::test_case2()
{
    QVERIFY2(typeid(parse("Wrong request")).name() == QString("10QByteArray"), "Check parse");
}

QTEST_APPLESS_MAIN(unit_tests)

#include "unit_tests.moc"
