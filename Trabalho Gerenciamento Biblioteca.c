#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ISBN_TAM 14
#define MAX_TITULO_TAM 100
#define MAX_GENERO_TAM 40
#define MAX_AUTOR_TAM 60
#define MAX_AUTORES 3
#define MAX_EMAILS 3
#define MAX_EMAIL_SIZE 50
#define MAX_TELEFONE_SIZE 50
#define MAX_TELEFONES 3
#define MAX_NAME_SIZE 50
#define MAX_RUA_SIZE 50
#define MAX_CEP_SIZE 10
#define MAX_DATE_SIZE 11
#define MAX_PROFISSAO_SIZE 100
#define MAX_USERS_FILE_NAME 20

// Structs

typedef struct {
  char cpf[12];
  char nome[MAX_NAME_SIZE];
  char rua[MAX_RUA_SIZE];
  int numero;
  char cep[MAX_CEP_SIZE];
  char **Emails;
  char **Telefones;
  char DataNascimento[MAX_DATE_SIZE];
  char Profissao[MAX_PROFISSAO_SIZE];
  int num_emails;
  int num_telefones;
} usuario;

typedef struct {
  char ISBN[MAX_ISBN_TAM];
  char titulo[MAX_TITULO_TAM];
  char genero[MAX_GENERO_TAM];
  char autores[MAX_AUTORES][MAX_AUTOR_TAM];
  int quantidade_paginas;
} livro;

typedef struct {
  char cpf[12];
  char ISBN[14];
  char data_retirada[11];
  char data_devolucao[11];
  float ValorMultaDiaria;

} emprestimo;

// Funções manipulação de arquivos

void excluirTodosArquivos() {
    char resposta;

    printf("> Deseja excluir todos os arquivos? (S ou N): ");
    scanf(" %c", &resposta); 

    if (resposta == 'S' || resposta == 's') {

        system("rm *.bin"); // Exclui todos os arquivos .bin no diretório atual
        system("rm *.txt"); // Exclui todos os arquivos .txt no diretório atual
        printf("> Arquivos excluídos com sucesso!\n");
    } else {
        printf("X Nenhum arquivo foi excluído.\n");
    }
}

int verificar_arquivo(const char *nome) {
  FILE *arquivo_aberto = fopen(nome, "rb");

  if (arquivo_aberto == NULL) {
    printf("\n> Arquivo não existe, deseja criar um novo? (S ou N)");
    char resposta;
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's') {
      FILE *novo_arquivo = fopen(nome, "wb"); // Cria um novo arquivo binário
      if (novo_arquivo != NULL) {
        printf("\n> Arquivo criado com sucesso!");
        fclose(novo_arquivo); // Fecha o novo arquivo após a criação
        return 1;
      } else {
        printf("\nX Erro ao criar o arquivo.\n");
        return -1;
      }
    } else {
      return -1;
    }
  } else {
    fclose(arquivo_aberto);
    return 1;
  }
}

void gravar_arquivo(const char *nome, usuario array[], int tamanho) {
  FILE *arquivo_aberto = fopen(nome, "wb+");
  fwrite(array, sizeof(usuario), tamanho, arquivo_aberto);
  fclose(arquivo_aberto);
}

// Funções Manipulação Arquivos Usuários

void listar_todos(usuario array[], int tamanho) { // Passa a array e o tamanho como parametros

  if (tamanho == 0) {
      printf("\nX Não há usuários cadastrados!\n");
  }
  for (int i = 0; i < tamanho; i++) {
    printf("Usuário:\n");
    printf("CPF: %s\n", array[i].cpf);
    printf("Nome: %s\n", array[i].nome);
    printf("Rua: %s\n", array[i].rua);
    printf("Numero: %d\n", array[i].numero);
    printf("CEP: %s\n", array[i].cep);

    printf("Emails:\n"); // Loop para ler os emails
    for (int j = 0; j < array[i].num_emails; j++) {
        printf("%s\n", array[i].Emails[j]);
    }

    printf("Telefones:\n"); // Loop para ler os telefones
    for (int j = 0; j < array[i].num_telefones; j++) {
        printf("%s\n", array[i].Telefones[j]);
    }

    printf("Data de Nascimento: %s\n", array[i].DataNascimento);
    printf("Profissão: %s\n", array[i].Profissao);
    printf("\n");
  }
}

void limpar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF); // Ele descarta os caracteres até achar a quebra de linha ou final do arquivo
}

int procurar_usuario(usuario array[], int tamanho, const char *cpf) { // Passa o array, o tamanho e o cpf como conteudo do ponteiro para poder pegar
  for (int i = 0; i < tamanho; i++) {
    if ((strcmp(array[i].cpf, cpf)) == 0) { // compara se o cpf do array é igual ao cpf que foi digitado
      printf("Usuário encontrado:\n");
      printf("CPF: %s\n", array[i].cpf);
      printf("Nome: %s\n", array[i].nome);
      printf("Rua: %s\n", array[i].rua);
      printf("Numero: %d\n", array[i].numero);
      printf("CEP: %s\n", array[i].cep);

      printf("Emails:\n"); // Loop para ler os emails
      for (int j = 0; j < array[i].num_emails; j++) {
        printf("%s\n", array[i].Emails[j]);
      }

      printf("Telefones:\n"); // Loop para ler os telefones
      for (int j = 0; j < array[i].num_telefones; j++) {
        printf("%s\n", array[i].Telefones[j]);
      }

      printf("Data de Nascimento: %s\n", array[i].DataNascimento);
      printf("Profissão: %s\n", array[i].Profissao);
      printf("\n");
      return 1; // Deu certo retorna 1
    }
  }
  return 0; // Deu errado retorna 0
}

void gravar_usuario(usuario **array, int *tamanho) { // Traz como ponteiro de ponteiro o array pois é uma lista, e o tamanho como *tamanho
  usuario novo_usuario;

  printf("\n> Digite os dados do novo usuário:\n");

  // CPF
  printf("\n> Digite o CPF do usuário: ");
  scanf("%11s", novo_usuario.cpf);
  if (procurar_usuario(*array, *tamanho, novo_usuario.cpf) != 0) { // Certifica se já não existe o cpf cadastrado
    printf("\nX Usuário já cadastrado\n");
    return;
  }

  // Nome
  printf("\n> Digite o Nome do usuário: ");
  scanf("%s", novo_usuario.nome);

  // Rua
  printf("\n> Digite a Rua do usuário: ");
  scanf("%s", novo_usuario.rua);

  // Numero
  printf("\n> Digite o Número da casa/apartamento do Usuário: ");
  scanf("%d", &novo_usuario.numero);

  // CEP
  printf("\n> Digite o CEP do usuário(XXXX-XXXX): ");
  scanf("%s", novo_usuario.cep);

  // Emails
  printf("\n> Quantos Emails serão cadastrados? (Máximo 3) ");
  int quantidade_emails;
  scanf("%d", &quantidade_emails);
  limpar_buffer();

  novo_usuario.num_emails = quantidade_emails; 
  novo_usuario.Emails = (char **)malloc(quantidade_emails * sizeof(char *)); // Aloca a memória de acordo com a quantidade_emails * sizeof(char*)
  for (int i = 0; i < quantidade_emails; i++) {
    novo_usuario.Emails[i] = (char *)malloc((MAX_EMAIL_SIZE + 1) * sizeof(char)); // Aloca individualmente cada email, seguindo o tamanho max_email_size + 1, pois adicionou um
    printf("\n> Digite o email do usuário: ");
    scanf("%s", novo_usuario.Emails[i]);
  }

  // Telefones
  printf("\n> Quantos Telefones serão cadastrados? (Máximo 3) ");
  int quantidade_telefones;
  scanf("%d", &quantidade_telefones);
  limpar_buffer();

  novo_usuario.num_telefones = quantidade_telefones; 
  novo_usuario.Telefones = (char **)malloc(quantidade_telefones * sizeof(char *)); // Aloca a memória de acordo com a quantidade_telefones * sizeof(char*)
  for (int i = 0; i < quantidade_telefones; i++) {
    novo_usuario.Telefones[i] = (char *)malloc((MAX_TELEFONE_SIZE + 1) * sizeof(char)); // Aloca individualmente cada email, seguindo o tamanho max_telefone_size + 1, pois adicionou um
    printf("\n> Digite o telefone do usuário (XX)XXXXXXXX: ");
    scanf("%s", novo_usuario.Telefones[i]);
  }

  limpar_buffer();
  // Data de Nascimento
  printf("\n> Data de nascimento (dd/mm/yyyy): ");
  scanf(" %s", novo_usuario.DataNascimento);

  // Profissão
  printf("\n> Digite a Profissão do usuário: ");
  scanf(" %s", novo_usuario.Profissao);
  limpar_buffer();

  (*tamanho)++;

  *array = realloc(*array, *tamanho * sizeof(usuario)); // Realoca o tamanho reservado para o arquivo com um novo usuario gravado
    if (*array == NULL) {
      perror("X Erro ao realocar memória");
      exit(EXIT_FAILURE);
    }

    // Insere o novo usuário na matriz
    (*array)[*tamanho - 1] = novo_usuario;

    
    FILE *arquivo_aberto = fopen("usuarios.bin", "ab");  // Abre o arquivo e insere nele
    if (arquivo_aberto == NULL) {
      perror("X Erro ao abrir o arquivo");
      exit(EXIT_FAILURE);
    }
    
    fwrite(&((*array)[*tamanho - 1]), sizeof(usuario), 1, arquivo_aberto); // Escreve no arquivo seguindo criterio de tamanho
    fclose(arquivo_aberto);
  
}

