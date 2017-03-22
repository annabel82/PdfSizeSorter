#ifndef PAPERSIZE_H
#define PAPERSIZE_H

#include <QtWidgets>


class PaperSize : public QWidget
{
    Q_OBJECT

public:
    PaperSize();
    PaperSize(QString name, int width, int height, QString homeFolder, bool isKnownSize);
    void                setOutputFolder(QString derivedFromSourceFolder);
    QString             getOutputFolder();
    int                 getMinWidth();
    int                 getMaxWidth();
    int                 getMinHeight();
    int                 getMaxHeight();
    bool                getHasChosenBespokeFolder();

private:
    void                handleFolderBtn();

    QSpinBox           *minWidth;
    QSpinBox           *maxWidth;
    QSpinBox           *minHeight;
    QSpinBox           *maxHeight;
    QLabel             *minWidthLabel;
    QLabel             *maxWidthLabel;
    QLabel             *minHeightLabel;
    QLabel             *maxHeightLabel;
    QLineEdit          *outputFolderText;
    QString             name;
    bool                hasChosenBespokeFolder = false;
};

#endif // PAPERSIZE_H


