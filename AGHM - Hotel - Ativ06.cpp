//AGHM - Hotel - Ativ06
//Ana Clara Boaventura Dattoli
//Guilherme Almeida Coutinho
//Heitor de Sousa Cavalcanti
//Marcelo Liao
//18/06/2025

#include <iostream>


#define NIVEL 20    // Número de andares
#define SALA 14     // Número de quartos por andar


typedef struct 
	{
    char residencia[40];
    char municipio[20];
    char uf[3];
    char cep[10];
	} domicilio;

typedef struct 
	{
    char nome[40];
    char cpf[15];
    char celular[20];
    char email[40];
    int Valido;
    domicilio endereco;
	} dadosHospede;

dadosHospede hospedes[NIVEL][SALA];   // Matriz para armazenar as reservas válidas e os check-ins válidas

// Protótipos
void ftabela(char hotel[NIVEL][SALA]);   // Função que exibe o mapa de ocupação do hotel
void fclear();                           // Função que limpa o buffer do teclado
int fverificar(char a[], char b[]);      // Função que verificar os dados da reserva com os do check-in
    
dadosHospede cadastrarHospede(int andar, int quarto);     // Cadastro dos hospedes
void mostrarHospede(char hotel[NIVEL][SALA], dadosHospede h, int andar, int quarto);   // Função que mostra o status/dados do apartamento

