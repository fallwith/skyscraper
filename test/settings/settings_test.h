#include "src/settings.h"

#include <QtTest/QtTest>

class TestSettings : public QObject {
    Q_OBJECT
public:
    TestSettings() {}
    ~TestSettings() {}
private slots:
    void configIniMain();
    void configIniPlatform();
    void configIniFrontend();
    void configIniScraper();
};
