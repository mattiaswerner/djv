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

//! \file djvSgi.h

#ifndef DJV_SGI_H
#define DJV_SGI_H

#include <djvFileIo.h>
#include <djvImageIo.h>

//! \addtogroup plugins
//@{

//! \defgroup djvSgiPlugin djvSgiPlugin
//!
//! This plugin provides support for the Silicon Graphics image file format.
//!
//! File extensions: .sgi, .rgba, .rgb, .bw
//!
//! Supported features:
//!
//! - 8-bit, 16-bit, Luminance, Luminance Alpha, RGB, RGBA
//! - File compression
//!
//! References:
//!
//! - Paul Haeberli, "The SGI Image File Format, Version 1.00"

//@} // plugins

//! \addtogroup djvSgiPlugin
//@{

//------------------------------------------------------------------------------
//! \struct djvSgi
//!
//! This struct provides SGI utilities.
//------------------------------------------------------------------------------

struct djvSgi
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

    static bool readRle(
        const void * in,
        const void * end,
        void *       out,
        int          size,
        int          bytes,
        bool         endian);

    //! Save RLE data.

    static quint64 writeRle(
        const void * in,
        void *       out,
        int          size,
        int          bytes,
        bool         endian);

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
        Options();

        COMPRESSION compression;
    };
};

//------------------------------------------------------------------------------

DJV_STRING_OPERATOR(, djvSgi::COMPRESSION);

//@} // djvSgiPlugin

#endif // DJV_SGI_H

