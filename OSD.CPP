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

void OSD::Empty( void ) noexcept
{
   HeadingDegreesTrue       = 0.0;
   IsHeadingValid           = NMEA0183_BOOLEAN::NMEA_Unknown;
   VesselCourseDegreesTrue  = 0.0;
   VesselCourseReference    = REFERENCE::ReferenceUnknown;
   VesselSpeed              = 0.0;
   VesselSpeedReference     = REFERENCE::ReferenceUnknown;
   VesselSetDegreesTrue     = 0.0;
   VesselDriftSpeed         = 0.0;
   VesselDriftSpeedUnits.clear();
}

bool OSD::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** OSD - Own Ship Data
   **
   **        1   2 3   4 5   6 7   8   9 10
   **        |   | |   | |   | |   |   | |
   ** $--OSD,x.x,A,x.x,a,x.x,a,x.x,x.x,a*hh<CR><LF>
   **
   **  1) Heading, degrees true
   **  2) Status, A = Data Valid
   **  3) Vessel Course, degrees True
   **  4) Course Reference
   **  5) Vessel Speed
   **  6) Speed Reference
   **  7) Vessel Set, degrees True
   **  8) Vessel drift (speed)
   **  9) Speed Units
   ** 10) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 10 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   HeadingDegreesTrue       = sentence.Double( 1 );
   IsHeadingValid           = sentence.Boolean( 2 );
   VesselCourseDegreesTrue  = sentence.Double( 3 );
   VesselCourseReference    = sentence.Reference( 4 );
   VesselSpeed              = sentence.Double( 5 );
   VesselSpeedReference     = sentence.Reference( 6 );
   VesselSetDegreesTrue     = sentence.Double( 7 );
   VesselDriftSpeed         = sentence.Double( 8 );
   VesselDriftSpeedUnits    = sentence.Field( 9 );

   return( true );
}

bool OSD::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += HeadingDegreesTrue;
   sentence += IsHeadingValid;
   sentence += VesselCourseDegreesTrue;
   sentence += VesselCourseReference;
   sentence += VesselSpeed;
   sentence += VesselSpeedReference;
   sentence += VesselSetDegreesTrue;
   sentence += VesselDriftSpeed;
   sentence += VesselDriftSpeedUnits;

   sentence.Finish();

   return( true );
}

OSD const& OSD::operator = ( OSD const& source ) noexcept
{
   HeadingDegreesTrue      = source.HeadingDegreesTrue;
   IsHeadingValid          = source.IsHeadingValid;
   VesselCourseDegreesTrue = source.VesselCourseDegreesTrue;
   VesselCourseReference   = source.VesselCourseReference;
   VesselSpeed             = source.VesselSpeed;
   VesselSpeedReference    = source.VesselSpeedReference;
   VesselSetDegreesTrue    = source.VesselSetDegreesTrue;
   VesselDriftSpeed        = source.VesselDriftSpeed;
   VesselDriftSpeedUnits   = source.VesselDriftSpeedUnits;

   return( *this );
}
