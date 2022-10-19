#include <iostream>
#include <vector>
#include <unordered_map>
#include "DLL.h"
using namespace std;

DLL list;
vector <int> v;

bool compare(vector <int> &vec,  DLL &l){
    
    bool same = true;
    l.reset();
    
    for (int i: vec)
        if (i != l.getNext())
            same = false;
        
    return same;
}

// due to the optimization, this function has to be called first
bool test_prepend_append(vector <int> values){
    
    for (int i=0; i<values.size(); i++){
        list.prepend(values[i]);
        list.append(values[i]);
    }
    
    // we split this up so we shouldn't have to insert at the beginning of the vector
    
    for (int i=values.size()-1; i>=0; i--)
        v.push_back(values[i]);
    
    for (int i=0; i<values.size(); i++)
        v.push_back(values[i]);
        DLL copy;
    
    return compare(v, list);
}

bool test_append(vector <int> values){
    
    for (int i=0; i<values.size(); i++){
        list.append(values[i]);
        v.push_back(values[i]);
    }
    
    return compare(v, list);
}

bool test_prepend(vector <int> values){
    
    for (int i=0; i<values.size(); i++){
        list.prepend(values[i]);
        v.insert(v.begin(), values[i]);
    }
    
    return compare(v, list);
}

bool test_assignment_operator(){
    
    int i;
    bool same=true;
    
    // this way it invokes operator=
    DLL copy;
    copy = list;
    
    list.reset();
    copy.reset();
    
    while(i = list.getNext())
        if (i != copy.getNext()) same = false;
    
    // because then copy has more elements
    if (copy.getNext()) same = false;
    
    return same;
}

// test this after assignment
bool test_merge(vector <int> values){
    
    DLL otherList, listCopy;
    vector <int> newvec = v;
    
    listCopy = list;
    
    // make another list
    for (int i=0; i<values.size(); i++){
        otherList.append(values[i]);
        newvec.push_back(values[i]);
    }
    
    listCopy.merge(otherList);
    
    otherList.reset();
    if (otherList.getNext()) return false;
    
    // test self-merge
    listCopy.merge(listCopy);
    
    // if it's still the same as the vector, all good
    return compare(newvec, listCopy);
}

bool test_operator_plus_equals(vector <int> values){
    
    DLL otherList, listCopy=list;
    vector <int> newvec=v;
    bool same = true;
    
    // make another list
    for (int i=0; i<values.size(); i++){
        otherList.append(values[i]);
        newvec.push_back(values[i]);
    }
    
    
    listCopy += otherList;
    
    
    // check that otherList is intact
    otherList.reset();
    
    for (int i=newvec.size()-values.size(); i<newvec.size(); i++)
        if (newvec[i] != otherList.getNext()) same = false;
    
    if (!same) return false;
    
    if (!compare(newvec, listCopy)) return false;
    
    // check that there is no weird pointer situation
    otherList.append(5);
    
    return compare(newvec, listCopy);
}

// values_to_remove should contain unique values
// there is no reason to do duplicates
bool test_operator_minus_equals(vector <int> list_values, vector <int> values_to_remove){
    
    int all_elements = list_values.size();
    int to_remove = values_to_remove.size();
    
    DLL list, otherList;
    vector <int> vec;
    unordered_map <int, int> hashmap;
    
    // add the values to remove to the hashmap
    for (int i=0; i<to_remove; i++)
        hashmap[values_to_remove[i]] = values_to_remove[i];
    
    for (int i=0; i<all_elements; i++){
        
        // if it's not in the hashmap, add to the vector
        // otherwise, add it to the other list
        if (hashmap.find(list_values[i]) == hashmap.end())
            vec.push_back(list_values[i]);
        else
            otherList.append(list_values[i]);
        
        // either way, add to the list
        list.append(list_values[i]);
    }
    
    list-=otherList;
    
    // at this point list should equal vec
    if (!compare(vec, list)) return false;
    
    // and the size of the hashmap should be the size of otherList
    int list_size=0;
    otherList.reset();
    while(otherList.getNext())
        list_size++;
    
    return to_remove == list_size;
}