usuario *excluir_usuario(usuario *array, int *tamanho, const char *cpf) { // Aponta o ponteiro do usuario array pois vai ser modificado, o tamanho também, e o cpf também é necessário acessar o conteudo
  int encontrado = 0;
  int contador = 0;

  for (int i = 0; i < *tamanho; i++) {
    if (strcmp(array[i].cpf, cpf) == 0) { // Compara se é encontrado o cpf, se sim, ele modifica para encontrado = 1;
      encontrado = 1;
      printf("\n> Usuário encontrado e excluído\n");
    } else {
      array[contador++] = array[i]; 
    }
  }

  if (encontrado) { // Se encontrar ele executa o resto
    (*tamanho)--; // Diminui um no tamanho
    return realloc(array, (*tamanho) * sizeof(usuario)); // Realoca o tamanho reservado para o arquivo com um novo
  } else {
    printf("X Impossível excluir");
    return array;
  }
}

void alterar_usuario(usuario *array, int tamanho, const char *cpf) { // Passa o ponteiro do array, o tamanho e o cpf
  int found = -1; 

  for (int i = 0; i < tamanho; i++) {
    if (strcmp(array[i].cpf, cpf) == 0) {
      found = i; // se encontrar ele altera a encontrado para a posição
      break;
    }
  }

  if (found != -1) {
    printf("Usuário encontrado:\n");
    printf("CPF: %s\n", array[found].cpf);
    printf("Nome: %s\n", array[found].nome);
    printf("Rua: %s\n", array[found].rua);
    printf("Numero: %d\n", array[found].numero);
    printf("CEP: %s\n", array[found].cep);

    // Itera sobre os emails
    printf("Emails:\n");
    for (int j = 0; j < array[found].num_emails; j++) {
      printf("Email %d: %s\n", j + 1, array[found].Emails[j]);
    }

    // Itera sobre os telefones
    printf("Telefones:\n");
    for (int j = 0; j < array[found].num_telefones; j++) {
      printf("Telefone %d: %s\n", j + 1, array[found].Telefones[j]);
    }

    printf("\nData de Nascimento: %s\n", array[found].DataNascimento);
    printf("\nProfissão: %s\n", array[found].Profissao);
    printf("\n");

    printf("\n> Deseja alterar dados deste usuário? (S ou N): ");
    char resposta;
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's') {
      // Alterar Rua
      printf("\n> Nova Rua (deixe em branco para manter): ");
      char nova_rua[MAX_RUA_SIZE];
      limpar_buffer();
      fgets(nova_rua, sizeof(nova_rua), stdin);
      nova_rua[strcspn(nova_rua, "\n")] = '\0';
      if (strlen(nova_rua) > 0) {
        strcpy(array[found].rua, nova_rua);
      }

      // Alterar Número
      printf("\n> Novo Número (digite 0 para manter): ");
      int novo_numero;
      scanf("%d", &novo_numero);
      limpar_buffer();
      if (novo_numero != 0) {
        array[found].numero = novo_numero;
      }

      // Alterar CEP
      printf("\n> Novo CEP (deixe em branco para manter): ");
      char novo_cep[MAX_CEP_SIZE];
      fgets(novo_cep, sizeof(novo_cep), stdin);
      novo_cep[strcspn(novo_cep, "\n")] = '\0';
      if (strlen(novo_cep) > 0) {
        strcpy(array[found].cep, novo_cep);
      }

      // Alterar Emails
      printf("\n> Quantos Emails serão alterados? ");
      int quantidade_emails;
      scanf("%d", &quantidade_emails);
      limpar_buffer();
      for (int i = 0; i < quantidade_emails; i++) {
        printf("\n> Novo Email %d (deixe em branco para manter): ", i + 1);
        char novo_email[MAX_EMAIL_SIZE];
        fgets(novo_email, sizeof(novo_email), stdin);
        novo_email[strcspn(novo_email, "\n")] = '\0';
        if (strlen(novo_email) > 0) {
          strcpy(array[found].Emails[i], novo_email);
        }
      }

      // Alterar Telefones
      printf("\n> Quantos Telefones serão alterados? ");
      int quantidade_telefones;
      scanf("%d", &quantidade_telefones);
      limpar_buffer();  // Limpa o buffer após a leitura de quantidade_telefones

      for (int i = 0; i < quantidade_telefones; i++) {
          printf("\n> Novo Telefone %d (deixe em branco para manter): ", i + 1);
          scanf(" %[^\n]", array[found].Telefones[i]);
          limpar_buffer();
      }

      // Altera a Data de Nascimento
      printf("\n> Nova Data de Nascimento (dd/mm/yyyy): ");
      scanf(" %s", array[found].DataNascimento);
      limpar_buffer();

      // Altera a Profissão
      printf("\n> Nova Profissão: ");
      scanf(" %s", array[found].Profissao);
      limpar_buffer();

    }
  } else {
    printf("X Usuário não encontrado.\n");
  }
}

// Emprestimos

/* Description: Function that checks if a loan record exists.
Parameters: The function takes the array of loans recorded so far, the CPF associated with the sought loan, as well as the ISBN. It also takes the size of the array.

Returns the index of the found loan, which, if not found, is -1.
  */
