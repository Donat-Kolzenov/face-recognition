#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filterdialog.h"
#include "Contour.h"
#include "Color.h"
#include "ImageProperties.h"
#include <QGraphicsBlurEffect>
#include <QtWidgets>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Convert.h"
 
 
MainWindow::MainWindow(QWidget *parent,
                       QtRecognition::Image *image,
                       QtRecognition::IRecognizable *recognitionMethod)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image_ = image;
    recognitionMethod_ = recognitionMethod;
    image_->getProperties()->setScenePixmap(nullptr);
}
 
MainWindow::~MainWindow()
{
    delete ui;
    delete image_;
    delete recognitionMethod_;
}
 
 
void MainWindow::on_AddImageButton_clicked()
{
    ui->BlurCheckBox->setEnabled(Qt::ItemIsEnabled);
    ui->BlurCheckBox->setChecked(false);
    image_->openFileSource(this);
    ui->graphicsView->setScene(image_->getProperties()->getScene());
    image_->getProperties()->setAdditionalPixmapOriginal(*image_->getProperties()->getPixmap());
    ui->graphicsView->fitInView(
                image_->getProperties()->getScene()->itemsBoundingRect(),
                Qt::IgnoreAspectRatio);
}
 
 
void MainWindow::on_RemoveImageButton_clicked()
{
    image_->getProperties()->setScenePixmap(nullptr);
    ui->BlurCheckBox->setChecked(false);
    image_->getProperties()->clearFaces();
}
 
 
void MainWindow::on_FilterButton_clicked()
{
    FilterDialog dialog(this,image_);
    dialog.exec();
    ui->graphicsView->setScene(image_->getProperties()->getScene());
    ui->graphicsView->fitInView(
                image_->getProperties()->getScene()->itemsBoundingRect(),
                Qt::IgnoreAspectRatio);
}
 
 
void MainWindow::on_BlurCheckBox_stateChanged(int state)
{
    if(Qt::Checked == state)
    {
        ui->BlurVerticalSlider->setEnabled(Qt::ItemIsEnabled);
        ui->BlurVerticalSlider->setCursor(Qt::OpenHandCursor);
        if (!image_->getProperties()->getPixmap()->isNull()){
            QPixmap srcImage = *image_->getProperties()->getPixmap();
            image_->getProperties()->setAdditionalPixmap(srcImage);

            image_->getProperties()->setScenePixmap(srcImage);
            ui->BlurVerticalSlider->setValue(ui->BlurVerticalSlider->value());

            QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
            blur->setBlurRadius(ui->BlurVerticalSlider->value());

            QImage image = image_->getProperties()->getPixmap()->toImage();
            QPixmap res_image = applyEffectToImage(image, ui->BlurVerticalSlider->value());

            image_->getProperties()->setScenePixmap(res_image);
            image_->getProperties()->setPixmap(srcImage);
        }
    }
    else if(Qt::Unchecked == state)
    {
        image_->getProperties()->clearFaces();
        if (!image_->getProperties()->getAdditionalPixmap().isNull() and !image_->getProperties()->getPixmap()->isNull()){
            image_->getProperties()->setScenePixmap(image_->getProperties()->getAdditionalPixmapOriginal());
        }
        ui->BlurVerticalSlider->setEnabled(!Qt::ItemIsEnabled);
        ui->BlurVerticalSlider->setCursor(Qt::ArrowCursor);
        ui->BlurVerticalSlider->setValue(1);
 
    }
}
QPixmap MainWindow::applyEffectToImage(QImage src, int position)
{

    cv::Mat srcMat = cv::cvarrToMat(
                cvLoadImage(
                    image_->getProperties()->getFileSource().toStdString().c_str(),
                    CV_LOAD_IMAGE_UNCHANGED
                )
    );
    cv::Mat mask = cv::Mat(srcMat.size(), srcMat.type(), cv::Scalar(0));

    cv::Mat dstMat;
    srcMat.copyTo(dstMat);

    for ( int i = 1; i < position*3; i = i + 2 )
    {
        cv::medianBlur ( srcMat, dstMat, i );
    }

    if (image_->getProperties()->getFaces().size() == 0) {
        for (int y = 0; y < mask.rows; y++) {
            for (int x = 0; x < mask.cols; x++) {
                cv::Vec3b& color = mask.at<cv::Vec3b>(y,x);
                cv::Vec3b& color_blurred = dstMat.at<cv::Vec3b>(y,x);

                color[0] = color_blurred[0];
                color[1] = color_blurred[1];
                color[2] = color_blurred[2];
            }
        }
    }
    else {
        for (int y = 0; y < mask.rows; y++) {
            for (int x = 0; x < mask.cols; x++) {
                cv::Vec3b& color = mask.at<cv::Vec3b>(y,x);
                cv::Vec3b& color1 = srcMat.at<cv::Vec3b>(y,x);
                cv::Vec3b& color2 = dstMat.at<cv::Vec3b>(y,x);

                for (int faces = 0; faces < image_->getProperties()->getFaces().size(); faces++) {
                    int x_ = image_->getProperties()->getFaces()[faces].x+image_->getProperties()->getFaces()[faces].width/2;
                    int y_ = image_->getProperties()->getFaces()[faces].y+image_->getProperties()->getFaces()[faces].height/2;
                    if ( (x - x_)*(x - x_) + (y - y_)*(y - y_)
                         <= (image_->getProperties()->getFaces()[faces].width/2)*(image_->getProperties()->getFaces()[faces].width/2) )
                    {
                        color[0] = color1[0];
                        color[1] = color1[1];
                        color[2] = color1[2];
                    }
                }
                if (static_cast<int>(color[0]) == 0
                      and color[1] == 0
                      and color[2] == 0) {
                    color[0] = color2[0];
                    color[1] = color2[1];
                    color[2] = color2[2];
                }
            }
        }
    }

    return QtRecognition::Convert::toQPixmap(mask);

}

