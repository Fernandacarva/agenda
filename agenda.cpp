#include "agenda.h"

#define VAL_CHARS "abcdefghijklmnopqrstuvxywzABCDEFGHIJKLMNOPQRSTUVXYWZ0123456789.!?:;,-=*&@%/'\'()[]{}+ "

using namespace std;


bool nomeValido(const char *nome, const char *valChars) //valida o nome
{
  unsigned k = 0;
  
  if (strlen(nome) == 0)
    return false;
    
  for (unsigned i = 0; i < strlen(nome); i++) //analisa a validade de cada caracter
  {  
    for (unsigned j = 0; j < strlen(valChars); j++)
    {  
      if (nome[i] == valChars[j])
        k++;
    }
  }

  if (k!= strlen(nome)) //se algum caracter nao for valido, o nome nao e valido
    return false;

  return true;
}

void removerNome(agenda *&nome, agenda *&primeiroNome) //remove a estrutura da lista
{
  if((nome == primeiroNome) && (nome->proximo == primeiroNome))
    primeiroNome = NULL;
  else
  {
    nome->anterior->proximo = nome->proximo;
    nome->proximo->anterior = nome->anterior;
    
    if(nome == primeiroNome)
        primeiroNome = nome->proximo;           
  }          
                             
  free(nome);       
}

void removerNomeMenu(agenda *&nome, agenda *&primeiroNome) //apresenta a confirmacao de remocao
{
  char opcao = 'a';
  
  system("clear"); //limpa a tela
    
  cout << "Remover nome" << endl << endl;
   
  cout.width(TAMANHO_NOME);   cout << left << "Nome";
  cout.width(TAMANHO_NOME);   cout << left << "E-mail";
  cout.width(TAMANHO_NUMERO); cout << left << "Telefone";
  cout.width(TAMANHO_NUMERO); cout << left << "Endereço" << endl << endl;
 
  cout.width(TAMANHO_NOME);   cout << left << nome->nome;
  cout.width(TAMANHO_NOME);   cout << left << nome->email;
  cout.width(TAMANHO_NUMERO); cout << left << nome->telefone;
  cout.width(TAMANHO_NUMERO); cout << left << nome->endereco << endl << endl << endl;

  cout << "Confirmar? (S/N)" << endl;
  
  while((opcao != 'S') && (opcao != 'N'))
  {  
    opcao = getchar();
    opcao = toupper(opcao);
        
    switch(opcao)
    {
      case 'S':
        cout << endl << "Removendo..." << endl;
        
        removerNome(nome, primeiroNome);   
        
        system("clear"); //limpa a tela
    
        cout << "Remoção concluida" << endl << endl << endl;
        cout << "Pressione qualquer tecla para continuar" << endl;
  
        getchar(); 
      break;

      case 'N':
        system("clear"); //limpa a tela
    
        cout << "Remoção cancelada" << endl << endl << endl;
        cout << "Pressione qualquer tecla para continuar" << endl;
  
        getchar();   
      break;
      
      default:
      break;
    }
  }
}


void inserirNome(agenda *&novo, agenda *&primeiroNome) //ordena a nova estrutura de acordo com o titulo
{
  if(primeiroNome == NULL) //lista vazia
  {
    primeiroNome = novo;
    primeiroNome->proximo = novo;
    primeiroNome->anterior = novo;
  }
  else  
  {
    agenda *atual = primeiroNome;
    
    while ((strcmp(atual->nome, novo->nome) <= 0) && (atual->proximo != primeiroNome)) //procura a posicao certa
    {  
        atual = atual->proximo;
    }
     
    if (strcmp(atual->nome, novo->nome) > 0)  
    {                                                     
      novo->anterior = atual->anterior;
      novo->proximo = atual;
      atual->anterior->proximo = novo;
      atual->anterior = novo;
      
      if(atual == primeiroNome) //novo e menor que o primeiro
        primeiroNome = novo;      
    }   
    else //novo e maior que o ultimo
    {
      novo->anterior = atual;
      novo->proximo = primeiroNome;
      atual->proximo = novo;
      primeiroNome->anterior = novo;
    }
  }
}

