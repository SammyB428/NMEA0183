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

void BEC::Empty( void ) noexcept
{
   UTCTime.clear();
   Time                  = 0;
   Position.Empty();
   BearingTrue           = 0.0;
   BearingMagnetic       = 0.0;
   DistanceNauticalMiles = 0.0;
   To.clear();
}

bool BEC::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** BEC - Bearing & Distance to Waypoint - Dead Reckoning
   **                                                         12
   **        1         2       3 4        5 6   7 8   9 10  11|    13
   **        |         |       | |        | |   | |   | |   | |    |
   ** $--BEC,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N,c--c*hh<CR><LF>
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 13 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   UTCTime               = sentence.Field( 1 );
   Time                  = sentence.Time( 1 );
   Position.Parse( 2, 3, 4, 5, sentence );
   BearingTrue           = sentence.Double( 6 );
   BearingMagnetic       = sentence.Double( 8 );
   DistanceNauticalMiles = sentence.Double( 10 );
   To                    = sentence.Field( 12 );

   return( true );
}

bool BEC::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Position;
   sentence += BearingTrue;
   sentence += STRING_VIEW("T");
   sentence += BearingMagnetic;
   sentence += STRING_VIEW("M");
   sentence += DistanceNauticalMiles;
   sentence += STRING_VIEW("N");
   sentence += To;

   sentence.Finish();

   return( true );
}

BEC const& BEC::operator = ( BEC const& source ) noexcept
{
   UTCTime               = source.UTCTime;
   Time                  = source.Time;
   Position              = source.Position;
   BearingTrue           = source.BearingTrue;
   BearingMagnetic       = source.BearingMagnetic;
   DistanceNauticalMiles = source.DistanceNauticalMiles;
   To                    = source.To;

   return( *this );
}
