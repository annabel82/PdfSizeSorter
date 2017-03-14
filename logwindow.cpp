#include <QtWidgets>
#include <logwindow.h>

LogWindow::LogWindow()
{
    LogWindow::setReadOnly(true);
    LogWindow::appendPlainText("Output window successfully initialised...\n");
}

void LogWindow::print(const QString& text)
{
    this->appendPlainText(text); // Adds the message to the widget
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum()); // Scrolls to the bottom
    //m_logFile.write(text); // Logs to file
}

void LogWindow::print(const int value)
{
    this->appendPlainText(QString::number(value)); // Adds the message to the widget
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum()); // Scrolls to the bottom
    //m_logFile.write(text); // Logs to file
}
