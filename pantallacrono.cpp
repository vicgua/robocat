#include "pantallacrono.h"
#include "constants.h"
#include "ui_cronoidle.h"
#include "ui_cronoseguents.h"
#include "ui_cronoplaying.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>

PantallaCrono::PantallaCrono(QWidget *parent) :
    QWidget(parent),
    idleUi(new Ui::CronoIdle),
    seguentsUi(new Ui::CronoSeguents),
    playingUi(new Ui::CronoPlaying)
{
    QVBoxLayout *layout = new QVBoxLayout;
    stackedLayout = new QStackedLayout;
    layout->addLayout(stackedLayout);
    QWidget *idleWidget = new QWidget;
    stackedLayout->addWidget(idleWidget);
    idleUi->setupUi(idleWidget);
    QWidget *seguentsWidget = new QWidget;
    stackedLayout->addWidget(seguentsWidget);
    seguentsUi->setupUi(seguentsWidget);
    QWidget *cronoWidget = new QWidget;
    stackedLayout->addWidget(cronoWidget);
    playingUi->setupUi(cronoWidget);
    setLayout(layout);

    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::Window | Qt::CustomizeWindowHint | Qt::WindowFullscreenButtonHint;
    flags &= ~Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    setWindowTitle("Cronòmetre RoboCAT");

    playingUi->cronometre->warningTime = constants::WARN_TIME;
}

PantallaCrono::~PantallaCrono()
{
    delete idleUi;
    delete seguentsUi;
    delete playingUi;
}

void PantallaCrono::setPantalla(PantallaCrono::Pantalles pantalla)
{
    stackedLayout->setCurrentIndex(int(pantalla));
}

void PantallaCrono::setTaula1Enabled(bool enabled)
{
    seguentsUi->taula1Widget->setVisible(enabled);
    playingUi->taula1Widget->setVisible(enabled);
    if (enabled == seguentsUi->taula2Widget->isVisible()) {
        seguentsUi->seguentsLabel->setText("Següents partides");
    } else {
        seguentsUi->seguentsLabel->setText("Següent partida");
    }
}

void PantallaCrono::setTaula2Enabled(bool enabled)
{
    seguentsUi->taula2Widget->setVisible(enabled);
    playingUi->taula2Widget->setVisible(enabled);
    if (enabled == seguentsUi->taula1Widget->isVisible()) {
        seguentsUi->seguentsLabel->setText("Següents partides");
    } else {
        seguentsUi->seguentsLabel->setText("Següent partida");
    }
}

void PantallaCrono::setEquip1Taula1(const QString &equip)
{
    seguentsUi->e1t1Label->setText(equip);
    playingUi->e1t1Label->setText(equip);
}

void PantallaCrono::setEquip2Taula1(const QString &equip)
{
    seguentsUi->e2t1Label->setText(equip);
    playingUi->e2t1Label->setText(equip);
}

void PantallaCrono::setEquip1Taula2(const QString &equip)
{
    seguentsUi->e1t2Label->setText(equip);
    playingUi->e1t2Label->setText(equip);
}

void PantallaCrono::setEquip2Taula2(const QString &equip)
{
    seguentsUi->e2t2Label->setText(equip);
    playingUi->e2t2Label->setText(equip);
}

void PantallaCrono::chronoTick(int temps)
{
    playingUi->cronometre->updateTicks(temps);
}

void PantallaCrono::keyPressEvent(QKeyEvent *event)
{
    event->accept();
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

