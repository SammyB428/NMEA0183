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

/*
** This Sentence Not Recommended For New Designs
** XDR is recommended.
*/

#include "nmea0183.h"
#pragma hdrstop

void MTA::Empty(void) noexcept
{
    Temperature = 0.0;
    UnitOfMeasurement.clear();
}

bool MTA::Parse(SENTENCE const& sentence) noexcept
{
    /*
    ** MTA - Air Temperature
    **
    **        1   2 3
    **        |   | |
    ** $--MTA,x.x,C*hh<CR><LF>
    **
    ** Field Number:
    **  1) Degrees
    **  2) Unit of Measurement, Celcius
    **  3) Checksum
    */

    /*
    ** First we check the checksum...
    */

    if (sentence.IsChecksumBad(3) == NMEA0183_BOOLEAN::True)
    {
        SetErrorMessage("Invalid Checksum");
        return(false);
    }

    Temperature = sentence.Double(1);
    UnitOfMeasurement = sentence.Field(2);

    return(true);
}

std::string MTA::PlainEnglish(void) const noexcept
{
    std::string return_string(STRING_VIEW("The air temperature is "));

    char temp_string[65];

    auto const number_of_characters{ ::sprintf(temp_string, "%.1f ", Temperature) };

    return_string.append(temp_string, number_of_characters);
    return_string.append(UnitOfMeasurement);
    return_string.push_back('.');

    return(return_string);
}

bool MTA::Write(SENTENCE& sentence) const noexcept
{
    /*
    ** Let the parent do its thing
    */

    RESPONSE::Write(sentence);

    sentence += Temperature;
    sentence += UnitOfMeasurement;

    sentence.Finish();

    return(true);
}

MTA const& MTA::operator = (MTA const& source) noexcept
{
    Temperature = source.Temperature;
    UnitOfMeasurement = source.UnitOfMeasurement;

    return(*this);
}
