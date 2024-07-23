#include <stdio.h> // entrada e saida de dados
#include <stdlib.h> // utilização do system
#include <locale.h> // junto com setlocale() para funcionar ç e acentuação
#include <string.h> // manipulação de strings em arrays

#define LOGIN_LENGHT 50 // definindo constantes para tamanhos de dados
#define SENHA_LENGHT 50
#define NOME_LENGHT 50
#define EMAIL_LENGHT 50

// declarando a struct de acesso do adm
typedef struct{
    char acesso[15]; // vetor de acesso da struct pessoa
    char senha[15]; // vetor senha da struct pessoa
} pessoa; pessoa p[1];  // diminuindo o nome da struct para "p" e o "[1]" é o máximo de pessoas com login e senha

// declarando as funções
int menu(void);
void criarUsuario(void);
void listarUsuarios(void);
void editarUsuario(void);
void removerUsuario(void);
void salvarUsuarioNoArquivo(void);
void carregarUsuariosDoArquivo(void);

int main(){
    // ajustando para aceitar acentos e ç
    setlocale(LC_ALL, "Portuguese");

    char acesso[15]; // responsável por armazenar o acesso inserido pelo usuário
    char senha[15]; // responsável por armazenar a senha inserida pelo usuário

    strcpy(p[0].acesso, "Administrador"); // Definindo o acesso "Administrador" na struct copiando o valor para o atributo
    strcpy(p[0].senha, "123456"); // Definindo a senha "123456"  na struct copiando o valor para o atributo

    printf("\n===================================================================\n");
    printf("\n                        ACESSO ADMINISTRADOR                           \n");
    printf("\n                     CRUD Embarcado de Usuários                         \n");
    printf("\n===================================================================\n");

    printf("\nLogin: ");
    scanf("%s", acesso); // armazenando os dados inseridos pelo usuário dentro da variavel acesso declarada

    printf("\nSenha: ");
    scanf("%s", senha); // armazenando os dados inseridos pelo usuário dentro da variavel senha declarada

    if ((strcmp(acesso,p[0].acesso)==0) && (strcmp(senha,p[0].senha)==0)){ // A função strcmp é responsável por comparar string com string e assim verificarmos o acesso
        system("cls"); // para limpar a tela do console
        printf("Usuário logado\n"); // se o que foi inserido pelo adm bater com o que foi estabelecido com os valores que foram atribuídos, será logado
        menu();
    }else{
        system("cls");
        printf("Login e/ou senha incorretos"); // senão, login ou senha incorreta.
        main();
    }
    return 0;
}

// declarando a struct do usuário
typedef struct {
	int id;
	char login[LOGIN_LENGHT];
	char password[SENHA_LENGHT];
	char nome[NOME_LENGHT];
	char email[EMAIL_LENGHT];
} Usuario;

int menu(){
    setlocale(LC_ALL, "Portuguese"); // ajustando para aceitar acentos e ç

    int select; // declaração da variavel de seleção de função
    
    carregarUsuariosDoArquivo(); // chamada da função de leitura do arquivo txt

	// menu principal com do while para executar antes de verificar a condição
	do{
	    printf("\n===================================================================\n");
	    printf("\n                                MENU                           \n");
	    printf("\n===================================================================\n");
	    printf("1 - Criar um novo usuário\n");
	    printf("2 - Listar todos os usuários criados\n");
	    printf("3 - Editar um usuário\n");
	    printf("4 - Remover um usuário\n");
	    printf("0 - Finalizar o sistema\n");
	
		// entrada do número da função
	    printf("Digite o número da opção desejada: ");
	    scanf("%d",&select); //pegando o valor digitado pelo usuário e atribuindo para o endereço da variavel select
	
	    // switch case trazendo cada função conforme opção selecionada
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
	
	    // se o usuário não inserir um número entre 0 e 4, irá aparecer essa mensagem com o retorno do menu 
	    if(select < 0 || select > 4){
	    	system("cls");
	        printf("O número da opção é inválido!\nTente novamente. \n");
	        return menu();
	    }
	
	// enquanto for diferente de 0, executa o do
	}while (select != 0);

}

