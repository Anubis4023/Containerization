#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "balance_upload.h"
#include "login.h"
#include "comment.h"

#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    loading = new Dialog(this);
    loading->show();
}




void MainWindow::on_pushButton_clicked()
{
    //this->setVisible(false);
    move = new balance_upload(this);
    move->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    Login login;
    login.isModal();
    login.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    comment com;
    com.isModal();
    com.exec();
}

