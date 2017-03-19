#ifndef LOGIC_H
#define LOGIC_H

#include <poppler-qt5.h>
#include <sourcefolder.h>
#include <papersize.h>
#include <logwindow.h>

class Logic : public QObject {

    Q_OBJECT

public:
    Logic();
    QWidget*            getPaperSize(int arrayElementLocation);
    QWidget*            getSourceFolder();
    QPlainTextEdit*     getLogWindow();
    QDialogButtonBox*   getActionBtns();

private:
    QStringList         getFileList();
    QSize               getDocSize(QString fileName);
    int                 getDocsPaperSizeArrayLocation(QSize pageSize);
    void                handleSortFilesBtn();
    void                handleSourceFolderBtn();
    bool                getIsInRange(int val, int lwrA, int uprA, int lwrB, int uprB);
    bool                getMimeIsOk(QString);
    QString             copyFileToFolder(QString fileName, QString outputFolder);

    QString             homeFolder;
    PaperSize          *paperSizes[7];
    SourceFolder       *sourceFolder;
    LogWindow          *logWindow;
    QString             sourceFolderChoice;
    QDialogButtonBox   *actionBtns;
    bool                proceed = true;
};

#endif // LOGIC_H


