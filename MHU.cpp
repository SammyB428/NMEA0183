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

/*
** This Sentence Not Recommended For New Designs
** XDR is recommended.
*/

#include "nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

MHU::MHU()
{
   Mnemonic = "MHU";
   Empty();
}

MHU::~MHU()
{
   Mnemonic.clear();
   Empty();
}

void MHU::Empty( void )
{
   RelativeHumidityPercent = 0.0;
   AbsoluteHumidityPercent = 0.0;
   DewPointDegreesCelcius  = 0.0;
}

bool MHU::Parse( const SENTENCE& sentence )
{
   /*
   ** MHU - Humidity
   **
   **        1   2   3   4 5
   **        |   |   |   | |
   ** $--MHU,x.x,x.x,x.x,C*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Relative Humidity Percent
   **  2) Absolute humidity percent
   **  3) Dew Point
   **  4) C = Degrees Celsius
   **  5) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 5 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   } 

   RelativeHumidityPercent = sentence.Double( 1 );
   AbsoluteHumidityPercent = sentence.Double( 2 );
   DewPointDegreesCelcius  = sentence.Double( 3 );

   return( false );
}

bool MHU::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += RelativeHumidityPercent;
   sentence += AbsoluteHumidityPercent;
   sentence += DewPointDegreesCelcius;
   sentence += "C";

   sentence.Finish();

   return( true );
}

const MHU& MHU::operator = ( const MHU& source )
{
   RelativeHumidityPercent  = source.RelativeHumidityPercent;
   AbsoluteHumidityPercent  = source.AbsoluteHumidityPercent;
   DewPointDegreesCelcius   = source.DewPointDegreesCelcius;

   return( *this );
}
