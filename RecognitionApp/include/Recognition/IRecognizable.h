#ifndef IRECOGNIZABLE_H
#define IRECOGNIZABLE_H

#include "Image.h"
#include "opencv2/imgproc/imgproc.hpp"

namespace QtRecognition
{
    class IRecognizable
    {
    public:
        virtual void recognizeObject(QGraphicsScene *scene, Image **image) = 0;

    public:
        IRecognizable() {}
        virtual ~IRecognizable() = default;
    };
}

#endif // IRECOGNIZABLE_H
