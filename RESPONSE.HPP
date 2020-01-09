#if ! defined( RESPONSE_CLASS_HEADER )

#define RESPONSE_CLASS_HEADER

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

class NMEA0183;

class RESPONSE
{
   private:

       NMEA0183 * container_p{ nullptr };

   public:

      inline RESPONSE(std::string_view id) noexcept : Mnemonic(id), DataSource(STRING_VIEW("--")) {}

      std::string const Mnemonic;

      /*
      ** Data
      */

      std::string DataSource;
      std::string ErrorMessage;
      std::string Talker;

      /*
      ** Methods
      */

      virtual void Empty( void ) noexcept = 0;
      virtual bool Parse( SENTENCE const& sentence ) noexcept = 0;
      virtual std::string PlainEnglish( void ) const noexcept;
      virtual void SetErrorMessage( std::string_view message ) noexcept;
      virtual void SetContainer( NMEA0183 * container ) noexcept;
      virtual bool Write( SENTENCE& sentence ) const noexcept;
};

class GENERIC_RESPONSE : public RESPONSE
{
public:

    inline GENERIC_RESPONSE(std::string_view id) noexcept : RESPONSE(id) {}
    void Empty(void) noexcept override {}
    bool Parse(SENTENCE const& ) noexcept override { return(true); }
    bool Write(SENTENCE& ) const noexcept override { return(true); }

};

#endif // RESPONSE_CLASS_HEADER
