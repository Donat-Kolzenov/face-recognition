#include "ImageProperties.h"
#include <iostream>

namespace QtRecognition
{
    ImageProperties::ImageProperties()
    {
        fileSource_ = nullptr;
        pixmap_ = new QPixmap();
        scene_ = new QGraphicsScene();
    }

    ImageProperties::ImageProperties(QString fileSource)
        : ImageProperties()
    {
        setScenePixmap(fileSource);
        ///
        fileSource_ = fileSource;
    }

    ImageProperties::ImageProperties(QPixmap pixmap)
        : ImageProperties()
    {
        setScenePixmap(pixmap);
    }

    ImageProperties::ImageProperties(const ImageProperties& other)
        : ImageProperties()
    {
        fileSource_ = other.fileSource_;
        setScenePixmap(*other.pixmap_);
    }

    ImageProperties& ImageProperties::operator=(const ImageProperties& other)
    {
        if(this != &other)
        {
            delete pixmap_;
            delete scene_;

            pixmap_ = new QPixmap();
            scene_ = new QGraphicsScene();
            fileSource_ = other.fileSource_;
            setScenePixmap(*other.pixmap_);
        }
        return *this;
    }

    ImageProperties::~ImageProperties()
    {
        delete pixmap_;
        delete scene_;
        ///
        pixmap_ = nullptr;
        scene_ = nullptr;
    }


    QString ImageProperties::getFileSource() const
    {
        return fileSource_;
    }


    QPixmap* ImageProperties::getPixmap() const
    {
        return pixmap_;
    }
    QPixmap ImageProperties::getAdditionalPixmap() const
    {
        return add_pixmap;
    }

    void ImageProperties::setAdditionalPixmapOriginal(QPixmap pixmap)
    {
        add_pixmap_orig = pixmap;
    }

    QPixmap ImageProperties::getAdditionalPixmapOriginal() const
    {
        return add_pixmap_orig;
    }


    QGraphicsScene* ImageProperties::getScene() const
    {
        return scene_;
    }


    void ImageProperties::setScenePixmap(QString fileSource)
    {

        fileSource_ = fileSource;
        pixmap_->load(fileSource_);
        setScenePixmap(*pixmap_);
    }


    void ImageProperties::setScenePixmap(QPixmap pixmap)
    {

        *pixmap_ = pixmap;
        scene_->clear();
        scene_->setSceneRect(0,0,pixmap.width(),pixmap.height());
        scene_->addPixmap(*pixmap_);
    }

    void ImageProperties::setPixmap(QPixmap pixmap)
    {
        *pixmap_ = pixmap;
    }

    void ImageProperties::setAdditionalPixmap(QPixmap pixmap)
    {
        add_pixmap = pixmap;
    }
    std::vector<cv::Rect> ImageProperties::getFaces() const
    {
        return detectedFaces;
    }
    void ImageProperties::setFaces(std::vector<cv::Rect> vector)
    {
        detectedFaces=vector;
    }
    void ImageProperties::clearFaces()
    {
        detectedFaces.clear();
    }

}
