#ifndef SOURCEFOLDER_H
#define SOURCEFOLDER_H

#include <QtWidgets>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QGridlayout>


class SourceFolder : public QGroupBox
{
    Q_OBJECT

public:
    SourceFolder(bool);

    void                setSourceFolderText(QString sourceFolderText);

    QPushButton        *sourceFolderBtn;

private:
    QLabel             *sourceFolderLabel;
    QLineEdit          *sourceFolderLine;
    QGridLayout        *sourceContainer;
    QString             homeFolder;
    QString             sourceFolder;
};

#endif // SOURCEFOLDER_H


