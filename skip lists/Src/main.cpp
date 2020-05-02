/*
 * @Author: lsyy
 * @Date: 2020-04-01 20:59:30
 * @LastEditTime: 2020-04-27 18:07:31
 * @LastEditors: Please set LastEditors
 * @Description: list ÈİÆ÷ÊµÏÖ
 * @FilePath: \List\Src\main.cpp
 */

#include <iostream>
#include "List.h"
#include "Random.h"
class test{
public:
    int *p;
    int **p2;
};
// int main( ){

//     int a = 1, b = 2, c = 3;
//     test *pt = new test;

//     pt->p2 = new int*[3];
    
//     int **pp2 = pt->p2;

//     pt->p2[0] = &a;
//     pt->p2[1] = &b;
//     pt->p2[2] = &c;

//     delete [] pt->p2;
//     delete pt;

//     for( int i = 0; i < 3; ++i ){
//         std::cout << *( pt->p2[ i ] ) << "  ";
//     }

//     return 0;
// }
// int main( ){

//     test *pt = new test;
//     pt->p = new int[10];

//     for( int i = 0; i < 10; ++i ){
//         pt->p[i] = i;
//     }
//     int *pp = pt->p;

//     delete []pt->p;
//     delete pt;
    
//     pt = nullptr;
//     pp[0] = 10;

//     for( int i = 0; i < 10; ++i ){
//         std::cout << *(pp++) << "   ";
//     }


//     return 0;
// }

// int main( ){

//     test *pt = new test;
//     pt->p = new int[10];
//     pt->p2 = new int*[2];
//     for( int i = 0; i < 10; ++i ){
//         pt->p[i] = i;
//     }
//     int *pp = pt->p;
//     int **pp2 = pt->p2;

//     delete pt;
//     pt = nullptr;
//     pp[0] = 10;

//     for( int i = 0; i < 10; ++i ){
//         std::cout << *(pp++) << "   ";
//     }
//     return 0;
// }
int main( ){

    skiplist<int> sl;
    sl.insert( 11 );
    sl.insert( 21 );

    sl.insert( 34 );
    sl.insert( 11 );
    sl.insert( 21 );

    sl.insert( 34 );
    sl.insert( 1 );
    sl.insert( 2 );
    sl.insert( 7 );
    sl.insert( 3 );
    sl.insert( 11 );
    sl.insert( 21 );

    sl.insert( 34 );
    sl.insert( 11 );
    sl.insert( 21 );

    sl.insert( 34 );
    sl.insert( 34 );
    sl.insert( 1 );
    sl.insert( 2 );
    sl.insert( 7 );
    sl.insert( 3 );
    sl.insert( 11 );
    sl.insert( 21 );

    sl.insert( 34 );
    sl.insert( 11 );
    sl.insert( 21 );

    bool f = sl.contains( 11 );
    sl.print( );
    
    sl.remove( 7 );
    sl.print( );
    return 0;
}