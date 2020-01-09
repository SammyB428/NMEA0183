#if ! defined( RADAR_DATA_CLASS_HEADER )

#define RADAR_DATA_CLASS_HEADER

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

/* SPDX-License-Identifier: MIT */

class RADAR_DATA
{
   public:

      inline RADAR_DATA() noexcept {};

      /*
      ** Data
      */

      double OriginRangeFromOwnShip{ 0.0 };
      double OriginBearingDegreesFromZero{ 0.0 };
      double VariableRangeMarkerRange{ 0.0 };
      double BearingLineDegreesFromZero{ 0.0 };

      /*
      ** Methods
      */

      virtual void Empty( void ) noexcept;
      virtual void Parse( int field_number, SENTENCE const& sentence ) noexcept;
      virtual void Write( SENTENCE& sentence ) const noexcept;

      /*
      ** Operators
      */

      virtual RADAR_DATA const& operator = ( RADAR_DATA const& source ) noexcept;
};

#endif // RADAR_DATA_CLASS_HEADER