Usuario usuarios[100]; // atribuindo a struct Usuario para a variavel usuarios para ter acesso aos atributos e definindo seu tamanho máximo
int contador_usuario = 0; // variavel para contar o número de usuários criados que obviamente se inicia com 0

// função de criar usuário utilizando if else com a condição de o contador do usuário ser menor que 100 para executar
void criarUsuario() {
    if (contador_usuario < 100) {
        Usuario novoUsuario; // atribuindo a struct Usuario para a variavel novoUsuario, assim terá acesso aos atributos
        novoUsuario.id = contador_usuario + 1; // novoUsuario referenciando o ID da struct atribuindo valor para ele que seria o contador + 1
        printf("\n===================================================================\n");
	    printf("\n                        CRIAR NOVO USUÁRIO                           \n");
	    printf("\n===================================================================\n");
        printf("Insira o login do usuário: "); // atribuindo valor para cada atributo dentro da struct do novo usuário
        scanf("%s", novoUsuario.login); 
        printf("Insira a senha do usuário: ");
        scanf("%s", novoUsuario.password); 
        printf("Insira o nome do usuário utilizando underline ao invés de espaço: ");
        scanf("%s", novoUsuario.nome); 
        printf("Insira o email do usuário: ");
        scanf("%s", novoUsuario.email); 

        usuarios[contador_usuario++] = novoUsuario; // a variavel usuarios incrementando + 1 no contador como parâmetro e sendo atribuída a novoUsuario pois foi criado mais um
        salvarUsuarioNoArquivo(); // chamada da função salvarUsuarioNoArquivo para salvar o novo usuário criado dentro do arquivo txt
        system("cls");
        printf("Usuário criado com sucesso!\n"); // mensagem de confirmação da operação
    
	// se tiver atingido o limite(100) de usuários, mostra a mensagem abaixo e retorna ao menu    
    } else {
    	system("cls");
        printf("Impossível continuar!\nLimite de usuários criados foi atingido!\nRemova algum usuário para continuar."); // mensagem de erro ao tentar inserir usuário
    }
}

// função de listar todos os usuários criados até o momento
void listarUsuarios() {
	// se a contador de usuários for igual a 0, não possui nenhum usuário criado até então
    if (contador_usuario == 0) {
    	system("cls");
        printf("Nenhum usuário criado até o momento.\n"); // mensagem de erro ao tentar executar a listagem de usuários
    }

    // para trazer todos os usuários inseridos na sequência, i iniciando 0, condição de i ser menor que o contador e em seguida faz o incremento se repetindo até o ultimo usuário
	for (int i = 0; i < contador_usuario; i++) {
        printf("ID: %d\n", usuarios[i].id);          // imprimindo na tela cada informação através da variavel usuarios
        printf("Login: %s\n", usuarios[i].login);    // que tem como parâmetro i que possui uma contagem estabelecida nesse for
        printf("Senha: %s\n", usuarios[i].password); // e em seguida trazendo o valores referentes aos atributos dentro da struct
        printf("Nome: %s\n", usuarios[i].nome);      
        printf("Email: %s\n", usuarios[i].email);
        printf("\n");
    }
}

