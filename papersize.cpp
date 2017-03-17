#include <papersize.h>

PaperSize::PaperSize(QString name, int width, int height, QString homeFolder) {

    this->name = name;

    outputFolder = homeFolder + name + "/";                                                     // set the default output folder

    minWidthLabel = new QLabel(tr("Min Width"));
    minWidth = new QSpinBox();
    minWidth->setStatusTip("Set the minimum " + name + " width");
    minWidth->setRange(width - 40, width);
    minWidth->setSuffix("mm");
    minWidth->setSingleStep(5);
    minWidth->setValue(width - 20);

    // -------------------------------------

    maxWidthLabel = new QLabel(tr("Max Width"));
    maxWidth = new QSpinBox();
    maxWidth->setStatusTip("Set the maximum " + name + " width");
    maxWidth->setRange(width, width + 40);
    maxWidth->setSuffix("mm");
    maxWidth->setSingleStep(5);
    maxWidth->setValue(width + 20);

    // -------------------------------------

    minHeightLabel = new QLabel(tr("Min Height"));
    minHeight = new QSpinBox();
    minHeight->setStatusTip("Set the minimum " + name + " height");
    minHeight->setRange(height - 40, height);
    minHeight->setSuffix("mm");
    minHeight->setSingleStep(5);
    minHeight->setValue(height - 20);

    // -------------------------------------

    maxHeightLabel = new QLabel(tr("Max Height"));
    maxHeight = new QSpinBox();
    maxHeight->setStatusTip("Set the maximum " + name + " height");
    maxHeight->setRange(height, height + 40);
    maxHeight->setSuffix("mm");
    maxHeight->setSingleStep(5);
    maxHeight->setValue(height + 20);

    // -------------------------------------

    outputFolderLabel = new QLabel(tr("Output Folder"));
    outputFolderText = new QLineEdit(outputFolder);
    outputFolderText->setStatusTip("Location " + name + " sized files will be copied to (read only)");
    outputFolderText->setReadOnly(true);
    outputFolderBtn = new QPushButton(tr("..."), this);
    outputFolderBtn->setStatusTip("Choose the location " + name + " sized files will be copied to");

    connect(outputFolderBtn, &QPushButton::clicked, this, [this]{ handleFolderBtn(); });

    // -------------------------------------

    container = new QGridLayout;
    container->setVerticalSpacing(6);
    container->setContentsMargins(10, 10, 10, 10);                                              // Left Top Right Bottom

    container->setColumnMinimumWidth(0,92);
    container->setColumnMinimumWidth(1,92);
    container->setColumnMinimumWidth(2,92);
    container->setColumnMinimumWidth(3,92);

    container->addWidget(minWidthLabel, 0, 0);
    container->addWidget(minWidth, 1, 0);
    container->addWidget(maxWidthLabel, 0, 1);
    container->addWidget(maxWidth, 1, 1);
    container->addWidget(minHeightLabel, 0, 2);
    container->addWidget(minHeight, 1, 2);
    container->addWidget(maxHeightLabel, 0, 3);
    container->addWidget(maxHeight, 1, 3);
    container->addWidget(outputFolderLabel, 0, 4);
    container->addWidget(outputFolderText, 1, 4);
    container->addWidget(outputFolderBtn, 1, 5);

    // -------------------------------------

    setLayout(container);
}


// -------------------------------------------------------------------------

                                                                                                // Called when a user clicks the output folder btn and sets a
void PaperSize::handleFolderBtn() {                                                             // bespoke folder into which this papersize will be copied.

    QFileDialog dialog;                                                                         // Create new dialog template which allows the slection of only
    dialog.setOptions(QFileDialog::ShowDirsOnly);                                               // folders and whose default folder is the user's home directory.
    dialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last());

    if (dialog.exec()) {                                                                        // If user clicked ok to confirm their choice

        outputFolder = dialog.selectedFiles()[0];                                               // Get their first clicked folder as the location for output
        hasChosenBespokeFolder = true;                                                          // Set true so choosing a new source folder doesn't auto
        outputFolderText->setText(outputFolder);                                                // change this value anymore and set the cosmetic folder text.
    }
}


// -------------------------------------------------------------------------


void PaperSize::setOutputFolder(QString derivedFromSourceFolder) {                              // Called from Logic only if hasChosenBespokeFolder returns false
                                                                                                // and updates the output folder such that it's a subfolder of
    outputFolderText->setText(derivedFromSourceFolder + name + "/");                            // the source folder the user just chose.
    outputFolder = derivedFromSourceFolder + name + "/";                                        // Sets cosmetic (because read only) QLineEdit value.
}                                                                                               // Sets actual variable value we'll use to determine where to
                                                                                                // copy the size to.

// -------------------------------------------------------------------------


bool PaperSize::getHasChosenBespokeFolder() {                                                   // Called

    return hasChosenBespokeFolder;
}


// -------------------------------------------------------------------------


QString PaperSize::getName() {                                                                  // Called from logic to get name

    return name;
}


// -------------------------------------------------------------------------


int PaperSize::getMinWidth() {                                                                  // Called from logic to get min width

    return minWidth->value();
}


// -------------------------------------------------------------------------


int PaperSize::getMaxWidth() {                                                                  // Called from logic to get max width

    return maxWidth->value();
}


// -------------------------------------------------------------------------


int PaperSize::getMinHeight() {                                                                 // Called from logic to get min height

    return minHeight->value();
}


// -------------------------------------------------------------------------


int PaperSize::getMaxHeight() {                                                                 // Called from logic to get max height

    return maxHeight->value();
}


// -------------------------------------------------------------------------


QString PaperSize::getOutputFolder() {                                                          // Called from logic to get output folder choice

    return outputFolder;
}


