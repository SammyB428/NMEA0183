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

#include "../nmea0183.h"
#pragma hdrstop

#if defined( _DEBUG )
#pragma comment( lib, "../x64/Debug/nmea0183.lib" )
#else
#pragma comment( lib, "../x64/Release/nmea0183.lib" )
#endif

/*
** This is the test scenario. Add more sentences to the list to test them
*/

struct NMEA_TEST
{
    int              test_number{ 0 };
    std::string_view sentence{ nullptr, 0 };
    bool             expected_parse_result{ false };
    std::string_view source{ nullptr, 0 };
    std::string_view plain_english{ nullptr, 0 };
};

class TestingFunctorinator // Dr. Doofenshmirtz naming convention
{
public:

    NMEA0183 nmea0183;

    // Now turn this mild mannered class into a functor!
    void operator () (NMEA_TEST const& item) noexcept
    {
        nmea0183.SetSentence(item.sentence);

        if (nmea0183.Parse() != item.expected_parse_result)
        {
            std::string sentence;

            nmea0183.GetSentence(sentence);
            printf("Failed test %d with \"%s\"\n", item.test_number, nmea0183.ErrorMessage.c_str());
            printf("Last Sentence Received is \"%s\"\n", nmea0183.LastSentenceIDReceived.c_str());
            printf("Last Sentence Parsed is   \"%s\"\n\n", nmea0183.LastSentenceIDParsed.c_str());
        }
        else
        {
            if (item.plain_english.empty() == false && nmea0183.PlainText.compare(item.plain_english) != 0 )
            {
                std::string sentence;

                nmea0183.GetSentence(sentence);

                printf("\nFailed test %d plain English test for %s", item.test_number, sentence.c_str());
            }
        }
    }
};