int emprestimo_existe(emprestimo array[], const char *cpf, const char *isbn, int tamanho) {
  int achou = 0, i,index=0;
  int indice = -1;
  for(i=0;i<tamanho;i++){
    if (strcmp(array[i].cpf, cpf) == 0 && strcmp(array[i].ISBN, isbn) == 0) {
      achou++;
      indice = i;
    }
  }
  if(achou>1){
    int achados[achou];
    for(i=0;i<tamanho;i++){
      if (strcmp(array[i].cpf, cpf) == 0 && strcmp(array[i].ISBN, isbn) == 0) {
        achados[index] = i;
        index++;
      }
    }
    printf("X Foi achado mais de um emprestimo com esse CPF e ISBN.\nEscolha outro dado para fornecer: ");
    printf("\n1 - Data de retirada");
    printf("\n2 - Data de devolução");
     char data[11];
    int opt;
    printf("\nEscolha: ");
    scanf("%d", &opt);
    switch(opt){
      case 1 :
        printf("> Digite a data de retirada: ");
        scanf("%s",&data);
        for(int j = 0; j<achou;j++){
          int indice_nav = achados[j];
          if(strcmp(array[indice_nav].data_retirada, data)==0){
            indice = indice_nav;
            break;
          }
        }
        printf("X Empréstimo não encontrado");
        break;
      case 2 :
      printf("> Digite a data de devolução: ");
      scanf("%s",&data);
      for(int j = 0; j<achou;j++){
        int indice_nav = achados[j];
        if(strcmp(array[indice_nav].data_devolucao, data)==0){
          indice = indice_nav;
          break;
        }
      }
      printf("X Empréstimo não encontrado");
      break;
    default:
        printf("X Opção inválida");
    }
  }
  return indice;
}
/* Description: Function that checks if a loan record exists considering it's date too.
Parameters: The function takes the array of loans recorded so far, the CPF associated with the sought loan, as well as the ISBN. It also takes the size of the array and the dates of the loan.

Returns the index of the found loan, which, if not found, is -1. */
int emprestimo_existe_data(emprestimo array[], const char *cpf, const char *isbn,const char *retirada,const char *devolucao, int tamanho) {
  int achou = -1;
  for(int i=0;i<tamanho;i++){
    if (strcmp(array[i].cpf, cpf) == 0 && strcmp(array[i].ISBN, isbn) == 0 && strcmp(array[i].data_retirada, retirada) == 0 || strcmp(array[i].cpf, cpf) == 0 && strcmp(array[i].ISBN, isbn) == 0 && strcmp(array[i].data_devolucao, devolucao) == 0) {
      achou = i;
      break;
    }
  }
  return achou;
}
/* Description: Function that lists all existing loans.
Parameters: The function takes the array of loans recorded so far and the size of the array.

Prints all the loans found. */
void listar_emprestimos(emprestimo array[], int tamanho) {
  if(tamanho==0){
    printf("X Arquivo vazio!");
  }
  for(int i = 0;i<tamanho;i++){
    printf("\n---------------------------------\n");
    printf("CPF: %s\n", array[i].cpf);
    printf("ISBN: %s\n", array[i].ISBN);
    printf("Data de retirada: %s\n", array[i].data_retirada);
    printf("Data de devolução: %s\n", array[i].data_devolucao);
    printf("Multa: %f\n", array[i].ValorMultaDiaria);
    printf("---------------------------------\n");
  }
}
/* Description: Function that calls another function to search for the loan and prints the existing loan at the returned index.
  Parameters: The function takes the array of loans recorded so far, the CPF associated with the sought loan, as well as the ISBN. It also takes the size of the array.
 Prints the loan fount. */
void procurar_emprestimo(emprestimo array[], int tamanho, const char *cpf, const char *isbn) {
      int i = emprestimo_existe(array,cpf, isbn,tamanho);
      if(i==-1)
        printf("X Empréstimo não encontrado!");
      else{
        printf("\nEmprestimo encontrado:\n");
        printf("\nCPF: %s\n", array[i].cpf);
        printf("ISBN: %s\n", array[i].ISBN);
        printf("Data de retirada: %s\n", array[i].data_retirada);
        printf("Data de devolução: %s\n", array[i].data_devolucao);
        printf("Multa: %f\n", array[i].ValorMultaDiaria);
    }

}

int verificarISBN_emprestimo(char *nome, char *ISBN) {
  FILE *arquivo_aberto = fopen(nome, "rb");
  if (arquivo_aberto == NULL){
    arquivo_aberto = fopen(nome, "wb+");
    fclose(arquivo_aberto);
    arquivo_aberto = fopen(nome, "rb");
  }       
  livro book;
  int tamanho = 0;

  while (fread(&book, sizeof(livro), 1, arquivo_aberto) == 1){
    tamanho++;
  }

  fseek(arquivo_aberto, 0, SEEK_SET);
  livro *array = malloc(tamanho * sizeof(livro));

  if (array == NULL) {
    perror("X Erro de alocação de memória");
    fclose(arquivo_aberto);
    exit(EXIT_FAILURE);
  }

  int lidos = fread(array, sizeof(livro), tamanho, arquivo_aberto);

  if (lidos != tamanho) {
    perror("X Erro na leitura do arquivo de emprestimo");
    fclose(arquivo_aberto);
  }
  int i = 0;
  while (i < tamanho) { 
    if (strcmp(array[i].ISBN, ISBN) == 0) {       
      return 1; // ISBN já existe
    }
    i++;
  }
  return 0; // ISBN não existe
}

int verificarCPF_emprestimo(char *nome, char *CPF) {
  FILE *arquivo_aberto = fopen(nome, "rb");
  if (arquivo_aberto == NULL){
    arquivo_aberto = fopen(nome, "wb+");
    fclose(arquivo_aberto);
    arquivo_aberto = fopen(nome, "rb");
  }       
  usuario user;
  int tamanho = 0;

  while (fread(&user, sizeof(usuario), 1, arquivo_aberto) == 1){
    tamanho++;
  }

  fseek(arquivo_aberto, 0, SEEK_SET);
  usuario *array = malloc(tamanho * sizeof(usuario));

  if (array == NULL) {
    perror("X Erro de alocação de memória");
    fclose(arquivo_aberto);
    exit(EXIT_FAILURE);
  }

  int lidos = fread(array, sizeof(usuario), tamanho, arquivo_aberto);

  if (lidos != tamanho) {
    perror("X Erro na leitura do arquivo de emprestimo");
    fclose(arquivo_aberto);
  }
  int i = 0;
  while (i < tamanho) { 
    if (strcmp(array[i].cpf, CPF) == 0) {       
      return 1; // ISBN já existe
    }
    i++;
  }

  return 0; // ISBN não existe
}
/* Description: Function that reallocates the array for a new loan record.
Parameters: The function takes the array of loans recorded so far, the size of the array, and the loan to be registered.

Returns the loan. */
void adicionar_emprestimo(emprestimo *array[], int *tamanho,emprestimo lend) {
  int verificarISBN = verificarISBN_emprestimo("livros.bin", lend.ISBN);
  int verificarCPF = verificarCPF_emprestimo("usuarios.bin", lend.cpf);
  if(verificarCPF == 0 || verificarISBN==0){
    printf("X Dados invalidos: insira um CPF e ISBN existente no sistema!");
    exit(0);
  }
  *tamanho = *tamanho + 1;
  *array = (emprestimo *)realloc(*array, *tamanho * sizeof(emprestimo));
  *array[*tamanho-1] = lend;
  //return lend;
}
/* Description: Function that writes the loans from the array to the open file.
Parameters: The function takes the loan file, the array of loans recorded so far, and the size of the array.

Writes to the file and closes it. */
void gravar_emprestimo(const char *nome, emprestimo array[], int tamanho) {
  FILE *arquivo_aberto = fopen(nome, "wb+");
  int taman = fwrite(array, sizeof(emprestimo), tamanho, arquivo_aberto);
  fclose(arquivo_aberto);
}
/*Description: Function that calls another function to search for the loan and updates the existing loan at the returned index.
Parameters: The function takes the loan file, the array of loans recorded so far, the size of the array, the CPF associated with the sought loan, and the ISBN.

It checks if a loan identical to the provided information already exists, and if not, it updates the loan in the array.  */
void alterar_emprestimo(emprestimo array[], const char *cpf, const char *isbn, int tamanho) {
  int contador = 0;
  int found = emprestimo_existe(array, cpf, isbn, tamanho);
  emprestimo temp_lend;
    if (found!=-1) {
        printf("\n> Emprestimo encontrado:\n");
        printf("\n> Digite o novo CPF: ");
        scanf("%s", &temp_lend.cpf);
        printf("\n> Digite o novo ISBN: ");
        scanf("%s", &temp_lend.ISBN);
        printf("\n> Digite a nova data de retirada: ");
        scanf("%s", &temp_lend.data_retirada);
        printf("\n> Digite a nova data de devolução: ");
        scanf("%s", &temp_lend.data_devolucao);
        printf("\n> Digite a nova multa: ");
        scanf("%f", &temp_lend.ValorMultaDiaria);
        int existe = emprestimo_existe_data(array, temp_lend.cpf,temp_lend.ISBN,temp_lend.data_retirada,temp_lend.data_devolucao, tamanho);
        if(existe==-1){array[found] = temp_lend;}
        else
          printf("X Emprestimo similar/igual já cadastrado");

    }
}
/*Description: Function that calls another function to search for the loan and deletes the existing loan at the returned index.
Parameters: The function takes the loan file, the array of loans recorded so far, the size of the array, the CPF associated with the sought loan, and the ISBN.

It checks if a loan exists and records all the other loans in the array back, excluding the specified one. It also reallocates the array to a smaller size.  */
emprestimo* excluir_emprestimo(emprestimo array[], const char *cpf, const char *isbn, int tamanho) {
  emprestimo* array_temp = malloc((tamanho-1) * sizeof(emprestimo));
  int encontrado = 0, contador = 0;
  int indice = emprestimo_existe(array, cpf, isbn,  tamanho);
  for(int i = 0; i<tamanho;i++) {
    if (indice==i) {
      encontrado = 1;
      printf("\n> Emprestimo encontrado e excluído\n");
    }
  
    else{
      array_temp[contador] = array[i];
      contador++;
    }
  }
  
  if (encontrado==1) {
    free(array);
    return array_temp;
  } else {
    printf("X Impossível excluir");
    free(array_temp);
    return NULL;
  }
}

