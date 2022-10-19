#include "DLLNode.h"
using namespace std;

class DLL {
    private:
        DLLNode *head, *tail, *pointer;
    public:
        DLL();
        ~DLL();
        DLL &operator+=(const DLL &other);
        DLL &operator-=(const DLL &other);
        int getMax();
        int extractMax();
        DLL extractOdds();
        DLL extractEvens();
        void deleteAllNodes();
        bool prepend(int data);
        bool append(int data);
        bool merge(DLL &other);
        void show();
        bool reset();
        int getNext();
};