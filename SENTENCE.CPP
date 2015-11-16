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

NMEA0183_BOOLEAN SENTENCE::Boolean( int field_number ) const
{
   std::string field_data = Field( field_number );

   if ( field_data == "A" )
   {
      return( True );
   }
   else if ( field_data == "V" )
   {
      return( False );
   }
   else
   {
      return( NMEA_Unknown );
   }
}

COMMUNICATIONS_MODE SENTENCE::CommunicationsMode( int field_number ) const
{
   std::string field_data = Field( field_number );

   if ( field_data == "d" )
   {		 
      return( F3E_G3E_SimplexTelephone );
   }
   else if ( field_data == "e" )
   {
      return( F3E_G3E_DuplexTelephone );
   }
   else if ( field_data == "m" )
   {
      return( J3E_Telephone );
   }
   else if ( field_data == "o" )
   {
      return( H3E_Telephone );
   }
   else if ( field_data == "q" )
   {
      return( F1B_J2B_FEC_NBDP_TelexTeleprinter );
   }
   else if ( field_data == "s" )
   {
      return( F1B_J2B_ARQ_NBDP_TelexTeleprinter );
   }
   else if ( field_data == "w" )
   {
      return( F1B_J2B_ReceiveOnlyTeleprinterDSC );
   }
   else if ( field_data == "x" )
   {
      return( A1A_MorseTapeRecorder );
   }
   else if ( field_data == "{" )
   {
      return( A1A_MorseKeyHeadset );
   }
   else if ( field_data == "|" )
   {
      return( F1C_F2C_F3C_FaxMachine );
   }
   else
   {
      return( CommunicationsModeUnknown );
   }
}