// Livros - Extras

int verificarISBN(livro *array[], int *tamanho, char *ISBN) {
  int i = 0;
  while (i < *tamanho) { 
    if (strcmp(array[i]->ISBN, ISBN) == 0) {       
      return 1; // ISBN já existe
    }
    i++;
  }

  return 0; // ISBN não existe
}

void gravar_livro(livro array[], int tamanho) { 
  FILE* arquivo = fopen("livros.bin", "wb+");
  
  if (arquivo == NULL) {
    perror("X Erro ao salvar no arquivo de livros");
    exit(EXIT_FAILURE);
  }
  fwrite(array, sizeof(livro), tamanho, arquivo); // Salva o array no arquivo .bin quando sai do submenu
  fclose(arquivo);
}

// Livros - Principal 

void listar_livros(livro array[], int tamanho) { // Pronta
  int i;
  printf("\n====== Lista de Livros ======\n");
  for (i = 0; i < tamanho; i++) {
    printf("\nLivro #%d\n", i+1);
    printf("\nISBN: %s\n", array[i].ISBN);
    printf("Título: %s\n", array[i].titulo);
    printf("Gênero: %s\n", array[i].genero);
    printf("Autores: %s, %s, %s\n", array[i].autores[0], array[i].autores[1], array[i].autores[2]);
    printf("Quantidade de Páginas: %d\n", array[i].quantidade_paginas);
    printf("=============================\n");
  }
  if (tamanho == 0) {
    printf("\nX Não há livros cadastrados!\n");
  }
}

void procurar_livro(livro array[], int tamanho) { // Pronta
  int encontrado = 0, i = 0;
  char procurarISBN[MAX_ISBN_TAM];
  
  printf("> Digite o ISBN do livro que deseja procurar (13 dígitos): ");
  fgets(procurarISBN, sizeof(procurarISBN), stdin);

  
  size_t len = strlen(procurarISBN);
  
  if (len > 0 && procurarISBN[len - 1] == '\n') {
    procurarISBN[len - 1] = '\0';  // Remove caractere de nova linha
  }
  
  if ((len) != 13) {
    printf("X Formato de ISBN inválido. O ISBN deve ter 13 caracteres.\n");
    return;
  }
  
  while (i < tamanho) { 
    if (strcmp(array[i].ISBN, procurarISBN) == 0) { // Compara o ISBN dado com o ISBN do array
      encontrado = 1; // Livro encontrado :P
      printf("\n===== Livro Encontrado: =====\n");
      printf("\nLivro #%d\n", i +1);
      printf("ISBN: %s\n", array[i].ISBN);
      printf("Título: %s\n", array[i].titulo);
      printf("Gênero: %s\n", array[i].genero);
      printf("Autores: %s, %s, %s\n", array[i].autores[0], array[i].autores[1], array[i].autores[2]);
      printf("Quantidade de Páginas: %d\n", array[i].quantidade_paginas);
      printf("=============================\n");
      break; // Para a procura após achar o livro
    }
    i++;
  }

  if (!encontrado) {
    printf("\nX Livro com ISBN %s não encontrado.\n", procurarISBN);
  }
}

void incluir_livro(livro *array[], int *tamanho) { // Pronta
  int adicionar;

  do { 
    livro novoLivro;
    
    printf("> Digite o ISBN do livro (13 dígitos): ");
    fgets(novoLivro.ISBN, sizeof(novoLivro.ISBN), stdin);

    size_t len = strlen(novoLivro.ISBN);

    if (len > 0 && novoLivro.ISBN[len - 1] == '\n') {
      novoLivro.ISBN[len - 1] = '\0';  // Remove caractere de nova linha
    }
    
    if ((len) != 13) {
      printf("X Formato de ISBN inválido. O ISBN deve ter 13 caracteres.\n");
      return;
    }

    if (verificarISBN(array, tamanho, novoLivro.ISBN)) { 
      printf("X ISBN já registrado. Não é possível adicionar o livro.\n");
      return;
    }

    limpar_buffer();

    do {
      printf("> Digite o título do livro: ");
      fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
      novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0'; // Remove caractere de nova linha
  
      if (strlen(novoLivro.titulo) == 0) {
        printf("X Título do livro não pode ser deixado em branco.\n");
      }
    } while (strlen(novoLivro.titulo) == 0);       
  
    do {
      printf("> Digite o gênero do livro: ");
      fgets(novoLivro.genero, sizeof(novoLivro.genero), stdin);
      novoLivro.genero[strcspn(novoLivro.genero, "\n")] = '\0'; // Remove caractere de nova linha
  
      if (strlen(novoLivro.genero) == 0) {
        printf("X Gênero do livro não pode ser deixado em branco.\n");
      }
    } while (strlen(novoLivro.genero) == 0);
    
    printf("> Digite os autores do livro (até 3 autores, deixe em branco se não houver):\n");
    printf("> Autor 1: ");
    do {
      fgets(novoLivro.autores[0], sizeof(novoLivro.autores[0]), stdin);

      size_t len = strlen(novoLivro.autores[0]);
      if (len > 0 && novoLivro.autores[0][len - 1] == '\n') {
        novoLivro.autores[0][len - 1] = '\0'; // Remove caractere de nova linha
      }

      if (strlen(novoLivro.autores[0]) == 0) {
        printf("X Pelo menos um autor deve ser fornecido. Tente novamente:\n");
        printf("> Autor 1: ");
      }
    } while (strlen(novoLivro.autores[0]) == 0);

    for (int i = 1; i < 3; ++i) {
      printf("> Autor %d: ", i + 1);
      fgets(novoLivro.autores[i], sizeof(novoLivro.autores[i]), stdin);

      size_t len = strlen(novoLivro.autores[i]);
      if (len > 0 && novoLivro.autores[i][len - 1] == '\n') {
        novoLivro.autores[i][len - 1] = '\0'; // Remove caractere de nova linha
      }

      if (strlen(novoLivro.autores[i]) == 0) {
        strcpy(novoLivro.autores[i], "n/a");
      }
    }
 
    do {
        printf("> Digite a quantidade de páginas do livro: ");
  
        if (scanf("%d", &novoLivro.quantidade_paginas) == 1) {
            limpar_buffer();
            break;
        } else {
            printf("X Entrada inválida. Tente novamente.\n");
            limpar_buffer();
          }
    } while (1);

    *tamanho = *tamanho + 1;
    *array = (livro *)realloc(*array, *tamanho * sizeof(livro)); // Aumenta o tamanho do array
    (*array)[*tamanho-1] = novoLivro; // Adiciona o novo livro ao array
    
    printf("> Livro adicionado com sucesso!\n");

    printf("> Deseja adicionar outro livro? (1 para Sim, 0 para Não): ");
    while (scanf("%d", &adicionar) != 1) {
      printf("X Entrada inválida. Por favor, digite 1 para Sim ou 0 para Não: ");
    }
    limpar_buffer();
  } while (adicionar == 1); // Permite que mais de 1 livro seja adicionado
}

