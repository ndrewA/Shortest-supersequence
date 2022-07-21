#include "BST.h"

BST::BST(std::vector<std::queue<size_t>>& indexes)
{

    for(size_t iter = 0; iter < indexes.size(); iter++)
    {
        size_t curIndex = indexes[iter].front();

        addNumber(curIndex, iter);
    }
}

std::shared_ptr<Node> BST::addNumber(const size_t& num, const size_t& index)
{
    if(root == nullptr)
    {
        root = std::make_shared<Node>(num, index);

        if(smallest == nullptr || smallest->number > num)
            smallest = root;

        if(biggest == nullptr || biggest->number < num)
            biggest = root;

        return root;
    }

    std::shared_ptr<Node> curNode = root;

    while(true)
    {
        if(num > curNode->number){

            if(curNode->right == nullptr)
            {
                curNode->right = std::make_shared<Node>(num, index);
                curNode->right->parent = curNode;

                if(smallest == nullptr || smallest->number > num)
                    smallest = curNode->right;

                if(biggest == nullptr || biggest->number < num)
                    biggest = curNode->right;

                return curNode->right;
            }
            curNode = curNode->right;

        } else {

            if(curNode->left == nullptr)
            {
                curNode->left = std::make_shared<Node>(num, index);
                curNode->left->parent = curNode;

                if(smallest == nullptr || smallest->number > num)
                    smallest = curNode->left;

                if(biggest == nullptr || biggest->number < num)
                    biggest = curNode->left;

                return curNode->left;
            }
            curNode = curNode->left;
        }
    }
    return root;
}

size_t BST::removeSmallest()
{
    if(root == nullptr) return 0;

    size_t i = 0;
    if(smallest != nullptr) i = smallest->index;

    if(smallest->right) {

        if(smallest == root)
            root = root->right;

        std::shared_ptr<Node> iterNode = smallest->right;

        while(iterNode->left)
            iterNode = iterNode->left;

        auto node = smallest;

        if(smallest->parent) smallest->parent->left = smallest->right;

        smallest->right->parent = smallest->parent;

        smallest = iterNode;

        node.reset();

        if(root) root->parent.reset();

    } else {

        if(smallest == root) root = smallest->parent;
        smallest = smallest->parent;
        if(smallest) smallest->left.reset();
    }

    return i;
}

size_t BST::getSmallest()
{
    if(smallest)
        return smallest->number;
    else return -1;
}

size_t BST::getBiggest()
{
    if(biggest)
        return biggest->number;
    else return -1;
}

void BST::printTree()
{
    if(root == nullptr) return;
    std::queue<std::shared_ptr<Node>> q;
    q.push(root);
    while(!q.empty())
    {
        std::cout << q.front()->number << '\n';
        if(q.front()->right) q.push(q.front()->right);
        if(q.front()->left) q.push(q.front()->left);
        q.pop();
    }
    std::cout << "===================\n";
}
