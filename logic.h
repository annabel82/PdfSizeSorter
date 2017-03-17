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
    QWidget*            getSourceFolder();
    QWidget*            getPaperSize(int arrayElementLocation);
    QPlainTextEdit*     getLogWindow();
    QDialogButtonBox*   getActionBtns();
    QStringList         getFileList();
    QSize               getDocSize(QString fileNameWithDir);
    int                 getDocsPaperSizeArrayLocation(QSize pageSize);
    bool                getIsInRange(int val, int lowA, int upA, int lowB, int upB);
    bool                copyFileToFolder(QString fileName, int paperSizeElementLocation);

private:
    void                handleRunBtn();
    void                handleSourceFolderBtn();
    PaperSize          *paperSizes[7];
    SourceFolder       *sourceFolder;
    LogWindow          *logWindow;
    QString             homeFolder;
    QString             sourceFolderChoice;
    QDialogButtonBox   *actionBtns;
};

#endif // LOGIC_H


