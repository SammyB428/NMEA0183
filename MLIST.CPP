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

// SPDX-License-Identifier: MIT

#include "nmea0183.h"
#pragma hdrstop

void MANUFACTURER_LIST::Empty( void ) noexcept
{
    ManufacturerTable.clear();
}

static bool is_less_than(MANUFACTURER const& left, MANUFACTURER const& right) noexcept
{
    return(left.Mnemonic < right.Mnemonic);
}

void MANUFACTURER_LIST::Fill( void ) noexcept
{
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AAR"), STRING_VIEW("Asian American Resources")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ACE"), STRING_VIEW("Auto-Comm Engineering Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ACR"), STRING_VIEW("ACR Electronics, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ACS"), STRING_VIEW("Arco Solar, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ACT"), STRING_VIEW("Advanced Control Technology")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AGI"), STRING_VIEW("Airguide Instrument Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AHA"), STRING_VIEW("Autohelm of America")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AIP"), STRING_VIEW("Aiphone Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ALD"), STRING_VIEW("Alden Electronics, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AMR"), STRING_VIEW("AMR Systems")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AMT"), STRING_VIEW("Airmar Technology")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ANS"), STRING_VIEW("Antenna Specialists")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ANX"), STRING_VIEW("Analytyx Electronic Systems")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ANZ"), STRING_VIEW("Anschutz of America")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("APC"), STRING_VIEW("Apelco")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("APN"), STRING_VIEW("American Pioneer, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("APX"), STRING_VIEW("Amperex, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AQC"), STRING_VIEW("Aqua-Chem, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AQD"), STRING_VIEW("Aquadynamics, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AQM"), STRING_VIEW("Aqua Meter Instrument Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ASP"), STRING_VIEW("American Solar Power")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ATE"), STRING_VIEW("Aetna Engineering")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ATM"), STRING_VIEW("Atlantic Marketing Company, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ATR"), STRING_VIEW("Airtron")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ATV"), STRING_VIEW("Activation, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AVN"), STRING_VIEW("Advanced Navigation, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("AWA"), STRING_VIEW("Awa New Zealand, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BBL"), STRING_VIEW("BBL Industries, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BBR"), STRING_VIEW("BBR and Associates")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BDV"), STRING_VIEW("Brisson Development, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BEC"), STRING_VIEW("Boat Electric Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BGS"), STRING_VIEW("Barringer Geoservice")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BGT"), STRING_VIEW("Brookes and Gatehouse, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BHE"), STRING_VIEW("BH Electronics")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BHR"), STRING_VIEW("Bahr Technologies, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BLB"), STRING_VIEW("Bay Laboratories")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BMC"), STRING_VIEW("BMC")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BME"), STRING_VIEW("Bartel Marine Electronics")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BNI"), STRING_VIEW("Neil Brown Instrument Systems")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BNS"), STRING_VIEW("Bowditch Navigation Systems")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BRM"), STRING_VIEW("Mel Barr Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BRY"), STRING_VIEW("Byrd Industries")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BTH"), STRING_VIEW("Benthos, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BTK"), STRING_VIEW("Baltek Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BTS"), STRING_VIEW("Boat Sentry, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("BXA"), STRING_VIEW("Bendix-Avalex, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CAT"), STRING_VIEW("Catel")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CBN"), STRING_VIEW("Cybernet Marine Products")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CCA"), STRING_VIEW("Copal Corporation of America")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CCC"), STRING_VIEW("Coastal Communications Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CCL"), STRING_VIEW("Coastal Climate Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CCM"), STRING_VIEW("Coastal Communications")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CDC"), STRING_VIEW("Cordic Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CEC"), STRING_VIEW("Ceco Communications, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CHI"), STRING_VIEW("Charles Industries, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CKM"), STRING_VIEW("Cinkel Marine Electronics Industries")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CMA"), STRING_VIEW("Societe Nouvelle D'Equiment du Calvados")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CMC"), STRING_VIEW("Coe Manufacturing Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CME"), STRING_VIEW("Cushman Electronics, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CMP"), STRING_VIEW("C-Map, s.r.l.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CMS"), STRING_VIEW("Coastal Marine Sales Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CMV"), STRING_VIEW("CourseMaster USA, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CNV"), STRING_VIEW("Coastal Navigator")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CNX"), STRING_VIEW("Cynex Manufactoring Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CPL"), STRING_VIEW("Computrol, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CPN"), STRING_VIEW("Compunav")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CPS"), STRING_VIEW("Columbus Positioning, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CPT"), STRING_VIEW("CPT, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CRE"), STRING_VIEW("Crystal Electronics, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CRO"), STRING_VIEW("The Caro Group")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CRY"), STRING_VIEW("Crystek Crystals Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CSM"), STRING_VIEW("Comsat Maritime Services")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CST"), STRING_VIEW("Cast, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CSV"), STRING_VIEW("Combined Services")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CTA"), STRING_VIEW("Current Alternatives")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CTB"), STRING_VIEW("Cetec Benmar")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CTC"), STRING_VIEW("Cell-tech Communications")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CTE"), STRING_VIEW("Castle Electronics")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CTL"), STRING_VIEW("C-Tech, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CNI"), STRING_VIEW("Continental Instruments"))); // Possible error in NMEA0183 docs
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CWD"), STRING_VIEW("Cubic Western Data")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CWV"), STRING_VIEW("Celwave R.F., Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("CYZ"), STRING_VIEW("cYz, Incorporated")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DCC"), STRING_VIEW("Dolphin Components Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DEB"), STRING_VIEW("Debeg Gmbh")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DFI"), STRING_VIEW("Defender Industries, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DGC"), STRING_VIEW("Digicourse, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DME"), STRING_VIEW("Digital Marine Electronics Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DMI"), STRING_VIEW("Datamarine International, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DNS"), STRING_VIEW("Dornier System Gmbh")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DNT"), STRING_VIEW("Del Norte Technology, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DPS"), STRING_VIEW("Danaplus, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DRL"), STRING_VIEW("R.L. Drake Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DSC"), STRING_VIEW("Dynascan Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DYN"), STRING_VIEW("Dynamote Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("DYT"), STRING_VIEW("Dytek Laboratories, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("EBC"), STRING_VIEW("Emergency Beacon, Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ECT"), STRING_VIEW("Echotec, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("EEV"), STRING_VIEW("EEV, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("EFC"), STRING_VIEW("Efcom Communication Systems")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ELD"), STRING_VIEW("Electronic Devices, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("EMC"), STRING_VIEW("Electric Motion Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("EMS"), STRING_VIEW("Electro Marine Systems, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ENA"), STRING_VIEW("Energy Analysts, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ENC"), STRING_VIEW("Encron, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("EPM"), STRING_VIEW("Epsco Marine")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("EPT"), STRING_VIEW("Eastprint, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ERC"), STRING_VIEW("The Ericsson Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ESA"), STRING_VIEW("European Space Agency")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FDN"), STRING_VIEW("Fluiddyne")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FHE"), STRING_VIEW("Fish Hawk Electronics")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FJN"), STRING_VIEW("Jon Fluke Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FMM"), STRING_VIEW("First Mate Marine Autopilots")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FNT"), STRING_VIEW("Franklin Net and Twine, Limited"))); // Compiler Die Here
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FRC"), STRING_VIEW("The Fredericks Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FTG"), STRING_VIEW("T.G. Faria Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FUJ"), STRING_VIEW("Fujitsu Ten Corporation of America")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FEC"), STRING_VIEW("Furuno Electric Company"))); // Possible NMEA document error
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("FUR"), STRING_VIEW("Furuno, USA Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GAM"), STRING_VIEW("GRE America, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GCA"), STRING_VIEW("Gulf Cellular Associates")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GES"), STRING_VIEW("Geostar Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GFC"), STRING_VIEW("Graphic Controls, Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GIS"), STRING_VIEW("Galax Integrated Systems")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GPI"), STRING_VIEW("Global Positioning Instrument Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GRM"), STRING_VIEW("Garmin Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GSC"), STRING_VIEW("Gold Star Company, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GTO"), STRING_VIEW("Gro Electronics")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GVE"), STRING_VIEW("Guest Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("GVT"), STRING_VIEW("Great Valley Technology")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HAL"), STRING_VIEW("HAL Communications Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HAR"), STRING_VIEW("Harris Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HIG"), STRING_VIEW("Hy-Gain")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HIT"), STRING_VIEW("Hi-Tec")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HPK"), STRING_VIEW("Hewlett-Packard")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HRC"), STRING_VIEW("Harco Manufacturing Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HRT"), STRING_VIEW("Hart Systems, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HTI"), STRING_VIEW("Heart Interface, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HUL"), STRING_VIEW("Hull Electronics Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("HWM"), STRING_VIEW("Honeywell Marine Systems")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ICO"), STRING_VIEW("Icom of America, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IFD"), STRING_VIEW("International Fishing Devices")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IFI"), STRING_VIEW("Instruments for Industry")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IME"), STRING_VIEW("Imperial Marine Equipment")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IMI"), STRING_VIEW("I.M.I.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IMM"), STRING_VIEW("ITT MacKay Marine")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IMP"), STRING_VIEW("Impulse Manufacturing, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IMT"), STRING_VIEW("International Marketing and Trading, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("INM"), STRING_VIEW("Inmar Electronic and Sales, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("INT"), STRING_VIEW("Intech, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IRT"), STRING_VIEW("Intera Technologies, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("IST"), STRING_VIEW("Innerspace Technology, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ITM"), STRING_VIEW("Intermarine Electronics, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ITR"), STRING_VIEW("Itera, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("JAN"), STRING_VIEW("Jan Crystals")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("JFR"), STRING_VIEW("Ray Jefferson")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("JMT"), STRING_VIEW("Japan Marine Telecommunications")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("JRC"), STRING_VIEW("Japan Radio Company, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("JRI"), STRING_VIEW("J-R Industries, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("JTC"), STRING_VIEW("J-Tech Associates, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("JTR"), STRING_VIEW("Jotron Radiosearch, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KBE"), STRING_VIEW("KB Electronics, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KBM"), STRING_VIEW("Kennebec Marine Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KLA"), STRING_VIEW("Klein Associates, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KMR"), STRING_VIEW("King Marine Radio Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KNG"), STRING_VIEW("King Radio Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KOD"), STRING_VIEW("Koden Electronics Company, Limited")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KRP"), STRING_VIEW("Krupp International, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KVH"), STRING_VIEW("KVH Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("KYI"), STRING_VIEW("Kyocera International, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("LAT"), STRING_VIEW("Latitude Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("LEC"), STRING_VIEW("Lorain Electronics Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("LMM"), STRING_VIEW("Lamarche Manufacturing Company")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("LRD"), STRING_VIEW("Lorad")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("LSE"), STRING_VIEW("Littlemore Scientific Engineering")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("LSP"), STRING_VIEW("Laser Plot, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("LTF"), STRING_VIEW("Littlefuse, Inc.")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("LWR"), STRING_VIEW("Lowrance Electronics Corportation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MCL"), STRING_VIEW("Micrologic, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MDL"), STRING_VIEW("Medallion Instruments, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MEC"), STRING_VIEW("Marine Engine Center, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MEG"), STRING_VIEW("Maritec Engineering GmbH"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MFR"), STRING_VIEW("Modern Products, Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MFW"), STRING_VIEW("Frank W. Murphy Manufacturing"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MGM"), STRING_VIEW("Magellan Systems Corporation"))); // Thanks to Chuck Shannon, cshannon@imtn.tpd.dsccc.com
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MGS"), STRING_VIEW("MG Electronic Sales Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MIE"), STRING_VIEW("Mieco, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MIM"), STRING_VIEW("Marconi International Marine Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MLE"), STRING_VIEW("Martha Lake Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MLN"), STRING_VIEW("Matlin Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MLP"), STRING_VIEW("Marlin Products"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MLT"), STRING_VIEW("Miller Technologies"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MMB"), STRING_VIEW("Marsh-McBirney, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MME"), STRING_VIEW("Marks Marine Engineering"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MMP"), STRING_VIEW("Metal Marine Pilot, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MMS"), STRING_VIEW("Mars Marine Systems"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MNI"), STRING_VIEW("Micro-Now Instrument Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MNT"), STRING_VIEW("Marine Technology"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MNX"), STRING_VIEW("Marinex"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MOT"), STRING_VIEW("Motorola Communications and Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MPN"), STRING_VIEW("Memphis Net and Twine Company, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MQS"), STRING_VIEW("Marquis Industries, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MRC"), STRING_VIEW("Marinecomp, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MRE"), STRING_VIEW("Morad Electronics Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MRP"), STRING_VIEW("Mooring Products of New England"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MRR"), STRING_VIEW("II Morrow, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MRS"), STRING_VIEW("Marine Radio Service"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MSB"), STRING_VIEW("Mitsubishi Electric Company, Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MSE"), STRING_VIEW("Master Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MSM"), STRING_VIEW("Master Mariner, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MST"), STRING_VIEW("Mesotech Systems, Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MTA"), STRING_VIEW("Marine Technical Associates"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MTG"), STRING_VIEW("Narine Technical Assistance Group"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MTK"), STRING_VIEW("Martech, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MTR"), STRING_VIEW("Mitre Corporation, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MTS"), STRING_VIEW("Mets, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MUR"), STRING_VIEW("Murata Erie North America"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MVX"), STRING_VIEW("Magnavox Advanced Products and Systems Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MXX"), STRING_VIEW("Maxxima Marine"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("MES"), STRING_VIEW("Marine Electronics Service, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NAT"), STRING_VIEW("Nautech, Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NEF"), STRING_VIEW("New England Fishing Gear, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NMR"), STRING_VIEW("Newmar"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NGS"), STRING_VIEW("Navigation Sciences, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NOM"), STRING_VIEW("Nav-Com, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NOV"), STRING_VIEW("NovAtel Communications, Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NSM"), STRING_VIEW("Northstar Marine"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NTK"), STRING_VIEW("Novatech Designs, Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NVC"), STRING_VIEW("Navico"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NVS"), STRING_VIEW("Navstar"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("NVO"), STRING_VIEW("Navionics, s.p.a."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("OAR"), STRING_VIEW("O.A.R. Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ODE"), STRING_VIEW("Ocean Data Equipment Corporation")));
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ODN"), STRING_VIEW("Odin Electronics, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("OIN"), STRING_VIEW("Ocean instruments, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("OKI"), STRING_VIEW("Oki Electronic Industry Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("OLY"), STRING_VIEW("Navstar Limited (Polytechnic Electronics)"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("OMN"), STRING_VIEW("Omnetics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("ORE"), STRING_VIEW("Ocean Research"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("OTK"), STRING_VIEW("Ocean Technology"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PCE"), STRING_VIEW("Pace"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PDM"), STRING_VIEW("Prodelco Marine Systems"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PLA"), STRING_VIEW("Plath, C. Division of Litton"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PLI"), STRING_VIEW("Pilot Instruments"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PMI"), STRING_VIEW("Pernicka Marine Products"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PMP"), STRING_VIEW("Pacific Marine Products"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PRK"), STRING_VIEW("Perko, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PSM"), STRING_VIEW("Pearce-Simpson"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PTC"), STRING_VIEW("Petro-Com"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PTG"), STRING_VIEW("P.T.I./Guest"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("PTH"), STRING_VIEW("Pathcom, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RAC"), STRING_VIEW("Racal Marine, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RAE"), STRING_VIEW("RCA Astro-Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RAY"), STRING_VIEW("Raytheon Marine Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RCA"), STRING_VIEW("RCA Service Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RCH"), STRING_VIEW("Roach Engineering"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RCI"), STRING_VIEW("Rochester Instruments, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RDI"), STRING_VIEW("Radar Devices"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RDM"), STRING_VIEW("Ray-Dar Manufacturing Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("REC"), STRING_VIEW("Ross Engineering Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RFP"), STRING_VIEW("Rolfite Products, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RGC"), STRING_VIEW("RCS Global Communications, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RGY"), STRING_VIEW("Regency Electronics, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RMR"), STRING_VIEW("RCA Missile and Surface Radar"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RSL"), STRING_VIEW("Ross Laboratories, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RSM"), STRING_VIEW("Robertson-Shipmate, USA"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RWI"), STRING_VIEW("Rockwell International"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RME"), STRING_VIEW("Racal Marine Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("RTN"), STRING_VIEW("Robertson Tritech Nyaskaien A/S"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SAI"), STRING_VIEW("SAIT, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SBR"), STRING_VIEW("Sea-Bird electronics, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SCR"), STRING_VIEW("Signalcrafters, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SEA"), STRING_VIEW("SEA"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SEC"), STRING_VIEW("Sercel Electronics of Canada"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SEP"), STRING_VIEW("Steel and Engine Products, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SFN"), STRING_VIEW("Seafarer Navigation International, Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SGC"), STRING_VIEW("SGC, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SIG"), STRING_VIEW("Signet, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SIM"), STRING_VIEW("Simrad,Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SKA"), STRING_VIEW("Skantek Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SKP"), STRING_VIEW("Skipper Electronics A/S"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SME"), STRING_VIEW("Shakespeare Marine Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SMF"), STRING_VIEW("Seattle Marine and Fishing Supply Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SML"), STRING_VIEW("Simerl Instruments"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SMI"), STRING_VIEW("Sperry Marine, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SNV"), STRING_VIEW("Starnav Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SOM"), STRING_VIEW("Sound Marine Electronics, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SOV"), STRING_VIEW("Sell Overseas America"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SPL"), STRING_VIEW("Spelmar"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SPT"), STRING_VIEW("Sound Powered Telephone"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SRD"), STRING_VIEW("SRD Labs"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SRS"), STRING_VIEW("Scientific Radio Systems, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SRT"), STRING_VIEW("Standard Radio and Telefon AB"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SSI"), STRING_VIEW("Sea Scout Industries"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("STC"), STRING_VIEW("Standard Communications"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("STI"), STRING_VIEW("Sea-Temp Instrument Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("STM"), STRING_VIEW("Si-Tex Marine Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SVY"), STRING_VIEW("Savoy Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SWI"), STRING_VIEW("Swoffer Marine Instruments, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("SRS"), STRING_VIEW("Shipmate, Rauff & Sorensen, A/S"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TBB"), STRING_VIEW("Thompson Brothers Boat Manufacturing Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TCN"), STRING_VIEW("Trade Commission of Norway (THE)"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TDL"), STRING_VIEW("Tideland Signal"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("THR"), STRING_VIEW("Thrane and Thrane A/A"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TLS"), STRING_VIEW("Telesystems"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TMT"), STRING_VIEW("Tamtech, Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TNL"), STRING_VIEW("Trimble Navigation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TRC"), STRING_VIEW("Tracor, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TSI"), STRING_VIEW("Techsonic Industries, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TTK"), STRING_VIEW("Talon Technology Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TTS"), STRING_VIEW("Transtector Systems"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TWC"), STRING_VIEW("Transworld Communications, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("TXI"), STRING_VIEW("Texas Instruments, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("UME"), STRING_VIEW("Umec"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("UNI"), STRING_VIEW("Uniden Corporation of America"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("UNP"), STRING_VIEW("Unipas, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("UNF"), STRING_VIEW("Uniforce Electronics Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("VAN"), STRING_VIEW("Vanner, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("VAR"), STRING_VIEW("Varian Eimac Associates"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("VCM"), STRING_VIEW("Videocom"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("VEX"), STRING_VIEW("Vexillar"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("VIS"), STRING_VIEW("Vessel Information Systems, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("VMR"), STRING_VIEW("Vast Marketing Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WAL"), STRING_VIEW("Walport USA"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WBG"), STRING_VIEW("Westberg Manufacturing, Inc."))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WEC"), STRING_VIEW("Westinghouse electric Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WHA"), STRING_VIEW("W-H Autopilots"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WMM"), STRING_VIEW("Wait Manufacturing and Marine Sales Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WMR"), STRING_VIEW("Wesmar Electronics"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WNG"), STRING_VIEW("Winegard Company"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WSE"), STRING_VIEW("Wilson Electronics Corporation"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WTC"), STRING_VIEW("Watercom"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("WST"), STRING_VIEW("West Electronics Limited"))); 
   ManufacturerTable.push_back(MANUFACTURER(STRING_VIEW("YAS"), STRING_VIEW("Yaesu Electronics"))); 

   std::sort(std::begin(ManufacturerTable), std::end(ManufacturerTable), is_less_than);
}

std::string const& MANUFACTURER_LIST::Find( std::string_view mnemonic ) noexcept
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

   MANUFACTURER needle(mnemonic, STRING_VIEW(""));

   auto iterator{ std::lower_bound(std::cbegin(ManufacturerTable), std::cend(ManufacturerTable), needle, is_less_than) };

   if (iterator not_eq std::cend(ManufacturerTable) and iterator->Mnemonic.compare( mnemonic ) == 0)
   {
       return_value = iterator->CompanyName;
   }

   return( return_value );
}

std::string const& MANUFACTURER_LIST::operator [] ( std::string_view mnemonic ) noexcept
{
   return( Find( mnemonic ) );
}
