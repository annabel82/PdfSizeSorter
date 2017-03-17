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
    QSize               getDocSize(QString fileName);
    int                 getDocsPaperSizeArrayLocation(QSize pageSize);
    bool                getIsInRange(int val, int lwrA, int uprA, int lwrB, int uprB);
    QString             copyFileToFolder(QString fileName, QString outputFolder);

private:
    void                handleSortFilesBtn();
    void                handleSourceFolderBtn();
    PaperSize          *paperSizes[7];
    SourceFolder       *sourceFolder;
    LogWindow          *logWindow;
    QString             homeFolder;
    QString             sourceFolderChoice;
    QDialogButtonBox   *actionBtns;
    bool                cont = true;
};

#endif // LOGIC_H


