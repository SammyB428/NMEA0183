#if ! defined( NMEA_0183_CLASS_HEADER )

#define NMEA_0183_CLASS_HEADER

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

/*
** General Purpose Classes
*/

#include "Sentence.hpp"
#include "Response.hpp"
#include "LatLong.hpp"
#include "LoranTD.hpp"
#include "Manufact.hpp"
#include "MList.hpp"
#include "OmegaPar.hpp"
#include "DeccaLOP.hpp"
#include "RatioPls.hpp"
#include "RadarDat.hpp"
#include "SatDat.hpp"
#include "FreqMode.hpp"
#include "WayptLoc.hpp" // Sentence Not Recommended For New Designs

/*
** Response Classes
*/

#include "AAM.hpp"
#include "ALM.hpp"
#include "APB.hpp"
#include "ASD.hpp"
#include "BEC.hpp"
#include "BOD.hpp"
#include "BWC.hpp"
#include "BWR.hpp"
#include "BWW.hpp"
#include "DBT.hpp"
#include "DCN.hpp"
#include "DPT.hpp"
#include "FSI.hpp"
#include "GDA.hpp" // Sentence Not Recommended For New Designs
#include "GDF.hpp" // Sentence Not Recommended For New Designs
#include "GDP.hpp" // Sentence Not Recommended For New Designs
#include "GGA.hpp"
#include "GLA.hpp" // Sentence Not Recommended For New Designs
#include "GLC.hpp"
#include "GLF.hpp" // Sentence Not Recommended For New Designs
#include "GLL.hpp"
#include "GLP.hpp" // Sentence Not Recommended For New Designs
#include "GOA.hpp" // Sentence Not Recommended For New Designs
#include "GOF.hpp" // Sentence Not Recommended For New Designs
#include "GOP.hpp" // Sentence Not Recommended For New Designs
#include "GSA.hpp"
#include "GSV.hpp"
#include "GTD.hpp" // Sentence Not Recommended For New Designs
#include "GXA.hpp"
#include "GXF.hpp" // Sentence Not Recommended For New Designs
#include "GXP.hpp" // Sentence Not Recommended For New Designs
#include "HCC.hpp" // Sentence Not Recommended For New Designs
#include "HDG.hpp"
#include "HDM.hpp" // Sentence Not Recommended For New Designs
#include "HDT.hpp"
#include "HSC.hpp"
#include "IMA.hpp" // Sentence Not Recommended For New Designs
#include "LCD.hpp"
#include "MHU.hpp" // Sentence Not Recommended For New Designs
#include "MTA.hpp" // Sentence Not Recommended For New Designs
#include "MTW.hpp"
#include "MWV.hpp"
#include "OLN.hpp"
#include "OSD.hpp"
#include "P.hpp"
#include "RMA.hpp"
#include "RMB.hpp"
#include "RMC.hpp"
#include "ROT.hpp"
#include "RPM.hpp"
#include "RSA.hpp"
#include "RSD.hpp"
#include "RTE.hpp"
#include "SFI.hpp"
#include "STN.hpp"
#include "TEP.hpp" // Sentence Not Recommended For New Designs
#include "TRF.hpp"
#include "TTM.hpp"
#include "VBW.hpp"
#include "VDR.hpp"
#include "VHW.hpp"
#include "VLW.hpp"
#include "VPW.hpp"
#include "VTG.hpp"
#include "VWE.hpp" // Sentence Not Recommended For New Designs
#include "WCV.hpp"
#include "WDC.hpp" // Sentence Not Recommended For New Designs
#include "WDR.hpp" // Sentence Not Recommended For New Designs
#include "WNC.hpp"
#include "WPL.hpp"
#include "XDR.hpp"
#include "XTE.hpp"
#include "XTR.hpp"
#include "ZDA.hpp"
#include "ZFI.hpp" // Sentence Not Recommended For New Designs
#include "ZFO.hpp" 
#include "ZLZ.hpp" // Sentence Not Recommended For New Designs
#include "ZPI.hpp" // Sentence Not Recommended For New Designs
#include "ZTA.hpp" // Sentence Not Recommended For New Designs
#include "ZTE.hpp" // Sentence Not Recommended For New Designs
#include "ZTG.hpp"
#include "ZTI.hpp" // Sentence Not Recommended For New Designs
#include "ZWP.hpp" // Sentence Not Recommended For New Designs
#include "ZZU.hpp" // Sentence Not Recommended For New Designs

class NMEA0183
{
   private:

      SENTENCE m_Sentence;

      /*
        ASD is chosen as the RESPONSE class to be the needle (what we're searching for) because it is the
        most light weight concrete class. It has no data members...
        This needle is used to binary search the haystack of possible responses.
      */
      ASD m_Needle;

