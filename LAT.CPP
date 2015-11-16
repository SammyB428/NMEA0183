/*
Author: Samuel R. Blackburn
Internet: wfc@pobox.com

"You can get credit for something or get it done, but not both."
Dr. Richard Garwin

The MIT License (MIT)

Copyright (c) 1996-2015 Sam Blackburn

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

#include "nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

LATITUDE::LATITUDE()
{
   Empty();
}

LATITUDE::~LATITUDE()
{
   Empty();
}

void LATITUDE::Empty( void )
{
   Latitude = 0.0;
   Northing = NS_Unknown;
}

bool LATITUDE::IsDataValid( void )
{
   if ( Northing != North && Northing != South )
   {
      return( false );
   }

   return( true );
}

void LATITUDE::Parse( int position_field_number, int north_or_south_field_number, const SENTENCE& sentence )
{
   // Thanks go to Eric Parsonage (ericpa@mpx.com.au) for finding a nasty
   // little bug that used to live here.

   double position = 0.0;

   position = sentence.Double( position_field_number );

   std::string north_or_south = sentence.Field( north_or_south_field_number );

   Set( position, north_or_south.c_str() );
}

void LATITUDE::Set( double position, const char *north_or_south )
{
   Latitude   = position;
   Coordinate = position;
   
   if ( north_or_south[ 0 ] == 'N' )
   {
      Northing = North;
   }
   else if ( north_or_south[ 0 ] == 'S' )
   {
      Northing = South;
   }
   else
   {
      Northing = NS_Unknown;
   }
}

void LATITUDE::Write( SENTENCE& sentence )
{
   char temp_string[ 80 ];

   ::sprintf( temp_string, "%07.2f", Latitude );
   sentence += temp_string;
   
   if ( Northing == North )
   {
      sentence += "N";
   }
   else if ( Northing == South )
   {
      sentence += "S";
   }
   else
   {
      /*
      ** Thanks to Jan-Erik Eriksson (Jan-Erik.Eriksson@st.se) for
      ** finding and fixing a bug here
      */

      sentence += "";
   }
}

const LATITUDE& LATITUDE::operator = ( const LATITUDE& source )
{
   Latitude = source.Latitude;
   Northing = source.Northing;

   return( *this );
}

// COORDINATE stuff

// Coordinates are in the format dddmm.ddd
// For example, 76 degrees 46.887 minutes would be 7646.887

double COORDINATE::GetDecimalDegrees( void ) const
{
   double return_value = 0.0;

   int degrees = (int) ::floor( Coordinate );
   int minutes = degrees % 100;

   double fractional_minutes = 0.0;
   double throw_away         = 0.0;

   fractional_minutes = ::modf( Coordinate, &throw_away );

   degrees -= minutes;
   degrees /= 100;

   return_value = degrees;
   return_value += (double) ( (double) minutes / (double) 60.0 );
   return_value += (double) ( (double) fractional_minutes / (double) 60.0 );

   return( return_value );
}

double COORDINATE::GetDecimalMinutes( void ) const
{
   double return_value = 0.0;

   int degrees = (int) ::floor( Coordinate );
   int minutes = degrees % 100;

   double fractional_minutes = 0.0;
   double throw_away         = 0.0;

   fractional_minutes = ::modf( Coordinate, &throw_away );

   return_value  = (double) ( (double) minutes );
   return_value += fractional_minutes;

   return( return_value );
}

double COORDINATE::GetDecimalSeconds( void ) const
{
   double return_value = 0.0;

   double minutes = GetDecimalMinutes();

   double fractional_minutes = 0.0;
   double throw_away         = 0.0;

   fractional_minutes = ::modf( minutes, &throw_away );

   return_value = (double) ( (double) fractional_minutes * (double) 60.0 );

   return( return_value );
}

int COORDINATE::GetWholeDegrees( void ) const
{
   return( (int) ::floor( GetDecimalDegrees() ) );
}

int COORDINATE::GetWholeMinutes( void ) const
{
   return( (int) ::floor( GetDecimalMinutes() ) );
}

int COORDINATE::GetWholeSeconds( void ) const
{
   return( (int) ::floor( GetDecimalSeconds() ) );
}
