#ifndef PANTALLACRONO_H
#define PANTALLACRONO_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QVBoxLayout>
#include "scalingimage.h"
#include "constants.h"

namespace Ui {
class CronoIdle;
class CronoSeguents;
class CronoPlaying;
}

class PantallaCrono : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(EstatPantalla estat READ estat WRITE setEstat NOTIFY estatChanged)
    Q_PROPERTY(bool taula1Enabled READ taula1Enabled WRITE setTaula1Enabled NOTIFY taula1EnabledChanged)
    Q_PROPERTY(bool taula2Enabled READ taula2Enabled WRITE setTaula2Enabled NOTIFY taula2EnabledChanged)
    Q_PROPERTY(QString equip1Taula1 READ equip1Taula1 WRITE setEquip1Taula1 NOTIFY equip1Taula1Changed)
    Q_PROPERTY(QString equip2Taula1 READ equip2Taula1 WRITE setEquip2Taula1 NOTIFY equip2Taula1Changed)
    Q_PROPERTY(QString equip1Taula2 READ equip1Taula2 WRITE setEquip1Taula2 NOTIFY equip1Taula2Changed)
    Q_PROPERTY(QString equip2Taula2 READ equip2Taula2 WRITE setEquip2Taula2 NOTIFY equip2Taula2Changed)

public:
    static int warnTempsCrono;
    enum EstatPantalla {
        IDLE,
        SEGUENTS,
        CRONO
    };

    explicit PantallaCrono(QWidget *parent = nullptr);
    EstatPantalla estat() const { return estat_; }
    bool taula1Enabled() const { return taula1Enabled_; }
    bool taula2Enabled() const { return taula2Enabled_; }
    QString equip1Taula1() const { return equip1Taula1_; }
    QString equip2Taula1() const { return equip2Taula1_; }
    QString equip1Taula2() const { return equip1Taula2_; }
    QString equip2Taula2() const { return equip2Taula2_; }

signals:
    void estatChanged(EstatPantalla);
    void taula1EnabledChanged(bool);
    void taula2EnabledChanged(bool);
    void equip1Taula1Changed(const QString&);
    void equip2Taula1Changed(const QString&);
    void equip1Taula2Changed(const QString&);
    void equip2Taula2Changed(const QString&);

public slots:
    void setEstat(EstatPantalla nouEstat);
    void setIdle();
    void setSeguents();
    void setCrono();
    void setTaula1Enabled(bool enabled);
    void setTaula2Enabled(bool enabled);
    void setEquip1Taula1(const QString &equip);
    void setEquip2Taula1(const QString &equip);
    void setEquip1Taula2(const QString &equip);
    void setEquip2Taula2(const QString &equip);
    void chronoTick(int temps);
protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    int tempsCrono;
    EstatPantalla estat_;
    bool taula1Enabled_;
    bool taula2Enabled_;
    QString equip1Taula1_;
    QString equip2Taula1_;
    QString equip1Taula2_;
    QString equip2Taula2_;

    Ui::CronoIdle *idleUi;
    Ui::CronoSeguents *seguentsUi;
    Ui::CronoPlaying *playingUi;
    void escalaImatge(ScalingImage *imatge);

    void updateWidgetsStatus();
};

#endif // PANTALLACRONO_H
