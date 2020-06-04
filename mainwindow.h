#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <logic.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    QDialogButtonBox   *closeRunButtons;
    void                handleSourceFolderBtn();
    Logic              *logic;
};

#endif


