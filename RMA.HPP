#if ! defined( RMA_CLASS_HEADER )

#define RMA_CLASS_HEADER

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

class RMA : public RESPONSE
{
   public:

      inline RMA() noexcept : RESPONSE(STRING_VIEW("RMA")) {}

      /*
      ** Data
      */

      NMEA0183_BOOLEAN IsDataValid{ NMEA0183_BOOLEAN::NMEA_Unknown };
      LATLONG          Position;
      double           TimeDifferenceA{ 0.0 };
      double           TimeDifferenceB{ 0.0 };
      double           SpeedOverGroundKnots{ 0.0 };
      double           TrackMadeGoodDegreesTrue{ 0.0 };
      double           MagneticVariation{ 0.0 };
      EASTWEST         MagneticVariationDirection{ EASTWEST::EW_Unknown };

      /*
      ** Methods
      */

      void Empty( void ) noexcept override;
      bool Parse( SENTENCE const& sentence ) noexcept override;
      bool Write( SENTENCE& sentence ) const noexcept override;

      /*
      ** Operators
      */

      virtual RMA const& operator = ( RMA const& source ) noexcept;
};

#endif // RMA_CLASS_HEADER
