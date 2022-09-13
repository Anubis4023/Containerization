#include "balancecalc.h"
#include "ui_balancecalc.h"
#include "container.h"
#include "balance.h"
#include <QMessageBox>
#include <QTime>
#include <QDate>
#include <QFile>
#include <QTextStream>

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

int balanceCalc::tallest(vector<vector<Container>>& grid, int column) {
    int tallest = -1;
    //vector<vector<Container>> temp = grid.state;
    //printGrid(grid);
    for (int i = 0; i < 8; ++i) {
        //cout << "i is : " << i << endl;
        if (grid[i][column].weight > 0) {
            //cout << "tallest is returning: " << i << " in the column " << column << endl;
            return i;
        }
    }
    //cout << "TALLEST is returning: " << tallest << " in the column " << column << endl;
    return tallest;
}

string balanceCalc::moveString(int startx, int starty, int endx, int endy) {
    string movement = "(" + to_string(startx) + "," + to_string(starty) + ") to (" + to_string(endx) + "," + to_string(endy) + ")";
    return movement;
}

vector<string> balanceCalc::findMovements(Node& answer, vector<vector<Container>>& initial) {

    //Update the coordinate numbers to match the final output instead of typical top left in 2d array 0,0
    for (unsigned long long i = 0; i < answer.position.size(); ++i) {
        answer.position.at(i).first = abs(answer.position.at(i).first-8);
        answer.position.at(i).second = answer.position.at(i).second+1;
    }

    vector<string> movements;
    //First position moves to the position after in the vector
    for (unsigned long long i = 0; i < answer.position.size()-2; i+=2) { //For each movement, elaborate the horizontal and vertical movements. //size-2 to skip movement to top left at the end
        //If the target coordinate has a container, it means to simply move the crane to that position so no need to print the movements
        if (initial[8-answer.position.at(i+1).first][answer.position.at(i+1).second-1].weight > 0) {
            continue;
        }

        int top = -1;
        int xStart = answer.position.at(i).second;
        int xEnd = answer.position.at(i+1).second;

        //cout << "xStart: " << xStart << ". xEnd: " << xEnd << endl;

        //Find the tallest column between the two positions. i is position1 moving to position2 at i+1
        //Check all columns between start and end, and include end
        if (xStart > xEnd) { //moving from right to left
            for (int j = xEnd; j < xStart; ++j) {
                //Find tallest column in each column j
                int tall = tallest(initial, j-1);
                if (top < abs(tall-8) && tall != -1) {
                    top = abs(tall-8);
                }
            }
        } else { //moving from left to right
            for (int j = xStart+1; j <= xEnd; ++j) {
                //Find tallest column in each column j
                int tall = tallest(initial, j-1);
                if (top < abs(tall-8) && tall != -1) {
                    top = abs(tall-8);
                    //cout << "New top is: " << top << endl;
                }
            }
        }

        //cout << "top found is: " << top << endl;
        int startX = answer.position.at(i).first;
        int startY = answer.position.at(i).second;
        int endX = answer.position.at(i+1).first;
        int endY = answer.position.at(i+1).second;
        //cout << "check" << endl;
        //If tallest column is as tall as or taller than starting column, move container one level above that
        if (top >= startX) {
            //cout << "top is: " << top << endl;
            movements.push_back(moveString(8-startX, startY-1, 8-(top + 1), startY-1));
            //cout << "temp accessed: " << 8-startX << " and " << startY-1 << endl;
            //cout << "temp stored in : " << 8-(top+1) << " and " << startY-1 << endl;

            Container temp = initial[8-startX][startY-1];
            initial[8-startX][startY-1] = Container();
            initial[8-(top+1)][startY-1] = temp;
            startX = top + 1;
            //cout << "MOVEMENT WAS DONE" << endl;
            //printGrid(initial);
        }

        //cout << "check2" << endl;
        //Now that row level is good, move horizontal
        if (startY != endY) {
            movements.push_back(moveString(8-startX, startY-1, 8-startX, endY-1));
            //cout << startX << "," << startY << " and " << startX << "," << endY << endl;
            //printGrid(initial);
            Container temp = initial[8-startX][startY-1];
            initial[8-startX][startY-1] = Container();
            initial[8-startX][endY-1] = temp;
        }

        //cout << "check3" << endl;
        //Now move down to place the container to the goal level
        if (startX != endX) {
            movements.push_back(moveString(8-startX, endY-1, 8-endX, endY-1));
            Container temp = initial[8-startX][endY-1];
            initial[8-startX][endY-1] = Container();
            initial[8-endX][endY-1] = temp;
        }

        /*cout << "Movements so far: " << endl;
        for (unsigned long long h = 0; h < movements.size(); ++h) {
            cout << movements.at(h) << endl;
        }
        //printGrid(initial);
        cout << endl;*/
    }

    //cout << "About to return" << endl;
    return movements;
}

void balanceCalc::on_pushButton_clicked()
{
    if (ui->listWidget->count() > 0) {
        return;
    }

    vector<vector<Container>> initial = ship;
    answer = searchG(ship, 1, offload, onload); //1 is balance, 2 is load/offload

    for (unsigned long long i = 0; i < answer.position.size(); ++i) {
        if (answer.position.at(i).first == -1) {
            answer.position.at(i).first = 17;
        }

        if (answer.position.at(i).second == -1) {
            answer.position.at(i).second = 0;
        }
    }



    QFile file ("C:/Users/pacow/OneDrive/Desktop/animation.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (initial[i][j].weight > 0) {
                out << QString::fromStdString("(" + to_string(i) + "," + to_string(j) + ")") << Qt::endl;
            }
        }
    }
    vector<string> finalMoves = findMovements(answer, initial);
    out << QString::fromStdString("(-1,-1)") << Qt::endl;
    for (unsigned long long i = 0; i < finalMoves.size()-1; ++i) {
        out << QString::fromStdString(finalMoves.at(i)) << Qt::endl;
    }
    out << QString::fromStdString(finalMoves.at(finalMoves.size()-1));

    int iter = 1;
    for (unsigned long long i = 0; i < answer.position.size(); i += 2) {
           //QString move = QString::fromStdString(to_string(iter) + ". From position (" + to_string(abs(answer.position.at(i).first-8)) + ", " + to_string(answer.position.at(i).second+1) + ") to (" + to_string(abs(answer.position.at(i+1).first-8)) + ", " + to_string(answer.position.at(i+1).second+1) + ")");
           QString move = QString::fromStdString("(" + to_string(answer.position.at(i).first) + ", " + to_string(answer.position.at(i).second) + ") to (" + to_string(answer.position.at(i+1).first) + ", " + to_string(answer.position.at(i+1).second) + ")");
             ui->listWidget->addItem(move);
             ++iter;
            //cout << "here" << endl;
    }
    ui->listWidget->addItem(QString::fromStdString("Estimated time: " + to_string(answer.gn)));
}

void balanceCalc::printGrid(vector<vector<Container>>& initial) {
    for (int i = 0; i < 8; ++i) {
        for (int h = 0; h < 12; ++h) {
            if (initial[i][h].weight > 0) {
                cout << "1 ";
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
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

