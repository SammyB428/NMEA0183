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

static inline bool is_less_than(RESPONSE const * left, RESPONSE const * right) noexcept
{
    return(left->Mnemonic < right->Mnemonic);
}

NMEA0183::NMEA0183()
{
   m_Initialize();

   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Aam) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Alm) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Apb) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Asd) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Bec) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Bod) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Bwc) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Bwr) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Bww) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Dbt) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Dcn) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Dpt) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Fsi) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gda) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gdf) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gdp) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gga) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gla) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Glc) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Glf) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gll) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Glp) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gsa) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gsv) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gtd) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gxa) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gxf) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Gxp) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Hcc) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Hdg) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Hdm) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Hdt) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Hsc) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Ima) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Lcd) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Mhu) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Mta) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Mtw) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Mwv) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Oln) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Osd) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Proprietary) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Rma) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Rmb) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Rmc) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Rot) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Rpm) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Rsa) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Rsd) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Rte) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Sfi) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Stn) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Tep) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Trf) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Ttm) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Vbw) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Vhw) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Vdr) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Vlw) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Vpw) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Vtg) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Vwe) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Wcv) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Wdc) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Wdr) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Wnc) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Wpl) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Xdr) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Xte) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Xtr) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zda) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zfi) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zfo) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zlz) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zpi) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zta) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zte) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Ztg) );
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zti) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zwp) ); // Sentence Not Recommended For New Designs
   m_ResponseTable.push_back( static_cast<RESPONSE *>(&Zzu) ); // Sentence Not Recommended For New Designs

   std::sort(m_ResponseTable.begin(), m_ResponseTable.end(), is_less_than);

   m_SetContainerPointers();
}

NMEA0183::~NMEA0183()
{
   m_Initialize();
}

void NMEA0183::m_Initialize( void ) noexcept
{
   ErrorMessage.clear();
}

void NMEA0183::m_SetContainerPointers( void ) noexcept
{
   for (auto& entry : m_ResponseTable)
   {
       entry->SetContainer(this);
   }
}

/*
** Public Interface
*/

bool NMEA0183::IsGood( void ) const noexcept
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

bool NMEA0183::Parse( void ) noexcept
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

       ErrorMessage.clear();

       LastSentenceIDReceived = mnemonic;

       /*
       ** Do a Binary Search to call the appropriate function
       */

       m_Needle.Mnemonic = mnemonic;

       auto iterator = std::lower_bound(m_ResponseTable.begin(), m_ResponseTable.end(), &m_Needle, is_less_than);

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
           ErrorMessage = mnemonic;
           ErrorMessage.append( " is an unknown type of sentence" );
           return_value = false;
       }
   }

   return( return_value );
}

void NMEA0183::SetSentence(char const * source) noexcept
{
    m_Sentence = source;
}

void NMEA0183::GetSentence(std::string& destination) const noexcept
{
    destination = m_Sentence;
}

time_t ctime(int const year, int const month, int const day, int const hour, int const minute, int const second) noexcept
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
