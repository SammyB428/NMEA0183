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

// SPDX-License-Identifier: MIT

#include "nmea0183.h"
#pragma hdrstop

void ZDA::Empty( void ) noexcept
{
   UTCTime.clear();
   Time                  = 0;
   Day                   = 0;
   Month                 = 0;
   Year                  = 0;
   LocalHourDeviation    = 0;
   LocalMinutesDeviation = 0;
}

bool ZDA::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** ZDA - Time & Date
   ** UTC, day, month, year and local time zone
   **
   ** $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh<CR><LF>
   **        |         |  |  |    |  |
   **        |         |  |  |    |  +- Local zone minutes description, same sign as local hours
   **        |         |  |  |    +- Local zone description, 00 to +- 13 hours
   **        |         |  |  +- Year
   **        |         |  +- Month, 01 to 12
   **        |         +- Day, 01 to 31
   **        +- Universal Time Coordinated (UTC)
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   UTCTime = sentence.Field( 1 );

   int hours{ 0 };
   std::ignore = std::from_chars(UTCTime.data(), UTCTime.data() + 2, hours, 10);

   int minutes{ 0 };
   std::ignore = std::from_chars(UTCTime.data() + 2, UTCTime.data() + 4, minutes, 10);

   int seconds{ 0 };
   std::ignore = std::from_chars(UTCTime.data() + 4, UTCTime.data() + 6, seconds, 10);

   Day                   = sentence.Integer( 2 );
   Month                 = sentence.Integer( 3 );
   Year                  = sentence.Integer( 4 );
   LocalHourDeviation    = sentence.Integer( 5 );
   LocalMinutesDeviation = sentence.Integer( 6 );

   Time = ctime( Year, Month, Day, hours, minutes, seconds );

   return( true );
}

bool ZDA::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Day;
   sentence += Month;
   sentence += Year;
   sentence += LocalHourDeviation;
   sentence += LocalMinutesDeviation;

   sentence.Finish();

   return( true );
}

ZDA const& ZDA::operator = ( ZDA const& source ) noexcept
{
   UTCTime               = source.UTCTime;
   Time                  = source.Time;
   Day                   = source.Day;
   Month                 = source.Month;
   Year                  = source.Year;
   LocalHourDeviation    = source.LocalHourDeviation;
   LocalMinutesDeviation = source.LocalMinutesDeviation;

   return( *this );
}
