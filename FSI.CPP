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

void FSI::Empty( void ) noexcept
{
   TransmittingFrequency = 0.0;
   ReceivingFrequency    = 0.0;
   Mode                  = COMMUNICATIONS_MODE::CommunicationsModeUnknown;
   PowerLevel            = 0;
}

bool FSI::Parse( SENTENCE const& sentence ) noexcept
{
   /*
   ** FSI - Frequency Set Information
   **
   **        1      2      3 4 5
   **        |      |      | | |
   ** $--FSI,xxxxxx,xxxxxx,c,x*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Transmitting Frequency
   **  2) Receiving Frequency
   **  3) Communications Mode
   **  4) Power Level
   **  5) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 5 ) == NMEA0183_BOOLEAN::True )
   {
       SetErrorMessage(STRING_VIEW("Invalid Checksum"));
       return( false );
   } 

   TransmittingFrequency = sentence.Double( 1 );
   ReceivingFrequency    = sentence.Double( 2 );
   Mode                  = sentence.CommunicationsMode( 3 );
   PowerLevel            = static_cast<uint16_t>(sentence.Integer( 4 ));

   return( true );
}

bool FSI::Write( SENTENCE& sentence ) const noexcept
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += TransmittingFrequency;
   sentence += ReceivingFrequency;
   sentence += Mode;
   sentence += PowerLevel;

   sentence.Finish();

   return( true );
}

FSI const& FSI::operator = ( FSI const& source ) noexcept
{
   TransmittingFrequency = source.TransmittingFrequency;
   ReceivingFrequency    = source.ReceivingFrequency;
   Mode                  = source.Mode;
   PowerLevel            = source.PowerLevel;

   return( *this );
}
