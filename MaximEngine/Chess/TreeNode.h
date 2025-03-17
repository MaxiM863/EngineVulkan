#ifndef TREENODE
#define TREENODE

#include<vector>

struct Position
{
    Position(){}
    Position(int x, int y) { xPos = x; yPos = y; }

    int xPos;
    int yPos;
};

struct TreeNode
{
    TreeNode(){}
    TreeNode(TreeNode* _parent, std::vector<TreeNode*> _childs, Position position)
    {
        parent = _parent;
        childs = _childs;
        positionBoard = position;
        valeurChild = 0;
    }

    TreeNode* parent;
    std::vector<TreeNode*> childs;

    Position positionBoard;

    int valeurChild;
};

#endif