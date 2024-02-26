#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QPalette>

const int GRID_HEIGHT = 10;
const int GRID_WIDTH = 10;

void drawGameGrid(QWidget *widget){
    QGridLayout *layout = qobject_cast<QGridLayout*>(widget->layout());
    if(!layout){
        qDebug() << "Layout is not a QGridLayout!";
        return;
    }

    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            QLabel *cellLabel = new QLabel("EMPTY", widget);
            layout->addWidget(cellLabel, i, j);
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *centralwidget = new QWidget;
    centralwidget->setWindowTitle("Fire Fighter");
    QGridLayout *layout = new QGridLayout(centralwidget);
    layout->setColumnStretch(GRID_WIDTH, 1);
    layout->setRowStretch(GRID_HEIGHT, 1);
    centralwidget->setFixedSize(1000, 700);

    QPixmap backgroundImage("/Users/charlie/Downloads/A_pixel_art_illustration_of_a_battlefield_where_wa.jpg");
    QPixmap scaledBackground = backgroundImage.scaled(centralwidget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, scaledBackground);
    centralwidget->setAutoFillBackground(true);
    centralwidget->setPalette(palette);

    centralwidget->setLayout(layout);




    QPushButton *startButton = new QPushButton("Start", centralwidget);
    layout->addWidget(startButton, GRID_HEIGHT, GRID_WIDTH, Qt::AlignCenter | Qt::AlignBottom);


    centralwidget->show();
    return a.exec();
}
