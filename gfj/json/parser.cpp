#if !defined GRAPEFRUITJUICE_JSON_PARSER_CPP_INCLUDED
#define      GRAPEFRUITJUICE_JSON_PARSER_CPP_INCLUDED

#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <tuple>

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/phoenix/stl.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include <boost/range/numeric.hpp>

#include <boost/optional/optional.hpp>

#include <boost/any.hpp>

namespace gfj {
namespace json {

struct json_value { // {{{
    using string_type = std::string;
    using null_type = std::nullptr_t;
    using array_type = std::vector<json_value>;
    using object_type = std::unordered_map<std::string, json_value>;
    using value_type = boost::variant<
                           std::nullptr_t
                           , bool
                           , double
                           , std::string
                           , boost::recursive_wrapper<array_type>
                           , boost::recursive_wrapper<object_type>
                       >;
    value_type value;

    auto get_null() const
        -> boost::optional<std::nullptr_t>
    {
        if (value.which() == 0) {
            return nullptr;
        } else {
            return boost::none;
        }
    }

    auto get_bool() const
        -> boost::optional<bool>
    {
        if (value.which() == 1) {
            return boost::get<bool>(value);
        } else {
            return boost::none;
        }
    }

    auto get_number() const
        -> boost::optional<double>
    {
        if (value.which() == 2) {
            return boost::get<double>(value);
        } else {
            return boost::none;
        }
    }

    auto get_string() const
        -> boost::optional<std::string>
    {
        if (value.which() == 3) {
            return boost::get<std::string>(value);
        } else {
            return boost::none;
        }
    }

    auto get_array() const
        -> boost::optional<array_type>
    {
        if (value.which() == 4) {
            return boost::get<array_type>(value);
        } else {
            return boost::none;
        }
    }

    auto get_object() const
        -> boost::optional<object_type>
    {
        if (value.which() == 5) {
            return boost::get<object_type>(value);
        } else {
            return boost::none;
        }
    }

    boost::any get() const
    {
        return value;
    }
};

template<class T>
boost::optional<T> get(json_value const& j)
{
    try {
        return boost::get<T>(j.value);
    } catch (boost::bad_get const&){
        return boost::none;
    }
}
// }}}

struct stringizer : public boost::static_visitor<std::string> { // {{{
    std::string operator()(std::nullptr_t const) const
    {
        return "null";
    }
    std::string operator()(bool const b) const
    {
        return b ? "true" : "false";
    }
    std::string operator()(double const d) const
    {
        return std::to_string(d);
    }
    std::string operator()(std::string const& str) const
    {
        return '"' + str + '"';
    }
    std::string operator()(json_value::array_type const& arr) const
    {
        return "[ " +
            boost::accumulate(arr, std::string{},
                              [](auto const& acc, auto const& j){
                                  return acc + (acc.empty() ? "" : ", ") + boost::apply_visitor(stringizer(), j.value);
                              }
                             ) +
               " ]";
    }
    std::string operator()(json_value::object_type const& obj) const
    {
        return "{ " +
            boost::accumulate(obj, std::string{},
                              [](auto const& acc, auto const& keyval){
                                  return acc + (acc.empty() ? "" : ", \"")
                                             + keyval.first + "\": "
                                             + boost::apply_visitor(stringizer(), keyval.second.value);
                              }
                             ) +
              " }";
    }
};

std::string stringize(json_value const& json_val)
{
    return boost::apply_visitor(stringizer(), json_val.value);
}

// }}}

// Grammar {{{
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phx = boost::phoenix;

template<class Iterator, class JsonValue = json_value>
struct json_grammar : qi::grammar<Iterator, JsonValue(), ascii::space_type> {
    template<class Value>
    using rule = qi::rule<Iterator, Value, ascii::space_type>;

    rule<JsonValue()>                                   value_;
    rule<typename JsonValue::object_type()>             object_;
    rule<typename JsonValue::array_type()>              array_;
    rule<typename JsonValue::string_type()>             string_;
    rule<typename JsonValue::null_type()>               null_;
    rule<std::pair<
            typename JsonValue::object_type::key_type,
            typename JsonValue::object_type::mapped_type
        > ()> key_value_;

    json_grammar() : json_grammar::base_type(value_)
    {
        value_ = (qi::double_ | qi::bool_ | array_ | object_ | string_ | null_)[phx::bind(&JsonValue::value, qi::_val) = qi::_1];
        array_ = '[' > value_[phx::push_back(qi::_val, qi::_1)] % ',' > ']';
        object_ = '{' > key_value_[phx::insert(qi::_val, qi::_1)] % ',' > '}';
        key_value_ = (string_ > ':' > value_)
                        [ qi::_val = phx::bind( [](auto const& s, auto const& j){ return std::make_pair(s, j); }, qi::_1, qi::_2 ) ];
        string_ = qi::lexeme['"' > *(
                    (qi::char_ - '"' - '\\')[qi::_val += qi::_1] |
                    ('\\' > ( qi::lit('"') [qi::_val += '"']
                            | qi::lit('\\')[qi::_val += '\\']
                            | qi::lit('/') [qi::_val += '/']
                            | qi::lit('b') [qi::_val += '\b']
                            | qi::lit('f') [qi::_val += '\f']
                            | qi::lit('n') [qi::_val += '\n']
                            | qi::lit('r') [qi::_val += '\r']
                            | qi::lit('t') [qi::_val += '\t']
                            | qi::lit('u') [qi::_val += "\\u"]          // XXX parse utf-8 characters properly
                            | qi::char_    [qi::_val += qi::_1]
                        )
                    )
                  ) > '"'];
        null_ = qi::lit("null")[qi::_val = nullptr];

        qi::on_error<qi::fail>
        (
            value_,
            std::cerr
                << phx::val( "Error! Expecting " )
                << qi::_4                          // what failed?
                << phx::val( " here: \"" )
                << phx::construct<std::string>( qi::_3, qi::_2 )    // iterators to error-pos, end
                << phx::val( "\"" )
                << std::endl
        );
    }
};
// }}}
} // namespace gfj
#endif    // GRAPEFRUITJUICE_JSON_PARSER_CPP_INCLUDED
