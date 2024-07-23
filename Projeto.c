#include <stdio.h> // entrada e saida de dados
#include <stdlib.h> // utiliza��o do system
#include <locale.h> // junto com setlocale() para funcionar � e acentua��o
#include <string.h> // manipula��o de strings em arrays

#define LOGIN_LENGHT 50 // definindo constantes para tamanhos de dados
#define SENHA_LENGHT 50
#define NOME_LENGHT 50
#define EMAIL_LENGHT 50

// declarando a struct de acesso do adm
typedef struct{
    char acesso[15]; // vetor de acesso da struct pessoa
    char senha[15]; // vetor senha da struct pessoa
} pessoa; pessoa p[1];  // diminuindo o nome da struct para "p" e o "[1]" � o m�ximo de pessoas com login e senha

// declarando as fun��es
int menu(void);
void criarUsuario(void);
void listarUsuarios(void);
void editarUsuario(void);
void removerUsuario(void);
void salvarUsuarioNoArquivo(void);
void carregarUsuariosDoArquivo(void);

int main(){
    // ajustando para aceitar acentos e �
    setlocale(LC_ALL, "Portuguese");

    char acesso[15]; // respons�vel por armazenar o acesso inserido pelo usu�rio
    char senha[15]; // respons�vel por armazenar a senha inserida pelo usu�rio

    strcpy(p[0].acesso, "Administrador"); // Definindo o acesso "Administrador" na struct copiando o valor para o atributo
    strcpy(p[0].senha, "123456"); // Definindo a senha "123456"  na struct copiando o valor para o atributo

    printf("\n===================================================================\n");
    printf("\n                        ACESSO ADMINISTRADOR                           \n");
    printf("\n                     CRUD Embarcado de Usu�rios                         \n");
    printf("\n===================================================================\n");

    printf("\nLogin: ");
    scanf("%s", acesso); // armazenando os dados inseridos pelo usu�rio dentro da variavel acesso declarada

    printf("\nSenha: ");
    scanf("%s", senha); // armazenando os dados inseridos pelo usu�rio dentro da variavel senha declarada

    if ((strcmp(acesso,p[0].acesso)==0) && (strcmp(senha,p[0].senha)==0)){ // A fun��o strcmp � respons�vel por comparar string com string e assim verificarmos o acesso
        system("cls"); // para limpar a tela do console
        printf("Usu�rio logado\n"); // se o que foi inserido pelo adm bater com o que foi estabelecido com os valores que foram atribu�dos, ser� logado
        menu();
    }else{
        system("cls");
        printf("Login e/ou senha incorretos"); // sen�o, login ou senha incorreta.
        main();
    }
    return 0;
}

// declarando a struct do usu�rio
typedef struct {
	int id;
	char login[LOGIN_LENGHT];
	char password[SENHA_LENGHT];
	char nome[NOME_LENGHT];
	char email[EMAIL_LENGHT];
} Usuario;

int menu(){
    setlocale(LC_ALL, "Portuguese"); // ajustando para aceitar acentos e �

    int select; // declara��o da variavel de sele��o de fun��o
    
    carregarUsuariosDoArquivo(); // chamada da fun��o de leitura do arquivo txt

	// menu principal com do while para executar antes de verificar a condi��o
	do{
	    printf("\n===================================================================\n");
	    printf("\n                                MENU                           \n");
	    printf("\n===================================================================\n");
	    printf("1 - Criar um novo usu�rio\n");
	    printf("2 - Listar todos os usu�rios criados\n");
	    printf("3 - Editar um usu�rio\n");
	    printf("4 - Remover um usu�rio\n");
	    printf("0 - Finalizar o sistema\n");
	
		// entrada do n�mero da fun��o
	    printf("Digite o n�mero da op��o desejada: ");
	    scanf("%d",&select); //pegando o valor digitado pelo usu�rio e atribuindo para o endere�o da variavel select
	
	    // switch case trazendo cada fun��o conforme op��o selecionada
		switch (select)
	    {
	    case 1:
	    	system("cls");
	    	criarUsuario();
	        break;
	    case 2:
	    	system("cls");
	    	listarUsuarios();
	        break;
	    case 3:
	    	system("cls");
	    	editarUsuario();
	        break;
	    case 4:
	    	system("cls");
	    	removerUsuario();
	        break;    
	    default:
	        break;
	    }
	
	    // se o usu�rio n�o inserir um n�mero entre 0 e 4, ir� aparecer essa mensagem com o retorno do menu 
	    if(select < 0 || select > 4){
	    	system("cls");
	        printf("O n�mero da op��o � inv�lido!\nTente novamente. \n");
	        return menu();
	    }
	
	// enquanto for diferente de 0, executa o do
	}while (select != 0);

}

