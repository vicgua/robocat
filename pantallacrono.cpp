#include "pantallacrono.h"
#include "ui_cronoidle.h"
#include "ui_cronoseguents.h"
#include "ui_cronoplaying.h"

PantallaCrono::PantallaCrono(QWidget *parent) :
    QMainWindow(parent),
    taula1Enabled_(true), // Temporary fix
    taula2Enabled_(true), // Temporary fix
    equip1Taula1_("AAA"), // TF
    equip2Taula1_("BBB"), // TF
    equip1Taula2_("CCC"), // TF
    equip2Taula2_("DDD"), // TF
    idleUi(new Ui::CronoIdle),
    seguentsUi(new Ui::CronoSeguents),
    playingUi(new Ui::CronoPlaying)
{
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::CustomizeWindowHint | Qt::WindowFullscreenButtonHint;
    flags &= ~Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    setEstat(IDLE);
}

void PantallaCrono::setEstat(PantallaCrono::EstatPantalla nouEstat) {
    if (nouEstat == estat_) return;
    estat_ = nouEstat;
    QWidget *newCentralWidget = new QWidget;
    switch (estat_) {
    case IDLE:
        idleUi->setupUi(newCentralWidget);
        break;
    case SEGUENTS:
        seguentsUi->setupUi(newCentralWidget);
        break;
    case CRONO:
        playingUi->setupUi(newCentralWidget);
        break;
    }
    setCentralWidget(newCentralWidget);
    updateWidgetsStatus();
    emit estatChanged(estat_);
}

void PantallaCrono::setIdle()
{
    setEstat(IDLE);
}

void PantallaCrono::setSeguents()
{
    setEstat(SEGUENTS);
}

void PantallaCrono::setCrono()
{
    setEstat(CRONO);
}

void PantallaCrono::setTaula1Enabled(bool enabled)
{
    taula1Enabled_ = enabled;
    updateWidgetsStatus();
    emit taula1EnabledChanged(enabled);
}

void PantallaCrono::setTaula2Enabled(bool enabled)
{
    taula2Enabled_ = enabled;
    updateWidgetsStatus();
    emit taula2EnabledChanged(enabled);
}

void PantallaCrono::setEquip1Taula1(const QString &equip)
{
    equip1Taula1_ = equip;
    updateWidgetsStatus();
    emit equip1Taula1Changed(equip);
}

void PantallaCrono::setEquip2Taula1(const QString &equip)
{
    equip2Taula1_ = equip;
    updateWidgetsStatus();
    emit equip2Taula1Changed(equip);
}

void PantallaCrono::setEquip1Taula2(const QString &equip)
{
    equip1Taula2_ = equip;
    updateWidgetsStatus();
    emit equip1Taula2Changed(equip);
}

void PantallaCrono::setEquip2Taula2(const QString &equip)
{
    equip2Taula2_ = equip;
    updateWidgetsStatus();
    emit equip2Taula2Changed(equip);
}

void PantallaCrono::chronoTick(int temps)
{
    tempsCrono = temps;
    if (estat_ == CRONO) {
        playingUi->cronometre->updateTicks(temps);
    }
}

void PantallaCrono::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    //escalaImatge(idleUi->logoRobocat);
}

void PantallaCrono::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_F11:
        setWindowState(windowState() ^ Qt::WindowFullScreen);
        break;
    case Qt::Key_Escape:
        setWindowState(windowState() & ~Qt::WindowFullScreen);
        break;
    default:
        event->ignore();
    }
}

void PantallaCrono::escalaImatge(ScalingImage *imatge)
{
    imatge->resize(imatge->width(), imatge->height());
}

void PantallaCrono::updateWidgetsStatus()
{
    switch (estat_) {
    case IDLE:
        break;
    case SEGUENTS:
        seguentsUi->e1t1Label->setText(equip1Taula1_);
        seguentsUi->e2t1Label->setText(equip2Taula1_);
        seguentsUi->e1t2Label->setText(equip1Taula2_);
        seguentsUi->e2t2Label->setText(equip2Taula2_);
        seguentsUi->taula1Widget->setVisible(taula1Enabled_);
        seguentsUi->taula2Widget->setVisible(taula2Enabled_);
        seguentsUi->seguentsLabel->setVisible(taula1Enabled_ || taula2Enabled_);
        if (taula1Enabled_ == taula2Enabled_) {
            seguentsUi->seguentsLabel->setText("Següents partides");
        } else {
            seguentsUi->seguentsLabel->setText("Següent partida");
        }
        break;
    case CRONO:
        playingUi->e1t1Label->setText(equip1Taula1_);
        playingUi->e2t1Label->setText(equip2Taula1_);
        playingUi->e1t2Label->setText(equip1Taula2_);
        playingUi->e2t2Label->setText(equip2Taula2_);
        playingUi->taula1Widget->setVisible(taula1Enabled_);
        playingUi->taula2Widget->setVisible(taula2Enabled_);
        playingUi->cronometre->warningTime = constants::WARN_TIME;
        playingUi->cronometre->updateTicks(tempsCrono);
        break;
    }
}
