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

//! \file djvFileBrowserTestWidget.h

#ifndef DJV_FILE_BROWSER_TEST_WIDGET_H
#define DJV_FILE_BROWSER_TEST_WIDGET_H

#include <djvUtil.h>

#include <QDir>
#include <QMainWindow>

struct djvFileBrowserTestWidgetPrivate;

class djvGuiContext;

//------------------------------------------------------------------------------
//! \class djvFileBrowserTestWidget
//!
//! This class provides the file browser widget.
//------------------------------------------------------------------------------

class djvFileBrowserTestWidget : public QMainWindow
{
    Q_OBJECT
    
    //! This property holds the current directory.
    
    Q_PROPERTY(
        QDir   dir
        READ   dir
        WRITE  setDir
        NOTIFY dirChanged)
    
    //! This property holds the current directory's path.
    
    Q_PROPERTY(
        QString path
        READ    path
        WRITE   setPath
        NOTIFY  pathChanged)
    
public:

    //! Constructor.
    
    explicit djvFileBrowserTestWidget(
        djvGuiContext * context,
        QWidget *       parent  = 0);
    
    //! Destructor.
    
    virtual ~djvFileBrowserTestWidget();
    
    //! Get the current directory.
    
    const QDir & dir() const;
    
    //! Get the current directory's path.
    
    QString path() const;

public Q_SLOTS:

    //! Set the current directory.

    void setDir(const QDir &);
    
    //! Set the current directory's path.
    
    void setPath(const QString &);

Q_SIGNALS:

    //! This signal is emitted when the current directory is changed.
    
    void dirChanged(const QDir &);

    //! This signal is emitted when the current directory's path is changed.
    
    void pathChanged(const QString &);
    
private Q_SLOTS:

    void sequenceCallback(QAction *);
    void viewModeCallback(QAction *);
    
private:

    DJV_PRIVATE_COPY(djvFileBrowserTestWidget)
    
    djvFileBrowserTestWidgetPrivate * _p;
};

#endif // DJV_FILE_BROWSER_TEST_WIDGET_H

