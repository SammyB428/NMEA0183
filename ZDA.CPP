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

#include "nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

ZDA::ZDA()
{
   Mnemonic = "ZDA";
   Empty();
}

ZDA::~ZDA()
{
   Mnemonic.clear();
   Empty();
}

void ZDA::Empty( void ) noexcept
{
   UTCTime.clear();
   Time                  = 0;
   Day                   = 0;
   Month                 = 0;
   Year                  = 0;
   LocalHourDeviation    = 0;
   LocalMinutesDeviation = 0;
}

bool ZDA::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** ZDA - Time & Date
   ** UTC, day, month, year and local time zone
   **
   ** $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh<CR><LF>
   **        |         |  |  |    |  |
   **        |         |  |  |    |  +- Local zone minutes description, same sign as local hours
   **        |         |  |  |    +- Local zone description, 00 to +- 13 hours
   **        |         |  |  +- Year
   **        |         |  +- Month, 01 to 12
   **        |         +- Day, 01 to 31
   **        +- Universal Time Coordinated (UTC)
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == NMEA0183_BOOLEAN::True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   } 

   UTCTime = sentence.Field( 1 );

   char temp_number[ 3 ];

   temp_number[ 2 ] = 0x00;

   temp_number[ 0 ] = UTCTime[ 0 ];
   temp_number[ 1 ] = UTCTime[ 1 ];

   int hours = ::atoi( temp_number );

   temp_number[ 0 ] = UTCTime[ 2 ];
   temp_number[ 1 ] = UTCTime[ 3 ];

   int minutes = ::atoi( temp_number );

   temp_number[ 0 ] = UTCTime[ 4 ];
   temp_number[ 1 ] = UTCTime[ 5 ];

   int seconds = ::atoi( temp_number );

   Day                   = sentence.Integer( 2 );
   Month                 = sentence.Integer( 3 );
   Year                  = sentence.Integer( 4 );
   LocalHourDeviation    = sentence.Integer( 5 );
   LocalMinutesDeviation = sentence.Integer( 6 );

   Time = ctime( Year, Month, Day, hours, minutes, seconds );

   return( true );
}

bool ZDA::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Day;
   sentence += Month;
   sentence += Year;
   sentence += LocalHourDeviation;
   sentence += LocalMinutesDeviation;

   sentence.Finish();

   return( true );
}

ZDA const& ZDA::operator = ( ZDA const& source ) noexcept
{
   UTCTime               = source.UTCTime;
   Time                  = source.Time;
   Day                   = source.Day;
   Month                 = source.Month;
   Year                  = source.Year;
   LocalHourDeviation    = source.LocalHourDeviation;
   LocalMinutesDeviation = source.LocalMinutesDeviation;

   return( *this );
}
