#ifndef LOADING_H
#define LOADING_H

#include <QDialog>
#include "ui_loading.h"
#include "movements.h"
#include "container.h"

#include <string>
#include <iostream>


extern vector<Container> onload;

namespace Ui {
class Loading;
}

class Loading : public QDialog
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = nullptr);
    ~Loading();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    bool isNumber(const std::string& str);

private:
    Ui::Loading *ui;
    movements *move;
};

#endif // LOADING_H
