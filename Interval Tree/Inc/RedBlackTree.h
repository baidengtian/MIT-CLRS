/*
 * @Author: your name
 * @Date: 2020-04-25 17:12:26
 * @LastEditTime: 2020-04-26 10:15:35
 * @LastEditors: Please set LastEditors
 * @Description: Interval Tree ������
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
        // ���������������Լ���ǰ�ڵ���Ҷζ˵�����ֵ
        int m;                  
        Node() : value{ Object{ } }, color{ RED }, leftTree{ nullptr }, 
        rightTree{ nullptr }, parent{ nullptr }, m{ value.second } { }

        Node( Object val, Node *lf, Node *rt, Node *pt, bool col = RED )
        : value{ val }, leftTree{ lf }, rightTree{ rt }, parent{ pt }, color{ col }, m{ val.second } { }
        
        // �����游�ڵ�
        Node* grandparent( ){
            if( parent == nullptr )
                return nullptr;
            return parent->parent;
        }
        // �����常�ڵ�
        Node* uncle( ){
            if( grandparent( ) == nullptr )
                return nullptr;
            if( parent == grandparent( )->rightTree )
                return grandparent( )->leftTree;
            else
                return grandparent( )->rightTree;
        }
        // �����ֵܽڵ�
        Node* sibling( ){
            if( parent->leftTree == this )
                return parent->rightTree;
            else
                return parent->leftTree;
        }
    };
    Node *root, *NIL;
    Comparable cmp;
    // ���� p �ĸ��ڵ� fa
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


        // ���� m
        fa->m = updatam( fa );
        p->m = updatam( p );
        if( gp != nullptr )
            gp->m = updatam( gp );

    }
    // ���� p �ĸ��ڵ� fa 
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

        // ���� m
        fa->m = updatam( fa );
        p->m = updatam( p );
        if( gp != nullptr )
            gp->m = updatam( gp );


    }
    // ��ĳ�ڵ����һ��ֵ
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
                // case 2 ����ڵ�ĸ��ڵ��Ǻ�ɫ�� ��ִ�� insert_case( tmp )
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
        // ����
        insert_case( p->grandparent( ) ); 
    }
    inline void insert_case4_1( Node *p ){
        rotate_left( p );
        p = p->leftTree;
        // ��һ�� case 5
        insert_case5( p );
    }
    inline void insert_case4_2( Node *p ){
        rotate_right( p );
        p = p->rightTree;
        // ��һ�� case 5
        insert_case5( p );
    }
    inline void insert_case5( Node *p ){
        if( p->parent->leftTree == p && p->grandparent( )->leftTree == p->parent ){
                p->parent->color = BLACK;
                p->grandparent( )->color = RED;
                rotate_right( p->parent );
            }
        // case 5 P ���Ҷ��� p �ĸ��ڵ����Ҷ��� �����Ǻ�ڵ� �常�Ǻڽڵ�
        else if( p->parent->rightTree == p && p->grandparent( )->rightTree == p->parent ){
            p->parent->color = BLACK;
            p->grandparent( )->color = RED;
            rotate_left( p->parent );
        }
    }
    void insert_case( Node *p ){
        // ������ڵ�Ϊ�ڽڵ�ֱ�Ӳ��� �����ж�ȫΪ��
        // case 1 ��������     
        if( p->parent == nullptr ){
            insert_case1( p );
            return;
        }
        if( p->parent->color == RED ){
            // case 3 ����ڵ㸸�ڵ� �常�ڵ㶼Ϊ��ɫ
            if( p->uncle( )->color == RED ){
                insert_case3( p );
            }
            else{
                // ע�� ����ά�ٿ� C++ ���������������
                // case 4 P ���Ҷ��� p �ĸ��ڵ�������� �����Ǻ�ڵ� �常�Ǻڽڵ�
                if( p->parent->rightTree == p && p->grandparent( )->leftTree == p->parent ){
                    insert_case4_1( p );
                }
                // case 4 p �������  p �ĸ��ڵ����Ҷ��� �����Ǻ�ڵ� �常�Ǻڽڵ� ??????
                else if( p->parent->leftTree == p && p->grandparent( )->rightTree == p->parent ){
                    insert_case4_2( p );
                }
                // case 5 P ������� p �ĸ��ڵ�������� �����Ǻ�ڵ� �常�Ǻڽڵ�
                else {
                    insert_case5( p );
                }

            }
        }
    }
    // �õ���С�ڵ�
    Node* getSmallestChild( Node *p ){
        if( p->leftTree == NIL )
            return p;
        return getSmallestChild( p->leftTree );
    }

    // �� p �ڵ����ϸ��� m ֱֵ�����ڵ�
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
    // ɾ���ڵ�
    bool delete_child( Node *p, Object data ){
        // �ݹ�ɾ��
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
            // ��ɾ���ڵ�û��������ʱ
            if( p->rightTree == NIL ){
                // ���ڼ�¼ɾ���ŵĸ��ڵ�
                Node *p_parent = p->parent;
                delete_one_child( p );
                // ���ϸ��� m ֵ
                updatamup( p_parent );
                return true;
            }
            // ������������Сֵ�����ɾ���ڵ�
            Node *smallest = getSmallestChild( p->rightTree );
            // ���ڼ�¼ɾ���ŵĸ��ڵ�
            Node *smallestparent = smallest->parent;
            std::swap( p->value, smallest->value );
            delete_one_child( smallest );
            // ���ϸ��� m ֵ
            updatamup( smallestparent );
            return true;
        }
        // else
        return false;
    }
    // ɾ��������һ�����ӵ� p �ڵ�
    void delete_one_child( Node *p )
    {
        Node *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
        // ɾ�������Ľڵ�
        if( p->parent == nullptr && p->leftTree == NIL && p->rightTree == NIL ){
            p = nullptr;
            root = p;
            return;
        }
        // ɾ�����ڵ�
        if( p->parent == nullptr ){
            delete p;
            child->parent = nullptr;
            root = child;
            root->color = BLACK;
            return;
        }

        // �˴�����ɾ������
        // p ������� 
        if( p->parent->leftTree == p )
            p->parent->leftTree = child;
        else
            p->parent->rightTree = child;
        
        child->parent = p->parent;

        // ���ɾ���ڵ��Ǻ�ɫ��
        if( p->color == BLACK ){
            // ��ɾ���ڵ��Ǻ�ɫ ���Ķ����Ǻ�ɫʱ
            if( child->color == RED )
                child->color = BLACK;
            else
                // ��ɾ���ڵ�ͱ�ɾ���ڵ�Ķ��Ӷ��Ǻ�ɫʱ ���е���
                delete_case( child );
        }

        delete p;
    }

    void delete_case( Node *p ){
        // CASE 1 ɾ���ڵ��Ǹ��ڵ�
        if( p->parent == nullptr ){
            p->color = BLACK;
        }
        // CASE 2 ɾ���ڵ���ֵ��Ǻ�ɫ��
        // �ٽ���  CASE 3 | 4 | 5 | 6 ƽ����ٵ�һ����ɫ�ڵ�
        if( p->sibling( )->color == RED ){
            p->parent->color = RED;
            p->sibling( )->color = BLACK;
            if( p == p->parent->leftTree )
                rotate_left( p->sibling( ) );
                // ע�� ά���ٿ� C++���� �˴��д���
                // rotate_left( p->parent );
            else
                rotate_right( p->sibling( ) );
                // ע�� ά���ٿ� C++���� �˴��д���
                // rotate_right( p->parent );
        }
        // CASE 3
        if( p->parent->color == BLACK 
            && p->sibling( )->color == BLACK
            && p->sibling( )->leftTree->color == BLACK 
            && p->sibling( )->rightTree->color == BLACK ){
            p->sibling( )->color = RED;
            // ���ˣ� ƽ�� p ͨ�� p ������·����ɫ�ڵ㶼����һ��
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
    // �������
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
    // ��������Ҷ˵�m
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
    // �ҳ����� x ���� i ���غϵ���������
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
    // �����½ڵ�
    void insert( Object x ){
        if( root == nullptr ){
            root = new Node( x, NIL, NIL, nullptr, BLACK );
        }else{
            insert( root, x );
        }
    }
    // ɾ���ڵ�
    bool remove( Object data ){
        return delete_child( root, data );
    }
    // Ѱ���� i �غϵ�����
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
    // �ҳ����� x ���� i ���غϵ���������
    std::vector< Object > searchlist( Object i )  {
        return searchlist( root, i );      
    }


};

