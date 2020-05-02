/*
 * @Author: your name
 * @Date: 2020-04-25 17:12:26
 * @LastEditTime: 2020-04-26 10:18:48
 * @LastEditors: Please set LastEditors
 * @Description: interval tree Çø¼äÊ÷
 * @FilePath: \Interval Tree\Src\main.cpp
 */



#include <iostream>
#include "RedBlackTree.h"
#include <climits>

int main( )
{
	// RedBlackTree<int> t;
	// t.insert( 1 );
	// t.insert( 22 );
	// t.insert( 3 );
	// t.insert( 14 );
	// t.insert( 11 );
	// t.insert( 9 );
	// t.insert( 81 );
	// t.remove( 1 );
	// t.inorder( );
	RedBlackTree<std::pair<int,int>> t;
	t.insert({17,19});
	t.insert({22,23});
	t.insert({5,11});
	t.insert({4,8});
	t.insert({7,10});
	t.insert({15,18});
	t.insert({1,2});
	t.remove({1,2});
	t.remove({22,23});
	t.remove({15,18});
	// t.insert({17,19});
	// t.insert({5,11});
	// t.insert({4,8});
	// t.insert({15,18});
	// t.insert({7,10});
	// t.insert({22,23});
	std::pair<int,int> result = t.search({12,14});
	std::vector<std::pair<int,int>> resv = t.searchlist({ 16,18 });
	t.inorder( );
	return 0; 
}
