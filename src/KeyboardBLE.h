/*
    KeyboardBLE.h

    Modified by Earle F. Philhower, III <earlephilhower@yahoo.com>
    Main Arduino Library Copyright (c) 2015, Arduino LLC
    Original code (pre-library): Copyright (c) 2011, Peter Barrett

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef KEYBOARDBLE_h
#define KEYBOARDBLE_h

#include <HID_Keyboard.h>

#define VOLUME_UP 0xE9
#define VOLUME_DOWN 0xEA
#define VOLUME_MUTE 0xE2
#define MEDIA_PLAY_PAUSE 0xCD
#define MEDIA_STOP 0xB7
#define MEDIA_NEXT 0xB5
#define MEDIA_PREV 0xB6

class KeyboardBLE_ : public HID_Keyboard {
private:
    virtual void sendReport(KeyReport* keys) override;
    virtual void sendConsumerReport(uint16_t key) override;
public:
    KeyboardBLE_(void);
    void begin(const char *localName = nullptr, const char *hidName = nullptr, const uint8_t *layout = KeyboardLayout_en_US);
    void end(void);
    void setBattery(int lvl);
    void pressm(uint8_t mediaKey);
    void releasem();
};
extern KeyboardBLE_ KeyboardBLE;

#endif