void alterar_livro(livro *array[], int *tamanho) { // Pronta
  int encontrado = 0, i = 0;
  livro livroEncontrado;

  printf("> Digite o ISBN do livro que deseja procurar (13 dígitos): ");
  fgets(livroEncontrado.ISBN, sizeof(livroEncontrado.ISBN), stdin);

  size_t len = strlen(livroEncontrado.ISBN);
  if (len > 0 && livroEncontrado.ISBN[len - 1] == '\n') {
    livroEncontrado.ISBN[len - 1] = '\0';  // Remove caractere de nova linha
  }
  
  if ((len) != 13) {
    printf("X Formato de ISBN inválido. O ISBN deve ter 13 caracteres.\n");
    return;
  }

  limpar_buffer();

  while (i < *tamanho) {    
    if (strcmp((*array)[i].ISBN, livroEncontrado.ISBN) == 0) { // Compara o ISBN com o ISBN fornecido      
      encontrado = 1; // Livro encontrado
      printf("\n===== Livro Encontrado: =====\n");
      printf("\nLivro #%d\n", i + 1);
      printf("ISBN: %s\n", array[i]->ISBN);
      printf("Título: %s\n", array[i]->titulo);
      printf("Gênero: %s\n", array[i]->genero);
      printf("Autores: %s, %s, %s\n", array[i]->autores[0], array[i]->autores[1], array[i]->autores[2]);
      printf("Quantidade de Páginas: %d\n", array[i]->quantidade_paginas);
      printf("=============================\n");

      printf("\n> Atualize os dados do livro:\n"); // Solicita ao usuário os novos dados
      do {
        printf("> Digite o título do livro: ");
        fgets(livroEncontrado.titulo, sizeof(livroEncontrado.titulo), stdin);
        livroEncontrado.titulo[strcspn(livroEncontrado.titulo, "\n")] = '\0'; // Remove caractere de nova linha

        if (strlen(livroEncontrado.titulo) == 0) {
          printf("X Título do livro não pode ser deixado em branco.\n");
        }
      } while (strlen(livroEncontrado.titulo) == 0);       

      do {
        printf("> Digite o gênero do livro: ");
        fgets(livroEncontrado.genero, sizeof(livroEncontrado.genero), stdin);
        livroEncontrado.genero[strcspn(livroEncontrado.genero, "\n")] = '\0'; // Remove caractere de nova linha

        if (strlen(livroEncontrado.genero) == 0) {
          printf("X Gênero do livro não pode ser deixado em branco.\n");
        }
      } while (strlen(livroEncontrado.genero) == 0);
      
      printf("> Digite os autores do livro (até 3 autores, deixe em branco se não houver):\n");
      printf("> Autor 1: ");
      do {
        fgets(livroEncontrado.autores[0], sizeof(livroEncontrado.autores[0]), stdin);

        size_t len = strlen(livroEncontrado.autores[0]);
        if (len > 0 && livroEncontrado.autores[0][len - 1] == '\n') {
          livroEncontrado.autores[0][len - 1] = '\0'; // Remove caractere de nova linha
        }

        if (strlen(livroEncontrado.autores[0]) == 0) {
          printf("X Pelo menos um autor deve ser fornecido. Tente novamente:\n");
          printf("> Autor 1: ");
        }
      } while (strlen(livroEncontrado.autores[0]) == 0);

      for (int i = 1; i < 3; ++i) {
        printf("> Autor %d: ", i + 1);
        fgets(livroEncontrado.autores[i], sizeof(livroEncontrado.autores[i]), stdin);

        size_t len = strlen(livroEncontrado.autores[i]);
        if (len > 0 && livroEncontrado.autores[i][len - 1] == '\n') {
          livroEncontrado.autores[i][len - 1] = '\0'; // Remove caractere de nova linha
        }

        if (strlen(livroEncontrado.autores[i]) == 0) {
          strcpy(livroEncontrado.autores[i], "n/a");
        }
      }

      do {
          printf("> Digite a quantidade de páginas do livro: ");

          if (scanf("%d", &livroEncontrado.quantidade_paginas) == 1) {
              limpar_buffer();
              break;
          } else {
              printf("X Entrada inválida. Tente novamente.\n");
              limpar_buffer();
            }
      } while (1);

      *array[i] = livroEncontrado; // Substitui o conteúdo do array no índice específico pelo livro alterado

      printf("\n> Livro alterado com sucesso!\n");

      break; // Interrompe a busca após encontrar o livro
    }
    i++;
  }

  if (!encontrado) { 
    printf("\nX Livro com ISBN %s não encontrado.\n", livroEncontrado.ISBN);
  }
}

void excluir_livro(livro *array[], int *tamanho) { // Pronta
  int encontrado = 0, i = 0;
  char procurarISBN[MAX_ISBN_TAM];

  printf("> Digite o ISBN do livro que deseja excluir (13 dígitos): ");
  fgets(procurarISBN, sizeof(procurarISBN), stdin);

  size_t len = strlen(procurarISBN);
  if (len > 0 && procurarISBN[len - 1] == '\n') {
    procurarISBN[len - 1] = '\0';  // // Remove caractere de nova linha
  }
  
  if ((len) != 13) {
    printf("X Formato de ISBN inválido. O ISBN deve ter 13 caracteres.\n");
    return;
  }

  limpar_buffer();

  while (i < *tamanho) {  
    if ((strcmp((*array)[i].ISBN, procurarISBN) == 0)) { // Compara o ISBN com o ISBN fornecido
      encontrado = 1; // Livro encontrado
      printf("\n====== Livro Excluído: ======\n");
      printf("\nLivro #%d\n", i + 1);
      printf("ISBN: %s\n", array[i]->ISBN);
      printf("Título: %s\n", array[i]->titulo);
      printf("Gênero: %s\n", array[i]->genero);
      printf("Autores: %s, %s, %s\n", array[i]->autores[0], array[i]->autores[1], array[i]->autores[2]);
      printf("Quantidade de Páginas: %d\n", array[i]->quantidade_paginas);
      printf("=============================\n");
      
      for (int j = i; j < *tamanho - 1; j++) { // Desloca todos os livros uma posição para trás
        (*array)[j] = (*array)[j + 1];
      }

      (*tamanho)--; // Decrementa o tamanho do array
      *array = (livro *)realloc(*array, *tamanho * sizeof(livro)); // Redimensiona o array com o novo tamanho reduzido
      printf("\n> Livro excluído com sucesso!\n");

      break;
    }
    i++;
  }

  if (!encontrado) {
    printf("\nX Livro com ISBN %s não encontrado.\n", procurarISBN);
  } 
}

