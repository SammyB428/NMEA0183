#if ! defined( SENTENCE_CLASS_HEADER )

#define SENTENCE_CLASS_HEADER

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

class LATLONG;

class SENTENCE
{
   public:

      inline SENTENCE() noexcept {};

      /*
      ** Data
      */

      std::string Sentence;

      /*
      ** Methods
      */

      virtual NMEA0183_BOOLEAN Boolean( int field_number ) const noexcept;
      virtual uint8_t ComputeChecksum( void ) const noexcept;
      virtual COMMUNICATIONS_MODE CommunicationsMode( int field_number ) const noexcept;
      virtual double Double( int field_number ) const noexcept;
      virtual EASTWEST EastOrWest( int field_number ) const noexcept;
      virtual std::string_view Field( int field_number ) const noexcept;
      virtual void Finish( void ) noexcept;
      virtual uint16_t GetNumberOfDataFields( void ) const noexcept;
      virtual int Integer( int field_number ) const noexcept;
      virtual NMEA0183_BOOLEAN IsChecksumBad( int checksum_field_number ) const noexcept;
      virtual LEFTRIGHT LeftOrRight( int field_number ) const noexcept;
      virtual NORTHSOUTH NorthOrSouth( int field_number ) const noexcept;
      virtual REFERENCE Reference( int field_number ) const noexcept;
      virtual time_t Time( int field_number ) const noexcept;
      virtual TRANSDUCER_TYPE TransducerType( int field_number ) const noexcept;
      virtual FAA_MODE FAAMode(int field_number) const noexcept;

      /*
      ** Operators
      */

      operator std::string() const noexcept;
      operator std::string_view() const noexcept;
      virtual SENTENCE const& operator  = ( SENTENCE const& source ) noexcept;
      virtual SENTENCE const& operator  = ( std::string_view source ) noexcept;
      virtual SENTENCE const& operator += ( std::string_view source ) noexcept;
      virtual SENTENCE const& operator += ( double const value ) noexcept;
      virtual SENTENCE const& operator += ( int const value ) noexcept;
      virtual SENTENCE const& operator += ( COMMUNICATIONS_MODE const mode ) noexcept;
      virtual SENTENCE const& operator += ( EASTWEST const easting ) noexcept;
      virtual SENTENCE const& operator += ( LATLONG const& source ) noexcept;
      virtual SENTENCE const& operator += ( NMEA0183_BOOLEAN const boolean ) noexcept;
      virtual SENTENCE const& operator += ( NORTHSOUTH const northing ) noexcept;
      virtual SENTENCE const& operator += ( time_t const time ) noexcept;
      virtual SENTENCE const& operator += ( TRANSDUCER_TYPE const transducer ) noexcept;
      virtual SENTENCE const& operator += ( LEFTRIGHT const left_or_right ) noexcept;
      virtual SENTENCE const& operator += ( REFERENCE const a_reference ) noexcept;
};

#endif // SENTENCE_CLASS_HEADER