void inserirNomeMenu(agenda *&primeiroNome) //apresenta menu e lê os dados para uma nova estrutura
{
  char buffer[TAMANHO_NUMERO];
  agenda *novo = new agenda;
    
  system("clear");  //limpa a tela
  
  cout << "Inserir nome" << endl << endl;
  
  cout << "Nome:" << endl;
  cin.getline(novo->nome,TAMANHO_NOME);
  
  while(!nomeValido(novo->nome,  VAL_CHARS)) //validar novo nome
  {
    cout << endl << "Nome Invalido - Digite outro por favor" << endl;
    cin.getline(novo->nome,TAMANHO_NOME);
  }  
  
  cout << endl << "E-mail:" << endl;
  cin.getline(novo->email, TAMANHO_NOME);
  while(!nomeValido(novo->email, VAL_CHARS)) //validar novo nome
  {
    cout << endl << "Nome invalido - Digite outro por favor" << endl;
    cin.getline(novo->email, TAMANHO_NOME);
  }  
  
  cout << endl << "Telefone:" << endl;
  cin.getline(buffer, TAMANHO_NUMERO);
  novo->telefone = atoi(buffer);
  
  cout << endl << "Endereço:" << endl;
  cin.getline(buffer, TAMANHO_NUMERO);
  novo->endereco = atoi(buffer);
  
  cout << endl << endl << "Inserindo... " << endl;
  
  inserirNome(novo, primeiroNome);  
}


void modificarNome(agenda *&nome, agenda *&primeiroNome)
{
  char buffer[TAMANHO_NOME];     
  agenda *novo = new agenda;
     
  system("clear"); //limpa a tela 
  
  cout << "Modificar nome" << endl << endl;
  
  cout << "Caso não queira modificar um campo, pressione ENTER" << endl << endl;
  
  cout << "Nome:" << nome->nome << endl;
  cout << "Novo nome:";
  cin.getline(buffer, TAMANHO_NOME);
  
  if(strlen(buffer) != 0) //tamanho 0 representa nao mudar o nome
    strcpy(novo->nome, buffer);
  else
    strcpy(novo->nome, nome->nome);
  
  while(!nomeValido(novo->nome, VAL_CHARS)) //validar novo nome
  {
    cout << endl << "Nome Invalido - Digite outro por favor" << endl;
    cin.getline(buffer, TAMANHO_NOME);
  
    if(strlen(buffer) != 0)
      strcpy(novo->nome, buffer);
    else
      strcpy(novo->nome, nome->nome);
  }  
  
  cout << "Email:" << nome->email << endl;
  cout << "Novo email:";
  cin.getline(buffer, TAMANHO_NOME);
  
  if(strlen(buffer) != 0) //tamanho 0 representa nao mudar o nome
    strcpy(novo->email, buffer);
  else
    strcpy(novo->email, nome->email);
  
  while(!nomeValido(novo->email, VAL_CHARS)) //validar novo nome
  {
    cout << endl << "Email invalido - Digite outro por favor" << endl;
    cin.getline(buffer, TAMANHO_NOME);
  
    if(strlen(buffer) != 0)
      strcpy(novo->email, buffer);
    else
      strcpy(novo->email, nome->email);
  }  
  
  cout << "Telefone:" << nome->telefone << endl;
  cout << "Novo telefone:";
  cin.getline(buffer, TAMANHO_NUMERO);
  
  if(strlen(buffer) != 0) //tamanho 0 representa nao mudar o nome
    novo->telefone = atoi(buffer);
  else
    novo->telefone = nome->telefone;
  
  cout << "Endereço:" << nome->endereco << endl;
  cout << "Novo endereço:";
  cin.getline(buffer, TAMANHO_NUMERO);
  
  if(strlen(buffer) != 0) //tamanho 0 representa nao mudar o nome
    novo->endereco = atoi(buffer);
  else
    novo->endereco = nome->endereco;
    
  cout << endl << endl << "Modifcando..." << endl; 
  
  if(strcmp(nome->nome, novo->nome) == 0) //se for o mesmo nome, nao precisa re-ordenar
  {
    strcpy(nome->email, novo->email);
    nome->telefone = novo->telefone;
    nome->endereco = novo->endereco;
  }
  else //re-ordener consiste em remover o antigo e inserir o novo
  {
    removerNome(nome, primeiroNome);
    inserirNome(novo, primeiroNome);
  }
    
  system("clear"); //limpa a tela
    
  cout << "Modificado com sucesso" << endl << endl << endl;
  cout << "Pressione qualquer tecla para continuar" << endl;

  getchar();
}

