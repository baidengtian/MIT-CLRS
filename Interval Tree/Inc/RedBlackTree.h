/*
 * @Author: your name
 * @Date: 2020-04-25 17:12:26
 * @LastEditTime: 2020-04-26 10:15:35
 * @LastEditors: Please set LastEditors
 * @Description: Interval Tree 区间树
 * @FilePath: \Interval Tree\Inc\RedBlackTree.h
 */

#pragma

#include <iostream>
#include <string>
#include <vector>

class isLessThan{
public:
    bool operator()( const std::pair<int, int> p1,
    const std::pair<int, int> p2 )   const{
        return p1.first > p2.first;
    }
};

template <  typename Object, typename Comparable = isLessThan >

class RedBlackTree{

private:
    struct Node{
        Object value;
        bool color;
        Node *leftTree, *rightTree, *parent;
        // 左子树、右子树以及当前节点的右段端点的最大值
        int m;                  
        Node() : value{ Object{ } }, color{ RED }, leftTree{ nullptr }, 
        rightTree{ nullptr }, parent{ nullptr }, m{ value.second } { }

        Node( Object val, Node *lf, Node *rt, Node *pt, bool col = RED )
        : value{ val }, leftTree{ lf }, rightTree{ rt }, parent{ pt }, color{ col }, m{ val.second } { }
        
        // 返回祖父节点
        Node* grandparent( ){
            if( parent == nullptr )
                return nullptr;
            return parent->parent;
        }
        // 返回叔父节点
        Node* uncle( ){
            if( grandparent( ) == nullptr )
                return nullptr;
            if( parent == grandparent( )->rightTree )
                return grandparent( )->leftTree;
            else
                return grandparent( )->rightTree;
        }
        // 返回兄弟节点
        Node* sibling( ){
            if( parent->leftTree == this )
                return parent->rightTree;
            else
                return parent->leftTree;
        }
    };
    Node *root, *NIL;
    Comparable cmp;
    // 右旋 p 的父节点 fa
    //          gp                      gp
    //         /                       /
    //       fa                       p
    //       /          -->          / \
    //      p                       x   fa
    //     / \                          /                
    //    x   y                        y
    void rotate_right( Node *p ){
        Node *gp = p->grandparent( );
        Node *fa = p->parent;
        Node *y = p->rightTree;

        fa->leftTree = y;

        if( y != NIL )
            y->parent = fa;
        p->rightTree = fa;
        fa->parent = p;

        if( root == fa )
            root = p;
        p->parent = gp;

        if( gp != nullptr )
            if( gp->leftTree == fa )
                gp->leftTree = p;
            else
                gp->rightTree = p; 


        // 更新 m
        fa->m = updatam( fa );
        p->m = updatam( p );
        if( gp != nullptr )
            gp->m = updatam( gp );

    }
    // 左旋 p 的父节点 fa 
    void rotate_left(Node *p){
        if(p->parent == NULL){
            root = p;
            return;
        }
        Node *gp = p->grandparent();
        Node *fa = p->parent;
        Node *y = p->leftTree;

        fa->rightTree = y;

        if(y != NIL)
            y->parent = fa;
        p->leftTree = fa;
        fa->parent = p;

        if(root == fa)
            root = p;
        p->parent = gp;

        if(gp != NULL){
            if(gp->leftTree == fa)
                gp->leftTree = p;
            else
                gp->rightTree = p;
        }

        // 更新 m
        fa->m = updatam( fa );
        p->m = updatam( p );
        if( gp != nullptr )
            gp->m = updatam( gp );


    }
    // 向某节点插入一个值
    void insert( Node *p, Object data ){
     
        if( data.second > p->m )
            p->m = data.second;
        // if( p->value >= data )
        if( cmp( p->value, data ) )
        {
            if( p->leftTree != NIL )
                insert( p->leftTree, data );
            else {
                Node *tmp = new Node(data, NIL, NIL, p );
                p->leftTree = tmp;
                insert_case( tmp );
            }
        }
        else
        {
            if( p->rightTree != NIL )
                insert( p->rightTree, data );
            else{
                // case 2 插入节点的父节点是黑色的 不执行 insert_case( tmp )
                Node *tmp = new Node( data, NIL, NIL, p );
                p->rightTree = tmp;     
                insert_case( tmp );
            }
        }
    }

