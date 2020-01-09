#if ! defined( TTM_CLASS_HEADER )

#define TTM_CLASS_HEADER

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

enum class TARGET_STATUS
{
   TargetUnknown = 0,
   TargetLost,
   TargetQuery,
   TargetTracking
};

class TTM : public RESPONSE
{
   public:

      inline TTM() noexcept : RESPONSE(STRING_VIEW("TTM")) {}

      /*
      ** Data
      */

      int           TargetNumber{ 0 };
      double        TargetDistance{ 0.0 };
      double        BearingFromOwnShip{ 0.0 };
      std::string   BearingUnits;
      double        TargetSpeed{ 0.0 };
      double        TargetCourse{ 0.0 };
      std::string   TargetCourseUnits;
      double        DistanceOfClosestPointOfApproach{ 0.0 };
      double        NumberOfMinutesToClosestPointOfApproach{ 0.0 };
      std::string   Increasing;
      std::string   TargetName;
      TARGET_STATUS TargetStatus{ TARGET_STATUS::TargetUnknown };
      std::string   ReferenceTarget;

      /*
      ** Methods
      */

      void Empty( void ) noexcept override;
      bool Parse( SENTENCE const& sentence ) noexcept override;
      bool Write( SENTENCE& sentence ) const noexcept override;

      /*
      ** Operators
      */

      virtual TTM const& operator = ( TTM const& source ) noexcept;
};

#endif // TTM_CLASS_HEADER
