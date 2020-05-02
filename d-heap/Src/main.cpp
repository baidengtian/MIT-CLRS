/*
 * @Author: your name
 * @Date: 2020-04-22 19:52:22
 * @LastEditTime: 2020-04-23 11:00:13
 * @LastEditors: Please set LastEditors
 * @Description: Ëã·¨µ¼ÂÛ d¶Ñ
 * @FilePath: \d-heap\Src\main.cpp
 */

#include <iostream>
#include <vector>
#include "Random.h"
#include "dheap.h"


int main( ){

    std::vector<int> vi{ 1,7,4,14,6,99,8,102,88,44,32,11,999,1010,13,14,15,19 };
    // std::vector<int> vi{ 0,1,2,3,5,4,7,10,13,15,6,8,17,9,11,9 };
    // std::vector<int> vi{ 0,10,20,30,40,21,22,23 };
    // std::vector<int> vi{ 0,100,70,80,90,11,13,15,65,55,25,33,31,27 };
    // std::vector<int> vi{ 0,1,2,3,4,5,6,7 };
    dheap<int> dp{ vi, 3 };
    dp.extract_max( );
    // int pos = dp.findMaxChild( 1 );
    // bool f = dp.increase_key( 4, 1000 );
    // dp.insert( 1100 );
    // int max = dp.extract_max( );

    return 0;

}