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

void TTM::Empty( void ) noexcept
{
   TargetNumber                            = 0;
   TargetDistance                          = 0.0;
   BearingFromOwnShip                      = 0.0;
   BearingUnits.clear();
   TargetSpeed                             = 0.0;
   TargetCourse                            = 0.0;
   TargetCourseUnits.clear();
   DistanceOfClosestPointOfApproach        = 0.0;
   NumberOfMinutesToClosestPointOfApproach = 0.0;
   Increasing.clear();
   TargetName.clear();
   TargetStatus                            = TARGET_STATUS::TargetUnknown;
}

bool TTM::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** TTM - Tracked Target Message
   **
   **                                         11     13
   **        1  2   3   4 5   6   7 8   9   10|    12| 14
   **        |  |   |   | |   |   | |   |   | |    | | |
   ** $--TTM,xx,x.x,x.x,a,x.x,x.x,a,x.x,x.x,a,c--c,a,a*hh<CR><LF>
   **
   **  1) Target Number
   **  2) Target Distance
   **  3) Bearing from own ship
   **  4) Bearing Units
   **  5) Target speed
   **  6) Target Course
   **  7) Course Units
   **  8) Distance of closest-point-of-approach
   **  9) Time until closest-point-of-approach "-" means increasing
   ** 10) "-" means increasing
   ** 11) Target name
   ** 12) Target Status
   ** 13) Reference Target
   ** 14) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 14 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   TargetNumber                            = sentence.Integer( 1 );
   TargetDistance                          = sentence.Double( 2 );
   BearingFromOwnShip                      = sentence.Double( 3 );
   BearingUnits                            = sentence.Field( 4 );
   TargetSpeed                             = sentence.Double( 5 );
   TargetCourse                            = sentence.Double( 6 );
   TargetCourseUnits                       = sentence.Field( 7 );
   DistanceOfClosestPointOfApproach        = sentence.Double( 8 );
   NumberOfMinutesToClosestPointOfApproach = sentence.Double( 9 );
   Increasing                              = sentence.Field( 10 );
   TargetName                              = sentence.Field( 11 );

   auto field_data{ sentence.Field(12) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'L')
       {
           TargetStatus = TARGET_STATUS::TargetLost;
       }
       else if (field_data[0] == 'Q')
       {
           TargetStatus = TARGET_STATUS::TargetQuery;
       }
       else if (field_data[0] == 'T')
       {
           TargetStatus = TARGET_STATUS::TargetTracking;
       }
       else
       {
           TargetStatus = TARGET_STATUS::TargetUnknown;
       }
   }
   else
   {
       TargetStatus = TARGET_STATUS::TargetUnknown;
   }

   ReferenceTarget = sentence.Field( 13 );

   return( true );
}

bool TTM::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += TargetNumber;
   sentence += TargetDistance;
   sentence += BearingFromOwnShip;
   sentence += BearingUnits;
   sentence += TargetSpeed;
   sentence += TargetCourse;
   sentence += TargetCourseUnits;
   sentence += DistanceOfClosestPointOfApproach;
   sentence += NumberOfMinutesToClosestPointOfApproach;
   sentence += Increasing;
   sentence += TargetName;
   
   switch( TargetStatus )
   {
   case TARGET_STATUS::TargetLost:

         sentence += STRING_VIEW("L");
         break;

   case TARGET_STATUS::TargetQuery:

         sentence += STRING_VIEW("Q");
         break;

   case TARGET_STATUS::TargetTracking:

         sentence += STRING_VIEW("T");
         break;

      default:

         sentence += STRING_VIEW("");
         break;
   }

   sentence += ReferenceTarget;

   sentence.Finish();

   return( true );
}

TTM const& TTM::operator = ( TTM const& source ) noexcept
{
   TargetNumber                            = source.TargetNumber;
   TargetDistance                          = source.TargetDistance;
   BearingFromOwnShip                      = source.BearingFromOwnShip;
   BearingUnits                            = source.BearingUnits;
   TargetSpeed                             = source.TargetSpeed;
   TargetCourse                            = source.TargetCourse;
   TargetCourseUnits                       = source.TargetCourseUnits;
   DistanceOfClosestPointOfApproach        = source.DistanceOfClosestPointOfApproach;
   NumberOfMinutesToClosestPointOfApproach = source.NumberOfMinutesToClosestPointOfApproach;
   Increasing                              = source.Increasing;
   TargetName                              = source.TargetName;
   TargetStatus                            = source.TargetStatus;

   return( *this );
}
