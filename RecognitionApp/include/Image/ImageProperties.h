#ifndef IMAGEPROPERTIES_H
#define IMAGEPROPERTIES_H

#include <QGraphicsScene>
#include <opencv2/opencv.hpp>
#include <iostream>

namespace QtRecognition
{
    class ImageProperties
    {
    private:
        QString fileSource_;
        QPixmap *pixmap_;
        QPixmap add_pixmap;
        QPixmap add_pixmap_orig;
        QGraphicsScene *scene_;
        std::vector<cv::Rect> detectedFaces;

    public:
        QString getFileSource() const;
        QPixmap* getPixmap() const;
        QGraphicsScene* getScene() const;
        QPixmap getAdditionalPixmap() const;
        QPixmap getAdditionalPixmapOriginal() const;

    public:
        void setScenePixmap(QString fileSource);
        void setScenePixmap(QPixmap pixmap);
        void setPixmap(QPixmap pixmap);
        void setAdditionalPixmap(QPixmap pixmap);
        void setAdditionalPixmapOriginal(QPixmap pixmap);
        std::vector<cv::Rect> getFaces() const;
        void setFaces(std::vector<cv::Rect> vector);
        void clearFaces();

    public:
        ImageProperties();
        ImageProperties(QString fileSource);
        ImageProperties(QPixmap pixmap);
        ImageProperties(const ImageProperties& other);
        ImageProperties& operator=(const ImageProperties& other);
        ~ImageProperties();
    };
}

#endif // IMAGEPROPERTIES_H
