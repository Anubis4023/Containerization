#ifndef COMMENT_H
#define COMMENT_H

#include <QDialog>

namespace Ui {
class comment;
}

class comment : public QDialog
{
    Q_OBJECT

public:
    explicit comment(QWidget *parent = nullptr);
    ~comment();

private slots:
    void on_pushButton_clicked();

private:
    Ui::comment *ui;
};

#endif // COMMENT_H
