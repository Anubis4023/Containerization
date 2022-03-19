#ifndef BALANCECALC_H
#define BALANCECALC_H

#include <QDialog>
#include "container.h"

extern vector<Container> offload;
extern vector<Container> onload;
extern vector<vector<Container>> ship;

namespace Ui {
class balanceCalc;
}

class balanceCalc : public QDialog
{
    Q_OBJECT

public:
    explicit balanceCalc(QWidget *parent = nullptr);
    ~balanceCalc();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::balanceCalc *ui;
};

#endif // BALANCECALC_H
