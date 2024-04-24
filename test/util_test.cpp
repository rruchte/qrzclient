#include "../src/Util.h"
#include <gtest/gtest.h>

namespace qrz
{
	namespace
	{
		TEST(UtilTests, TestToUpper)
		{
			std::string expected = "WOMBATS";
			std::string actual = "wOmbaTs";

			ToUpper(actual);

			ASSERT_STREQ(expected.c_str(), actual.c_str()) << "Strings should be equal and uppercase";
		}

		TEST(UtilTests, TestToLower)
		{
			std::string expected = "wombats";
			std::string actual = "wOmbaTs";

			ToLower(actual);

			ASSERT_STREQ(expected.c_str(), actual.c_str()) << "Strings should be equal and lowercase";
		}

		TEST(UtilTests, TestVectorToCSV)
		{
			std::string expected = "\"foo\",\"bar\",\"baz\",\"wom,bats\"";

			std::vector<std::string> input = {"foo", "bar", "baz", "wom,bats"};

			std::string actual = VectorToCSV(input);

			ASSERT_STREQ(expected.c_str(), actual.c_str()) << "Strings should be equal and lowercase";
		}
	}
}