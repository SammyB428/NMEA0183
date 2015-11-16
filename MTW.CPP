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

#include "nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

MTW::MTW()
{
   Mnemonic = "MTW";
   Empty();
}

MTW::~MTW()
{
   Mnemonic.clear();
   Empty();
}

void MTW::Empty( void )
{
   Temperature = 0.0;
   UnitOfMeasurement.clear();
}

bool MTW::Parse( const SENTENCE& sentence )
{
   /*
   ** MTW - Water Temperature
   **
   **        1   2 3
   **        |   | | 
   ** $--MTW,x.x,C*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Degrees
   **  2) Unit of Measurement, Celcius
   **  3) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 3 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( false );
   } 

   Temperature       = sentence.Double( 1 );
   UnitOfMeasurement = sentence.Field( 2 );

   return( true );
}

std::string MTW::PlainEnglish( void ) const
{
   std::string return_string("The water temperature is ");
    
   char temp_string[65];

   sprintf( temp_string, "%3.1lf ", Temperature );

   return_string += temp_string;
   return_string += UnitOfMeasurement;
   return_string += ".";

   return( return_string );
}

bool MTW::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Temperature;
   sentence += UnitOfMeasurement;

   sentence.Finish();

   return( true );
}

const MTW& MTW::operator = ( const MTW& source )
{
   Temperature       = source.Temperature;
   UnitOfMeasurement = source.UnitOfMeasurement;

   return( *this );
}
