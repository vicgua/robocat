#ifndef CHRONOLABEL_H
#define CHRONOLABEL_H

#include <QLabel>

class ChronoLabel : public QLabel
{
    Q_OBJECT

public:
    int warningTime;

    ChronoLabel(QWidget *parent = 0);

public slots:
    void updateTicks(int temps);

private:
    void updateColors(int temps);
};

#endif // CHRONOLABEL_H
