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

void LORAN_TIME_DIFFERENCE::Empty( void ) noexcept
{
   Microseconds = 0.0;
   SignalStatus = LORAN_SIGNAL_STATUS::LoranUnknown;
}

void LORAN_TIME_DIFFERENCE::Parse( int first_field_number, SENTENCE const& sentence ) noexcept
{
   Microseconds = sentence.Double( first_field_number );

   auto field_data{ sentence.Field(first_field_number + 1) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'B')
       {
           SignalStatus = LORAN_SIGNAL_STATUS::LoranBlinkWarning;
       }
       else if (field_data[0] == 'C')
       {
           SignalStatus = LORAN_SIGNAL_STATUS::LoranCycleWarning;
       }
       else if (field_data[0] == 'S')
       {
           SignalStatus = LORAN_SIGNAL_STATUS::LoranSignalToNoiseRatioWarning;
       }
       else if (field_data[0] == 'A')
       {
           SignalStatus = LORAN_SIGNAL_STATUS::LoranValid;
       }
       else
       {
           SignalStatus = LORAN_SIGNAL_STATUS::LoranUnknown;
       }
   }
   else
   {
       SignalStatus = LORAN_SIGNAL_STATUS::LoranUnknown;
   }
}

void LORAN_TIME_DIFFERENCE::Write( SENTENCE& sentence ) const noexcept
{
   sentence += Microseconds;

   switch( SignalStatus )
   {
   case LORAN_SIGNAL_STATUS::LoranValid:
      
         sentence += STRING_VIEW("A");
         break; 

   case LORAN_SIGNAL_STATUS::LoranBlinkWarning:
      
         sentence += STRING_VIEW("B");
         break; 

   case LORAN_SIGNAL_STATUS::LoranCycleWarning:
      
         sentence += STRING_VIEW("C");
         break; 

   case LORAN_SIGNAL_STATUS::LoranSignalToNoiseRatioWarning:
      
         sentence += STRING_VIEW("S");
         break; 

      default:

         sentence += STRING_VIEW("");
   }
}

LORAN_TIME_DIFFERENCE const& LORAN_TIME_DIFFERENCE::operator = ( LORAN_TIME_DIFFERENCE const& source ) noexcept
{
   Microseconds = source.Microseconds;
   SignalStatus = source.SignalStatus;

   return( *this );
}
