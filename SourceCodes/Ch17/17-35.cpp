#include<cstddef>

    class IntTreeNode
    {
    public:
        IntTreeNode(int theData, IntTreeNode* left, IntTreeNode* right) 
            : data(theData), leftLink(left), rightLink(right){}
    private:
        int data;
        IntTreeNode *leftLink;
        IntTreeNode *rightLink;
    };


    IntTreeNode *root;