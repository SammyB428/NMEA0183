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

void HSC::Empty( void ) noexcept
{
   DegreesTrue     = 0.0;
   DegreesMagnetic = 0.0;
}

bool HSC::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** HSC - Heading Steering Command
   **
   **        1   2 3   4  5
   **        |   | |   |  |
   ** $--HSC,x.x,T,x.x,M,*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Heading Degrees, True
   **  2) T = True
   **  3) Heading Degrees, Magnetic
   **  4) M = Magnetic
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

   DegreesTrue     = sentence.Double( 1 );
   DegreesMagnetic = sentence.Double( 3 );

   return( true );
}

bool HSC::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += DegreesTrue;
   sentence += STRING_VIEW("T");
   sentence += DegreesMagnetic;
   sentence += STRING_VIEW("M");

   sentence.Finish();

   return( true );
}

HSC const& HSC::operator = ( HSC const& source ) noexcept
{
   DegreesTrue     = source.DegreesTrue;
   DegreesMagnetic = source.DegreesMagnetic;

   return( *this );
}
