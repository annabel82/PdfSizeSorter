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
    QLineEdit          *sourceFolderText;
    QString             homeFolder;
};

#endif // SOURCEFOLDER_H