Usuario usuarios[100]; // atribuindo a struct Usuario para a variavel usuarios para ter acesso aos atributos e definindo seu tamanho m�ximo
int contador_usuario = 0; // variavel para contar o n�mero de usu�rios criados que obviamente se inicia com 0

// fun��o de criar usu�rio utilizando if else com a condi��o de o contador do usu�rio ser menor que 100 para executar
void criarUsuario() {
    if (contador_usuario < 100) {
        Usuario novoUsuario; // atribuindo a struct Usuario para a variavel novoUsuario, assim ter� acesso aos atributos
        novoUsuario.id = contador_usuario + 1; // novoUsuario referenciando o ID da struct atribuindo valor para ele que seria o contador + 1
        printf("\n===================================================================\n");
	    printf("\n                        CRIAR NOVO USU�RIO                           \n");
	    printf("\n===================================================================\n");
        printf("Insira o login do usu�rio: "); // atribuindo valor para cada atributo dentro da struct do novo usu�rio
        scanf("%s", novoUsuario.login); 
        printf("Insira a senha do usu�rio: ");
        scanf("%s", novoUsuario.password); 
        printf("Insira o nome do usu�rio utilizando underline ao inv�s de espa�o: ");
        scanf("%s", novoUsuario.nome); 
        printf("Insira o email do usu�rio: ");
        scanf("%s", novoUsuario.email); 

        usuarios[contador_usuario++] = novoUsuario; // a variavel usuarios incrementando + 1 no contador como par�metro e sendo atribu�da a novoUsuario pois foi criado mais um
        salvarUsuarioNoArquivo(); // chamada da fun��o salvarUsuarioNoArquivo para salvar o novo usu�rio criado dentro do arquivo txt
        system("cls");
        printf("Usu�rio criado com sucesso!\n"); // mensagem de confirma��o da opera��o
    
	// se tiver atingido o limite(100) de usu�rios, mostra a mensagem abaixo e retorna ao menu    
    } else {
    	system("cls");
        printf("Imposs�vel continuar!\nLimite de usu�rios criados foi atingido!\nRemova algum usu�rio para continuar."); // mensagem de erro ao tentar inserir usu�rio
    }
}

// fun��o de listar todos os usu�rios criados at� o momento
void listarUsuarios() {
	// se a contador de usu�rios for igual a 0, n�o possui nenhum usu�rio criado at� ent�o
    if (contador_usuario == 0) {
    	system("cls");
        printf("Nenhum usu�rio criado at� o momento.\n"); // mensagem de erro ao tentar executar a listagem de usu�rios
    }

    // para trazer todos os usu�rios inseridos na sequ�ncia, i iniciando 0, condi��o de i ser menor que o contador e em seguida faz o incremento se repetindo at� o ultimo usu�rio
	for (int i = 0; i < contador_usuario; i++) {
        printf("ID: %d\n", usuarios[i].id);          // imprimindo na tela cada informa��o atrav�s da variavel usuarios
        printf("Login: %s\n", usuarios[i].login);    // que tem como par�metro i que possui uma contagem estabelecida nesse for
        printf("Senha: %s\n", usuarios[i].password); // e em seguida trazendo o valores referentes aos atributos dentro da struct
        printf("Nome: %s\n", usuarios[i].nome);      
        printf("Email: %s\n", usuarios[i].email);
        printf("\n");
    }
}

