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

void LCD::Empty( void ) noexcept
{
   GroupRepetitionInterval = 0;
   Master.Empty();
   Secondary1.Empty();
   Secondary2.Empty();
   Secondary3.Empty();
   Secondary4.Empty();
   Secondary5.Empty();
}

bool LCD::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** LCD - Loran-C Signal Data
   **
   **        1    2   3   4   5   6   7   8   9   10  11  12  13  14
   **        |    |   |   |   |   |   |   |   |   |   |   |   |   |
   ** $--LCD,xxxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx*hh<CR><LF>
   **
   **  1) Group Repetition Interval (GRI) Microseconds/10
   **  2) Master Relative SNR
   **  3) Master Relative ECD
   **  4) Time Difference 1 Microseconds
   **  5) Time Difference 1 Signal Status
   **  6) Time Difference 2 Microseconds
   **  7) Time Difference 2 Signal Status
   **  8) Time Difference 3 Microseconds
   **  9) Time Difference 3 Signal Status
   ** 10) Time Difference 4 Microseconds
   ** 11) Time Difference 4 Signal Status
   ** 12) Time Difference 5 Microseconds
   ** 13) Time Difference 5 Signal Status
   ** 14) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 14 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   GroupRepetitionInterval = sentence.Integer( 1 );
   Master.Parse( 2, sentence );
   Secondary1.Parse( 4, sentence );
   Secondary2.Parse( 6, sentence );
   Secondary3.Parse( 8, sentence );
   Secondary4.Parse( 10, sentence );
   Secondary5.Parse( 12, sentence );

   return( true );
}

bool LCD::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += GroupRepetitionInterval;
   Master.Write( sentence );
   Secondary1.Write( sentence );
   Secondary2.Write( sentence );
   Secondary3.Write( sentence );
   Secondary4.Write( sentence );
   Secondary5.Write( sentence );

   sentence.Finish();

   return( true );
}

LCD const& LCD::operator = ( LCD const& source ) noexcept
{
   GroupRepetitionInterval = source.GroupRepetitionInterval;
   Master                  = source.Master;
   Secondary1              = source.Secondary1;
   Secondary2              = source.Secondary2;
   Secondary3              = source.Secondary3;
   Secondary4              = source.Secondary4;
   Secondary5              = source.Secondary5;

   return( *this );
}