int main()
{
   std::vector<NMEA_TEST> test_sentences;

   /*
   ** Load our test sentences and keep track of where they came from
   */

   test_sentences.push_back({ 1, STRING_VIEW("$GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*11\r\n"), false, STRING_VIEW("Peter Wyld, pwyld@cix.compulink.co.uk"), STRING_VIEW("") });
   test_sentences.push_back({ 2, STRING_VIEW("$PGRMM,NAD27 Canada*2F\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 3, STRING_VIEW("$LCAAM,V,A,.15,N,CHAT-N6*56\r\n"), true, STRING_VIEW("NMEA0183 document, pg 39"), STRING_VIEW("") });
   test_sentences.push_back({ 4, STRING_VIEW("$GPAPB,A,A,0.0,R,N,V,V,86.8,T,001,86.9,T,86.9,T\r\n"), true, STRING_VIEW(""), STRING_VIEW("") });
   test_sentences.push_back({ 5, STRING_VIEW("$GPBWC,104432.69,3337.36,N,11154.54,W,86.9,T,74.6,M,3.2,N,001\r\n"), true, STRING_VIEW(""), STRING_VIEW("") });
   test_sentences.push_back({ 6, STRING_VIEW("$GPBWC,104435.12,3337.36,N,11154.54,W,86.9,T,74.6,M,3.2,N,001\r\n"), true, STRING_VIEW(""), STRING_VIEW("") });
   test_sentences.push_back({ 7, STRING_VIEW("$GPBWC,225444,4917.24,N,12309.57,W,051.9,T,031.6,M,001.3,N,004*29\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 8, STRING_VIEW("$CTFSI,020230,026140,m,5*11\r\n"), true, STRING_VIEW("NMEA0183 document, pg 41"), STRING_VIEW("") });
   test_sentences.push_back({ 9, STRING_VIEW("$CDFSI,900016,,d,9*08\r\n"), true, STRING_VIEW("NMEA0183 document, pg 41"), STRING_VIEW("") });
   test_sentences.push_back({ 10, STRING_VIEW("$CTFSI,416193,,s,0*00\r\n"), true, STRING_VIEW("NMEA0183 document, pg 41"), STRING_VIEW("") });
   test_sentences.push_back({ 11, STRING_VIEW("$CXFSI,,021875,t,*3A\r\n"), true, STRING_VIEW("NMEA0183 document, pg 41"), STRING_VIEW("") });
   test_sentences.push_back({ 12, STRING_VIEW("$GPGGA,104435.12,3337.19,N,11158.43,W,1,06,4.5,,,,,,\r\n"), true, STRING_VIEW(""), STRING_VIEW("At Fri Nov  1 06:44:35 2019 UTC, you were at Latitude 33 37.19 North, Longitude 111 58.43 West, based upon a GPS fix, 6 satellites are in use.") });
   test_sentences.push_back({ 13, STRING_VIEW("$GPGGA,104432.69,3337.19,N,11158.43,W,1,06,5.1,,,,,,\r\n"), true, STRING_VIEW(""), STRING_VIEW("At Fri Nov  1 06:44:32 2019 UTC, you were at Latitude 33 37.19 North, Longitude 111 58.43 West, based upon a GPS fix, 6 satellites are in use.") });
   test_sentences.push_back({ 14, STRING_VIEW("$GPGLL,3337.190,N,11158.430,W,104432.686,A\r\n"), true, STRING_VIEW(""), STRING_VIEW("") });
   test_sentences.push_back({ 15, STRING_VIEW("$GPGLL,3337.190,N,11158.430,W,104435.122,A\r\n"), true, STRING_VIEW(""), STRING_VIEW("At Fri Nov  1 06:44:35 2019 you were at Latitude 33 37.19 North, Longitude 111 58.43 West.") });
   test_sentences.push_back({ 16, STRING_VIEW("$LCGLL,4728.31,N,12254.25,W,091342,A*21\r\n"), true, STRING_VIEW("NMEA0183 document, pg 39"), STRING_VIEW("At Fri Nov  1 05:13:42 2019 you were at Latitude 47 28.31 North, Longitude 122 54.25 West.") });
   test_sentences.push_back({ 17, STRING_VIEW("$GPGLL,4916.45,N,12311.12,W*71\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 18, STRING_VIEW("$GPGLL,5133.81,N,00042.25,W*75\r\n"), true, STRING_VIEW("Peter Wyld, pwyld@cix.compulink.co.uk"), STRING_VIEW("") });
   test_sentences.push_back({ 19, STRING_VIEW("$GPR00,MINST,CHATN,CHAT1,CHATW,CHATM,CHATE,003,004,005,006,007,,,*05\r\n"), false, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 20, STRING_VIEW("$LCRMA,V,,,,,14162.8,,,,,*0D\r\n"), true, STRING_VIEW("NMEA0183 document, pg 40"), STRING_VIEW("") });
   test_sentences.push_back({ 21, STRING_VIEW("$LCRMA,V,,,,,14172.3,26026.7,,,,*2E\r\n"), true, STRING_VIEW("NMEA0183 document, pg 40"), STRING_VIEW("") });
   test_sentences.push_back({ 22, STRING_VIEW("$LCRMA,A,,,,,14182.3,26026.7,,,,*36\r\n"), true, STRING_VIEW("NMEA0183 document, pg 40"), STRING_VIEW("") });
   test_sentences.push_back({ 23, STRING_VIEW("$LCRMA,A,4226.26,N,07125.89,W,14182.3,26026.7,8.5,275.,14.0,W*68\r\n"), true, STRING_VIEW("NMEA0183 document, pg 40"), STRING_VIEW("") });
   test_sentences.push_back({ 24, STRING_VIEW("$LCRMA,V,4226.26,N,07125.89,W,14182.3,26026.7,8.5,275.,14.0,W*7F\r\n"), true, STRING_VIEW(""), STRING_VIEW("") });
   test_sentences.push_back({ 25, STRING_VIEW("$LCRMA,A,4226.265,N,07125.890,W,14172.33,26026.71,8.53,275.,14.0,W*53\r\n"), true, STRING_VIEW("NMEA0183 document, pg 40"), STRING_VIEW("") });
   test_sentences.push_back({ 26, STRING_VIEW("$GPRMB,A,0.66,L,003,004,4917.24,N,12309.57,W,001.3,052.5,000.5,V*20\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 27, STRING_VIEW("$GPRMB,A,4.08,L,EGLL,EGLM,5130.02,N,00046.34,W,004.6,213.9,122.9,A*3D\r\n"), true, STRING_VIEW("Peter Wyld, pwyld@cix.compulink.co.uk"), STRING_VIEW("") });
   test_sentences.push_back({ 28, STRING_VIEW("$GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 29, STRING_VIEW("$GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70\r\n"), true, STRING_VIEW("Peter Wyld, pwyld@cix.compulink.co.uk"), STRING_VIEW("") });
   test_sentences.push_back({ 30, STRING_VIEW("$GPVTG,0.0,T,347.6,M,0.0,N,0.0,K\r\n"), true, STRING_VIEW(""), STRING_VIEW("") });
   test_sentences.push_back({ 31, STRING_VIEW("$GPVTG,054.7,T,034.4,M,000.5,N,000.9,K*47\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 32, STRING_VIEW("$GPWPL,4917.16,N,12310.64,W,003*65\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 33, STRING_VIEW("$GPWPL,5128.62,N,00027.58,W,EGLL*59\r\n"), true, STRING_VIEW("Peter Wyld, pwyld@cix.compulink.co.uk"), STRING_VIEW("") });
   test_sentences.push_back({ 34, STRING_VIEW("$GPXTE,A,A,0.67,L,N*6F\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 35, STRING_VIEW("$GPXTE,A,A,4.07,L,N*6D\r\n"), true, STRING_VIEW("Peter Wyld, pwyld@cix.compulink.co.uk"), STRING_VIEW("") });
   test_sentences.push_back({ 36, STRING_VIEW("$GPGGA,103050,3912.073,N,07646.887,W,1,08,1.8,2.5,M,-34.0,M,,*72\r\n"), true, STRING_VIEW("Me sitting at home with my Garmin 12XL"), STRING_VIEW("") });
   test_sentences.push_back({ 37, STRING_VIEW("$PGRMZ,93,f,3*21\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 38, STRING_VIEW("$PGRMZ,201,f,3*18\r\n"), true, STRING_VIEW("Peter Wyld, pwyld@cix.compulink.co.uk"), STRING_VIEW("") });
   test_sentences.push_back({ 39, STRING_VIEW("$PSLIB,,,J*22\r\n"), true, STRING_VIEW("Peter Bennett, bennett@triumf.ca"), STRING_VIEW("") });
   test_sentences.push_back({ 40, STRING_VIEW("$PSRDA003[470738][1224523]??RST47,3809,A004*47\r\n"), true, STRING_VIEW("NMEA0183 document, pg 40"), STRING_VIEW("") });

   // Now loop through the list and attempt to parse each sentence

   TestingFunctorinator testerinator;

   std::for_each( test_sentences.cbegin(), test_sentences.cend(), testerinator );

   return( EXIT_SUCCESS );
}
