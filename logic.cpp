#include <logic.h>

Logic::Logic()
{
    homeFolder = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),
                                        QStandardPaths::LocateDirectory);
    sourceFolderChoice = homeFolder;                                                            // In the unlikely event that default (home) folder value is
                                                                                                // the actual sourceFolder the user wants, set it as such.
    // --------------------------------------------

    sourceFolder = new SourceFolder(true, homeFolder);                                          // True because the text box in source folder is read only.

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

    connect(actionBtns, &QDialogButtonBox::accepted,              this, [this] { handleSortFilesBtn(); });
    connect(actionBtns, &QDialogButtonBox::rejected,              this, [this] { QApplication::quit(); });
    connect(sourceFolder->sourceFolderBtn, &QPushButton::clicked, this, [this] { handleSourceFolderBtn(); });

}


// -------------------------------------------------------------------------


void Logic::handleSortFilesBtn() {                                                              // Called when the user clicks the "Sort Files" button.

    QString sourceFile;
    QStringList allFileNames = getFileList();                                                   // Get a QString array of all files that exist in the
                                                                                                // selected source folder.
    // --------------------------------------------

    foreach (QString fileName, allFileNames) {                                                  // Foreach through the file list array.

        sourceFile = sourceFolderChoice + "/" + fileName;

        if (proceed && QFile::exists(sourceFile) && getMimeIsOk(sourceFile)) {                  // If the file exists, and it's mime type returns as a pdf
                                                                                                // and our continue flag is still true.
            QSize pageSize = getDocSize(fileName);
                                                                                                // Return the size of the document.
            // --------------------------------------------

            int elementLocation = getDocsPaperSizeArrayLocation(pageSize);                      // Return the location in the paper array for document size.
            QString outputFolder;

            if (elementLocation == 404) {

                outputFolder = sourceFolderChoice + "/Size-Unknown";                            // Set a specific output folder if we don't know the size.

            } else {

                outputFolder = paperSizes[elementLocation]->getOutputFolder();                  // Otherwise use the array location value to determine
            }                                                                                   // output folder.

            // --------------------------------------------

            QString copyAttemptOutcome = copyFileToFolder(fileName, outputFolder);              // Attempt our copy and return a QString detailing outcome.
            logWindow->print(copyAttemptOutcome);                                               // Then send the returned outcome string to log window.

        } else {

            logWindow->print("'" + sourceFolderChoice + "/" + fileName +                        // Or if the file doesn't exists, Print a sane message to
                             "' not found or not a valid pdf file.");                           // the logWindow.
        }
    }

    logWindow->n();                                                                             // Finally we add an empty line to our logWindow and ensure
    proceed = true;                                                                             // the continue flag is set to true, so next time the
}                                                                                               // button is used, the sequences re-tries.


// -------------------------------------------------------------------------


QStringList Logic::getFileList() {                                                              // Called first by handleSortFilesBtn().

    if (QFile::exists(sourceFolderChoice)) {                                                    // If our source folder choice exists

        QDir recoredDir(sourceFolderChoice);
        recoredDir.setNameFilters(QStringList()<<"*.pdf");

        return recoredDir.entryList(QDir::NoDotAndDotDot | QDir::Files);                        // Return a String array of all .pdf files in the source
                                                                                                // folder.
    } else {

        proceed = false;
        logWindow->print("Source folder '" + sourceFolderChoice +                               // If source folder doesn't exist set our continue flag to
                         "' not found or not readable.");                                       // false, print a message to the log window  and return NULL.
        QStringList empty;
        return empty;
    }
}


// -------------------------------------------------------------------------


bool Logic::getMimeIsOk(QString sourceFile) {                                                   // Called from handleSortFilesBtn() for each file found in
                                                                                                // source folder.
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(sourceFile);

    if (mime.inherits("application/pdf")) {                                                     // Check mime type returns pdf and return true if so

        return true;
                                                                                                // Otherwise return false.
    } else {

        return false;
    }
}


