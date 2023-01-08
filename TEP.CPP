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
** There is no recommended replacement.
*/

#include "nmea0183.h"
#pragma hdrstop

void TEP::Empty( void ) noexcept
{
   ElevationDegrees = 0.0;
}

bool TEP::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** TEP - TRANSIT Satellite Predicted Elevation
   **
   **        1   2 3
   **        |   | |
   ** $--TEP,x.x,T*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Elevation degrees
   **  2) D = Degrees
   **  3) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 3 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   ElevationDegrees = sentence.Double( 1 );

   return( true );
}

std::string TEP::PlainEnglish( void ) const noexcept
{
   std::string return_string(STRING_VIEW("TRANSIT satellite predicted elevation is "));

   char temp_string[65];

   auto const number_of_characters{ ::sprintf(temp_string, "%.3f degrees.", ElevationDegrees) };

   return_string.append(temp_string, number_of_characters);

   return( return_string );
}

bool TEP::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */

   RESPONSE::Write( sentence );

   sentence += ElevationDegrees;
   sentence += STRING_VIEW("D");

   sentence.Finish();

   return( true );
}

TEP const& TEP::operator = ( TEP const& source ) noexcept
{
   ElevationDegrees = source.ElevationDegrees;

   return( *this );
}
