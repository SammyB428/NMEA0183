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

#include "nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

SENTENCE::SENTENCE()
{
   Sentence.clear();
}

SENTENCE::~SENTENCE()
{
   Sentence.clear();
}

NMEA0183_BOOLEAN SENTENCE::Boolean( int field_number ) const noexcept
{
   std::string const field_data = Field( field_number );

   if ( field_data == "A" )
   {
      return(NMEA0183_BOOLEAN::True );
   }
   else if ( field_data == "V" )
   {
      return(NMEA0183_BOOLEAN::False );
   }
   else
   {
      return(NMEA0183_BOOLEAN::NMEA_Unknown );
   }
}

COMMUNICATIONS_MODE SENTENCE::CommunicationsMode( int field_number ) const noexcept
{
   std::string const field_data = Field( field_number );

   if ( field_data == "d" )
   {
      return(COMMUNICATIONS_MODE::F3E_G3E_SimplexTelephone );
   }
   else if ( field_data == "e" )
   {
      return(COMMUNICATIONS_MODE::F3E_G3E_DuplexTelephone );
   }
   else if ( field_data == "m" )
   {
      return(COMMUNICATIONS_MODE::J3E_Telephone );
   }
   else if ( field_data == "o" )
   {
      return(COMMUNICATIONS_MODE::H3E_Telephone );
   }
   else if ( field_data == "q" )
   {
      return(COMMUNICATIONS_MODE::F1B_J2B_FEC_NBDP_TelexTeleprinter );
   }
   else if ( field_data == "s" )
   {
      return(COMMUNICATIONS_MODE::F1B_J2B_ARQ_NBDP_TelexTeleprinter );
   }
   else if ( field_data == "w" )
   {
      return(COMMUNICATIONS_MODE::F1B_J2B_ReceiveOnlyTeleprinterDSC );
   }
   else if ( field_data == "x" )
   {
      return(COMMUNICATIONS_MODE::A1A_MorseTapeRecorder );
   }
   else if ( field_data == "{" )
   {
      return(COMMUNICATIONS_MODE::A1A_MorseKeyHeadset );
   }
   else if ( field_data == "|" )
   {
      return(COMMUNICATIONS_MODE::F1C_F2C_F3C_FaxMachine );
   }
   else
   {
      return(COMMUNICATIONS_MODE::CommunicationsModeUnknown );
   }
}

uint8_t SENTENCE::ComputeChecksum( void ) const noexcept
{
   uint8_t checksum_value = 0;

   std::size_t string_length = Sentence.length();
   std::size_t index = 1; // Skip over the $ at the begining of the sentence

   while( index < string_length    && 
          Sentence[ index ] != '*' && 
          Sentence[ index ] != CARRIAGE_RETURN && 
          Sentence[ index ] != LINE_FEED )
   {
      checksum_value ^= Sentence[ index ];
      index++;
   }

   return( checksum_value );
}

double SENTENCE::Double( int field_number ) const noexcept
{
   std::string const field_data = Field( field_number );

   return( ::atof( field_data.c_str() ) );
}

EASTWEST SENTENCE::EastOrWest( int field_number ) const noexcept
{
   std::string const field_data = Field( field_number );

   if ( field_data == "E" )
   {
      return(EASTWEST::East);
   }
   else if ( field_data == "W" )
   {
      return(EASTWEST::West);
   }
   else
   {
      return(EASTWEST::EW_Unknown);
   }
}

const std::string SENTENCE::Field( int desired_field_number ) const noexcept
{
   // Thanks to Vilhelm Persson (vilhelm.persson@st.se) for finding a 
   // bug that lived here.

   std::string return_string;

   std::size_t index        = 1; // Skip over the $ at the begining of the sentence
   int current_field_number = 0;

   std::size_t const string_length = Sentence.length();

   while( current_field_number < desired_field_number && index < string_length )
   {
      if ( Sentence[ index ] == ',' || Sentence[ index ] == '*' )
      {
         current_field_number++;
      }

      index++;
   }

   if ( current_field_number == desired_field_number )
   {
      while( index < string_length    &&
             Sentence[ index ] != ',' &&
             Sentence[ index ] != '*' &&
             Sentence[ index ] != 0x00 )
      {
         return_string += Sentence[ index ];
         index++;
      }
   }

   return( return_string );
}

