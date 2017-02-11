SOURCES += \
    src/glwidget.cpp \
    src/main.cpp \
    src/modelwindow.cpp \
    src/modeldb.cpp \
    src/modelsimcore.cpp \
    src/settingswindow.cpp \
    src/settingsxml.cpp \
    src/modelparameterswindow.cpp \
    src/modelparameters.cpp \
    src/controlwidget.cpp \
    src/modelgraphics.cpp \
    src/modeldataanalysis.cpp \
    src/apptools.cpp
HEADERS += \
    src/glwidget.h \
    src/main.h \
    src/modelwindow.h \
    src/controlwidget.h \
    src/modeldb.h \
    src/modelsimcore.h \
    src/settingswindow.h \
    src/settingsxml.h \
    src/modelparameterswindow.h \
    src/modelparameters.h \
    src/modelgraphics.h \
    src/modeldataanalysis.h \
    src/apptools.h

qtHaveModule(opengl) {
	DEFINES += QT_OPENGL_SUPPORT
	QT += opengl
}
QT += widgets

#SHARED_FOLDER = ../shared

#include($$SHARED_FOLDER/shared.pri)

#RESOURCES += \
#    ffans.qrc

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/affine
#INSTALLS += target

#wince*: {
#    DEPLOYMENT_PLUGIN += qjpeg
#}
