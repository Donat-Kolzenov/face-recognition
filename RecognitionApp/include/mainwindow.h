#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Contour.h"


#include "opencv2/imgproc/imgproc.hpp"


#include <iostream> ///



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
            QWidget *parent = nullptr,
            QtRecognition::Image *image = new QtRecognition::Image(),
            QtRecognition::IRecognizable *recognitionMethod =
                new QtRecognition::Method::Contour());

    ~MainWindow();

private slots:
    void on_AddImageButton_clicked();

    void on_RemoveImageButton_clicked();

    void on_FilterButton_clicked();

    void on_BlurCheckBox_stateChanged(int state);

    void on_BlurVerticalSlider_sliderMoved(int position);

    void on_BlurVerticalSlider_sliderPressed();

    void on_BlurVerticalSlider_sliderReleased();

    void on_RecognitionButton_clicked();

    void on_FaceRecognitionRadioButton_toggled(bool checked);

    void on_ObjectRecognitionRadioButton_toggled(bool checked);

    void on_BlurCheckBox_pressed();

private:
    Ui::MainWindow *ui;
    QtRecognition::Image *image_;
    QtRecognition::IRecognizable *recognitionMethod_;
    QPixmap applyEffectToImage(QImage src, int position);
};
#endif // MAINWINDOW_H
