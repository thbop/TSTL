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

#include <TSTL/exception>

namespace tstl {
    exception::exception() noexcept {
        set_message( "Exception!\n" );
    }
    exception::exception( const exception &other ) noexcept {
        set_message( other.what() );
    }
    exception::exception( const char *message ) noexcept {
        set_message( message );
    }

    void exception::clear_message() {
        if ( this->message != nullptr )
            delete[] this->message;
    }

    void exception::set_message( const char *message ) {
        if ( message == nullptr ) return;

        size_t message_size = strlen( message ) + 1;
        if ( message_size == 0 ) return;

        clear_message();

        this->message = new char[message_size];
        strncpy( this->message, message, message_size );
    }

    exception::~exception() {
        clear_message();
    }

    void exception::operator=( const exception &other ) noexcept {
        set_message( other.what() );
    }

    const char *exception::what() const noexcept {
        return message;
    }
}