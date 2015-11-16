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

RSD::RSD()
{
   Mnemonic = "RSD";
   Empty();
}

RSD::~RSD()
{
   Mnemonic.clear();
   Empty();
}

void RSD::Empty( void )
{
   Data1.Empty();
   Data2.Empty();
   CursorRangeFromOwnShip                = 0.0;
   CursorBearingDegreesClockwiseFromZero = 0.0;
   RangeScale                            = 0.0;
   RangeUnits.clear();
   DisplayRotation                       = RotationUnknown;
}

bool RSD::Parse( const SENTENCE& sentence )
{
   /*
   ** RSD - RADAR System Data
   **                                                        14
   **        1   2   3   4   5   6   7   8   9   10  11 12 13|
   **        |   |   |   |   |   |   |   |   |   |   |   | | |
   ** $--RSD,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,a,a*hh<CR><LF>
   **
   ** 14) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 14 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   } 

   Data1.Parse( 1, sentence );
   Data2.Parse( 5, sentence );
   CursorRangeFromOwnShip                = sentence.Double( 9 );
   CursorBearingDegreesClockwiseFromZero = sentence.Double( 10 );
   RangeScale                            = sentence.Double( 11 );
   RangeUnits                            = sentence.Field( 12 );

   int temp_integer = sentence.Integer( 13 );

   switch( temp_integer )
   {
      case 'C':

         DisplayRotation = CourseUpRotation;
         break;

      case 'H':

         DisplayRotation = HeadUpRotation;
         break;

      case 'N':

         DisplayRotation = NorthUpRotation;
         break;

      default:

         DisplayRotation = RotationUnknown;
         break;
   }

   return( true );
}

bool RSD::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   Data1.Write( sentence );
   Data2.Write( sentence );
   sentence += CursorRangeFromOwnShip;
   sentence += CursorBearingDegreesClockwiseFromZero;
   sentence += RangeScale;
   sentence += RangeUnits;

   switch( DisplayRotation )
   {
      case CourseUpRotation:

         sentence += "C";
         break;

      case HeadUpRotation:

         sentence += "H";
         break;

      case NorthUpRotation:

         sentence += "N";
         break;

      default:

         sentence += "";
         break;
   }

   sentence.Finish();

   return( true );
}

const RSD& RSD::operator = ( const RSD& source )
{
   Data1                                 = source.Data1;
   Data2                                 = source.Data2;
   CursorRangeFromOwnShip                = source.CursorRangeFromOwnShip;
   CursorBearingDegreesClockwiseFromZero = source.CursorBearingDegreesClockwiseFromZero;
   RangeScale                            = source.RangeScale;
   RangeUnits                            = source.RangeUnits;
   DisplayRotation                       = source.DisplayRotation;

   return( *this );
}