uint16_t SENTENCE::GetNumberOfDataFields( void ) const noexcept
{
   int index                = 1; // Skip over the $ at the begining of the sentence
   int current_field_number = 0;

   std::size_t const string_length = Sentence.length();

   while( index < string_length )
   {
      if ( Sentence[ index ] == '*' )
      {
         return( static_cast<uint16_t>(current_field_number) );
      }

      if ( Sentence[ index ] == ',' )
      {
         current_field_number++;
      }

      index++;
   }

   return( static_cast<uint16_t>(current_field_number) );
}

void SENTENCE::Finish( void ) noexcept
{
   uint8_t const checksum = ComputeChecksum();

   char temp_string[ 10 ];

   ::sprintf( temp_string, "*%02X%c%c", static_cast<int>(checksum), CARRIAGE_RETURN, LINE_FEED );

   Sentence += temp_string;
}

int SENTENCE::Integer( int field_number ) const noexcept
{
   std::string const integer_string = Field( field_number );

   return( ::atoi( integer_string.c_str() ) );
}

NMEA0183_BOOLEAN SENTENCE::IsChecksumBad( int checksum_field_number ) const noexcept
{
   /*
   ** Checksums are optional, return TRUE if an existing checksum is known to be bad
   */

   std::string const checksum_in_sentence = Field( checksum_field_number );

   if ( checksum_in_sentence.empty() == true )
   {
      return(NMEA0183_BOOLEAN::NMEA_Unknown);
   }

   if ( ComputeChecksum() != HexValue( checksum_in_sentence ) )
   {
      return(NMEA0183_BOOLEAN::True);
   }

   return(NMEA0183_BOOLEAN::False);
}

LEFTRIGHT SENTENCE::LeftOrRight( int field_number ) const noexcept
{
   std::string const field_data = Field( field_number );

   if ( field_data == "L" )
   {
      return(LEFTRIGHT::Left );
   }
   else if ( field_data == "R" )
   {
      return(LEFTRIGHT::Right );
   }
   else
   {
      return(LEFTRIGHT::LR_Unknown );
   }
}

NORTHSOUTH SENTENCE::NorthOrSouth( int field_number ) const noexcept
{
   std::string const field_data = Field( field_number );

   if ( field_data == "N" )
   {
      return(NORTHSOUTH::North );
   }
   else if ( field_data == "S" )
   {
      return(NORTHSOUTH::South );
   }
   else
   {
      return(NORTHSOUTH::NS_Unknown );
   }
}

REFERENCE SENTENCE::Reference( int field_number ) const noexcept
{
   std::string const field_data = Field( field_number );

   if ( field_data == "B" )
   {
      return(REFERENCE::BottomTrackingLog );
   }
   else if ( field_data == "M" )
   {
      return(REFERENCE::ManuallyEntered );
   }
   else if ( field_data == "W" )
   {
      return(REFERENCE::WaterReferenced );
   }
   else if ( field_data == "R" )
   {
      return(REFERENCE::RadarTrackingOfFixedTarget );
   }
   else if ( field_data == "P" )
   {
      return(REFERENCE::PositioningSystemGroundReference );
   }
   else
   {
      return(REFERENCE::ReferenceUnknown );
   }
}

