# PdfSizeSorter
Organises PDF files into various folders based on the physical size of their first page. Utilises Qt 5.15 for the UI and Poppler pdf library for reading pdf files.

This program was requested by a friend and implemented chiefly as a learning exercise.



## Compiling

### MacOS

* Install brew and then run `brew install poppler` (This will install the poppler-qt files too).

* Use the included PdfSizeSorter.pro file for Qt Creator.

### Windows

* All Poppler libs for compiling are contained in the poppler\_for\_win folder and are linked to from the included .pro file below.

* Use the included PdfSizeSorter_windows.pro file for Qt Creator.



## Screenshots

![MainUI](https://github.com/annabel82/PdfSizeSorter/blob/master/images/PdfSizeSorter.png)

![MainUI](https://github.com/annabel82/PdfSizeSorter/blob/master/images/PdfSizeSorter_win.png)

