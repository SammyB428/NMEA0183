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

void GXA::Empty( void ) noexcept
{
   UTCTime.clear();
   Time = 0;
   Position.Empty();
   WaypointID.clear();
   SatelliteNumber = 0;
}

bool GXA::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** GXA - TRANSIT Position - Latitude/Longitude
   ** Location and time of TRANSIT fix at waypoint
   **
   **        1         2       3 4        5 6    7 8
   **        |         |       | |        | |    | |
   ** $--GXA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,c--c,X*hh<CR><LF>
   **
   ** 1) UTC of position fix
   ** 2) Latitude
   ** 3) East or West
   ** 4) Longitude
   ** 5) North or South
   ** 6) Waypoint ID
   ** 7) Satelite number
   ** 8) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 8 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   UTCTime         = sentence.Field( 1 );
   Time            = sentence.Time( 1 );
   Position.Parse( 2, 3, 4, 5, sentence );
   WaypointID      = sentence.Field( 6 );
   SatelliteNumber = static_cast<uint16_t>(sentence.Integer( 7 ));

   return( true );
}

bool GXA::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Position;
   sentence += WaypointID;
   sentence += Hex( SatelliteNumber ); // Thanks to Chuck Shannon, cshannon@imtn.tpd.dsccc.com

   sentence.Finish();

   return( true );
}

GXA const& GXA::operator = ( GXA const& source ) noexcept
{
   UTCTime         = source.UTCTime;
   Time            = source.Time;
   Position        = source.Position;
   WaypointID      = source.WaypointID;
   SatelliteNumber = source.SatelliteNumber;

   return( *this );
}
