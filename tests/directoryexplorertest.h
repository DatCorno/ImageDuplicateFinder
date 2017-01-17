#ifndef DIRECTORYEXPLORERTEST_H
#define DIRECTORYEXPLORERTEST_H

#include <QObject>
#include <QtTest>
#include <string>
#include "directoryexplorer.h"

class DirectoryExplorerTest : public QObject
{
    Q_OBJECT
public:
    DirectoryExplorerTest();

signals:

private slots:
    void test_is_image();
    void test_get_all_images();
};

#endif // DIRECTORYEXPLORERTEST_H
