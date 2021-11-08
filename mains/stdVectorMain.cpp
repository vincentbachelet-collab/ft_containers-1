#include <iostream>
#include <vector>
#include <iterator>

int main(void)
{
  //on ne peut pas utiliser using pour faire des alias dans la norme 98
  typedef std::vector<int> vecInt;
  typedef vecInt::iterator vecIntIt;
  /*
  ** ASSIGN
  ** Assigns new contents to the vector, replacing its currebt contents,
  ** and modifying its size accordingly
  */

  vecInt first;
  vecInt second;
  //cpp reference
  first.assign(7, 100); //7 ints with a value of 100
  vecIntIt it = first.begin() + 1;
  second.assign(it, first.end() -1);//celui ci au une taille de 5 et pas de 7

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
}
