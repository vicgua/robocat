#include "pantallapuntuacio.h"
#include "ui_pantallapuntuacio.h"
#include "constants.h"
#include <QFont>
#include <QScrollBar>

#include <QDebug>

PantallaPuntuacio::PantallaPuntuacio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PantallaPuntuacio),
    scrollTimer(new QTimer),
    scrollPoint(0)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::Window | Qt::CustomizeWindowHint | Qt::WindowFullscreenButtonHint;
    flags &= ~Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);

    ultimesWidgets[0] = PartidaWidgetGroup(
                ui->equip11, ui->taps11, ui->bandera11, ui->punts11,
                ui->equip12, ui->taps12, ui->bandera12, ui->punts12
                );
    ultimesWidgets[1] = PartidaWidgetGroup(
                ui->equip21, ui->taps21, ui->bandera21, ui->punts21,
                ui->equip22, ui->taps22, ui->bandera22, ui->punts22
                );
    ultimesWidgets[2] = PartidaWidgetGroup(
                ui->equip31, ui->taps31, ui->bandera31, ui->punts31,
                ui->equip32, ui->taps32, ui->bandera32, ui->punts32
                );
    ultimesWidgets[3] = PartidaWidgetGroup(
                ui->equip41, ui->taps41, ui->bandera41, ui->punts41,
                ui->equip42, ui->taps42, ui->bandera42, ui->punts42
                );
    scrollTimer->start(constants::AUTOSCROLL_REFRESH_TIME);
    qDebug() << "Timer" << scrollTimer->interval();
    qDebug() << "AUTOSCROLL_REFRESH_TIME" << constants::AUTOSCROLL_REFRESH_TIME;
    connect(scrollTimer, &QTimer::timeout, this, &PantallaPuntuacio::updateScroll);
}

PantallaPuntuacio::~PantallaPuntuacio()
{
    delete ui;
    delete scrollTimer;
}

void PantallaPuntuacio::setUltimesPartides(const QVector<Partida> &ultimesPartides)
{
    this->ultimesPartides = ultimesPartides;
    updatePartides();
}

void PantallaPuntuacio::setModel(QAbstractItemModel *model)
{
    ui->taulaClassificacio->setModel(model);
}

void PantallaPuntuacio::dadesActualitzades()
{
    ui->taulaClassificacio->resizeColumnsToContents();
    ui->taulaClassificacio->resizeRowsToContents();
    int width = ui->taulaClassificacio->verticalHeader()->width();
    width += ui->taulaClassificacio->verticalScrollBar()->width();
    width += ui->taulaClassificacio->horizontalHeader()->length();
    ui->taulaClassificacio->setMinimumWidth(width);
}

void PantallaPuntuacio::keyPressEvent(QKeyEvent *event)
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

void PantallaPuntuacio::updatePartides()
{
    desactivarTot();
    switch (ultimesPartides.length()) {
    default:
    case 4:
        setPartida(ultimesWidgets[3], ultimesPartides.at(3));
        Q_FALLTHROUGH();
    case 3:
        setPartida(ultimesWidgets[2], ultimesPartides.at(2));
        Q_FALLTHROUGH();
    case 2:
        setPartida(ultimesWidgets[1], ultimesPartides.at(1));
        Q_FALLTHROUGH();
    case 1:
        setPartida(ultimesWidgets[0], ultimesPartides.at(0));
        Q_FALLTHROUGH();
    case 0:
        break;
    }
}

void PantallaPuntuacio::setPartida(PantallaPuntuacio::PartidaWidgetGroup &group, const Partida &partida)
{
    group.equip1->show();
    group.equip1->setText(partida.equip1);
    group.taps1->show();
    group.taps1->setText(QString::number(partida.taps1));
    group.bandera1->setVisible(partida.bandera1);
    group.punts1->show();
    group.punts1->setText(partida.valid1 ? QString::number(partida.total1()) : "-INVÀLIDA-");
    group.equip2->show();
    group.equip2->setText(partida.equip2);
    group.taps2->show();
    group.taps2->setText(QString::number(partida.taps2));
    group.bandera2->show();
    group.bandera2->setVisible(partida.bandera2);
    group.punts2->show();
    group.punts2->setText(partida.valid2 ? QString::number(partida.total2()) : "-INVÀLIDA-");
    QFont font1 = group.punts1->font();
    font1.setBold(partida.winner1());
    group.punts1->setFont(font1);
    QFont font2 = group.punts2->font();
    font2.setBold(partida.winner2());
    group.punts2->setFont(font2);
}

void PantallaPuntuacio::desactivarTot()
{
    for (PartidaWidgetGroup &wg : ultimesWidgets) {
        wg.equip1->hide();
        wg.taps1->hide();
        wg.bandera1->hide();
        wg.punts1->hide();
        wg.equip2->hide();
        wg.taps2->hide();
        wg.bandera2->hide();
        wg.punts2->hide();
    }
}

namespace {
int calcularPos(int point, int min, int max) {
    return min + ((max - min) * point) / constants::AUTOSCROLL_MAX;
}
}

void PantallaPuntuacio::updateScroll()
{
    QScrollBar *bar = ui->taulaClassificacio->verticalScrollBar();
    bar->setSliderPosition(calcularPos(scrollPoint, bar->minimum(), bar->maximum()));
    if (++scrollPoint > constants::AUTOSCROLL_MAX) scrollPoint = 0;
}
