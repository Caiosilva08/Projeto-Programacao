#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Caio da Silva de Miranda 6368 - Pedro Lucas ALves de Caravlho 6330

typedef struct sInfo{
	
	char nome[31];
	float tempo;
	
}Info;

typedef struct sCampos{ // Struct para auxiliar a gerar a matriz interna e externa

	int valor;
	char x;
	
}Campos;

void obterRec (Info *x){
	
	int k = 0;
	
	FILE* rec;
	
	rec = fopen("Recordes.txt", "r");
		
	if(rec == NULL){
		
 		printf("Erro na abertura.\n");
 		
	}
	
	while(k<5){
		
		fscanf(rec, "%s %f\n", &x[k].nome , &x[k].tempo);
		k++;
	}
	/*for(k=0;k<5;k++){
		printf("nome : %s  -  %f\n", x[k].nome , x[k].tempo);
	}*/
	fclose(rec);
	
}

void recordes (Info *x){
	
	Info aux;
	int i, j;
	
	for(i = 0; i < 5; i++){
		for(j = i+1; j < 5; j++){
			
			if(x[i].tempo > x[j].tempo){
				
				strcpy(aux.nome, x[i].nome);
				
				aux.tempo = x[i].tempo;
				
				strcpy(x[i].nome, x[j].nome);
				
				x[i].tempo = x[j].tempo;
				
				strcpy(x[j].nome, aux.nome);
				
				x[j].tempo = aux.tempo;
				
			}
		}
	}
	
	for(i = 0; i < 5; i++){
		
		printf("\n%d - %s possui o recorde de %.2f segundos\n", i, x[i].nome, x[i].tempo);
	}
}

void obterRec2 (Info *x){
	
	int k = 0;
	
	FILE* rec;
	
	rec = fopen("RecordesPers.txt", "r");
		
	if(rec == NULL){
		
 		printf("Erro na abertura.\n");
 		
	}
	
	while(k<5){
		
		fscanf(rec, "%s %f\n", &x[k].nome , &x[k].tempo);
		k++;
	}
	/*for(k=0;k<5;k++){
		printf("nome : %s  -  %f\n", x[k].nome , x[k].tempo);
	}*/
	fclose(rec);
	
}

void recordes2 (Info *x){
	
	Info aux;
	int i, j;
	
	for(i = 0; i < 5; i++){
		for(j = i+1; j < 5; j++){
			
			if(x[i].tempo > x[j].tempo){
				
				strcpy(aux.nome, x[i].nome);
				
				aux.tempo = x[i].tempo;
				
				strcpy(x[i].nome, x[j].nome);
				
				x[i].tempo = x[j].tempo;
				
				strcpy(x[j].nome, aux.nome);
				
				x[j].tempo = aux.tempo;
				
			}
		}
	}
	
	for(i = 0; i < 5; i++){
		
		printf("\n%d - %s possui o recorde de %.2f segundos\n", i, x[i].nome, x[i].tempo);
	}
}

void salvae(Info x, Info *rec){
	
	float maior = rec[0].tempo;
	
	int i, indice;
	
	for(i = 0; i < 5; i++){
		
		if(maior < rec[i].tempo){
			
			maior = rec[i].tempo;
			indice = i;
			
		}
	}
	
	rec[indice].tempo = x.tempo;
	strcpy(rec[indice].nome, x.nome);
	
	FILE* arquivo;
	
	arquivo = fopen("Recordes.txt", "w+");
	
	for(i = 0; i < 5; i++){
		
		fprintf(arquivo, "%s %f", rec[i].nome, rec[i].tempo);
		
	}
	
	fclose(arquivo);
	
}

void salvae2(Info x, Info *rec){
	
	float maior = rec[0].tempo;
	
	int i, indice;
	
	for(i = 0; i < 5; i++){
		
		if(maior < rec[i].tempo){
			
			maior = rec[i].tempo;
			indice = i;
			
		}
	}
	
	rec[indice].tempo = x.tempo;
	strcpy(rec[indice].nome, x.nome);
	
	FILE* arquivo;
	
	arquivo = fopen("RecordesPers.txt", "w+");
	
	for(i = 0; i < 5; i++){
		
		fprintf(arquivo, "%s %f", rec[i].nome, rec[i].tempo);
		
	}
	
	fclose(arquivo);
	
}

void livre (Campos **campo, int lin, int col, int cont, int tamlin, int tamcol){
	
	
	for (lin = 0; lin < 9; lin++){
		for (col = 0; col < 9; col++){
			
			if(campo[lin][col].valor >= 0){
				
				cont++;
				
			}
		}
	}
}

