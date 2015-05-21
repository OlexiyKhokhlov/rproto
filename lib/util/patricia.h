#pragma once

#include "bitutil.h"

#include <functional>
#include <memory>
#include <iterator>
#include <stddef.h>


template < class T, class Alloc = std::allocator<T> >
class patricia_tree
{
public:
    template <class Tp>
    struct Node
    {
        enum Flags{
            ZERO     = 0,
            LEFT_UP  = 1,
            RIGHT_UP = 2
        };

        Node(const Tp& nkey)
        {
            left   = nullptr;
            right  = nullptr;
            position = 0;
            attr   = ZERO;
            key = nkey;
        }

        Node *left;
        Node *right;
        size_t position;
        Flags  attr;
        Tp key;
    };

    patricia_tree()
    { root = nullptr; }

    bool isContain(const T& key)const
    {
       auto node = lookUp(root, key);
       return node != nullptr && node->key == key;
    }

    void insert(const T& key)
    {
        auto node = lookUp(root, key);

        //If the key is already present
        if( node != nullptr
                && node->key == key) return;

        auto newNode = node_allocator.allocate(1, 0);
        node_allocator.construct(newNode, key);

        //Define bit-position in the new node
        if(node != nullptr){
            newNode->position = util::mismatch_bit(node->key, key);
            if(newNode->position == -1){
                //keys are prefix for each to other
                if(key.size() > node->key.size())
                    newNode->position = (util::bit_count(key) - util::bit_count(node->key))/2;
                else
                    newNode->position = util::bit_count(key)/2;
            }
        }else{
            //New node hasn't prefix in the trie
            newNode->position = util::bit_count(key)/2;
        }

    }

private:
    typedef typename Alloc::template rebind< Node<T> >::other Node_alloc_type;
    Node_alloc_type node_allocator;
    Node<T>    *root;

    Node<T>* lookUp(Node<T>* start_node, const T& key
                          ,std::function<bool(Node<T>*)> visitor=[](Node<T>*)
    { return false; })const
    {
        auto node = start_node;
        if(node == nullptr) return node;

        auto key_len = util::bit_count(key);
        if(key_len-1 < node->position) return node;

        do{
            if(visitor(node)) break;

            bool finish = false;
            if( util::checkbit(key, node->position) ){
                if( node->right != nullptr && key_len < node->right->position )
                    break;
                finish = node->attr | Node<T>::RIGHT_UP ? true : false ;
                node = node->right;
            }else{
                if( node->left != nullptr && key_len < node->left->position )
                    break;
                finish  = node->attr | Node<T>::LEFT_UP ? true : false ;
                node = node->left;
            }

            if(finish)break;

        }while(true);

        return node;
    }
};
