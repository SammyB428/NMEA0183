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

void RMB::Empty( void ) noexcept
{
   IsDataValid                     = NMEA0183_BOOLEAN::NMEA_Unknown;
   CrossTrackError                 = 0.0;
   DirectionToSteer                = LEFTRIGHT::LR_Unknown;
   To.clear();
   From.clear();
   DestinationPosition.Empty();
   RangeToDestinationNauticalMiles = 0.0;
   BearingToDestinationDegreesTrue = 0.0;
   DestinationClosingVelocityKnots = 0.0;
   IsArrivalCircleEntered          = NMEA0183_BOOLEAN::NMEA_Unknown;
}

bool RMB::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** RMB - Recommended Minimum Navigation Information
   **                                                             14
   **        1 2   3 4    5    6       7 8        9 10  11  12  13|
   **        | |   | |    |    |       | |        | |   |   |   | |
   ** $--RMB,A,x.x,a,c--c,c--c,llll.ll,a,yyyyy.yy,a,x.x,x.x,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Status, V = Navigation receiver warning
   **  2) Cross Track error - nautical miles
   **  3) Direction to Steer, Left or Right
   **  4) TO Waypoint ID
   **  5) FROM Waypoint ID
   **  6) Destination Waypoint Latitude
   **  7) N or S
   **  8) Destination Waypoint Longitude
   **  9) E or W
   ** 10) Range to destination in nautical miles
   ** 11) Bearing to destination in degrees True
   ** 12) Destination closing velocity in knots
   ** 13) Arrival Status, A = Arrival Circle Entered
   ** 14) Checksum
   */

   /*
   ** First we check the checksum...
   */

   auto const check = sentence.IsChecksumBad( 14 );

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

   IsDataValid                     = sentence.Boolean( 1 );
   CrossTrackError                 = sentence.Double( 2 );
   DirectionToSteer                = sentence.LeftOrRight( 3 );
   From                            = sentence.Field( 4 );
   To                              = sentence.Field( 5 );
   DestinationPosition.Parse( 6, 7, 8, 9, sentence );
   RangeToDestinationNauticalMiles = sentence.Double( 10 );
   BearingToDestinationDegreesTrue = sentence.Double( 11 );
   DestinationClosingVelocityKnots = sentence.Double( 12 );
   IsArrivalCircleEntered          = sentence.Boolean( 13 );

   return( true );
}

bool RMB::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += IsDataValid;
   sentence += CrossTrackError;
   sentence += DirectionToSteer;
   sentence += From;
   sentence += To;
   sentence += DestinationPosition;
   sentence += RangeToDestinationNauticalMiles;
   sentence += BearingToDestinationDegreesTrue;
   sentence += DestinationClosingVelocityKnots;
   sentence += IsArrivalCircleEntered;

   sentence.Finish();

   return( true );
}

RMB const& RMB::operator = ( RMB const& source ) noexcept
{
   IsDataValid                     = source.IsDataValid;
   CrossTrackError                 = source.CrossTrackError;
   DirectionToSteer                = source.DirectionToSteer;
   From                            = source.From;
   To                              = source.To;
   DestinationPosition             = source.DestinationPosition;
   RangeToDestinationNauticalMiles = source.RangeToDestinationNauticalMiles;
   BearingToDestinationDegreesTrue = source.BearingToDestinationDegreesTrue;
   DestinationClosingVelocityKnots = source.DestinationClosingVelocityKnots;
   IsArrivalCircleEntered          = source.IsArrivalCircleEntered;

  return( *this );
}
