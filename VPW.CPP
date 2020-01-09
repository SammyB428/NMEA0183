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

void VPW::Empty( void ) noexcept
{
   Knots           = 0.0;
   MetersPerSecond = 0.0;
}

bool VPW::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** VPW - Speed - Measured Parallel to Wind
   **
   **        1   2 3   4 5
   **        |   | |   | |
   ** $--VPW,x.x,N,x.x,M*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Speed, "-" means downwind
   **  2) N = Knots
   **  3) Speed, "-" means downwind
   **  4) M = Meters per second
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

   Knots           = sentence.Double( 1 );
   MetersPerSecond = sentence.Double( 3 );

   return( true );
}

bool VPW::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Knots;
   sentence += STRING_VIEW("N");
   sentence += MetersPerSecond;
   sentence += STRING_VIEW("M");

   sentence.Finish();

   return( true );
}

VPW const& VPW::operator = ( VPW const& source ) noexcept
{
   Knots           = source.Knots;
   MetersPerSecond = source.MetersPerSecond;

   return( *this );
}