void percorrerNomes(agenda *&primeiroNome) //apresenta cada filme, a partir do primeiro
{
  agenda *atual = primeiroNome;
  char opcao = 'a';
  
  if(atual == NULL)
  {
    system("clear"); //limpa a tela
    
    cout << "Lista vazia" << endl << endl <<endl;
    cout << "Pressione qualquer tecla para continuar" << endl;
  
    getchar();
  }
  else
    while(opcao != 'S')
    {
      system("clear"); //limpa a tela
      
      cout << "Contatos:" << endl << endl;
      
      cout.width(TAMANHO_NOME);   cout << left << "Nome";
      cout.width(TAMANHO_NOME);   cout << left << "Email";
      cout.width(TAMANHO_NUMERO); cout << left << "Telefone";
      cout.width(TAMANHO_NUMERO); cout << left << "Endereço" << endl << endl;
 
      cout.width(TAMANHO_NOME);   cout << left << atual->nome;
      cout.width(TAMANHO_NOME);   cout << left << atual->email;
      cout.width(TAMANHO_NUMERO); cout << left << atual->telefone;
      cout.width(TAMANHO_NUMERO); cout << left << atual->endereco << endl << endl << endl;

      cout << "A para avançar" << endl;
      cout << "V para voltar" << endl << endl;
      cout << "R para remover" << endl;
      cout << "M para modificar" << endl << endl;      
      cout << "S para sair" << endl;
      
      opcao = getchar();
      opcao = toupper(opcao);
      
      switch(opcao)
      {
        case 'A':             
          atual = atual->proximo;
        break;
        
        case 'V':             
          atual = atual->anterior;
        break;
      
        case 'R':             
          removerNomeMenu(atual, primeiroNome);
          opcao = 'S';
        break;
        
        case 'M':             
          modificarNome(atual, primeiroNome);
          opcao = 'S';
        break;
        
        default:
        break;
      }
    }
}

void buscarPorNome(agenda *&primeiroNome)
{
  char opcao = 'a';
  char buffer[TAMANHO_NOME];
  agenda *atual = primeiroNome;
  
  system("clear"); //limpa a tela 

  cout << "Busca por nome" << endl << endl << endl;
  cout << "Nome:" << endl;

  cin.getline(buffer, TAMANHO_NOME);

  while((atual->proximo != primeiroNome) && (strcmp(atual->nome, buffer) != 0))
    atual = atual->proximo;

  if(strcmp(atual->nome, buffer) != 0) //nenhum resultado
  {
    system("clear"); //limpa a tela
    
    cout << "Nenhum nome foi encontrado" << buffer << endl << endl << endl;
    cout << "Pressione qualquer tecla para continuar" << endl;
  
    getchar();
  }
  else
  {
    while(opcao != 'S')
    {

      system("clear"); //limpa a tela
      
      cout << "Reultado da busca por nome: "<< buffer << endl << endl;
      
      cout.width(TAMANHO_NOME); cout << left << "Nome";
      cout.width(TAMANHO_NOME); cout << left << "Email";
      cout.width(TAMANHO_NUMERO);  cout << left << "Telefone";
      cout.width(TAMANHO_NUMERO);  cout << left << "Endereço" << endl << endl;
 
      cout.width(TAMANHO_NOME); cout << left << atual->nome;
      cout.width(TAMANHO_NOME); cout << left << atual->email;
      cout.width(TAMANHO_NUMERO);  cout << left << atual->telefone;
      cout.width(TAMANHO_NUMERO);  cout << left << atual->endereco << endl << endl << endl;

      cout << "A para avancar ao proximo resultado" << endl;
      cout << "V para voltar ao resultado anterior" << endl << endl;
      cout << "R para remover" << endl;
      cout << "M para modificar" << endl << endl;      
      cout << "S para sair" << endl;


      opcao = getchar();
      opcao = toupper(opcao);
      
      switch(opcao)
      {
        case 'A':  
          atual = atual->proximo;           
          while(strcmp(atual->nome, buffer) != 0) //procura um novo resultado
            atual = atual->proximo;
        break;
        
        case 'V':
          atual = atual->anterior;
          while(strcmp(atual->nome, buffer) != 0) //procura um novo resultado             
            atual = atual->anterior;
        break;
      
        case 'R':             
          removerNomeMenu(atual, primeiroNome);
          opcao = 'S';
        break;
        
        case 'M':             
          modificarNome(atual, primeiroNome);
          opcao = 'S';
        break;
        
        default:
        break;
      }
    }    
  }
}  

