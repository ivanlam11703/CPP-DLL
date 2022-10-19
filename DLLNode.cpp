#include "DLLNode.h"
using namespace std;

    DLLNode::DLLNode() {
        data = -99;
        next = nullptr; 
        prev = nullptr;
    }

    DLLNode::DLLNode(int new_data) {
        data = new_data; 
        next = nullptr; 
        prev = nullptr;
    }