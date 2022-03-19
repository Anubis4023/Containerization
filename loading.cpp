#include "loading.h"
#include <QMessageBox>
#include "movements.h"

using namespace std;



Loading::Loading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
}

Loading::~Loading()
{
    delete ui;
}

bool Loading::isNumber(const std::string& str)
{
  char* ptr;
  strtol(str.c_str(), &ptr, 10);
  return *ptr == '\0';
}

void Loading::on_pushButton_clicked()
{
    if (!ui->name->text().isEmpty() && !ui->weight->text().isEmpty()) {
        if (!isNumber(ui->weight->text().toStdString())) {
            QMessageBox::critical(this, "Error", "Weight must be only integers");
            return;
        }
        string name = ui->name->text().toStdString();
        int weight = stoi(ui->weight->text().toStdString());

        if (weight < 1 || weight > 99999) {
            QMessageBox::critical(this, "Error", "Weight must be integer within 1 - 99999");
        } else {
            QString colon = ": ";
            ui->listWidget->addItem(ui->name->text() + colon + ui->weight->text());

            Container temp;
            temp.name = name;
            temp.weight = weight;
            onload.push_back(temp);

            ui->name->clear();
            ui->weight->clear();
        }
    } else {
        QMessageBox::critical(this, "Error", "Name or weight not entered. Try again");
    }
}


void Loading::on_pushButton_2_clicked()
{
    this->setVisible(false);
    move = new movements(this);
    move->show();
}

