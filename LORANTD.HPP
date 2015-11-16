#if ! defined( LORAN_TIME_DIFFERENCE_CLASS_HEADER )

#define LORAN_TIME_DIFFERENCE_CLASS_HEADER

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

typedef enum
{
   LoranUnknown = 0,
   LoranValid,
   LoranBlinkWarning,
   LoranCycleWarning,
   LoranSignalToNoiseRatioWarning
}
LORAN_SIGNAL_STATUS;

class LORAN_TIME_DIFFERENCE
{
   public:

      LORAN_TIME_DIFFERENCE();
      virtual ~LORAN_TIME_DIFFERENCE();

      /*
      ** Data
      */

      double              Microseconds;
      LORAN_SIGNAL_STATUS SignalStatus;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual void Parse( int field_number, const SENTENCE& sentence );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LORAN_TIME_DIFFERENCE& LORAN_TIME_DIFFERENCE::operator = ( const LORAN_TIME_DIFFERENCE& source );
};

#endif // LORAN_TIME_DIFFERENCE_CLASS_HEADER
