#if ! defined( TTM_CLASS_HEADER )

#define TTM_CLASS_HEADER

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
   TargetUnknown = 0,
   TargetLost,
   TargetQuery,
   TargetTracking
}
TARGET_STATUS;

class TTM : public RESPONSE
{
   public:

      TTM();
      virtual ~TTM();

      /*
      ** Data
      */

      int           TargetNumber;
      double        TargetDistance;
      double        BearingFromOwnShip;
      std::string   BearingUnits;
      double        TargetSpeed;
      double        TargetCourse;
      std::string   TargetCourseUnits;
      double        DistanceOfClosestPointOfApproach;
      double        NumberOfMinutesToClosestPointOfApproach;
      std::string   Increasing;
      std::string   TargetName;
      TARGET_STATUS TargetStatus;
      std::string   ReferenceTarget;

      /*
      ** Methods
      */

      virtual void Empty( void ) override;
      virtual bool Parse( const SENTENCE& sentence ) override;
      virtual bool Write( SENTENCE& sentence ) override;

      /*
      ** Operators
      */

      virtual const TTM& operator = ( const TTM& source );
};

#endif // TTM_CLASS_HEADER
