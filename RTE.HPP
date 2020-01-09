#if ! defined( RTE_CLASS_HEADER )

#define RTE_CLASS_HEADER

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

class RTE : public RESPONSE
{
   private:

       double m_TotalNumberOfMessages{ 0.0 };
       double m_LastMessageNumberReceived{ 0.0 };
       double m_MessageNumber{ 0.0 };

       int m_LastWaypointNumberWritten{ 0 };

   public:

      inline RTE() noexcept : RESPONSE(STRING_VIEW("RTE")) {}

      enum class ROUTE_TYPE
      {
          RouteUnknown = 0,
          CompleteRoute,
          WorkingRoute
      };

      ROUTE_TYPE  TypeOfRoute{ RTE::ROUTE_TYPE::RouteUnknown };
      std::string RouteName;
      std::vector<std::string> Waypoints;

      void Empty( void ) noexcept override;
      bool Parse( SENTENCE const& sentence ) noexcept override;
      bool Write( SENTENCE& sentence ) const noexcept override;
};

#endif // RTE_CLASS_HEADER