void buscarPorEmail(agenda *&primeiroNome)
{
  char opcao = 'a';
  char buffer[TAMANHO_NOME];
  agenda *atual = primeiroNome;
  
  system("clear"); //limpa a tela 

  cout << "Busca por email" << endl << endl <<endl;
  cout << "Email:" << endl;

  cin.getline(buffer, TAMANHO_NOME);

  while((atual->proximo != primeiroNome) && (strcmp(atual->email, buffer) != 0))
    atual = atual->proximo;

  if(strcmp(atual->email, buffer) != 0) //nenhum resultado
  {
    system("clear"); //limpa a tela
    
    cout << "Nenhum email foi encontrado" << buffer << endl << endl << endl;
    cout << "Pressione qualquer tecla para continuar" << endl;
  
    getchar();
  }
  else
  {
    while(opcao != 'S')
    {

      system("clear"); //limpa a tela
      
      cout << "Reultado da Busca por email: " << buffer << endl << endl;
      
      cout.width(TAMANHO_NOME); cout << left << "Nome";
      cout.width(TAMANHO_NOME); cout << left << "Email";
      cout.width(TAMANHO_NUMERO);  cout << left << "Telefone";
      cout.width(TAMANHO_NUMERO);  cout << left << "Endereço" << endl << endl;
 
      cout.width(TAMANHO_NOME); cout << left << atual->nome;
      cout.width(TAMANHO_NOME); cout << left << atual->email;
      cout.width(TAMANHO_NUMERO);  cout << left << atual->telefone;
      cout.width(TAMANHO_NUMERO);  cout << left << atual->endereco << endl << endl << endl;

      cout << "A para avançar ao proximo resultado" << endl;
      cout << "V para voltar ao resultado anterior" << endl << endl;
      cout << "R para remover" << endl;
      cout << "M para modificar" << endl << endl;      
      cout << "S para sair" << endl;


      opcao = getchar();
      opcao = toupper(opcao);
      
      switch(opcao)
      {
        case 'A':                   
          atual = atual->proximo;
          while(strcmp(atual->email, buffer) != 0) //procura um novo resultado
            atual = atual->proximo;          
        break;
        
        case 'V':
          atual = atual->anterior;
          while(strcmp(atual->email, buffer) != 0) //procura um novo resultado            
            atual = atual->anterior;
        break;
      
        case 'R':             
          removerNomeMenu(atual, primeiroNome);
          opcao = 'S';
        break;
        
        case 'M':             
          modificarNome(atual, primeiroNome);
          opcao = 'S';
        break;
        
        default:
        break;
      }
    }    
  }
}  

void buscarPorTelefone(agenda *&primeiroNome)
{
  char opcao = 'a';
  char buffer[TAMANHO_NUMERO];
  agenda *atual = primeiroNome;
  
  system("clear"); //limpa a tela 

  cout << "Busca por telefone" << endl << endl << endl;
  cout << "Telefone:" << endl;

  cin.getline(buffer, TAMANHO_NUMERO);

  while((atual->proximo != primeiroNome) && (atual->telefone != atoi(buffer)))
    atual = atual->proximo;

  if(atual->telefone != atoi(buffer)) //nenhum resultado
  {
    system("clear"); //limpa a tela
    
    cout << "Nenhum email foi encontrado" << buffer << endl << endl << endl;
    cout << "Pressione qualquer tecla para continuar" << endl;
  
    getchar();
  }
  else
  {
    while(opcao != 'S')
    {

      system("clear"); //limpa a tela
      
      cout << "Reultado da busca por email: " << buffer << endl << endl;
      
      cout.width(TAMANHO_NOME);   cout << left << "Nome";
      cout.width(TAMANHO_NOME);   cout << left << "Email";
      cout.width(TAMANHO_NUMERO); cout << left << "Telefone";
      cout.width(TAMANHO_NUMERO); cout << left << "Endereço" << endl << endl;
 
      cout.width(TAMANHO_NOME);   cout << left << atual->nome;
      cout.width(TAMANHO_NOME);   cout << left << atual->email;
      cout.width(TAMANHO_NUMERO); cout << left << atual->telefone;
      cout.width(TAMANHO_NUMERO); cout << left << atual->endereco << endl << endl << endl;

      cout << "A para avancar ao proximo resultado" << endl;
      cout << "V para voltar ao resultado anterior" << endl << endl;
      cout << "R para remover" << endl;
      cout << "M para modificar" << endl << endl;      
      cout << "S para sair" << endl;


      opcao = getchar();
      opcao = toupper(opcao);
      
      switch(opcao)
      {
        case 'A':                   
          atual = atual->proximo;
          while(atual->telefone != atoi(buffer)) //procura um novo resultado
            atual = atual->proximo;          
        break;
        
        case 'V':
          atual = atual->anterior;
          while(atual->telefone != atoi(buffer)) //procura um novo resultado             
            atual = atual->anterior;
        break;
      
        case 'R':             
          removerNomeMenu(atual, primeiroNome);
          opcao = 'S';
        break;
        
        case 'M':             
          modificarNome(atual, primeiroNome);
          opcao = 'S';
        break;
        
        default:
        break;
      }
    }    
  }
}

