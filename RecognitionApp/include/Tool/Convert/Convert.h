#ifndef CONVERT_H
#define CONVERT_H

#include <opencv2/core/mat.hpp>
#include <QPixmap>
#include "Image.h"

namespace QtRecognition
{
    class Convert
    {
    public:
        static cv::Mat toMat(const Image *image);
        static QPixmap toQPixmap(const cv::Mat mat);

    private:
        static bool isMatHasAlphaChannel(const cv::Mat mat);

    private:
        Convert() {}
        ~Convert() {}

    private:
        enum Channel
        {
            HAS_ALPHA = 4,
            HAS_NOT_ALPHA = 3
        };
    };
}

#endif // CONVERT_H
