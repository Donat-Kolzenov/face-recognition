#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsScene>
#include <ImageProperties.h>

namespace QtRecognition
{
    class Image
    {
    private:
        ImageProperties *properties_;

    public:
        Image();
        Image(QString fileSource);
        Image(QPixmap pixmap);
        Image(const Image& other);
        Image& operator=(const Image& other);
        ~Image();
    
    public:
        void openFileSource(QWidget *widget);
        bool isFileSourceValid();
        ImageProperties* getProperties() const;
    };
}

#endif // IMAGE_H
