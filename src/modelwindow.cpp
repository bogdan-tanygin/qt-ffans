/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "modelwindow.h"
#include "glwidget.h"
#include "controlwidget.h"

#include <QApplication>
#include <QtWidgets>
#include <QMenuBar>
#include <QGroupBox>
#include <QGridLayout>

ModelWindow::ModelWindow()
{
    // Control part
    // ------------
    controlWidget = new ControlWidget(0);
    //QStyle *arthurStyle = new ArthurStyle();
    //controlWidget->setStyle(arthurStyle);

    QList<QWidget *> widgets = controlWidget->findChildren<QWidget *>();
    foreach (QWidget *w, widgets) {
        //w->setStyle(arthurStyle);
        w->setAttribute(Qt::WA_AcceptTouchEvents);
    }

    // GL part
    // -------
    glWidget = new GLWidget;

    //xSlider = createSlider();
    //ySlider = createSlider();
    //zoomSlider = createSlider();

    //xSlider->setValue(15 * 16);
    //ySlider->setValue(345 * 16);
    //zoomSlider->setValue(0 * 16);

    /*connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
    connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
    connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));*/

    //connect(zoomSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZoom(int)));
    //connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

    // Main window
    // -----------
    setWindowTitle(tr("Hello GL"));

    QGroupBox * groupBoxMain = new QGroupBox(this);
    setCentralWidget(groupBoxMain);

    QGroupBox * groupBoxGL = new QGroupBox(groupBoxMain);
    groupBoxGL->setTitle(tr("Model View"));

    QGroupBox * groupBoxProjection = new QGroupBox(groupBoxGL);
    groupBoxProjection->setTitle(tr("Projection"));
    orthographicProjection = new QRadioButton(groupBoxProjection);
    perspectiveProjection = new QRadioButton(groupBoxProjection);
    orthographicProjection->setText(tr("Orthographic"));
    perspectiveProjection->setText(tr("Perspective"));
    orthographicProjection->setChecked(true);
    QVBoxLayout *layoutProjection = new QVBoxLayout(groupBoxProjection);
    layoutProjection->addWidget(orthographicProjection);
    layoutProjection->addWidget(perspectiveProjection);
    connect(orthographicProjection, SIGNAL(clicked()), glWidget, SLOT(setOrthographicProjection()));
    connect(perspectiveProjection, SIGNAL(clicked()), glWidget, SLOT(setPerspectiveProjection()));

    QVBoxLayout *layoutGL = new QVBoxLayout(groupBoxGL);
    layoutGL->addWidget(glWidget);
    layoutGL->addWidget(groupBoxProjection);

    //layoutGL->setStretchFactor(groupBoxMain,1);

    /*QGroupBox *zoomBox = new QGroupBox(groupBoxGL);
    zoomBox->setTitle(tr("Zoom"));
    zoomValueEdit = new QLineEdit();*/

    //connect(textType, SIGNAL(toggled(bool)), textEditor, SLOT(setEnabled(bool)));
    //connect(textEditor, SIGNAL(textChanged(QString)), view, SLOT(setText(QString)));

    QHBoxLayout *mainLayout = new QHBoxLayout(groupBoxMain);
    //mainLayout->addWidget(glWidget);
    mainLayout->addWidget(controlWidget);
    mainLayout->addSpacing(1);
    mainLayout->addWidget(groupBoxGL);
    /*mainLayout->addWidget(xSlider);
    mainLayout->addWidget(ySlider);*/
    groupBoxMain->setLayout(mainLayout);

    // Menu bar
    // --------

    // File menu
    QMenu *fileMenu = new QMenu("File");
    menuBar()->addMenu(fileMenu);

    QAction *newFile = new QAction("New...", fileMenu);
    fileMenu->addAction(newFile);
    connect(newFile, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    QAction *openFile = new QAction("Open...", fileMenu);
    fileMenu->addAction(openFile);
    connect(openFile, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    QAction *saveFile = new QAction("Save", fileMenu);
    fileMenu->addAction(saveFile);
    connect(saveFile, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    QAction *saveFileAs = new QAction("Save As...", fileMenu);
    fileMenu->addAction(saveFileAs);
    connect(saveFileAs, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    // Help menu
    QMenu *helpMenu = new QMenu("Help");
    menuBar()->addMenu(helpMenu);

    QAction *aboutQt = new QAction("About...", helpMenu);
    helpMenu->addAction(aboutQt);
    connect(aboutQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

QSlider *ModelWindow::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}
//! [2]

void ModelWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void ModelWindow::closeEvent(QCloseEvent * e)
{
    //This function does nothing if QT_NO_DEBUG_OUTPUT was defined during compilation.
    qDebug() << "Close event" << __FUNCTION__;
}
