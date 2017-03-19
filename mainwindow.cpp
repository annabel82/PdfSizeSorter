#include <mainwindow.h>

MainWindow::MainWindow()
{                                                                                               // Instantiate Logic class which in turn instantiates source,
    Logic *logic = new Logic;                                                                   // pageSize and logWindow.
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

    // -------------------------------------

    grid->addWidget(logic->getSourceFolder(), 0, 0);                                            // Add source folder
    grid->addWidget(tabWidget, 1, 0);
    grid->addWidget(logic->getActionBtns(), 2, 0);                                              // Add close / run buttons
    grid->addWidget(logic->getLogWindow(), 3, 0);                                               // Add logWindow

    // -------------------------------------

    setCentralWidget(window);                                                                   // Define the widget we intended to be primary, as primary
    window->setLayout(grid);
    statusBar()->show();
    setWindowTitle(tr("PDF Size Sorter"));
    resize(900, 500);
}


