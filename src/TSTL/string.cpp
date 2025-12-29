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
    string::string( const char *str, size_t count ) {
        set_buffer( str, count );
    }
    string::string( const string& str ) {
        set_buffer( str.c_str() );
    }
    string::string( const string &str, size_t count ) {
        set_buffer( str.c_str(), count );
    }
    string::~string() {
        clear();
    }

    void string::operator=( const string &other ) {
        set_buffer( other.c_str() );
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

        size_t
            move_size  = char_count + 1 - index,
            move_pos = index + count;
        if ( move_size == 1 )
            buffer[move_pos] = '\0';
        else
            memmove( buffer + move_pos, buffer + index, move_size );

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

    string &string::insert( size_t index, const string &str, size_t pos, size_t count ) {
        if ( &str == this ) {
            string str_copy = str;
            return insert( index, str_copy.c_str() + pos, count );
        }
        return insert( index, str.c_str() + pos, count );
    }

    string &string::erase( size_t index, size_t count ) {
        size_t
            remove_count   = tstl_min( count, size() - index ),
            move_start_pos = index + remove_count,
            move_count     = size() + 1 - move_start_pos;
        
        if ( move_count == 1 )
            buffer[index] = '\0';
        else
            memmove( buffer + index, buffer + move_start_pos, move_count );
        
        char_count -= remove_count;

        return *this;
    }

    void string::push_back( char ch ) {
        // +1 for new character
        // +1 for null terminator
        reserve( size() + 2 );

        buffer[size()] = ch;
        buffer[size() + 1] = '\0';
        char_count++;
    }

    void string::pop_back() {
        buffer[--char_count] = '\0';
    }

    string &string::append( size_t count, char ch ) {
        char *buffer = new char[count + 1];
        memset( buffer, ch, count );
        buffer[count] = '\0';

        append( buffer );
        delete[] buffer;

        return *this;
    }
    string &string::append( const char *str ) {
        return insert( size(), str );
    }
    string &string::append( const char *str, size_t count ) {
        return insert( size(), str, count );
    }
    string &string::append( const string &str ) {
        return insert( size(), str );
    }
    string &string::append( const string &str, size_t pos, size_t count ) {
        return insert( size(), str, pos, count );
    }

    string &string::operator+=( const string &str ) {
        return append( str );
    }
    string &string::operator+=( char ch ) {
        push_back( ch );
        return *this;
    }
    string &string::operator+=( const char *str ) {
        return append( str );
    }

    int string::compare( const string &str ) const {
        return strncmp( c_str(), str.c_str(), size() );
    }
    int string::compare( size_t pos0, size_t count0, const string &str ) const {
        count0 = count0 > size() - pos0 ? size() - pos0 : count0;

        return strncmp( c_str() + pos0, str.c_str(), count0 );
    }
    int string::compare( size_t pos0, size_t count0, const string &str, size_t pos1, size_t count1 ) const {
        count0 = count0 > size() - pos0 ? size() - pos0 : count0;
        count1 = count1 > str.size() - pos1 ? str.size() - pos1 : count1;

        // That min function might not be "lore accurate" per se
        return strncmp( c_str() + pos0, str.c_str() + pos1, tstl_min( count0, count1 ) );
    }
    int string::compare( const char *str ) const {
        return strncmp( c_str(), str, size() );
    }
    int string::compare( size_t pos0, size_t count0, const char *str ) const {
        count0 = count0 > size() - pos0 ? size() - pos0 : count0;

        return strncmp( c_str() + pos0, str, count0 );
    }
    int string::compare( size_t pos0, size_t count0, const char *str, size_t pos1, size_t count1 ) const {
        count0 = count0 > size() - pos0 ? size() - pos0 : count0;
        size_t str_size = strlen( str );
        count1 = count1 > str_size - pos1 ? str_size - pos1 : count1;

        // That min function might not be "lore accurate" per se
        return strncmp( c_str() + pos0, str + pos1, tstl_min( count0, count1 ) );
    }

    bool string::starts_with( const char *str ) const {
        return compare( 0, strlen( str ), str ) == 0;
    }
    bool string::starts_with( const string &str ) const {
        return compare( 0, str.size(), str ) == 0;
    }

    bool string::ends_with( const char *str ) const {
        size_t str_size = strlen( str );
        return compare( size() - str_size, str_size, str ) == 0;
    }
    bool string::ends_with( const string &str ) const {
        return compare( size() - str.size(), str.size(), str ) == 0;
    }

    bool string::contains( char ch ) const {
        for ( size_t i = 0; i < size(); i++ )
            if ( buffer[i] == ch )
                return true;
        return false;
    }
    bool string::contains( const char *str ) const {
        if ( starts_with( str ) || ends_with( str ) )
            return true;

        size_t str_size = strlen( str );

        for ( size_t i = 0; i < size() - str_size; i++ )
            if ( buffer[i] == str[0] && compare( i, str_size, str ) == 0 )
                return true;
        
        return false;
    }
    bool string::contains( const string &str ) const {
        return contains( str.c_str() );
    }

    string string::substr( size_t pos, size_t count ) const {
        return string( c_str() + pos, count );
    }

    // Private
    void string::set_buffer( const char *str, size_t count ) {
        clear();
        char_count  = count;
        buffer_size = char_count + 1;

        buffer = new char[buffer_size];
        strncpy( buffer, str, buffer_size );
        buffer[char_count] = '\0'; // Ensure string is null-terminated
    }
    void string::set_buffer( const char *str ) {
        set_buffer( str, strlen( str ) );
    }
}