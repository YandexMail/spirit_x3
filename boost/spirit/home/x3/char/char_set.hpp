/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_X3_CHAR_SET_APRIL_16_2006_1051AM)
#define BOOST_SPIRIT_X3_CHAR_SET_APRIL_16_2006_1051AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/x3/char/char_parser.hpp>
#include <boost/spirit/home/x3/support/utility/utf8.hpp>
#include <boost/spirit/home/x3/support/traits/string_traits.hpp>
#include <boost/spirit/home/x3/char/detail/cast_char.hpp>
#include <boost/spirit/home/support/char_set/basic_chset.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace spirit { namespace x3
{
    template <typename Encoding, typename Attribute = typename Encoding::char_type>
    struct char_set : char_parser<char_set<Encoding, Attribute>>
    {
        typedef typename Encoding::char_type char_type;
        typedef Encoding encoding;
        typedef Attribute attribute_type;
        static bool const has_attribute =
            !is_same<unused_type, attribute_type>::value;

        template <typename String>
        char_set(String const& str)
        {
          typedef typename
            remove_const<
              typename traits::char_type_of<String>::type
            >::type
          in_type;

#if 0
          BOOST_SPIRIT_ASSERT_MSG((
                (sizeof(char_type) >= sizeof(in_type))
          ), cannot_convert_string, (String));
#endif

          in_type const* definition =
            (in_type const*)traits::get_c_string(str);

          in_type ch = *definition++;

          while (ch)
          {
            in_type next = *definition++;
            if (next == '-')
            {
              next = *definition++;
              if (next == 0)
              {
                chset.set (detail::cast_char<char_type> (ch));
                chset.set ('-');
                break;
              }
              chset.set (
                  detail::cast_char<char_type> (ch),
                  detail::cast_char<char_type> (next)
              );
            }
            else
            {
              chset.set (detail::cast_char<char_type> (ch));
            }
            ch = next;
          }
        }

        template <typename Char, typename Context>
        bool test(Char ch_, Context const&) const
        {
          return ((sizeof(Char) <= sizeof(char_type)) || encoding::ischar(ch_))
              && chset.test (char_type(ch_));
        }

        support::detail::basic_chset<char_type> chset;
    };

    template <typename Encoding, typename Attribute>
    struct get_info<char_set<Encoding, Attribute>>
    {
        typedef std::string result_type;
        std::string operator()(char_set<Encoding, Attribute> const& p) const
        {
            return '\'' + to_utf8(Encoding::toucs4(' ' /*p.ch*/)) + '\'';
        }
    };
}}}

#endif
