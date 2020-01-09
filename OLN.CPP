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

void OLN::Empty( void ) noexcept
{
   Pair1.Empty();
   Pair2.Empty();
   Pair3.Empty();
}

bool OLN::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** OLN - Omega Lane Numbers
   **
   **        1          2          3          4
   **        |--------+ |--------+ |--------+ |
   ** $--OLN,aa,xxx,xxx,aa,xxx,xxx,aa,xxx,xxx*hh<CR><LF>
   **
   **  1) Omega Pair 1
   **  2) Omega Pair 1
   **  3) Omega Pair 1
   **  4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 10 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   Pair1.Parse( 1, sentence );
   Pair2.Parse( 4, sentence );
   Pair3.Parse( 7, sentence );

   return( true );
}

bool OLN::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   Pair1.Write( sentence );
   Pair2.Write( sentence );
   Pair3.Write( sentence );

   sentence.Finish();

   return( true );
}

OLN const& OLN::operator = ( OLN const& source ) noexcept
{
   Pair1 = source.Pair1;
   Pair2 = source.Pair2;
   Pair3 = source.Pair3;

   return( *this );
}
