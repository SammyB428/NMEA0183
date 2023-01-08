#if ! defined( NMEA_0183_HEADER )

#define NMEA_0183_HEADER

/*
Author: Samuel R. Blackburn
Internet: wfc@pobox.com

"You can get credit for something or get it done, but not both."
Dr. Richard Garwin

The MIT License (MIT)

Copyright (c) 1996-2019 Sam Blackburn

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

/* SPDX-License-Identifier: MIT */

/*
** Now include the math stuff for some calculations in the COORDINATE class
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <charconv>
#include <math.h>
#include <time.h>
#include <inttypes.h>

#define STRING_VIEW(_x)  std::string_view(  _x, std::size(_x) - 1)

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

enum class NMEA0183_BOOLEAN
{
   NMEA_Unknown = 0,
   True,
   False
};

enum class LEFTRIGHT
{
   LR_Unknown = 0,
   Left,
   Right
};

enum class EASTWEST
{
   EW_Unknown = 0,
   East,
   West
};

enum class NORTHSOUTH
{
   NS_Unknown = 0,
   North,
   South
};

enum class REFERENCE
{
   ReferenceUnknown = 0,
   BottomTrackingLog,
   ManuallyEntered,
   WaterReferenced,
   RadarTrackingOfFixedTarget,
   PositioningSystemGroundReference
};

enum class COMMUNICATIONS_MODE
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
};

enum class TRANSDUCER_TYPE
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
};

enum class FAA_MODE
{
    ModeUnknown = 0,
    Autonomous = 'A',
    Differential = 'D',
    Estimated = 'E',
    NotValid = 'N',
    Simulated = 'S',
    Manual = 'M'
};

/*
** Misc Function Prototypes
*/

inline uint32_t HexValue(std::string_view hex_string) noexcept
{
    uint32_t return_value{ 0 };

    std::ignore = std::from_chars(&hex_string[0], &hex_string[0] + hex_string.length(), return_value, 16);

    return(return_value);
}

std::string expand_talker_id( std::string_view talker ) noexcept;
std::string Hex( uint32_t const value ) noexcept;
std::string talker_id( std::string_view sentence ) noexcept;
time_t ctime( int const year, int const month, int const day, int const hour, int const minute, int const second) noexcept;

#include "nmea0183.hpp"

#endif // NMEA0183_HEADER
