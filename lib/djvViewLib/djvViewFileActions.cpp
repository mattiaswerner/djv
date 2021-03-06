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

//! \file djvViewFileActions.cpp

#include <djvViewFileActions.h>

#include <djvViewContext.h>
#include <djvViewFilePrefs.h>
#include <djvViewShortcutPrefs.h>
#include <djvViewUtil.h>

#include <djvIconLibrary.h>
#include <djvOsxMenuHack.h>

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QDir>

//------------------------------------------------------------------------------
// djvViewFileActionsPrivate
//------------------------------------------------------------------------------

struct djvViewFileActionsPrivate
{
    djvViewFileActionsPrivate() :
        layer      (0),
        osxMenuHack(0)
    {}

    int              layer;
    QStringList      layers;
    djvOsxMenuHack * osxMenuHack;
};

//------------------------------------------------------------------------------
// djvViewFileActions
//------------------------------------------------------------------------------

djvViewFileActions::djvViewFileActions(
    djvViewContext * context,
    QObject *        parent) :
	djvViewAbstractActions(context, parent),
    _p(new djvViewFileActionsPrivate)
{
    // Create the actions.

    for (int i = 0; i < ACTION_COUNT; ++i)
    {
        _actions[i] = new QAction(this);
    }

    _actions[OPEN]->setText(qApp->translate("djvViewFileActions", "&Open"));
    _actions[OPEN]->setIcon(context->iconLibrary()->icon(
        "djvFileOpenIcon.png"));

    _actions[RELOAD]->setText(qApp->translate("djvViewFileActions", "Re&load"));
    _actions[RELOAD]->setIcon(context->iconLibrary()->icon(
        "djvFileReloadIcon.png"));

    _actions[RELOAD_FRAME]->setText(qApp->translate("djvViewFileActions", "Reload Frame"));

    _actions[CLOSE]->setText(qApp->translate("djvViewFileActions", "Clos&e"));
    _actions[CLOSE]->setIcon(context->iconLibrary()->icon(
        "djvFileCloseIcon.png"));

    _actions[SAVE]->setText(qApp->translate("djvViewFileActions", "&Save"));

    _actions[SAVE_FRAME]->setText(qApp->translate("djvViewFileActions", "Save &Frame"));

    _actions[LAYER_PREV]->setText(qApp->translate("djvViewFileActions", "Layer Previous"));

    _actions[LAYER_NEXT]->setText(qApp->translate("djvViewFileActions", "Layer Next"));

    _actions[U8_CONVERSION]->setText(qApp->translate("djvViewFileActions", "&8-bit Conversion"));
    _actions[U8_CONVERSION]->setCheckable(true);

    _actions[CACHE]->setText(qApp->translate("djvViewFileActions", "&Memory Cache"));
    _actions[CACHE]->setCheckable(true);

    _actions[PRELOAD]->setText(qApp->translate("djvViewFileActions", "Preloa&d Cache"));
    _actions[PRELOAD]->setCheckable(true);

    _actions[CLEAR_CACHE]->setText(qApp->translate("djvViewFileActions", "Clear Memory Cac&he"));

    _actions[MESSAGES]->setText(qApp->translate("djvViewFileActions", "Messa&ges"));
    
    _actions[PREFS]->setText(qApp->translate("djvViewFileActions", "&Preferences"));

    _actions[DEBUG_LOG]->setText(qApp->translate("djvViewFileActions", "Debugging Log"));

    _actions[EXIT]->setText(qApp->translate("djvViewFileActions", "E&xit"));

    // Create the action groups.

    for (int i = 0; i < GROUP_COUNT; ++i)
    {
        _groups[i] = new QActionGroup(this);
    }

    _groups[LAYER_GROUP]->setExclusive(true);

    _groups[PROXY_GROUP]->setExclusive(true);

    for (int i = 0; i < djvPixelDataInfo::proxyLabels().count(); ++i)
    {
        QAction * action = new QAction(this);
        action->setText(djvPixelDataInfo::proxyLabels()[i]);
        action->setCheckable(true);
        action->setData(i);

        _groups[PROXY_GROUP]->addAction(action);
    }

    // Initialize.

    update();

    // Setup the callbacks.

    connect(
        context->filePrefs(),
        SIGNAL(recentChanged(const djvFileInfoList &)),
        SLOT(update()));

    connect(
        context->shortcutPrefs(),
        SIGNAL(shortcutsChanged(const QVector<djvShortcut> &)),
        SLOT(update()));
}

