//------------------------------------------------------------------------------
// Copyright (c) 2004-2015 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the names of the copyright holders nor the names of any
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

//! \file djvViewWindowPrefsWidget.cpp

#include <djvViewWindowPrefsWidget.h>

#include <djvViewContext.h>
#include <djvViewWindowPrefs.h>

#include <djvPrefsGroupBox.h>
#include <djvVector2iEditWidget.h>

#include <djvSignalBlocker.h>

#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QVBoxLayout>

//------------------------------------------------------------------------------
// djvViewWindowPrefsWidgetPrivate
//------------------------------------------------------------------------------

struct djvViewWindowPrefsWidgetPrivate
{
    djvViewWindowPrefsWidgetPrivate() :
        autoFitWidget           (0),
        viewMaxWidget           (0),
        viewMaxUserWidget       (0),
        fullScreenControlsWidget(0),
        toolBarButtonGroup      (0)
    {}
    
    QCheckBox *             autoFitWidget;
    QComboBox *             viewMaxWidget;
    djvVector2iEditWidget * viewMaxUserWidget;
    QCheckBox *             fullScreenControlsWidget;
    QButtonGroup *          toolBarButtonGroup;
};

//------------------------------------------------------------------------------
// djvViewWindowPrefsWidget
//------------------------------------------------------------------------------

djvViewWindowPrefsWidget::djvViewWindowPrefsWidget(djvViewContext * context) :
    djvViewAbstractPrefsWidget(
        qApp->translate("djvViewWindowPrefsWidget", "Windows"), context),
    _p(new djvViewWindowPrefsWidgetPrivate)
{
    // Create the size widgets.

    _p->autoFitWidget = new QCheckBox(
        qApp->translate(
            "djvViewWindowPrefsWidget",
            "Automatically fit the window to the image"));

    _p->viewMaxWidget = new QComboBox;
    _p->viewMaxWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _p->viewMaxWidget->addItems(djvViewUtil::viewMaxLabels());

    _p->viewMaxUserWidget = new djvVector2iEditWidget;
    _p->viewMaxUserWidget->setRange(djvVector2i(100, 100), djvVector2i(8192, 8192));
    _p->viewMaxUserWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    // Create the full screen widgets.

    _p->fullScreenControlsWidget = new QCheckBox(
        qApp->translate(
            "djvViewWindowPrefsWidget",
            "Set whether the controls are visible in full screen mode"));

    // Create the tool bar widgets.

    _p->toolBarButtonGroup = new QButtonGroup(this);
    _p->toolBarButtonGroup->setExclusive(false);
    
    for (int i = 0; i < djvViewUtil::toolBarLabels().count(); ++i)
    {
        QCheckBox * checkBox = new QCheckBox(djvViewUtil::toolBarLabels()[i]);
        
        _p->toolBarButtonGroup->addButton(checkBox, i);
    }

    // Layout the widgets.

    QVBoxLayout * layout = new QVBoxLayout(this);

    djvPrefsGroupBox * prefsGroupBox = new djvPrefsGroupBox(
        qApp->translate("djvViewWindowPrefsWidget", "Window Size"), context);
    QFormLayout * formLayout = prefsGroupBox->createLayout();
    formLayout->addRow(_p->autoFitWidget);
    formLayout->addRow(
        qApp->translate("djvViewWindowPrefsWidget", "Maximum view size:"),
        _p->viewMaxWidget);
    formLayout->addRow("", _p->viewMaxUserWidget);
    layout->addWidget(prefsGroupBox);

    prefsGroupBox = new djvPrefsGroupBox(
        qApp->translate("djvViewWindowPrefsWidget", "Full Screen"), context);
    formLayout = prefsGroupBox->createLayout();
    formLayout->addRow(_p->fullScreenControlsWidget);
    layout->addWidget(prefsGroupBox);

    prefsGroupBox = new djvPrefsGroupBox(
        qApp->translate("djvViewWindowPrefsWidget", "Tool Bars"),
        qApp->translate("djvViewWindowPrefsWidget", "Set which tool bars are visible."),
        context);
    formLayout = prefsGroupBox->createLayout();
    for (int i = 0; i < _p->toolBarButtonGroup->buttons().count(); ++i)
        formLayout->addRow(_p->toolBarButtonGroup->button(i));
    layout->addWidget(prefsGroupBox);

    layout->addStretch();

    // Initialize.
    
    widgetUpdate();

    // Setup the callbacks.

    connect(
        _p->autoFitWidget,
        SIGNAL(toggled(bool)),
        SLOT(autoFitCallback(bool)));
    
    connect(
        _p->viewMaxWidget,
        SIGNAL(activated(int)),
        SLOT(viewMaxCallback(int)));

    connect(
        _p->viewMaxUserWidget,
        SIGNAL(valueChanged(const djvVector2i &)),
        SLOT(viewMaxUserCallback(const djvVector2i &)));
    
    connect(
        _p->fullScreenControlsWidget,
        SIGNAL(toggled(bool)),
        SLOT(fullScreenControlsCallback(bool)));
    
    connect(
        _p->toolBarButtonGroup,
        SIGNAL(buttonClicked(int)),
        SLOT(toolBarCallback(int)));
}

