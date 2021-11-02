#include "VectorSource.hpp"
//On aurait pu faire un fichier tpp
//Garder ce main pour montrer aux correcteurs

//A changer pour faire d autres tests
typedef int value_type_t;

int main(void)
{
  //Instanciation via le constructor 0
  std::allocator<value_type_t> intAlloc;
  ft::vector<value_type_t> vector0(intAlloc);

  //Instanciation avec le constructeur 1
  value_type_t n = 10;
  ft::vector<value_type_t> vector1(n);

  ft::vector<int> vector2(n, )
  return (0);
}
