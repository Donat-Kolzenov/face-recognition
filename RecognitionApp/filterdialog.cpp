#include "filterdialog.h"
#include "ui_filterdialog.h"
#include "opencv2/highgui/highgui.hpp"
#include "Convert.h"
#include <QMessageBox>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

FilterDialog::FilterDialog(QWidget *parent, QtRecognition::Image *image):
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
    image_ = image;
}

FilterDialog::~FilterDialog()
{
    delete ui;
}


void FilterDialog::on_FilterButton_clicked()
{
    using namespace cv;
    Mat mat = QtRecognition::Convert::toMat(image_);

    if(!(image_)->isFileSourceValid())
        return;

    else if(mat.empty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Предупреждение");
        msgBox.setText((image_)->getProperties()->getFileSource() +
                       "\nПуть не должен содержать символы кириллицы");

        msgBox.exec();
        return;
    }
    //Морфологические градиенты используются для отображения границ ярких областей, а затем их можно рассматривать как цели или части целей.
    //фильтр
    Mat gradient;
    cv::morphologyEx(mat, gradient, cv::MORPH_GRADIENT, cv::Mat());

    (image_)->getProperties()->setScenePixmap(QtRecognition::Convert::toQPixmap(gradient));
    this->close();
}




void FilterDialog::on_FilterButton2_clicked()
{
    using namespace cv;
    Mat mat = QtRecognition::Convert::toMat(image_);

    if(!(image_)->isFileSourceValid())
        return;

    else if(mat.empty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Предупреждение");
        msgBox.setText((image_)->getProperties()->getFileSource() +
                       "\nПуть не должен содержать символы кириллицы");

        msgBox.exec();
        return;
    }
    //операция коррозии вычисляет локальное минимальное значение в зоне ядерного покрытия, чтобы уменьшить яркую область и устранить выпуклость.
    //фильтр
    Mat erosion;
    cv::erode(mat,erosion,cv::Mat());

    (image_)->getProperties()->setScenePixmap(QtRecognition::Convert::toQPixmap(erosion));
    this->close();
}


void FilterDialog::on_FilterButton3_clicked()
{
    using namespace cv;
    Mat mat = QtRecognition::Convert::toMat(image_);

    if(!(image_)->isFileSourceValid())
        return;

    else if(mat.empty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Предупреждение");
        msgBox.setText((image_)->getProperties()->getFileSource() +
                       "\nПуть не должен содержать символы кириллицы");

        msgBox.exec();
        return;
    }
    //Закрытая операция используется для уменьшения бесполезных или управляемых шумом фрагментов в сложных алгоритмах связанных ветвей
    //фильтр
    Mat closing;
    cv::morphologyEx(mat, closing, cv::MORPH_CLOSE, cv::Mat());

    (image_)->getProperties()->setScenePixmap(QtRecognition::Convert::toQPixmap(closing));
    this->close();
}


void FilterDialog::on_FilterButton4_clicked()
{

    using namespace cv;
    Mat mat = QtRecognition::Convert::toMat(image_);

    if(!(image_)->isFileSourceValid())
        return;

    else if(mat.empty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Предупреждение");
        msgBox.setText((image_)->getProperties()->getFileSource() +
                       "\nПуть не должен содержать символы кириллицы");

        msgBox.exec();
        return;
    }
    //черная шляпа используется для отображения более темной части по сравнению с соседом.
    //фильтр
    Mat blackHat;
    cv::morphologyEx(mat, blackHat, cv::MORPH_BLACKHAT, cv::Mat());

    (image_)->getProperties()->setScenePixmap(QtRecognition::Convert::toQPixmap(blackHat));
    this->close();
}