    inline void insert_case1( Node *p ){
        root = p;
        p->color = BLACK;
    }
    inline void insert_case3( Node *p ){
        p->parent->color = p->uncle( )->color = BLACK;
        p->grandparent( )->color = RED;
        // 上滤
        insert_case( p->grandparent( ) ); 
    }
    inline void insert_case4_1( Node *p ){
        rotate_left( p );
        p = p->leftTree;
        // 下一步 case 5
        insert_case5( p );
    }
    inline void insert_case4_2( Node *p ){
        rotate_right( p );
        p = p->rightTree;
        // 下一步 case 5
        insert_case5( p );
    }
    inline void insert_case5( Node *p ){
        if( p->parent->leftTree == p && p->grandparent( )->leftTree == p->parent ){
                p->parent->color = BLACK;
                p->grandparent( )->color = RED;
                rotate_right( p->parent );
            }
        // case 5 P 是右儿子 p 的父节点是右儿子 父亲是红节点 叔父是黑节点
        else if( p->parent->rightTree == p && p->grandparent( )->rightTree == p->parent ){
            p->parent->color = BLACK;
            p->grandparent( )->color = RED;
            rotate_left( p->parent );
        }
    }
    void insert_case( Node *p ){
        // 如果父节点为黑节点直接插入 以下判断全为否
        // case 1 空树插入     
        if( p->parent == nullptr ){
            insert_case1( p );
            return;
        }
        if( p->parent->color == RED ){
            // case 3 插入节点父节点 叔父节点都为红色
            if( p->uncle( )->color == RED ){
                insert_case3( p );
            }
            else{
                // 注意 ：基维百科 C++ 代码这里存在问题
                // case 4 P 是右儿子 p 的父节点是左儿子 父亲是红节点 叔父是黑节点
                if( p->parent->rightTree == p && p->grandparent( )->leftTree == p->parent ){
                    insert_case4_1( p );
                }
                // case 4 p 是左儿子  p 的父节点是右儿子 父亲是红节点 叔父是黑节点 ??????
                else if( p->parent->leftTree == p && p->grandparent( )->rightTree == p->parent ){
                    insert_case4_2( p );
                }
                // case 5 P 是左儿子 p 的父节点是左儿子 父亲是红节点 叔父是黑节点
                else {
                    insert_case5( p );
                }

            }
        }
    }
    // 得到最小节点
    Node* getSmallestChild( Node *p ){
        if( p->leftTree == NIL )
            return p;
        return getSmallestChild( p->leftTree );
    }

    // 沿 p 节点向上更新 m 值直至根节点
    void updatamup( Node *p ){
        Node *tmp = p;
        for( ; ; ){
            tmp->m = updatam( tmp );
            if( tmp != root )
                tmp = tmp->parent;
            else
                break;
        }
    }  
    // 删除节点
    bool delete_child( Node *p, Object data ){
        // 递归删除
        if( cmp( p->value, data ) ) 
        // if( p->value > data )
        {
            if( p->leftTree == NIL )
                return false;
            return delete_child( p->leftTree, data );
        }
        else if( cmp( data, p->value ) )
        // else if( p->value < data )
        {
            if( p->rightTree == NIL )
                return false;
            return delete_child( p->rightTree, data );
        }
        // else if( p->value == data )
        else
        {
            // 被删除节点没有右子树时
            if( p->rightTree == NIL ){
                // 用于记录删除着的父节点
                Node *p_parent = p->parent;
                delete_one_child( p );
                // 向上更新 m 值
                updatamup( p_parent );
                return true;
            }
            // 用右子树的最小值代替待删除节点
            Node *smallest = getSmallestChild( p->rightTree );
            // 用于记录删除着的父节点
            Node *smallestparent = smallest->parent;
            std::swap( p->value, smallest->value );
            delete_one_child( smallest );
            // 向上更新 m 值
            updatamup( smallestparent );
            return true;
        }
        // else
        return false;
    }
    // 删除至多有一个儿子的 p 节点
    void delete_one_child( Node *p )
    {
        Node *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
        // 删除空树的节点
        if( p->parent == nullptr && p->leftTree == NIL && p->rightTree == NIL ){
            p = nullptr;
            root = p;
            return;
        }
        // 删除根节点
        if( p->parent == nullptr ){
            delete p;
            child->parent = nullptr;
            root = child;
            root->color = BLACK;
            return;
        }

        // 此处就是删除操作
        // p 是左儿子 
        if( p->parent->leftTree == p )
            p->parent->leftTree = child;
        else
            p->parent->rightTree = child;
        
        child->parent = p->parent;

        // 如果删除节点是黑色的
        if( p->color == BLACK ){
            // 被删除节点是黑色 它的儿子是红色时
            if( child->color == RED )
                child->color = BLACK;
            else
                // 被删除节点和别删除节点的儿子都是黑色时 进行调整
                delete_case( child );
        }

        delete p;
    }

