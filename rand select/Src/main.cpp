/*
 * @Author: your name
 * @Date: 2020-04-13 21:46:15
 * @LastEditTime: 2020-04-25 10:09:20
 * @LastEditors: Please set LastEditors
 * @Description: �㷨���� �����ѡ��� i ����СԪ��
 * @FilePath: \quicksort\Src\main.cpp
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include "Random.h"


// ��С����
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
// ��������ѡ���� i СԪ��
// int rand_select( std::vector<int> &a, int p, int q, int i ){
//     if( p == q )
//         return a[ p ];
//     int r = rand_partition( a, p, q );
//     int k = r - p + 1;
//     if( i == k )
//         return a[ r ];
//     else if( i < k )
//         return rand_select( a, p, r - 1, i );
//     else
//         return rand_select( a, r + 1, q, i - k );
// }
// ��С����
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
int rand_select( std::vector<int> &a, int p, int q, int i ){
    if( p == q )
        return a[ p ];
    int r = rand_partition( a, p, q );
    if( i == r )
        return a[ r ];
    else if( i < r )
        return rand_select( a, p, r - 1, i );
    else
        return rand_select( a, r + 1, q, i );
}
int rand_select( std::vector<int> &a, int i ){
    // �� i ת��Ϊ�±�� 1 ��ʼ
    i = i - 1;
    return rand_select( a, 0, a.size( ) - 1, i );
}

int main( ){

    std::vector<int> array{ 7,8,1,3,5,4,9,10,6,7,8,9,2,12,11,3 };
    int val = rand_select( array, 15 );
    return 0;
}


 