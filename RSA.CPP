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

void RSA::Empty( void ) noexcept
{
   Starboard            = 0.0;
   IsStarboardDataValid = NMEA0183_BOOLEAN::NMEA_Unknown;
   Port                 = 0.0;
   IsPortDataValid      = NMEA0183_BOOLEAN::NMEA_Unknown;
}

bool RSA::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** RSA - Rudder Sensor Angle
   **
   **        1   2 3   4 5
   **        |   | |   | |
   ** $--RSA,x.x,A,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Starboard (or single) rudder sensor, "-" means Turn To Port
   **  2) Status, A means data is valid
   **  3) Port rudder sensor
   **  4) Status, A means data is valid
   **  5) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 5 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   Starboard            = sentence.Double(  1 );
   IsStarboardDataValid = sentence.Boolean( 2 );
   Port                 = sentence.Double(  3 );
   IsPortDataValid      = sentence.Boolean( 4 );

   return( true );
}

bool RSA::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Starboard;
   sentence += IsStarboardDataValid;
   sentence += Port;
   sentence += IsPortDataValid;
   
   sentence.Finish();

   return( true );
}

RSA const& RSA::operator = ( RSA const& source ) noexcept
{
   Starboard            = source.Starboard;
   IsStarboardDataValid = source.IsStarboardDataValid;
   Port                 = source.Port;
   IsPortDataValid      = source.IsPortDataValid;

   return( *this );
}
