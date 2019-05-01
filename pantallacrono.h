#ifndef PANTALLACRONO_H
#define PANTALLACRONO_H

#include <QWidget>
#include <QStackedLayout>

namespace Ui {
class CronoIdle;
class CronoSeguents;
class CronoPlaying;
}

class PantallaCrono : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCrono(QWidget *parent = 0);
    ~PantallaCrono();

    enum Pantalles {
        IDLE = 0,
        SEGUENTS = 1,
        CRONO = 2
    };

public slots:
    void setPantalla(Pantalles pantalla);
    void setIdle() { setPantalla(IDLE); }
    void setSeguents() { setPantalla(SEGUENTS); }
    void setCrono() { setPantalla(CRONO); }

    void setTaula1Enabled(bool enabled);
    void setTaula2Enabled(bool enabled);
    void setTaula3Enabled(bool enabled);
    void chronoTick(int temps);
    void setEquips(const QString equips[3][2]);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QStackedLayout *stackedLayout;
    Ui::CronoIdle *idleUi;
    Ui::CronoSeguents *seguentsUi;
    Ui::CronoPlaying *playingUi;
    bool t1Enabled, t2Enabled, t3Enabled;
    void actualitzarTextSeguents();
};

#endif // PANTALLACRONO_H