void adja (Campos **campo, int lin, int col, int tamlin, int tamcol){ // Função para abrir as posições adjacentes
	
	int l, c;
	
	for (l = lin-1;  l < lin+2; l ++){
		for(c = col -1; c < col+2; c ++){
			
			if (l >= 0 &&  c >= 0 && l < tamlin && c < tamcol && campo[l][c].valor == 0 && campo[l][c].x != 'B'){
				
			campo[l][c].valor = -2;
			
			campo[l][c].x = '-';
			
			adja(campo, l, c, tamlin, tamcol);
			
		}else if(l >= 0 &&  c >= 0 && l < tamlin && c < tamcol && campo[l][c].valor > 0 && campo[l][c].x != 'B'){
				
			campo[l][c].x = campo[l][c].valor + 48;
				
			}
			
		}
	
	}
	

}
void verificabom(Campos **campo, int lin, int col,int tamlin, int tamcol){ // Matriz para verificar se tem bomba ao redor
	
	int l, c;
	int cont;
	
	for (l = lin-1; l < lin+2; l ++){
		for(c = col -1; c < col+2; c ++){
			
			if (l >= 0 &&  c >= 0 && l < tamlin && c < tamcol && campo[l][c].valor != -1 )
			
				campo[l][c].valor++;
				
		}
		
	}
	
	
	
}

void imprimeaberta(Campos **campo, int tamlin, int tamcol){ // Função para abrir a matriz ao perder o jogo
	
	int i, j, z = 0;
	
    system("cls");
    
    int k;
    
    for(k = 0; k < tamcol; k++){
    	
    	printf("        %d       ", k);
    	
	}
    	
    for(i=0; i<tamlin; i++)
    {
    	printf("\n %d", i);
    	
        for(j=0; j<tamcol; j++)
        {
            	if(campo[i][j].valor == -1){
            		
            		printf("\t|*\t");
				}
				
				else{
				
                printf("\t|%d\t", campo[i][j].valor);
                
            }
          
        }
        printf("|");
 
    }
	
}
void imprimatriz(Campos **campo, int tamlin, int tamcol){ // Função para imprimir a matriz externa (a que o usuário visualiza)
	
	int i, j, z = 0;
	
    system("cls");
    
    int k;
    
    for(k = 0; k < tamcol; k++){
    	
    	printf("        %d       ", k);
    	
	}
    
    for(i=0; i < tamlin; i++)
    {
    	printf("\n %d", i);
    	
        for(j=0; j < tamcol; j++)
        {
            	
                printf("\t|%c\t", campo[i][j].x);
          
        }
        printf("|");
 
    }
    
}

void gerarbomba(Campos **campo, int tamlin, int tamcol, int nb){ // Função para gerar as bombas na matriz interna
	
	int x, y, z;
	
	srand(time(NULL));
	
	
	for(z = 0; z < nb; z++){
	
	x = rand() % tamlin;
	
	y = rand() % tamcol;
	
		while (campo[x][y].valor == -1){
		
			x = rand() % tamlin;
	
			y = rand() % tamcol;
		
		}
	
	campo[x][y].valor = -1;
	
	verificabom(campo, x, y, tamlin, tamcol);
	
	}
	
}
	
void inicmatriz(Campos **campo, int tamlin, int tamcol){ // Função para inicializar a matriz interna e externa
	
	int i, j, k;

	for(i=0; i<tamlin; i++){
    	
        for(j=0; j<tamcol; j++){
        	
            campo[i][j].x = '#';
            
            campo[i][j].valor = 0;
            
        }
	
	}
	
}

