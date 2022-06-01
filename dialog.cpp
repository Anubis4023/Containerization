#include "dialog.h"
#include "loading.h"

#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QList>

#include <string>
#include <iostream>
#include <vector>

using namespace std;

int ROW = 8;
int COLUMN = 12;
vector<Container> offload;
vector<Container> onload;
vector<vector<Container>> ship (ROW+2, vector<Container> (COLUMN, Container())); //Make empty ship grid
//vector<Container> weights;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    //ui->pushButton->setText()
    QString file_n = QFileDialog::getOpenFileName(this, "Open a file", "C://Users/pacow/OneDrive/Desktop");
    //QFile file (file_n);
    //QString file = "C://Users/pacow/OneDrive/Desktop/test_full_balance.txt";
    //QString file_name = file.mid(32, file.size() - 32);
    ui->pushButton->setText(file_n);
    //QTextStream in(&file);
    //string name;




    //vector<vector<Container>> ship (ROW, vector<Container> (COLUMN, Container())); //Make empty ship grid
           //weights; //Make list for containers on the ship
           //cout << "got here" << endl;
           //ifstream manifest ("manifest.txt"); //Populate the grid with containers
           QFile manifest(file_n);
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



                   if (ship[0][0].name != " UNUSED" && ship[0][0].name != " NAN") {
                       ui->_0_0->setText(QString::fromStdString(ship[0][0].name));
                    ui->_0_0->setToolTip(QString::fromStdString(ship[0][0].name));
                   }
                   if (ship[0][1].name != " UNUSED" && ship[0][1].name != " NAN") {
                       ui->_0_1->setText(QString::fromStdString(ship[0][1].name));
                    ui->_0_1->setToolTip(QString::fromStdString(ship[0][1].name));
                   }
                   if (ship[0][2].name != " UNUSED" && ship[0][2].name != " NAN") {
                       ui->_0_2->setText(QString::fromStdString(ship[0][2].name));
                    ui->_0_2->setToolTip(QString::fromStdString(ship[0][2].name));
                   }
                   if (ship[0][3].name != " UNUSED" && ship[0][3].name != " NAN") {
                       ui->_0_3->setText(QString::fromStdString(ship[0][3].name));
                    ui->_0_3->setToolTip(QString::fromStdString(ship[0][3].name));
                   }
                   if (ship[0][4].name != " UNUSED" && ship[0][4].name != " NAN") {
                       ui->_0_4->setText(QString::fromStdString(ship[0][4].name));
                    ui->_0_4->setToolTip(QString::fromStdString(ship[0][4].name));
                   }
                   if (ship[0][5].name != " UNUSED" && ship[0][5].name != " NAN") {
                       ui->_0_5->setText(QString::fromStdString(ship[0][5].name));
                    ui->_0_5->setToolTip(QString::fromStdString(ship[0][5].name));
                   }
                   if (ship[0][6].name != " UNUSED" && ship[0][6].name != " NAN") {
                       ui->_0_6->setText(QString::fromStdString(ship[0][6].name));
                    ui->_0_6->setToolTip(QString::fromStdString(ship[0][6].name));
                   }
                   if (ship[0][7].name != " UNUSED" && ship[0][7].name != " NAN") {
                       ui->_0_7->setText(QString::fromStdString(ship[0][7].name));
                    ui->_0_7->setToolTip(QString::fromStdString(ship[0][7].name));
                   }
                   if (ship[0][8].name != " UNUSED" && ship[0][8].name != " NAN") {
                       ui->_0_8->setText(QString::fromStdString(ship[0][8].name));
                    ui->_0_8->setToolTip(QString::fromStdString(ship[0][8].name));
                   }
                   if (ship[0][9].name != " UNUSED" && ship[0][9].name != " NAN") {
                       ui->_0_9->setText(QString::fromStdString(ship[0][9].name));
                    ui->_0_9->setToolTip(QString::fromStdString(ship[0][9].name));
                   }
                   if (ship[0][10].name != " UNUSED" && ship[0][10].name != " NAN") {
                       ui->_0_10->setText(QString::fromStdString(ship[0][10].name));
                    ui->_0_10->setToolTip(QString::fromStdString(ship[0][10].name));
                   }
                   if (ship[0][11].name != " UNUSED" && ship[0][11].name != " NAN") {
                       ui->_0_11->setText(QString::fromStdString(ship[0][11].name));
                    ui->_0_11->setToolTip(QString::fromStdString(ship[0][11].name));
                   }
                   if (ship[1][0].name != " UNUSED" && ship[1][0].name != " NAN") {
                       ui->_1_0->setText(QString::fromStdString(ship[1][0].name));
                    ui->_1_0->setToolTip(QString::fromStdString(ship[1][0].name));
                   }
                   if (ship[1][1].name != " UNUSED" && ship[1][1].name != " NAN") {
                       ui->_1_1->setText(QString::fromStdString(ship[1][1].name));
                    ui->_1_1->setToolTip(QString::fromStdString(ship[1][1].name));
                   }
                   if (ship[1][2].name != " UNUSED" && ship[1][2].name != " NAN") {
                       ui->_1_2->setText(QString::fromStdString(ship[1][2].name));
                    ui->_1_2->setToolTip(QString::fromStdString(ship[1][2].name));
                   }
                   if (ship[1][3].name != " UNUSED" && ship[1][3].name != " NAN") {
                       ui->_1_3->setText(QString::fromStdString(ship[1][3].name));
                    ui->_1_3->setToolTip(QString::fromStdString(ship[1][3].name));
                   }
                   if (ship[1][4].name != " UNUSED" && ship[1][4].name != " NAN") {
                       ui->_1_4->setText(QString::fromStdString(ship[1][4].name));
                    ui->_1_4->setToolTip(QString::fromStdString(ship[1][4].name));
                   }
                   if (ship[1][5].name != " UNUSED" && ship[1][5].name != " NAN") {
                       ui->_1_5->setText(QString::fromStdString(ship[1][5].name));
                    ui->_1_5->setToolTip(QString::fromStdString(ship[1][5].name));
                   }
                   if (ship[1][6].name != " UNUSED" && ship[1][6].name != " NAN") {
                       ui->_1_6->setText(QString::fromStdString(ship[1][6].name));
                    ui->_1_6->setToolTip(QString::fromStdString(ship[1][6].name));
                   }
                   if (ship[1][7].name != " UNUSED" && ship[1][7].name != " NAN") {
                       ui->_1_7->setText(QString::fromStdString(ship[1][7].name));
                    ui->_1_7->setToolTip(QString::fromStdString(ship[1][7].name));
                   }
                   if (ship[1][8].name != " UNUSED" && ship[1][8].name != " NAN") {
                       ui->_1_8->setText(QString::fromStdString(ship[1][8].name));
                    ui->_1_8->setToolTip(QString::fromStdString(ship[1][8].name));
                   }
                   if (ship[1][9].name != " UNUSED" && ship[1][9].name != " NAN") {
                       ui->_1_9->setText(QString::fromStdString(ship[1][9].name));
                    ui->_1_9->setToolTip(QString::fromStdString(ship[1][9].name));
                   }
                   if (ship[1][10].name != " UNUSED" && ship[1][10].name != " NAN") {
                       ui->_1_10->setText(QString::fromStdString(ship[1][10].name));
                    ui->_1_10->setToolTip(QString::fromStdString(ship[1][10].name));
                   }
                   if (ship[1][11].name != " UNUSED" && ship[1][11].name != " NAN") {
                       ui->_1_11->setText(QString::fromStdString(ship[1][11].name));
                    ui->_1_11->setToolTip(QString::fromStdString(ship[1][11].name));
                   }
                   if (ship[2][0].name != " UNUSED" && ship[2][0].name != " NAN") {
                       ui->_2_0->setText(QString::fromStdString(ship[2][0].name));
                    ui->_2_0->setToolTip(QString::fromStdString(ship[2][0].name));
                   }
                   if (ship[2][1].name != " UNUSED" && ship[2][1].name != " NAN") {
                       ui->_2_1->setText(QString::fromStdString(ship[2][1].name));
                    ui->_2_1->setToolTip(QString::fromStdString(ship[2][1].name));
                   }
                   if (ship[2][2].name != " UNUSED" && ship[2][2].name != " NAN") {
                       ui->_2_2->setText(QString::fromStdString(ship[2][2].name));
                    ui->_2_2->setToolTip(QString::fromStdString(ship[2][2].name));
                   }
                   if (ship[2][3].name != " UNUSED" && ship[2][3].name != " NAN") {
                       ui->_2_3->setText(QString::fromStdString(ship[2][3].name));
                    ui->_2_3->setToolTip(QString::fromStdString(ship[2][3].name));
                   }
                   if (ship[2][4].name != " UNUSED" && ship[2][4].name != " NAN") {
                       ui->_2_4->setText(QString::fromStdString(ship[2][4].name));
                    ui->_2_4->setToolTip(QString::fromStdString(ship[2][4].name));
                   }
                   if (ship[2][5].name != " UNUSED" && ship[2][5].name != " NAN") {
                       ui->_2_5->setText(QString::fromStdString(ship[2][5].name));
                    ui->_2_5->setToolTip(QString::fromStdString(ship[2][5].name));
                   }
                   if (ship[2][6].name != " UNUSED" && ship[2][6].name != " NAN") {
                       ui->_2_6->setText(QString::fromStdString(ship[2][6].name));
                    ui->_2_6->setToolTip(QString::fromStdString(ship[2][6].name));
                   }
                   if (ship[2][7].name != " UNUSED" && ship[2][7].name != " NAN") {
                       ui->_2_7->setText(QString::fromStdString(ship[2][7].name));
                    ui->_2_7->setToolTip(QString::fromStdString(ship[2][7].name));
                   }
                   if (ship[2][8].name != " UNUSED" && ship[2][8].name != " NAN") {
                       ui->_2_8->setText(QString::fromStdString(ship[2][8].name));
                    ui->_2_8->setToolTip(QString::fromStdString(ship[2][8].name));
                   }
                   if (ship[2][9].name != " UNUSED" && ship[2][9].name != " NAN") {
                       ui->_2_9->setText(QString::fromStdString(ship[2][9].name));
                    ui->_2_9->setToolTip(QString::fromStdString(ship[2][9].name));
                   }
                   if (ship[2][10].name != " UNUSED" && ship[2][10].name != " NAN") {
                       ui->_2_10->setText(QString::fromStdString(ship[2][10].name));
                    ui->_2_10->setToolTip(QString::fromStdString(ship[2][10].name));
                   }
                   if (ship[2][11].name != " UNUSED" && ship[2][11].name != " NAN") {
                       ui->_2_11->setText(QString::fromStdString(ship[2][11].name));
                    ui->_2_11->setToolTip(QString::fromStdString(ship[2][11].name));
                   }
                   if (ship[3][0].name != " UNUSED" && ship[3][0].name != " NAN") {
                       ui->_3_0->setText(QString::fromStdString(ship[3][0].name));
                    ui->_3_0->setToolTip(QString::fromStdString(ship[3][0].name));
                   }
                   if (ship[3][1].name != " UNUSED" && ship[3][1].name != " NAN") {
                       ui->_3_1->setText(QString::fromStdString(ship[3][1].name));
                    ui->_3_1->setToolTip(QString::fromStdString(ship[3][1].name));
                   }
                   if (ship[3][2].name != " UNUSED" && ship[3][2].name != " NAN") {
                       ui->_3_2->setText(QString::fromStdString(ship[3][2].name));
                    ui->_3_2->setToolTip(QString::fromStdString(ship[3][2].name));
                   }
                   if (ship[3][3].name != " UNUSED" && ship[3][3].name != " NAN") {
                       ui->_3_3->setText(QString::fromStdString(ship[3][3].name));
                    ui->_3_3->setToolTip(QString::fromStdString(ship[3][3].name));
                   }
                   if (ship[3][4].name != " UNUSED" && ship[3][4].name != " NAN") {
                       ui->_3_4->setText(QString::fromStdString(ship[3][4].name));
                    ui->_3_4->setToolTip(QString::fromStdString(ship[3][4].name));
                   }
                   if (ship[3][5].name != " UNUSED" && ship[3][5].name != " NAN") {
                       ui->_3_5->setText(QString::fromStdString(ship[3][5].name));
                    ui->_3_5->setToolTip(QString::fromStdString(ship[3][5].name));
                   }
                   if (ship[3][6].name != " UNUSED" && ship[3][6].name != " NAN") {
                       ui->_3_6->setText(QString::fromStdString(ship[3][6].name));
                    ui->_3_6->setToolTip(QString::fromStdString(ship[3][6].name));
                   }
                   if (ship[3][7].name != " UNUSED" && ship[3][7].name != " NAN") {
                       ui->_3_7->setText(QString::fromStdString(ship[3][7].name));
                    ui->_3_7->setToolTip(QString::fromStdString(ship[3][7].name));
                   }
                   if (ship[3][8].name != " UNUSED" && ship[3][8].name != " NAN") {
                       ui->_3_8->setText(QString::fromStdString(ship[3][8].name));
                    ui->_3_8->setToolTip(QString::fromStdString(ship[3][8].name));
                   }
                   if (ship[3][9].name != " UNUSED" && ship[3][9].name != " NAN") {
                       ui->_3_9->setText(QString::fromStdString(ship[3][9].name));
                    ui->_3_9->setToolTip(QString::fromStdString(ship[3][9].name));
                   }
                   if (ship[3][10].name != " UNUSED" && ship[3][10].name != " NAN") {
                       ui->_3_10->setText(QString::fromStdString(ship[3][10].name));
                    ui->_3_10->setToolTip(QString::fromStdString(ship[3][10].name));
                   }
                   if (ship[3][11].name != " UNUSED" && ship[3][11].name != " NAN") {
                       ui->_3_11->setText(QString::fromStdString(ship[3][11].name));
                    ui->_3_11->setToolTip(QString::fromStdString(ship[3][11].name));
                   }
                   if (ship[4][0].name != " UNUSED" && ship[4][0].name != " NAN") {
                       ui->_4_0->setText(QString::fromStdString(ship[4][0].name));
                    ui->_4_0->setToolTip(QString::fromStdString(ship[4][0].name));
                   }
                   if (ship[4][1].name != " UNUSED" && ship[4][1].name != " NAN") {
                       ui->_4_1->setText(QString::fromStdString(ship[4][1].name));
                    ui->_4_1->setToolTip(QString::fromStdString(ship[4][1].name));
                   }
                   if (ship[4][2].name != " UNUSED" && ship[4][2].name != " NAN") {
                       ui->_4_2->setText(QString::fromStdString(ship[4][2].name));
                    ui->_4_2->setToolTip(QString::fromStdString(ship[4][2].name));
                   }
                   if (ship[4][3].name != " UNUSED" && ship[4][3].name != " NAN") {
                       ui->_4_3->setText(QString::fromStdString(ship[4][3].name));
                    ui->_4_3->setToolTip(QString::fromStdString(ship[4][3].name));
                   }
                   if (ship[4][4].name != " UNUSED" && ship[4][4].name != " NAN") {
                       ui->_4_4->setText(QString::fromStdString(ship[4][4].name));
                    ui->_4_4->setToolTip(QString::fromStdString(ship[4][4].name));
                   }
                   if (ship[4][5].name != " UNUSED" && ship[4][5].name != " NAN") {
                       ui->_4_5->setText(QString::fromStdString(ship[4][5].name));
                    ui->_4_5->setToolTip(QString::fromStdString(ship[4][5].name));
                   }
                   if (ship[4][6].name != " UNUSED" && ship[4][6].name != " NAN") {
                       ui->_4_6->setText(QString::fromStdString(ship[4][6].name));
                    ui->_4_6->setToolTip(QString::fromStdString(ship[4][6].name));
                   }
                   if (ship[4][7].name != " UNUSED" && ship[4][7].name != " NAN") {
                       ui->_4_7->setText(QString::fromStdString(ship[4][7].name));
                    ui->_4_7->setToolTip(QString::fromStdString(ship[4][7].name));
                   }
                   if (ship[4][8].name != " UNUSED" && ship[4][8].name != " NAN") {
                       ui->_4_8->setText(QString::fromStdString(ship[4][8].name));
                    ui->_4_8->setToolTip(QString::fromStdString(ship[4][8].name));
                   }
                   if (ship[4][9].name != " UNUSED" && ship[4][9].name != " NAN") {
                       ui->_4_9->setText(QString::fromStdString(ship[4][9].name));
                    ui->_4_9->setToolTip(QString::fromStdString(ship[4][9].name));
                   }
                   if (ship[4][10].name != " UNUSED" && ship[4][10].name != " NAN") {
                       ui->_4_10->setText(QString::fromStdString(ship[4][10].name));
                    ui->_4_10->setToolTip(QString::fromStdString(ship[4][10].name));
                   }
                   if (ship[4][11].name != " UNUSED" && ship[4][11].name != " NAN") {
                       ui->_4_11->setText(QString::fromStdString(ship[4][11].name));
                    ui->_4_11->setToolTip(QString::fromStdString(ship[4][11].name));
                   }
                   if (ship[5][0].name != " UNUSED" && ship[5][0].name != " NAN") {
                       ui->_5_0->setText(QString::fromStdString(ship[5][0].name));
                    ui->_5_0->setToolTip(QString::fromStdString(ship[5][0].name));
                   }
                   if (ship[5][1].name != " UNUSED" && ship[5][1].name != " NAN") {
                       ui->_5_1->setText(QString::fromStdString(ship[5][1].name));
                    ui->_5_1->setToolTip(QString::fromStdString(ship[5][1].name));
                   }
                   if (ship[5][2].name != " UNUSED" && ship[5][2].name != " NAN") {
                       ui->_5_2->setText(QString::fromStdString(ship[5][2].name));
                    ui->_5_2->setToolTip(QString::fromStdString(ship[5][2].name));
                   }
                   if (ship[5][3].name != " UNUSED" && ship[5][3].name != " NAN") {
                       ui->_5_3->setText(QString::fromStdString(ship[5][3].name));
                    ui->_5_3->setToolTip(QString::fromStdString(ship[5][3].name));
                   }
                   if (ship[5][4].name != " UNUSED" && ship[5][4].name != " NAN") {
                       ui->_5_4->setText(QString::fromStdString(ship[5][4].name));
                    ui->_5_4->setToolTip(QString::fromStdString(ship[5][4].name));
                   }
                   if (ship[5][5].name != " UNUSED" && ship[5][5].name != " NAN") {
                       ui->_5_5->setText(QString::fromStdString(ship[5][5].name));
                    ui->_5_5->setToolTip(QString::fromStdString(ship[5][5].name));
                   }
                   if (ship[5][6].name != " UNUSED" && ship[5][6].name != " NAN") {
                       ui->_5_6->setText(QString::fromStdString(ship[5][6].name));
                    ui->_5_6->setToolTip(QString::fromStdString(ship[5][6].name));
                   }
                   if (ship[5][7].name != " UNUSED" && ship[5][7].name != " NAN") {
                       ui->_5_7->setText(QString::fromStdString(ship[5][7].name));
                    ui->_5_7->setToolTip(QString::fromStdString(ship[5][7].name));
                   }
                   if (ship[5][8].name != " UNUSED" && ship[5][8].name != " NAN") {
                       ui->_5_8->setText(QString::fromStdString(ship[5][8].name));
                    ui->_5_8->setToolTip(QString::fromStdString(ship[5][8].name));
                   }
                   if (ship[5][9].name != " UNUSED" && ship[5][9].name != " NAN") {
                       ui->_5_9->setText(QString::fromStdString(ship[5][9].name));
                    ui->_5_9->setToolTip(QString::fromStdString(ship[5][9].name));
                   }
                   if (ship[5][10].name != " UNUSED" && ship[5][10].name != " NAN") {
                       ui->_5_10->setText(QString::fromStdString(ship[5][10].name));
                    ui->_5_10->setToolTip(QString::fromStdString(ship[5][10].name));
                   }
                   if (ship[5][11].name != " UNUSED" && ship[5][11].name != " NAN") {
                       ui->_5_11->setText(QString::fromStdString(ship[5][11].name));
                    ui->_5_11->setToolTip(QString::fromStdString(ship[5][11].name));
                   }
                   if (ship[6][0].name != " UNUSED" && ship[6][0].name != " NAN") {
                       ui->_6_0->setText(QString::fromStdString(ship[6][0].name));
                    ui->_6_0->setToolTip(QString::fromStdString(ship[6][0].name));
                   }
                   if (ship[6][1].name != " UNUSED" && ship[6][1].name != " NAN") {
                       ui->_6_1->setText(QString::fromStdString(ship[6][1].name));
                    ui->_6_1->setToolTip(QString::fromStdString(ship[6][1].name));
                   }
                   if (ship[6][2].name != " UNUSED" && ship[6][2].name != " NAN") {
                       ui->_6_2->setText(QString::fromStdString(ship[6][2].name));
                    ui->_6_2->setToolTip(QString::fromStdString(ship[6][2].name));
                   }
                   if (ship[6][3].name != " UNUSED" && ship[6][3].name != " NAN") {
                       ui->_6_3->setText(QString::fromStdString(ship[6][3].name));
                    ui->_6_3->setToolTip(QString::fromStdString(ship[6][3].name));
                   }
                   if (ship[6][4].name != " UNUSED" && ship[6][4].name != " NAN") {
                       ui->_6_4->setText(QString::fromStdString(ship[6][4].name));
                    ui->_6_4->setToolTip(QString::fromStdString(ship[6][4].name));
                   }
                   if (ship[6][5].name != " UNUSED" && ship[6][5].name != " NAN") {
                       ui->_6_5->setText(QString::fromStdString(ship[6][5].name));
                    ui->_6_5->setToolTip(QString::fromStdString(ship[6][5].name));
                   }
                   if (ship[6][6].name != " UNUSED" && ship[6][6].name != " NAN") {
                       ui->_6_6->setText(QString::fromStdString(ship[6][6].name));
                    ui->_6_6->setToolTip(QString::fromStdString(ship[6][6].name));
                   }
                   if (ship[6][7].name != " UNUSED" && ship[6][7].name != " NAN") {
                       ui->_6_7->setText(QString::fromStdString(ship[6][7].name));
                    ui->_6_7->setToolTip(QString::fromStdString(ship[6][7].name));
                   }
                   if (ship[6][8].name != " UNUSED" && ship[6][8].name != " NAN") {
                       ui->_6_8->setText(QString::fromStdString(ship[6][8].name));
                    ui->_6_8->setToolTip(QString::fromStdString(ship[6][8].name));
                   }
                   if (ship[6][9].name != " UNUSED" && ship[6][9].name != " NAN") {
                       ui->_6_9->setText(QString::fromStdString(ship[6][9].name));
                    ui->_6_9->setToolTip(QString::fromStdString(ship[6][9].name));
                   }
                   if (ship[6][10].name != " UNUSED" && ship[6][10].name != " NAN") {
                       ui->_6_10->setText(QString::fromStdString(ship[6][10].name));
                    ui->_6_10->setToolTip(QString::fromStdString(ship[6][10].name));
                   }
                   if (ship[6][11].name != " UNUSED" && ship[6][11].name != " NAN") {
                       ui->_6_11->setText(QString::fromStdString(ship[6][11].name));
                    ui->_6_11->setToolTip(QString::fromStdString(ship[6][11].name));
                   }
                   if (ship[7][0].name != " UNUSED" && ship[7][0].name != " NAN") {
                       ui->_7_0->setText(QString::fromStdString(ship[7][0].name));
                    ui->_7_0->setToolTip(QString::fromStdString(ship[7][0].name));
                   }
                   if (ship[7][1].name != " UNUSED" && ship[7][1].name != " NAN") {
                       ui->_7_1->setText(QString::fromStdString(ship[7][1].name));
                    ui->_7_1->setToolTip(QString::fromStdString(ship[7][1].name));
                   }
                   if (ship[7][2].name != " UNUSED" && ship[7][2].name != " NAN") {
                       ui->_7_2->setText(QString::fromStdString(ship[7][2].name));
                    ui->_7_2->setToolTip(QString::fromStdString(ship[7][2].name));
                   }
                   if (ship[7][3].name != " UNUSED" && ship[7][3].name != " NAN") {
                       ui->_7_3->setText(QString::fromStdString(ship[7][3].name));
                    ui->_7_3->setToolTip(QString::fromStdString(ship[7][3].name));
                   }
                   if (ship[7][4].name != " UNUSED" && ship[7][4].name != " NAN") {
                       ui->_7_4->setText(QString::fromStdString(ship[7][4].name));
                    ui->_7_4->setToolTip(QString::fromStdString(ship[7][4].name));
                   }
                   if (ship[7][5].name != " UNUSED" && ship[7][5].name != " NAN") {
                       ui->_7_5->setText(QString::fromStdString(ship[7][5].name));
                    ui->_7_5->setToolTip(QString::fromStdString(ship[7][5].name));
                   }
                   if (ship[7][6].name != " UNUSED" && ship[7][6].name != " NAN") {
                       ui->_7_6->setText(QString::fromStdString(ship[7][6].name));
                    ui->_7_6->setToolTip(QString::fromStdString(ship[7][6].name));
                   }
                   if (ship[7][7].name != " UNUSED" && ship[7][7].name != " NAN") {
                       ui->_7_7->setText(QString::fromStdString(ship[7][7].name));
                    ui->_7_7->setToolTip(QString::fromStdString(ship[7][7].name));
                   }
                   if (ship[7][8].name != " UNUSED" && ship[7][8].name != " NAN") {
                       ui->_7_8->setText(QString::fromStdString(ship[7][8].name));
                    ui->_7_8->setToolTip(QString::fromStdString(ship[7][8].name));
                   }
                   if (ship[7][9].name != " UNUSED" && ship[7][9].name != " NAN") {
                       ui->_7_9->setText(QString::fromStdString(ship[7][9].name));
                    ui->_7_9->setToolTip(QString::fromStdString(ship[7][9].name));
                   }
                   if (ship[7][10].name != " UNUSED" && ship[7][10].name != " NAN") {
                       ui->_7_10->setText(QString::fromStdString(ship[7][10].name));
                    ui->_7_10->setToolTip(QString::fromStdString(ship[7][10].name));
                   }
                   if (ship[7][11].name != " UNUSED" && ship[7][11].name != " NAN") {
                       ui->_7_11->setText(QString::fromStdString(ship[7][11].name));
                    ui->_7_11->setToolTip(QString::fromStdString(ship[7][11].name));
                   }


                   QFile file_name ("C:/Users/pacow/OneDrive/Desktop/log.txt");
                   if (!file_name.open(QIODevice::Append)) {
                       QMessageBox::warning(this, "warning", "File not open");
                   }
                   QTextStream out(&file_name);

                   QTime time = QTime::currentTime();
                   QDate date = QDate::currentDate();
                   QString time_text = date.toString("MM/dd/yyyy") + " " +time.toString("hh:mm:ss");
                   time_text += " " + file_n + " is opened, there are " + QString::fromStdString(to_string(weights.size())) + " containers on the ship\n";
                   out << time_text;
                   file_name.flush();
                   file_name.close();

}



