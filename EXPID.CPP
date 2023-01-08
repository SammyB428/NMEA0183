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

std::string expand_talker_id( std::string_view identifier ) noexcept
{
   std::string expanded_identifier;

   auto first_character{ identifier[0] };
   auto second_character{ identifier[1] };

   /*
   ** Set up our default return value
   */

   expanded_identifier.assign(STRING_VIEW("Unknown - "));
   expanded_identifier.append(identifier);

   switch( first_character )
   {
      case 'A': // AG, AP

         switch( second_character )
         {
            case 'G': // AG

               expanded_identifier.assign(STRING_VIEW("Autopilot - General"));
               break;

            case 'P': // AP

               expanded_identifier.assign(STRING_VIEW("Autopilot - Magnetic"));
               break;
         }

         break;

      case 'C': // CD, CS, CT, CV, CX and CC,CM

         switch( second_character )
         {
            case 'C': // CC

               expanded_identifier.assign(STRING_VIEW("Commputer - Programmed Calculator (outdated)"));
               break;

            case 'D': // CD

               expanded_identifier.assign(STRING_VIEW("Communications - Digital Selective Calling (DSC)"));
               break;

            case 'M': // CM

               expanded_identifier.assign(STRING_VIEW("Computer - Memory Data (outdated)"));
               break;

            case 'S': // CS

               expanded_identifier.assign(STRING_VIEW("Communications - Satellite"));
               break;

            case 'T': // CT

               expanded_identifier.assign(STRING_VIEW("Communications - Radio-Telephone (MF/HF)"));
               break;

            case 'V': // CV

               expanded_identifier.assign(STRING_VIEW("Communications - Radio-Telephone (VHF)"));
               break;

            case 'X': // CX

               expanded_identifier.assign(STRING_VIEW("Communications - Scanning Receiver"));
               break;
         }

         break;

      case 'D': // DE, DF

         switch( second_character )
         {
            case 'E': // DE

               expanded_identifier.assign(STRING_VIEW("DECCA Navigation"));
               break;

            case 'F': // DF

               expanded_identifier.assign(STRING_VIEW("Direction Finder"));
               break;
         }

         break;

      case 'E': // EC, EP, ER

         switch( second_character )
         {
            case 'C': // EC

                expanded_identifier.assign(STRING_VIEW("Electronic Chart Display & Information System (ECDIS)"));
               break;

            case 'P': // EP

               expanded_identifier.assign(STRING_VIEW("Emergency Position Indicating Beacon (EPIRB)"));
               break;

            case 'R': // ER

               expanded_identifier.assign(STRING_VIEW("Engine Room Monitoring Systems"));
               break;
         }

         break;

      case 'G': // GP
 
         switch( second_character )
         {
            case 'P': // GP

               expanded_identifier.assign(STRING_VIEW("Global Positioning System (GPS)"));
               break;
         }

         break;

      case 'H': // HC, HE, HN
 
         switch( second_character )
         {
            case 'C': // HC

               expanded_identifier.assign(STRING_VIEW("Heading - Magnetic Compass"));
               break;

            case 'E': // HE

               expanded_identifier.assign(STRING_VIEW("Heading - North Seeking Gyro"));
               break;

            case 'N': // HN

               expanded_identifier.assign(STRING_VIEW("Heading - Non North Seeking Gyro"));
               break;
         }

         break;

      case 'I': // II, IN
 
         switch( second_character )
         {
            case 'I': // II

               expanded_identifier.assign(STRING_VIEW("Integrated Instrumentation"));
               break;

            case 'N': // IN

               expanded_identifier.assign(STRING_VIEW("Integrated Navigation"));
               break;
         }

         break;

      case 'L': // LA, LC
 
         switch( second_character )
         {
            case 'A': // LA

               expanded_identifier.assign(STRING_VIEW("Loran A"));
               break;

            case 'C': // LC

               expanded_identifier.assign(STRING_VIEW("Loran C"));
               break;
         }

         break;

      case 'M': // MP
 
         switch( second_character )
         {
            case 'P': // MP

               expanded_identifier.assign(STRING_VIEW("Microwave Positioning System (outdated)"));
               break;
         }

         break;

      case 'O': // OM, OS
 
         switch( second_character )
         {
            case 'M': // OM

               expanded_identifier.assign(STRING_VIEW("OMEGA Navigation System"));
               break;

            case 'S': // OS

               expanded_identifier.assign(STRING_VIEW("Distress Alarm System (outdated)"));
               break;
         }

         break;

      case 'P': // P
 
         break;

      case 'R': // RA
 
         switch( second_character )
         {
            case 'A': // RA

               expanded_identifier.assign(STRING_VIEW("RADAR and/or ARPA"));
               break;
         }

         break;

      case 'S': // SD, SN, SS
 
         switch( second_character )
         {
            case 'D': // SD

               expanded_identifier.assign(STRING_VIEW("Sounder, Depth"));
               break;

            case 'N': // SN

               expanded_identifier.assign(STRING_VIEW("Electronic Positioning System, other/general"));
               break;

            case 'S': // SS

               expanded_identifier.assign(STRING_VIEW("Sounder, Scanning"));
               break;
         }

         break;

      case 'T': // TI, TR
       
         switch( second_character )
         {
            case 'I': // TI

               expanded_identifier.assign(STRING_VIEW("Turn Rate Indicator"));
               break;

            case 'R': // TR

               expanded_identifier.assign(STRING_VIEW("TRANSIT Navigation System"));
               break;
         }

         break;

      case 'V': // VD, VM, VW
 
         switch( second_character )
         {
            case 'D': // VD

               expanded_identifier.assign(STRING_VIEW("Velocity Sensor, Doppler, other/general"));
               break;

            case 'M': // VM

               expanded_identifier.assign(STRING_VIEW("Velocity Sensor, Speed Log, Water, Magnetic"));
               break;

            case 'W': // VW

               expanded_identifier.assign(STRING_VIEW("Velocity Sensor, Speed Log, Water, Mechanical"));
               break;
         }

         break;


      case 'W': // WI
 
         switch( second_character )
         {
            case 'I': // WI

               expanded_identifier.assign(STRING_VIEW("Weather Instruments"));
               break;
         }

         break;

      case 'Y': // YC, YD, YF, YL, YP, YR, YT, YV, YX
 
         switch( second_character )
         {
            case 'C': // YC

               expanded_identifier.assign(STRING_VIEW("Transducer - Temperature (outdated)"));
               break;

            case 'D': // YD

               expanded_identifier.assign(STRING_VIEW("Transducer - Displacement, Angular or Linear (outdated)"));
               break;

            case 'F': // YF

               expanded_identifier.assign(STRING_VIEW("Transducer - Frequency (outdated)"));
               break;

            case 'L': // YL

               expanded_identifier.assign(STRING_VIEW("Transducer - Level (outdated)"));
               break;

            case 'P': // YP

               expanded_identifier.assign(STRING_VIEW("Transducer - Pressure (outdated)"));
               break;

            case 'R': // YR

               expanded_identifier.assign(STRING_VIEW("Transducer - Flow Rate (outdated)"));
               break;

            case 'T': // YT

               expanded_identifier.assign(STRING_VIEW("Transducer - Tachometer (outdated)"));
               break;

            case 'V': // YV

               expanded_identifier.assign(STRING_VIEW("Transducer - Volume (outdated)"));
               break;

            case 'X': // YX

               expanded_identifier.assign(STRING_VIEW("Transducer"));
               break;

         }

         break;

      case 'Z': // ZA, ZC, ZQ, ZV
 
         switch( second_character )
         {
            case 'A': // ZA

               expanded_identifier.assign(STRING_VIEW("Timekeeper - Atomic Clock"));
               break;

            case 'C': // ZC

               expanded_identifier.assign(STRING_VIEW("Timekeeper - Chronometer"));
               break;

            case 'Q': // ZQ

               expanded_identifier.assign(STRING_VIEW("Timekeeper - Quartz"));
               break;

            case 'V': // ZV

               expanded_identifier.assign(STRING_VIEW("Timekeeper - Radio Update, WWV or WWVH"));
               break;
         }

         break;
   }

   return( expanded_identifier );
}
