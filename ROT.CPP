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

void ROT::Empty( void ) noexcept
{
   RateOfTurn  = 0.0;
   IsDataValid = NMEA0183_BOOLEAN::NMEA_Unknown;
}

bool ROT::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** ROT - Rate Of Turn
   **
   **        1   2 3
   **        |   | |
   ** $--ROT,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Rate Of Turn, degrees per minute, "-" means bow turns to port
   **  2) Status, A means data is valid
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

   RateOfTurn  = sentence.Double( 1 );
   IsDataValid = sentence.Boolean( 2 );

   return( true );
}

std::string ROT::PlainEnglish( void ) const noexcept
{
   std::string return_string(STRING_VIEW("The bow is turning to "));

   char temp_string[ 80 ];

   std::size_t number_of_characters{ 0 };

   if ( RateOfTurn < 0 )
   {
      number_of_characters = ::sprintf( temp_string, "Port at a rate of %.1f degrees per minute.", static_cast<double>(RateOfTurn * -1.0) );
   }
   else
   {
      number_of_characters = ::sprintf( temp_string, "Starboard at a rate of %.1f degrees per minute.", RateOfTurn );
   }

   return_string.append(temp_string, number_of_characters);

   if ( IsDataValid not_eq NMEA0183_BOOLEAN::True )
   {
      if ( IsDataValid == NMEA0183_BOOLEAN::False )
      {
         return_string.append(STRING_VIEW(" However, this data is not valid."));
      }
      else
      {
         return_string.append(STRING_VIEW(" However, this data cannot be confirmed."));
      }
   }

   return( return_string );
}

bool ROT::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */

   RESPONSE::Write( sentence );

   sentence += RateOfTurn;
   sentence += IsDataValid;

   sentence.Finish();

   return( true );
}

ROT const& ROT::operator = ( ROT const& source ) noexcept
{
   RateOfTurn  = source.RateOfTurn;
   IsDataValid = source.IsDataValid;

   return( *this );
}
