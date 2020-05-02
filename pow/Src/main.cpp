/*
 * @Author: your name
 * @Date: 2020-04-13 21:46:15
 * @LastEditTime: 2020-04-21 14:01:46
 * @LastEditors: Please set LastEditors
 * @Description: 算法导论 随机法选择第 i 个最小元素
 * @FilePath: \quicksort\Src\main.cpp
 */


#include <iostream>
#include <vector>
#include "Random.h"


// 从小到大
int rand_partition( std::vector<int> &a, int p, int q ){
    static Random r;
    int pos = r.randomInt( p, q );
    int i = p;
    std::swap( a[ pos ], a[ p ] );
    for( int j = p + 1; j <= q; ++j ){
        if( a[ j ] < a[ p ] )
            std::swap( a[ ++i ], a[ j ] );  
    }
    std::swap( a[ p ], a[ i ] );
    return i;
}
// 从数组中选出第 i 小元素
int rand_select( std::vector<int> &a, int p, int q, int i ){
    if( p == q )
        return a[ p ];
    int r = rand_partition( a, p, q );
    int k = r - p + 1;
    if( i == k )
        return a[ r ];
    else if( i < k )
        return rand_select( a, p, r - 1, i );
    else
        return rand_select( a, r + 1, q, i );
}
int rand_select( std::vector<int> &a, int i ){
    return rand_select( a, 0, a.size( ) - 1, i );
}


int POW( int a, int n ){
    if( n == 1 )
        return a;
    if( n % 2 )
        return POW( a, n / 2 ) * POW( a, n / 2 ) * a;    
    else
        return POW( a, n / 2 ) * POW( a, n / 2 );
}
int main( ){
    int num = POW( 2, 4 );
    // std::vector<int> array{ 7,8,1,3,5,4,9,1,6,7,8,9,2,1,1,3 };
    // int val = rand_select( array, 6 );
    // median_of_median_of_five_select( array, 0 );
    return 0;
}


 