main()
{	
	char hotel[NIVEL][SALA];   // Matriz que representará o status dos quartos
	int linha, coluna, andar, quarto;
	int opMenu, op1, op2, conf1, conf2;
	
	// Inicializa todos os apartamentos como disponíveis ('.')
	for(linha = 0; linha < NIVEL; linha++) 	
		for(coluna = 0; coluna < SALA; coluna++) 
			hotel[linha][coluna] = '.';	

	do 
		{
		ftabela(hotel);
		printf("\n");
    	printf("                  - HOTEL AGHM -                 \n");
   		printf("+===============================================+\n");
    	printf("|                 MENU DE OPCOES                |\n");
    	printf("+-----------------------------------------------+\n");
    	printf("| 1 - Check-in                                  |\n");
    	printf("| 2 - Check-out                                 |\n");
    	printf("| 3 - Reserva                                   |\n");
    	printf("| 4 - Cancelamento de Reserva                   |\n");
    	printf("| 5 - Status do Quarto                          |\n");
    	printf("| 6 - Taxas de Ocupacao, Reserva e Lotacao      |\n");
    	printf("| 7 - Mapa Geral                                |\n");
    	printf("| 0 - Sair                                      |\n");		
    	printf("+===============================================+\n");
    	printf("Digite a opcao desejada: ");
		scanf("%d", &opMenu);
		
		fclear();
			
		printf("\n\n");
		
		if (opMenu == 0)
			{
			system("cls");	
			printf("Encerrando o sistema...\nObrigado por utilizar o sistema do Hotel AGHM.\n");
			break;
			}
			
		else if (opMenu >= 1 && opMenu <= 5)
			{
    		int entradaValida = 0;

    		// Repete até a entrada ser válida ou o usuário digitar 0 0
    		while (entradaValida == 0)
    			{
        		printf("Digite o ANDAR (1 a 20) e o QUARTO (1 a 14), separados por espaco (0 0 para voltar): ");
        		scanf("%d %d", &andar, &quarto);
				printf("\n");
				
        		if (andar == 0 && quarto == 0)
            		{
            		system("cls");          // Limpa a tela          
            		entradaValida = -1;     // Marca para voltar ao menu
            		break;
        			}
				
				int erro = 0;
        		if (andar < 1 || andar > NIVEL)
        			{
            		printf("> Andar invalido.\n");
            		erro = 1;
        			}

        		if (quarto < 1 || quarto > SALA)
        			{
            		printf("> Quarto invalido.\n");
            		erro = 1;
        			}
        		
        		if (erro == 1)
        			{
        			printf("\nPor favor, tente novamente.\n\n\n");
            		continue;
					}
				
        		entradaValida = 1;  // Entrada válida
    			}
    			
    			// Volta ao menu principal
    			if (entradaValida == -1)
        			continue;    

            	// Ajuste para os índices da matriz (começam em 0)
            	andar--; 
		    	quarto--;
            	printf("\n");
        	}
        
        else if (opMenu < 0 || opMenu > 7)
        	{
        	system("cls");
        	continue;
			}
        	
        	
        else if (opMenu == 7)
        	{
        	system("cls");
        	continue;
			}
			
		else if (opMenu == 6)
			{
			// Calcula as taxas de reserva, ocupação e lotação
			float R = 0, O = 0;
			
			for(linha = 0; linha < NIVEL; linha++) 
				{
				for(coluna = 0; coluna < SALA; coluna++)
					{
					if (hotel[linha][coluna] == 'r')
						R = R + 1;
					else if (hotel[linha][coluna] == 'o')
						O = O + 1;
					}
				}
				
			// Cálculo da Taxa
			R = 100.0 * R / (NIVEL * SALA);
			O = 100.0 * O / (NIVEL * SALA);
			
			system("cls");
			printf("| Taxa de Reservas: %.2f%%\n", R);
			printf("| Taxa de Ocupacao: %.2f%%\n", O);
			printf("| Lotacao Total: %.2f%%\n", R+O);
			}
        
		
		// Opções
		switch (opMenu)
			{
			case 1:  // Check-in
				if (hotel[andar][quarto] == '.') 
					{
					system("cls");
                    printf("Para prosseguir com o Check-In, forneca os seguintes dados:\n\n");
					dadosHospede h = cadastrarHospede(andar, quarto);
					if (h.Valido != 0) 
						{
						hospedes[andar][quarto] = h;
    					hotel[andar][quarto] = 'o';  // Marca como ocupado
    					system("cls");
    					printf("+====================================+\n");
    					printf("    CHECK-IN REALIZADO COM SUCESSO    \n");
    					printf("+====================================+\n");
    					printf("        ANDAR %d || QUARTO %d         \n\n", andar + 1, quarto + 1);
						}
					}
				else if (hotel[andar][quarto] == 'r')
					{
					do
						{
						system("cls");
                   		printf("Este quarto ja tem uma RESERVA. O que deseja fazer: ");
                   		printf("\n\n1 - Check-In\n0 - Sair\n");
						scanf("%d", &op1);
						} while (op1 != 0 && op1 != 1);
					if (op1 == 1)
						{
						system("cls");   
						char cpfconfirmacao [15];
						dadosHospede h = hospedes[andar][quarto];
						
						printf("Para prosseguir com o Check-In, forneca o CPF do hospede: ");
						scanf("%s", cpfconfirmacao);
						if ((h.Valido && fverificar(h.cpf, cpfconfirmacao)) != 0)  // Verifica se a reserva é válida e o CPF confere
							{
    						hospedes[andar][quarto] = h; // Copia os dados da reserva para o check-in
    						hotel[andar][quarto] = 'o';  // Marca como ocupado
    						system("cls");
    						printf("+====================================+\n");
    						printf("    CHECK-IN REALIZADO COM SUCESSO    \n");
    						printf("+====================================+\n");
    						printf("        ANDAR %d || QUARTO %d         \n\n", andar + 1, quarto + 1);
    						}
    					else
							{
							system("cls");
							printf("+===========================================================================================+\n");
    						printf("    O CPF inserido NAO CORRESPONDE ao fornecido no ato da Reserva. CHECK-IN NAO PERMITIDO    \n");
    						printf("+===========================================================================================+\n");
    						printf("                                 ANDAR %d || QUARTO %d                                       \n\n", andar + 1, quarto + 1);
							}
						break;	
						}
                	else 
                		system("cls");
						continue;
					}
				else if (hotel[andar][quarto] == 'o') 
					{
					system("cls");
					printf("+======================================================+\n");
					printf("    Este quarto esta OCUPADO. CHECK-IN NAO PERMITIDO    \n");
					printf("+======================================================+\n");
					printf("                 ANDAR %d || QUARTO %d                  \n\n", andar + 1, quarto + 1);
					}
				break;
				
			case 2:  // Check-out
				if (hotel[andar][quarto] == 'o') 
					{
					do
						{
						system("cls");
						printf("Gostaria de prosseguir com o Check-Out da locacao ANDAR %d || QUARTO %d ?", andar + 1, quarto + 1);
						printf("\n\n1 - Sim\n0 - Nao\n");
						scanf("%d", &conf1);
						} while (conf1 != 0 && conf1 != 1);
					if (conf1 == 1)
						{
						hotel[andar][quarto] = '.';    // Marca como disponível
						system("cls");
						printf("+=====================================+\n");
						printf("    CHECK-OUT REALIZADO COM SUCESSO    \n");
						printf("+=====================================+\n");
						printf("         ANDAR %d || QUARTO %d         \n\n", andar + 1, quarto + 1);
						}
					else 
						{
						system("cls");
						break;
						}
					}
				else if (hotel[andar][quarto] == 'r') 
					{
					system("cls");
					printf("+=========================================================+\n");
					printf("    Este quarto esta RESERVADO. CHECK-OUT NAO PERMITIDO    \n");
					printf("+=========================================================+\n");
					printf("                   ANDAR %d || QUARTO %d                   \n\n", andar + 1, quarto + 1);
					}
				else if (hotel[andar][quarto] == '.') 
					{
					system("cls");
					printf("+==========================================================+\n");
					printf("    Este quarto esta DISPONIVEL. CHECK-OUT NAO PERMITIDO    \n");
					printf("+==========================================================+\n");
					printf("                   ANDAR %d || QUARTO %d                    \n\n", andar + 1, quarto + 1);
					}
				break;
				
			case 3:  // Reservar
				if (hotel[andar][quarto] == '.') 
					{
					system("cls");
					printf("Para prosseguir com a Reserva, forneca os seguintes dados:\n\n");
					dadosHospede h = cadastrarHospede(andar, quarto);
					if (h.Valido != 0) 
						{
    					hospedes[andar][quarto] = h;
    					hotel[andar][quarto] = 'r';   // Marca como reservado
    					system("cls");
    					printf("+===================================+\n");
    					printf("    RESERVA REALIZADA COM SUCESSO    \n");
    					printf("+===================================+\n");
    					printf("        ANDAR %d || QUARTO %d        \n\n", andar + 1, quarto + 1);
						}
					}
				else if (hotel[andar][quarto] == 'r') 
					{
					system("cls");
					printf("+==========================================================================+\n");
					printf("    Este quarto esta RESERVADO para outro hospede. RESERVA NAO PERMITIDA    \n");
					printf("+==========================================================================+\n");
					printf("                           ANDAR %d || QUARTO %d                            \n\n", andar + 1, quarto + 1);
					}
				else if (hotel[andar][quarto] == 'o') 
					{
					system("cls");
					printf("+=====================================================+\n");
        			printf("    Este quarto esta OCUPADO. RESERVA NAO PERMITIDA    \n");
        			printf("+=====================================================+\n");
        			printf("                 ANDAR %d || QUARTO %d                 \n\n", andar + 1, quarto + 1);
        			}
				break;
				
			case 4:  // Cancelar reserva
				if (hotel[andar][quarto] == 'r')
					{
					do
						{
						system("cls");
						printf("Gostaria de prosseguir com o Cancelamento de Reserva da locacao ANDAR %d || QUARTO %d ?", andar + 1, quarto + 1);
						printf("\n\n1 - Sim\n0 - Nao\n");
						scanf("%d", &conf2);
						} while (conf2 != 0 && conf2 != 1);
					if (conf2 == 1)
						{
						hotel[andar][quarto] = '.';  // Marca como disponivel
						system("cls");
						printf("+===================================================+\n");
						printf("    CANCELAMENTO DE RESERVA REALIZADO COM SUCESSO    \n");
						printf("+===================================================+\n");
						printf("                ANDAR %d || QUARTO %d                \n\n", andar + 1, quarto + 1);
						}
					else 
						{
						system("cls");
						break;
						}
					}
				else if (hotel[andar][quarto] == '.') 
					{
					system("cls");
					printf("+========================================================================+\n");
					printf("    Este quarto esta DISPONIVEL. CANCELAMENTO DE RESERVA NAO PERMITIDO    \n");
					printf("+========================================================================+\n");
					printf("                          ANDAR %d || QUARTO %d                           \n\n", andar + 1, quarto + 1);
        			}
        		else if (hotel[andar][quarto] == 'o') 
					{
					system("cls");
					printf("+=====================================================================+\n");
					printf("    Este quarto esta OCUPADO. CANCELAMENTO DE RESERVA NAO PERMITIDO    \n");
					printf("+=====================================================================+\n");
					printf("                         ANDAR %d || QUARTO %d                         \n\n", andar + 1, quarto + 1);
        			}
				break;
				
			case 5:   // Mostrar dados
				if (hotel[andar][quarto] == 'r')
					{
					system("cls");
					printf("+================================+\n");
					printf("    Este quarto esta RESERVADO    \n");
					printf("+================================+\n\n");
					mostrarHospede(hotel, hospedes[andar][quarto], andar, quarto);
					}
				else if (hotel[andar][quarto] == 'o')
					{
					system("cls");
					printf("+==============================+\n");
					printf("    Este quarto esta OCUPADO    \n");
					printf("+==============================+\n\n");
					mostrarHospede(hotel, hospedes[andar][quarto], andar, quarto);	
					}
				if (hotel[andar][quarto] == '.')
					{
					system("cls");
					printf("+=================================+\n");
					printf("    Este quarto esta DISPONIVEL    \n");
					printf("+=================================+\n\n");
					do
						{
						printf("O que deseja fazer: ");
						printf("\n\n1 - Reserva\n2 - Check-In\n0 - Sair\n");
						scanf("%d", &op2);
						} while (op2 != 0 && op2 != 1 && op2 != 2);
					if (op2 == 1)
						{
						system("cls");   
						printf("Para prosseguir com a Reserva, forneca os seguintes dados:\n\n");
						dadosHospede h = cadastrarHospede(andar, quarto);
						if (h.Valido != 0)
							{
    						hospedes[andar][quarto] = h;
   	 						hotel[andar][quarto] = 'r';
							system("cls");
							printf("+===================================+\n");
    						printf("    RESERVA REALIZADA COM SUCESSO    \n");
    						printf("+===================================+\n");
    						printf("        ANDAR %d || QUARTO %d        \n\n", andar + 1, quarto + 1);
    						}
    					break;
						}
					else if (op2 == 2) 
						{
						system("cls");  
						printf("Para prosseguir com o Check-In, forneca os seguintes dados:\n\n");
						dadosHospede h = cadastrarHospede(andar, quarto);
						if (h.Valido != 0)
							{
    						hospedes[andar][quarto] = h;
    						hotel[andar][quarto] = 'o';
							system("cls");
							printf("+====================================+\n");
    						printf("    CHECK-IN REALIZADO COM SUCESSO    \n");
    						printf("+====================================+\n");
    						printf("        ANDAR %d || QUARTO %d         \n\n", andar + 1, quarto + 1);
    						}
    					break;
                		}
                	else 
						continue;
                	}
                	fclear();
					break;
			}
		} while (1);	
			
		printf("\n");
}


