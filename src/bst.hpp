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
    node_count++;
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
    //3 general cases....node to remove has 0, 1, or 2 children


    Node<T> *curNode = root;
    Node<T> *parentNode = NULL;

    while(curNode!= NULL)
    {
        if (val == curNode->get_data())
        {

            //2. if(node to remove has one node), set parent to deleting node's child to skip over the node to remove (set pointer to other node), delete  node
            //3. if(node has 2 children...), find the largest item in the left subtree OR find the smallest item in the right subtree
            //      then put that node in place of the one you want to remove
            //if removal successful, node_count--;
            if ((curNode->get_left()==NULL)&&(curNode->get_right()==NULL))
            {
                if (parentNode == NULL)
                {
                    root = NULL;
                }
                else if (parentNode->get_left() == curNode)
                {
                    parentNode->set_left(NULL);
                }
                else
                {
                    parentNode->set_right(NULL);
                }
                delete(curNode);
                node_count--;
            }
            else if ((curNode->get_left()==NULL)&&(curNode->get_right() != NULL))//Remove node with only RIGHT child
            {
                if(parentNode==NULL)
                {
                    root = curNode->get_right();
                }
                else if (parentNode->get_left()== curNode)
                {
                    parentNode->set_left(curNode->get_right());
                }
                else
                {
                    parentNode->set_right(curNode->get_right());
                }
                delete(curNode);
                node_count--;
            }
            else if ((curNode->get_left()!=NULL) && (curNode->get_right() == NULL))//Remove node with only LEFT child
            {
                if(parentNode==NULL)
                {
                    root = curNode->get_left();
                }
                else if (parentNode->get_left()== curNode)
                {
                    parentNode->set_left(curNode->get_left());
                }
                else
                {
                    parentNode->set_right(curNode->get_left());
                }
                delete(curNode);
                node_count--;
            }
            else // the node has 2 children
            {
                Node<T> *successorNode = curNode->get_right();
                T succData;
                while (successorNode->get_left()!= NULL)
                {
                    successorNode=successorNode->get_left();
                }
                succData = successorNode->get_data();
                remove(succData);
                curNode->set_data(succData);
            }
        }
        else if(curNode->get_data()>val) // search left for value to remove
        {
            parentNode = curNode;
            curNode = curNode->get_left();
        }
        else // (curNode->get_data()<val)  search right for value to remove
        {
            parentNode = curNode;
            curNode = curNode->get_right();
        }
    }
    return;

    
}



template<class T>
int BST<T>::get_size()
{
    return node_count;

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
        if (val < node->get_data())
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