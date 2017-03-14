#include <sourcefolder.h>

SourceFolder::SourceFolder(bool readOnly) {

    sourceFolderLabel = new QLabel(tr("Source Folder Location"));

    homeFolder = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),
                                        QStandardPaths::LocateDirectory);

    sourceFolderLine = new QLineEdit(homeFolder);
    sourceFolderLine->setStatusTip("Source files location");
    sourceFolderLine->setReadOnly(readOnly);

    sourceFolderBtn = new QPushButton(tr("..."), this);
    sourceFolderBtn->setStatusTip("");

    sourceContainer = new QGridLayout;
    sourceContainer->setContentsMargins(10, 10, 10, 10);                                        // Left Top Right Bottom
    sourceContainer->setVerticalSpacing(12);
    sourceContainer->addWidget(sourceFolderLabel, 0, 1);
    sourceContainer->addWidget(sourceFolderLine, 1, 1);
    sourceContainer->addWidget(sourceFolderBtn, 1, 2);

    setLayout(sourceContainer);
}


// -------------------------------------------------------------------------


void SourceFolder::setSourceFolderText(QString sourceFolderText) {                              // Allows logic to update the cosmetic source line edit

    sourceFolderLine->setText(sourceFolderText);
}


