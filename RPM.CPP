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

void RPM::Empty( void ) noexcept
{
   Source.clear();
   SourceNumber             = 0;
   RevolutionsPerMinute     = 0.0;
   PropellerPitchPercentage = 0.0;
   IsDataValid              = NMEA0183_BOOLEAN::NMEA_Unknown;
}

bool RPM::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** RPM - Revolutions
   **
   **        1 2 3   4   5 6
   **        | | |   |   | |
   ** $--RPM,a,x,x.x,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Sourse, S = Shaft, E = Engine
   **  2) Engine or shaft number
   **  3) Speed, Revolutions per minute
   **  4) Propeller pitch, % of maximum, "-" means astern
   **  5) Status, A means data is valid
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

   Source                   = sentence.Field( 1 );
   SourceNumber             = sentence.Integer( 2 );
   RevolutionsPerMinute     = sentence.Double( 3 );
   PropellerPitchPercentage = sentence.Double( 4 );
   IsDataValid              = sentence.Boolean( 5 );

   return( true );
}

bool RPM::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Source;
   sentence += SourceNumber;
   sentence += RevolutionsPerMinute;
   sentence += PropellerPitchPercentage;
   sentence += IsDataValid;
   
   sentence.Finish();

   return( true );
}

RPM const& RPM::operator = ( RPM const& source ) noexcept
{
   Source                   = source.Source;
   SourceNumber             = source.SourceNumber;
   RevolutionsPerMinute     = source.RevolutionsPerMinute;
   PropellerPitchPercentage = source.PropellerPitchPercentage;
   IsDataValid              = source.IsDataValid;

   return( *this );
}
