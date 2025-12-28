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
    // Public
    string::string() {}
    string::string( const char *str ) {
        set_buffer( str );
    }
    string::string( const string &str ) {
        set_buffer( str.buffer );
    }
    string::~string() {
        clear();
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

    char string::front() {
        return buffer[0];
    }

    char string::back() {
        return buffer[size() - 1];
    }
    
    const char *string::data() const {
        return buffer;
    }

    const char *string::c_str() const {
        return buffer;
    }

    bool string::empty() const {
        return char_count == 0;
    }

    size_t string::size() const {
        return char_count;
    }

    size_t string::length() const {
        return char_count;
    }

    void string::reserve( size_t new_capacity ) {
        if ( new_capacity > capacity() ) {
            char *new_buffer = new char[new_capacity];
            memcpy( new_buffer, buffer, buffer_size );

            buffer_size = new_capacity;

            delete[] buffer;
            buffer = new_buffer;
        }
    }

    size_t string::capacity() const {
        return buffer_size;
    }
    
    void string::shrink_to_fit() {
        // Remember, char_count does not include the null-terminator
        if ( buffer_size > char_count + 1 ) {
            size_t new_buffer_size = char_count + 1;
            char *new_buffer = new char[new_buffer_size];
            memcpy( new_buffer, buffer, new_buffer_size );

            buffer_size = new_buffer_size;

            delete[] buffer;
            buffer = new_buffer;
        }
    }

    void string::clear() {
        if ( buffer != nullptr ) {
            delete[] buffer;
            buffer = nullptr;
            buffer_size = 
            char_count  = 0;
        }
    }

    string &string::insert( size_t index, const char *str ) {
        return insert( index, str, strlen( str ) );
    }

    string &string::insert( size_t index, const char *str, size_t count ) {
        if ( index > char_count )
            return *this;

        reserve( size() + count + 1 ); // + 1 for the null-terminator

        size_t move_size = char_count + 1 - index;
        memmove( buffer + index + count, buffer + index, move_size );
        memcpy( buffer + index, str, count );

        char_count += count;

        return *this;
    }

    string &string::insert( size_t index, const string &str ) {
        if ( &str == this ) {
            string str_copy = str;
            return insert( index, str_copy.c_str(), str_copy.size() );
        }
        return insert( index, str.c_str(), str.size() );
    }

    string &string::insert( size_t index, const string &str, size_t s_index, size_t count ) {
        if ( &str == this ) {
            string str_copy = str;
            return insert( index, str_copy.c_str() + s_index, count );
        }
        return insert( index, str.c_str() + s_index, count );
    }

    // Private
    void string::set_buffer( const char *str ) {
        clear();
        char_count  = strlen( str );
        buffer_size = char_count + 1;

        buffer = new char[buffer_size];
        strncpy( buffer, str, buffer_size );
    }
}