void Dialog::on_pushButton_2_clicked()
{
    Container temp;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if (ui->listWidget->item(i)) { //if it exists
            for (int j = 0; j < 8; ++j) {
                for (int a = 0; a < 8; ++a) {
                    if (ship[j][a].name == ui->listWidget->item(i)->text().toStdString()) {
                        temp.weight = ship[j][a].weight;
                        temp.name = ship[j][a].name;
                    }
                }
            }
            offload.push_back(temp);
        }
    }

    /*for (int i = 0; i < offload.size(); ++i) {
        cout << offload.at(i).name << endl;
    }*/
    this->setVisible(false);
    load = new Loading(this);
    load->show();

}

void Dialog::on__0_0_clicked()
{
    QString Qname = ui->_0_0->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_0->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_1_clicked()
{
    QString Qname = ui->_0_1->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_1->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_2_clicked()
{
    QString Qname = ui->_0_2->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_2->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_3_clicked()
{
    QString Qname = ui->_0_3->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_3->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_4_clicked()
{
    QString Qname = ui->_0_4->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_4->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_5_clicked()
{
    QString Qname = ui->_0_5->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_5->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_6_clicked()
{
    QString Qname = ui->_0_6->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_6->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_7_clicked()
{
    QString Qname = ui->_0_7->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_7->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_8_clicked()
{
    QString Qname = ui->_0_8->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_8->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_9_clicked()
{
    QString Qname = ui->_0_9->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_9->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_10_clicked()
{
    QString Qname = ui->_0_10->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_10->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__0_11_clicked()
{
    QString Qname = ui->_0_11->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_0_11->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_0_clicked()
{
    QString Qname = ui->_1_0->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_0->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_1_clicked()
{
    QString Qname = ui->_1_1->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_1->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_2_clicked()
{
    QString Qname = ui->_1_2->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_2->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_3_clicked()
{
    QString Qname = ui->_1_3->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_3->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_4_clicked()
{
    QString Qname = ui->_1_4->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_4->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_5_clicked()
{
    QString Qname = ui->_1_5->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_5->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_6_clicked()
{
    QString Qname = ui->_1_6->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_6->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_7_clicked()
{
    QString Qname = ui->_1_7->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_7->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_8_clicked()
{
    QString Qname = ui->_1_8->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_8->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_9_clicked()
{
    QString Qname = ui->_1_9->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_9->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_10_clicked()
{
    QString Qname = ui->_1_10->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_10->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__1_11_clicked()
{
    QString Qname = ui->_1_11->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_1_11->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_0_clicked()
{
    QString Qname = ui->_2_0->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_0->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_1_clicked()
{
    QString Qname = ui->_2_1->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_1->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_2_clicked()
{
    QString Qname = ui->_2_2->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_2->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_3_clicked()
{
    QString Qname = ui->_2_3->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_3->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_4_clicked()
{
    QString Qname = ui->_2_4->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_4->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_5_clicked()
{
    QString Qname = ui->_2_5->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_5->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_6_clicked()
{
    QString Qname = ui->_2_6->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_6->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_7_clicked()
{
    QString Qname = ui->_2_7->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_7->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_8_clicked()
{
    QString Qname = ui->_2_8->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_8->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_9_clicked()
{
    QString Qname = ui->_2_9->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_9->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_10_clicked()
{
    QString Qname = ui->_2_10->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_10->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__2_11_clicked()
{
    QString Qname = ui->_2_11->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_2_11->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_0_clicked()
{
    QString Qname = ui->_3_0->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_0->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_1_clicked()
{
    QString Qname = ui->_3_1->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_1->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_2_clicked()
{
    QString Qname = ui->_3_2->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_2->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_3_clicked()
{
    QString Qname = ui->_3_3->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_3->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_4_clicked()
{
    QString Qname = ui->_3_4->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_4->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_5_clicked()
{
    QString Qname = ui->_3_5->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_5->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_6_clicked()
{
    QString Qname = ui->_3_6->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_6->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_7_clicked()
{
    QString Qname = ui->_3_7->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_7->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_8_clicked()
{
    QString Qname = ui->_3_8->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_8->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_9_clicked()
{
    QString Qname = ui->_3_9->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_9->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_10_clicked()
{
    QString Qname = ui->_3_10->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_10->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__3_11_clicked()
{
    QString Qname = ui->_3_11->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_3_11->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_0_clicked()
{
    QString Qname = ui->_4_0->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_0->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_1_clicked()
{
    QString Qname = ui->_4_1->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_1->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_2_clicked()
{
    QString Qname = ui->_4_2->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_2->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_3_clicked()
{
    QString Qname = ui->_4_3->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_3->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_4_clicked()
{
    QString Qname = ui->_4_4->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_4->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_5_clicked()
{
    QString Qname = ui->_4_5->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_5->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_6_clicked()
{
    QString Qname = ui->_4_6->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_6->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_7_clicked()
{
    QString Qname = ui->_4_7->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_7->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_8_clicked()
{
    QString Qname = ui->_4_8->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_8->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_9_clicked()
{
    QString Qname = ui->_4_9->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_9->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_10_clicked()
{
    QString Qname = ui->_4_10->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_10->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__4_11_clicked()
{
    QString Qname = ui->_4_11->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_4_11->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_0_clicked()
{
    QString Qname = ui->_5_0->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_0->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_1_clicked()
{
    QString Qname = ui->_5_1->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_1->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_2_clicked()
{
    QString Qname = ui->_5_2->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_2->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_3_clicked()
{
    QString Qname = ui->_5_3->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_3->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_4_clicked()
{
    QString Qname = ui->_5_4->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_4->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_5_clicked()
{
    QString Qname = ui->_5_5->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_5->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_6_clicked()
{
    QString Qname = ui->_5_6->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_6->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_7_clicked()
{
    QString Qname = ui->_5_7->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_7->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_8_clicked()
{
    QString Qname = ui->_5_8->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_8->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_9_clicked()
{
    QString Qname = ui->_5_9->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_9->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_10_clicked()
{
    QString Qname = ui->_5_10->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_10->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__5_11_clicked()
{
    QString Qname = ui->_5_11->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_5_11->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_0_clicked()
{
    QString Qname = ui->_6_0->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_0->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_1_clicked()
{
    QString Qname = ui->_6_1->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_1->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_2_clicked()
{
    QString Qname = ui->_6_2->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_2->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_3_clicked()
{
    QString Qname = ui->_6_3->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_3->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_4_clicked()
{
    QString Qname = ui->_6_4->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_4->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_5_clicked()
{
    QString Qname = ui->_6_5->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_5->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_6_clicked()
{
    QString Qname = ui->_6_6->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_6->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_7_clicked()
{
    QString Qname = ui->_6_7->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_7->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_8_clicked()
{
    QString Qname = ui->_6_8->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_8->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_9_clicked()
{
    QString Qname = ui->_6_9->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_9->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_10_clicked()
{
    QString Qname = ui->_6_10->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_10->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__6_11_clicked()
{
    QString Qname = ui->_6_11->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_6_11->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_0_clicked()
{
    QString Qname = ui->_7_0->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_0->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_1_clicked()
{
    QString Qname = ui->_7_1->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_1->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_2_clicked()
{
    QString Qname = ui->_7_2->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_2->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_3_clicked()
{
    QString Qname = ui->_7_3->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_3->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_4_clicked()
{
    QString Qname = ui->_7_4->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_4->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_5_clicked()
{
    QString Qname = ui->_7_5->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_5->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_6_clicked()
{
    QString Qname = ui->_7_6->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_6->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_7_clicked()
{
    QString Qname = ui->_7_7->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_7->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_8_clicked()
{
    QString Qname = ui->_7_8->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_8->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_9_clicked()
{
    QString Qname = ui->_7_9->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_9->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_10_clicked()
{
    QString Qname = ui->_7_10->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_10->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
void Dialog::on__7_11_clicked()
{
    QString Qname = ui->_7_11->text();
    if (Qname.toStdString() == " UNUSED" || Qname.toStdString() == " NAN" || Qname.isEmpty()) {
        return;
    }
    string name = Qname.toStdString();
    QList<QListWidgetItem*> find = ui->listWidget->findItems(Qname, Qt::MatchExactly);
    if (find.isEmpty()) { //add the name to the list
        ui->listWidget->addItem(ui->_7_11->text());
    } else { //take the name off the list
        int row = ui->listWidget->row(find.first());
        ui->listWidget->takeItem(row);
    }
}