time_t SENTENCE::Time( int field_number ) const noexcept
{
   time_t return_value = time(nullptr);

   std::string const temp_string = Field( field_number );

   if ( temp_string.length() >= 6 )
   {
      char temp_number[ 3 ];

      temp_number[ 2 ] = 0x00;

      temp_number[ 0 ] = temp_string[ 0 ];
      temp_number[ 1 ] = temp_string[ 1 ];

      int hours = ::atoi( temp_number );

      temp_number[ 0 ] = temp_string[ 2 ];
      temp_number[ 1 ] = temp_string[ 3 ];

      int minutes = ::atoi( temp_number );

      temp_number[ 0 ] = temp_string[ 4 ];
      temp_number[ 1 ] = temp_string[ 5 ];

      int seconds = ::atoi( temp_number );

      auto tm_p = gmtime(&return_value);

      int year = tm_p->tm_year + 1900;
      int month = tm_p->tm_mon;
      int day = tm_p->tm_mday;

      return_value = ctime( year, month, day, hours, minutes, seconds );
   }

   return( return_value );
}

TRANSDUCER_TYPE SENTENCE::TransducerType( int field_number ) const noexcept
{
   std::string const field_data = Field( field_number );

   if ( field_data == "A" )
   {
      return(TRANSDUCER_TYPE::AngularDisplacementTransducer );
   }
   else if ( field_data == "D" )
   {
      return(TRANSDUCER_TYPE::LinearDisplacementTransducer );
   }
   else if ( field_data == "C" )
   {
      return(TRANSDUCER_TYPE::TemperatureTransducer );
   }
   else if ( field_data == "F" )
   {
      return(TRANSDUCER_TYPE::FrequencyTransducer );
   }
   else if ( field_data == "N" )
   {
      return(TRANSDUCER_TYPE::ForceTransducer );
   }
   else if ( field_data == "P" )
   {
      return(TRANSDUCER_TYPE::PressureTransducer );
   }
   else if (field_data == "R" )
   {
      return(TRANSDUCER_TYPE::FlowRateTransducer );
   }
   else if ( field_data == "T" )
   {
      return(TRANSDUCER_TYPE::TachometerTransducer );
   }
   else if ( field_data == "H" )
   {
      return(TRANSDUCER_TYPE::HumidityTransducer );
   }
   else if ( field_data == "V" )
   {
      return(TRANSDUCER_TYPE::VolumeTransducer );
   }
   else
   {
      return(TRANSDUCER_TYPE::TransducerUnknown );
   }
}

/*
** Operators
*/

SENTENCE::operator std::string() const noexcept
{
   return( Sentence );
}

SENTENCE const& SENTENCE::operator = ( SENTENCE const& source ) noexcept
{
   Sentence = source.Sentence;

   return( *this );
}

