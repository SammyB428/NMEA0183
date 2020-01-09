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

void DBT::Empty( void ) noexcept
{
   DepthFeet    = 0.0;
   DepthMeters  = 0.0;
   DepthFathoms = 0.0;
}

bool DBT::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** DBT - Depth below transducer
   **
   **        1   2 3   4 5   6 7
   **        |   | |   | |   | |
   ** $--DBT,x.x,f,x.x,M,x.x,F*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Depth, feet
   **  2) f = feet
   **  3) Depth, meters
   **  4) M = meters
   **  5) Depth, Fathoms
   **  6) F = Fathoms
   **  7) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   DepthFeet    = sentence.Double( 1 );
   DepthMeters  = sentence.Double( 3 );
   DepthFathoms = sentence.Double( 5 );

   return( true );
}

bool DBT::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += DepthFeet;
   sentence += STRING_VIEW("f");
   sentence += DepthMeters;
   sentence += STRING_VIEW("M");
   sentence += DepthFathoms;
   sentence += STRING_VIEW("F");

   sentence.Finish();

   return( true );
}

DBT const& DBT::operator = ( DBT const& source ) noexcept
{
   DepthFeet    = source.DepthFeet;
   DepthMeters  = source.DepthMeters;
   DepthFathoms = source.DepthFathoms;

   return( *this );
}
