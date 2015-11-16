#if ! defined( NMEA_0183_HEADER )

#define NMEA_0183_HEADER

/*
Author: Samuel R. Blackburn
Internet: wfc@pobox.com

"You can get credit for something or get it done, but not both."
Dr. Richard Garwin

The MIT License (MIT)

Copyright (c) 1996-2015 Sam Blackburn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
** Now include the math stuff for some calculations in the COORDINATE class
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>

/*
** Turn off the warning about precompiled headers, it is rather annoying
*/

#pragma warning( disable : 4699 )

#if ! defined( CARRIAGE_RETURN )
#define CARRIAGE_RETURN (0x0D)
#endif

#if ! defined( LINE_FEED )
#define LINE_FEED       (0x0A)
#endif

typedef enum _NMEA0183_BOOLEAN
{
   NMEA_Unknown = 0,
   True,
   False
} NMEA0183_BOOLEAN;

typedef enum _leftright
{
   LR_Unknown = 0,
   Left,
   Right
} LEFTRIGHT;

typedef enum _eastwest
{
   EW_Unknown = 0,
   East,
   West
} EASTWEST;

typedef enum
{
   NS_Unknown = 0,
   North,
   South
} NORTHSOUTH;

typedef enum
{
   ReferenceUnknown = 0,
   BottomTrackingLog,
   ManuallyEntered,
   WaterReferenced,
   RadarTrackingOfFixedTarget,
   PositioningSystemGroundReference
} REFERENCE;

typedef enum
{
   CommunicationsModeUnknown         = 0,
   F3E_G3E_SimplexTelephone          = 'd',
   F3E_G3E_DuplexTelephone           = 'e',
   J3E_Telephone                     = 'm',
   H3E_Telephone                     = 'o',
   F1B_J2B_FEC_NBDP_TelexTeleprinter = 'q',
   F1B_J2B_ARQ_NBDP_TelexTeleprinter = 's',
   F1B_J2B_ReceiveOnlyTeleprinterDSC = 'w',
   A1A_MorseTapeRecorder             = 'x',
   A1A_MorseKeyHeadset               = '{',
   F1C_F2C_F3C_FaxMachine            = '|'
} COMMUNICATIONS_MODE;

typedef enum
{
   TransducerUnknown   = 0,
   AngularDisplacementTransducer = 'A',
   TemperatureTransducer         = 'C',
   LinearDisplacementTransducer  = 'D',
   FrequencyTransducer           = 'F',
   HumidityTransducer            = 'H',
   ForceTransducer               = 'N',
   PressureTransducer            = 'P',
   FlowRateTransducer            = 'R',
   TachometerTransducer          = 'T',
   VolumeTransducer              = 'V'
} TRANSDUCER_TYPE;

/*
** Misc Function Prototypes
*/

uint32_t HexValue( const char *hex_string );
inline uint32_t HexValue(const std::string& hex_string)
{
    return(HexValue(hex_string.c_str()));
}

std::string expand_talker_id( const std::string & );
std::string Hex( const uint32_t value );
std::string talker_id( const std::string& sentence );
time_t ctime( const int year, const int month, const int day, const int hour, const int minute, const int second);

#include "nmea0183.hpp"

#endif // NMEA0183_HEADER
