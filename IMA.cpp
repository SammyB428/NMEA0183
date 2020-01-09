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
** There is no recommended replacement.
*/

#include "nmea0183.h"
#pragma hdrstop

void IMA::Empty( void ) noexcept
{
   VesselName.clear();
   Callsign.clear();
   HeadingDegreesTrue     = 0.0;
   HeadingDegreesMagnetic = 0.0;
   SpeedKnots             = 0.0;
}

bool IMA::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** IMA - Vessel Identification
   **                                                              11    13
   **        1            2       3       4 5        6 7   8 9   10|   12|
   **        |            |       |       | |        | |   | |   | |   | |
   ** $--IMA,aaaaaaaaaaaa,aaaxxxx,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N*hh<CR><LF>
   **
   **  1) Twelve character vessel name
   **  2) Radio Call Sign
   **  3) Latitude
   **  4) North/South
   **  5) Longitude
   **  6) East/West
   **  7) Heading, degrees true
   **  8) T = True
   **  9) Heading, degrees magnetic
   ** 10) M = Magnetic
   ** 11) Speed
   ** 12) N = Knots
   ** 13) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 13 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   }

   VesselName             = sentence.Field( 1 );
   Callsign               = sentence.Field( 2 );
   Position.Parse( 3, 4, 5, 6, sentence );
   HeadingDegreesTrue     = sentence.Double( 7 );
   HeadingDegreesMagnetic = sentence.Double( 9 );
   SpeedKnots             = sentence.Double( 11 );

   return( true );
}

bool IMA::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += VesselName;
   sentence += Callsign;
   sentence += Position;
   sentence += HeadingDegreesTrue;
   sentence += STRING_VIEW("T");
   sentence += HeadingDegreesMagnetic;
   sentence += STRING_VIEW("M");
   sentence += SpeedKnots;
   sentence += STRING_VIEW("N");

   sentence.Finish();

   return( true );
}

IMA const& IMA::operator = ( IMA const& source ) noexcept
{
   VesselName             = source.VesselName;
   Callsign               = source.Callsign;
   Position               = source.Position;
   HeadingDegreesTrue     = source.HeadingDegreesTrue;
   HeadingDegreesMagnetic = source.HeadingDegreesMagnetic;
   SpeedKnots             = source.SpeedKnots;

   return( *this );
}
