#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void keyPressEvent(QKeyEvent* event);
    QMediaPlayer* player;
    QVideoWidget* videoWidget;
    int mVolume;
    int isMuted;
    qint64 mPosition;

public slots:
    //for test signal
    void on_positionChanged();
};

#endif // MAINWINDOW_H
