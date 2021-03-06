/*
  Q Light Controller Plus
  nanodmx.h

  Copyright (C) Massimo Callegari

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef NANODMX_H
#define NANODMX_H

#include <QFile>

#include "dmxusbwidget.h"

class QLCFTDI;

class NanoDMX : public DMXUSBWidget
{
    /************************************************************************
     * Initialization
     ************************************************************************/
public:
    NanoDMX(const QString& serial, const QString& name, const QString& vendor,
                    void *usb_ref);
    virtual ~NanoDMX();

    /** @reimp */
    DMXUSBWidget::Type type() const;

    /************************************************************************
     * Widget functions
     ************************************************************************/
public:
    /** @reimp */
    bool open();

    /** @reimp */
    bool close();

    /** @reimp */
    QString uniqueName() const;

    /** @reimp */
    QString additionalInfo() const;

    /** @reimp */
    bool writeUniverse(const QByteArray& universe);

private:
    bool checkReply();
    bool sendChannelValue(int channel, uchar value);
    QString getDeviceName();

private:
    /** File handle for /dev/ttyACMx */
    QFile m_file;

#ifdef LIBFTDI1
    libusb_device *m_device;
#else
    struct usb_device *m_device;
#endif

    QByteArray m_universe;
};

#endif
