#include <mainwindow.h>

MainWindow::MainWindow()
{                                                                                               // Instantiate Logic class which in turn instantiates source,
    logic = new Logic;                                                                          // pageSize and logWindow.
    QWidget *window = new QWidget;                                                              // Create widget we intend to be used as primary widget (frame).
    QGridLayout *grid = new QGridLayout;

    // -------------------------------------

    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);                       // Don't want this to resize with window
    tabWidget->addTab(logic->getPaperSize(0), tr("2A0"));
    tabWidget->addTab(logic->getPaperSize(1), tr("A0"));
    tabWidget->addTab(logic->getPaperSize(2), tr("A1"));
    tabWidget->addTab(logic->getPaperSize(3), tr("A2"));
    tabWidget->addTab(logic->getPaperSize(4), tr("A3"));
    tabWidget->addTab(logic->getPaperSize(5), tr("A4"));
    tabWidget->addTab(logic->getPaperSize(6), tr("A5"));

    tabWidget->addTab(logic->getOtherPaperSize(), tr("Other"));

    // -------------------------------------

    actionBtns = new QDialogButtonBox();
    actionBtns->addButton(tr("Sort Files"), QDialogButtonBox::AcceptRole);
    actionBtns->addButton(tr("Close"),QDialogButtonBox::RejectRole);

    // --------------------------------------------

    connect(actionBtns, &QDialogButtonBox::accepted, this, [this] { logic->handleSortFilesBtn(); });
    connect(actionBtns, &QDialogButtonBox::rejected, this, [this] { QApplication::quit(); });

    grid->addWidget(logic->getSourceFolder(), 0, 0);                                            // Add source folder
    grid->addWidget(tabWidget, 1, 0);
    grid->addWidget(actionBtns, 2, 0);                                                          // Add close / run buttons
    grid->addWidget(logic->getLogWindow(), 3, 0);                                               // Add logWindow

    // -------------------------------------

    setCentralWidget(window);                                                                   // Define the widget we intended to be primary, as primary
    window->setLayout(grid);
    statusBar()->show();
    setWindowTitle(tr("PDF Size Sorter"));
    resize(900, 500);

    connect(logic->sourceFolder->sourceFolderBtn, &QPushButton::clicked, this, [this] { handleSourceFolderBtn(); });
}


// -------------------------------------------------------------------------


void MainWindow::handleSourceFolderBtn() {                                                      // Called when user presses the source folder button

    QFileDialog srcDialog;                                                                      // Create new dialog template which restricts user to selecting
    srcDialog.setFileMode(QFileDialog::Directory);                                              // folders and whose default folder is the user's home directory.
    srcDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last());

    if (srcDialog.exec()) {                                                                     // If user clicked ok to confirm their choice

        QString choice = srcDialog.selectedFiles()[0];                                          // Get first clicked folder as "choice" value.

        if (!choice.endsWith("/")) {                                                            // Test to see if the OS appends or location choice results
                                                                                                // in a trailing forward slash.
            logic->setSourceFolderChoice(choice + "/");
                                                                                                // If it doesn't have a trailing forward slash add one.
        } else {

            logic->setSourceFolderChoice(choice);                                               // Otherwise simply set the value as QLineEdit output folder
        }
    }
}
