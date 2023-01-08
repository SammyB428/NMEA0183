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

/*
** This Sentence Not Recommended For New Designs
** ZTG is recommended.
*/

#include "nmea0183.h"
#pragma hdrstop

void ZPI::Empty( void ) noexcept
{
   UTCTimeString.clear();
   UTCTime = 0;
   ArrivalTimeString.clear();
   ArrivalTime = 0;
   To.clear();
}

bool ZPI::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** ZPI - Arrival time at point of interest
   **
   **        1         2         3    4
   **        |         |         |    |  
   ** $--ZPI,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
   **
   ** 1) Universal Time Coordinated (UTC)
   ** 2) Arrival Time
   ** 3) Waypoint ID (To)
   ** 4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 4 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   }

   auto temp_time{ time(nullptr) };
   auto tm_p{ gmtime(&temp_time) };
   auto const year{ tm_p->tm_year + 1900 };
   auto const month{ tm_p->tm_mon };
   auto const day{ tm_p->tm_mday };

   UTCTimeString = sentence.Field( 1 );

   int hours{ 0 };
   std::ignore = std::from_chars(UTCTimeString.data(), UTCTimeString.data() + 2, hours, 10);

   int minutes{ 0 };
   std::ignore = std::from_chars(UTCTimeString.data() + 2, UTCTimeString.data() + 4, minutes, 10);

   int seconds{ 0 };
   std::ignore = std::from_chars(UTCTimeString.data() + 4, UTCTimeString.data() + 6, seconds, 10);

   UTCTime = ctime( year, month, day, hours, minutes, seconds );

   ArrivalTimeString = sentence.Field( 2 );

   std::ignore = std::from_chars(ArrivalTimeString.data(), ArrivalTimeString.data() + 2, hours, 10);
   std::ignore = std::from_chars(ArrivalTimeString.data() + 2, ArrivalTimeString.data() + 4, minutes, 10);
   std::ignore = std::from_chars(ArrivalTimeString.data() + 4, ArrivalTimeString.data() + 6, seconds, 10);

   ArrivalTime = ctime( year, month, day, hours, minutes, seconds );

   To = sentence.Field( 3 );

   return( true );
}

bool ZPI::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTimeString;
   sentence += ArrivalTimeString;
   sentence += To;

   sentence.Finish();

   return( true );
}

ZPI const& ZPI::operator = ( ZPI const& source ) noexcept
{
   UTCTimeString     = source.UTCTimeString;
   UTCTime           = source.UTCTime;
   ArrivalTimeString = source.ArrivalTimeString;
   ArrivalTime       = source.ArrivalTime;
   To                = source.To;

   return( *this );
}
