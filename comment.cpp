#include "comment.h"
#include "ui_comment.h"

#include <QTime>
#include <QDate>
#include <QMessageBox>
#include <QFile>

comment::comment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::comment)
{
    ui->setupUi(this);
}

comment::~comment()
{
    delete ui;
}

void comment::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "No comment was provided. Try again.");
    } else {
        this->hide();
        QMessageBox::information(this, "Success", "Comment was succesfully recorded");

        QFile file ("C:/Users/pacow/OneDrive/Desktop/log.txt");
        if (!file.open(QIODevice::Append)) {
            QMessageBox::warning(this, "warning", "File not open");
        }
        QTextStream out(&file);

        QTime time = QTime::currentTime();
        QDate date = QDate::currentDate();
        QString time_text = date.toString("MM/dd/yyyy") + " " +time.toString("hh:mm:ss");
        time_text += ui->lineEdit->text() + "\n";
        out << time_text;
        file.flush();
        file.close();
    }
}