djvViewWindowPrefsWidget::~djvViewWindowPrefsWidget()
{
    delete _p;
}

void djvViewWindowPrefsWidget::resetPreferences()
{
    context()->windowPrefs()->setAutoFit(
        djvViewWindowPrefs::autoFitDefault());
    context()->windowPrefs()->setViewMax(
        djvViewWindowPrefs::viewMaxDefault());
    context()->windowPrefs()->setViewMaxUser(
        djvViewWindowPrefs::viewMaxUserDefault());
    context()->windowPrefs()->setFullScreenControls(
        djvViewWindowPrefs::fullScreenControlsDefault());
    context()->windowPrefs()->setToolBar(
        djvViewWindowPrefs::toolBarDefault());
    
    widgetUpdate();
}

void djvViewWindowPrefsWidget::autoFitCallback(bool in)
{
    context()->windowPrefs()->setAutoFit(in);
}

void djvViewWindowPrefsWidget::viewMaxCallback(int in)
{
    context()->windowPrefs()->setViewMax(static_cast<djvViewUtil::VIEW_MAX>(in));
    
    widgetUpdate();
}

void djvViewWindowPrefsWidget::viewMaxUserCallback(const djvVector2i & in)
{
    context()->windowPrefs()->setViewMaxUser(in);
}

void djvViewWindowPrefsWidget::fullScreenControlsCallback(bool in)
{
    context()->windowPrefs()->setFullScreenControls(in);
}

void djvViewWindowPrefsWidget::toolBarCallback(int id)
{
    QVector<bool> visible = context()->windowPrefs()->toolBar();
    
    visible[id] = _p->toolBarButtonGroup->button(id)->isChecked();

    context()->windowPrefs()->setToolBar(visible);
}

void djvViewWindowPrefsWidget::widgetUpdate()
{
    djvSignalBlocker signalBlocker(QObjectList() <<
        _p->autoFitWidget <<
        _p->viewMaxWidget <<
        _p->viewMaxUserWidget <<
        _p->fullScreenControlsWidget <<
        _p->toolBarButtonGroup);

    _p->autoFitWidget->setChecked(
        context()->windowPrefs()->hasAutoFit());
    
    _p->viewMaxWidget->setCurrentIndex(
        context()->windowPrefs()->viewMax());
    
    _p->viewMaxUserWidget->setValue(
        context()->windowPrefs()->viewMaxUser());
    _p->viewMaxUserWidget->setVisible(
        djvViewUtil::VIEW_MAX_USER == context()->windowPrefs()->viewMax());
    
    _p->fullScreenControlsWidget->setChecked(
        context()->windowPrefs()->hasFullScreenControls());

    const QVector<bool> & visible = context()->windowPrefs()->toolBar();
    
    for (int i = 0; i < visible.count(); ++i)
    {
        _p->toolBarButtonGroup->button(i)->setChecked(visible[i]);
    }
}

