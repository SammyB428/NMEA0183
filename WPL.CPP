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

void WPL::Empty( void ) noexcept
{
   Position.Empty();
   To.clear();
}

bool WPL::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** WPL - Waypoint Location
   **
   **        +-------------------------------- 1) Latitude
   **        |       +------------------------ 2) N or S (North or South)
   **        |       | +---------------------- 3) Longitude
   **        |       | |        +------------- 4) E or W (East or West)
   **        |       | |        | +----------- 5) Waypoint name
   **        |       | |        | |    +-------6) Checksum     
   **        |       | |        | |    |
   ** $--WPL,llll.ll,a,yyyyy.yy,a,c--c*hh<CR><LF>
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 6 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   Position.Parse( 1, 2, 3, 4, sentence );
   To = sentence.Field( 5 );

   return( true );
}

bool WPL::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Position;
   sentence += To;

   sentence.Finish();

   return( true );
}

WPL const& WPL::operator = ( WPL const& source ) noexcept
{
   Position = source.Position;
   To       = source.To;

   return( *this );
}
