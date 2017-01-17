#include "directoryexplorertest.h"

using namespace std;

DirectoryExplorerTest::DirectoryExplorerTest()
{

}

void DirectoryExplorerTest::test_is_image()
{
    QFileInfo info(QString("samples/sample1.jpg"));

    QVERIFY2(is_image(info.absoluteFilePath().toStdString()), "Error on detecting an image, sample1.jpg is an image");
}

void DirectoryExplorerTest::test_get_all_images()
{
    auto paths = get_all_images("samples/");

    QVERIFY2(paths.size() > 0, "No images were found inside samples");
}
