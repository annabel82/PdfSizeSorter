QT += widgets

HEADERS       = \
    mainwindow.h \
    logwindow.h \
    papersize.h \
    sourcefolder.h \
    logic.h

SOURCES       = \
    main.cpp \
    mainwindow.cpp \
    logwindow.cpp \
    papersize.cpp \
    sourcefolder.cpp \
    logic.cpp

INCLUDEPATH += /usr/local/include/poppler/qt5
LIBS += -L/usr/local/lib/ -lpoppler-qt5

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/groupbox
INSTALLS += target
