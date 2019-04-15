#include "scalingimage.h"

ScalingImage::ScalingImage(QWidget *parent) : QLabel(parent)
{

}

void ScalingImage::resize(int width, int height)
{
    currWidth = width;
    currHeight = height;
    redraw();
}

void ScalingImage::setPixmap(const QPixmap &newPixmap)
{
    originalPixmap = newPixmap;
    redraw();
}

void ScalingImage::redraw()
{
    QLabel::setPixmap(originalPixmap.scaled(currWidth, currHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
