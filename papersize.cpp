#include <papersize.h>

PaperSize::PaperSize(QString name, int width, int height, QString homeFolder, bool isKnownSize) {

    this->name = name;

    if (isKnownSize) {                                                                          // If is a known size (aka not the wildcard unknown papersize)
                                                                                                // we need to create the spinboxes
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

    // -------------------------------------

    QLabel *outputFolderLabel = new QLabel(tr("Output Folder"));
    outputFolderText = new QLineEdit(homeFolder + name + "/");
    outputFolderText->setStatusTip("Location " + name + " sized files will be copied to");
    QPushButton *outputFolderBtn = new QPushButton(tr("Choose location"), this);
    outputFolderBtn->setStatusTip("Choose the location " + name + " sized files will be copied to");

    connect(outputFolderBtn, &QPushButton::clicked, this, [this]{ handleFolderBtn(); });

    // -------------------------------------

    QGridLayout *container = new QGridLayout;
    container->setVerticalSpacing(6);
    container->setContentsMargins(10, 10, 10, 10);                                              // Left Top Right Bottom
    container->setRowMinimumHeight(1, 25);                                                      // Second column (numbered 1, after label row which is 0. This
                                                                                                // is so that unknown tab without spinboxes aligns properly.
    if (isKnownSize) {
                                                                                                // If is a known size (aka not the wildcard unknown papersize)
        container->setColumnMinimumWidth(0, 92);                                                // we need to tailor spinboxes a little further and then add
        container->setColumnMinimumWidth(1, 92);                                                // them to the container widget.
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

    container->setColumnMinimumWidth(5, 96);                                                    // Set "Choose folder" button minimum size.
    container->addWidget(outputFolderLabel, 0, 4);
    container->addWidget(outputFolderText, 1, 4);
    container->addWidget(outputFolderBtn, 1, 5);

    // -------------------------------------

    setLayout(container);
}


// -------------------------------------------------------------------------

                                                                                                // Called when user clicks the output folder btn and sets a
void PaperSize::handleFolderBtn() {                                                             // bespoke folder into which this papersize will be copied.

    QFileDialog dialog;                                                                         // Create new dialog which only allows the slection of
    dialog.setFileMode(QFileDialog::Directory);                                                 // folders & whose default folder is tuser's home directory.
    dialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last());
                                                                                                // If user clicked ok to confirm their choice
    if (dialog.exec()) {
                                                                                                // Set true so choosing a new source folder doesn't auto
        hasChosenBespokeFolder = true;                                                          // update this output folder any longer.

        QString choice = dialog.selectedFiles()[0];                                             // Get first clicked folder as "choice" value.

        if (!choice.endsWith("/")) {                                                            // Test to see if the OS appends or location choice results
                                                                                                // in a trailing forward slash.
            outputFolderText->setText(choice + "/");
                                                                                                // If it doesn't have a trailing forward slash, add one and
        } else {                                                                                // then set the QLineEdit output folder text accordingly.

            outputFolderText->setText(choice);                                                  // Otherwise simply set the value as QLineEdit output folder
        }                                                                                       // text accordingly.
    }
}


// -------------------------------------------------------------------------

                                                                                                // Called from Logic if hasChosenBespokeFolder returns false.
void PaperSize::setOutputFolder(QString derivedFromSourceFolder) {                              // This updates the output folder of this paper size such
                                                                                                // that it's a subfolder of the source folder the just chose.
    outputFolderText->setText(derivedFromSourceFolder + name + "/");
}


// -------------------------------------------------------------------------


bool PaperSize::getHasChosenBespokeFolder() {                                                   // Called from logic to get whether or not the user has chosen
                                                                                                // a bespoke output folder for this papersize.
    return hasChosenBespokeFolder;
}


// -------------------------------------------------------------------------


int PaperSize::getMinWidth() {                                                                  // Called from logic to get min width.

    return minWidth->value();
}


// -------------------------------------------------------------------------


int PaperSize::getMaxWidth() {                                                                  // Called from logic to get max width.

    return maxWidth->value();
}


// -------------------------------------------------------------------------


int PaperSize::getMinHeight() {                                                                 // Called from logic to get min height.

    return minHeight->value();
}


// -------------------------------------------------------------------------


int PaperSize::getMaxHeight() {                                                                 // Called from logic to get max height.

    return maxHeight->value();
}


// -------------------------------------------------------------------------


QString PaperSize::getOutputFolder() {                                                          // Called from logic to get output folder choice. Typing in the
                                                                                                // QLineEdit box updates displayText value, as does clicking the
    return outputFolderText->displayText();                                                     // button next to tQLineEdit box and choosing a folder that way.
}


