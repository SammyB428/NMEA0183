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

ROT::ROT()
{
   Mnemonic = "ROT";
   Empty();
}

ROT::~ROT()
{
   Mnemonic.clear();
   Empty();
}

void ROT::Empty( void )
{
   RateOfTurn  = 0.0;
   IsDataValid = NMEA_Unknown;
}

bool ROT::Parse( const SENTENCE& sentence )
{
   /*
   ** ROT - Rate Of Turn
   **
   **        1   2 3
   **        |   | |
   ** $--ROT,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Rate Of Turn, degrees per minute, "-" means bow turns to port
   **  2) Status, A means data is valid
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

   RateOfTurn  = sentence.Double( 1 );
   IsDataValid = sentence.Boolean( 2 );

   return( true );
}

std::string ROT::PlainEnglish( void ) const
{
   std::string return_string;

   return_string = "The bow is turning to ";

   char temp_string[ 80 ];

   if ( RateOfTurn < 0 )
   {
      ::sprintf( temp_string, "Port at a rate of %4.1lf degrees per minute.", (double) (RateOfTurn * -1.0) );
   }
   else
   {
      ::sprintf( temp_string, "Starboard at a rate of %4.1lf degrees per minute.", RateOfTurn );
   }

   return_string += temp_string;

   if ( IsDataValid != True )
   {
      if ( IsDataValid == False )
      {
         return_string += " However, this data is not valid.";
      }
      else
      {
         return_string += " However, this data cannot be confirmed.";
      }
   }

   return( return_string );
}

bool ROT::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += RateOfTurn;
   sentence += IsDataValid;
   
   sentence.Finish();

   return( true );
}

const ROT& ROT::operator = ( const ROT& source )
{
   RateOfTurn  = source.RateOfTurn;
   IsDataValid = source.IsDataValid;

   return( *this );
}
