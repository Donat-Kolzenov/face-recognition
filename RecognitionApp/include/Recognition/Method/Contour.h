#ifndef CONTOUR_H
#define CONTOUR_H

#include "IRecognizable.h"
#include "Image.h"
#include "opencv2/imgproc/imgproc.hpp"

namespace QtRecognition
{
    namespace Method
    {
        class Contour : public IRecognizable
        {
        public:
            void recognizeObject(QGraphicsScene *scene,
                                 Image **image) override;
        };
    }
}

#endif // CONTOUR_H
