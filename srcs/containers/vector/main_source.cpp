#include "VectorSource.hpp"
//On aurait pu faire un fichier tpp
//Garder ce main pour montrer aux correcteurs

//A changer pour faire d autres tests
typedef int value_type_t;

//Faire une fonction affichage  du container

int main(void)
{
  //Instanciation via le constructor 0
  std::allocator<value_type_t> intAlloc;
  ft::vector<value_type_t> vector0(intAlloc);

  //vector0.display_vector();
  //Instanciation avec le constructeur 1
  value_type_t n = 10;
  ft::vector<value_type_t> vector1(n);
  //vector1.display_vector();

  ft::vector<int> vector2(n, 10, intAlloc);
  //vector2.display_vector();
  std::cout << vector0 << std::endl;
  return (0);
}
