//This is the implementation file tree.cpp. This is the implementation for
//the template class SearchTree. The interface is in the file tree.h.
namespace TreeSavitch
{
    template<class T>
    void SearchTree<T>::insert(T item, TreeNode<T>*& subTreeRoot)
    {
        if (subTreeRoot == NULL)
            subTreeRoot = new TreeNode<T>(item, NULL, NULL);
        else if (item < subTreeRoot->data)
            insert(item, subTreeRoot->leftLink);
        else //item >= subTreeRoot->data
            insert(item, subTreeRoot->rightLink);
    }

    template<class T>
    void SearchTree<T>::insert(T item)
    {
        insert(item, root);
    }

    template<class T>
    bool SearchTree<T>::inTree(T item, TreeNode<T>* subTreeRoot) const
    {
        if (subTreeRoot == NULL)
            return false;
        else if (subTreeRoot->data == item)
            return true;
        else if (item < subTreeRoot->data)
            return inTree(item, subTreeRoot->leftLink);
        else //item >= link->data
            return inTree(item, subTreeRoot->rightLink);
    }

    template<class T>
    bool SearchTree<T>::inTree(T item) const
    {
        return inTree(item, root);
    }

    template<class T> //uses iostream:
    void SearchTree<T>::inOrderShow(TreeNode<T>* subTreeRoot) const
    {
        if (subTreeRoot != NULL)
        {
            inOrderShow(subTreeRoot->leftLink);
            cout << subTreeRoot->data << " ";
            inOrderShow(subTreeRoot->rightLink);
        }
    }

    template<class T> //uses iostream:
    void SearchTree<T>::inOrderShow( ) const
    {
        inOrderShow(root);
    }

    template<class T>
    void SearchTree<T>::deleteSubtree(TreeNode<T>*& subTreeRoot)
    {
        if (subTreeRoot != NULL)
        {
            deleteSubtree(subTreeRoot->leftLink);

            deleteSubtree(subTreeRoot->rightLink);

            //subTreeRoot now points to a one node tree.
            delete subTreeRoot;
            subTreeRoot = NULL;
        }
    }

    template<class T>
    SearchTree<T>::~SearchTree( )
    {
        deleteSubtree(root);
    }
}//TreeSavitch
