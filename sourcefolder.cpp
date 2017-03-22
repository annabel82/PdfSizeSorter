#include <sourcefolder.h>

SourceFolder::SourceFolder(bool readOnly, QString homeFolder) {

    QLabel *sourceFolderLabel = new QLabel(tr("Source Folder Location"));

    sourceFolderText = new QLineEdit(homeFolder);
    sourceFolderText->setStatusTip("Source files location");
    sourceFolderText->setReadOnly(readOnly);

    sourceFolderBtn = new QPushButton(tr("Choose location"), this);
    sourceFolderBtn->setStatusTip("Choose the location of source files");

    QGridLayout *sourceContainer = new QGridLayout;
    sourceContainer->setVerticalSpacing(12 );
    sourceContainer->setContentsMargins(10, 10, 12, 10);                                        // Left Top Right Bottom
    sourceContainer->setRowMinimumHeight(1, 25);                                                // Second column (numbered 1, after label row which is 0. This is
                                                                                                // so that unknown tab without spinboxes aligns properly.
    sourceContainer->setColumnMinimumWidth(2, 96);                                              // Choose folder button minimum size.
    sourceContainer->addWidget(sourceFolderLabel, 0, 1);
    sourceContainer->addWidget(sourceFolderText, 1, 1);
    sourceContainer->addWidget(sourceFolderBtn, 1, 2);

    setLayout(sourceContainer);
}


// -------------------------------------------------------------------------


void SourceFolder::setSourceFolderText(QString sourceFolderText) {                              // Allows logic to update the source line edit, the value of
                                                                                                // which is read when
    this->sourceFolderText->setText(sourceFolderText);
}


