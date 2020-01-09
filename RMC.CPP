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

void RMC::Empty( void ) noexcept
{
   UTCTime.clear();
   Time                       = 0;
   IsDataValid                = NMEA0183_BOOLEAN::NMEA_Unknown;
   Position.Empty();
   SpeedOverGroundKnots       = 0.0;
   TrackMadeGoodDegreesTrue   = 0.0;
   Date.clear();
   MagneticVariation          = 0.0;
   MagneticVariationDirection = EASTWEST::EW_Unknown;
}

bool RMC::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** RMC - Recommended Minimum Navigation Information
   **                                                            12
   **        1         2 3       4 5        6 7   8   9    10  11|
   **        |         | |       | |        | |   |   |    |   | |
   ** $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxx,x.x,a*hh<CR><LF>
   **
   ** Field Number: 
   **  1) UTC Time
   **  2) Status, V = Navigation receiver warning
   **  3) Latitude
   **  4) N or S
   **  5) Longitude
   **  6) E or W
   **  7) Speed over ground, knots
   **  8) Track made good, degrees true
   **  9) Date, ddmmyy
   ** 10) Magnetic Variation, degrees
   ** 11) E or W
   ** 12) Checksum
   */

   /*
   ** First we check the checksum...
   */

   NMEA0183_BOOLEAN const check = sentence.IsChecksumBad( 12 );

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

   UTCTime                    = sentence.Field( 1 );
   Time                       = sentence.Time( 1 );
   IsDataValid                = sentence.Boolean( 2 );
   Position.Parse( 3, 4, 5, 6, sentence );
   SpeedOverGroundKnots       = sentence.Double( 7 );
   TrackMadeGoodDegreesTrue   = sentence.Double( 8 );
   Date                       = sentence.Field( 9 );
   MagneticVariation          = sentence.Double( 10 );
   MagneticVariationDirection = sentence.EastOrWest( 11 );

   return( true );
}

std::string RMC::PlainEnglish( void ) const noexcept
{
   std::string return_string(STRING_VIEW("At "));
   std::string const time_string = ctime(&Time);
   return_string.append(time_string.substr(0, time_string.length() - 1));
   return_string.append(STRING_VIEW(" you were at "));
   return_string.append(Position.PlainEnglish());
   return_string.append(STRING_VIEW(", making "));

   char temp_string[ 128 ];

   std::size_t number_of_characters = ::sprintf( temp_string, "%lg", SpeedOverGroundKnots );

   return_string.append(temp_string, number_of_characters);
   return_string.append(STRING_VIEW(" knots, track made good "));

   number_of_characters = ::sprintf(temp_string, "%lg", TrackMadeGoodDegreesTrue );
   return_string.append(temp_string, number_of_characters);
   return_string.append(STRING_VIEW(" degrees true."));

   return( return_string );
}

bool RMC::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += IsDataValid;
   sentence += Position;
   sentence += SpeedOverGroundKnots;
   sentence += TrackMadeGoodDegreesTrue;
   sentence += Date;
   sentence += MagneticVariation;
   sentence += MagneticVariationDirection;

   sentence.Finish();

   return( true );
}

RMC const& RMC::operator = ( RMC const& source ) noexcept
{
   UTCTime                    = source.UTCTime;
   Time                       = source.Time;
   IsDataValid                = source.IsDataValid;
   Position                   = source.Position;
   SpeedOverGroundKnots       = source.SpeedOverGroundKnots;
   TrackMadeGoodDegreesTrue   = source.TrackMadeGoodDegreesTrue;
   Date                       = source.Date;
   MagneticVariation          = source.MagneticVariation;
   MagneticVariationDirection = source.MagneticVariationDirection;

  return( *this );
}
