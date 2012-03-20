#ifndef PQRS_STRING_HPP
#define PQRS_STRING_HPP

#include <string>
#include <boost/optional.hpp>
#include <tr1/cstdint>
#include <tr1/unordered_map>

namespace pqrs {
  namespace string {
    typedef std::tr1::unordered_map<std::string, std::string> replacement;

    int string_by_replacing_double_curly_braces_from_file(std::string& string,
                                                          const char* filename,
                                                          replacement replacement);
    int string_by_replacing_double_curly_braces_from_string(std::string& string,
                                                            const std::string& source,
                                                            replacement replacement);

    // octal,decimal,hex is supported.
    boost::optional<uint32_t> to_uint32_t(const char* string);
    boost::optional<uint32_t> to_uint32_t(const std::string& string);
  }
}

#endif