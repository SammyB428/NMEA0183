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

void BWW::Empty( void ) noexcept
{
   BearingTrue     = 0.0;
   BearingMagnetic = 0.0;
   To.clear();
   From.clear();
}

bool BWW::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** BWW - Bearing - Waypoint to Waypoint
   **
   **        1   2 3   4 5    6    7
   **        |   | |   | |    |    |
   ** $--BWW,x.x,T,x.x,M,c--c,c--c*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Bearing Degrees, TRUE
   **  2) T = True
   **  3) Bearing Degrees, Magnetic
   **  4) M = Magnetic
   **  5) TO Waypoint
   **  6) FROM Waypoint
   **  7) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   BearingTrue     = sentence.Double( 1 );
   BearingMagnetic = sentence.Double( 3 );
   To              = sentence.Field( 5 );
   From            = sentence.Field( 6 );

   return( true );
}

bool BWW::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += BearingTrue;
   sentence += STRING_VIEW("T");
   sentence += BearingMagnetic;
   sentence += STRING_VIEW("M");
   sentence += To;
   sentence += From;

   sentence.Finish();

   return( true );
}

BWW const& BWW::operator = ( BWW const& source ) noexcept
{
   BearingTrue     = source.BearingTrue;
   BearingMagnetic = source.BearingMagnetic;
   To              = source.To;
   From            = source.From;

   return( *this );
}
