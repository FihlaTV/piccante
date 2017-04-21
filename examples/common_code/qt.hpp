/*

PICCANTE
The hottest HDR imaging library!
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
  Check if QT is not disabled, and includes the necessary headers.
  Works with QT version 4 or version 5
  */

#ifndef PIC_QT_HPP
#define PIC_QT_HPP

#ifndef PIC_DISABLE_QT


#include <QtCore/QtGlobal>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))

/* not ready for future versions */

#elif (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
/* we got Qt 5 */
#define PIC_QT

#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qfile.h>
#include <QtCore/qtimer.h>
#include <QtCore/qvariant.h>

#include <QtCore/qdir.h>
#include <QtCore/QTextStream>

#include <QtGui/QColor>
#include <QtGui/QImage>

#elif (QT_VERSION >= QT_VERSION_CHECK(4, 0, 0))
/* we got Qt 4 */
#define PIC_QT

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTimer>
#include <QVariant.h>
#include <QColor>
#include <QDir.h>
#include <QTextStream>
#include <QTime>
#include <QImage>
#include <QDebug>

#else /* unsupported qt version */

/* we got Qt 3 or below, unsupported */

#endif /* qt version selection */

#ifndef PIC_DISABLE_OPENGL
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#endif

#endif /* PIC_DISABLE_QT */

#endif /* PIC_QT_HPP */