djvViewFileActions::~djvViewFileActions()
{
    delete _p;
}

void djvViewFileActions::setLayers(const QStringList & layers)
{
    if (layers == _p->layers)
        return;

    _p->layers = layers;

    update();
}

void djvViewFileActions::setLayer(int layer)
{
    if (layer == _p->layer)
        return;

    _p->layer = layer;

    update();
}

void djvViewFileActions::update()
{
    const QVector<djvShortcut> & shortcuts =
        context()->shortcutPrefs()->shortcuts();

    // Update the actions.

    _actions[OPEN]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_FILE_OPEN].value);
    _actions[OPEN]->setToolTip(
        qApp->translate("djvViewFileActions", "Open a new file\n\nShortcut: %1").
        arg(shortcuts[djvViewUtil::SHORTCUT_FILE_OPEN].value.toString()));

    _actions[RELOAD]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_FILE_RELOAD].value);
    _actions[RELOAD]->setToolTip(
        qApp->translate("djvViewFileActions", "Reload the current file\n\nShortcut: %1").
        arg(shortcuts[djvViewUtil::SHORTCUT_FILE_RELOAD].value.toString()));

    _actions[RELOAD_FRAME]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_FILE_RELOAD_FRAME].value);
    _actions[RELOAD_FRAME]->setToolTip(
        qApp->translate("djvViewFileActions", "Reload the current frame\n\nShortcut: %1").
        arg(shortcuts[djvViewUtil::SHORTCUT_FILE_RELOAD_FRAME].value.toString()));

    _actions[CLOSE]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_FILE_CLOSE].value);
    _actions[CLOSE]->setToolTip(
        qApp->translate("djvViewFileActions", "Close the current file\n\nShortcut: %1").
        arg(shortcuts[djvViewUtil::SHORTCUT_FILE_CLOSE].value.toString()));

    _actions[SAVE]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_FILE_SAVE].value);

    _actions[SAVE_FRAME]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_FILE_SAVE_FRAME].value);

    _actions[LAYER_PREV]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_PREV].value);

    _actions[LAYER_NEXT]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_NEXT].value);

    _actions[EXIT]->setShortcut(
        shortcuts[djvViewUtil::SHORTCUT_EXIT].value);

    // Update the action groups.

    Q_FOREACH(QAction * action, _groups[RECENT_GROUP]->actions())
        delete action;

    const djvFileInfoList & recent = context()->filePrefs()->recentFiles();

    for (int i = 0; i < recent.count(); ++i)
    {
        QAction * action = new QAction(this);
        action->setText(QDir::toNativeSeparators(recent[i]));
        action->setData(i);

        _groups[RECENT_GROUP]->addAction(action);
    }

    Q_FOREACH(QAction * action, _groups[LAYER_GROUP]->actions())
        delete action;

    const QVector<QKeySequence> layerShortcuts = QVector<QKeySequence>() <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_DEFAULT].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_1].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_2].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_3].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_4].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_5].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_6].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_7].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_8].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_9].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_LAYER_10].value;

    for (int i = 0; i < _p->layers.count(); ++i)
    {
        QAction * action = new QAction(this);
        action->setText(_p->layers[i]);
        action->setCheckable(true);
        action->setChecked(i == _p->layer);
        action->setShortcut(
            i < layerShortcuts.count() ? layerShortcuts[i] : QKeySequence());
        action->setData(i);

        _groups[LAYER_GROUP]->addAction(action);
    }
    
    const QVector<QKeySequence> proxyShortcuts = QVector<QKeySequence>() <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_PROXY_NONE].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_PROXY_1_2].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_PROXY_1_4].value <<
        shortcuts[djvViewUtil::SHORTCUT_FILE_PROXY_1_8].value;

    for (int i = 0; i < _groups[PROXY_GROUP]->actions().count(); ++i)
    {
        _groups[PROXY_GROUP]->actions()[i]->setShortcut(proxyShortcuts[i]);
    }

    // Fix up the actions.
    
    osxMenuHack();

    // Emit changed signal.

    Q_EMIT changed();
}
