#include <QtWidgets>
#include <logwindow.h>


LogWindow::LogWindow()
{
    LogWindow::setReadOnly(true);
}


/*! ------------------------------------------------------------------------
  Outputs a string to the log window
  \param    value    The text to add to the log window
*/
void LogWindow::print(const QString& value)
{
    // Add to log window then scroll to bottom
    this->appendPlainText(value);
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}



/*! ------------------------------------------------------------------------
  Outputs an int to the log window
  \param    value   The int to add to the log window
*/
void LogWindow::print(const int value)
{
    // Convert int to QStrimg and add to log window then
    // scroll to the bottom
    this->appendPlainText(QString::number(value));
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}



/*! ------------------------------------------------------------------------
  Simply adds a blank line to log window
*/
void LogWindow::n()
{
    this->appendPlainText("");
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}
