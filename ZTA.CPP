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

/*
** This Sentence Not Recommended For New Designs
** ZTG is recommended.
*/

#include "nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

ZTA::ZTA()
{
   Mnemonic = "ZTA";
   Empty();
}

ZTA::~ZTA()
{
   Mnemonic.clear();
   Empty();
}

void ZTA::Empty( void ) noexcept
{
   UTCTimeString.clear();
   UTCTime = 0;
   ArrivalTimeString.clear();
   ArrivalTime = 0;
   To.clear();
}

bool ZTA::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** ZTA - Estimated Arrival time at point of interest
   **
   **        1         2         3    4
   **        |         |         |    |  
   ** $--ZTA,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
   **
   ** 1) Universal Time Coordinated (UTC)
   ** 2) Arrival Time
   ** 3) Waypoint ID (To)
   ** 4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 4 ) == NMEA0183_BOOLEAN::True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   }

   time_t temp_time = time(nullptr);

   auto tm_p = gmtime(&temp_time);

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

   ArrivalTimeString = sentence.Field( 2 );

   temp_number[ 0 ] = ArrivalTimeString[ 0 ];
   temp_number[ 1 ] = ArrivalTimeString[ 1 ];

   hours = ::atoi( temp_number );

   temp_number[ 0 ] = ArrivalTimeString[ 2 ];
   temp_number[ 1 ] = ArrivalTimeString[ 3 ];

   minutes = ::atoi( temp_number );

   temp_number[ 0 ] = ArrivalTimeString[ 4 ];
   temp_number[ 1 ] = ArrivalTimeString[ 5 ];

   seconds = ::atoi( temp_number );

   ArrivalTime = ctime( year, month, day, hours, minutes, seconds );

   To = sentence.Field( 3 );

   return( true );
}

bool ZTA::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTimeString;
   sentence += ArrivalTimeString;
   sentence += To;

   sentence.Finish();

   return( true );
}

ZTA const& ZTA::operator = ( ZTA const& source ) noexcept
{
   UTCTimeString     = source.UTCTimeString;
   UTCTime           = source.UTCTime;
   ArrivalTimeString = source.ArrivalTimeString;
   ArrivalTime       = source.ArrivalTime;
   To                = source.To;

   return( *this );
}