void jogar(int tamlin, int tamcol, int nb, Info x, Info *rec, int opc){ // Função que começa o jogo
	
	float inicio, fim;
	int lin, col, lin2;
	
	Campos **campo;
	
	campo = (Campos**) malloc (tamlin * sizeof(Campos*));
	
	int i;
	
	for (i = 0; i < tamlin; i++){
		
		campo[i] = (Campos*) malloc (tamcol * sizeof(Campos));
		
	}
	 
	
	inicmatriz(campo, tamlin, tamcol);
	
	gerarbomba(campo, tamlin, tamcol, nb);
	
	inicio = clock();
	
	int contab = 0;
	int cont = 0;
	int l, c;
    
    do{
    
	imprimatriz(campo, tamlin, tamcol);
	
	printf("\n\n%d espacos abertos", cont);
	printf("\n\nBandeiras ja colocadas %d/10", contab);
    printf ("\n\nDigite a linha que deseja abrir ou digite -1 para colocar uma bandeira: ");
    scanf("%d", &lin2);
    
    	if(lin2 >= tamlin){
    		
    		printf("\nLinha invalida\n");
    		system("pause");
    		continue;
		}
    
    if(lin2 == -1 && contab < 10){
   		
   		printf ("\n\nDigite a linha que deseja colocar bandeira: ");
    	scanf("%d", &lin);
    	printf("Digite a coluna que deseja colocar bandeira: ");
    	scanf("%d", &col);
    	
    	if(lin > tamlin || col > tamcol || campo[lin][col].x == '-' || campo[lin][col].x == 'B' || campo[lin][col].x == '1' || campo[lin][col].x == '2' || campo[lin][col].x == '3' || campo[lin][col].x == '4' || campo[lin][col].x == '5' || campo[lin][col].x == '6' || campo[lin][col].x == '7' || campo[lin][col].x == '8'){
    		
    		printf("\nLinha ou coluna invalida\n");
    		system("pause");
    		
		}else{
    	
    		campo[lin][col].x = 'B';
    	
    		contab++;
    		
    		printf("aaa %c", campo[lin][col].x);
    	}
    	
    	continue;
	   
    }
    
    if(lin2 > -1 && lin2 < tamlin){
    	
    	lin = lin2;
		
    	printf("Digite a coluna que deseja abrir: ");
    	scanf("%d", &col);
    	
    	if(col > tamcol){
    		
    		printf("\nColuna invalida\n");
    		system("pause");
    		continue;
		}
    	
	}
	
	if(campo[lin][col].x == 'B'){
    		
    	campo[lin][col].x = '#';
    	contab--;
    		
    	continue;
    	
		}
		
    if(campo[lin][col].valor == -1 && campo[lin][col].x != 'B'){
    	
    	imprimeaberta(campo, tamlin, tamcol);
   		
   		printf("\nVoce perdeu !!\n");
		break;
		
	}
	
	if(campo[lin][col].valor == 0){
	   	
	   		campo[lin][col].x = '-';
	   		
		}
		    
	else {
		
			campo[lin][col].x = campo[lin][col].valor + 48;
			
	}
	
	if(campo[lin][col].valor == 0){
		
		adja(campo, lin, col, tamlin, tamcol);
		
	}
	
	cont = 0;
	
	for(l = 0; l < tamlin; l++){
		for(c = 0; c < tamcol; c++){
			
			if(campo[l][c].x == '-'){
		
				cont++;
		
			}
			
			if(campo[l][c].valor > 0 && campo[l][c].x != '#' && campo[l][c].x  != '*'){
		
				cont++;
		
			}
			
		}
	}
	
	if(cont == (tamlin * tamcol) - nb){
		
		printf("\nVOCE GANH0U !!!!");
		
		fim = clock();
		
		x.tempo = (float)(fim - inicio)/CLOCKS_PER_SEC;
				
		printf("\nTempo: %0.2f segundos\n",(float)(fim - inicio)/CLOCKS_PER_SEC);
		
		if(opc == 1){
		
			obterRec(rec);
			salvae(x, rec);
		
		}else{
			
			obterRec2(rec);
			salvae2(x, rec);
		}
		
		break;
		
		
	}
	
	   system("cls");
	   
	}while(cont < (tamlin * tamcol) - nb);
	
	for (i = 0; i < tamlin; i++){
		
		free (campo[i]);
		
	}
	 
	free (campo);
		
}
    
int imprimenu (Info x, Info *rec){ // Função para exibir o menu
	
	clock_t inicio, fim;
	int opc;
	
	printf("                                                                                                            \n");
	printf("                                                                                                            \n");
	printf("                                                               |          Campo Minado Definitivo          |\n");
	printf("                                                               |                                           |\n");
	printf("                                                               |              1 - Novo Jogo                |\n");
	printf("                                                               |        2 - Personalizar Tabuleiro         |\n");
	printf("                                                               |              3 - Recordes                 |\n");
	printf("                                                               |                 4 - Sair                  |\n");
	printf("                                                               |                                           |\n");
	
	scanf("%d", &opc);

	if(opc == 1){
		
		Info x;
		
		printf("Digite seu nome: ");
		scanf("%s", &x.nome);
		
		system("cls");
  			
		jogar(9, 9, 10, x, rec, opc);
		
		system("pause");
		system("cls");
		
	}
	
	if(opc == 2){
		
		int lin, col, nb;
		Info x;
		
		printf("Digite seu nome: ");
		scanf("%s", &x.nome);
		printf("\nDigite o numero de linhas: ");
		scanf("%d", &lin);
		printf("Digite o numero de colunas: ");
		scanf("%d", &col);
		printf("Digite a quantidade de bombas: ");
		scanf("%d", &nb);
			
  		inicio=clock();
  			
		jogar(lin, col, nb, x, rec, opc);
		
		fim=clock();
		
		x.tempo = (float)(fim - inicio)/CLOCKS_PER_SEC;
		
		printf("\nTempo: %0.2f segundos\n",(float)(fim - inicio)/CLOCKS_PER_SEC);
		
		
	}
	
	if(opc == 3){
		
		char c;
		
		printf("\nDigite P para ver os recordes de tabuleiro padrao ou R para ver os recordes de tabeleiro personalizado\n");
		fflush(stdin);
		
		scanf("%c", &c);
		
		if(c == 'P' || c == 'p'){

			obterRec(rec);
			recordes(rec);
		}
		
		if(c == 'R' || c == 'r'){
			
			obterRec2(rec);
			recordes2(rec);
			
		}
	}
 	
 	if(opc == 4){
 		
 		exit(1);
 		
	 }
	
	return opc;	
}

int main(){ // Função principal
	
	Info *rec, atual;
	
	rec = (Info*) malloc (5*sizeof(Info));
	
	int opc;
	
	do{
	
	opc = imprimenu(atual, rec);
	
    }while(opc != 4);
    
	scanf("%d", &opc);

}
