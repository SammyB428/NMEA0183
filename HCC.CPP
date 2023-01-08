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

/*
** This Sentence Not Recommended For New Designs
** Use of HDG is recommended.
*/

#include "nmea0183.h"
#pragma hdrstop

void HCC::Empty( void ) noexcept
{
   HeadingDegrees = 0.0;
}

bool HCC::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** HCC - Compass Heading
   **       Vessel compass heading, which differs from magnetic heading by the amount of
   **       uncorrected magnetic deviation.
   **
   **        1   2
   **        |   |
   ** $--HCC,x.x*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Commpass heading, degrees
   **  2) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 2 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   HeadingDegrees = sentence.Double( 1 );

   return( true );
}

std::string HCC::PlainEnglish( void ) const noexcept
{
   std::string return_string(STRING_VIEW("The compass heading is "));

   char temp_string[ 80 ];

   auto const number_of_characters{ ::sprintf(temp_string, "%.2f degrees.", HeadingDegrees) };

   return_string.append(temp_string, number_of_characters);

   return( return_string );
}

bool HCC::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += HeadingDegrees;
   
   sentence.Finish();

   return( true );
}

HCC const& HCC::operator = ( HCC const& source ) noexcept
{
   HeadingDegrees = source.HeadingDegrees;

   return( *this );
}