// Relatórios - Extras

int calcular_idade(const char *data_nascimento) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int dia, mes, ano;
    sscanf(data_nascimento, "%d/%d/%d", &dia, &mes, &ano);

    int idade = tm.tm_year + 1900 - ano;

    if (tm.tm_mon + 1 < mes || (tm.tm_mon + 1 == mes && tm.tm_mday < dia)) {
        idade--;
    }

    return idade;
}

int contar_autores(char autores[MAX_AUTORES][MAX_AUTOR_TAM]) {
  int contador = 0;

  for (int i = 0; i < 3; ++i) {
    if (strlen(autores[i]) > 0 && strcmp(autores[i], "n/a") != 0) {
      contador++;
    }
  }
  return contador;
}

time_t converter_data(char data[]) {
  struct tm tm;
  strptime(data, "%d-%m-%Y", &tm);
  return mktime(&tm);
}

// Relatórios - Principal

void listar_usuarios_mais_velhos(int idade_minima) {
  int contador = 0;
  FILE *arquivo_aberto = fopen("usuarios.bin", "rb");
  if (arquivo_aberto == NULL){
    arquivo_aberto = fopen("usuarios.bin", "wb+");
    fclose(arquivo_aberto);
    arquivo_aberto = fopen("usuarios.bin", "rb");
  }       
  usuario user;
  int tamanho = 0;

  while (fread(&user, sizeof(usuario), 1, arquivo_aberto) == 1){
    tamanho++;
  }

  fseek(arquivo_aberto, 0, SEEK_SET);
  usuario *array = malloc(tamanho * sizeof(usuario));

  if (array == NULL) {
    perror("X Erro de alocação de memória");
    fclose(arquivo_aberto);
    exit(EXIT_FAILURE);
  }

  int lidos = fread(array, sizeof(livro), tamanho, arquivo_aberto);

  if (lidos != tamanho) {
    perror("X Erro na leitura do arquivo de livros");
    fclose(arquivo_aberto);
    exit(EXIT_FAILURE);
  }

  fclose(arquivo_aberto);

  FILE* arquivoTexto = fopen("usuarios_relatorio.txt", "a");

  if (arquivoTexto == NULL) {
    perror("X Erro ao criar ou abrir o arquivo de relatório de usuários");
    exit(EXIT_FAILURE);
    return;
  }

  fprintf(arquivoTexto, "===== Usuários com mais de %d anos de Idade =====\n", idade_minima);
  printf("\n===== Usuários com mais de %d anos de Idade =====\n", idade_minima);
  
  for (int i = 0; i < tamanho; i++) {
    int idade = calcular_idade(array[i].DataNascimento);

    if (idade > idade_minima) {
      printf("Usuário:\n");
      printf("CPF: %s\n", array[i].cpf);
      printf("Nome: %s\n", array[i].nome);
      printf("Rua: %s\n", array[i].rua);
      printf("Numero: %d\n", array[i].numero);
      printf("CEP: %s\n", array[i].cep);

      fprintf(arquivoTexto, "Usuário:\n");
      fprintf(arquivoTexto, "CPF: %s\n", array[i].cpf);
      fprintf(arquivoTexto, "Nome: %s\n", array[i].nome);
      fprintf(arquivoTexto, "Rua: %s\n", array[i].rua);
      fprintf(arquivoTexto, "Numero: %d\n", array[i].numero);
      fprintf(arquivoTexto, "CEP: %s\n", array[i].cep);

      printf("Emails:\n");
      for (int j = 0; j < array[i].num_emails; j++) {
        printf("%s\n", array[i].Emails[j]);
      }

      fprintf(arquivoTexto, "Emails:\n");
      for (int j = 0; j < array[i].num_emails; j++) {
        fprintf(arquivoTexto, "%s\n", array[i].Emails[j]);
      }

      printf("Telefones:\n");
      for (int j = 0; j < array[i].num_telefones; j++) {
        printf("%s\n", array[i].Telefones[j]);
      }

      fprintf(arquivoTexto, "Telefones:\n");
      for (int j = 0; j < array[i].num_telefones; j++) {
        fprintf(arquivoTexto, "%s\n", array[i].Telefones[j]);
      }

      printf("Data de Nascimento: %s\n", array[i].DataNascimento);
      printf("Profissão: %s\n", array[i].Profissao);
      printf("Idade: %d\n", idade);
      printf("================================================\n\n");

      fprintf(arquivoTexto, "Data de Nascimento: %s\n", array[i].DataNascimento);
      fprintf(arquivoTexto, "Profissão: %s\n", array[i].Profissao);
      fprintf(arquivoTexto, "Idade: %d\n", idade);
      fprintf(arquivoTexto, "================================================\n\n");
      contador++;
    }
  }

  if (contador == 0) {
    fprintf(arquivoTexto, "\nNenhum usuário encontrado.\n\n");
    printf("\nX Nenhum usuário encontrado.\n");
  } else {
      printf("> Usuários com mais de %d anos salvos em 'usuarios_relatorio.txt'\n", idade_minima);
  }

  fclose(arquivoTexto); // Fecha o arquivo
}

void livros_autores() { // Pronta
  int X, contador = 0, i = 0;
  FILE *arquivo = fopen("livros.bin", "rb");
  if (arquivo == NULL){
    arquivo = fopen("livros.bin", "wb+");
    fclose(arquivo);
    arquivo = fopen("livros.bin", "rb");
  }       
  livro book;
  int tamanho = 0;

  while (fread(&book, sizeof(livro), 1, arquivo) == 1){ // Conta quantos livros já existem no arquivo binário
    tamanho++;
  }

  fseek(arquivo, 0, SEEK_SET);
  livro *array = (livro *)malloc(tamanho * sizeof(livro));

  if (array == NULL) {
    perror("X Erro de alocação de memória");
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }

  int lidos = fread(array, sizeof(livro), tamanho, arquivo);

  if (lidos != tamanho) {
    perror("X Erro na leitura do arquivo de livros");
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }

  fclose(arquivo);
  FILE* arquivoTexto = fopen("livros_relatorio.txt", "a");

  if (arquivoTexto == NULL) {
    perror("X Erro ao criar ou abrir o arquivo de relatório de livros");
    exit(EXIT_FAILURE);
    return;
  }

  while (1) {
    printf("> Digite qual o número deve ser superado pelo número de autores (de 0 a 2): ");

    if (scanf("%d", &X) != 1) { // Confere se o input é um inteiro
        printf("X Entrada inválida. Por favor, digite um inteiro.\n");
        limpar_buffer(); // Limpa o buffer do input
        continue; // Pergunta de novo ao usuário
    }
    
    if (X < 0 || X > 2) { // Confere se X está no alcance válido
        printf("X Número de autores inválido. Por favor, digite um número entre 0 e 2.\n");
        limpar_buffer(); // Limpa o buffer do input
        continue; // Pergunta de novo ao usuário
    }
    break; // Quebra do loop se ambas as condições são atingidas
  }

  fprintf(arquivoTexto, "===== Livros com mais de %d Autores =====\n", X);
  printf("\n===== Livros com mais de %d Autores =====\n", X);

  while (i < tamanho) {
    int numAutores = contar_autores(array[i].autores);

    if (numAutores > X) {
      fprintf(arquivoTexto, "\nLivro #%d\n", i + 1);
      fprintf(arquivoTexto, "\nISBN: %s\n", array[i].ISBN);   
      fprintf(arquivoTexto, "Título: %s\n", array[i].titulo);
      fprintf(arquivoTexto, "Gênero: %s\n", array[i].genero);
      fprintf(arquivoTexto, "Autores: %s, %s, %s\n", array[i].autores[0], array[i].autores[1], array[i].autores[2]);
      fprintf(arquivoTexto, "Quantidade de Páginas: %d\n", array[i].quantidade_paginas);
      fprintf(arquivoTexto, "========================================\n\n");
      
      printf("\nLivro #%d\n", i + 1);
      printf("\nISBN: %s\n", array[i].ISBN);
      printf("Título: %s\n", array[i].titulo);
      printf("Gênero: %s\n", array[i].genero);
      printf("Autores: %s, %s, %s\n", array[i].autores[0], array[i].autores[1], array[i].autores[2]);
      printf("Quantidade de Páginas: %d\n", array[i].quantidade_paginas);
      printf("========================================\n");
      contador++;
    }
    i++;
  }
  
  if (contador == 0) {
    fprintf(arquivoTexto, "\nNenhum livro encontrado.\n\n");
    printf("\nX Nenhum livro encontrado.\n");
  } else {
      printf("> Livros com mais de %d autores salvos em 'livros_relatorio.txt'\n", X);
  }

  fclose(arquivoTexto); // Fecha o arquivo .txt
}

