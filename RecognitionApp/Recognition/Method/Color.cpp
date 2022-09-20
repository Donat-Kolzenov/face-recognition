#include "Color.h"
#include "Convert.h"
#include <QMessageBox>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace QtRecognition
{
    namespace Method
    {
        void Color::recognizeObject(QGraphicsScene *scene,Image **image)
        {
            using namespace cv;
            Mat mat = Convert::toMat(*image);

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

            Mat only_object;
            //нахождение объектов по диапазону цвета
            inRange(mat, Scalar(0,165,255), Scalar(0,255,255), only_object);

            (*image)->getProperties()->setScenePixmap(Convert::toQPixmap(mat));
        }
    }
}
