/*
 * @Author: lsyy
 * @Date: 2020-04-01 21:02:49
 * @LastEditTime: 2020-04-27 21:59:06
 * @LastEditors: Please set LastEditors
 * @Description: list 容器实现
 * @FilePath: \List\Inc\List.h
 */

#pragma

#include "Random.h"
#include <iostream>
#include <algorithm>

#define MAX_lEVEL	100			// 最大层数

using namespace std;

template <typename Object>

class skiplist{
private:
	struct node
	{
		Object data;
		node **next;
		node(  Object val, int level = 1 ) : data{ val } {
			next = new node*[ level ];
			for( int i = level; i >= 0; --i )
				next[ i ] = nullptr;
		}
	};
	node *head;
	Random r;
	// 层数 : 1,2,3,4,5...N
	int level;
public:
	skiplist( ) : level{ 1 } { 
		head = new node{ INT_MIN, MAX_lEVEL };
	}
	~skiplist( ) {
		makeEmpty( );
	}
	void makeEmpty( ){
		node *tmp;
		for( node *it = head; it != nullptr; it = tmp ){
			tmp = it->next[1];
			// if( it->next != nullptr )
			// 	delete [] it->next;
			delete it;			
		}
	}
	// 插入操作
	void insert( const Object &x ){
		// 随机化
		int r_lev = 1;
		while( r.randomInt( 0,1 ) )
			++r_lev;

		if( r_lev > level )
			level = r_lev;
			
		node *tmp = head;
		node *newNode = new node{ x, r_lev };

		// 查找和插入
		for( int i = r_lev; i > 0; ){
			for( node *it = tmp; ; it = it->next[ i ] ){

				// 一定要先 it == nullptr 再 it->data > x
				if( it == nullptr || it->data > x ){
					
					newNode->next[ i ] = tmp->next[i];
					tmp->next[i] = newNode;
					--i;
					break;
				}
				tmp = it;
			}
		}

	}

	// 查找操作
	bool contains( const Object &x )	const{
		node *tmp = head;
		for( int i = level; i > 0; ){
			for( node *it = tmp; ; it = it->next[ i ] ){
				// 一定要先 it == nullptr 再 it->data > x
				if( it == nullptr || it->data > x ){
					--i;
					break;
				}else if( it->data == x ){
					return true;
				}

				tmp = it;
			}
		}
		return false;
	}

	// 移除节点
	bool remove( const Object &x ){
		node *tmp = head;
		node *deletenode;
		bool bret = false;
		for( int i = level; i > 0; ){
			for( node *it = tmp; ; it = it->next[ i ] ){
				// 一定要先 it == nullptr 再 it->data > x
				if( it == nullptr || it->data >= x ){
					--i;
					break;
				}else if( it->data == x ){
					deletenode = it;
					tmp->next[i] = it->next[i];
					bret = true;
					--i;
					break;
				}
				tmp = it;
			}
		}
		if( bret )
			delete deletenode;

		return bret;
	}
	// 打印
	void print( )	const{

		for( int i = level; i > 0; --i ){
			node *tmp = head;
			while( tmp != nullptr ){
			std::cout << tmp->data << "	";
			tmp = tmp->next[i];
			}
			std::cout << std::endl;
		}
		
	}
	
};