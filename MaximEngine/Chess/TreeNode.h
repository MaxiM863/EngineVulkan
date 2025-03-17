#ifndef TREENODE
#define TREENODE

#include<vector>

#include "ChessCase.h"

struct TreeNode
{
    TreeNode(){}
    TreeNode(TreeNode* _parent, int nbrChilds, ChessCase* caseD)
    {
        parent = _parent;
        childs = new TreeNode*[nbrChilds];
        caseData = caseD;
        valeurChild = 0;
    }

    TreeNode* parent;
    TreeNode** childs;

    ChessCase* caseData;

    int valeurChild;
};

#endif