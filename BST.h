#ifndef BST_H
#define BST_H

#include <iostream>

#include <memory>
#include <queue>
#include <vector>

struct Node
{
    size_t number;
    size_t index;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;
    Node(const size_t& n, const size_t& i) : number(n), index(i) { }
};

class BST
{
    private:
        std::shared_ptr<Node> root;
        std::shared_ptr<Node> smallest;
        std::shared_ptr<Node> biggest;

    public:
        BST(std::vector<std::queue<size_t>>& indexes);
        BST() {}
        ~BST() {}
        std::shared_ptr<Node> addNumber(const size_t& num, const size_t& index);
        size_t removeSmallest();
        size_t getBiggest();
        size_t getSmallest();
        void printTree();
};

#endif // BST_H
