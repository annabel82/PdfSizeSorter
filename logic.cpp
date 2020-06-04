#include <logic.h>

/*! ------------------------------------------------------------------------
  Called by mainwidnow to handle the logic of the application. This then
  calls source folder, papersize and log window
*/
Logic::Logic()
{
    homeFolder = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

    // In the unlikely event that default (home) folder value is
    // the actual sourceFolder the user wants, set it as such.
    sourceFolderChoice = homeFolder;

    // True because the text box in source folder is read only.
    sourceFolder = new SourceFolder(true, homeFolder);

    // True because it's a known size, which means the entry
    // will have spinboxes to provide some flexibility in it's
    // min and max height and width.
    paperSizes[0]  = new PaperSize("2A0", 1189, 1682, homeFolder, true);
    paperSizes[1]  = new PaperSize( "A0",  841, 1189, homeFolder, true);
    paperSizes[2]  = new PaperSize( "A1",  594,  841, homeFolder, true);
    paperSizes[3]  = new PaperSize( "A2",  420,  594, homeFolder, true);
    paperSizes[4]  = new PaperSize( "A3",  297,  420, homeFolder, true);
    paperSizes[5]  = new PaperSize( "A4",  210,  297, homeFolder, true);
    paperSizes[6]  = new PaperSize( "A5",  210,  148, homeFolder, true);
    otherPaperSize = new PaperSize( "Other", 0,    0, homeFolder, false);

    logWindow = new LogWindow;

    // We want the log to take up any extra space upon window
    // resize.
    logWindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}



/*! ------------------------------------------------------------------------
  Called when the user clicks the "Sort Files" button and does the requests
  a list of all pdfs in the source folder and sorts them (after some basic
  checks are passed). Also responsible for outputting to the log window
*/
void Logic::handleSortFilesBtn() {

    QString sourceFile;
    QStringList allFileNames = getFileList();

    foreach (QString fileName, allFileNames)
    {
        bool isNotValid = true;
        sourceFile = sourceFolderChoice + fileName;

        // If the proceed flag is still true, and the file exists,
        // and it's mime type returns as a pdf
        if (proceed && QFile::exists(sourceFile) && getMimeIsOk(sourceFile)) {

            // Get the size of the doc, the getDocSize function
            // returns 0 for both height and width of the pdf
            // was unreadable
            QSize pageSize = getDocSize(fileName);

            if (pageSize.height() != 0 && pageSize.width() != 0)
            {
                isNotValid = false;

                // Return the location in the paper array for document size.
                int elementLocation = getDocsPaperSizeArrayLocation(pageSize);

                QString outputFolder;

                // If we don't know the size
                if (elementLocation == 404)
                {
                    // Set the outfolder from otherPapoerSize object.
                    outputFolder = otherPaperSize->getOutputFolder();
                }
                else
                {
                    // Otherwise use the array location value to determine
                    // output folder.
                    outputFolder = paperSizes[elementLocation]->getOutputFolder();
                }

                // --------------------------------------------

                // Attempt our copy and return a QString detailing outcome.
                QString copyAttemptOutcome = copyFileToFolder(fileName, outputFolder);
                logWindow->print(copyAttemptOutcome);
            }
        }

        if (isNotValid)
        {
            logWindow->print("'" + sourceFolderChoice + fileName + "' not found or not a valid pdf file.");
        }
    }

    // Finally we add an empty line to our logWindow and ensure the continue flag is
    // set to true, so next time the button button is used, the sequences re-tries
    logWindow->n();
    proceed = true;
}



/*! ------------------------------------------------------------------------
  Called by handleSortFilesBtn to get a list of .pdf files in the source
  folder
  \returns      A list of .pdf files in the source folder
*/
QStringList Logic::getFileList() {

    if (QFile::exists(sourceFolderChoice))
    {
        QDir recoredDir(sourceFolderChoice);
        recoredDir.setNameFilters(QStringList()<<"*.pdf");

        // Return a String array of all files named .pdf
        // in the source folder
        return recoredDir.entryList(QDir::NoDotAndDotDot | QDir::Files);
    }
    else
    {
        // If source folder doesn't exist set our continue flag to
        // false, print a message to the log window  and return NULL.
        proceed = false;
        logWindow->print("Source folder '" + sourceFolderChoice + "' not found or not readable.");
        QStringList empty;
        return empty;
    }
}



/*! ------------------------------------------------------------------------
  Called from handleSortFilesBtn for each file found in in the source folder
  to check the mime type of the file
  \param    fileName      The name of the file
  \returns                  Whether or not the mime check passed
*/
bool Logic::getMimeIsOk(QString fileName)
{
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(fileName);

    if (mime.inherits("application/pdf"))
    {
        return true;
    }

    return false;
}



/*! ------------------------------------------------------------------------
  Called second by handleSortFilesBtn after getFileList and GetMimeIsOk in
  order to get the size of the first page of the .pdf file.
  \param    fileName    The name of the file
  \returns              The size of the first part of the .pdf file,
                        will return 0, 0 if unable to calculate it
*/
QSize Logic::getDocSize(QString fileName)
{
    QSize pageSize(0, 0);

    // Create a variable which holds a poppler document.
    // and then load a doc into it
    Poppler::Document *doc;
    doc = Poppler::Document::load(sourceFolderChoice + fileName);

    if (doc && !doc->isLocked() && doc != 0)
    {
        // Get the first page from the document and then its size
        Poppler::Page *page = doc->page(0);

        pageSize = page->pageSize();
    }

    delete doc;

    return pageSize;
}



