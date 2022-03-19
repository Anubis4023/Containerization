#ifndef MOVEMENTS_H
#define MOVEMENTS_H

//#include "loading.h"
//#include "dialog.h"
#include <vector>
#include "container.h"
#include <QDialog>

extern vector<Container> offload;
extern vector<Container> onload;
extern vector<vector<Container>> ship;
extern Node answer;

namespace Ui {
class movements;
}

class movements : public QDialog
{
    Q_OBJECT

public:
    explicit movements(QWidget *parent = nullptr);
    ~movements();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::movements *ui;
};

#endif // MOVEMENTS_H
