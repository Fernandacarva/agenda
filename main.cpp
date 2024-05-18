#include "agenda.h"

using namespace std;


int main ()
{
  agenda *primeiroNome;  
   
  inicializar(primeiroNome); 
   
  char opcao = 'a';  
    
  while(opcao != 'S') //menu principal
  {  
    system("cls"); //limpa a tela
    
    cout << "Lista de nomes" << endl << endl <<endl;
    cout << "P para percorrer" << endl;
    cout << "B para buscar" << endl;
    cout << "I para inserir" << endl;
    cout << "M para modificar" << endl;
    cout << "R para remover" << endl << endl;
    cout << "S para sair" << endl;
        
    opcao = getchar();
    opcao = toupper(opcao);
      
    switch(opcao)
    {
      case 'P': percorrerNomes(primeiroNome); break;
      
      case 'B': buscarPorNome(primeiroNome); break;
      
      case 'I': inserirNomeMenu(primeiroNome); break;
      
      case 'M': case 'R': modificarRemoverNomeMenu(primeiroNome); break;
      
      default: break;
    }      
  }   
  
  finalizar(primeiroNome);  
  
  return 0;
}