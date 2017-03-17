#include <logic.h>

Logic::Logic()
{
    homeFolder = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),
                                        QStandardPaths::LocateDirectory);
    sourceFolderChoice = homeFolder;                                                            // In the unlikely event that default (home) folder value is
                                                                                                // the actual sourceFolder the user wants, set it as such.
    // --------------------------------------------

    sourceFolder = new SourceFolder(true);                                                      // True because the text box in source folder is read only.

    // --------------------------------------------

    paperSizes[0] = new PaperSize("2A0", 1189, 1682, homeFolder);
    paperSizes[1] = new PaperSize( "A0",  841, 1189, homeFolder);
    paperSizes[2] = new PaperSize( "A1",  594,  841, homeFolder);
    paperSizes[3] = new PaperSize( "A2",  420,  594, homeFolder);
    paperSizes[4] = new PaperSize( "A3",  297,  420, homeFolder);
    paperSizes[5] = new PaperSize( "A4",  210,  297, homeFolder);
    paperSizes[6] = new PaperSize( "A5",  210,  148, homeFolder);

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


void Logic::handleRunBtn() {                                                                    // Called when the user clicks the "Sort Files" button.

    QStringList allFileNames = getFileList();                                                   // Get a QString array of all files that exist in the selected
                                                                                                // source folder.
    int i = 0;

    foreach (QString fileName, allFileNames) {

        QFile qFileNameWithDir(sourceFolderChoice + "/" + fileName);                            // Cast to QFile so we can check the file still exists.

        if (qFileNameWithDir.exists()) {                                                        // If the file exists

            QSize pageSize = getDocSize(sourceFolderChoice + "/" + fileName);                   // Return the size of the page.
            int paperSizeElementLocation = getDocsPaperSizeArrayLocation(pageSize);             // Return the name of the papersize this document is.

            if (copyFileToFolder(fileName, paperSizeElementLocation)) {                         // Finally copy the file to associated output folder.

                logWindow->print(
                              //    paperSizeName + "document  '" + sourceFolderChoice + "/"
                                fileName + "' successfully moved to "
                                + paperSizes[paperSizeElementLocation]->getOutputFolder());

            } else {


            }

        } else {                                                                                // If the file doesn't exists

            logWindow->print("'" + sourceFolderChoice + "/" + fileName + "' not found.");       // Print a sane message to the logWindow.
        }
    }
}


// -------------------------------------------------------------------------


QStringList Logic::getFileList() {

    QDir recoredDir(sourceFolderChoice);
    recoredDir.setNameFilters(QStringList()<<"*.pdf");

    return recoredDir.entryList(QDir::NoDotAndDotDot | QDir::Files);
}


// -------------------------------------------------------------------------


QSize Logic::getDocSize(QString fileNameWithDir) {                                              // Called by handleRunBtn() after getFileList().

    Poppler::Document *doc;                                                                     // Create a variable which holds a poppler document.
    doc = Poppler::Document::load(fileNameWithDir);                                             // Load an actual pdf into that variable.
    Poppler::Page *page = doc->page(0);                                                         // Get the first page from the document.

    QSize pageSize = page->pageSize();                                                          // Get the size of the page.
    delete doc;                                                                                 // Delete the doc before we return pageSize

    return pageSize;
}


// -------------------------------------------------------------------------

                                                                                                // Called for each document returned by the getFileList()
int Logic::getDocsPaperSizeArrayLocation(QSize pageSize) {                                     // function after the user clicks the "Sort Files" button.

    int width  = pageSize.width()  * 0.3528;                                                    // Calculate width and height in millimeteres from the amount
    int height = pageSize.height() * 0.3528;                                                    // of points (kind of like dots) the page contains.
    int elementLocation = 0;                                                                    // This serves as a counter so we can return element location.

    for (PaperSize *paperSize : paperSizes) {                                                   // For each size in our papersize array

        int minW = paperSize->getMinWidth();                                                    // Get the min and max width and height allowed in order for
        int maxW = paperSize->getMaxWidth();                                                    // our document to qualify as being this size, then check to
        int minH = paperSize->getMinHeight();                                                   // see if our document matches the ranges.
        int maxH = paperSize->getMaxHeight();

        if (getIsInRange(width, minW, maxW, minH, maxH) && getIsInRange(height, minW, maxW, minH, maxH)) {

            return elementLocation;                                                             // If the document is within range of this paper size's values
        }                                                                                       // return an int that correlates to the element location of
                                                                                                // the associated paper size.
    }
    elementLocation++;                                                                          // Increment our counter which serves to describe the location
                                                                                                // of the paper size's location in the paper size array.
    return NULL;
}                                                                                               // Returns NULL if size isn't within range of a paperSize.


// -------------------------------------------------------------------------


bool Logic::copyFileToFolder(QString fileName, int paperSizeElementLocation) {


return true;

}


// -------------------------------------------------------------------------


bool Logic::getIsInRange(int val, int lowA, int upA, int lowB, int upB) {                       // Should be checking orientation but unsure if reliable

    return (val >= lowA && val <= upA) || (val >= lowB && val <= upB);                          // Returns true if val is between Lower & Upper A or B
}


// -------------------------------------------------------------------------


void Logic::handleSourceFolderBtn() {                                                           // Called when user presses the source folder button

    sourceFolderChoice = QFileDialog::getExistingDirectory(sourceFolder,                        // Get the  from the user
                         tr("Select Directory"), homeFolder,
                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + "/";

    sourceFolder->setSourceFolderText(sourceFolderChoice);                                      // Set the cosmetic text line in the source widget

    for (PaperSize *paperSize : paperSizes) {                                                   // Then for each paperSize

        if (!paperSize->getHasChosenBespokeFolder()) {                                          // If a bespoke output folder hasn't been chosen for that size

            paperSize->setOutputFolder(sourceFolderChoice);                                     // Send the new source folder so the sizes can update their
        }                                                                                       // respective output folders
    }
}


// -------------------------------------------------------------------------


QWidget* Logic::getSourceFolder() {                                                             // Allows mainWindow to get new sourceFolder object

    return sourceFolder;
}


// -------------------------------------------------------------------------


QWidget* Logic::getPaperSize(int arrayElementLocation) {                                        // Allows mainWindow to get new paperSize object

    return paperSizes[arrayElementLocation];
}


// -------------------------------------------------------------------------


QPlainTextEdit* Logic::getLogWindow() {                                                         // Allows mainMindow to get new logWindow object

    return logWindow;
}


// -------------------------------------------------------------------------


QDialogButtonBox* Logic::getActionBtns() {                                                      // Allows mainMindow to get new actionBtns object

    return actionBtns;
}