// -------------------------------------------------------------------------


QSize Logic::getDocSize(QString fileName) {                                                     // Called second by handleSortFilesBtn() after getFileList().

    Poppler::Document *doc;                                                                     // Create a variable which holds a poppler document.
    doc = Poppler::Document::load(sourceFolderChoice + "/" + fileName);                         // Load an actual pdf into that variable.
    Poppler::Page *page = doc->page(0);                                                         // Get the first page from the document.

    QSize pageSize = page->pageSize();                                                          // Get the size of the page.
    delete doc;                                                                                 // Delete the doc before we return pageSize

    return pageSize;
}


// -------------------------------------------------------------------------

                                                                                                // Called for each document returned by the getFileList()
int Logic::getDocsPaperSizeArrayLocation(QSize pageSize) {                                      // function after the user clicks the "Sort Files" button.

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
        elementLocation++;                                                                      // the associated paper size.
    }                                                                                           // Increment our counter which serves to describe the location
                                                                                                // of the paper size's location in the paper size array.
    return 404;
}                                                                                               // Returns 404 if size isn't within range of a known paperSize.


// -------------------------------------------------------------------------


QString Logic::copyFileToFolder(QString fileName, QString outputFolder) {                       // Called for each document returned by the getFileList() that
                                                                                                // also passes mine type validity check.
    QDir qOutputFolder(outputFolder);

    if (!qOutputFolder.exists()) {
                                                                                                // Check to see if the output folder exists.
        qOutputFolder.mkpath(outputFolder);                                                     // If it doesn't exist create it.
    }

    // --------------------------------------------

    if (!QFile::exists(outputFolder + "/" + fileName)) {
                                                                                                // Check to see if the file already exists
        QFile::copy(sourceFolderChoice + "/" + fileName, outputFolder + "/" + fileName);        // If it doesn't already exist copy it.

    } else {

        return "Source file '" + fileName + "' already exists in '" + outputFolder + "'";       // If it already exists return a message that reflects this.
    }

    // --------------------------------------------

    if (QFile::exists(outputFolder + "/" + fileName)) {
                                                                                                // Again check to see if the file exists
        return "Successfully copied '" + fileName + "' to '" + outputFolder + "'";              // If it does add a success message to the log window.

    } else {
                                                                                                // If the file doesn't exist, the copy to output folder failed
        return "Failed to copy '" + fileName + "' to '" + outputFolder + "'";                   // so add a failure message to log window.
    }
}


// -------------------------------------------------------------------------


bool Logic::getIsInRange(int val, int lwrA, int uprA, int lwrB, int uprB) {                     // Should be checking orientation but unsure if reliable

    return (val >= lwrA && val <= uprA) || (val >= lwrB && val <= uprB);                        // Returns true if val is between Lower & Upper A or B
}


// -------------------------------------------------------------------------


void Logic::handleSourceFolderBtn() {                                                           // Called when user presses the source folder button

    QFileDialog srcDialog;                                                                      // Create new dialog template which only allows the user to select
    srcDialog.setFileMode(QFileDialog::Directory);                                              // folders and whose default folder is the user's home directory.
    srcDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last());

    if (srcDialog.exec()) {                                                                     // If user clicked ok to confirm their choice

        sourceFolderChoice = srcDialog.selectedFiles()[0];                                      // Get their first clicked folder as the location for output
        sourceFolder->setSourceFolderText(sourceFolderChoice);                                  // Set the cosmetic text line in the source widget

        for (PaperSize *paperSize : paperSizes) {                                               // Then for each paperSize

            if (!paperSize->getHasChosenBespokeFolder()) {                                      // If a bespoke output folder hasn't been chosen for that size.

                paperSize->setOutputFolder(sourceFolderChoice);                                 // Send the new source folder so the sizes can update their
            }                                                                                   // respective output folders
        }
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


