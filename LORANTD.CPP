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

LORAN_TIME_DIFFERENCE::LORAN_TIME_DIFFERENCE()
{
   Empty();
}

LORAN_TIME_DIFFERENCE::~LORAN_TIME_DIFFERENCE()
{
   Empty();
}

void LORAN_TIME_DIFFERENCE::Empty( void )
{
   Microseconds = 0.0;
   SignalStatus = LoranUnknown;
}

void LORAN_TIME_DIFFERENCE::Parse( int first_field_number, const SENTENCE& sentence )
{
   Microseconds = sentence.Double( first_field_number );

   std::string field_data = sentence.Field( first_field_number + 1 );

   if ( field_data == "B" )
   {
      SignalStatus = LoranBlinkWarning;   
   }
   else if ( field_data == "C" )
   {
      SignalStatus = LoranCycleWarning;
   }
   else if ( field_data == "S" )
   {
      SignalStatus = LoranSignalToNoiseRatioWarning;
   }
   else if ( field_data == "A" )
   {
      SignalStatus = LoranValid;
   }
   else
   {
      SignalStatus = LoranUnknown;
   }
}

void LORAN_TIME_DIFFERENCE::Write( SENTENCE& sentence )
{
   sentence += Microseconds;

   switch( SignalStatus )
   {
      case LoranValid:
      
         sentence += "A";
         break; 

      case LoranBlinkWarning:
      
         sentence += "B";
         break; 

      case LoranCycleWarning:
      
         sentence += "C";
         break; 

      case LoranSignalToNoiseRatioWarning:
      
         sentence += "S";
         break; 

      default:

         sentence += "";
   }
}

const LORAN_TIME_DIFFERENCE& LORAN_TIME_DIFFERENCE::operator = ( const LORAN_TIME_DIFFERENCE& source )
{
   Microseconds = source.Microseconds;
   SignalStatus = source.SignalStatus;

   return( *this );
}