uint8_t SENTENCE::ComputeChecksum( void ) const
{
   uint8_t checksum_value = 0;

   size_t string_length = Sentence.length();
   size_t index = 1; // Skip over the $ at the begining of the sentence

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

double SENTENCE::Double( int field_number ) const
{
   std::string field_data = Field( field_number );

   return( ::atof( field_data.c_str() ) );
}

EASTWEST SENTENCE::EastOrWest( int field_number ) const
{
   std::string field_data = Field( field_number );

   if ( field_data == "E" )
   {
      return( East );
   }
   else if ( field_data == "W" )
   {
      return( West );
   }
   else
   {
      return( EW_Unknown );
   }
}

const std::string SENTENCE::Field( int desired_field_number ) const
{
   // Thanks to Vilhelm Persson (vilhelm.persson@st.se) for finding a 
   // bug that lived here.

   std::string return_string;

   size_t index             = 1; // Skip over the $ at the begining of the sentence
   int current_field_number = 0;

   const size_t string_length = Sentence.length();

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

uint16_t SENTENCE::GetNumberOfDataFields( void ) const
{
   int index                = 1; // Skip over the $ at the begining of the sentence
   int current_field_number = 0;

   const size_t string_length = Sentence.length();

   while( index < string_length )
   {
      if ( Sentence[ index ] == '*' )
      {
         return( (uint16_t) current_field_number );
      }

      if ( Sentence[ index ] == ',' )
      {
         current_field_number++;
      }

      index++;
   }

   return( (uint16_t) current_field_number );
}

void SENTENCE::Finish( void )
{
   const uint8_t checksum = ComputeChecksum();

   char temp_string[ 10 ];

   ::sprintf( temp_string, "*%02X%c%c", (int) checksum, CARRIAGE_RETURN, LINE_FEED );

   Sentence += temp_string;
}

int SENTENCE::Integer( int field_number ) const
{
   std::string integer_string = Field( field_number );

   return( ::atoi( integer_string.c_str() ) );
}

NMEA0183_BOOLEAN SENTENCE::IsChecksumBad( int checksum_field_number ) const
{
   /*
   ** Checksums are optional, return TRUE if an existing checksum is known to be bad
   */

   std::string checksum_in_sentence = Field( checksum_field_number );

   if ( checksum_in_sentence == "" )
   {
      return( NMEA_Unknown );
   }

   if ( ComputeChecksum() != HexValue( checksum_in_sentence ) )
   {
      return( True );
   } 

   return( False );
}

LEFTRIGHT SENTENCE::LeftOrRight( int field_number ) const
{
   std::string field_data = Field( field_number );

   if ( field_data == "L" )
   {
      return( Left );
   }
   else if ( field_data == "R" )
   {
      return( Right );
   }
   else
   {
      return( LR_Unknown );
   }
}

NORTHSOUTH SENTENCE::NorthOrSouth( int field_number ) const
{
   std::string field_data = Field( field_number );

   if ( field_data == "N" )
   {
      return( North );
   }
   else if ( field_data == "S" )
   {
      return( South );
   }
   else
   {
      return( NS_Unknown );
   }
}

REFERENCE SENTENCE::Reference( int field_number ) const
{
   std::string field_data = Field( field_number );

   if ( field_data == "B" )
   {
      return( BottomTrackingLog );
   }
   else if ( field_data == "M" )
   {
      return( ManuallyEntered );
   }
   else if ( field_data == "W" )
   {
      return( WaterReferenced );
   }
   else if ( field_data == "R" )
   {
      return( RadarTrackingOfFixedTarget );
   }
   else if ( field_data == "P" )
   {
      return( PositioningSystemGroundReference );
   }
   else
   {
      return( ReferenceUnknown );
   }
}

const time_t SENTENCE::Time( int field_number ) const
{
   time_t return_value = time(nullptr);

   std::string temp_string = Field( field_number );

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

      struct tm * tm_p = gmtime(&return_value);

      int year = tm_p->tm_year + 1900;
      int month = tm_p->tm_mon;
      int day = tm_p->tm_mday;

      return_value = ctime( year, month, day, hours, minutes, seconds );
   }

   return( return_value );
}

TRANSDUCER_TYPE SENTENCE::TransducerType( int field_number ) const
{
   std::string field_data = Field( field_number );

   if ( field_data == "A" )
   {		 
      return( AngularDisplacementTransducer );
   }
   else if ( field_data == "D" )
   {
      return( LinearDisplacementTransducer );
   }
   else if ( field_data == "C" )
   {
      return( TemperatureTransducer );
   }
   else if ( field_data == "F" )
   {
      return( FrequencyTransducer );
   }
   else if ( field_data == "N" )
   {
      return( ForceTransducer );
   }
   else if ( field_data == "P" )
   {
      return( PressureTransducer );
   }
   else if ( field_data == "R" )
   {
      return( FlowRateTransducer );
   }
   else if ( field_data == "T" )
   {
      return( TachometerTransducer );
   }
   else if ( field_data == "H" )
   {
      return( HumidityTransducer );
   }
   else if ( field_data == "V" )
   {
      return( VolumeTransducer );
   }
   else
   {
      return( TransducerUnknown );
   }
}

/*
** Operators
*/

SENTENCE::operator std::string() const
{
   return( Sentence );
}

const SENTENCE& SENTENCE::operator = ( const SENTENCE& source )
{
   Sentence = source.Sentence;

   return( *this );
}

const SENTENCE& SENTENCE::operator = ( const std::string& source )
{
   Sentence = source;

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( const std::string& source )
{
   Sentence += ",";
   Sentence += source;

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( double value )
{
   char temp_string[ 80 ];

   ::sprintf( temp_string, "%.3f", value );

   Sentence += ",";
   Sentence += temp_string;

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( COMMUNICATIONS_MODE mode )
{
   Sentence += ",";

   switch( mode )
   {
      case F3E_G3E_SimplexTelephone:

	      Sentence += "d";
		   break;

      case F3E_G3E_DuplexTelephone:

	      Sentence += "e";
		   break;

      case J3E_Telephone:

	      Sentence += "m";
		   break;

      case H3E_Telephone:

	      Sentence += "o";
		   break;

      case F1B_J2B_FEC_NBDP_TelexTeleprinter:

	      Sentence += "q";
		   break;

      case F1B_J2B_ARQ_NBDP_TelexTeleprinter:

	      Sentence += "s";
		   break;

      case F1B_J2B_ReceiveOnlyTeleprinterDSC:

	      Sentence += "w";
		   break;

      case A1A_MorseTapeRecorder:

	      Sentence += "x";
		   break;

      case A1A_MorseKeyHeadset:

	      Sentence += "{";
		   break;

      case F1C_F2C_F3C_FaxMachine:

	      Sentence += "|";
		   break;
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( TRANSDUCER_TYPE transducer )
{
   Sentence += ",";

   switch( transducer )
   {
      case TemperatureTransducer:

	      Sentence += "C";
		   break;

      case AngularDisplacementTransducer:

	      Sentence += "A";
		   break;

      case LinearDisplacementTransducer:

	      Sentence += "D";
		   break;

      case FrequencyTransducer:

	      Sentence += "F";
		   break;

      case ForceTransducer:

	      Sentence += "N";
		   break;

      case PressureTransducer:

	      Sentence += "P";
		   break;

      case FlowRateTransducer:

	      Sentence += "R";
		   break;

      case TachometerTransducer:

	      Sentence += "T";
		   break;

      case HumidityTransducer:

	      Sentence += "H";
		   break;

      case VolumeTransducer:

	      Sentence += "V";
		   break;
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( NORTHSOUTH northing )
{
   Sentence += ",";

   if ( northing == North )
   {
      Sentence += "N";
   }
   else if ( northing == South )
   {
      Sentence += "S";
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( int value )
{
   char temp_string[ 80 ];

   ::sprintf( temp_string, "%d", value );

   Sentence += ",";
   Sentence += temp_string;

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( EASTWEST easting )
{
   Sentence += ",";

   if ( easting == East )
   {
      Sentence += "E";
   }
   else if ( easting == West )
   {
      Sentence += "W";
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( NMEA0183_BOOLEAN boolean )
{
   Sentence += ",";

   if ( boolean == True )
   {
      Sentence += "A";
   }
   else if ( boolean == False )
   {
      Sentence += "V";
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( LATLONG& source )
{
   source.Write( *this );

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( const time_t time_value )
{
   struct tm * tm_p = gmtime(&time_value);

   char temp_string[65];

   sprintf( temp_string, "%02d%02d%02d", tm_p->tm_hour, tm_p->tm_min, tm_p->tm_sec );

   Sentence += ",";
   Sentence += temp_string;

   return( *this );
}