bool test_getMax(){
    
    // this vector has no negative values, so this is ok
    int max=0;
    
    for (int i: v)
        if (i>max) max = i;
        
    return max == list.getMax();
}

bool test_extractMax(){
    
    int max_index=0, list_max;
    
    for (int i=0; i<v.size(); i++)
        if (v[i] > v[max_index]) max_index = i;
    
    list_max = list.extractMax();
    
    if (list_max != v[max_index]) return false;
    
    // erase the max from the vector
    v.erase(v.begin()+max_index);
    
    return compare(v, list);
}

bool test_extractOdds(){
    
    bool correct = true;
    int val;
    
    DLL odds = list.extractOdds();
    
    // all the values in odds should be odd
    odds.reset();
    while (val = odds.getNext())
        if (val %2 == 0) correct = false;
    
    // all values in the list should be even
    list.reset();
    while (val = list.getNext())
        if (val %2 == 1) correct = false;
    
    return correct;
}

bool test_extractEvens(){
    
    bool correct = true;
    int val;
    
    DLL evens = list.extractEvens();
    
    // all the values in evens should be even
    evens.reset();
    while (val = evens.getNext())
        if (val %2 == 1) correct = false;
    
    // all values in the list should be odd
    list.reset();
    while (val = list.getNext())
        if (val %2 == 0) correct = false;
    
    return correct;
}


int main(){
    
    // the numbers are all from $RANDOM
    // I used a for loop in bash to get them all
    
    cout << "\nPrepend/append test:\t";
    if (test_prepend_append({28170, 22244, 10055, 28510, 14157, 8993, 19835, 23513, 25011, 22874, 21410, 814, 15570, 26076, 29625}))
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << "\nAppend test:\t";
    if (test_append({27463, 13097, 18921, 1399, 32202, 706, 22108, 6454}))
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << "\nPrepend test:\t";
    if (test_prepend({11793, 8920, 11499, 7243, 6824, 20568, 31454, 7856}))
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << "\nAssignment operator test:\t";
    if (test_assignment_operator())
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << "\nMerge test:\t";
    if (test_merge({31723, 4975, 3522, 21205, 19842, 20621, 27836, 9795}))
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << "\nOperator+= test:\t";
    if (test_operator_plus_equals({19089, 15267, 4818, 28409, 18906, 27530, 31274, 10630}))
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << "\nOperator-= test:\t";
    if (test_operator_minus_equals({29354, 8400, 26395, 15712, 7210, 28, 19046, 26920, 4149, 23409, 9604, 30295, 19696, 26798, 31185, 24765, 17342, 29629, 2915, 5726, 3431, 21024, 13322, 6379, 2879, 10605, 15686, 7737, 21337, 23878}, {8400, 7210, 17342, 3431, 23878}))
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << "\ngetMax test:\t";
    if (test_getMax())
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << "\nextractMax test:\t";
    if (test_extractMax())
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    
    // add some more to the list here
    test_prepend_append({23068, 18454, 26228, 3351, 4893, 8235, 3455, 14813, 28285, 15786, 12020, 27481, 30852, 29499, 31309, 16970, 13371, 11543, 26961, 13550, 9074, 6955, 29761, 27436, 21033, 9042, 13198, 2101, 2357, 3633});
    
    cout << "\nExtract odds test:\t";
    if (test_extractOdds())
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    
    // add some more to the list here
    test_prepend_append({17201, 8170, 22689, 13331, 12562, 31873, 32630, 17054, 30924, 3571, 7118, 23667, 11504, 20477, 17494, 12142, 20307, 17970, 21893, 21397, 15356, 32065, 32318, 25632, 30831, 1187, 12865, 26891, 17807, 22797});
    
    
    cout << "\nExtract evens test:\t";
    if (test_extractEvens())
        cout << "Pass\n";
    else
        cout << "Fail\n";
    
    cout << endl;
}
