#ifndef BALANCE_UPLOAD_H
#define BALANCE_UPLOAD_H

#include "container.h"
#include <QDialog>
#include "balancecalc.h"

extern int ROW;
extern int COLUMN;
extern vector<vector<Container>> ship;

namespace Ui {
class balance_upload;
}

class balance_upload : public QDialog
{
    Q_OBJECT

public:
    explicit balance_upload(QWidget *parent = nullptr);
    ~balance_upload();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::balance_upload *ui;
    balanceCalc* next;
};

#endif // BALANCE_UPLOAD_H
