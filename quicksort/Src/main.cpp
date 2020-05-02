/*
 * @Author: your name
 * @Date: 2020-04-13 21:46:15
 * @LastEditTime: 2020-04-18 11:51:55
 * @LastEditors: Please set LastEditors
 * @Description: 算法导论 quicksort
 * @FilePath: \quicksort\Src\main.cpp
 */


#include <iostream>
#include <vector>
// 从小到大
int partition( std::vector<int> &a, int p, int q ){
    int i = p;
    for( int j = p + 1; j <= q; ++j ){
        if( a[ j ] < a[ p ] )
            std::swap( a[ ++i ], a[ j ] );  
    }
    std::swap( a[ p ], a[ i ] );
    return i;
}
void quicksort( std::vector<int> &a, int p, int r ){
    if( p < r ) {
        // 分治 确定一个 mid 位置
        int mid = partition( a, p, r );
        // 分
        quicksort( a, p, mid - 1 );
        quicksort( a, mid + 1, r );
    }
}
void quicksort( std::vector<int> &a ){
    quicksort( a, 0, a.size( ) - 1 );
}
void countingsort( std::vector<int> &a, int maxval ){
    // 保存个元素的排序序号
    std::vector<int> c( maxval + 1, 0 );
    // 排好序的数组
    std::vector<int> b( a.size( ) );
    for( auto &x : a )
        ++c[x];
    for( int i = 1; i < c.size( ); ++i )
        c[ i ] += c[ i- 1 ];
    for( int j = a.size( ) - 1; j >= 0; --j ){
        b[ c[ a[ j ] ] ] = a[ j ];
        --c[ a[ j ] ];
    }
    std::swap( a, b );
}
int main( ){
    // std::vector<int> a{ 10,9,8,7,6,5,4,3,2,1};
    std::vector<int> a{ 1,1,1,1,1,1,1};  
    // std::vector<int> a{ 5,6,4,8,7,1,9,10,11,2,3,4,1,9,6,5,4 };
    // int pos = partition( a, 0, a.size( ) - 1 );
    quicksort( a );
    // std::vector<int> array{ 4, -3, 5, -2, -1, 2, -2 };
    std::vector<int> array{ 7,8,1,3,5,4,9,1,6,7,8,9,2,1,1,3 };
    countingsort( array, 9 );
    return 0;
}


 