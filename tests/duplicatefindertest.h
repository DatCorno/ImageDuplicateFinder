#ifndef DUPLICATEFINDERTEST_H
#define DUPLICATEFINDERTEST_H

#include <QtTest>
#include <iostream>
#include "duplicatefinder.h"

class DuplicateFinderTest : public QObject{
    Q_OBJECT

public:
    DuplicateFinderTest();

signals:

private slots:
    void test_find_duplicates();
};


#endif // DUPLICATEFINDERTEST_H