void emprestimos_datas() {
  char data_inicio[10], data_fim[10];
  printf("> Digite a data de início (dd-mm-yyyy): ");
  scanf("%s", data_inicio);
  printf("> Digite a data de fim (dd-mm-yyyy): ");
  scanf("%s", data_fim);
  printf("1");
  FILE *arquivo_aberto = fopen("arquivo_emprestimos.bin", "rb");
  if (arquivo_aberto == NULL){
    arquivo_aberto = fopen("arquivo_emprestimos.bin", "wb+");
    fclose(arquivo_aberto);
    arquivo_aberto = fopen("arquivo_emprestimos.bin", "rb");
  }       
  emprestimo lend;
  int tamanho=0, novo_tamanho;

  while (fread(&lend, sizeof(emprestimo),1,arquivo_aberto) == 1){
    tamanho++;
  }

  fseek(arquivo_aberto,0,SEEK_SET);
  emprestimo *array = malloc(tamanho* sizeof(emprestimo));
  if (array == NULL)
    printf("X Erro de alocação de memória.");

  int lidos = fread(array, sizeof(emprestimo),tamanho, arquivo_aberto);
  fclose(arquivo_aberto);

  time_t inicio = converter_data(data_inicio);
  time_t fim = converter_data(data_fim);
  printf("Inicio: %ld\n", inicio);
  printf("Fim: %ld\n", fim);

  FILE* arquivoTexto = fopen("emprestimos_relatorio.txt", "w");

  if (arquivoTexto == NULL) {
    perror("X Erro ao criar ou abrir o arquivo de relatório de usuários");
    exit(EXIT_FAILURE);
    return;
  }

  fprintf(arquivoTexto, "===== Empréstimos entre %s e %s =====\n", data_inicio, data_fim);
  
  printf("Empréstimos entre %s e %s:\n", data_inicio, data_fim);
  for(int i = 0; i < tamanho; i++) {
    time_t retirada = converter_data(array[i].data_retirada);
    time_t devolucao = converter_data(array[i].data_devolucao);
      if(difftime(retirada, inicio) >= 0 && difftime(devolucao, fim) <= 0) {
          char data_de_retirada[11];
          char data_de_devolucao[11];
        printf("\n---------------------------------\n");
        printf("CPF: %s\n", array[i].cpf);
        printf("ISBN: %s\n", array[i].ISBN);
        printf("Data de retirada: %s\n", array[i].data_retirada);
        printf("Data de devolução: %s\n", array[i].data_devolucao);
        printf("Multa: %f\n", array[i].ValorMultaDiaria);
        printf("\n---------------------------------\n");

        fprintf(arquivoTexto, "\n---------------------------------\n");
        fprintf(arquivoTexto, "CPF: %s\n", array[i].cpf);
        fprintf(arquivoTexto, "ISBN: %s\n", array[i].ISBN);
        fprintf(arquivoTexto, "Data de retirada: %s\n", array[i].data_retirada);
        fprintf(arquivoTexto, "Data de devolução: %s\n", array[i].data_devolucao);
        fprintf(arquivoTexto, "Multa: %f\n", array[i].ValorMultaDiaria);
        fprintf(arquivoTexto, "\n---------------------------------\n");
      }
  }
  fclose(arquivoTexto); // Fecha o arquivo
}

// Menus

int submenu_users() {
  int option;
  FILE *arquivo_aberto = fopen("usuarios.bin", "rb");
  if (arquivo_aberto == NULL) {
    arquivo_aberto = fopen("usuarios.bin", "wb+");
    fclose(arquivo_aberto);
    arquivo_aberto = fopen("usuarios.bin", "rb");
  }

  usuario user;
  int tamanho = 0;

  while (fread(&user, sizeof(usuario), 1, arquivo_aberto) == 1) {
    tamanho++;
  }

  fseek(arquivo_aberto, 0, SEEK_SET);
  usuario *array = malloc(tamanho * sizeof(usuario));
  if (array == NULL)
    printf("X Erro de alocação de memória.");

  int lidos = fread(array, sizeof(usuario), tamanho, arquivo_aberto);
  
  fclose(arquivo_aberto);

  do {
    printf("\n╔═══════════════════════════════════╗");
    printf("\n║     Submenu     |     Usuários    ║");
    printf("\n╠═══════════════════════════════════╣");
    printf("\n║ 1. Listar todos os usuários       ║");
    printf("\n║ 2. Procurar um usuário            ║");
    printf("\n║ 3. Incluir um usuário             ║");
    printf("\n║ 4. Alterar um usuário             ║");
    printf("\n║ 5. Excluir um usuário             ║");
    printf("\n║ 6. Voltar                         ║");
    printf("\n╚═══════════════════════════════════╝");
    printf("\n> Escolha das opções acima: ");
    scanf("%d", &option);
  
    char nome_arquivo[] = "usuarios.bin";
    char cpf[12];
    switch (option) {
    case 1:
      listar_todos(array, tamanho);
      break;
    case 2:
      printf("\n> Digite o CPF do usuário que deseja buscar: ");
      scanf("%11s", cpf);
      procurar_usuario(array, tamanho, cpf);
      break;
    case 3:
      gravar_usuario(&array, &tamanho);
      printf("\n> Usuário gravado com sucesso!\n");
      gravar_arquivo("usuarios.bin", array, tamanho);
      break;
    case 4:
      printf("\n> Digite o CPF do usuário que deseja alterar: ");
      scanf("%11s", cpf);
      alterar_usuario(array, tamanho, cpf);
      gravar_arquivo("usuarios.bin", array, tamanho);
      break;
    case 5:
      printf("\n> Digite o CPF do usuário que deseja excluir: ");
      scanf("%11s", cpf);
      array = excluir_usuario(array, &tamanho, cpf);
      gravar_arquivo("usuarios.bin", array, tamanho);
      break;
    case 6:
      printf("> Retornando...\n");
      break;
    default:
      printf("X Opção inválida. Tente novamente.\n");
    }
  } while (option != 6);
}

