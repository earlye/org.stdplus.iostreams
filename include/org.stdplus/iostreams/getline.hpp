#ifndef h8B45CCAB_7238_4F5E_B343_44553C67DC27
#define h8B45CCAB_7238_4F5E_B343_44553C67DC27

//#include <stdplus/compiler/disable_code_in_header_yield_noprecompile.hpp>

#include <iostream>
#include <string>

namespace org
{
  namespace stdplus
  {
    namespace iostreams
    {
      template< class char_type, class char_traits, class allocator>
      inline std::basic_istream< char_type , char_traits >& getline
      ( std::basic_istream< char_type , char_traits >& input_stream,
        std::basic_string<char_type,char_traits,allocator>& output_string,
        std::basic_string<char_type,char_traits,allocator> const& delimiters)
      {
        using namespace std;
        typedef basic_istream<char_type, char_traits> istream_t;
        typedef basic_streambuf< char_type , char_traits > streambuf_t;
        typedef basic_string<char_type,char_traits,allocator > string_t;
#ifndef _MSC_VER

        size_t num_read = 0;

        typename basic_istream<char_type, char_traits>::sentry sentry(input_stream, true);

        if (sentry)
          {
            streambuf_t* buffer = input_stream.rdbuf();
            output_string.clear();

            while (num_read < output_string.max_size())
              {
                int char_read = buffer->sbumpc();
                if (char_traits::eq_int_type(char_read, char_traits::eof()))
                  {
                    input_stream.setstate(istream_t::eofbit);
                    break;
                  }
                else
                  {
                    ++num_read;
                    char_type char_converted = char_traits::to_char_type(char_read);
                    if ( string_t::npos == delimiters.find( char_converted ) )
                      output_string.push_back( char_converted );
                    else
                      break; // Character is extracted but not appended.
                  }
              }
          }
        if (num_read == 0 || num_read >= output_string.max_size())
          input_stream.setstate(istream_t::failbit);

        return input_stream;
#else
        string_t result;
        for( char_type ch = input_stream.get() ; input_stream && !input_stream.eof() ; ch = input_stream.get() )
          {
            if ( string_t::npos != delimiters.find( ch ) )
              break;
            result += ch;
          }
        output_string = result;
        return input_stream;
#endif
      }

      template
      < class char_type
        , class char_traits
        , class allocator>
      inline std::basic_istream < char_type , char_traits >& getline
      ( std::basic_istream< char_type , char_traits >&      input_stream
        , std::basic_string<char_type,char_traits,allocator>& output_string
        , char const* delimiters)
      {
        typedef std::basic_string< char_type , char_traits , allocator > string_t;
        string_t temp( delimiters );
        return org::stdplus::iostreams::getline<char_type,char_traits,allocator>
          ( input_stream , output_string , temp );
      }

      inline std::string getline
      ( std::istream& input_stream
        , std::string const& delimiters )
      {
        std::string result;
        org::stdplus::iostreams::getline( input_stream , result , delimiters );
        return result;
      }
    }
  }
}
#endif
