#include "mainwindow.h"
#include "ui_mainwindow.h"

//constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

//destructor
MainWindow::~MainWindow()
{
    delete ui;
}


//actions for New button
void MainWindow::on_actionNew_triggered()
{
    //setting empty file name
    rFilename = "";
    ui->textEdit->setPlainText("");

}

void MainWindow::on_actionOpen_triggered()
{
    //creating new window with caption "Open File" for the newly created window
    QString file = QFileDialog::getOpenFileName(this,"Open File");

    if(!file.isEmpty()) {
        //creating file stream
        QFile fileStream(file);

        //open file in read-only mode
        if(fileStream.open(QFile::ReadOnly | QFile::Text)) {
            rFilename = file;
            QTextStream inp(&fileStream);

            //assigning a qstring which contains all contents of text-stream inp
            QString str = inp.readAll();

            fileStream.close();

            //writing the contents of the the opened file on screen
            ui->textEdit->setPlainText(str);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFile fileStream(rFilename);
    if(fileStream.open(QFile::WriteOnly | QFile::Text)) {

        //creating output stream
        QTextStream out(&fileStream);

        //ostream in given file
        out<< ui->textEdit->toPlainText();

        fileStream.flush();
        fileStream.close();
    }

}

void MainWindow::on_actionSave_AS_triggered()
{
    QString file = QFileDialog::getSaveFileName(this,"Open File");

    if(!file.isEmpty()) {
        //set the filename to current opened file
        rFilename = file;

        //functionality same as on_actionSave_triggered function except rFilename contains custom name
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionBold_triggered()
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeCharFormat(format);

}

void MainWindow::on_actionUnbold_triggered()
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Thin);

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeCharFormat(format);


}