// fun��o de editar um usu�rio selecionando seu ID conforme a sequ�ncia de usu�rios inseridos
void editarUsuario() {
    int id;
    printf("\n===================================================================\n");
	printf("\n                          EDITAR USU�RIO                           \n");
	printf("\n===================================================================\n");
    printf("Insira o ID do usu�rio que deseja editar: ");
    scanf("%d", &id);

    // estrutura de condi��o if else verificando se id for maior que 0 e menor ou igual ao contador para executar
	if (id > 0 && id <= contador_usuario) {
        Usuario *usuario = &usuarios[id - 1]; // declara um ponteiro para a variavel Usuario atribu�do para o array usuarios tendo como par�metro id - 1
        printf("Insira o novo login: ");      // que calcula a posi��o correta onde o array se inicia em 0 e assim encontre o endere�o do usu�rio que se inicia com 1
        scanf("%s", usuario->login);         
        printf("Insira a nova senha: "); 	  
        scanf("%s", &usuario->password);      // l� uma string de entrada do usu�rio e armazena no campo name da estrutura Usuario apontada pelo ponteiro usuario
        printf("Insira o novo nome: ");
        scanf("%s", usuario->nome);
        printf("Insira o novo email: ");
        scanf("%s", usuario->email);

        salvarUsuarioNoArquivo();
        system("cls");
        printf("Usu�rio atualizado com sucesso!\n"); // mensagem de confirma��o da opera��o
    } else {
        printf("ID do usu�rio n�o encontrado!\n"); // mensagem de erro na busca do usu�rio
    }
}

// fun��o de remover o usu�rio desejado atrav�s do seu ID
void removerUsuario() {
    int id;
    printf("\n===================================================================\n");
	printf("\n                         REMOVER USU�RIO                           \n");
	printf("\n===================================================================\n");
    printf("Insira o ID do usu�rio que deseja remover: ");
    scanf("%d", &id);

    // estrutura de condi��o if else verificando se id for maior que 0 e menor ou igual ao contador para executar
	if (id > 0 && id <= contador_usuario) {
        // la�o come�a no id - 1 pois o array come�a em 0 ao contr�rio do id, assim encontra a posi��o correta; continua o la�o enquanto i for menor que contador e depois incrementa 1
		for (int i = id - 1; i < contador_usuario - 1; i++) {
            usuarios[i] = usuarios[i + 1]; // o elemento i � substitu�do pelo elemento i + 1 deslocando todos os elementos na sequ�ncia para a esquerda, efetuando a remo��o
        }                                  
        contador_usuario--;                 
        salvarUsuarioNoArquivo();           
        system("cls");
        printf("Usu�rio removido com sucesso!\n"); // mensagem de confirma��o da opera��o
    } else {
        printf("ID do usu�rio n�o encontrado!\n"); // mensagem de erro na busca do usu�rio
    }
}

// fun��o de leitura do arquivo usuarios.txt
void carregarUsuariosDoArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "r"); // referenciamos arquivo atrav�s do seu ponteiro atribu�mos fopen para abrir com o nome do arquivo e a fun��o "r" de leitura(read)
    if (arquivo == NULL) {
        return; // faz o retorno para o menu se o arquivo for vazio
    }

    contador_usuario = 0; //contador se inicia com valor 0
    // la�o enquanto ler o arquivo atrav�s do endere�o da vari�vel usuarios que possui a struct, contador como par�metro para a posi��o e referenciando qual atributo dentro da struct
    while (fscanf(arquivo, "%d %s %s %s %s", &usuarios[contador_usuario].id, usuarios[contador_usuario].login, usuarios[contador_usuario].password, 
	usuarios[contador_usuario].nome, usuarios[contador_usuario].email) != EOF) {
        contador_usuario++; // incremento em contador para criar a sequ�ncia correta
    }

    fclose(arquivo); // fechando o arquivo ap�s a leitura
}

// fun��o de salvar no arquivo.txt a inser��o, atualiza��o ou remo��o de dados do usu�rio
void salvarUsuarioNoArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "w"); // fluxo de arquivo onde "arquivo" � o ponteiro para este fluxo; fopen para abrir o arquivo.txt e editar com write(escrever) "w"
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n"); // se o arquivo estiver vazio, informa um erro na tentativa de abertura e depois retorna para o menu
        return;
    }

	// la�o come�a no 0 por conta do array, condi��o de continuar o la�o at� ser menor que o contador e em seguida fazendo o incremento ap�s itera��o
    for (int i = 0; i < contador_usuario; i++) {
        // salvando no arquivo.txt os valores atrav�s do fprintf; arquivo � ponteiro para onde os dados s�o gravados; os dados s�o espec�ficos do usu�rio conforme a posi��o do i 
		fprintf(arquivo, "%d %s %s %s %s\n", usuarios[i].id, usuarios[i].login, usuarios[i].password, usuarios[i].nome, usuarios[i].email);
    }

    fclose(arquivo); // fechando o arquivo ap�s a inser��o, atualiza��o ou remo��o de dados do usu�rio
}
