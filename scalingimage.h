#ifndef SCALINGIMAGE_H
#define SCALINGIMAGE_H

#include <QLabel>

class ScalingImage : public QLabel
{
public:
    explicit ScalingImage(QWidget *parent = 0);
    const QPixmap *pixmap() const { return &originalPixmap; }

public slots:
    void resize(int width, int height);
    void setPixmap(const QPixmap &newPixmap);
private:
    int currWidth, currHeight;
    QPixmap originalPixmap;
    void redraw();
};

#endif // SCALINGIMAGE_H
