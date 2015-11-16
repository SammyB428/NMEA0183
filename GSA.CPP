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

GSA::GSA()
{
   Mnemonic = "GSA";
   Empty();
}

GSA::~GSA()
{
   Mnemonic.clear();
   Empty();
}

void GSA::Empty( void )
{
   OperatingMode = UnknownOperatingMode;
   FixMode       = FixUnknown;

   int index = 0;

   while( index < 12 )
   {
      SatelliteNumber[ index ] = 0;
      index++;
   }

   PDOP = 0.0;
   HDOP = 0.0;
   VDOP = 0.0;
}

bool GSA::Parse( const SENTENCE& sentence )
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

   if ( sentence.IsChecksumBad( 18 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   } 

   std::string field_data = sentence.Field( 1 );

   if ( field_data == "A" )
   {
      OperatingMode = Automatic;
   }
   else if ( field_data == "M" )
   {
      OperatingMode = Manual;
   }
   else
   {
      OperatingMode = UnknownOperatingMode;
   }

   int index = sentence.Integer( 2 );

   switch( index )
   {
      case 1:

         FixMode = FixUnavailable;
         break;

      case 2:

         FixMode = TwoDimensional;
         break;

      case 3:

         FixMode = ThreeDimensional;
         break;

      default:

         FixMode = FixUnknown;
         break;
   }

   index = 0;

   while( index < 12 )
   {
      SatelliteNumber[ index ] = sentence.Integer( index + 3 );
      index++;
   }

   PDOP = sentence.Double( 15 );
   HDOP = sentence.Double( 16 );
   VDOP = sentence.Double( 17 );

   return( true );
}

bool GSA::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   switch( OperatingMode )
   {
      case Manual:

         sentence += "M";
         break;

      case Automatic:

         sentence += "A";
         break;

      default:

         sentence += "";
         break;
   }

   switch( FixMode )
   {
      case FixUnavailable:

         sentence += "1";
         break;

      case TwoDimensional:

         sentence += "2";
         break;

      case ThreeDimensional:

         sentence += "3";
         break;

      default:

         sentence += "";
         break;
   }

   int index = 0;

   while( index < 12 )
   {
      if ( SatelliteNumber[ index ] != 0 )
      {
         sentence += SatelliteNumber[ index ];
      }
      else
      {
         sentence += "";
      }

      index++;
   }

   sentence += PDOP;
   sentence += HDOP;
   sentence += VDOP;

   sentence.Finish();

   return( true );
}

const GSA& GSA::operator = ( const GSA& source )
{
   OperatingMode = source.OperatingMode;
   FixMode       = source.FixMode;

   int index = 0;

   while( index < 12 )
   {
      SatelliteNumber[ index ] = source.SatelliteNumber[ index ];
      index++;
   }

   PDOP = source.PDOP;
   HDOP = source.HDOP;
   VDOP = source.VDOP;

   return( *this );
}
