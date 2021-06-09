#include "utilities.hpp"

using namespace std;

template <typename T>
bool contains(std::vector<T> list, T to_be_found){
   for (int i = 0 ; i < list.size() ; i++){
       if (list[i] == to_be_found) return true;
   }
   return false;
}