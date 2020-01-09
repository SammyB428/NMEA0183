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

void FREQUENCY_AND_MODE::Empty( void ) noexcept
{
   Frequency = 0.0;
   Mode      = COMMUNICATIONS_MODE::CommunicationsModeUnknown;
}

void FREQUENCY_AND_MODE::Parse( int first_field_number, SENTENCE const& sentence ) noexcept
{
   Frequency = sentence.Double( first_field_number );
   Mode      = sentence.CommunicationsMode( first_field_number + 1 );
}

void FREQUENCY_AND_MODE::Write( SENTENCE& sentence ) const noexcept
{
   sentence += Frequency;
   sentence += Mode;
}

FREQUENCY_AND_MODE const& FREQUENCY_AND_MODE::operator = ( FREQUENCY_AND_MODE const& source ) noexcept
{
   Frequency = source.Frequency;
   Mode      = source.Mode;

   return( *this );
}