// Funções:
void ftabela(char hotel[NIVEL][SALA])
	{
    int linha, coluna;
    
    printf("\n");
	printf("                                    MAPA DO HOTEL\n\n");
	
    // Impressão do Cabeçalho da Coluna
    printf("Quartos  ||");
    for (coluna = 0; coluna < SALA; coluna++)
        printf("%4d ", coluna + 1);

    printf("\n\n");

    // Impressão do Cabeçalho da Linha e do conteúdo
    for (linha = NIVEL - 1; linha >= 0; linha--) 
		{
        printf("Andar %2d   ", linha + 1);

        for (coluna = 0; coluna < SALA; coluna++)
            printf("   %c ", hotel[linha][coluna]);

        printf("\n");
        }
    printf("\nLegenda: . = Disponivel | r = Reservado | o = Ocupado\n\n\n");
	}
	
	
void fclear()
	{
	char carac;
	while((carac = fgetc(stdin)) != EOF && carac != '\n') {}
	}


void mostrarHospede(char hotel[NIVEL][SALA], dadosHospede h, int andar, int quarto)
	{   
	printf("\nQuarto: Andar %d, Numero: %d, Status: ", andar + 1, quarto + 1);
	if (hotel[andar][quarto] == 'r')
		{
		printf("Reservado");	
		printf("\n--------------------------------------------------\n");
    	printf("Nome: %s\n", h.nome);
   		printf("CPF: %s\n", h.cpf);
    	printf("Celular: %s\n", h.celular);
    	printf("Email: %s\n", h.email);
    	printf("Endereco: %s\n", h.endereco.residencia);
    	printf("Municipio: %s\n", h.endereco.municipio);
    	printf("UF: %s\n", h.endereco.uf);
    	printf("CEP: %s\n", h.endereco.cep);
		printf("--------------------------------------------------\n\n");
		}
	else if (hotel[andar][quarto] == 'o')
		{
		printf("Ocupado");	
		printf("\n---------------------------------------------------\n");
    	printf("Nome: %s\n", h.nome);
   		printf("CPF: %s\n", h.cpf);
    	printf("Celular: %s\n", h.celular);
    	printf("Email: %s\n", h.email);
    	printf("Endereco: %s\n", h.endereco.residencia);
    	printf("Municipio: %s\n", h.endereco.municipio);
    	printf("UF: %s\n", h.endereco.uf);
    	printf("CEP: %s\n", h.endereco.cep);
		printf("---------------------------------------------------\n\n");
		}
	}
	

