/*
 * @Author: your name
 * @Date: 2020-04-03 16:31:28
 * @LastEditTime: 2020-04-15 20:05:49
 * @LastEditors: Please set LastEditors
 * @Description: Queue ÈÝÆ÷ÊµÏÖ
 * @FilePath: \queue\Src\main.cpp
 */

#include <iostream>
#include <vector>


bool binarySearch( std::vector<int> &array, int begin, int end, int element ){
    
    if( begin > end )
        return false;
    int mid = ( end + begin ) / 2;
    if( array[ mid ] > element )
        binarySearch( array, begin, mid - 1, element );
    else if( array[ mid ] < element )
        binarySearch( array, mid + 1, end, element );
    else
        return true;
}
bool binarySearch( std::vector<int> &array, int element ){
    return binarySearch( array, 0, array.size( ) - 1, element );
}
bool binarySearch2( std::vector<int> &array, int element ){

    int mid = -1, left = 0, right = array.size( ) - 1;
    while( left != mid ){
        mid = ( left + right ) / 2;
        if( array[ mid ] > element )
            right = mid;
        else if( array[ mid ] < element )
            left = mid;
        else
            return true;
    }
    
    return array[ left ] == element || array[ right ] == element;
}

bool AddTwoNumbers( std::vector<int> &vi, int sum ){
    for( auto &x : vi )
        if( binarySearch( vi, sum - x ) )
            return true;
    return false;
}
struct node
{
    int maxleft;
    int maxright;
    int summax;
};

node FindMaxCrossingSub( std::vector<int> &a, int left, int mid, int right ){
    int leftsum = INT_MIN;
    int sum = 0;
    int maxleft = 0;
    for( int i = mid; i >= left; --i ){
        sum = sum + a[ i ];
        if( sum > leftsum ){
            leftsum = sum;
            maxleft = i;
        }
    }
    int rightsum = INT_MIN;
    sum = 0;
    int maxright = 0;
    for( int i = mid + 1; i <= right; ++i ){
        sum = sum + a[ i ];
        if( sum > rightsum ){
            rightsum = sum;
            maxright = i;
        }
    }
    return { maxleft, maxright, leftsum + rightsum };
}
class Compare{
public:
    bool operator( )( const node &n1, const node &n2 )  const{
        return n1.summax < n2.summax;
    }
};
node FindMaxSub( std::vector<int> &a, int left, int right ){
    if( left == right )
        return{ left, right, a[ left ] };
    else{
        int mid = ( left + right ) / 2;
        node lnode = FindMaxSub( a, left, mid );
        node rnode = FindMaxSub( a, mid + 1, right );
        node mnode = FindMaxCrossingSub( a, left, mid, right );
        return std::max( std::max( lnode, rnode, Compare{ } ), mnode, Compare{ } );
    }    
}
node FindMaxSub2( std::vector<int> array ){
    node summax{ 0, 0, INT_MIN };
    for( int i = 0; i < array.size( ); ++i ){
        int sum = 0;
        for( int j = i; j < array.size( ); ++j ){
            sum += array[ j ];
            if( sum >= summax.summax )
                summax = { i, j, sum }; 
        }
    }
    return summax;
}
int FindMaxSub3( std::vector<int> &array ){
    int summax = INT_MIN;
    int sum = 0;
    for( auto &x : array ){

        sum += x;      
        if( summax < sum )
            summax = sum;
        if( sum < 0 )
            sum = 0;
                   
    }
    return summax;
}
int FindMaxSub4( std::vector<int> &array ){
    int summax = 0;
   
    for( int i = 0; i < array.size( ); ++i ){
        int sum = 0;
        int basesum = 0;
        basesum += array[ i ];
        if( basesum > summax )
            summax = basesum;
        for( int j = i; j > 0 ; --j ){
            sum += array[ j ];
            if( sum > summax )
                summax = sum;
        }
    }
    return summax;
}
int main( ){


    // std::vector<int> vi{0,1,2,3,5,6,7,9,10};
    // // binarySearch( vi, 10 );
    // std::cout << binarySearch( vi, 118 ) << "   " << binarySearch( vi, 118 )
    // << "   " << binarySearch( vi, 7 ) << "   " << binarySearch( vi, 10 );
    // bool flag = AddTwoNumbers( vi, 16 );
    std::vector<int> array{ 4, -3, 5, -2, -1, 2, -2 };
    // int maxmid = FindMaxCrossingSub( array, 0, ( array.size( ) - 1 ) / 2, array.size( ) - 1 ).summax;
    // std::vector<int> array{ -4, -3, -5, -2, -1, -2, -6, -2 };
    int maxval = FindMaxSub( array, 0, array.size( ) - 1 ).summax;
    int maxval2 = FindMaxSub2( array ).summax;
    int maxval3 = FindMaxSub3( array );
    int maxval4 = FindMaxSub4( array );
    return 0;
}




 