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

void ALM::Empty( void ) noexcept
{
   NumberOfMessages         = 0;
   MessageNumber            = 0;
   PRNNumber                = 0;
   WeekNumber               = 0;
   SVHealth                 = 0;
   Eccentricity             = 0;
   AlmanacReferenceTime     = 0;
   InclinationAngle         = 0;
   RateOfRightAscension     = 0;
   RootOfSemiMajorAxis      = 0;
   ArgumentOfPerigee        = 0;
   LongitudeOfAscensionNode = 0;
   MeanAnomaly              = 0;
   F0ClockParameter         = 0;
   F1ClockParameter         = 0;
}

bool ALM::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** ALM - GPS Almanac Data
   **
   **        1   2   3  4   5  6    7  8    9    10     11     12     13     14  15   16
   **        |   |   |  |   |  |    |  |    |    |      |      |      |      |   |    |
   ** $--ALM,x.x,x.x,xx,x.x,hh,hhhh,hh,hhhh,hhhh,hhhhhh,hhhhhh,hhhhhh,hhhhhh,hhh,hhh,*hh<CR><LF>
   **
   **  1) Total number of messages
   **  2) Message Number
   **  3) Satellite PRN number (01 to 32)
   **  4) GPS Week Number
   **  5) SV health, bits 17-24 of each almanac page
   **  6) Eccentricity
   **  7) Almanac Reference Time
   **  8) Inclination Angle
   **  9) Rate of Right Ascension
   ** 10) Root of semi-major axis
   ** 11) Argument of perigee
   ** 12) Longitude of ascension node
   ** 13) Mean anomaly
   ** 14) F0 Clock Parameter
   ** 15) F1 Clock Parameter
   ** 16) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 16 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   NumberOfMessages         = static_cast<uint16_t>(sentence.Integer( 1 ));
   MessageNumber            = static_cast<uint16_t>(sentence.Integer( 2 ));
   PRNNumber                = static_cast<uint16_t>(sentence.Integer( 3 ));
   WeekNumber               = static_cast<uint16_t>(sentence.Integer( 4 ));
   SVHealth                 = static_cast<uint16_t>(::HexValue( sentence.Field( 5 ) ));
   Eccentricity             = static_cast<uint16_t>(::HexValue( sentence.Field( 6 ) ));
   AlmanacReferenceTime     = static_cast<uint16_t>(::HexValue( sentence.Field( 7 ) ));
   InclinationAngle         = static_cast<uint16_t>(::HexValue( sentence.Field( 8 ) ));
   RateOfRightAscension     = static_cast<uint16_t>(::HexValue( sentence.Field( 9 ) ));
   RootOfSemiMajorAxis      = ::HexValue( sentence.Field( 10 ) );
   ArgumentOfPerigee        = ::HexValue( sentence.Field( 11 ) );
   LongitudeOfAscensionNode = ::HexValue( sentence.Field( 12 ) );
   MeanAnomaly              = ::HexValue( sentence.Field( 13 ) );
   F0ClockParameter         = static_cast<uint16_t>(::HexValue( sentence.Field( 14 ) ));
   F1ClockParameter         = static_cast<uint16_t>(::HexValue( sentence.Field( 15 ) ));

   return( true );
}

bool ALM::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Hex( NumberOfMessages ); // Thanks to Chuck Shannon, cshannon@imtn.tpd.dsccc.com
   sentence += Hex( MessageNumber );    // Thanks to Chuck Shannon, cshannon@imtn.tpd.dsccc.com
   sentence += Hex( PRNNumber );        // Thanks to Chuck Shannon, cshannon@imtn.tpd.dsccc.com
   sentence += Hex( WeekNumber );       // Thanks to Chuck Shannon, cshannon@imtn.tpd.dsccc.com
   sentence += Hex( SVHealth );
   sentence += Hex( Eccentricity );
   sentence += Hex( AlmanacReferenceTime );
   sentence += Hex( InclinationAngle );
   sentence += Hex( RateOfRightAscension );
   sentence += Hex( RootOfSemiMajorAxis );
   sentence += Hex( ArgumentOfPerigee );
   sentence += Hex( LongitudeOfAscensionNode );
   sentence += Hex( MeanAnomaly );
   sentence += Hex( F0ClockParameter );
   sentence += Hex( F1ClockParameter );

   sentence.Finish();

   return( true );
}

ALM const& ALM::operator = ( ALM const& source ) noexcept
{
   NumberOfMessages         = source.NumberOfMessages;
   MessageNumber            = source.MessageNumber;
   PRNNumber                = source.PRNNumber;
   WeekNumber               = source.WeekNumber;
   SVHealth                 = source.SVHealth;
   Eccentricity             = source.Eccentricity;
   AlmanacReferenceTime     = source.AlmanacReferenceTime;
   InclinationAngle         = source.InclinationAngle;
   RateOfRightAscension     = source.RateOfRightAscension;
   RootOfSemiMajorAxis      = source.RootOfSemiMajorAxis;
   ArgumentOfPerigee        = source.ArgumentOfPerigee;
   LongitudeOfAscensionNode = source.LongitudeOfAscensionNode;
   MeanAnomaly              = source.MeanAnomaly;
   F0ClockParameter         = source.F0ClockParameter;
   F1ClockParameter         = source.F1ClockParameter;

   return( *this );
}