dadosHospede cadastrarHospede(int andar, int quarto)
	{
    dadosHospede h;    // Variável local para armazenar temporariamente os dados
	
	h.Valido = 1;
	
	fclear();
    printf("Nome: ");
    gets(h.nome);
    if (h.nome[0] == '\0')
    	// Se não digitar, retorna struct vazia
        h.Valido = 0;
	
    printf("CPF: ");
    gets(h.cpf);
	if (h.cpf[0] == '\0')
        h.Valido = 0;
    
    printf("Telefone Celular: ");
    gets(h.celular);
    if (h.celular[0] == '\0')
        h.Valido = 0;

    printf("Email: ");
    gets(h.email);
    if (h.email[0] == '\0')
        h.Valido = 0;

    printf("Endereco: ");
    gets(h.endereco.residencia);
    if (h.endereco.residencia[0] == '\0')
        h.Valido = 0;

    printf("Municipio: ");
    gets(h.endereco.municipio);
    if (h.endereco.municipio[0] == '\0')
        h.Valido = 0;
    
    printf("UF: ");
    gets(h.endereco.uf);
    if (h.endereco.uf[0] == '\0')
    	h.Valido  = 0;

    printf("CEP: ");
    gets(h.endereco.cep);
    if (h.endereco.cep[0] == '\0')
        h.Valido = 0;	
        
    if (h.Valido == 0) 
    	{
    	printf("\n+=========================================+\n");
        printf("    ACAO CANCELADA. DADOS INSUFICIENTES    \n");
        printf("+=========================================+\n");
        printf("           ANDAR %d || QUARTO %d           \n\n", andar + 1, quarto + 1);
    	}
    	
	else
    	return h;     // Retorna struct preenchido
	}
	
	
int fverificar(char a[], char b[]) 
	{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') 
    	{
        if (a[i] != b[i]) 
            return 0;
        i++;
    	}
    return a[i] == b[i];   // Garante que ambas terminaram ao mesmo tempo
	}
