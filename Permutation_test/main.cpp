#include <iostream>
#include <vector>

using namespace std;

//template<class T>
//void Combination(vector<T>& collection, int positions, void (* fun)(vector<T>))
//{
//       
//    vector<T> tab(positions);
//    for (int i = 0; i != positions; i++)
//        tab[i] = collection[i];
//    
//    int i = collection.size() - positions;
//    int x= positions - 2;
//    T* ptr = &collection[positions-2];
//
//    do
//    {
//        while (i != collection.size()+1)
//        {
//            tab[tab.size() - 1] = collection[i - 1];
//            fun(tab);
//            i++;
//        };
//        ptr--;
//        tab[tab.size() - 1];
//
//    } while (true);
//    
//
//}
static int idx = 0;
template<class T>
void print(vector<T> a)
{
   
    idx++;
    for (auto& x : a)
    {
        cout << x;
    }
    cout << endl;

}


template<class T>
void Combination(vector<T>& collection, unsigned int offset, unsigned int k, void (*fun)(vector<T>)) {
   
    static vector<T> combination{};

    if (k == 0) {
        fun(combination);
        return;
    }

    for (unsigned int i = offset; i <= collection.size() - k; ++i) {
        combination.push_back(collection[i]);
        Combination(collection, i + 1, k - 1, fun);
        combination.pop_back();
    }
}

int main()
{
    vector<int> test;
    vector<char> test2{ 'a', 'b','c','d','e', 'f', 'g'};
    for (int i = 0; i != 47; i++)
        test.push_back(i);

    Combination(test,0, 2, &print);

    cout << endl << idx; 
}