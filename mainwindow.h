#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>


#include <QDir>
#include <QFileDialog>


#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage blurImage(QImage imageSource, int blurRadius);
    void processNewImage(QString sourceFile, int blurRadius);


public slots:
    void openFile();
    void blurImage();

private:
    QString imageSource = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
