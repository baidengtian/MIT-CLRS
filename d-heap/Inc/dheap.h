/*
 * @Author: your name
 * @Date: 2020-04-22 19:54:16
 * @LastEditTime: 2020-04-23 16:11:32
 * @LastEditors: Please set LastEditors
 * @Description: d 堆 最大堆
 * @FilePath: \d-heap\Inc\dheap.h
 */
#pragma
#include <iostream>
#include <vector>

template < typename Comparable >
class dheap{

public:
    dheap( std::vector<Comparable> &a, int d_val )
    : array{ a }, d{ d_val } {
        currentSize = a.size( ) - 1;
        buildheap( );
    }
    dheap( int d_val = 3 ) : d{ d_val } ,currentSize{ 0 } {

    }
    // i 节点的父节点
    int parent( int i ) const{
        return ( i - 1 ) / d + 1;
    }
    // i 节点的第 j 个儿子 j 从 1 开始
    int child( int i, int j )   const{
        return d * ( i - 1 ) + j + 1;
    }
    // 返回 i 位置的元素值
    Comparable getElement( int i )  const{
        return array[ i ];
    }
    // 取出堆顶最大元素
    Comparable extract_max( ){
        Comparable max = array[ 1 ];
        array[ 1 ] = array[ array.size( ) - 1 ];
        --currentSize;
        // percolateDown( 1 );
        heapify( array, 1, currentSize, d );
        return max;
    }
    // 把 i 的键值增加到 k
    bool increase_key( int i, Comparable k ){
        if( array[ i ] > k )
            return false;
        else{
            array[ i ] = k;
            // i 的父节点的键值小于 i 节点的键值
            // 上滤
            if( array[ ( i - 1 ) / d + 1 ] < array[ i ] ){
                std::swap( array[ ( i - 1 ) / d + 1 ], array[ i ] );
                increase_key( ( i - 1 ) / d + 1, array[ ( i - 1 ) / d + 1 ] );
            }           
        }           
        return true;
    }
    // 插入元素 k
    void insert( Comparable k ){
        if( currentSize + 1 > array.capacity( ) )
            array.resize( 2 * array.capacity( ) );
        array[ currentSize + 1 ] = { INT_MIN };
        increase_key( currentSize + 1, k );
        ++currentSize;
    }
    // 打印
    void print( )   const{
        for( int i = 1; i <= currentSize; ++i )
            std::cout << array[ i ] << "    ";
    }
private:

    // 堆化
    void heapify( std::vector<Comparable> &A, int i, int n, int dd ){
        int j = i;
        for( int k = dd - 1; k >= 0; --k ){
            if( dd * i + k <= n && A[ dd * i + k ] > A[ j ] )
                j = d * i + k;
        }
        if( i != j ){
            std::swap( A[ i ], A[ j ] );
            heapify( A, j, n, d );
        } 
    }
    // 构建堆 下标从1开始
    void buildheap( ){
        for( int i = ( currentSize + d - 2 ) / d; i > 0; --i ){
            percolateDown( i );
        }
    }
    // 下滤
    void percolateDown( int i ){
        int maxchild = findMaxChild( i );
        if( maxchild <= currentSize &&
        array[ maxchild ] > array[ i ] ){
            std::swap( array[ maxchild ], array[ i ] );
            percolateDown( maxchild );
        }           
    }
    // 找出 i 节点的最大的儿子
    inline int findMaxChild( int i ){
        int max = INT_MIN;
        int pos = 0;
        for( int k = 1; k <= d; ++k ){
            int childpos = child( i, k );
            if( childpos <= currentSize && max < array[ childpos ] ){
                max = array[ childpos ]; 
                pos = childpos; 
            }        
        }
        return pos;
    }

    // root 存在 array[ 1 ]
    std::vector<Comparable> array;
    // d堆 2/3/4...N堆
    int d;
    // 当前堆大小
    int currentSize;

};
