#include "Contour.h"
#include "Convert.h"
#include <QMessageBox>
#include "qpainter.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

namespace QtRecognition
{
    namespace Method
    {
        void Contour::recognizeObject(QGraphicsScene *scene, Image **image)//QGraphicsScene *scene
        {
            using namespace cv;
            QImage image1(scene->sceneRect().size().toSize(), QImage::Format_BGR888);
            image1.fill(Qt::transparent);                                              // Start all pixels transparent

            QPainter painter(&image1);
            scene->render(&painter);


            Mat mat(image1.height(), image1.width(), CV_8UC3, image1.bits());


           if(!(*image)->isFileSourceValid())
              return;

            else if(mat.empty())
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Предупреждение");
                msgBox.setText((*image)->getProperties()->getFileSource() +
                               "\nПуть не должен содержать символы кириллицы");

                msgBox.exec();
                return;
            }
            // Загрузка каскадов (шаблонов - xml-файлы установленные вместе с OpenCV)
            CascadeClassifier faceCascade;
            // Указываем полный путь для загрузки
            faceCascade.load(
                "C:/OpenCV/opencv/sources/data/haarcascades_cuda"
                    "/haarcascade_frontalface_alt2.xml");
            std::vector<Rect> faces;
            // Находим лица
            faceCascade.detectMultiScale(mat,
                                         faces,
                                         1.1,
                                         2,
                                         0,
                                         Size(30, 30));
            (*image)->getProperties()->setFaces(faces);
            // Рисуем эллипсы на найденных лицах
            for (int i = 0; i < faces.size(); i++)
            {
                Point center(faces.at(i).x + faces.at(i).width*0.5,
                             faces.at(i).y + faces.at(i).height*0.5);

                ellipse(mat,
                        center,
                        Size(faces.at(i).width*0.5,
                             faces.at(i).height*0.5),
                        0,
                        0,
                        360,
                        Scalar(255, 0, 255, 255),
                        4,
                        8,
                        0);
            }
            // Преобразовываем mat в QPixmap
            (*image)->getProperties()->setScenePixmap(Convert::toQPixmap(mat));
            return;
        }
    }
}
