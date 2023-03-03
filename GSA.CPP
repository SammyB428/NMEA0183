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

void GSA::Empty( void ) noexcept
{
   OperatingMode = OPERATING_MODE::UnknownOperatingMode;
   FixMode       = FIX_MODE::FixUnknown;

   for (auto& entry : SatelliteNumber)
   {
       entry = 0;
   }

   PDOP = 0.0;
   HDOP = 0.0;
   VDOP = 0.0;
}

bool GSA::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** GSA - GPS DOP and Active Satellites
   **
   **        1 2 3  4  5  6  7  8  9  10 11 12 13 14 15  16  17  18
   **        | | |  |  |  |  |  |  |  |  |  |  |  |  |   |   |   |
   ** $--GSA,a,x,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,x.x,x.x,x.x*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Operating Mode, A = Automatic, M = Manual
   **  2) Fix Mode, 1 = Fix not available, 2 = 2D, 3 = 3D
   **  3) Satellite PRN #1
   **  4) Satellite PRN #2
   **  5) Satellite PRN #3
   **  6) Satellite PRN #4
   **  7) Satellite PRN #5
   **  8) Satellite PRN #6
   **  9) Satellite PRN #7
   ** 10) Satellite PRN #8
   ** 11) Satellite PRN #9
   ** 12) Satellite PRN #10
   ** 13) Satellite PRN #11
   ** 14) Satellite PRN #12
   ** 15) PDOP
   ** 16) HDOP
   ** 17) VDOP
   ** 18) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 18 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   auto field_data = sentence.Field( 1 );

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'A')
       {
           OperatingMode = GSA::OPERATING_MODE::Automatic;
       }
       else if (field_data[0] == 'M')
       {
           OperatingMode = GSA::OPERATING_MODE::Manual;
       }
       else
       {
           OperatingMode = GSA::OPERATING_MODE::UnknownOperatingMode;
       }
   }
   else
   {
       OperatingMode = GSA::OPERATING_MODE::UnknownOperatingMode;
   }

   auto index = sentence.Integer( 2 );

   switch( index )
   {
      case 1:

         FixMode = GSA::FIX_MODE::FixUnavailable;
         break;

      case 2:

         FixMode = GSA::FIX_MODE::TwoDimensional;
         break;

      case 3:

         FixMode = GSA::FIX_MODE::ThreeDimensional;
         break;

      default:

         FixMode = GSA::FIX_MODE::FixUnknown;
         break;
   }

   index = 0;

   while( index < std::size(SatelliteNumber) )
   {
      SatelliteNumber[ index ] = sentence.Integer( static_cast<int>(index + 3) );
      index++;
   }

   PDOP = sentence.Double( 15 );
   HDOP = sentence.Double( 16 );
   VDOP = sentence.Double( 17 );

   return( true );
}

bool GSA::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   switch( OperatingMode )
   {
      case GSA::OPERATING_MODE::Manual:

         sentence += STRING_VIEW("M");
         break;

      case GSA::OPERATING_MODE::Automatic:

         sentence += STRING_VIEW("A");
         break;

      default:

         sentence += STRING_VIEW("");
         break;
   }

   switch( FixMode )
   {
      case GSA::FIX_MODE::FixUnavailable:

         sentence += STRING_VIEW("1");
         break;

      case GSA::FIX_MODE::TwoDimensional:

         sentence += STRING_VIEW("2");
         break;

      case GSA::FIX_MODE::ThreeDimensional:

         sentence += STRING_VIEW("3");
         break;

      default:

         sentence += STRING_VIEW("");
         break;
   }

   for (auto const& entry : SatelliteNumber)
   {
       if (entry not_eq 0)
       {
           sentence += entry;
       }
       else
       {
           sentence += STRING_VIEW("");
       }
   }

   sentence += PDOP;
   sentence += HDOP;
   sentence += VDOP;

   sentence.Finish();

   return( true );
}

GSA const& GSA::operator = ( GSA const& source ) noexcept
{
   OperatingMode = source.OperatingMode;
   FixMode       = source.FixMode;

   std::size_t index{ 0 };

   while( index < std::size(SatelliteNumber) )
   {
      SatelliteNumber[ index ] = source.SatelliteNumber[ index ];
      index++;
   }

   PDOP = source.PDOP;
   HDOP = source.HDOP;
   VDOP = source.VDOP;

   return( *this );
}
