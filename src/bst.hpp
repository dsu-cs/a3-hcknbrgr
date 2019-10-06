#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
    // helper function for insert 
    Node<T> *insertHelper(T, Node<T>*);
    std::vector<T> *inOrderHelper(std::vector<T>*, Node<T>*);
    std::vector<T> *preOrderHelper(std::vector<T>*, Node<T>*);
    std::vector<T> *postOrderHelper(std::vector<T>*, Node<T>*);

    
        
};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;
    vec = inOrderHelper(vec, root);

    return vec;
}


template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    vec = preOrderHelper(vec, root);
    return vec;
}


template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    vec = postOrderHelper(vec, root);
    return vec;
}

template<class T>
void BST<T>::insert(T new_data)
{
    root = insertHelper(new_data, root);
}



template<class T>
Node<T> *BST<T>::search(T val)
{
    Node<T> *curNode = root;

    while(curNode!= NULL)
    {
        if (val == curNode->get_data())
        {
            return curNode;
        }
        else if(curNode->get_data()>val)
        {
            curNode = curNode->get_left();
        }
        else if(curNode->get_data()<val)
        {
            curNode = curNode->get_right();
        }
    }
    return NULL;
}



template<class T>
void BST<T>::remove(T val)
{

}



template<class T>
int BST<T>::get_size()
{

}

template<class T>
Node<T> *BST<T>::insertHelper(T val, Node<T> *node)
{

    if(node==NULL)
    {
        Node<T>* tmp = new Node<T>;
        tmp->set_data(val);
        tmp->set_left(NULL);
        tmp->set_right(NULL);
        return tmp;
    }
    else
    {
        if (val <= node->get_data())
        {
            node->set_left(insertHelper(val, node->get_left()));        
        }
        else
        {
            node->set_right(insertHelper(val, node->get_right()));
        }   
    }
    return node;

}

template<class T>
 std::vector<T> *BST<T>::inOrderHelper(std::vector<T> *vec, Node<T> *curNode)
{
    
    //if (node is NULL) return; inorder(node->left); print node; inorder(node->right);
    if (curNode == NULL)
    {
        return vec;
    }
    inOrderHelper(vec, curNode->get_left());
    vec->push_back(curNode->get_data());
    inOrderHelper(vec, curNode->get_right());   
    return vec;
}

template<class T>
 std::vector<T> *BST<T>::preOrderHelper(std::vector<T> *vec, Node<T> *curNode)
{
    
    //if (node is NULL) return; print node; preorder(node->left);  preorder(node->right);
    if (curNode == NULL)
    {
        return vec;
    }
    vec->push_back(curNode->get_data());
    preOrderHelper(vec, curNode->get_left());
    preOrderHelper(vec, curNode->get_right());   
    return vec;
}
template<class T>
 std::vector<T> *BST<T>::postOrderHelper(std::vector<T> *vec, Node<T> *curNode)
{
    
    //if (node is NULL) return; postorder(node->left);  poastorder(node->right);  print node;
    if (curNode == NULL)
    {
        return vec;
    }
    postOrderHelper(vec, curNode->get_left());
    postOrderHelper(vec, curNode->get_right());
    vec->push_back(curNode->get_data());   
    return vec;
}