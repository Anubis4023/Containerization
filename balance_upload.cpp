 #include "balance_upload.h"
#include "ui_balance_upload.h"
#include "balancecalc.h"

#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QMessageBox>
#include <QTime>
#include <QDate>
#include <string>
#include <QFileDialog>


using namespace std;

QString file_name;
vector<Container> weights;

balance_upload::balance_upload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::balance_upload)
{
    ui->setupUi(this);
}

balance_upload::~balance_upload()
{
    delete ui;
}

void balance_upload::on_pushButton_clicked()
{
    file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://Users/pacow/OneDrive/Desktop");
    //QFile file (file_n);
    //weights.clear();
    //QString file_name = file.mid(32, file.size() - 32);
    //ui->pushButton->setText(file_name);
    ui->label->setText(file_name);
    //QTextStream in(&file);
    //string name;


    //vector<vector<Container>> ship (ROW, vector<Container> (COLUMN, Container())); //Make empty ship grid
           //Make list for containers on the ship
           //cout << "got here" << endl;
           //ifstream manifest ("manifest.txt"); //Populate the grid with containers
           QFile manifest(file_name);
           if (manifest.open(QFile::ReadOnly)) {
               cout << "open" << endl;
           } else {
               cout << "FAILURE" << endl;
           }
           QTextStream in(&manifest);

           //char buffer[11]; //Size of string that is before the weight
           //char buffer3[3];
           //char buff_char;
           string weight_string;
           string name;

           int row = 0;
           for (int i = ROW-1; i > -1; --i) {
               ++row;
               for (int j = 0; j < COLUMN; ++j) {
                   //Store the position in each Container object
                   ship[i][j].row = row;
                   ship[i][j].column = j+1;

                   QString weight;
                   QString line = in.readLine(0);
                   QString qname;
                   //manifest.read(buffer, sizeof(buffer) - 1); //Gets rid of all the the characters before the weight
                   for (int h = 10; h < 15; ++h) {
                       weight += line.at(h);
                   }
                   //cout << weight.toStdString() << endl;
                   qname += line.mid(17, line.size() - 17);
                   //cout << qname.toStdString() << endl;
                   for (int h = 0; h < 5; ++h) { //This loop will get the five digit weight string and store it in weight_string
                       //manifest.get(buff_char);
                       //weight_string += buff_char;
                   }

                   string name = qname.toStdString();
                   //manifest.read(buffer3, sizeof(buffer3) - 1); //Gets rid of the characters before the name of the container(could be NAN or UNUSED)
                   //getline(manifest, name); //Gets the name and stores it in the string name
                   //Name and weight have been read from manifest, now will store the information in the Contianer class for that slot
                   ship[i][j].name = name; //assign name
                   //qInfo() << name;
                   if (name == " NAN") {
                       ship[i][j].weight = -1;
                   } else {
                       //cout << "i: " << i << " and j: " << j << endl;
                       //cout << weight_string << endl;
                       //cout << name << endl;
                       ship[i][j].weight = stoi(weight.toStdString()); //assign weight
                       //cout << "got through" << endl;
                   }
                   if (ship[i][j].weight > 0) { //If there is a container then add it to the list of containers for balancing
                       weights.push_back(ship[i][j]);
                   }
                   //weight_string = "";
                   weight = "";
                   }
           }
                   manifest.close();
}


void balance_upload::on_pushButton_2_clicked()
{
    if (ui->label->text() == "File selection name displayed here") {
        QMessageBox::critical(this, "Error", "File was not selected. Select file before proceeding.");
    } else {

        QFile file ("C://Users/pacow/OneDrive/Desktop/log.txt");
        if (!file.open(QIODevice::Append)) {
            QMessageBox::warning(this, "warning", "File not open");
        }
        QTextStream out(&file);

        QTime time = QTime::currentTime();
        QDate date = QDate::currentDate();
        QString time_text = date.toString("MM/dd/yyyy") + " " +time.toString("hh:mm:ss");
        time_text += " " + file_name + " is opened, there are " + QString::fromStdString(to_string(weights.size())) + " containers on the ship\n";
        out << time_text;
        file.flush();
        file.close();

        this->setVisible(false);
        next = new balanceCalc(this);
        next->show();
    }
}

