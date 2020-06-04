#include <sourcefolder.h>


/*! ------------------------------------------------------------------------
  Constructs the source folder GUI component
  \param    readOnly    Whether or not the QLineEdit should be readonly
  \param    homeFolder  The users home folder location
*/
SourceFolder::SourceFolder(bool readOnly, QString homeFolder)
{
    QLabel *sourceFolderLabel = new QLabel(tr("Source Folder Location"));

    sourceFolderText = new QLineEdit(homeFolder);
    sourceFolderText->setStatusTip("Currently selected source pdf files location");
    sourceFolderText->setReadOnly(readOnly);

    sourceFolderBtn = new QPushButton(tr("  Choose location ...  "), this);
    sourceFolderBtn->setStatusTip("Choose the location of source pdf files");

    QGridLayout *sourceContainer = new QGridLayout;
    sourceContainer->setVerticalSpacing(12);
    //                                Left  T   R   Bottom
    sourceContainer->setContentsMargins(10, 10, 12, 10);

    // Second column which is number 1 (after label row which is 0). This
    // is set so that unknown tab without spinboxes aligns properly.
    sourceContainer->setRowMinimumHeight(1, 25);

    // Choose folder button minimum size.
    sourceContainer->setColumnMinimumWidth(2, 96);
    sourceContainer->addWidget(sourceFolderLabel, 0, 1);
    sourceContainer->addWidget(sourceFolderText, 1, 1);
    sourceContainer->addWidget(sourceFolderBtn, 1, 2);

    setLayout(sourceContainer);
}



/*! ------------------------------------------------------------------------
  Allows logic to update the source line edit box
  \param    sourceFolderText    The text with which to update
*/
void SourceFolder::setSourceFolderText(QString sourceFolderText)
{
    this->sourceFolderText->setText(sourceFolderText);
}
