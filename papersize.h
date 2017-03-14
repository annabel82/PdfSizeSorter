#ifndef PAPERSIZE_H
#define PAPERSIZE_H

#include <QtWidgets>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QGridlayout>

class PaperSize : public QWidget
{
    Q_OBJECT

public:
    PaperSize();
    PaperSize(QString, int, int, QString);
    void                setOutputFolder(QString);
    QString             getName();
    int                 getMinWidth();
    int                 getMaxWidth();
    int                 getMinHeight();
    int                 getMaxHeight();
    QString             getOutputFolder();
    bool                getHasChosenBespokeFolder();

private:
    void                handleFolderBtn();
    QPushButton        *outputFolderBtn;
    QLabel             *minWidthLabel;
    QLabel             *maxWidthLabel;
    QLabel             *minHeightLabel;
    QLabel             *maxHeightLabel;
    QLabel             *outputFolderLabel;
    QSpinBox           *minWidth;
    QSpinBox           *maxWidth;
    QSpinBox           *minHeight;
    QSpinBox           *maxHeight;
    QLineEdit          *outputFolderText;
    QGridLayout        *container;
    QString             outputFolder;
    QString             homeFolder;
    QString             name;
    bool                hasChosenBespokeFolder = false;
};

#endif // PAPERSIZE_H


