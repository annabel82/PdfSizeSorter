#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QPlainTextEdit>


class LogWindow : public QPlainTextEdit
{
    Q_OBJECT

public:
    LogWindow();
    void        print(const QString& text);
    void        print(const int);
    void        n();
};

#endif // LOGWINDOW_H


