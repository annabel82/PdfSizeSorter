#include <QtWidgets>
#include <logwindow.h>

LogWindow::LogWindow() {

    LogWindow::setReadOnly(true);
}


// -------------------------------------------------------------------------


void LogWindow::print(const QString& text) {

    this->appendPlainText(text);                                                                // Adds message to the log window.
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());                  // Scroll to the bottom.

    // m_logFile.write(text); // Logs to file
}


// -------------------------------------------------------------------------


void LogWindow::print(const int value) {

    this->appendPlainText(QString::number(value));                                              // Convert int to QStrimg and add to log window.
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());                  // Scroll to the bottom.

    // m_logFile.write(text); // Logs to file
}


// -------------------------------------------------------------------------


void LogWindow::n() {                                                                           // Simply adds a blank line to log window.

    this->appendPlainText("");
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}


