#include "Convert.h"
#include "opencv2/highgui/highgui.hpp"

namespace QtRecognition
{
    cv::Mat Convert::toMat(const Image *image)
    {
        IplImage* img = cvLoadImage(
                        image->getProperties()->getFileSource()
                            .toStdString()
                            .c_str(),
                        CV_LOAD_IMAGE_UNCHANGED);

        cv::Mat mat = cv::cvarrToMat(img);
        return mat;
    }


    QPixmap Convert::toQPixmap(const cv::Mat mat)
    {
        QPixmap pixmap;

        if(isMatHasAlphaChannel(mat))
            pixmap = QPixmap::fromImage(
                        QImage((unsigned char*) mat.data,
                               mat.cols,
                               mat.rows,
                               QImage::Format_RGBA8888).rgbSwapped());

        else
            pixmap = QPixmap::fromImage(
                        QImage((unsigned char*) mat.data,
                               mat.cols,
                               mat.rows,
                               QImage::Format_RGB888).rgbSwapped());

        return pixmap;
    }


    bool Convert::isMatHasAlphaChannel(const cv::Mat mat)
    {
        return mat.channels() == HAS_ALPHA;
    }
}
