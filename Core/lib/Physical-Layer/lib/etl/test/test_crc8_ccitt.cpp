/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2021 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include "unit_test_framework.h"

#include <iterator>
#include <string>
#include <vector>
#include <stdint.h>

#include "etl/crc8_ccitt.h"

//*****************************************************************************
// The results for these tests were created from https://crccalc.com/
//*****************************************************************************

namespace
{
  SUITE(test_crc_experimental)
  {
    //*************************************************************************
    // Table size 4
    //*************************************************************************
    TEST(test_crc8_ccitt_4_constructor)
    {
      std::string data("123456789");

      uint8_t crc = etl::crc8_ccitt_t4(data.begin(), data.end());

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_4_add_values)
    {
      std::string data("123456789");

      etl::crc8_ccitt_t4 crc_calculator;

      for (size_t i = 0UL; i < data.size(); ++i)
      {
        crc_calculator.add(data[i]);
      }

      uint8_t crc = crc_calculator;

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_4_add_range)
    {
      std::string data("123456789");

      etl::crc8_ccitt_t4 crc_calculator;

      crc_calculator.add(data.begin(), data.end());

      uint8_t crc = crc_calculator.value();

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_4_add_range_via_iterator)
    {
      std::string data("123456789");

      etl::crc8_ccitt_t4 crc_calculator;

      std::copy(data.begin(), data.end(), crc_calculator.input());

      uint8_t crc = crc_calculator.value();

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_4_add_range_endian)
    {
      std::vector<uint8_t>  data1 = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
      std::vector<uint32_t> data2 = { 0x04030201UL, 0x08070605UL };
      std::vector<uint8_t>  data3 = { 0x08U, 0x07U, 0x06U, 0x05U, 0x04U, 0x03U, 0x02U, 0x01U };

      uint8_t crc1 = etl::crc8_ccitt_t4(data1.begin(), data1.end());
      uint8_t crc2 = etl::crc8_ccitt_t4((uint8_t*)&data2[0], (uint8_t*)(&data2[0] + data2.size()));
      CHECK_EQUAL(int(crc1), int(crc2));

      uint8_t crc3 = etl::crc8_ccitt_t4(data3.rbegin(), data3.rend());
      CHECK_EQUAL(int(crc1), int(crc3));
    }

    //*************************************************************************
    // Table size 16
    //*************************************************************************
    TEST(test_crc8_ccitt_16_constructor)
    {
      std::string data("123456789");

      uint8_t crc = etl::crc8_ccitt_t16(data.begin(), data.end());

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_16_add_values)
    {
      std::string data("123456789");

      etl::crc8_ccitt_t16 crc_calculator;

      for (size_t i = 0UL; i < data.size(); ++i)
      {
        crc_calculator.add(data[i]);
      }

      uint8_t crc = crc_calculator;

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_16_add_range)
    {
      std::string data("123456789");

      etl::crc8_ccitt_t16 crc_calculator;

      crc_calculator.add(data.begin(), data.end());

      uint8_t crc = crc_calculator.value();

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_16_add_range_via_iterator)
    {
      std::string data("123456789");

      etl::crc8_ccitt_t16 crc_calculator;

      std::copy(data.begin(), data.end(), crc_calculator.input());

      uint8_t crc = crc_calculator.value();

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_16_add_range_endian)
    {
      std::vector<uint8_t>  data1 = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
      std::vector<uint32_t> data2 = { 0x04030201UL, 0x08070605UL };
      std::vector<uint8_t>  data3 = { 0x08U, 0x07U, 0x06U, 0x05U, 0x04U, 0x03U, 0x02U, 0x01U };

      uint8_t crc1 = etl::crc8_ccitt_t16(data1.begin(), data1.end());
      uint8_t crc2 = etl::crc8_ccitt_t16((uint8_t*)&data2[0], (uint8_t*)(&data2[0] + data2.size()));
      CHECK_EQUAL(int(crc1), int(crc2));

      uint8_t crc3 = etl::crc8_ccitt_t16(data3.rbegin(), data3.rend());
      CHECK_EQUAL(int(crc1), int(crc3));
    }

    //*************************************************************************
    // Table size 256
    //*************************************************************************
    TEST(test_crc8_ccitt_256_constructor)
    {
      std::string data("123456789");

      uint8_t crc = etl::crc8_ccitt(data.begin(), data.end());

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_256_add_values)
    {
      std::string data("123456789");

      etl::crc8_ccitt crc_calculator;

      for (size_t i = 0UL; i < data.size(); ++i)
      {
        crc_calculator.add(data[i]);
      }

      uint8_t crc = crc_calculator;

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_256_add_range)
    {
      std::string data("123456789");

      etl::crc8_ccitt crc_calculator;

      crc_calculator.add(data.begin(), data.end());

      uint8_t crc = crc_calculator.value();

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_256_add_range_via_iterator)
    {
      std::string data("123456789");

      etl::crc8_ccitt crc_calculator;

      std::copy(data.begin(), data.end(), crc_calculator.input());

      uint8_t crc = crc_calculator.value();

      CHECK_EQUAL(0xF4U, int(crc));
    }

    //*************************************************************************
    TEST(test_crc8_ccitt_256_add_range_endian)
    {
      std::vector<uint8_t>  data1 = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
      std::vector<uint32_t> data2 = { 0x04030201UL, 0x08070605UL };
      std::vector<uint8_t>  data3 = { 0x08U, 0x07U, 0x06U, 0x05U, 0x04U, 0x03U, 0x02U, 0x01U };

      uint8_t crc1 = etl::crc8_ccitt(data1.begin(), data1.end());
      uint8_t crc2 = etl::crc8_ccitt((uint8_t*)&data2[0], (uint8_t*)(&data2[0] + data2.size()));
      CHECK_EQUAL(int(crc1), int(crc2));

      uint8_t crc3 = etl::crc8_ccitt(data3.rbegin(), data3.rend());
      CHECK_EQUAL(int(crc1), int(crc3));
    }
  };
}
