#include "chronolabel.h"

#include <QDebug>

ChronoLabel::ChronoLabel(QWidget *parent) :
    QLabel(parent),
    warningTime(0)
{
    updateTicks(0);
}

void ChronoLabel::updateTicks(int temps)
{
    qDebug() << "Ticks updated: " << temps;
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
        palette.setColor(backgroundRole(), Qt::red);
    } else if (temps <= warningTime) {
        palette.setColor(backgroundRole(), Qt::yellow);
    } else {
        palette.setColor(backgroundRole(), Qt::green);
    }
    this->setPalette(palette);
}
