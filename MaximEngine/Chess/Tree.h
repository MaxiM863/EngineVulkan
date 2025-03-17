#include "TreeNode.h"

#define MAX_NODES 1000000

class Tree {

    public:

        Tree(int boardSize) { top = new TreeNode(nullptr, std::vector<TreeNode*>(), Position(-1, -1)); this->boardSize = boardSize; }

        TreeNode* getTopTree() { return top; }

        void addLevel(std::vector<Position> botPlayed, std::vector<Position> plyPlayed)
        {

            recursiveAddNode(top, botPlayed, plyPlayed, 0);
        }

        int getTreeDepth() 
        { 
            
            int count = 0;

            recursiveLeaf(top, count);
            
            return count;
        }

    private:

        void recursiveLeaf(TreeNode* actual, int& count)
        {       
            
            if(actual->childs.size() > 0)
            {

                count++;
                recursiveLeaf(actual->childs.at(0), count);                
            }
        }

        void recursiveAddNode(TreeNode* actual, std::vector<Position> botPlayed, std::vector<Position> plyPlayed, int level)
        {

            if(actual->childs.size() == 0)
            {

                TreeNode* tmpActual = actual;

                while(tmpActual->parent != nullptr)
                {
                    if(level % 2 == 0)
                    {
                        plyPlayed.push_back(tmpActual->positionBoard);
                    }
                    else
                    {
                        botPlayed.push_back(tmpActual->positionBoard);
                    }

                    tmpActual = tmpActual->parent;
                }

                for(int i = 0; i < boardSize; i++)
                {
                    for(int j = 0; j < boardSize; j++)
                    {
                        bool testExist = false;

                        for(int k = 0; k < botPlayed.size(); k++)
                        {
                            if(botPlayed.at(k).xPos == i && botPlayed.at(k).yPos == j)
                            {
                                testExist = true;
                                break;
                            }
                        }

                        if(!testExist)
                        {
                            for(int k = 0; k < plyPlayed.size(); k++)
                            {
                                if(plyPlayed.at(k).xPos == i && plyPlayed.at(k).yPos == j)
                                {
                                    testExist = true;
                                    break;
                                }
                            }
                        }

                        if(!testExist)
                        {
                        
                            actual->childs.push_back(new TreeNode(actual, std::vector<TreeNode*>(), Position(i, j)));
                        }
                    }
                }
            }
            else
            {
                for(int i = 0; i < actual->childs.size(); i++)
                {
                    recursiveAddNode(actual->childs.at(i), botPlayed, plyPlayed, level + 1);
                }
            }
        }

    private:

        TreeNode* top;
        int boardSize;
};