    void delete_case( Node *p ){
        // CASE 1 删除节点是根节点
        if( p->parent == nullptr ){
            p->color = BLACK;
        }
        // CASE 2 删除节点的兄弟是红色的
        // 再进行  CASE 3 | 4 | 5 | 6 平衡减少的一个黑色节点
        if( p->sibling( )->color == RED ){
            p->parent->color = RED;
            p->sibling( )->color = BLACK;
            if( p == p->parent->leftTree )
                rotate_left( p->sibling( ) );
                // 注意 维基百科 C++代码 此处有错误
                // rotate_left( p->parent );
            else
                rotate_right( p->sibling( ) );
                // 注意 维基百科 C++代码 此处有错误
                // rotate_right( p->parent );
        }
        // CASE 3
        if( p->parent->color == BLACK 
            && p->sibling( )->color == BLACK
            && p->sibling( )->leftTree->color == BLACK 
            && p->sibling( )->rightTree->color == BLACK ){
            p->sibling( )->color = RED;
            // 上滤： 平衡 p 通过 p 的所有路径黑色节点都少了一个
            delete_case( p->parent );
        }
        // CASE 4
        else if( p->parent->color ==RED 
            && p->sibling( )->color == BLACK
            && p->sibling( )->leftTree->color == BLACK 
            && p->sibling( )->rightTree->color == BLACK ){
            p->sibling( )->color = RED;
            p->parent->color = BLACK;
        }
        else{
            // CASE 5
            if( p->sibling( )->color == BLACK ){
                if( p == p->parent->leftTree 
                    && p->sibling( )->leftTree->color == RED
                    && p->sibling( )->rightTree->color == BLACK ){
                    p->sibling( )->color = RED;
                    p->sibling( )->leftTree->color = BLACK;
                    rotate_right( p->sibling( )->leftTree );
                }
            }
            else if( p == p->parent->rightTree
                    && p->sibling( )->leftTree->color == BLACK
                    && p->sibling( )->rightTree->color == RED ){
                p->sibling( )->color = RED;
                p->sibling( )->rightTree->color = BLACK;
                rotate_left( p->sibling( )->rightTree );
            }
            // CASE 6
            p->sibling( )->color = p->parent->color;
            p->parent->color = BLACK;
            if( p == p->parent->leftTree ){
                p->sibling( )->rightTree->color = BLACK;
                rotate_left( p->sibling( ) );
            }
            else{
                p->sibling( )->leftTree->color = BLACK;
                rotate_right( p->sibling( ) );
            }
        }

    }
    // 中序遍历
    void inorder( Node * p ){
        if( p == NIL )
            return;
        if( p->leftTree )
            inorder( p->leftTree );
        
        // std::cout << p->value << "  ";
        std::cout << p->value.first << "    " << p->value.second << "    " 
        << p->m << "    " << outputColor( p->color ) <<std::endl;
        
        if( p->rightTree )
            inorder( p->rightTree );
    }
    std::string outputColor( bool color ){
        return color ? "BLACK" : "RED";
    }
    void DeleteTree( Node *p ){
        if( !p || p == NIL )
            return;
        DeleteTree( p->leftTree );
        DeleteTree( p->rightTree );
        delete p;
    }
    // 更新最大右端点m
    int updatam( Node *p ){
        int maxval = 0;
        if(  p != NIL ){
            maxval = p->value.second;
            if( p->leftTree != NIL )
                maxval = std::max( maxval, p->leftTree->m );
            if( p->rightTree != NIL )
                maxval = std::max( maxval, p->rightTree->m );
        }
        return maxval;
        
    }
    // 找出子树 x 中与 i 有重合的所有区间
    std::vector< Object > searchlist( Node *x, Object i )  {

        static std::vector< Object > retv;
        bool flag = false;
        for( ;x != NIL && ( i.first > x->value.second 
        || x->value.first > i.second ); ){
            if( x->leftTree != NIL && i.first <= x->leftTree->m )
                x = x->leftTree;
            else if( x->rightTree != NIL )
                x = x->rightTree;
            else{
                flag = true;
                break;
            }
        }

        if( !flag )
            retv.push_back( x->value );
        
        if( i.first < x->value.second && x->leftTree != NIL )
            searchlist( x->leftTree, i );
        if(x->value.first < i.second && x->rightTree != NIL )
            searchlist( x->rightTree, i );

        return retv;
    }
public:
    RedBlackTree( ){
        NIL = new Node();
        NIL->color = BLACK;
        NIL->m = 0;
        root = nullptr;
    }
    ~RedBlackTree( ){
        if( root )
            DeleteTree( root );
        delete NIL;
    } 
    void inorder( ){
        if( root == nullptr )
            return;
        inorder( root );
        std::cout << std::endl;
    }
    enum { RED, BLACK };
    // 插入新节点
    void insert( Object x ){
        if( root == nullptr ){
            root = new Node( x, NIL, NIL, nullptr, BLACK );
        }else{
            insert( root, x );
        }
    }
    // 删除节点
    bool remove( Object data ){
        return delete_child( root, data );
    }
    // 寻找与 i 重合的区间
    Object search( Object i )   const{
        Node *x = root;
        while( x != NIL && ( i.first > x->value.second 
        || x->value.first > i.second ) ){
            if( x->leftTree != NIL && i.first <= x->leftTree->m )
                x = x->leftTree;
            else
                x = x->rightTree;
        }
        return x->value;
    }
    // 找出子树 x 中与 i 有重合的所有区间
    std::vector< Object > searchlist( Object i )  {
        return searchlist( root, i );      
    }


};


