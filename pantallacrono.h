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
    void setEquip1Taula1(const QString &equip);
    void setEquip2Taula1(const QString &equip);
    void setEquip1Taula2(const QString &equip);
    void setEquip2Taula2(const QString &equip);
    void chronoTick(int temps);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QStackedLayout *stackedLayout;
    Ui::CronoIdle *idleUi;
    Ui::CronoSeguents *seguentsUi;
    Ui::CronoPlaying *playingUi;
};

#endif // PANTALLACRONO_H
