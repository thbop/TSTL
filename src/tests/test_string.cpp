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
#include "stdio.h"

int main() {
    tstl::string f = "Hello World!";
    f.erase( 5, 6 );
    f.push_back( ' ' );
    f.insert( 7, f );
    f.pop_back();

    f.insert( f.size(), "Cheese puff" );
    f.erase( 20, 4 );

    f.reserve( 50 );

    f.append( 20, 'E' );

    f += " hmm..";
    f += '.';

    f.shrink_to_fit();

    printf( "%s %d %d\n", f.c_str(), (int)f.capacity(), (int)f.size() );

    f.clear();

    if ( f.empty() )
        printf("EMPTY\n");

    return 0;
}