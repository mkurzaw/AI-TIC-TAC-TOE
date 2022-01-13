#pragma once
#include <iostream>
#include <vector>
//punktacja
#define LOST -10
#define TIE 0
#define WIN 10


using namespace std;

class Node
{
    vector<Node> children;
    vector<vector<char>> state;
    unsigned int level;
    int value;
    char current_player;

public:
    static void getAdresses(vector<Node*>& v, Node* root);
    static char computer;
    static unsigned int depth;
    static unsigned int max_depth;
    Node(vector<vector<char>> state, unsigned int level, char current_player);
    unsigned int getLevel() const;
    void calculateValue(int& alphaBeta, bool first);
    int getValue() const;
    vector<vector<char>> getState() const;
    vector<Node> getChildren() const;
};
