#include <papersize.h>


/*! ------------------------------------------------------------------------
  Constructs a papersize tab, called by the logic class
  \param    name            Name of the papersize
  \param    width           Width of papersize
  \param    height          Height of papersize
  \param    homeFolder      Users home folder location
  \param    isKnownSize     Whether or not this is a known paper size (e.g. A4)
*/
PaperSize::PaperSize(QString name, int width, int height, QString homeFolder, bool isKnownSize)
{
    this->name = name;

    if (isKnownSize)
    {
        // Create all the spin boxes
        minWidthLabel = new QLabel(tr("Min Width"));
        minWidth = new QSpinBox();
        minWidth->setStatusTip("Set the minimum " + name + " width");
        minWidth->setRange(width - 60, width);
        minWidth->setSuffix("mm");
        minWidth->setSingleStep(5);
        minWidth->setValue(width - 20);

        // -------------------------------------

        maxWidthLabel = new QLabel(tr("Max Width"));
        maxWidth = new QSpinBox();
        maxWidth->setStatusTip("Set the maximum " + name + " width");
        maxWidth->setRange(width, width + 60);
        maxWidth->setSuffix("mm");
        maxWidth->setSingleStep(5);
        maxWidth->setValue(width + 20);

        // -------------------------------------

        minHeightLabel = new QLabel(tr("Min Height"));
        minHeight = new QSpinBox();
        minHeight->setStatusTip("Set the minimum " + name + " height");
        minHeight->setRange(height - 60, height);
        minHeight->setSuffix("mm");
        minHeight->setSingleStep(5);
        minHeight->setValue(height - 20);

        // -------------------------------------

        maxHeightLabel = new QLabel(tr("Max Height"));
        maxHeight = new QSpinBox();
        maxHeight->setStatusTip("Set the maximum " + name + " height");
        maxHeight->setRange(height, height + 60);
        maxHeight->setSuffix("mm");
        maxHeight->setSingleStep(5);
        maxHeight->setValue(height + 20);
    }

    QLabel *outputFolderLabel = new QLabel(tr("Output Folder"));
    outputFolderText = new QLineEdit(homeFolder + name + "/");
    outputFolderText->setStatusTip("Currently selected location that " + name + " sized pdf files will be copied in to");

    QPushButton *outputFolderBtn = new QPushButton(tr("Choose location ..."), this);
    outputFolderBtn->setStatusTip("Choose the location " + name + " sized pdf files will be copied in to");

    connect(outputFolderBtn, &QPushButton::clicked, this, [this]{ handleFolderBtn(); });

    // -------------------------------------

    QGridLayout *container = new QGridLayout;
    container->setVerticalSpacing(6);
    //                          Left  T   R   Bottom
    container->setContentsMargins(10, 10, 10, 10);
    // Second column numbered 1 (after label row which is 0). This
    // is so that unknown tab without spinboxes aligns properly.
    container->setRowMinimumHeight(1, 25);

    if (isKnownSize)
    {
        // If is a known size (aka not the wildcard unknown papersize)
        // we need to tailor spinboxes a little further and then add
        // them to the container widget.
        container->setColumnMinimumWidth(0, 92);
        container->setColumnMinimumWidth(1, 92);
        container->setColumnMinimumWidth(2, 92);
        container->setColumnMinimumWidth(3, 92);

        container->addWidget(minWidthLabel, 0, 0);
        container->addWidget(minWidth, 1, 0);
        container->addWidget(maxWidthLabel, 0, 1);
        container->addWidget(maxWidth, 1, 1);
        container->addWidget(minHeightLabel, 0, 2);
        container->addWidget(minHeight, 1, 2);
        container->addWidget(maxHeightLabel, 0, 3);
        container->addWidget(maxHeight, 1, 3);
    }

    // Set "Choose folder" button minimum size.
    container->setColumnMinimumWidth(5, 96);
    container->addWidget(outputFolderLabel, 0, 4);
    container->addWidget(outputFolderText, 1, 4);
    container->addWidget(outputFolderBtn, 1, 5);

    setLayout(container);
}



/*! ------------------------------------------------------------------------
  Called when user clicks the output folder btn and sets a
  bespoke folder into which the files that match this papersize
  will be copied.
*/
void PaperSize::handleFolderBtn()
{
    // Create new dialog which only allows the selection of
    // folders & whose default folder is tuser's home directory.
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last());

    // If user clicked ok to confirm their choice
    if (dialog.exec())
    {
        // Set true so choosing a new source folder doesn't auto
        // update this output folder any longer.
        hasChosenBespokeFolder = true;

        // Get first clicked folder as "choice" value.
        QString choice = dialog.selectedFiles()[0];

        // Test to see if the OS appends our location choice results
        // in a trailing forward slash.
        if (!choice.endsWith("/"))
        {
            // If it doesn't have a trailing forward slash, add one and
            // then set the QLineEdit output folder text accordingly.
            outputFolderText->setText(choice + "/");
        }
        else
        {
            // Otherwise simply set the value as QLineEdit output
            // folder text accordingly
            outputFolderText->setText(choice);
        }
    }
}



/*! ------------------------------------------------------------------------
  Called from Logic if hasChosenBespokeFolder returns false
  This updates the output folder of this paper size such
  that it's a subfolder of the source folder the just chose.
  \param    sourceFolder     The chosen source folder
*/
void PaperSize::setOutputFolder(QString sourceFolder)
{
    outputFolderText->setText(sourceFolder + name + "/");
}



/*! ------------------------------------------------------------------------
  Called from logic to get whether or not the user has chosen
  a bespoke output folder for this papersize.
  \returns  Whether or not the user has chosen a bespoke folder location
            to output this size of pdf in to
*/
bool PaperSize::getHasChosenBespokeFolder()
{
    return hasChosenBespokeFolder;
}



/*! ------------------------------------------------------------------------
  Called from logic to get min width
  \returns      The papersizes min width
*/
int PaperSize::getMinWidth()
{
    return minWidth->value();
}



/*! ------------------------------------------------------------------------
  Called from logic to get max width
  \returns      The papersizes max width
*/
int PaperSize::getMaxWidth()
{
    return maxWidth->value();
}



/*! ------------------------------------------------------------------------
  Called from logic to get min height
  \returns      The papersizes min height
*/
int PaperSize::getMinHeight()
{
    return minHeight->value();
}



/*! ------------------------------------------------------------------------
  Called from logic to get max height
  \returns      The papersizes max height
*/
int PaperSize::getMaxHeight()
{
    return maxHeight->value();
}



/*! ------------------------------------------------------------------------
  Called from logic to get output folder choice
  \returns      The string from the papersize's output folder
*/
QString PaperSize::getOutputFolder()
{
    // Typing in the QLineEdit box updates displayText
    // value, as does clicking the button next to
    // QLineEdit box and choosing a folder
    return outputFolderText->displayText();
}
