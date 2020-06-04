#include <mainwindow.h>


/*! ------------------------------------------------------------------------
  Constructs the main window and the components therein, called
  by main
*/
MainWindow::MainWindow()
{
    // Instantiate Logic class which in turn instantiates
    // source folder, pageSize and logWindow.
    logic = new Logic;

    // Create widget we intend to be used as primary widget (frame).
    QWidget *window = new QWidget;
    QGridLayout *grid = new QGridLayout;

    // -------------------------------------

    QTabWidget *tabWidget = new QTabWidget;
    // Don't want this to resize with window
    tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    tabWidget->addTab(logic->getPaperSize(0), tr("  2A0  "));
    tabWidget->addTab(logic->getPaperSize(1), tr("  A0  "));
    tabWidget->addTab(logic->getPaperSize(2), tr("  A1  "));
    tabWidget->addTab(logic->getPaperSize(3), tr("  A2  "));
    tabWidget->addTab(logic->getPaperSize(4), tr("  A3  "));
    tabWidget->addTab(logic->getPaperSize(5), tr("  A4  "));
    tabWidget->addTab(logic->getPaperSize(6), tr("  A5  "));

    tabWidget->addTab(logic->getOtherPaperSize(), tr("  Other  "));

    // -------------------------------------

    closeRunButtons = new QDialogButtonBox();
    closeRunButtons->addButton(tr("Sort Files"), QDialogButtonBox::AcceptRole)->setStatusTip("Begin sorting pdf files into folders");
    closeRunButtons->addButton(tr("Close"), QDialogButtonBox::RejectRole)->setStatusTip("Close the application");


    // -------------------------------------

    connect(closeRunButtons, &QDialogButtonBox::accepted, this, [this] { logic->handleSortFilesBtn(); });
    connect(closeRunButtons, &QDialogButtonBox::rejected, this, [] { QApplication::quit(); });

    grid->addWidget(logic->getSourceFolder(), 0, 0);
    grid->addWidget(tabWidget, 1, 0);
    grid->addWidget(closeRunButtons, 2, 0);
    grid->addWidget(logic->getLogWindow(), 3, 0);

    // -------------------------------------

    // Define the widget we want to be primary
    setCentralWidget(window);
    window->setLayout(grid);
    statusBar()->show();
    setWindowTitle(tr("PDF Size Sorter"));
    resize(1000, 600);

    connect(logic->sourceFolder->sourceFolderBtn, &QPushButton::clicked, this, [this] { handleSourceFolderBtn(); });
}



/*! ------------------------------------------------------------------------
  Called when user presses the source folder button and
  creates the dialog popup and handles the users choice
*/
void MainWindow::handleSourceFolderBtn() {

    // Create new dialog template which restricts user to selecting
    // folders and whose default folder is the user's home directory.
    QFileDialog srcDialog;
    srcDialog.setFileMode(QFileDialog::Directory);
    srcDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last());

    // If user clicked ok to confirm their choice
    if (srcDialog.exec())
    {
        // Get first clicked folder as "choice" value.
        QString choice = srcDialog.selectedFiles()[0];

        // Test to see if the OS appends our location choice results
        // with a trailing forward slash.
        if (!choice.endsWith("/"))
        {
            // If it doesn't have a trailing forward slash add one.
            logic->setSourceFolderChoice(choice + "/");
        }
        else
        {
            // Otherwise simply set the value as QLineEdit output folder
            logic->setSourceFolderChoice(choice);
        }
    }
}
