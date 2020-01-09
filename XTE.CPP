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

void XTE::Empty( void ) noexcept
{
    IsLoranBlinkOK = NMEA0183_BOOLEAN::NMEA_Unknown;
    IsLoranCCycleLockOK = NMEA0183_BOOLEAN::NMEA_Unknown;
    CrossTrackErrorMagnitude = 0.0;
    DirectionToSteer         = LEFTRIGHT::LR_Unknown;
    CrossTrackUnits.clear();
}

bool XTE::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** XTE - Cross-Track Error, Measured
   **
   **        1 2 3   4 5  6
   **        | | |   | |  |
   ** $--XTE,A,A,x.x,a,N,*hh<CR><LF>
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
   **  6) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 6 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   /*
   ** Line has already been checked for checksum validity
   */

   IsLoranBlinkOK           = sentence.Boolean( 1 );
   IsLoranCCycleLockOK      = sentence.Boolean( 2 );
   CrossTrackErrorMagnitude = sentence.Double( 3 );
   DirectionToSteer         = sentence.LeftOrRight( 4 );
   CrossTrackUnits          = sentence.Field( 5 );

   return( true );
}

bool XTE::Write( SENTENCE& sentence ) const noexcept
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

   sentence.Finish();

   return( true );
}

XTE const& XTE::operator = ( XTE const& source ) noexcept
{
   IsLoranBlinkOK           = source.IsLoranBlinkOK;
   IsLoranCCycleLockOK      = source.IsLoranCCycleLockOK;
   CrossTrackErrorMagnitude = source.CrossTrackErrorMagnitude;
   DirectionToSteer         = source.DirectionToSteer;
   CrossTrackUnits          = source.CrossTrackUnits;

   return( *this );
}
