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

MANUFACTURER_LIST::MANUFACTURER_LIST()
{
   ManufacturerTable.clear();
}

MANUFACTURER_LIST::~MANUFACTURER_LIST()
{
   Empty();
}

void MANUFACTURER_LIST::Empty( void )
{
    ManufacturerTable.clear();
}

static bool is_less_than(__in const MANUFACTURER& left, __in const MANUFACTURER& right)
{
    return(left.Mnemonic < right.Mnemonic);
}

void MANUFACTURER_LIST::Fill( void )
{
   ManufacturerTable.push_back( MANUFACTURER( "AAR", "Asian American Resources" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ACE", "Auto-Comm Engineering Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ACR", "ACR Electronics, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "ACS", "Arco Solar, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "ACT", "Advanced Control Technology" ) );
   ManufacturerTable.push_back( MANUFACTURER( "AGI", "Airguide Instrument Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "AHA", "Autohelm of America" ) );
   ManufacturerTable.push_back( MANUFACTURER( "AIP", "Aiphone Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ALD", "Alden Electronics, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "AMR", "AMR Systems" ) );
   ManufacturerTable.push_back( MANUFACTURER( "AMT", "Airmar Technology" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ANS", "Antenna Specialists" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ANX", "Analytyx Electronic Systems" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ANZ", "Anschutz of America" ) );
   ManufacturerTable.push_back( MANUFACTURER( "APC", "Apelco" ) );
   ManufacturerTable.push_back( MANUFACTURER( "APN", "American Pioneer, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "APX", "Amperex, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "AQC", "Aqua-Chem, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "AQD", "Aquadynamics, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "AQM", "Aqua Meter Instrument Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ASP", "American Solar Power" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ATE", "Aetna Engineering" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ATM", "Atlantic Marketing Company, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "ATR", "Airtron" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ATV", "Activation, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "AVN", "Advanced Navigation, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "AWA", "Awa New Zealand, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BBL", "BBL Industries, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "BBR", "BBR and Associates" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BDV", "Brisson Development, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "BEC", "Boat Electric Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BGS", "Barringer Geoservice" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BGT", "Brookes and Gatehouse, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "BHE", "BH Electronics" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BHR", "Bahr Technologies, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "BLB", "Bay Laboratories" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BMC", "BMC" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BME", "Bartel Marine Electronics" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BNI", "Neil Brown Instrument Systems" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BNS", "Bowditch Navigation Systems" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BRM", "Mel Barr Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BRY", "Byrd Industries" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BTH", "Benthos, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "BTK", "Baltek Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "BTS", "Boat Sentry, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "BXA", "Bendix-Avalex, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CAT", "Catel" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CBN", "Cybernet Marine Products" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CCA", "Copal Corporation of America" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CCC", "Coastal Communications Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CCL", "Coastal Climate Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CCM", "Coastal Communications" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CDC", "Cordic Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CEC", "Ceco Communications, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CHI", "Charles Industries, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CKM", "Cinkel Marine Electronics Industries" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CMA", "Societe Nouvelle D'Equiment du Calvados" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CMC", "Coe Manufacturing Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CME", "Cushman Electronics, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CMP", "C-Map, s.r.l." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CMS", "Coastal Marine Sales Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CMV", "CourseMaster USA, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CNV", "Coastal Navigator" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CNX", "Cynex Manufactoring Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CPL", "Computrol, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CPN", "Compunav" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CPS", "Columbus Positioning, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CPT", "CPT, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CRE", "Crystal Electronics, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CRO", "The Caro Group" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CRY", "Crystek Crystals Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CSM", "Comsat Maritime Services" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CST", "Cast, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CSV", "Combined Services" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CTA", "Current Alternatives" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CTB", "Cetec Benmar" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CTC", "Cell-tech Communications" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CTE", "Castle Electronics" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CTL", "C-Tech, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CNI", "Continental Instruments" ) ); // Possible error in NMEA0183 docs
   ManufacturerTable.push_back( MANUFACTURER( "CWD", "Cubic Western Data" ) );
   ManufacturerTable.push_back( MANUFACTURER( "CWV", "Celwave R.F., Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "CYZ", "cYz, Incorporated" ) );
   ManufacturerTable.push_back( MANUFACTURER( "DCC", "Dolphin Components Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "DEB", "Debeg Gmbh" ) );
   ManufacturerTable.push_back( MANUFACTURER( "DFI", "Defender Industries, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "DGC", "Digicourse, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "DME", "Digital Marine Electronics Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "DMI", "Datamarine International, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "DNS", "Dornier System Gmbh" ) );
   ManufacturerTable.push_back( MANUFACTURER( "DNT", "Del Norte Technology, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "DPS", "Danaplus, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "DRL", "R.L. Drake Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "DSC", "Dynascan Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "DYN", "Dynamote Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "DYT", "Dytek Laboratories, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "EBC", "Emergency Beacon, Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ECT", "Echotec, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "EEV", "EEV, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "EFC", "Efcom Communication Systems" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ELD", "Electronic Devices, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "EMC", "Electric Motion Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "EMS", "Electro Marine Systems, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "ENA", "Energy Analysts, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "ENC", "Encron, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "EPM", "Epsco Marine" ) );
   ManufacturerTable.push_back( MANUFACTURER( "EPT", "Eastprint, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "ERC", "The Ericsson Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ESA", "European Space Agency" ) );
   ManufacturerTable.push_back( MANUFACTURER( "FDN", "Fluiddyne" ) );
   ManufacturerTable.push_back( MANUFACTURER( "FHE", "Fish Hawk Electronics" ) );
   ManufacturerTable.push_back( MANUFACTURER( "FJN", "Jon Fluke Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "FMM", "First Mate Marine Autopilots" ) );
   ManufacturerTable.push_back( MANUFACTURER( "FNT", "Franklin Net and Twine, Limited" ) ); // Compiler Die Here
   ManufacturerTable.push_back( MANUFACTURER( "FRC", "The Fredericks Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "FTG", "T.G. Faria Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "FUJ", "Fujitsu Ten Corporation of America" ) );
   ManufacturerTable.push_back( MANUFACTURER( "FEC", "Furuno Electric Company" ) ); // Possible NMEA document error
   ManufacturerTable.push_back( MANUFACTURER( "FUR", "Furuno, USA Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "GAM", "GRE America, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "GCA", "Gulf Cellular Associates" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GES", "Geostar Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GFC", "Graphic Controls, Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GIS", "Galax Integrated Systems" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GPI", "Global Positioning Instrument Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GRM", "Garmin Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GSC", "Gold Star Company, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GTO", "Gro Electronics" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GVE", "Guest Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "GVT", "Great Valley Technology" ) );
   ManufacturerTable.push_back( MANUFACTURER( "HAL", "HAL Communications Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "HAR", "Harris Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "HIG", "Hy-Gain" ) );
   ManufacturerTable.push_back( MANUFACTURER( "HIT", "Hi-Tec" ) );
   ManufacturerTable.push_back( MANUFACTURER( "HPK", "Hewlett-Packard" ) );
   ManufacturerTable.push_back( MANUFACTURER( "HRC", "Harco Manufacturing Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "HRT", "Hart Systems, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "HTI", "Heart Interface, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "HUL", "Hull Electronics Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "HWM", "Honeywell Marine Systems" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ICO", "Icom of America, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "IFD", "International Fishing Devices" ) );
   ManufacturerTable.push_back( MANUFACTURER( "IFI", "Instruments for Industry" ) );
   ManufacturerTable.push_back( MANUFACTURER( "IME", "Imperial Marine Equipment" ) );
   ManufacturerTable.push_back( MANUFACTURER( "IMI", "I.M.I." ) );
   ManufacturerTable.push_back( MANUFACTURER( "IMM", "ITT MacKay Marine" ) );
   ManufacturerTable.push_back( MANUFACTURER( "IMP", "Impulse Manufacturing, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "IMT", "International Marketing and Trading, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "INM", "Inmar Electronic and Sales, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "INT", "Intech, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "IRT", "Intera Technologies, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "IST", "Innerspace Technology, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "ITM", "Intermarine Electronics, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "ITR", "Itera, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "JAN", "Jan Crystals" ) );
   ManufacturerTable.push_back( MANUFACTURER( "JFR", "Ray Jefferson" ) );
   ManufacturerTable.push_back( MANUFACTURER( "JMT", "Japan Marine Telecommunications" ) );
   ManufacturerTable.push_back( MANUFACTURER( "JRC", "Japan Radio Company, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "JRI", "J-R Industries, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "JTC", "J-Tech Associates, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "JTR", "Jotron Radiosearch, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "KBE", "KB Electronics, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "KBM", "Kennebec Marine Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "KLA", "Klein Associates, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "KMR", "King Marine Radio Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "KNG", "King Radio Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "KOD", "Koden Electronics Company, Limited" ) );
   ManufacturerTable.push_back( MANUFACTURER( "KRP", "Krupp International, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "KVH", "KVH Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "KYI", "Kyocera International, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "LAT", "Latitude Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "LEC", "Lorain Electronics Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "LMM", "Lamarche Manufacturing Company" ) );
   ManufacturerTable.push_back( MANUFACTURER( "LRD", "Lorad" ) );
   ManufacturerTable.push_back( MANUFACTURER( "LSE", "Littlemore Scientific Engineering" ) );
   ManufacturerTable.push_back( MANUFACTURER( "LSP", "Laser Plot, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "LTF", "Littlefuse, Inc." ) );
   ManufacturerTable.push_back( MANUFACTURER( "LWR", "Lowrance Electronics Corportation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "MCL", "Micrologic, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MDL", "Medallion Instruments, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MEC", "Marine Engine Center, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MEG", "Maritec Engineering GmbH" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MFR", "Modern Products, Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MFW", "Frank W. Murphy Manufacturing" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MGM", "Magellan Systems Corporation" ) ); // Thanks to Chuck Shannon, cshannon@imtn.tpd.dsccc.com
   ManufacturerTable.push_back( MANUFACTURER( "MGS", "MG Electronic Sales Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MIE", "Mieco, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MIM", "Marconi International Marine Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MLE", "Martha Lake Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MLN", "Matlin Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MLP", "Marlin Products" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MLT", "Miller Technologies" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MMB", "Marsh-McBirney, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MME", "Marks Marine Engineering" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MMP", "Metal Marine Pilot, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MMS", "Mars Marine Systems" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MNI", "Micro-Now Instrument Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MNT", "Marine Technology" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MNX", "Marinex" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MOT", "Motorola Communications and Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MPN", "Memphis Net and Twine Company, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MQS", "Marquis Industries, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MRC", "Marinecomp, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MRE", "Morad Electronics Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MRP", "Mooring Products of New England" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MRR", "II Morrow, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MRS", "Marine Radio Service" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MSB", "Mitsubishi Electric Company, Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MSE", "Master Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MSM", "Master Mariner, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MST", "Mesotech Systems, Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MTA", "Marine Technical Associates" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MTG", "Narine Technical Assistance Group" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MTK", "Martech, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MTR", "Mitre Corporation, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MTS", "Mets, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MUR", "Murata Erie North America" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MVX", "Magnavox Advanced Products and Systems Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MXX", "Maxxima Marine" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "MES", "Marine Electronics Service, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NAT", "Nautech, Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NEF", "New England Fishing Gear, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NMR", "Newmar" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NGS", "Navigation Sciences, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NOM", "Nav-Com, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NOV", "NovAtel Communications, Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NSM", "Northstar Marine" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NTK", "Novatech Designs, Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NVC", "Navico" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NVS", "Navstar" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "NVO", "Navionics, s.p.a." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "OAR", "O.A.R. Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "ODE", "Ocean Data Equipment Corporation" ) );
   ManufacturerTable.push_back( MANUFACTURER( "ODN", "Odin Electronics, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "OIN", "Ocean instruments, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "OKI", "Oki Electronic Industry Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "OLY", "Navstar Limited (Polytechnic Electronics)" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "OMN", "Omnetics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "ORE", "Ocean Research" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "OTK", "Ocean Technology" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PCE", "Pace" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PDM", "Prodelco Marine Systems" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PLA", "Plath, C. Division of Litton" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PLI", "Pilot Instruments" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PMI", "Pernicka Marine Products" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PMP", "Pacific Marine Products" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PRK", "Perko, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PSM", "Pearce-Simpson" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PTC", "Petro-Com" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PTG", "P.T.I./Guest" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "PTH", "Pathcom, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RAC", "Racal Marine, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RAE", "RCA Astro-Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RAY", "Raytheon Marine Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RCA", "RCA Service Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RCH", "Roach Engineering" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RCI", "Rochester Instruments, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RDI", "Radar Devices" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RDM", "Ray-Dar Manufacturing Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "REC", "Ross Engineering Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RFP", "Rolfite Products, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RGC", "RCS Global Communications, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RGY", "Regency Electronics, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RMR", "RCA Missile and Surface Radar" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RSL", "Ross Laboratories, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RSM", "Robertson-Shipmate, USA" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RWI", "Rockwell International" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RME", "Racal Marine Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "RTN", "Robertson Tritech Nyaskaien A/S" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SAI", "SAIT, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SBR", "Sea-Bird electronics, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SCR", "Signalcrafters, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SEA", "SEA" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SEC", "Sercel Electronics of Canada" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SEP", "Steel and Engine Products, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SFN", "Seafarer Navigation International, Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SGC", "SGC, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SIG", "Signet, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SIM", "Simrad,Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SKA", "Skantek Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SKP", "Skipper Electronics A/S" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SME", "Shakespeare Marine Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SMF", "Seattle Marine and Fishing Supply Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SML", "Simerl Instruments" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SMI", "Sperry Marine, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SNV", "Starnav Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SOM", "Sound Marine Electronics, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SOV", "Sell Overseas America" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SPL", "Spelmar" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SPT", "Sound Powered Telephone" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SRD", "SRD Labs" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SRS", "Scientific Radio Systems, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SRT", "Standard Radio and Telefon AB" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SSI", "Sea Scout Industries" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "STC", "Standard Communications" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "STI", "Sea-Temp Instrument Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "STM", "Si-Tex Marine Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SVY", "Savoy Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SWI", "Swoffer Marine Instruments, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "SRS", "Shipmate, Rauff & Sorensen, A/S" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TBB", "Thompson Brothers Boat Manufacturing Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TCN", "Trade Commission of Norway (THE)" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TDL", "Tideland Signal" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "THR", "Thrane and Thrane A/A" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TLS", "Telesystems" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TMT", "Tamtech, Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TNL", "Trimble Navigation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TRC", "Tracor, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TSI", "Techsonic Industries, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TTK", "Talon Technology Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TTS", "Transtector Systems" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TWC", "Transworld Communications, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "TXI", "Texas Instruments, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "UME", "Umec" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "UNI", "Uniden Corporation of America" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "UNP", "Unipas, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "UNF", "Uniforce Electronics Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "VAN", "Vanner, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "VAR", "Varian Eimac Associates" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "VCM", "Videocom" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "VEX", "Vexillar" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "VIS", "Vessel Information Systems, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "VMR", "Vast Marketing Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WAL", "Walport USA" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WBG", "Westberg Manufacturing, Inc." ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WEC", "Westinghouse electric Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WHA", "W-H Autopilots" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WMM", "Wait Manufacturing and Marine Sales Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WMR", "Wesmar Electronics" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WNG", "Winegard Company" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WSE", "Wilson Electronics Corporation" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WTC", "Watercom" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "WST", "West Electronics Limited" ) ); 
   ManufacturerTable.push_back( MANUFACTURER( "YAS", "Yaesu Electronics" ) ); 

   std::sort(ManufacturerTable.begin(), ManufacturerTable.end(), is_less_than);
}

const std::string& MANUFACTURER_LIST::Find( const std::string& mnemonic )
{
   static std::string return_value;

   return_value.clear();

   /*
   ** Check to see if the list has been filled
   */

   if ( ManufacturerTable.size() == 0 )
   {
      Fill();
   }

   MANUFACTURER needle(mnemonic.c_str(), "");

   std::vector<MANUFACTURER>::iterator iterator = std::lower_bound(ManufacturerTable.begin(), ManufacturerTable.end(), needle, is_less_than);

   if (iterator != ManufacturerTable.end() && iterator->Mnemonic.compare( mnemonic ) == 0)
   {
       return_value = iterator->CompanyName;
   }

   return( return_value );
}

const std::string& MANUFACTURER_LIST::operator [] ( const char *mnemonic )
{
   return( Find( mnemonic ) );
}
