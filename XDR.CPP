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

void XDR::Empty( void ) noexcept
{
    Transducers.clear();
}

bool XDR::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** XDR - Transducer Reading
   **
   **        1 2   3 4			    n
   **        | |   | |            |
   ** $--XDR,a,x.x,a,c--c, ..... *hh<CR><LF>
   **
   ** Field Number: 
   **  1) Transducer Type
   **  2) Measurement Data
   **  3) Units of measurement
   **  4) Name of transducer
   **  x) More of the same
   **  n) Checksum
   */

   Empty();

   int field_number{ 1 };

   TRANSDUCER_DATA transducer_data;

   while( sentence.Field( field_number + 1 ).empty() == false )
   {
       transducer_data.Empty();

      transducer_data.Parse( field_number, sentence );
      Transducers.push_back( transducer_data );
      
      field_number += 4;
   }

   return( true );
}

bool XDR::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   for (auto const& entry : Transducers)
   {
       entry.Write(sentence);
   }

   sentence.Finish();

   return( true );
}

void TRANSDUCER_DATA::Empty( void ) noexcept
{
   TransducerType  = TRANSDUCER_TYPE::TransducerUnknown;
   MeasurementData = 0.0;
   MeasurementUnits.clear();
   TransducerName.clear();
}

void TRANSDUCER_DATA::Parse( int first_field_number, SENTENCE const& sentence ) noexcept
{
   TransducerType   = sentence.TransducerType( first_field_number );
   MeasurementData  = sentence.Double( first_field_number + 1 );
   MeasurementUnits = sentence.Field(  first_field_number + 2 );
   TransducerName   = sentence.Field(  first_field_number + 3 );
}

void TRANSDUCER_DATA::Write( SENTENCE& sentence ) const noexcept
{
   sentence += TransducerType;
   sentence += MeasurementData;
   sentence += MeasurementUnits;
   sentence += TransducerName;
}

TRANSDUCER_DATA const& TRANSDUCER_DATA::operator = ( TRANSDUCER_DATA const& source ) noexcept
{
   TransducerType   = source.TransducerType;
   MeasurementData  = source.MeasurementData;
   MeasurementUnits = source.MeasurementUnits;
   TransducerName   = source.TransducerName;

   return( *this );
}
