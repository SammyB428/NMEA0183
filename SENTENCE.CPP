/*
Author: Samuel R. Blackburn
Internet: wfc@pobox.com

"You can get credit for something or get it done, but not both."
Dr. Richard Garwin

The MIT License (MIT)

Copyright (c) 1996-2021 Sam Blackburn

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

// SPDX-License-Identifier: MIT

#include "nmea0183.h"
#pragma hdrstop

NMEA0183_BOOLEAN SENTENCE::Boolean( int field_number ) const noexcept
{
   auto field_data{ Field(field_number) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'A')
       {
           return(NMEA0183_BOOLEAN::True);
       }
       else if (field_data[0] == 'V')
       {
           return(NMEA0183_BOOLEAN::False);
       }
       else
       {
           return(NMEA0183_BOOLEAN::NMEA_Unknown);
       }
   }
   else
   {
       return(NMEA0183_BOOLEAN::NMEA_Unknown);
   }
}

COMMUNICATIONS_MODE SENTENCE::CommunicationsMode( int field_number ) const noexcept
{
   auto field_data{ Field(field_number) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'd')
       {
           return(COMMUNICATIONS_MODE::F3E_G3E_SimplexTelephone);
       }
       else if (field_data[0] == 'e')
       {
           return(COMMUNICATIONS_MODE::F3E_G3E_DuplexTelephone);
       }
       else if (field_data[0] == 'm')
       {
           return(COMMUNICATIONS_MODE::J3E_Telephone);
       }
       else if (field_data[0] == 'o')
       {
           return(COMMUNICATIONS_MODE::H3E_Telephone);
       }
       else if (field_data[0] == 'q')
       {
           return(COMMUNICATIONS_MODE::F1B_J2B_FEC_NBDP_TelexTeleprinter);
       }
       else if (field_data[0] == 's')
       {
           return(COMMUNICATIONS_MODE::F1B_J2B_ARQ_NBDP_TelexTeleprinter);
       }
       else if (field_data[0] == 'w')
       {
           return(COMMUNICATIONS_MODE::F1B_J2B_ReceiveOnlyTeleprinterDSC);
       }
       else if (field_data[0] == 'x')
       {
           return(COMMUNICATIONS_MODE::A1A_MorseTapeRecorder);
       }
       else if (field_data[0] == '{')
       {
           return(COMMUNICATIONS_MODE::A1A_MorseKeyHeadset);
       }
       else if (field_data[0] == '|')
       {
           return(COMMUNICATIONS_MODE::F1C_F2C_F3C_FaxMachine);
       }
       else
       {
           return(COMMUNICATIONS_MODE::CommunicationsModeUnknown);
       }
   }
   else
   {
       return(COMMUNICATIONS_MODE::CommunicationsModeUnknown);
   }
}

uint8_t SENTENCE::ComputeChecksum( void ) const noexcept
{
   uint8_t checksum_value{ 0 };

   auto const string_length{ Sentence.length() };
   std::size_t index{ 1 }; // Skip over the $ at the begining of the sentence

   while( index < string_length and
          Sentence[ index ] not_eq '*' and
          Sentence[ index ] not_eq CARRIAGE_RETURN and
          Sentence[ index ] not_eq LINE_FEED )
   {
      checksum_value xor_eq Sentence[ index ];
      index++;
   }

   return( checksum_value );
}

double SENTENCE::Double( int field_number ) const noexcept
{
   auto field_data{ Field(field_number) };

   if (field_data.length() < 1)
   {
       return(0.0);
   }

   double return_value{ 0.0 };

   std::ignore = std::from_chars(&field_data[0], &field_data[0] + field_data.length(), return_value);

   return(return_value);
}

EASTWEST SENTENCE::EastOrWest( int field_number ) const noexcept
{
   auto field_data{ Field(field_number) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'E')
       {
           return(EASTWEST::East);
       }
       else if (field_data[0] == 'W')
       {
           return(EASTWEST::West);
       }
       else
       {
           return(EASTWEST::EW_Unknown);
       }
   }
   else
   {
       return(EASTWEST::EW_Unknown);
   }
}

std::string_view SENTENCE::Field( int desired_field_number ) const noexcept
{
   // Thanks to Vilhelm Persson (vilhelm.persson@st.se) for finding a 
   // bug that lived here.

   std::size_t index{ 1 }; // Skip over the $ at the begining of the sentence
   int current_field_number{ 0 };

   auto const string_length{ Sentence.length() };

   while( current_field_number < desired_field_number and index < string_length )
   {
      if ( Sentence[ index ] == ',' or Sentence[ index ] == '*' )
      {
         current_field_number++;
      }

      index++;
   }

   if ( current_field_number == desired_field_number )
   {
      auto address_of_first_character{ &Sentence[index] };

      while( index < string_length and
             Sentence[ index ] not_eq ',' and
             Sentence[ index ] not_eq '*' and
             Sentence[ index ] not_eq 0x00 )
      {
         //return_string += Sentence[ index ];
         index++;
      }

      return(std::string_view(address_of_first_character, std::distance(address_of_first_character, &Sentence[index])));
   }

   return( std::string_view() );
}

uint16_t SENTENCE::GetNumberOfDataFields( void ) const noexcept
{
   std::size_t index{ 1 }; // Skip over the $ at the begining of the sentence
   int current_field_number{ 0 };

   auto const string_length{ Sentence.length() };

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
   auto const checksum{ ComputeChecksum() };

   char temp_string[ 10 ];

   auto const number_of_characters{ ::sprintf(temp_string, "*%02X%c%c", static_cast<int>(checksum), CARRIAGE_RETURN, LINE_FEED) };

   Sentence.append(temp_string, number_of_characters);
}

int SENTENCE::Integer( int field_number ) const noexcept
{
   auto integer_string{ Field(field_number) };

   if (integer_string.length() < 1)
   {
       return(0);
   }

   int return_value{ 0 };

   std::ignore = std::from_chars(&integer_string[0], &integer_string[0] + integer_string.length(), return_value, 10);

   return(return_value);
}

NMEA0183_BOOLEAN SENTENCE::IsChecksumBad( int checksum_field_number ) const noexcept
{
   /*
   ** Checksums are optional, return TRUE if an existing checksum is known to be bad
   */

   auto checksum_in_sentence{ Field(checksum_field_number) };

   if ( checksum_in_sentence.empty() == true )
   {
      return(NMEA0183_BOOLEAN::NMEA_Unknown);
   }

   if ( ComputeChecksum() not_eq HexValue( checksum_in_sentence ) )
   {
      return(NMEA0183_BOOLEAN::True);
   }

   return(NMEA0183_BOOLEAN::False);
}

