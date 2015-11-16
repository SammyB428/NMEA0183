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

TRF::TRF()
{
   Mnemonic = "TRF";
   Empty();
}

TRF::~TRF()
{
   Mnemonic.clear();
   Empty();
}

void TRF::Empty( void )
{
   UTCTime.clear();
   Date.clear();
   Position.Empty();
   ElevationAngle              = 0.0;
   NumberOfIterations          = 0.0;
   NumberOfDopplerIntervals    = 0.0;
   UpdateDistanceNauticalMiles = 0.0;
   SatelliteID                 = 0;
   IsDataValid                 = NMEA_Unknown;
}

bool TRF::Parse( const SENTENCE& sentence )
{
   /*
   ** TRF - TRANSIT Fix Data
   **                                                                    13
   **        1         2      3       4 5        6 7   8   9   10  11  12|
   **        |         |      |       | |        | |   |   |   |   |   | |
   ** $--TRF,hhmmss.ss,xxxxxx,llll.ll,a,yyyyy.yy,a,x.x,x.x,x.x,x.x,xxx,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) UTC Time
   **  2) Date, ddmmyy
   **  3) Latitude
   **  4) N or S
   **  5) Longitude
   **  6) E or W
   **  7) Elevation Angle
   **  8) Number of iterations
   **  9) Number of Doppler intervals
   ** 10) Update distance, nautical miles
   ** 11) Satellite ID
   ** 12) Data Validity
   ** 13) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 13 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   } 

   UTCTime                     = sentence.Field( 1 );
   Time                        = sentence.Time( 1 );
   Date                        = sentence.Field( 2 );
   Position.Parse( 3, 4, 5, 6, sentence );
   ElevationAngle              = sentence.Double( 7 );
   NumberOfIterations          = sentence.Double( 8 );
   NumberOfDopplerIntervals    = sentence.Double( 9 );
   UpdateDistanceNauticalMiles = sentence.Double( 10 );
   SatelliteID                 = sentence.Integer( 11 );
   IsDataValid                 = sentence.Boolean( 12 );

   return( true );
}

bool TRF::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Date;
   sentence += Position;
   sentence += ElevationAngle;
   sentence += NumberOfIterations;
   sentence += NumberOfDopplerIntervals;
   sentence += UpdateDistanceNauticalMiles;
   sentence += SatelliteID;
   sentence += IsDataValid;

   sentence.Finish();

   return( true );
}

const TRF& TRF::operator = ( const TRF& source )
{
   UTCTime                     = source.UTCTime;
   Time                        = source.Time;
   Date                        = source.Date;
   Position                    = source.Position;
   ElevationAngle              = source.ElevationAngle;
   NumberOfIterations          = source.NumberOfIterations;
   NumberOfDopplerIntervals    = source.NumberOfDopplerIntervals;
   UpdateDistanceNauticalMiles = source.UpdateDistanceNauticalMiles;
   SatelliteID                 = source.SatelliteID;
   IsDataValid                 = source.IsDataValid;

  return( *this );
}
