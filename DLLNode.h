using namespace std;

class DLLNode 
{
    public:
        int data;
        DLLNode *next;
        DLLNode *prev;
        DLLNode();
        DLLNode(int new_data);
};