#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QTime>
#include <QDate>
#include <QFile>
#include <QTextStream>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "No username was provided. Try again.");
    } else {
        this->hide();
        QMessageBox::information(this, "Success", "Login was succesful");

        QFile file ("C:/Users/pacow/OneDrive/Desktop/log.txt");
        if (!file.open(QIODevice::Append)) {
            QMessageBox::warning(this, "warning", "File not open");
        }
        QTextStream out(&file);

        QTime time = QTime::currentTime();
        QDate date = QDate::currentDate();
        QString time_text = date.toString("MM/dd/yyyy") + " " +time.toString("hh:mm:ss");
        time_text += " " + ui->lineEdit->text() + " signs in\n";
        out << time_text;
        file.flush();
        file.close();


    }
}

