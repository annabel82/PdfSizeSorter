#ifndef LOGIC_H
#define LOGIC_H

#include <poppler-qt5.h>
#include <sourcefolder.h>
#include <papersize.h>
#include <logwindow.h>


class Logic : public QObject
{
    Q_OBJECT

public:
    Logic();
    void                handleSortFilesBtn();
    void                setSourceFolderChoice(QString sourceFolderChoice);
    QWidget*            getSourceFolder();
    QWidget*            getPaperSize(int arrayElementLocation);
    QWidget*            getOtherPaperSize();
    QPlainTextEdit*     getLogWindow();
    SourceFolder       *sourceFolder;

private:
    QStringList         getFileList();
    bool                getMimeIsOk(QString);
    QSize               getDocSize(QString fileName);
    int                 getDocsPaperSizeArrayLocation(QSize pageSize);
    QString             copyFileToFolder(QString fileName, QString outputFolder);
    bool                getIsInRange(int val, int lwrA, int uprA, int lwrB, int uprB);
    QString             homeFolder;
    PaperSize          *paperSizes[7];
    PaperSize          *otherPaperSize;
    LogWindow          *logWindow;
    QString             sourceFolderChoice;
    bool                proceed = true;
};

#endif // LOGIC_H