SENTENCE const& SENTENCE::operator = ( std::string const& source ) noexcept
{
   Sentence = source;

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( std::string const& source ) noexcept
{
    Sentence.push_back(',');
    Sentence += source;

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( double value ) noexcept
{
   char temp_string[ 80 ];

   ::sprintf( temp_string, "%.3f", value );

   Sentence.push_back(',');
   Sentence += temp_string;

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( COMMUNICATIONS_MODE mode ) noexcept
{
   Sentence.push_back(',');

   switch( mode )
   {
   case COMMUNICATIONS_MODE::F3E_G3E_SimplexTelephone:

       Sentence.push_back('d');
       break;

   case COMMUNICATIONS_MODE::F3E_G3E_DuplexTelephone:

       Sentence.push_back('e');
       break;

   case COMMUNICATIONS_MODE::J3E_Telephone:

       Sentence.push_back('m');
       break;

   case COMMUNICATIONS_MODE::H3E_Telephone:

       Sentence.push_back('o');
       break;

   case COMMUNICATIONS_MODE::F1B_J2B_FEC_NBDP_TelexTeleprinter:

       Sentence.push_back('1');
       break;

   case COMMUNICATIONS_MODE::F1B_J2B_ARQ_NBDP_TelexTeleprinter:

       Sentence.push_back('s');
       break;

   case COMMUNICATIONS_MODE::F1B_J2B_ReceiveOnlyTeleprinterDSC:

       Sentence.push_back('w');
       break;

   case COMMUNICATIONS_MODE::A1A_MorseTapeRecorder:

       Sentence.push_back('x');
       break;

   case COMMUNICATIONS_MODE::A1A_MorseKeyHeadset:

       Sentence.push_back('{');
       break;

   case COMMUNICATIONS_MODE::F1C_F2C_F3C_FaxMachine:

       Sentence.push_back('|');
       break;
   }

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( TRANSDUCER_TYPE transducer ) noexcept
{
    Sentence.push_back(',');

   switch( transducer )
   {
   case TRANSDUCER_TYPE::TemperatureTransducer:

       Sentence.push_back('C');
       break;

   case TRANSDUCER_TYPE::AngularDisplacementTransducer:

       Sentence.push_back('A');
       break;

   case TRANSDUCER_TYPE::LinearDisplacementTransducer:

       Sentence.push_back('D');
       break;

   case TRANSDUCER_TYPE::FrequencyTransducer:

       Sentence.push_back('F');
       break;

   case TRANSDUCER_TYPE::ForceTransducer:

       Sentence.push_back('N');
       break;

   case TRANSDUCER_TYPE::PressureTransducer:

       Sentence.push_back('P');
       break;

   case TRANSDUCER_TYPE::FlowRateTransducer:

       Sentence.push_back('R');
       break;

   case TRANSDUCER_TYPE::TachometerTransducer:

       Sentence.push_back('T');
       break;

   case TRANSDUCER_TYPE::HumidityTransducer:

       Sentence.push_back('H');
       break;

   case TRANSDUCER_TYPE::VolumeTransducer:

       Sentence.push_back('V');
       break;
   }

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( NORTHSOUTH northing ) noexcept
{
    Sentence.push_back(',');

   if ( northing == NORTHSOUTH::North )
   {
       Sentence.push_back('N');
   }
   else if ( northing == NORTHSOUTH::South )
   {
       Sentence.push_back('S');
   }

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( int value ) noexcept
{
   char temp_string[ 80 ];

   ::sprintf( temp_string, "%d", value );

   Sentence.push_back(',');
   Sentence += temp_string;

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( EASTWEST easting ) noexcept
{
    Sentence.push_back(',');

   if ( easting == EASTWEST::East )
   {
       Sentence.push_back('E');
   }
   else if ( easting == EASTWEST::West )
   {
       Sentence.push_back('W');
   }

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( NMEA0183_BOOLEAN boolean ) noexcept
{
    Sentence.push_back(',');

   if ( boolean == NMEA0183_BOOLEAN::True )
   {
       Sentence.push_back('A');
   }
   else if ( boolean == NMEA0183_BOOLEAN::False )
   {
       Sentence.push_back('V');
   }

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( LATLONG const& source ) noexcept
{
   source.Write( *this );

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( time_t const time_value ) noexcept
{
   auto tm_p = gmtime(&time_value);

   char temp_string[65];

   sprintf( temp_string, "%02d%02d%02d", tm_p->tm_hour, tm_p->tm_min, tm_p->tm_sec );

   Sentence.push_back(',');
   Sentence += temp_string;

   return( *this );
}

SENTENCE const& SENTENCE::operator += (LEFTRIGHT left_or_right) noexcept
{
    Sentence.push_back(',');

    if (left_or_right == LEFTRIGHT::Left)
    {
        Sentence.push_back('L');
    }
    else if (left_or_right == LEFTRIGHT::Right)
    {
        Sentence.push_back('R');
    }

    return(*this);
}

SENTENCE const& SENTENCE::operator += (REFERENCE a_reference) noexcept
{
    Sentence.push_back(',');

    switch (a_reference)
    {
    case REFERENCE::BottomTrackingLog:

        Sentence.push_back('B');
        break;

    case REFERENCE::ManuallyEntered:

        Sentence.push_back('M');
        break;

    case REFERENCE::WaterReferenced:

        Sentence.push_back('W');
        break;

    case REFERENCE::RadarTrackingOfFixedTarget:

        Sentence.push_back('R');
        break;

    case REFERENCE::PositioningSystemGroundReference:

        Sentence.push_back('P');
        break;
    }

    return(*this);
}