void MainWindow::on_BlurVerticalSlider_sliderMoved(int position)
{
    if (ui->BlurCheckBox->checkState() and !image_->getProperties()->getPixmap()->isNull()){
        QPixmap srcImage = *image_->getProperties()->getPixmap();
        image_->getProperties()->setAdditionalPixmap(srcImage);

        image_->getProperties()->setScenePixmap(srcImage);
        ui->BlurVerticalSlider->setValue(position);
 
        QImage image = image_->getProperties()->getPixmap()->toImage();
        QPixmap res_image = applyEffectToImage(image, position);

        image_->getProperties()->setScenePixmap(res_image);
        image_->getProperties()->setPixmap(srcImage);
    }
}
 
 
void MainWindow::on_BlurVerticalSlider_sliderPressed()
{
    ui->BlurVerticalSlider->setCursor(Qt::ClosedHandCursor);
}
 
 
void MainWindow::on_BlurVerticalSlider_sliderReleased()
{
    ui->BlurVerticalSlider->setCursor(Qt::OpenHandCursor);
}
 
 
void MainWindow::on_RecognitionButton_clicked()
{
    if (!image_->getProperties()->getPixmap()->isNull()) {
        recognitionMethod_->recognizeObject(image_->getProperties()->getScene(), &image_);
        ui->graphicsView->setScene(image_->getProperties()->getScene());
        ui->graphicsView->fitInView(
                    image_->getProperties()->getScene()->itemsBoundingRect(),
                    Qt::IgnoreAspectRatio);
    }
}
 
 
void MainWindow::on_FaceRecognitionRadioButton_toggled(bool checked)
{
    if(checked)
    {
        ui->ObjectRecognitionRadioButton->setChecked(false);
        if(nullptr != recognitionMethod_)
        {
            delete recognitionMethod_;
            recognitionMethod_ = new QtRecognition::Method::Contour();
        }
        QIcon icon(":/Assets/png/FaceRecognition.png");
        QSize size(42, 42);
        ui->RecognitionButton->setIconSize(size);
        ui->RecognitionButton->setIcon(icon);
    }
 
    else
        ui->ObjectRecognitionRadioButton->setChecked(true);
}
 
 
void MainWindow::on_ObjectRecognitionRadioButton_toggled(bool checked)
{
    if(checked)
    {
        ui->FaceRecognitionRadioButton->setChecked(false);
        if (nullptr != recognitionMethod_)
        {
            delete recognitionMethod_;
            recognitionMethod_ = new QtRecognition::Method::Color();
        }
        QIcon icon(":/Assets/png/ObjectRecognition.png");
        QSize size(35, 35);
        ui->RecognitionButton->setIconSize(size);
        ui->RecognitionButton->setIcon(icon);
    }

    else
        ui->FaceRecognitionRadioButton->setChecked(true);
}
 
 
void MainWindow::on_BlurCheckBox_pressed()
{
    if (image_->getProperties()->getPixmap()->isNull()) {
        ui->BlurCheckBox->setEnabled(!Qt::ItemIsEnabled);
    }
    else {
        ui->BlurCheckBox->setEnabled(Qt::ItemIsEnabled);
    }
}