/*! ------------------------------------------------------------------------
  Called for each document returned by the getFileList function after the
  user clicks the "Sort Files" button.
  \param    pageSize    The size of the current pdf's first page
  \returns              An int that correlates to the associated papersize
                        element in the papersize array or 404 if the size
                        was not found (it belongs in the 'other' folder).
*/
int Logic::getDocsPaperSizeArrayLocation(QSize pageSize)
{
    int width  = pageSize.width()  * 0.3528;// Calculate width and height in millimeteres from the amount
    int height = pageSize.height() * 0.3528;// of points (kind of like dots) the page contains.
    int elementLocation = 0;// This serves as a counter so we can return element location.

    for (PaperSize *paperSize : paperSizes)
    {
        // Get the min and max width and height allowed in order for
        // our document to qualify as being this size, then check to
        // see if our document matches the ranges.
        int minW = paperSize->getMinWidth();
        int maxW = paperSize->getMaxWidth();
        int minH = paperSize->getMinHeight();
        int maxH = paperSize->getMaxHeight();

        // If the document is within range of this paper size's values
        // return an int that correlates to the element location of
        // the associated paper size.
        if (getIsInRange(width, minW, maxW, minH, maxH) && getIsInRange(height, minW, maxW, minH, maxH)) {

            return elementLocation;
        }
        // Increment our counter which serves to describe the location
        // of the paper size's location in the paper size array.
        elementLocation++;
    }

    // Returns 404 if size isn't within range of a known paperSize.
    return 404;
}



/*! ------------------------------------------------------------------------
  Called for each document returned by the getFileList that also passes mine
  type validity check etc. Does the actual copying of the .pdf to the
  correct folder
  \param    fileName        The name of the .pdf file to copy
  \param    outputFolder    The name of the folder to copy the .pdf
  \returns                  A string stating the event which occured when
                            attempting to copy the file to the folder
*/
QString Logic::copyFileToFolder(QString fileName, QString outputFolder)
{
    QDir qOutputFolder(outputFolder);

    if (!qOutputFolder.exists())
    {
        // If it doesn't exist create it.
        qOutputFolder.mkpath(outputFolder);
    }

    // --------------------------------------------

    if (!QFile::exists(outputFolder + fileName))
    {
        QFile::copy(sourceFolderChoice + fileName, outputFolder + fileName);
    }
    else
    {
        return "A file named '" + fileName + "' already exists in '" + outputFolder + "'";
    }

    // --------------------------------------------

    if (QFile::exists(outputFolder + fileName))
    {
        return "Successfully copied '" + fileName + "' to '" + outputFolder + "'";
    }
    else
    {
        // If the file doesn't exist, then the copy to output folder
        // failed, so add a failure message to log window.
        return "Failed to copy '" + fileName + "' to '" + outputFolder + "'";
    }
}



/*! ------------------------------------------------------------------------
  Determines if val is between min and max width and height. This is called
  twice from getDocsPaperSizeArrayLocation
  \param    val     The value to test against, could be height or width of
                    the first page of the currently tested .pdf file
  \param    minW    The papersizes min allowed width
  \param    maxW    The papersizes max allowed width
  \param    minH    The papersizes min allowed height
  \param    maxH    The papersizes max allowed height
  \returns          Whether or not the val matches the min and max height
                    and width
*/
bool Logic::getIsInRange(int val, int minW, int maxW, int minH, int maxH)
{
    // Returns true if val is between min & max width or height
    return (val >= minW && val <= maxW) || (val >= minH && val <= maxH);
}



/*! ------------------------------------------------------------------------
  Called when user presses the source folder button, sets the newly chosen
  source folder
  \param    sourceFolderChoice
*/
void Logic::setSourceFolderChoice(QString sourceFolderChoice)
{
    // Set local (convenience) sourceFolderChoice variable.
    this->sourceFolderChoice = sourceFolderChoice;

    // Then set the QLineEdit source folder text accordingly.
    sourceFolder->setSourceFolderText(sourceFolderChoice);

    for (PaperSize *paperSize : paperSizes)
    {
        // If a bespoke output folder hasn't been chosen for that size.
        if (!paperSize->getHasChosenBespokeFolder())
        {

            // Send the new source folder so the sizes can update their
            // respective output folders
            paperSize->setOutputFolder(sourceFolderChoice);
        }
    }

    // If the "Other" paper size doesn't have a bespoke output choice,
    // send the new source folder so it can update its output folder.
    if (!otherPaperSize->getHasChosenBespokeFolder())
    {
        otherPaperSize->setOutputFolder(sourceFolderChoice);
    }
}



/*! ------------------------------------------------------------------------
 Allows mainWindow to get new sourceFolder object
 \returns   The source folder widget
*/
QWidget* Logic::getSourceFolder()
{
    return sourceFolder;
}



/*! ------------------------------------------------------------------------
 Allows mainWindow to get the paperSize object located at the element number
 passed in the variable
 \param     arrayElementLocation    The element in the array from which to
                                    return a papersize object
 \returns                           The associated papersize object
*/
QWidget* Logic::getPaperSize(int arrayElementLocation)
{
    return paperSizes[arrayElementLocation];
}



/*! ------------------------------------------------------------------------
 Allows mainWindow to get the 'other' paperSize object
 \returns   The papersize object
*/
QWidget* Logic::getOtherPaperSize()
{
    return otherPaperSize;
}



/*! ------------------------------------------------------------------------
 Allows mainMindow to get new logWindow object
 \returns   The logwindow object
*/
QPlainTextEdit* Logic::getLogWindow()
{
    return logWindow;
}
