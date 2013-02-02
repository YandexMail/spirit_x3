/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/home/x3.hpp>
//~ #include <boost/phoenix/core.hpp>
//~ #include <boost/phoenix/operator.hpp>

#include <string>
#include <iostream>
#include "test.hpp"

int
main()
{
    using boost::spirit::x3::ascii::char_;
    using boost::spirit::x3::lit;
    using spirit_test::test;
    using spirit_test::test_attr;

    // Basic tests
    {
        BOOST_TEST(test("b", char_ - 'a'));
        BOOST_TEST(!test("a", char_ - 'a'));
        BOOST_TEST(test("/* abcdefghijk */", "/*" >> *(char_ - "*/") >> "*/"));
        BOOST_TEST(!test("switch", lit("switch") - "switch"));
    }

    // Test attributes
    {
        char attr;
        BOOST_TEST(test_attr("xg", (char_ - 'g') >> 'g', attr));
        BOOST_TEST(attr == 'x');
    }

    // Test handling of container attributes
    {
        std::string attr;
        BOOST_TEST(test_attr("abcdefg", *(char_ - 'g') >> 'g', attr));
        BOOST_TEST(attr == "abcdef");
    }

    // $$$ Not yet implemented
    //~ {
        //~ BOOST_TEST(test("b", char_ - no_case['a']));
        //~ BOOST_TEST(!test("a", char_ - no_case['a']));
        //~ BOOST_TEST(!test("A", char_ - no_case['a']));

        //~ BOOST_TEST(test("b", no_case[lower - 'a']));
        //~ BOOST_TEST(test("B", no_case[lower - 'a']));
        //~ BOOST_TEST(!test("a", no_case[lower - 'a']));
        //~ BOOST_TEST(!test("A", no_case[lower - 'a']));
    //~ }

    // $$$ Not yet implemented
    //~ {
        //~ using boost::spirit::_1;
        //~ namespace phx = boost::phoenix;

        //~ std::string s;

        //~ BOOST_TEST(test(
            //~ "/*abcdefghijk*/"
          //~ , "/*" >> *(char_ - "*/")[phx::ref(s) += _1] >> "*/"
        //~ ));
        //~ BOOST_TEST(s == "abcdefghijk");
        //~ s.clear();

        //~ BOOST_TEST(test(
            //~ "    /*abcdefghijk*/"
          //~ , "/*" >> *(char_ - "*/")[phx::ref(s) += _1] >> "*/"
          //~ , space
        //~ ));
        //~ BOOST_TEST(s == "abcdefghijk");
    //~ }

    return boost::report_errors();
}
