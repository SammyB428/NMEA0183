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

void LATLONG::Empty( void ) noexcept
{
   Latitude.Empty();
   Longitude.Empty();
}

bool LATLONG::Parse( int LatitudePositionFieldNumber, int NorthingFieldNumber, int LongitudePositionFieldNumber, int EastingFieldNumber, SENTENCE const& LineToParse ) noexcept
{
   Latitude.Parse(  LatitudePositionFieldNumber, NorthingFieldNumber, LineToParse );
   Longitude.Parse( LongitudePositionFieldNumber, EastingFieldNumber, LineToParse );

   if ( Latitude.IsDataValid() == true and Longitude.IsDataValid() == true )
   {
      return( true );
   }
   else
   {
      return( false );
   }
}

std::string LATLONG::PlainEnglish( void ) const noexcept
{
   char temp_string[256];

   auto number_of_characters{ ::sprintf(temp_string, "Latitude %d %.5f", Latitude.GetWholeDegrees(), Latitude.GetDecimalMinutes()) };

   std::string return_string(temp_string, number_of_characters);

   if ( Latitude.Northing == NORTHSOUTH::North )
   {
      return_string.append(STRING_VIEW(" North, Longitude "));
   }
   else
   {
      return_string.append(STRING_VIEW(" South, Longitude "));
   }

   number_of_characters = ::sprintf( temp_string, "%d %.5f", Longitude.GetWholeDegrees(), Longitude.GetDecimalMinutes() );

   return_string.append(temp_string, number_of_characters);

   if ( Longitude.Easting == EASTWEST::East )
   {
      return_string.append(STRING_VIEW(" East"));
   }
   else
   {
      return_string.append(STRING_VIEW(" West"));
   }

   return( return_string );
}

void LATLONG::Write( SENTENCE& sentence ) const noexcept
{
   Latitude.Write( sentence );
   Longitude.Write( sentence );
}

LATLONG const& LATLONG::operator = ( LATLONG const& source ) noexcept
{
   Latitude  = source.Latitude;
   Longitude = source.Longitude;

   return( *this );
}
