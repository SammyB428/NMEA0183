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

void RMA::Empty( void ) noexcept
{
   IsDataValid                = NMEA0183_BOOLEAN::NMEA_Unknown;
   TimeDifferenceA            = 0.0;
   TimeDifferenceB            = 0.0;
   SpeedOverGroundKnots       = 0.0;
   TrackMadeGoodDegreesTrue   = 0.0;
   MagneticVariation          = 0.0;
   MagneticVariationDirection = EASTWEST::EW_Unknown;
}

bool RMA::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** RMA - Recommended Minimum Navigation Information
   **                                                    12
   **        1 2       3 4        5 6   7   8   9   10  11|
   **        | |       | |        | |   |   |   |   |   | |
   ** $--RMA,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,x.x,x.x,x.x,a*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Blink Warning
   **  2) Latitude
   **  3) N or S
   **  4) Longitude
   **  5) E or W
   **  6) Time Difference A, uS
   **  7) Time Difference B, uS
   **  8) Speed Over Ground, Knots
   **  9) Track Made Good, degrees true
   ** 10) Magnetic Variation, degrees
   ** 11) E or W
   ** 12) Checksum
   */

   /*
   ** First we check the checksum...
   */

   auto const check{ sentence.IsChecksumBad(12) };

   if ( check == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   }
   
   if ( check == NMEA0183_BOOLEAN::NMEA_Unknown )
   {
       SetErrorMessage(STRING_VIEW("Missing Checksum"));
       return( false );
   } 

   IsDataValid                = sentence.Boolean( 1 );
   Position.Parse( 2, 3, 4, 5, sentence );
   TimeDifferenceA            = sentence.Double( 6 );
   TimeDifferenceB            = sentence.Double( 7 );
   SpeedOverGroundKnots       = sentence.Double( 8 );
   TrackMadeGoodDegreesTrue   = sentence.Double( 9 );
   MagneticVariation          = sentence.Double( 10 );
   MagneticVariationDirection = sentence.EastOrWest( 11 );

   return( true );
}

bool RMA::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += IsDataValid;
   sentence += Position;
   sentence += TimeDifferenceA;
   sentence += TimeDifferenceB;
   sentence += SpeedOverGroundKnots;
   sentence += TrackMadeGoodDegreesTrue;
   sentence += MagneticVariation;
   sentence += MagneticVariationDirection;

   sentence.Finish();

   return( true );
}

RMA const& RMA::operator = ( RMA const& source ) noexcept
{
   IsDataValid                = source.IsDataValid;
   Position                   = source.Position;
   TimeDifferenceA            = source.TimeDifferenceA;
   TimeDifferenceB            = source.TimeDifferenceB;
   SpeedOverGroundKnots       = source.SpeedOverGroundKnots;
   TrackMadeGoodDegreesTrue   = source.TrackMadeGoodDegreesTrue;
   MagneticVariation          = source.MagneticVariation;
   MagneticVariationDirection = source.MagneticVariationDirection;

   return( *this );
}
