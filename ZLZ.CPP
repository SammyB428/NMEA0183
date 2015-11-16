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
** ZDA is recommended.
*/

#include "nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

ZLZ::ZLZ()
{
   Mnemonic = "ZLZ";
   Empty();
}

ZLZ::~ZLZ()
{
   Mnemonic.clear();
   Empty();
}

void ZLZ::Empty( void )
{
   UTCTimeString.clear();
   LocalTimeString.clear();
   LocalHourDeviation = 0;
}

bool ZLZ::Parse( const SENTENCE& sentence )
{
   /*
   ** ZLZ - Time of Day
   ** UTC, local time, zone
   **
   **        1         2         3  4
   **        |         |         |  |  
   ** $--ZLZ,hhmmss.ss,hhmmss.ss,xx*hh<CR><LF>
   **
   ** 1) Universal Time Coordinated (UTC)
   ** 2) Local Time
   ** 3) Local Zone Description, number of whole hours added to local time to obtain GMT
   ** 4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 4 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   }

   time_t temp_time = time(nullptr);

   struct tm * tm_p = gmtime(&temp_time);

   int year = tm_p->tm_year + 1900;
   int month = tm_p->tm_mon;
   int day = tm_p->tm_mday;

   UTCTimeString = sentence.Field( 1 );

   char temp_number[ 3 ];

   temp_number[ 2 ] = 0x00;

   temp_number[ 0 ] = UTCTimeString[ 0 ];
   temp_number[ 1 ] = UTCTimeString[ 1 ];

   int hours = ::atoi( temp_number );

   temp_number[ 0 ] = UTCTimeString[ 2 ];
   temp_number[ 1 ] = UTCTimeString[ 3 ];

   int minutes = ::atoi( temp_number );

   temp_number[ 0 ] = UTCTimeString[ 4 ];
   temp_number[ 1 ] = UTCTimeString[ 5 ];

   int seconds = ::atoi( temp_number );

   UTCTime = ctime( year, month, day, hours, minutes, seconds );

   LocalTimeString = sentence.Field( 2 );

   temp_number[ 0 ] = LocalTimeString[ 0 ];
   temp_number[ 1 ] = LocalTimeString[ 1 ];

   hours = ::atoi( temp_number );

   temp_number[ 0 ] = LocalTimeString[ 2 ];
   temp_number[ 1 ] = LocalTimeString[ 3 ];

   minutes = ::atoi( temp_number );

   temp_number[ 0 ] = LocalTimeString[ 4 ];
   temp_number[ 1 ] = LocalTimeString[ 5 ];

   seconds = ::atoi( temp_number );

   LocalTime = ctime( year, month, day, hours, minutes, seconds );

   LocalHourDeviation = sentence.Integer( 3 );

   return( true );
}

bool ZLZ::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTimeString;
   sentence += LocalTimeString;
   sentence += LocalHourDeviation;

   sentence.Finish();

   return( true );
}

const ZLZ& ZLZ::operator = ( const ZLZ& source )
{
   UTCTimeString      = source.UTCTimeString;
   UTCTime            = source.UTCTime;
   LocalTimeString    = source.LocalTimeString;
   LocalTime          = source.LocalTime;
   LocalHourDeviation = source.LocalHourDeviation;

   return( *this );
}
