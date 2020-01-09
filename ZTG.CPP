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

void ZTG::Empty( void ) noexcept
{
   UTCTime.clear();
   Time = 0;
   TimeRemaining.clear();
   To.clear();
}

bool ZTG::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** ZTG - UTC & Time to Destination Waypoint
   **
   **        1         2         3    4
   **        |         |         |    |
   ** $--ZTG,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
   **
   ** Fields:
   **  1) Universal Time Coordinated (UTC)
   **  2) Time Remaining
   **  3) Destination Waypoint ID
   **  4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 4 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   UTCTime       = sentence.Field( 1 );
   Time          = sentence.Time( 1 );
   TimeRemaining = sentence.Field( 2 );
   To            = sentence.Field( 3 );

   return( true );
}

bool ZTG::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += TimeRemaining;
   sentence += To;

   sentence.Finish();

   return( true );
}

ZTG const& ZTG::operator = ( ZTG const& source ) noexcept
{
   UTCTime       = source.UTCTime;
   Time          = source.Time;
   TimeRemaining = source.TimeRemaining;
   To            = source.To;

   return( *this );
}
