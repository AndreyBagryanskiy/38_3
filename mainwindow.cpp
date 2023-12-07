#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QImage MainWindow::blurImage(QImage imageSource, int blurRadius){
    if(imageSource.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(imageSource));

    auto* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurRadius);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result (imageSource.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(),
                 QRectF(0, 0, imageSource.width(), imageSource.height()));
    return result;
}

void MainWindow::processNewImage(QString sourceFile, int blurRadius){
    ui->label->setPixmap(QPixmap::fromImage(blurImage(QImage(sourceFile), blurRadius).scaled(
        ui->label->width(),
        ui->label->height(),
        Qt::KeepAspectRatio)));
}

void MainWindow::openFile(){
    imageSource = QFileDialog::getOpenFileName(nullptr,
                                                   "Open image to blur",
                                                   "",
                                                   "image files (*.jpg)"
                                                   );
    if(QFileInfo::exists(imageSource)){
        processNewImage(imageSource, ui->horizontalSlider->value());
    }
}


void MainWindow::blurImage(){
    if(QFileInfo::exists(imageSource)){
        processNewImage(imageSource, ui->horizontalSlider->value());
    }else{
        ui->label->setText("Image is not open.");
    }
}

