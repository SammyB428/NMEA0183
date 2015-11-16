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

#pragma comment( lib, "nmea0183.lib" )

/*
** This is the test scenario. Add more sentences to the list to test them
*/

class TestingFunctorinator // Dr. Doofenshmirtz naming convention
{
public:

    NMEA0183 nmea0183;

    // Now turn this mild mannered class into a functor!
    void operator () (std::string& item)
    { 
        nmea0183.SetSentence(item.c_str());

        if (nmea0183.Parse() != true)
        {
            std::string sentence;

            nmea0183.GetSentence(sentence);
            printf("\nCan't parse \"%s\"\n", (const char *)sentence.c_str());
            printf("Failed with \"%s\"\n", (const char *)nmea0183.ErrorMessage.c_str());
            printf("Last Sentence Received is \"%s\"\n", (const char *)nmea0183.LastSentenceIDReceived.c_str());
            printf("Last Sentence Parsed is   \"%s\"\n\n", (const char *)nmea0183.LastSentenceIDParsed.c_str());
        }
        else
        {
            printf("%s parsed OK from %s\n", (const char *)nmea0183.LastSentenceIDParsed.c_str(), (const char *)nmea0183.ExpandedTalkerID.c_str());

            if (nmea0183.PlainText.length() != 0)
            {
                printf("In plain English, %s\n", (const char *)nmea0183.PlainText.c_str());
            }
        }
    }
};

