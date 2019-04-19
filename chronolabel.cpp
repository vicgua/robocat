#include "chronolabel.h"

ChronoLabel::ChronoLabel(QWidget *parent) :
    QLabel(parent),
    warningTime(0),
    runningColor(0x99, 0xFF, 0x66),
    warningColor(0xFF, 0xFF, 0x66),
    ranoutColor(0xFF, 0x66, 0x66)
{
    updateTicks(0);
}

void ChronoLabel::updateTicks(int temps)
{
    int mins = temps / 60;
    int segs = temps % 60;
    QString text = QString("%1:%2").arg(QString::number(mins)).arg(QString::number(segs), 2, '0');
    setText(text);
    updateColors(temps);
}

void ChronoLabel::updateColors(int temps)
{
    QPalette palette = this->palette();
    if (temps == 0) {
        palette.setColor(backgroundRole(), ranoutColor);
    } else if (temps <= warningTime) {
        palette.setColor(backgroundRole(), warningColor);
    } else {
        palette.setColor(backgroundRole(), runningColor);
    }
    this->setPalette(palette);
}