void submenu_livros() { // Pronta
  int option;
  FILE *arquivo = fopen("livros.bin", "rb");
  if (arquivo == NULL){
    arquivo = fopen("livros.bin", "wb+");
    fclose(arquivo);
    arquivo = fopen("livros.bin", "rb");
  }       
  livro book;
  int tamanho = 0;

  while (fread(&book, sizeof(livro), 1, arquivo) == 1){
    tamanho++;
  }

  fseek(arquivo, 0, SEEK_SET);
  livro *array = malloc(tamanho * sizeof(livro));
  
  if (array == NULL) {
    perror("X Erro de alocação de memória");
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }

  int lidos = fread(array, sizeof(livro), tamanho, arquivo);

  if (lidos != tamanho) {
    perror("X Erro na leitura do arquivo de livros");
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }
  
  fclose(arquivo);
  
  do {
    printf("\n╔═══════════════════════════════════╗");
    printf("\n║     Submenu     |      Livros     ║");
    printf("\n╠═══════════════════════════════════╣");
    printf("\n║ 1. Listar todos os livros         ║");
    printf("\n║ 2. Procurar um livro              ║");
    printf("\n║ 3. Incluir um livro               ║");
    printf("\n║ 4. Alterar um livro               ║");
    printf("\n║ 5. Excluir um livro               ║");
    printf("\n║ 6. Voltar                         ║");
    printf("\n╚═══════════════════════════════════╝");
    printf("\n> Escolha das opções acima: ");
    scanf("%d", &option);
    limpar_buffer();
    switch (option) {
    case 1:
      listar_livros(array, tamanho);
      break;
    case 2:
      procurar_livro(array, tamanho);
      break;
    case 3:
      incluir_livro(&array, &tamanho);
      break;
    case 4:
      alterar_livro(&array, &tamanho);
      break;
    case 5:
      excluir_livro(&array, &tamanho);
      break;
    case 6:
      printf("> Retornando...\n");
      break;
    default:
      printf("X Opção inválida...\n");
    }
  } while (option != 6);
  gravar_livro(array, tamanho);
}

void submenu_emprestimos() {
  int option;
  FILE *arquivo_aberto = fopen("arquivo_emprestimos.bin", "rb");
  if (arquivo_aberto == NULL){
    arquivo_aberto = fopen("arquivo_emprestimos.bin", "wb+");
    fclose(arquivo_aberto);
    arquivo_aberto = fopen("arquivo_emprestimos.bin", "rb");
  }       
  emprestimo lend;
  int tamanho=0, novo_tamanho;

  while (fread(&lend, sizeof(emprestimo),1,arquivo_aberto) == 1){
    tamanho++;
  }

  fseek(arquivo_aberto,0,SEEK_SET);
  emprestimo *array = malloc(tamanho* sizeof(emprestimo));
  if (array == NULL)
    printf("X Erro de alocação de memória.");

  int lidos = fread(array, sizeof(emprestimo),tamanho, arquivo_aberto);
  fclose(arquivo_aberto);

  do {
    printf("\n╔═══════════════════════════════════╗");
    printf("\n║     Submenu     |   Empréstimos   ║");
    printf("\n╠═══════════════════════════════════╣");
    printf("\n║ 1. Listar todos os empréstimos    ║");
    printf("\n║ 2. Procurar um empréstimo         ║");
    printf("\n║ 3. Incluir um empréstimo          ║");
    printf("\n║ 4. Alterar um empréstimo          ║");
    printf("\n║ 5. Excluir um empréstimo          ║");
    printf("\n║ 6. Voltar                         ║");
    printf("\n╚═══════════════════════════════════╝");
    printf("\n> Escolha das opções acima: ");
    scanf("%d", &option);
    int procura;
    char cpf[12], isbn[14];
  
    switch (option) {
    case 1:
      listar_emprestimos(array,tamanho);
      break;
    case 2:
      printf("> Digite o cpf referente ao empréstimo procurado: ");
      scanf("%s", &cpf);
      printf("> Digite o isbn referente ao empréstimo procurado: ");
      scanf("%s", &isbn);
      procurar_emprestimo(array, tamanho, cpf, isbn);
      break;
    case 3:
      printf("> Digite o CPF do usuário: ");
      scanf("%s", &lend.cpf);
      printf("> Digite o ISBN do livro: ");
      scanf("%s", &lend.ISBN);
      printf("> Digite a data de retirada do livro: ");
      scanf("%s", &lend.data_retirada);
      printf("> Digite a data de devolução do livro: ");
      scanf("%s", &lend.data_devolucao);
      printf("> Digite o valor da multa: ");
      scanf("%f", &lend.ValorMultaDiaria);
      verificarISBN_emprestimo("arquivo_emprestimos.bin", isbn);
      int existe = emprestimo_existe_data(array, lend.cpf,lend.ISBN,lend.data_retirada,lend.data_devolucao, tamanho);
      if(existe==-1){
      adicionar_emprestimo(&array, &tamanho, lend);
      gravar_emprestimo("arquivo_emprestimos.bin", array, tamanho);}
      else
        printf("X Emprestimo similar/igual já cadastrado");
      break;
    case 4:
      printf("> Digite o cpf referente ao empréstimo procurado: ");
      scanf("%s", &cpf);
      printf("> Digite o isbn referente ao empréstimo procurado: ");
      scanf("%s", &isbn);
      alterar_emprestimo(array, cpf, isbn,tamanho);
      gravar_emprestimo("arquivo_emprestimos.bin", array, tamanho);
      break;
    case 5:
      printf("> Digite o cpf referente ao empréstimo procurado: ");
      scanf("%s", &cpf);
      printf("> Digite o isbn referente ao empréstimo procurado: ");
      scanf("%s", &isbn);
      array = excluir_emprestimo(array, cpf, isbn,tamanho);
      if (array==NULL) {
        printf("\n> Saindo...");
      } else {
          tamanho = tamanho-1;
          listar_emprestimos(array,tamanho);
          gravar_emprestimo("arquivo_emprestimos.bin", array, tamanho);
      }
      break;
    case 6:
      printf("> Retornando...\n");
      break;
    default:
      printf("X Opção inválida...\n");
    }
  } while (option != 6);
  free(array);
}

void submenu_relatorios() { 
  int option;
  do {
    printf("\n╔═════════════════════════════════════════════════════════════╗");
    printf("\n║           Submenu          |           Relatórios           ║");
    printf("\n╠═════════════════════════════════════════════════════════════╣");
    printf("\n║ 1. Mostrar dados de usuários acima de uma determinada idade ║");
    printf("\n║ 2. Mostrar dados de livros com múltiplos autores            ║");
    printf("\n║ 3. Mostrar dados de empréstimos entre determinadas datas    ║"); 
    printf("\n║ 4. Voltar                                                   ║");
    printf("\n╚═════════════════════════════════════════════════════════════╝");
    printf("\n> Escolha das opções acima: ");
    scanf("%d", &option);
    limpar_buffer();
    switch (option) {
    case 1:
      printf("\n> Digite a idade mínima dos usuários a serem listados: ");
      int idade_minima;
      scanf("%d", &idade_minima);
      listar_usuarios_mais_velhos(idade_minima);
      break;
    case 2:
      livros_autores();
      break;
    case 3:
      emprestimos_datas();
      break;
    case 4:
      printf("> Retornando...\n");
      break;
    default:
      printf("X Opção inválida...\n");
    }
  } while (option != 4);
}

int menu() {
  int option;
  printf("\n╔════════════════════════════╗");
  printf("\n║       Menu de Opções       ║");
  printf("\n╠════════════════════════════╣");
  printf("\n║ 1. Submenu de Usuários     ║");
  printf("\n║ 2. Submenu de Livros       ║");
  printf("\n║ 3. Submenu de Empréstimos  ║");
  printf("\n║ 4. Submenu de Relatórios   ║");
  printf("\n║ 5. Sair                    ║");
  printf("\n╚════════════════════════════╝");
  printf("\n> Escolha das opções acima: ");
  scanf("%d", &option);
  limpar_buffer();
  return option;
}

// Funções principais de navegação

int main() {
  excluirTodosArquivos();
  int escolha;
  do {
    escolha = menu();
    switch (escolha) {
    case 1:
      submenu_users();
      break;
    case 2:
      submenu_livros();
      break;
    case 3:
      submenu_emprestimos();
      break;
    case 4:
      submenu_relatorios();
      break;
    case 5:
      printf("> Encerrando programa...\n");
      break;
    default:
      printf("X Opção inválida. Tente novamente.\n");
    }
  } while (escolha != 5);
}