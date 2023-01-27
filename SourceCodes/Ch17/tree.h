//Header file tree.h. The only way to insert data in a tree is with the insert function.
//So, the tree satisfies the Binary Search Tree Storage Rule. The functions inTree 
//depends on this. < must be defined and give a well behaved ordering to the type T.
#ifndef TREE_H
#define TREE_H
namespace TreeSavitch
{
    template<class T>
    class SearchTree; //forward declaration

    template<class T>
    class TreeNode
    {
    public:
        TreeNode( ) : root(NULL){}
        TreeNode(T theData, TreeNode<T>* left, TreeNode<T>* right) 
            : data(theData), leftLink(left), rightLink(right){}
        friend class SearchTree<T>;
    private:
        T data;
        TreeNode<T> *leftLink;
        TreeNode<T> *rightLink;
    };

    
    template<class T>
    class SearchTree
    {
    public:
        SearchTree( ) : root(NULL){}
        virtual ~SearchTree( );
        void insert(T item); //Adds item has been added to the tree.
        bool inTree(T item) const; 
        void inOrderShow( ) const;
    private:
        void insert(T item, TreeNode<T>*& subTreeRoot);
        bool inTree(T item, TreeNode<T>* subTreeRoot) const;
        void deleteSubtree(TreeNode<T>*& subTreeRoot);
        void inOrderShow(TreeNode<T>* subTreeRoot) const;
        TreeNode<T> *root;
    };

} //TreeSavitch

#endif