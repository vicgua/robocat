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
    t1Enabled = enabled;
    seguentsUi->taula1Widget->setVisible(enabled);
    playingUi->taula1Widget->setVisible(enabled);
    actualitzarTextSeguents();
}

void PantallaCrono::setTaula2Enabled(bool enabled)
{
    t2Enabled = enabled;
    seguentsUi->taula2Widget->setVisible(enabled);
    playingUi->taula2Widget->setVisible(enabled);
    actualitzarTextSeguents();
}

void PantallaCrono::chronoTick(int temps)
{
    playingUi->cronometre->updateTicks(temps);
}

void PantallaCrono::setEquips(const QString equips[2][2])
{
    seguentsUi->e1t1Label->setText(equips[0][0]);
    playingUi->e1t1Label->setText(equips[0][0]);

    seguentsUi->e2t1Label->setText(equips[0][1]);
    playingUi->e2t1Label->setText(equips[0][1]);

    seguentsUi->e1t2Label->setText(equips[1][0]);
    playingUi->e1t2Label->setText(equips[1][0]);

    seguentsUi->e2t2Label->setText(equips[1][1]);
    playingUi->e2t2Label->setText(equips[1][1]);
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

void PantallaCrono::actualitzarTextSeguents()
{
    int nEnabled = 0;
    if (t1Enabled) ++nEnabled;
    if (t2Enabled) ++nEnabled;
    if (nEnabled == 1) {
        seguentsUi->seguentsLabel->setText("Següent partida");
    } else {
        seguentsUi->seguentsLabel->setText("Següents partides");
    }
}

