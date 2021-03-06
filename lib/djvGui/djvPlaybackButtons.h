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

//! \file djvPlaybackButtons.h

#ifndef DJV_PLAYBACK_BUTTONS_H
#define DJV_PLAYBACK_BUTTONS_H

#include <djvPlaybackUtil.h>

#include <QWidget>

class djvGuiContext;

class QButtonGroup;

//------------------------------------------------------------------------------
//! \class djvPlaybackButtons
//!
//! This class provides playback buttons.
//------------------------------------------------------------------------------

class DJV_GUI_EXPORT djvPlaybackButtons : public QWidget
{
    Q_OBJECT
    Q_ENUMS(PLAYBACK)
    
    //! This property holds the current playback state.
    
    Q_PROPERTY(
        djvPlaybackUtil::PLAYBACK playback
        READ                      playback
        WRITE                     setPlayback
        NOTIFY                    playbackChanged)
    
public:

    //! Constructor.
    
    explicit djvPlaybackButtons(djvGuiContext *, QWidget * parent = 0);
    
    //! Get the current playback state.
    
    djvPlaybackUtil::PLAYBACK playback() const;

public Q_SLOTS:

    //! Set the current playback state.
    
    void setPlayback(djvPlaybackUtil::PLAYBACK);
    
Q_SIGNALS:

    //! This signal is emitted when the current playback state is changed.
    
    void playbackChanged(djvPlaybackUtil::PLAYBACK);

private Q_SLOTS:

    void buttonCallback(int);
    
private:
    
    djvGuiContext *           _context;
    djvPlaybackUtil::PLAYBACK _playback;
    QButtonGroup *            _buttonGroup;
};

#endif // DJV_PLAYBACK_BUTTONS_H
