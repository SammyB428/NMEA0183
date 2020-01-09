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

void XTR::Empty( void ) noexcept
{
   Magnitude        = 0.0;
   DirectionToSteer = LEFTRIGHT::LR_Unknown;
}

bool XTR::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** XTR - Cross Track Error - Dead Reckoning
   **
   **        1   2 3 4
   **        |   | | |
   ** $--XTR,x.x,a,N*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Magnitude of cross track error
   **  2) Direction to steer, L or R
   **  3) Units, N = Nautical Miles
   **  4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 4 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   Magnitude        = sentence.Double( 1 );
   DirectionToSteer = sentence.LeftOrRight( 2 );

   return( true );
}

bool XTR::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Magnitude;
   sentence += DirectionToSteer;
   sentence += STRING_VIEW("N");

   sentence.Finish();

   return( true );
}

XTR const& XTR::operator = ( XTR const& source ) noexcept
{
   Magnitude        = source.Magnitude;
   DirectionToSteer = source.DirectionToSteer;

   return( *this );
}
