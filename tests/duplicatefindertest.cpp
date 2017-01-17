#include "duplicatefindertest.h"

using namespace std;

DuplicateFinderTest::DuplicateFinderTest()
{

}


void DuplicateFinderTest::test_find_duplicates()
{
    DuplicateFinder finder("samples/");

    list<Duplicate> dups = finder.find_duplicates();

    foreach(Duplicate dup, dups)
        cout << dup.original + " |||| " + dup.duplicate << endl;

    QVERIFY2(dups.size() > 0, "No duplicates were found inside the samples folder");
}
