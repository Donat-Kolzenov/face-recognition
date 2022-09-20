#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include "Image.h"

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr, QtRecognition::Image *image=nullptr);
    ~FilterDialog();

private slots:
    void on_FilterButton_clicked();

    void on_FilterButton2_clicked();

    void on_FilterButton3_clicked();

    void on_FilterButton4_clicked();

private:
    Ui::FilterDialog *ui;
    QtRecognition::Image *image_;
};

#endif // FILTERDIALOG_H
