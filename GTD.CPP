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

void GTD::Empty( void ) noexcept
{
   TimeDifference1.clear();
   TimeDifference2.clear();
   TimeDifference3.clear();
   TimeDifference4.clear();
   TimeDifference5.clear();
}

bool GTD::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** GTD - Geographical Position, Loran-C TDs
   **
   **        1   2   3   4   5   6
   **        |   |   |   |   |   |
   ** $--GTD,x.x,x.x,x.x,x,x,x.x*hh<CR><LF>
   **
   **  1) Time Difference 1 Microseconds
   **  2) Time Difference 2 Microseconds
   **  3) Time Difference 3 Microseconds
   **  4) Time Difference 4 Microseconds
   **  5) Time Difference 5 Microseconds
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

   TimeDifference1 = sentence.Field( 1 );
   TimeDifference2 = sentence.Field( 2 );
   TimeDifference3 = sentence.Field( 3 );
   TimeDifference4 = sentence.Field( 4 );
   TimeDifference5 = sentence.Field( 5 );

   return( true );
}

bool GTD::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += TimeDifference1;
   sentence += TimeDifference2;
   sentence += TimeDifference3;
   sentence += TimeDifference4;
   sentence += TimeDifference5;

   sentence.Finish();

   return( true );
}

GTD const& GTD::operator = ( GTD const& source ) noexcept
{
   TimeDifference1 = source.TimeDifference1;
   TimeDifference2 = source.TimeDifference2;
   TimeDifference3 = source.TimeDifference3;
   TimeDifference4 = source.TimeDifference4;
   TimeDifference5 = source.TimeDifference5;

   return( *this );
}
