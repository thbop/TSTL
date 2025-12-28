/*
* Copyright © 2025 Thbop
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the “Software”), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
* of the Software, and to permit persons to whom the Software is furnished to do
* so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <TSTL/string>
#include <TSTL/exception>

namespace tstl {
    string::string() {}
    string::string( const char *str ) {
        set_buffer( str );
    }
    string::string( const string &str ) {
        set_buffer( str.buffer );
    }
    string::~string() {
        clear_buffer();
    }

    void string::clear_buffer() {
        if ( buffer != nullptr )
            delete[] buffer;
    }

    void string::operator=( const string &other ) {
        set_buffer( other.buffer );
    }

    char string::at( size_t index ) {
        if ( index >= size() )
            throw exception( "Index out of bounds!\n" );
        
        return buffer[index];
    }

    char string::operator[]( size_t index ) {
        return buffer[index];
    }

    const char *string::c_str() {
        return buffer;
    }

    size_t string::size() {
        return buffer_size - 1;
    }

    void string::set_buffer( const char *str ) {
        clear_buffer();
        buffer_size = strlen( str ) + 1;

        buffer = new char[buffer_size];
        strncpy( buffer, str, buffer_size );
    }
}