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
** A combination of WPL, GLL, ZDA and ZTG is recommended.
*/

#include "nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

WAYPOINT_LOCATION::WAYPOINT_LOCATION()
{
   Mnemonic.clear();
   Empty();
}

WAYPOINT_LOCATION::~WAYPOINT_LOCATION()
{
   Mnemonic.clear();
   Empty();
}

void WAYPOINT_LOCATION::Empty( void ) noexcept
{
   UTCTime.clear();
   Time = 0;
   Position.Empty();
   Waypoint.clear();
}

bool WAYPOINT_LOCATION::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** xxx - Waypoint location
   **
   **        1         2       3 4        5 6    7
   **        |         |       | |        | |    |
   ** $--xxx,hhmmss.ss,llll.ll,a,yyyyy.yy,a,c--c*hh<CR><LF>
   **
   ** Field Number: 
   **  1) UTC Time
   **  2) Latitude
   **  3) N or S (North or South)
   **  4) Longitude
   **  5) E or W (East or West)
   **  6) Waypoint name
   **  7) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == NMEA0183_BOOLEAN::True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   } 

   UTCTime  = sentence.Field( 1 );
   Time     = sentence.Time( 1 );
   Position.Parse( 2, 3, 4, 5, sentence );
   Waypoint = sentence.Field( 6 );

   return( true );
}

std::string WAYPOINT_LOCATION::PlainEnglish( void ) const noexcept
{
   std::string return_string( "At " );
   std::string time_string = ctime(&Time);
   return_string += time_string.substr(0, time_string.length() - 1);
   return_string += ", you were at waypoint ";
   return_string += Waypoint;
   return_string += " located at ";
   return_string += Position.PlainEnglish();
   return_string += ".";

   return( return_string );
}

bool WAYPOINT_LOCATION::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Position;
   sentence += Waypoint;

   sentence.Finish();

   return( true );
}

WAYPOINT_LOCATION const& WAYPOINT_LOCATION::operator = ( WAYPOINT_LOCATION const& source ) noexcept
{
   UTCTime  = source.UTCTime;
   Time     = source.Time;
   Position = source.Position;
   Waypoint = source.Waypoint;

   return( *this );
}
