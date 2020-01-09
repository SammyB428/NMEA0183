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

void MWV::Empty( void ) noexcept
{
   WindAngle   = 0.0;
   Reference.clear();
   WindSpeed   = 0.0;
   WindSpeedUnits.clear();
   IsDataValid = NMEA0183_BOOLEAN::NMEA_Unknown;
}

bool MWV::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** MWV - Wind Speed and Angle
   **
   **        1   2 3   4 5
   **        |   | |   | |
   ** $--MWV,x.x,a,x.x,a*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Wind Angle, 0 to 360 degrees
   **  2) Reference, R = Relative, T = True
   **  3) Wind Speed
   **  4) Wind Speed Units, K/M/N
   **  5) Status, A = Data Valid
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

   WindAngle      = sentence.Double( 1 );
   Reference      = sentence.Field( 2 );
   WindSpeed      = sentence.Double( 3 );
   WindSpeedUnits = sentence.Field( 4 );
   IsDataValid    = sentence.Boolean( 5 );

   return( false );
}

bool MWV::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += WindAngle;
   sentence += Reference;
   sentence += WindSpeed;
   sentence += WindSpeedUnits;
   sentence += IsDataValid;

   sentence.Finish();

   return( true );
}

MWV const& MWV::operator = ( MWV const& source ) noexcept
{
   WindAngle      = source.WindAngle;
   Reference      = source.Reference;
   WindSpeed      = source.WindSpeed;
   WindSpeedUnits = source.WindSpeedUnits;
   IsDataValid    = source.IsDataValid;

   return( *this );
}
