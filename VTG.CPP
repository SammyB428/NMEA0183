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

void VTG::Empty( void ) noexcept
{
   TrackDegreesTrue       = 0.0;
   TrackDegreesMagnetic   = 0.0;
   SpeedKnots             = 0.0;
   SpeedKilometersPerHour = 0.0;
}

bool VTG::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** VTG - Track made good and Ground speed
   **
   **        1   2 3   4 5	 6 7   8 9
   **        |   | |   | |	 | |   | |
   ** $--VTG,x.x,T,x.x,M,x.x,N,x.x,K*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Track Degrees
   **  2) T = True
   **  3) Track Degrees
   **  4) M = Magnetic
   **  5) Speed Knots
   **  6) N = Knots
   **  7) Speed Kilometers Per Hour
   **  8) K = Kilometers Per Hour
   **  9) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 9 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   TrackDegreesTrue       = sentence.Double( 1 );
   TrackDegreesMagnetic   = sentence.Double( 3 );
   SpeedKnots             = sentence.Double( 5 );
   SpeedKilometersPerHour = sentence.Double( 7 );

   return( true );
}

bool VTG::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += TrackDegreesTrue;
   sentence += STRING_VIEW("T");
   sentence += TrackDegreesMagnetic;
   sentence += STRING_VIEW("M");
   sentence += SpeedKnots;
   sentence += STRING_VIEW("N");
   sentence += SpeedKilometersPerHour;
   sentence += STRING_VIEW("K");

   sentence.Finish();

   return( true );
}

VTG const& VTG::operator = ( VTG const& source ) noexcept
{
   TrackDegreesTrue       = source.TrackDegreesTrue;
   TrackDegreesMagnetic   = source.TrackDegreesMagnetic;
   SpeedKnots             = source.SpeedKnots;
   SpeedKilometersPerHour = source.SpeedKilometersPerHour;

   return( *this );
}
