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

static bool is_less_than(__in const RESPONSE * left, __in const RESPONSE * right)
{
    return(left->Mnemonic < right->Mnemonic);
}

NMEA0183::NMEA0183()
{
   m_Initialize();

   m_ResponseTable.push_back( (RESPONSE *) &Aam );
   m_ResponseTable.push_back( (RESPONSE *) &Alm );
   m_ResponseTable.push_back( (RESPONSE *) &Apb );
   m_ResponseTable.push_back( (RESPONSE *) &Asd );
   m_ResponseTable.push_back( (RESPONSE *) &Bec );
   m_ResponseTable.push_back( (RESPONSE *) &Bod );
   m_ResponseTable.push_back( (RESPONSE *) &Bwc );
   m_ResponseTable.push_back( (RESPONSE *) &Bwr );
   m_ResponseTable.push_back( (RESPONSE *) &Bww );
   m_ResponseTable.push_back( (RESPONSE *) &Dbt );
   m_ResponseTable.push_back( (RESPONSE *) &Dcn );
   m_ResponseTable.push_back( (RESPONSE *) &Dpt );
   m_ResponseTable.push_back( (RESPONSE *) &Fsi );
   m_ResponseTable.push_back( (RESPONSE *) &Gda ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Gdf ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Gdp ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Gga );
   m_ResponseTable.push_back( (RESPONSE *) &Gla ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Glc );
   m_ResponseTable.push_back( (RESPONSE *) &Glf ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Gll );
   m_ResponseTable.push_back( (RESPONSE *) &Glp ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Gsa );
   m_ResponseTable.push_back( (RESPONSE *) &Gsv );
   m_ResponseTable.push_back( (RESPONSE *) &Gtd ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Gxa );
   m_ResponseTable.push_back( (RESPONSE *) &Gxf ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Gxp ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Hcc ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Hdg );
   m_ResponseTable.push_back( (RESPONSE *) &Hdm ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Hdt );
   m_ResponseTable.push_back( (RESPONSE *) &Hsc );
   m_ResponseTable.push_back( (RESPONSE *) &Ima ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Lcd );
   m_ResponseTable.push_back( (RESPONSE *) &Mhu ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Mta ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Mtw );
   m_ResponseTable.push_back( (RESPONSE *) &Mwv );
   m_ResponseTable.push_back( (RESPONSE *) &Oln );
   m_ResponseTable.push_back( (RESPONSE *) &Osd );
   m_ResponseTable.push_back( (RESPONSE *) &Proprietary );
   m_ResponseTable.push_back( (RESPONSE *) &Rma );
   m_ResponseTable.push_back( (RESPONSE *) &Rmb );
   m_ResponseTable.push_back( (RESPONSE *) &Rmc );
   m_ResponseTable.push_back( (RESPONSE *) &Rot );
   m_ResponseTable.push_back( (RESPONSE *) &Rpm );
   m_ResponseTable.push_back( (RESPONSE *) &Rsa );
   m_ResponseTable.push_back( (RESPONSE *) &Rsd );
   m_ResponseTable.push_back( (RESPONSE *) &Rte );
   m_ResponseTable.push_back( (RESPONSE *) &Sfi );
   m_ResponseTable.push_back( (RESPONSE *) &Stn );
   m_ResponseTable.push_back( (RESPONSE *) &Tep ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Trf );
   m_ResponseTable.push_back( (RESPONSE *) &Ttm );
   m_ResponseTable.push_back( (RESPONSE *) &Vbw );
   m_ResponseTable.push_back( (RESPONSE *) &Vhw );
   m_ResponseTable.push_back( (RESPONSE *) &Vdr );
   m_ResponseTable.push_back( (RESPONSE *) &Vlw );
   m_ResponseTable.push_back( (RESPONSE *) &Vpw );
   m_ResponseTable.push_back( (RESPONSE *) &Vtg );
   m_ResponseTable.push_back( (RESPONSE *) &Vwe );
   m_ResponseTable.push_back( (RESPONSE *) &Wcv ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Wdc ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Wdr ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Wnc );
   m_ResponseTable.push_back( (RESPONSE *) &Wpl );
   m_ResponseTable.push_back( (RESPONSE *) &Xdr );
   m_ResponseTable.push_back( (RESPONSE *) &Xte );
   m_ResponseTable.push_back( (RESPONSE *) &Xtr );
   m_ResponseTable.push_back( (RESPONSE *) &Zda );
   m_ResponseTable.push_back( (RESPONSE *) &Zfi ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Zfo );
   m_ResponseTable.push_back( (RESPONSE *) &Zlz ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Zpi ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Zta ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Zte ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Ztg );
   m_ResponseTable.push_back( (RESPONSE *) &Zti ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Zwp ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( (RESPONSE *) &Zzu ); // Sentence Not Recommended For New Designs

   std::sort(m_ResponseTable.begin(), m_ResponseTable.end(), is_less_than);

   m_SetContainerPointers();
}

NMEA0183::~NMEA0183()
{
   m_Initialize();
}

void NMEA0183::m_Initialize( void )
{
   ErrorMessage.clear();
}

void NMEA0183::m_SetContainerPointers( void )
{
   size_t index = 0;
   const size_t number_of_entries_in_table = m_ResponseTable.size();

   while( index < number_of_entries_in_table )
   {
      m_ResponseTable[ index ]->SetContainer( this );

      index++;
   }
}

/*
** Public Interface
*/

bool NMEA0183::IsGood( void ) const
{
   /*
   ** NMEA 0183 sentences begin with $ and and with CR LF
   */

   if ( m_Sentence.Sentence[ 0 ] != '$' )
   {
      return( false );
   }

   /*
   ** Next to last character must be a CR
   */

   if ( m_Sentence.Sentence[ m_Sentence.Sentence.length() - 2 ] != CARRIAGE_RETURN )
   {
      return( false );
   }

   if ( m_Sentence.Sentence[m_Sentence.Sentence.length() - 1 ] != LINE_FEED )
   {
      return( false );
   }

   return( true );
}

bool NMEA0183::Parse( void )
{
   bool return_value = false;

   if (IsGood())
   {
       std::string mnemonic = m_Sentence.Field(0);

       /*
       ** See if this is a proprietary field
       */

       if (mnemonic[0] == 'P')
       {
           mnemonic = "P";
       }
       else
       {
           mnemonic = mnemonic.substr(mnemonic.length() - 3, 3);
       }

       /*
       ** Set up our default error message
       */

       ErrorMessage = mnemonic;
       ErrorMessage += " is an unknown type of sentence";

       LastSentenceIDReceived = mnemonic;

       /*
       ** Do a Binary Search to call the appropriate function
       */

       GLA needle;

       needle.Mnemonic = mnemonic;

       std::vector<RESPONSE *>::iterator iterator = std::lower_bound(m_ResponseTable.begin(), m_ResponseTable.end(), &needle, is_less_than);

       if (iterator != m_ResponseTable.end() && (*iterator)->Mnemonic.compare(mnemonic) == 0)
       {
           return_value = (*iterator)->Parse(m_Sentence);

           /*
           ** Set your ErrorMessage
           */

           if (return_value == true)
           {
               /*
               ** Now that we sucessfully parsed a sentence, record stuff *about* the transaction
               */

               ErrorMessage = "No Error";
               LastSentenceIDParsed = (*iterator)->Mnemonic;
               TalkerID = talker_id(m_Sentence);
               ExpandedTalkerID = expand_talker_id(TalkerID);
               PlainText = (*iterator)->PlainEnglish();
           }
           else
           {
               ErrorMessage = (*iterator)->ErrorMessage;
           }
       }
       else
       {
           return_value = false;
       }
   }

   return( return_value );
}

void NMEA0183::SetSentence(const char *source)
{
    m_Sentence = source;
}

void NMEA0183::GetSentence(std::string& destination) const
{
    destination = m_Sentence;
}

NMEA0183& NMEA0183::operator << ( const char *source )
{
   SetSentence(source);
   return( *this );
}

NMEA0183& NMEA0183::operator >> ( std::string& destination )
{
   GetSentence(destination);
   return( *this );
}

time_t ctime(const int year, const int month, const int day, const int hour, const int minute, const int second)
{
    struct tm gtime;

    gtime.tm_sec = second;
    gtime.tm_min = minute;
    gtime.tm_hour = hour;
    gtime.tm_mday = day;
    gtime.tm_mon = month;
    gtime.tm_year = year - 1900;
    gtime.tm_wday = 0;
    gtime.tm_yday = 0;
    gtime.tm_isdst = 0;

    return(_mkgmtime(&gtime));
}

