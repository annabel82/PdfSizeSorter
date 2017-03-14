#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <logic.h>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow();

private:
    QWidget            *window;
    QGridLayout        *grid;
    Logic              *logic;
    QTabWidget         *tabWidget;
};

#endif


