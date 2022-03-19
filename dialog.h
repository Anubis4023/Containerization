#ifndef DIALOG_H
#define DIALOG_H

#include "container.h"
#include "ui_dialog.h"
//#include "mainwindow.h"
#include "loading.h"
//#include "loading.h"
#include <QDialog>

extern vector<Container> weights;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void on__0_0_clicked();
    void on__0_1_clicked();
    void on__0_2_clicked();
    void on__0_3_clicked();
    void on__0_4_clicked();
    void on__0_5_clicked();
    void on__0_6_clicked();
    void on__0_7_clicked();
    void on__0_8_clicked();
    void on__0_9_clicked();
    void on__0_10_clicked();
    void on__0_11_clicked();
    void on__1_0_clicked();
    void on__1_1_clicked();
    void on__1_2_clicked();
    void on__1_3_clicked();
    void on__1_4_clicked();
    void on__1_5_clicked();
    void on__1_6_clicked();
    void on__1_7_clicked();
    void on__1_8_clicked();
    void on__1_9_clicked();
    void on__1_10_clicked();
    void on__1_11_clicked();
    void on__2_0_clicked();
    void on__2_1_clicked();
    void on__2_2_clicked();
    void on__2_3_clicked();
    void on__2_4_clicked();
    void on__2_5_clicked();
    void on__2_6_clicked();
    void on__2_7_clicked();
    void on__2_8_clicked();
    void on__2_9_clicked();
    void on__2_10_clicked();
    void on__2_11_clicked();
    void on__3_0_clicked();
    void on__3_1_clicked();
    void on__3_2_clicked();
    void on__3_3_clicked();
    void on__3_4_clicked();
    void on__3_5_clicked();
    void on__3_6_clicked();
    void on__3_7_clicked();
    void on__3_8_clicked();
    void on__3_9_clicked();
    void on__3_10_clicked();
    void on__3_11_clicked();
    void on__4_0_clicked();
    void on__4_1_clicked();
    void on__4_2_clicked();
    void on__4_3_clicked();
    void on__4_4_clicked();
    void on__4_5_clicked();
    void on__4_6_clicked();
    void on__4_7_clicked();
    void on__4_8_clicked();
    void on__4_9_clicked();
    void on__4_10_clicked();
    void on__4_11_clicked();
    void on__5_0_clicked();
    void on__5_1_clicked();
    void on__5_2_clicked();
    void on__5_3_clicked();
    void on__5_4_clicked();
    void on__5_5_clicked();
    void on__5_6_clicked();
    void on__5_7_clicked();
    void on__5_8_clicked();
    void on__5_9_clicked();
    void on__5_10_clicked();
    void on__5_11_clicked();
    void on__6_0_clicked();
    void on__6_1_clicked();
    void on__6_2_clicked();
    void on__6_3_clicked();
    void on__6_4_clicked();
    void on__6_5_clicked();
    void on__6_6_clicked();
    void on__6_7_clicked();
    void on__6_8_clicked();
    void on__6_9_clicked();
    void on__6_10_clicked();
    void on__6_11_clicked();
    void on__7_0_clicked();
    void on__7_1_clicked();
    void on__7_2_clicked();
    void on__7_3_clicked();
    void on__7_4_clicked();
    void on__7_5_clicked();
    void on__7_6_clicked();
    void on__7_7_clicked();
    void on__7_8_clicked();
    void on__7_9_clicked();
    void on__7_10_clicked();
    void on__7_11_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    Loading* load;
};

#endif // DIALOG_H
