#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("PdfSizeSorter.ico"));
    MainWindow window;
    //app.setWindowIcon(QIcon("PdfSizeSorter.icns"));
    window.show();
    return app.exec();
}


     /*
    QPalette pal = palette();

    pal.setColor(QPalette::Background, Qt::lightGray);
    tabWidget->setAutoFillBackground(true);
    tabWidget->setPalette(pal);




    connect(paperMinWidth, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));




    filename = "/users/anna/GroupBox/1.pdf";

    Poppler::Document *doc;

    doc = Poppler::Document::load(filename);
    Poppler::Page *page = doc->page(0);

    QSize pageSize = page->pageSize();
    int pageWidth = pageSize.width() * 0.3528;
    int pageHeight = pageSize.height() * 0.3528;

    QString mmWidth = QString::number(pageWidth);
    QString mmHeight = QString::number(pageHeight);

    qInfo() << mmWidth + "mm x " + mmHeight + "mm";
    */