LEFTRIGHT SENTENCE::LeftOrRight( int field_number ) const noexcept
{
   auto field_data{ Field(field_number) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'L')
       {
           return(LEFTRIGHT::Left);
       }
       else if (field_data[0] == 'R')
       {
           return(LEFTRIGHT::Right);
       }
       else
       {
           return(LEFTRIGHT::LR_Unknown);
       }
   }
   else
   {
       return(LEFTRIGHT::LR_Unknown);
   }
}

NORTHSOUTH SENTENCE::NorthOrSouth( int field_number ) const noexcept
{
   auto field_data{ Field(field_number) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'N')
       {
           return(NORTHSOUTH::North);
       }
       else if (field_data[0] == 'S')
       {
           return(NORTHSOUTH::South);
       }
       else
       {
           return(NORTHSOUTH::NS_Unknown);
       }
   }
   else
   {
       return(NORTHSOUTH::NS_Unknown);
   }
}

REFERENCE SENTENCE::Reference( int field_number ) const noexcept
{
   auto field_data{ Field(field_number) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'B')
       {
           return(REFERENCE::BottomTrackingLog);
       }
       else if (field_data[0] == 'M')
       {
           return(REFERENCE::ManuallyEntered);
       }
       else if (field_data[0] == 'W')
       {
           return(REFERENCE::WaterReferenced);
       }
       else if (field_data[0] == 'R')
       {
           return(REFERENCE::RadarTrackingOfFixedTarget);
       }
       else if (field_data[0] == 'P')
       {
           return(REFERENCE::PositioningSystemGroundReference);
       }
       else
       {
           return(REFERENCE::ReferenceUnknown);
       }
   }
   else
   {
       return(REFERENCE::ReferenceUnknown);
   }
}

time_t SENTENCE::Time( int field_number ) const noexcept
{
   auto return_value{ time(nullptr) };
   auto temp_string{ Field(field_number) };

   if ( temp_string.length() >= 6 )
   {
      int hours{ 0 };
      std::ignore = std::from_chars(&temp_string[0], &temp_string[2], hours);

      int minutes{ 0 };
      std::ignore = std::from_chars(&temp_string[2], &temp_string[4], minutes);

      int seconds{ 0 };
      // You have to code from_chars() with:
      // &temp_string[0] + 6 instead of:
      // &temp_string[6]
      // Because string_view will throw an exception that [6] is out of bounds.
      std::ignore = std::from_chars(&temp_string[4], &temp_string[0] + 6, seconds);

      auto tm_p{ gmtime(&return_value) };
      auto const year{ tm_p->tm_year + 1900 };
      auto const month{ tm_p->tm_mon };
      auto const day{ tm_p->tm_mday };

      return_value = ctime( year, month, day, hours, minutes, seconds );
   }

   return( return_value );
}