      void m_Initialize( void ) noexcept;

   protected:

      std::vector<RESPONSE *> m_ResponseTable;

      void m_SetContainerPointers( void ) noexcept;

   public:

      NMEA0183();
      virtual ~NMEA0183();

      /*
      HOW TO USE THIS CLASS
      Normally, you don't care about most sentences.
      Modify the declaration of this class (or copy this class to your own
      class) and get rid of the sentences you don't care about. For example,
      if you're interfacing with a device that will NEVER produce an AAM sentence,
      get rid of the Aam member. Don't have code that will never be called.
      */

      /*
      ** NMEA 0183 Sentences we understand
      */

      AAM Aam;
      ALM Alm;
      APB Apb;
      ASD Asd;
      BEC Bec;
      BOD Bod;
      BWC Bwc;
      BWR Bwr;
      BWW Bww;
      DBT Dbt;
      DCN Dcn;
      DPT Dpt;
      FSI Fsi;
      GDA Gda; // Sentence Not Recommended For New Designs
      GDF Gdf; // Sentence Not Recommended For New Designs
      GDP Gdp; // Sentence Not Recommended For New Designs
      GGA Gga;
      GLA Gla; // Sentence Not Recommended For New Designs
      GLC Glc;
      GLF Glf; // Sentence Not Recommended For New Designs
      GLL Gll;
      GLP Glp; // Sentence Not Recommended For New Designs
      GOA Goa; // Sentence Not Recommended For New Designs
      GOF Gof; // Sentence Not Recommended For New Designs
      GOP Gop; // Sentence Not Recommended For New Designs
      GSA Gsa;
      GSV Gsv;
      GTD Gtd; // Sentence Not Recommended For New Designs
      GXA Gxa;
      GXF Gxf; // Sentence Not Recommended For New Designs
      GXP Gxp; // Sentence Not Recommended For New Designs
      HCC Hcc; // Sentence Not Recommended For New Designs
      HDG Hdg;
      HDM Hdm; // Sentence Not Recommended For New Designs
      HDT Hdt;
      HSC Hsc;
      IMA Ima; // Sentence Not Recommended For New Designs
      LCD Lcd;
      MHU Mhu; // Sentence Not Recommended For New Designs
      MTA Mta; // Sentence Not Recommended For New Designs
      MTW Mtw;
      MWV Mwv;
      OLN Oln;
      OSD Osd;
      P   Proprietary;
      RMA Rma;
      RMB Rmb;
      RMC Rmc;
      ROT Rot;
      RPM Rpm;
      RSA Rsa;
      RSD Rsd;
      RTE Rte;
      SFI Sfi;
      STN Stn;
      TEP Tep; // Sentence Not Recommended For New Designs
      TRF Trf;
      TTM Ttm;
      VBW Vbw;
      VDR Vdr;
      VHW Vhw;
      VLW Vlw;
      VPW Vpw;
      VTG Vtg;
      VWE Vwe; // Sentence Not Recommended For New Designs
      WCV Wcv;
      WDC Wdc; // Sentence Not Recommended For New Designs
      WDR Wdr; // Sentence Not Recommended For New Designs
      WNC Wnc;
      WPL Wpl;
	  XDR Xdr;
	  XTE Xte;
      XTR Xtr;
      ZDA Zda;
      ZFI Zfi; // Sentence Not Recommended For New Designs
      ZFO Zfo;
      ZLZ Zlz; // Sentence Not Recommended For New Designs
      ZPI Zpi; // Sentence Not Recommended For New Designs
      ZTA Zta; // Sentence Not Recommended For New Designs
      ZTE Zte; // Sentence Not Recommended For New Designs
      ZTI Zti; // Sentence Not Recommended For New Designs
      ZTG Ztg;
      ZWP Zwp; // Sentence Not Recommended For New Designs
      ZZU Zzu; // Sentence Not Recommended For New Designs

      std::string ErrorMessage; // Filled when Parse returns FALSE
      std::string LastSentenceIDParsed; // ID of the lst sentence successfully parsed
      std::string LastSentenceIDReceived; // ID of the last sentence received, may not have parsed successfully
      std::string PlainText; // A human-readable string of text that explains what just happened

      std::string TalkerID;
      std::string ExpandedTalkerID;

      virtual bool IsGood( void ) const noexcept;
      virtual bool Parse( void ) noexcept;
      virtual void SetSentence(char const * source) noexcept;
      virtual void GetSentence(std::string& destination) const noexcept;

      inline NMEA0183& operator << (char const * source) noexcept
      {
          SetSentence(source);
          return(*this);
      }

      inline NMEA0183& operator >> (std::string& destination) noexcept
      {
          GetSentence(destination);
          return(*this);
      }
};

#endif // NMEA_0183_CLASS_HEADER
