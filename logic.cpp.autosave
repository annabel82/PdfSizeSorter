#include <logic.h>

Logic::Logic()
{
    homeFolder = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),
                                        QStandardPaths::LocateDirectory);
    sourceFolder = homeFolder;                                                            // In the unlikely event that default (home) folder value is
                                                                                                // the actual sourceFolder the user wants, set it as such.
    // --------------------------------------------

    sourceFolder = new SourceFolder(true);                                                      // True because the text box in source folder is read only.

    // --------------------------------------------

    paperSizes[0] = new PaperSize("2A0", 1189, 1682, homeFolder);
    paperSizes[1] = new PaperSize("A0", 841, 1189, homeFolder);
    paperSizes[2] = new PaperSize("A1", 594, 841, homeFolder);
    paperSizes[3] = new PaperSize("A2", 420, 594, homeFolder);
    paperSizes[4] = new PaperSize("A3", 297, 420, homeFolder);
    paperSizes[5] = new PaperSize("A4", 210, 297, homeFolder);
    paperSizes[6] = new PaperSize("A5", 210, 148, homeFolder);

    // --------------------------------------------

    logWindow = new LogWindow;
    logWindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);                   // We want the log to take up any extra space upon window
                                                                                                // resize.
    // --------------------------------------------

    actionBtns = new QDialogButtonBox();
    actionBtns->addButton(tr("Sort Files"), QDialogButtonBox::AcceptRole);
    actionBtns->addButton(tr("Close"),QDialogButtonBox::RejectRole);

    // --------------------------------------------

    connect(actionBtns, &QDialogButtonBox::accepted,              this, [this] { handleRunBtn(); });
    connect(actionBtns, &QDialogButtonBox::rejected,              this, [this] { QApplication::quit(); });
    connect(sourceFolder->sourceFolderBtn, &QPushButton::clicked, this, [this] { handleSourceFolderBtn(); });

}


// -------------------------------------------------------------------------


void Logic::handleRunBtn() {

    getFileList();

    for (int i = 0; i < allFiles.size(); ++i) {

        fileName = sourceFolder + "/" + allFiles.at(i).toLocal8Bit().constData();

        getDocSize(fileName);

        int pageWidth = pageSize.width() * 0.3528;
        int pageHeight = pageSize.height() * 0.3528;

        // ---------------------------------

        logWindow->print("Found: \"" + sourceFolder + "/" + allFiles.at(i).toLocal8Bit().constData() +
                         "\" which is " + QString::number(pageWidth) + "mm x " + QString::number(pageHeight) +
                         "mm -  making it " + getDocSizeName(pageWidth, pageHeight));
    }
}


// -------------------------------------------------------------------------


void Logic::getFileList() {

    QDir recoredDir(sourceFolderChoice);
    recoredDir.setNameFilters(QStringList()<<"*.pdf");
    allFiles = recoredDir.entryList(QDir::NoDotAndDotDot | QDir::Files);
}


// -------------------------------------------------------------------------


void Logic::getDocSize() {                                                                      // Called by handleRunBtn() after getFileList().

    Poppler::Document *doc;                                                                     // Create a variable which holds a poppler document.
    doc = Poppler::Document::load(fileName);                                                    // Load an actual pdf into that variable.
    Poppler::Page *page = doc->page(0);                                                         // Get the first page from the document.

    pageSize = page->pageSize();                                                                // Get the size of the page.
    delete doc;
}


// -------------------------------------------------------------------------

                                                                                                // Called for each document returned by the getFileList()
QString Logic::getDocSizeName(int width, int height) {                                          // function after the user clicks the "run" button. The width
                                                                                                // width and height are returned by the getDocSize() function
    for (PaperSize *paperSize : paperSizes) {                                                   // which runs prior to this.

        int minW = paperSize->getMinWidth();                                                    // For every papersize in our papersizes array.
        int maxW = paperSize->getMaxWidth();
        int minH = paperSize->getMinHeight();
        int maxH = paperSize->getMaxHeight();

        if (getIsInRange(width, minW, maxW, minH, maxH) && getIsInRange(height, minW, maxW, minH, maxH)) {

            return paperSize->getName();                                                        // For each size in our papersize array, check if the received
        }                                                                                       // document's width and height are within the range of the
                                                                                                // current papersize and if so return the name of the papersize.
    }
    return "Unknown";                                                                           // Returns "unknown" if size isn't within range of a paperSize.
}


// -------------------------------------------------------------------------


bool Logic::getIsInRange(int val, int lowA, int upA, int lowB, int upB) {                       // Should be checking orientation but unsure if reliable

    return (val >= lowA && val <= upA) || (val >= lowB && val <= upB);                          // Returns true if val is between Lower & Upper A or B
}


// -------------------------------------------------------------------------


void Logic::handleSourceFolderBtn() {                                                           // Called when user presses the source folder button

    sourceFolder = QFileDialog::getExistingDirectory(sourceFolder,                        // Get the  from the user
                         tr("Select Directory"), homeFolder,
                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + "/";

    sourceFolder->setSourceFolderText(sourceFolder);                                      // Set the cosmetic text line in the source widget

    for (PaperSize *paperSize : paperSizes) {                                                   // Then for each paperSize

        if (!paperSize->getHasChosenBespokeFolder()) {                                          // If a bespoke output folder hasn't been chosen for that size

            paperSize->setOutputFolder(sourceFolder);                                     // Send the new source folder so the sizes can update their
        }                                                                                       // respective output folders
    }
}


// -------------------------------------------------------------------------


QWidget* Logic::getSourceFolder() {                                                             // Allows mainWindow to get new sourceFolder object

    return sourceFolder;
}


// -------------------------------------------------------------------------


QWidget* Logic::getPaperSize(int no) {                                                          // Allows mainWindow to get new paperSize object

    return paperSizes[no];
}


// -------------------------------------------------------------------------


QPlainTextEdit* Logic::getLogWindow() {                                                         // Allows mainMindow to get new logWindow object

    return logWindow;
}


// -------------------------------------------------------------------------


QDialogButtonBox* Logic::getActionBtns() {                                                      // Allows mainMindow to get new actionBtns object

    return actionBtns;
}


