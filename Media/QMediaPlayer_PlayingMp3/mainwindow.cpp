#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("../mediaSource/Feel So Close.mp3"));
    player->play();

    mVolume = 50;
    isMuted = 0;
    mPosition = 0;

    /* Test Signal */
    connect(player, SIGNAL( positionChanged(qint64) ),
            this, SLOT( on_positionChanged()) );
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    /* Test Slots */
    //Slots: Stop, Play, Pause
    if (event->key() == Qt::Key_0)
    {
        player->stop();
        qDebug() << "player->stop();";
    }
    if (event->key() == Qt::Key_1)
    {
        player->play();
        qDebug() << "player->play();";
    }
    if (event->key() == Qt::Key_2)
    {
        player->pause();
        qDebug() << "player->pause();";
    }

    //Slots: setVolume, setMuted
    if (event->key() == Qt::Key_Up)
    {
        if (mVolume > 99) mVolume = 100;
        mVolume ++;
        player->setVolume(mVolume);
        qDebug() << "Volume: " << player->volume();
    }
    if (event->key() == Qt::Key_Down)
    {
        if (mVolume < 1) mVolume = 0;
        mVolume --;
        player->setVolume(mVolume);
        qDebug() << "Volume: " << player->volume();
    }
    if (event->key() == Qt::Key_M)
    {
        isMuted = !isMuted;
        player->setMuted(isMuted);
        qDebug() << "Muted: " << player->isMuted();
    }
    //Slots: setPosition
    if (event->key() == Qt::Key_Left)
    {
        mPosition -= 1000;
        player->setPosition(mPosition);
        qDebug() << "setPosition: " << player->position();
    }
    if (event->key() == Qt::Key_Right)
    {
        mPosition += 1000;
        player->setPosition(mPosition);
        qDebug() << "setPosition: " << player->position();
    }
}
void MainWindow::on_positionChanged()
{
    qDebug() << "Position: " << player->position();
    mPosition = player->position();
}
