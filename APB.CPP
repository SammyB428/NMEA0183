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

void APB::Empty( void ) noexcept
{
   CrossTrackErrorMagnitude = 0.0;
   DirectionToSteer         = LEFTRIGHT::LR_Unknown;
   CrossTrackUnits.clear();
   To.clear();
   IsArrivalCircleEntered   = NMEA0183_BOOLEAN::NMEA_Unknown;
   IsPerpendicular          = NMEA0183_BOOLEAN::NMEA_Unknown;
}

bool APB::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** APB - Autopilot Sentence "B"
   **                                         13    15
   **        1 2 3   4 5 6 7 8   9 10   11  12|   14|
   **        | | |   | | | | |   | |    |   | |   | |
   ** $--APB,A,A,x.x,a,N,A,A,x.x,a,c--c,x.x,a,x.x,a*hh<CR><LF>
   **
   **  1) Status
   **     V = LORAN-C Blink or SNR warning
   **     V = general warning flag or other navigation systems when a reliable
   **         fix is not available
   **  2) Status
   **     V = Loran-C Cycle Lock warning flag
   **     A = OK or not used
   **  3) Cross Track Error Magnitude
   **  4) Direction to steer, L or R
   **  5) Cross Track Units, N = Nautical Miles
   **  6) Status
   **     A = Arrival Circle Entered
   **  7) Status
   **     A = Perpendicular passed at waypoint
   **  8) Bearing origin to destination
   **  9) M = Magnetic, T = True
   ** 10) Destination Waypoint ID
   ** 11) Bearing, present position to Destination
   ** 12) M = Magnetic, T = True
   ** 13) Heading to steer to destination waypoint
   ** 14) M = Magnetic, T = True
   ** 15) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 15 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   /*
   ** Line has already been checked for checksum validity
   */

   IsLoranBlinkOK                           = sentence.Boolean( 1 );
   IsLoranCCycleLockOK                      = sentence.Boolean( 2 );
   CrossTrackErrorMagnitude                 = sentence.Double( 3 );
   DirectionToSteer                         = sentence.LeftOrRight( 4 );
   CrossTrackUnits                          = sentence.Field( 5 );
   IsArrivalCircleEntered                   = sentence.Boolean( 6 );
   IsPerpendicular                          = sentence.Boolean( 7 );
   BearingOriginToDestination               = sentence.Double( 8 );
   BearingOriginToDestinationUnits          = sentence.Field( 9 );
   To                                       = sentence.Field( 10 );
   BearingPresentPositionToDestination      = sentence.Double( 11 );
   BearingPresentPositionToDestinationUnits = sentence.Field( 12 );
   HeadingToSteer                           = sentence.Double( 13 );
   HeadingToSteerUnits                      = sentence.Field( 14 );

   return( true );
}

bool APB::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += IsLoranBlinkOK;
   sentence += IsLoranCCycleLockOK;
   sentence += CrossTrackErrorMagnitude;
   sentence += DirectionToSteer;
   sentence += CrossTrackUnits;
   sentence += IsArrivalCircleEntered;
   sentence += IsPerpendicular;
   sentence += BearingOriginToDestination;
   sentence += BearingOriginToDestinationUnits;
   sentence += To;
   sentence += BearingPresentPositionToDestination;
   sentence += BearingPresentPositionToDestinationUnits;
   sentence += HeadingToSteer;
   sentence += HeadingToSteerUnits;

   sentence.Finish();

   return( true );
}

APB const& APB::operator = ( APB const& source ) noexcept
{
   IsLoranBlinkOK                           = source.IsLoranBlinkOK;
   IsLoranCCycleLockOK                      = source.IsLoranCCycleLockOK;
   CrossTrackErrorMagnitude                 = source.CrossTrackErrorMagnitude;
   DirectionToSteer                         = source.DirectionToSteer;
   CrossTrackUnits                          = source.CrossTrackUnits;
   IsArrivalCircleEntered                   = source.IsArrivalCircleEntered;
   IsPerpendicular                          = source.IsPerpendicular;
   BearingOriginToDestination               = source.BearingOriginToDestination;
   BearingOriginToDestinationUnits          = source.BearingOriginToDestinationUnits;
   To                                       = source.To;
   BearingPresentPositionToDestination      = source.BearingPresentPositionToDestination;
   BearingPresentPositionToDestinationUnits = source.BearingPresentPositionToDestinationUnits;
   HeadingToSteer                           = source.HeadingToSteer;
   HeadingToSteerUnits                      = source.HeadingToSteerUnits;

   return( *this );
}