int main()
{
   std::vector<std::string> test_sentences;

   /*
   ** Load our test sentences and keep track of where they came from
   */
#if 1
   test_sentences.push_back("$PGRMM,NAD27 Canada*2F\r\n"); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$LCAAM,V,A,.15,N,CHAT-N6*56\r\n" ); // NMEA0183 document, pg 39
   test_sentences.push_back( "$GPAPB,A,A,0.0,R,N,V,V,86.8,T,001,86.9,T,86.9,T\r\n" ); // I can't remember
   test_sentences.push_back( "$GPAPB,A,A,0.0,R,N,V,V,86.8,T,001,86.9,T,86.9,T\r\n" ); // I can't remember
   test_sentences.push_back( "$GPBWC,104432.69,3337.36,N,11154.54,W,86.9,T,74.6,M,3.2,N,001\r\n" ); // I can't remember
   test_sentences.push_back( "$GPBWC,104435.12,3337.36,N,11154.54,W,86.9,T,74.6,M,3.2,N,001\r\n" ); // I can't remember
   test_sentences.push_back( "$GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*11\r\n" ); // pwyld@cix.compulink.co.uk ("Peter Wyld")
   test_sentences.push_back( "$GPBWC,225444,4917.24,N,12309.57,W,051.9,T,031.6,M,001.3,N,004*29\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$CTFSI,020230,026140,m,5*11\r\n" ); // NMEA0183 document, pg 41
   test_sentences.push_back( "$CDFSI,900016,,d,9*08\r\n" ); // NMEA0183 document, pg 41
   test_sentences.push_back( "$CTFSI,416193,,s,0*00\r\n" ); // NMEA0183 document, pg 41
   test_sentences.push_back( "$CXFSI,,021875,t,*3A\r\n" ); // NMEA0183 document, pg 41
   test_sentences.push_back( "$GPGGA,104435.12,3337.19,N,11158.43,W,1,06,4.5,,,,,,\r\n" ); // I can't remember
   test_sentences.push_back( "$GPGGA,104432.69,3337.19,N,11158.43,W,1,06,5.1,,,,,,\r\n" ); // I can't remember
   test_sentences.push_back( "$GPGLL,3337.190,N,11158.430,W,104432.686,A\r\n" ); // I can't remember
   test_sentences.push_back( "$GPGLL,3337.190,N,11158.430,W,104435.122,A\r\n" ); // I can't remember
   test_sentences.push_back( "$LCGLL,4728.31,N,12254.25,W,091342,A*21\r\n" ); // NMEA0183 document, pg 39
   test_sentences.push_back( "$GPGLL,4916.45,N,12311.12,W*71\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$GPGLL,5133.81,N,00042.25,W*75\r\n" ); // pwyld@cix.compulink.co.uk ("Peter Wyld")
   test_sentences.push_back( "$GPR00,MINST,CHATN,CHAT1,CHATW,CHATM,CHATE,003,004,005,006,007,,,*05\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$LCRMA,V,,,,,14162.8,,,,,*0D\r\n" ); // NMEA0183 document, pg 40
   test_sentences.push_back( "$LCRMA,V,,,,,14172.3,26026.7,,,,*2E\r\n" ); // NMEA0183 document, pg 40
   test_sentences.push_back( "$LCRMA,A,,,,,14182.3,26026.7,,,,*36\r\n" ); // NMEA0183 document, pg 40
   test_sentences.push_back( "$LCRMA,A,4226.26,N,07125.89,W,14182.3,26026.7,8.5,275.,14.0,W*68\r\n" ); // NMEA0183 document, pg 40
   test_sentences.push_back( "$LCRMA,V,4226.26,N,07125.89,W,14182.3,26026.7,8.5,275.,14.0,W*7F\r\n" ); // NMEA0183 document, pg 40
   test_sentences.push_back( "$LCRMA,A,4226.265,N,07125.890,W,14172.33,26026.71,8.53,275.,14.0,W*53\r\n" ); // NMEA0183 document, pg 40
   test_sentences.push_back( "$GPRMB,A,0.66,L,003,004,4917.24,N,12309.57,W,001.3,052.5,000.5,V*0B\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$GPRMB,A,4.08,L,EGLL,EGLM,5130.02,N,00046.34,W,004.6,213.9,122.9,A*3D\r\n" ); // pwyld@cix.compulink.co.uk ("Peter Wyld")
   test_sentences.push_back( "$GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70\r\n" ); // pwyld@cix.compulink.co.uk ("Peter Wyld")
   test_sentences.push_back( "$GPVTG,0.0,T,347.6,M,0.0,N,0.0,K\r\n" ); // I can't remember
   test_sentences.push_back( "$GPVTG,0.0,T,347.6,M,0.0,N,0.0,K\r\n" ); // I can't remember
   test_sentences.push_back( "$GPVTG,054.7,T,034.4,M,000.5,N,000.9,K*47\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$GPWPL,4917.16,N,12310.64,W,003*65\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$GPWPL,5128.62,N,00027.58,W,EGLL*59\r\n" ); // pwyld@cix.compulink.co.uk ("Peter Wyld")
   test_sentences.push_back( "$GPXTE,A,A,0.67,L,N*6F\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$GPXTE,A,A,4.07,L,N*6D\r\n" ); // pwyld@cix.compulink.co.uk ("Peter Wyld")
#endif
   test_sentences.push_back( "$GPGGA,103050,3912.073,N,07646.887,W,1,08,1.8,2.5,M,-34.0,M,,*72\r\n" ); // Me sitting at home with my Garmin 12XL
   
   /*
   ** Finish up with some proprietary sentences, just for giggles
   */

   test_sentences.push_back( "$PGRMZ,93,f,3*21\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$PGRMZ,201,f,3*18\r\n" ); // pwyld@cix.compulink.co.uk ("Peter Wyld")
   test_sentences.push_back( "$PSLIB,,,J*22\r\n" ); // Peter Bennett, bennett@triumf.ca
   test_sentences.push_back( "$PSRDA003[470738][1224523]??RST47,3809,A004*47\r\n" ); // NMEA0183 document, pg 40

   /*
   ** Now loop through the list and attempt to parse each sentence
   */

   TestingFunctorinator testerinator;

   std::for_each( test_sentences.begin(), test_sentences.end(), testerinator );

   return( EXIT_SUCCESS );
}