TRANSDUCER_TYPE SENTENCE::TransducerType( int field_number ) const noexcept
{
   auto field_data{ Field(field_number) };

   if (field_data.length() == 1)
   {
       if (field_data[0] == 'A')
       {
           return(TRANSDUCER_TYPE::AngularDisplacementTransducer);
       }
       else if (field_data[0] == 'D')
       {
           return(TRANSDUCER_TYPE::LinearDisplacementTransducer);
       }
       else if (field_data[0] == 'C')
       {
           return(TRANSDUCER_TYPE::TemperatureTransducer);
       }
       else if (field_data[0] == 'F')
       {
           return(TRANSDUCER_TYPE::FrequencyTransducer);
       }
       else if (field_data[0] == 'N')
       {
           return(TRANSDUCER_TYPE::ForceTransducer);
       }
       else if (field_data[0] == 'P')
       {
           return(TRANSDUCER_TYPE::PressureTransducer);
       }
       else if (field_data[0] == 'R')
       {
           return(TRANSDUCER_TYPE::FlowRateTransducer);
       }
       else if (field_data[0] == 'T')
       {
           return(TRANSDUCER_TYPE::TachometerTransducer);
       }
       else if (field_data[0] == 'H')
       {
           return(TRANSDUCER_TYPE::HumidityTransducer);
       }
       else if (field_data[0] == 'V')
       {
           return(TRANSDUCER_TYPE::VolumeTransducer);
       }
       else
       {
           return(TRANSDUCER_TYPE::TransducerUnknown);
       }
   }
   else
   {
       return(TRANSDUCER_TYPE::TransducerUnknown);
   }
}

FAA_MODE SENTENCE::FAAMode(int field_number) const noexcept
{
    auto field_data{ Field(field_number) };

    if (field_data.length() == 1)
    {
        if (field_data[0] == 'A')
        {
            return(FAA_MODE::Autonomous);
        }
        else if (field_data[0] == 'D')
        {
            return(FAA_MODE::Differential);
        }
        else if (field_data[0] == 'E')
        {
            return(FAA_MODE::Estimated);
        }
        else if (field_data[0] == 'N')
        {
            return(FAA_MODE::NotValid);
        }
        else if (field_data[0] == 'S')
        {
            return(FAA_MODE::Simulated);
        }
        else if (field_data[0] == 'M')
        {
            return(FAA_MODE::Manual);
        }
        else
        {
            return(FAA_MODE::ModeUnknown);
        }
    }
    else
    {
        return(FAA_MODE::ModeUnknown);
    }
}

/*
** Operators
*/

SENTENCE::operator std::string() const noexcept
{
   return( Sentence );
}

SENTENCE::operator std::string_view() const noexcept
{
    return(Sentence);
}

SENTENCE const& SENTENCE::operator = ( SENTENCE const& source ) noexcept
{
   Sentence = source.Sentence;

   return( *this );
}

SENTENCE const& SENTENCE::operator = ( std::string_view source ) noexcept
{
   Sentence = source;

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( std::string_view source ) noexcept
{
    Sentence.push_back(',');
    Sentence += source;

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( double const value ) noexcept
{
   char temp_string[ 80 ];

   auto const number_of_characters{ ::sprintf(temp_string, "%.3f", value) };

   Sentence.push_back(',');
   Sentence.append(temp_string, number_of_characters);

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( COMMUNICATIONS_MODE const mode ) noexcept
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

   case COMMUNICATIONS_MODE::CommunicationsModeUnknown:
       break;
   }

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( TRANSDUCER_TYPE const transducer ) noexcept
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

   case TRANSDUCER_TYPE::TransducerUnknown:
       break;
   }

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( NORTHSOUTH const northing ) noexcept
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

SENTENCE const& SENTENCE::operator += ( int const value ) noexcept
{
   char temp_string[ 80 ];

   auto conversion{ std::to_chars(temp_string, temp_string + std::size(temp_string), value) };

   Sentence.push_back(',');
   Sentence.append(temp_string, std::distance(temp_string, conversion.ptr));

   return( *this );
}

SENTENCE const& SENTENCE::operator += ( EASTWEST const easting ) noexcept
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

SENTENCE const& SENTENCE::operator += ( NMEA0183_BOOLEAN const boolean ) noexcept
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
   auto tm_p{ gmtime(&time_value) };

   char temp_string[65];

   auto const number_of_characters{ ::sprintf(temp_string, "%02d%02d%02d", tm_p->tm_hour, tm_p->tm_min, tm_p->tm_sec) };

   Sentence.push_back(',');
   Sentence.append(temp_string, number_of_characters);

   return( *this );
}

SENTENCE const& SENTENCE::operator += (LEFTRIGHT const left_or_right) noexcept
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

SENTENCE const& SENTENCE::operator += (REFERENCE const a_reference) noexcept
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

    case REFERENCE::ReferenceUnknown:
        break;
    }

    return(*this);
}
