#include "include\mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->file_finder_button, SIGNAL(clicked()), this, SLOT(open_file_finder()));
}

void MainWindow::open_file_finder()
{
    QFileDialog *file_finder = new QFileDialog();
    file_finder->setFileMode(QFileDialog::Directory);
    QString file_name = file_finder->getExistingDirectory(this, tr("Choose directory"));

    cout << file_name.toStdString() << endl;

    delete file_finder;
}

void MainWindow::find_duplicate()
{
}

MainWindow::~MainWindow()
{
    delete ui;
}
