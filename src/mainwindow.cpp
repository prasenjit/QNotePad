#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->MainTextArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->MainTextArea->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream readFile(&file);
    QString text = readFile.readAll();
    ui->MainTextArea->setText(text);

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream writeFile(&file);
    QString text = ui->MainTextArea->toPlainText();
    writeFile << text;
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QPrintDialog::Rejected) {
        QMessageBox::warning(this, "Warning", "Cannot access printer");
    }
    ui->MainTextArea->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
