#include "balancecalc.h"
#include "ui_balancecalc.h"
#include "container.h"
#include "balance.h"
#include <QMessageBox>
#include <QTime>
#include <QDate>
#include <QFile>

Node answer;



balanceCalc::balanceCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::balanceCalc)
{
    ui->setupUi(this);
}

balanceCalc::~balanceCalc()
{
    delete ui;
}

void balanceCalc::on_pushButton_clicked()
{
    if (ui->listWidget->count() > 0) {
        return;
    }
    answer = searchG(ship, 1, offload, onload); //1 is balance, 2 is load/offload

    for (int i = 0; i < answer.position.size(); ++i) {
        if (answer.position.at(i).first == -1) {
            answer.position.at(i).first = 17;
        }

        if (answer.position.at(i).second == -1) {
            answer.position.at(i).second = 1;
        }
    }

    int iter = 1;
    for (int i = 0; i < answer.position.size(); i += 2) {
           QString move = QString::fromStdString(to_string(iter) + ". From position (" + to_string(abs(answer.position.at(i).first-8)) + ", " + to_string(answer.position.at(i).second+1) + ") to (" + to_string(abs(answer.position.at(i+1).first-8)) + ", " + to_string(answer.position.at(i+1).second+1) + ")");
             ui->listWidget->addItem(move);
             ++iter;
            //cout << "cost: " << answer.costMoves.at(i) << endl << endl;
    }
    ui->listWidget->addItem(QString::fromStdString("Estimated time: " + to_string(answer.gn)));
}


void balanceCalc::on_pushButton_2_clicked()
{
    if (ui->pushButton_2->text() == "Finish") {
        //output log that cycle is done
        //output a new manifest file
        new_manifest();

        QFile file ("C:/Users/pacow/OneDrive/Desktop/log.txt");
        if (!file.open(QIODevice::Append)) {
            QMessageBox::warning(this, "warning", "File not open");
        }
        QTextStream out(&file);

        QTime time = QTime::currentTime();
        QDate date = QDate::currentDate();
        QString time_text = date.toString("MM/dd/yyyy") + " " +time.toString("hh:mm:ss");
        time_text += " Finished a cycle. Manifest OUTBOUND.txt was written to desktop, and a reminder pop-up to operator to send file was displayed\n";
        out << time_text;
        file.flush();
        file.close();

        QMessageBox::information(this, "Reminder", "Please remember to send the new manifest file");

        this->hide();
    }

    ui->listWidget->takeItem(0);
    if (ui->listWidget->count() == 1) {
        ui->pushButton_2->setText("Finish");
    }
}