void buscarNome(agenda *&primeiroNome)//menu de busca
{
  char opcao = 'a';
     
  if(primeiroNome == NULL) //lista vazia
  {
    system("clear"); //limpa a tela
    
    cout << "Lista vazia" << endl << endl << endl;
    cout << "Pressione qualquer tecla para continuar" << endl;
  
    getchar();
  }
  else
    while(opcao != 'S')
    {
      system("clear"); //limpa a tela
      
      cout << "Busca de Filmes" << endl << endl << endl;
      cout << "Para buscar um filmes, selecione:" << endl;
      cout << "T para titulo" << endl;
      cout << "D para diretor" << endl;
      cout << "A para ano" << endl << endl;
      cout << "S para sair" << endl;

      opcao = getchar();
      opcao = toupper(opcao);
      
      while(opcao != 'S') //escolha do tipo de busca
      {
        switch(opcao)
        {
          case 'T': 
            buscarPorNome(primeiroNome); 
            opcao = 'S';
          break;
         
          case 'D':
            buscarPorEmail(primeiroNome); 
            opcao = 'S'; 
          break;
      
          case 'A': 
            buscarPorTelefone(primeiroNome); 
            opcao='S';
          break;        
             
          default: break;
        }
      }
    }  
}

void modificarRemoverNomeMenu(agenda *&primeiroNome) //menu de romocao/modificacao
{
  char opcao = 'a';  
    
  while(opcao != 'S')
  {  
    system("clear"); //limpa a tela
    
    cout << "Remover ou modificar" << endl << endl << endl;
    cout << "Para encontrar o nome a ser removido/modificado, selecione:" << endl << endl;
    cout << "P para percorrer toda a lista de contatos" << endl;
    cout << "B para buscar um nome" << endl << endl;
    cout << "S para sair" << endl;
  
    opcao = getchar();
    opcao = toupper(opcao);
    
    switch(opcao)
    {  
      case 'P':
        opcao = 'S';
        percorrerNomes(primeiroNome);
      break;
      case 'B':
        buscarNome(primeiroNome);
        opcao = 'S';
      break;
      default:
      break;
    }
  }
}

void inicializar(agenda *&primeiroNome)
{
  ifstream arquivoDados("filmes.data");
 
  primeiroNome = NULL;
 
  if(arquivoDados) // le dados do arquivo, caso exista
  {
    agenda *atual,*novo;  
    char buffer[TAMANHO_NOME];
    while(true)
    {
      arquivoDados.getline(buffer,TAMANHO_NOME);
      if (arquivoDados.eof()) break;
      
      novo = new agenda;
      
      strcpy(novo->nome, buffer);
      arquivoDados.getline(buffer, TAMANHO_NOME);
      strcpy(novo->email, buffer);
      arquivoDados.getline(buffer, TAMANHO_NUMERO);
      novo->telefone = atoi(buffer);
      arquivoDados.getline(buffer, TAMANHO_NUMERO);
      novo->endereco = atoi(buffer);
      
      if(primeiroNome == NULL)
      {
        primeiroNome = novo;
        primeiroNome->proximo = novo;
        primeiroNome->anterior = novo;
      }
      else
      {
        atual->proximo = novo;
        novo->anterior = atual;
        novo->proximo = primeiroNome;
        primeiroNome->anterior = novo;
      }
      
      atual = novo;
    } 
  }
  arquivoDados.close();
}

void finalizar(agenda *&primeiroNome)
{
  remove("filmes.data");
  if(primeiroNome != NULL) //escreve dados em um arquivo, caso existam, liberando a memoria
  {
    ofstream arquivoDados("filmes.data");  
    agenda *atual = primeiroNome->anterior, *ultimo = atual;
    
    while(true)
    {        
      atual = atual->proximo;
                            
      arquivoDados << atual->nome << endl;
      arquivoDados << atual->email << endl;
      arquivoDados << atual->telefone << endl;
      arquivoDados << atual->endereco << endl;            
      
      if(atual != primeiroNome) free(atual->anterior);
     
      if(atual == ultimo) break;
    }   
    free(ultimo);
    arquivoDados.close();    
  }
}