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

void DCN::Empty( void ) noexcept
{
   DeccaChainID                     = 0;
   Red.Empty();
   Green.Empty();
   Purple.Empty();
   RedLineNavigationUse             = NMEA0183_BOOLEAN::NMEA_Unknown;
   GreenLineNavigationUse           = NMEA0183_BOOLEAN::NMEA_Unknown;
   PurpleLineNavigationUse          = NMEA0183_BOOLEAN::NMEA_Unknown;
   PositionUncertaintyNauticalMiles = 0.0;
   Basis                            = FIX_DATA_BASIS::BasisUnknown;
}

bool DCN::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** DCN - Decca Position
   **                                      11  13      16
   **        1  2  3   4 5  6   7 8  9   10| 12| 14  15| 17
   **        |  |  |   | |  |   | |  |   | | | | |   | | |
   ** $--DCN,xx,cc,x.x,A,cc,x.x,A,cc,x.x,A,A,A,A,x.x,N,x*hh<CR><LF>
   **
   **  1) Decca chain identifier
   **  2) Red Zone Identifier
   **  3) Red Line Of Position
   **  4) Red Master Line Status
   **  5) Green Zone Identifier
   **  6) Green Line Of Position
   **  7) Green Master Line Status
   **  8) Purple Zone Identifier
   **  9) Purple Line Of Position
   ** 10) Purple Master Line Status
   ** 11) Red Line Navigation Use
   ** 12) Green Line Navigation Use
   ** 13) Purple Line Navigation Use
   ** 14) Position Uncertainity
   ** 15) N = Nautical Miles
   ** 16) Fix Data Basis
   **     1 = Normal Pattern
   **     2 = Lane Identification Pattern
   **     3 = Lane Identification Transmissions
   ** 17) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 17 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   DeccaChainID                     = sentence.Integer( 1 );
   Red.Parse( 2, sentence );
   Green.Parse( 5, sentence );
   Purple.Parse( 8, sentence );
   RedLineNavigationUse             = sentence.Boolean( 11 );
   GreenLineNavigationUse           = sentence.Boolean( 12 );
   PurpleLineNavigationUse          = sentence.Boolean( 13 );
   PositionUncertaintyNauticalMiles = sentence.Double( 14 );

   auto const temp_integer = sentence.Integer( 16 );

   switch( temp_integer )
   {
      case 1:

         Basis = FIX_DATA_BASIS::NormalPatternBasis;
         break;

      case 2:

         Basis = FIX_DATA_BASIS::LaneIdentificationPatternBasis;
         break;

      case 3:

         Basis = FIX_DATA_BASIS::LaneIdentificationTransmissionsBasis;
         break;

      default:

         Basis = FIX_DATA_BASIS::BasisUnknown;
         break;
   }

   return( true );
}

bool DCN::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += DeccaChainID;
   Red.Write( sentence );
   Green.Write( sentence );
   Purple.Write( sentence );
   sentence += RedLineNavigationUse;
   sentence += GreenLineNavigationUse;
   sentence += PurpleLineNavigationUse;
   sentence += PositionUncertaintyNauticalMiles;
   sentence += STRING_VIEW("N");

   switch( Basis )
   {
   case FIX_DATA_BASIS::NormalPatternBasis:

         sentence += 1;
         break;

   case FIX_DATA_BASIS::LaneIdentificationPatternBasis:

         sentence += 2;
         break;

   case FIX_DATA_BASIS::LaneIdentificationTransmissionsBasis:

         sentence += 3;
         break;

      default:

         sentence += STRING_VIEW("");
         break;
   }

   sentence.Finish();

   return( true );
}

DCN const& DCN::operator = ( DCN const& source ) noexcept
{
   DeccaChainID                     = source.DeccaChainID;
   Red                              = source.Red;
   Green                            = source.Green;
   Purple                           = source.Purple;
   RedLineNavigationUse             = source.RedLineNavigationUse;
   GreenLineNavigationUse           = source.GreenLineNavigationUse;
   PurpleLineNavigationUse          = source.PurpleLineNavigationUse;
   PositionUncertaintyNauticalMiles = source.PositionUncertaintyNauticalMiles;
   Basis                            = source.Basis;

   return( *this );
}
