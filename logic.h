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
    QWidget*            getPaperSize(int no);
    QPlainTextEdit*     getLogWindow();
    QDialogButtonBox*   getActionBtns();
    void                getFileList();
    void                getDocSize();
    QString             getDocSizeName(int, int);
    bool                getIsInRange(int, int, int, int, int);

private:
    void                handleRunBtn();
    void                handleSourceFolderBtn();
    PaperSize          *paperSizes[7];
    SourceFolder       *sourceFolder;
    LogWindow          *logWindow;
    QString             homeFolder;
    QString             sourceFolderChoice;
    QDialogButtonBox   *actionBtns;
    QStringList         allFiles;
    QString             fileName;
    QSize               pageSize;
};

#endif // LOGIC_H


