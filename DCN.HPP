#if ! defined( DCN_CLASS_HEADER )

#define DCN_CLASS_HEADER

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

enum class FIX_DATA_BASIS
{
   BasisUnknown = 0,
   NormalPatternBasis,
   LaneIdentificationPatternBasis,
   LaneIdentificationTransmissionsBasis
};

class DCN : public RESPONSE
{
   public:

      inline DCN() noexcept : RESPONSE(STRING_VIEW("DCN")) {}

      /*
      ** Data
      */

      int              DeccaChainID{ 0 };
      LINE_OF_POSITION Red;
      LINE_OF_POSITION Green;
      LINE_OF_POSITION Purple;
      NMEA0183_BOOLEAN RedLineNavigationUse{ NMEA0183_BOOLEAN::NMEA_Unknown };
      NMEA0183_BOOLEAN GreenLineNavigationUse{ NMEA0183_BOOLEAN::NMEA_Unknown };
      NMEA0183_BOOLEAN PurpleLineNavigationUse{ NMEA0183_BOOLEAN::NMEA_Unknown };
      double           PositionUncertaintyNauticalMiles{ 0.0 };
      FIX_DATA_BASIS   Basis{ FIX_DATA_BASIS::BasisUnknown };

      /*
      ** Methods
      */

      void Empty( void ) noexcept override;
      bool Parse( SENTENCE const& sentence ) noexcept override;
      bool Write( SENTENCE& sentence ) const noexcept override;

      /*
      ** Operators
      */

      virtual DCN const& operator = ( DCN const& source ) noexcept;
};

#endif // DCN_CLASS_HEADER
