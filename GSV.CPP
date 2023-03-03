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

void GSV::Empty( void ) noexcept
{
   NumberOfSatellites = 0;

   for (auto& entry : SatellitesInView)
   {
       entry.Empty();
   }
}

bool GSV::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** GSV - TRANSIT Position - Latitude/Longitude
   ** Location and time of TRANSIT fix at waypoint
   **
   **        1 2 3  4  5  6   7  8  9  10  11 12 13 14  15 16 17 18  19  20
   **        | | |  |  |  |   |  |  |  |   |  |  |  |   |  |  |  |   |   |
   ** $--GSV,x,x,xx,xx,xx,xxx,xx,xx,xx,xxx,xx,xx,xx,xxx,xx,xx,xx,xxx,xx,*hh<CR><LF>
   **
   **  1) Total number of messages, 1-3
   **  2) Message Number, 1-3
   **  3) Total number of satellites in view
   **  4) Satellite Number #1
   **  5) Elevation #1
   **  6) Azimuth, Degrees True #1
   **  7) SNR #1, NULL when not tracking
   **  8) Satellite Number #2
   **  9) Elevation #2
   ** 10) Azimuth, Degrees True #2
   ** 11) SNR #2, NULL when not tracking
   ** 12) Satellite Number #3
   ** 13) Elevation #3
   ** 14) Azimuth, Degrees True #3
   ** 15) SNR #3, NULL when not tracking
   ** 16) Satellite Number #4
   ** 17) Elevation #4
   ** 18) Azimuth, Degrees True #4
   ** 19) SNR #4, NULL when not tracking
   ** 20) Checksum
   */  

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 20 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   }

   auto const message_number{ sentence.Integer(2) };

   NumberOfSatellites = sentence.Integer( 3 );

   int index{ 0 };

   while( index < 4 )
   {
      auto const array_index = ((message_number - 1) * 4) + index;

      if (array_index < std::size(SatellitesInView))
      {
          SatellitesInView[array_index].Parse((index * 4) + 4, sentence);
      }

      index++;
   }

   return( true );
}

bool GSV::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   /*
   ** OK, this is a hack, I'll figure out how to do multiple messages later
   */

   sentence.Finish();

   return( true );
}

GSV const& GSV::operator = ( GSV const& source ) noexcept
{
   NumberOfSatellites = source.NumberOfSatellites;

   std::size_t index{ 0 };

   while( index < std::size(SatellitesInView) )
   {
      SatellitesInView[ index ] = source.SatellitesInView[ index ];
      index++;
   }

   return( *this );
}
