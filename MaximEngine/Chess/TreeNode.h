#ifndef TREENODE
#define TREENODE

#include<vector>

struct TreeNode
{
    TreeNode(){}
    TreeNode(TreeNode* _parent, int nbrChilds)
    {
        parent = _parent;
        childs = new TreeNode*[nbrChilds];
        
        valeurChild = 0;
    }

    TreeNode* parent;
    TreeNode** childs;


    int valeurChild;
};

#endif