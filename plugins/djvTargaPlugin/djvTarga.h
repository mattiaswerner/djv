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

//! \file djvTarga.h

#ifndef DJV_TARGA_H
#define DJV_TARGA_H

#include <djvFileIo.h>
#include <djvImageIo.h>

//! \addtogroup plugins
//@{

//! \defgroup djvTargaPlugin djvTargaPlugin
//!
//! This plugin provides support for the Targa image file format.
//!
//! File extensions: .tga
//!
//! Supported features:
//!
//! - 8-bit Luminance, Luminance Alpha, RGB, RGBA
//! - File compression
//!
//! References:
//!
//! - James D. Murray, William vanRyper, "Encyclopedia of Graphics File Formats,
//!   Second Edition"

//@} // plugins

//! \addtogroup djvTargaPlugin
//@{

//------------------------------------------------------------------------------
//! \struct djvTarga
//!
//! This struct provides Targa utilities.
//------------------------------------------------------------------------------

struct djvTarga
{
    //! Plugin name.
    
    static const QString staticName;

    //! This enumeration provides the file compression.

    enum COMPRESSION
    {
        COMPRESSION_NONE,
        COMPRESSION_RLE,

        COMPRESSION_COUNT
    };

    //! Get compression labels.

    static const QStringList & compressionLabels();

    //! Load information.

    static void loadInfo(
        djvFileIo &      io,
        djvImageIoInfo & info,
        bool *           compression) throw (djvError);

    //! Save information.

    static void saveInfo(
        djvFileIo &            io,
        const djvImageIoInfo & info,
        bool                   compression) throw (djvError);

    //! Load RLE data.

    static const quint8 * readRle(
        const quint8 * in,
        const quint8 * end,
        quint8 *       out,
        int            size,
        int            channels);

    //! Save RLE data.

    static quint64 writeRle(
        const quint8 * in,
        quint8 *       out,
        int            size,
        int            channels);

    //! This enumeration provides the options.

    enum OPTIONS
    {
        COMPRESSION_OPTION,

        OPTIONS_COUNT
    };

    //! Get option labels.

    static const QStringList & optionsLabels();

    //! This struct provides options.

    struct Options
    {
        //! Constructor.

        Options();

        COMPRESSION compression;
    };
};

//------------------------------------------------------------------------------

DJV_STRING_OPERATOR(, djvTarga::COMPRESSION);

//@} // djvTargaPlugin

#endif // DJV_TARGA_H

