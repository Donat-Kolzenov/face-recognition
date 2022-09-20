#ifndef COLOR_H
#define COLOR_H

#include "IRecognizable.h"
#include "Image.h"

namespace QtRecognition
{
    namespace Method
    {
        class Color : public IRecognizable
        {
        public:
            void recognizeObject(QGraphicsScene *scene,Image **image) override;
        };
    }
}

#endif // COLOR_H
