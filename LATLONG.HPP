#if ! defined( LATLONG_CLASS_HEADER )

#define LATLONG_CLASS_HEADER

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

class SENTENCE;

class COORDINATE
{
   public:

      COORDINATE() { Coordinate = 0.0; }
     ~COORDINATE() { Coordinate = 0.0; }

      double Coordinate;

      double GetDecimalDegrees( void ) const;
      double GetDecimalMinutes( void ) const;
      double GetDecimalSeconds( void ) const;
      int    GetWholeDegrees( void ) const;
      int    GetWholeMinutes( void ) const;
      int    GetWholeSeconds( void ) const;
};

class LATITUDE : public COORDINATE
{
   public:

      LATITUDE();
      virtual ~LATITUDE();

      /*
      ** Data
      */

      double Latitude;

      NORTHSOUTH Northing;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool IsDataValid( void );
      virtual void Parse( int PositionFieldNumber, int NorthingFieldNumber, const SENTENCE& LineToParse );
      virtual void Set( double Position, const char *Northing );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LATITUDE& operator = ( const LATITUDE& source );
};

class LONGITUDE : public COORDINATE
{
   public:

      LONGITUDE();
      virtual ~LONGITUDE();

      /*
      ** Data
      */

      double Longitude;

      EASTWEST Easting;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool IsDataValid( void );
      virtual void Parse( int PositionFieldNumber, int EastingFieldNumber, const SENTENCE& LineToParse );
      virtual void Set( double Position, const char *Easting );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LONGITUDE& operator = ( const LONGITUDE& source );
};

class LATLONG
{
   public:

      LATLONG();
      virtual ~LATLONG();

      /*
      ** Data
      */

      LATITUDE  Latitude;
      LONGITUDE Longitude;

      /*
      ** Methods
      */
       
      virtual void Empty( void );
      virtual bool Parse( int LatitudePostionFieldNumber, int NorthingFieldNumber, int LongitudePositionFieldNumber, int EastingFieldNumber, const SENTENCE& LineToParse );
      virtual std::string PlainEnglish( void ) const;
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LATLONG& operator = ( const LATLONG& source );
};

#endif // LATLONG_CLASS_HEADER