// função de editar um usuário selecionando seu ID conforme a sequência de usuários inseridos
void editarUsuario() {
    int id;
    printf("\n===================================================================\n");
	printf("\n                          EDITAR USUÁRIO                           \n");
	printf("\n===================================================================\n");
    printf("Insira o ID do usuário que deseja editar: ");
    scanf("%d", &id);

    // estrutura de condição if else verificando se id for maior que 0 e menor ou igual ao contador para executar
	if (id > 0 && id <= contador_usuario) {
        Usuario *usuario = &usuarios[id - 1]; // declara um ponteiro para a variavel Usuario atribuído para o array usuarios tendo como parâmetro id - 1
        printf("Insira o novo login: ");      // que calcula a posição correta onde o array se inicia em 0 e assim encontre o endereço do usuário que se inicia com 1
        scanf("%s", usuario->login);         
        printf("Insira a nova senha: "); 	  
        scanf("%s", &usuario->password);      // lê uma string de entrada do usuário e armazena no campo name da estrutura Usuario apontada pelo ponteiro usuario
        printf("Insira o novo nome: ");
        scanf("%s", usuario->nome);
        printf("Insira o novo email: ");
        scanf("%s", usuario->email);

        salvarUsuarioNoArquivo();
        system("cls");
        printf("Usuário atualizado com sucesso!\n"); // mensagem de confirmação da operação
    } else {
        printf("ID do usuário não encontrado!\n"); // mensagem de erro na busca do usuário
    }
}

// função de remover o usuário desejado através do seu ID
void removerUsuario() {
    int id;
    printf("\n===================================================================\n");
	printf("\n                         REMOVER USUÁRIO                           \n");
	printf("\n===================================================================\n");
    printf("Insira o ID do usuário que deseja remover: ");
    scanf("%d", &id);

    // estrutura de condição if else verificando se id for maior que 0 e menor ou igual ao contador para executar
	if (id > 0 && id <= contador_usuario) {
        // laço começa no id - 1 pois o array começa em 0 ao contrário do id, assim encontra a posição correta; continua o laço enquanto i for menor que contador e depois incrementa 1
		for (int i = id - 1; i < contador_usuario - 1; i++) {
            usuarios[i] = usuarios[i + 1]; // o elemento i é substituído pelo elemento i + 1 deslocando todos os elementos na sequência para a esquerda, efetuando a remoção
        }                                  
        contador_usuario--;                 
        salvarUsuarioNoArquivo();           
        system("cls");
        printf("Usuário removido com sucesso!\n"); // mensagem de confirmação da operação
    } else {
        printf("ID do usuário não encontrado!\n"); // mensagem de erro na busca do usuário
    }
}

// função de leitura do arquivo usuarios.txt
void carregarUsuariosDoArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "r"); // referenciamos arquivo através do seu ponteiro atribuímos fopen para abrir com o nome do arquivo e a função "r" de leitura(read)
    if (arquivo == NULL) {
        return; // faz o retorno para o menu se o arquivo for vazio
    }

    contador_usuario = 0; //contador se inicia com valor 0
    // laço enquanto ler o arquivo através do endereço da variável usuarios que possui a struct, contador como parâmetro para a posição e referenciando qual atributo dentro da struct
    while (fscanf(arquivo, "%d %s %s %s %s", &usuarios[contador_usuario].id, usuarios[contador_usuario].login, usuarios[contador_usuario].password, 
	usuarios[contador_usuario].nome, usuarios[contador_usuario].email) != EOF) {
        contador_usuario++; // incremento em contador para criar a sequência correta
    }

    fclose(arquivo); // fechando o arquivo após a leitura
}

// função de salvar no arquivo.txt a inserção, atualização ou remoção de dados do usuário
void salvarUsuarioNoArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "w"); // fluxo de arquivo onde "arquivo" é o ponteiro para este fluxo; fopen para abrir o arquivo.txt e editar com write(escrever) "w"
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n"); // se o arquivo estiver vazio, informa um erro na tentativa de abertura e depois retorna para o menu
        return;
    }

	// laço começa no 0 por conta do array, condição de continuar o laço até ser menor que o contador e em seguida fazendo o incremento após iteração
    for (int i = 0; i < contador_usuario; i++) {
        // salvando no arquivo.txt os valores através do fprintf; arquivo é ponteiro para onde os dados são gravados; os dados são específicos do usuário conforme a posição do i 
		fprintf(arquivo, "%d %s %s %s %s\n", usuarios[i].id, usuarios[i].login, usuarios[i].password, usuarios[i].nome, usuarios[i].email);
    }

    fclose(arquivo); // fechando o arquivo após a inserção, atualização ou remoção de dados do usuário
}
