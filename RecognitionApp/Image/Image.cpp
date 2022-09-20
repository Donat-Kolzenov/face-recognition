#include "Image.h"
#include "ImageExtention.h"
#include <QFileDialog>

namespace QtRecognition
{
    Image::Image()
    {
        properties_ = new ImageProperties();
    }

    Image::Image(QString fileSourse)
    {
        properties_ = new ImageProperties(fileSourse);
    }

    Image::Image(QPixmap pixmap)
    {
        properties_ = new ImageProperties(pixmap);
    }

    Image::Image(const Image& other)
    {
        properties_ = new ImageProperties(*other.properties_);
    }

    Image& Image::operator=(const Image& other)
    {
        if(this != &other)
        {
            delete properties_;
            properties_ = new ImageProperties(*other.properties_);
        }
        return *this;
    }

    Image::~Image()
    {
        delete properties_;
    }


    void Image::openFileSource(QWidget *widget)
    {
        using namespace ImageExtention;
        QString filter = PNG + JPG;

        properties_->setScenePixmap(QFileDialog::getOpenFileName(
                                      widget,
                                      "Выбор изображения",
                                      QDir::currentPath(),
                                      filter));
    }


    bool Image::isFileSourceValid()
    {
        return (nullptr != properties_->getFileSource());
    }


    ImageProperties* Image::getProperties() const
    {
        return properties_;
    }
}
