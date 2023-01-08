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

void SFI::Empty( void ) noexcept
{
   TotalMessages = 0.0;
   MessageNumber = 0.0;

   for (auto& entry : Frequencies)
   {
       entry.Empty();
   }
}

bool SFI::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** SFI - Scanning Frequency Information
   **
   **        1   2   3      4                     x
   **        |   |   |      |                     |
   ** $--SFI,x.x,x.x,xxxxxx,c .......... xxxxxx,c*hh<CR><LF>
   **
   **  1) Total Number Of Messages
   **  2) Message Number
   **  3) Frequency 1
   **  4) Mode 1
   **  x) Checksum
   */

   /*
   ** First we check the checksum...
   */

   auto const number_of_data_fields{ sentence.GetNumberOfDataFields() };

   if ( sentence.IsChecksumBad( number_of_data_fields + 1 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   TotalMessages = sentence.Double( 1 );
   MessageNumber = sentence.Double( 2 );

   /*
   ** Clear out any old data
   */

   for (auto& entry : Frequencies)
   {
       entry.Empty();
   }

   int number_of_frequencies{ (number_of_data_fields - 2) / 2 };
   int frequency_number{ 0 };

   /*
   ** index is the number of data fields before the frequency/mode +
   ** the frequency number times the number of fields in a FREQUENC_AND_MODE
   */

   while( frequency_number < number_of_frequencies )
   {
      auto const index{ 2 + (static_cast<std::size_t>(frequency_number) * 2) };

      Frequencies[ frequency_number ].Parse( static_cast<int>(index), sentence );

      frequency_number++;
   }

   return( true );
}

bool SFI::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += TotalMessages;
   sentence += MessageNumber;

   for (auto const& entry : Frequencies)
   {
       entry.Write(sentence);
   }

   sentence.Finish();

   return( true );
}

SFI const& SFI::operator = ( SFI const& source ) noexcept
{
   TotalMessages = source.TotalMessages;
   MessageNumber = source.MessageNumber;

   std::size_t index{ 0 };

   while( index < std::size(Frequencies) )
   {
      Frequencies[ index ] = source.Frequencies[ index ];
      index++;
   }

   return( *this );
}
