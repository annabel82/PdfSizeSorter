#ifndef SOURCEFOLDER_H
#define SOURCEFOLDER_H

#include <QtWidgets>


class SourceFolder : public QGroupBox
{
    Q_OBJECT

public:
    SourceFolder(bool readOnly, QString homeFolder);
    void                setSourceFolderText(QString sourceFolderText);
    QPushButton        *sourceFolderBtn;

private:
    QLineEdit          *sourceFolderLine;
    QString             homeFolder;
    QString             sourceFolder;
};

#endif // SOURCEFOLDER_H


