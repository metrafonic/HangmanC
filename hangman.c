/*
 * hangman.c
 * 
 * Copyright 2014 Mathias Hedberg <hedberg.mathias@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define N 100000
#define HENGT 7

char hangmanOrd[N][30];
char hangman[HENGT][30]=
{	" ________ ",
	"     |    ",
	"     O    ",
	"    /|\\   ",
	"     |    ",
	"    / \\   ",
	"   /   \\  "};
char header[10][100]=
{	"\n\n\t\t    _    ,                                \n",
	"\t\t   ' )  /                                 \n",
	"\t\t    /--/ __.  ____  _,  ______  __.  ____ \n",
	"\t\t   /  (_(_/|_/ / <_(_)_/ / / <_(_/|_/ / <_\n",
	"\t\t                    /|                    \n",
	"\t\t                   |/ - Mathias Hedberg\n\n"};
	
int lesHangmanOrd(){
	char tempOrd[30];
	int i=0;
	FILE * ordFil = NULL;
	ordFil=fopen("Hangman.txt", "r");
	do{
		fscanf(ordFil, "%s", tempOrd);
		strcpy(hangmanOrd[i], tempOrd);
		i++;
	}while(!feof(ordFil) && i<N);
	fclose(ordFil);
	if (i>1){
		return i;
	}else{
		printf("ERROR: No word file\n");
		return -1;
	}
}
void tegnHeader(){
	int i=0;
	for (i=0;i<7;i++){
		printf("%s", header[i]);
	}
}
void tegnHangman(int nivaa){
	int i=0;
	for (i=0;i<nivaa;i++){
			printf("\t\t\t\t%s\n",hangman[i]);
		}
	for (i=0;i<(HENGT-nivaa);i++){
			printf("\n");
		}
}
void spillHangman(int antallOrd){
	               
	char funneteTegn[30], tegn, feil[30]={" "};
	int valgteOrd=0, i, antallTreff=0, antallGaleGjett=0, ordLengde, funnetriktig=0;
	memset(funneteTegn, '_', 30);
	valgteOrd=rand()%antallOrd;
	ordLengde= strlen(hangmanOrd[valgteOrd]);
	funneteTegn[ordLengde]= '\0';
	system("cls");
	tegnHeader();
	tegnHangman(antallGaleGjett);
	printf("\n\n\t\t  Word: %s", funneteTegn);
	printf("\t\t%sMistakes: %s\n\n", header[6],feil);
	
	while(antallGaleGjett<7 && antallTreff<ordLengde){
		printf("\t\t  Choose a letter : ");
		scanf(" %c", &tegn);
		system("cls");
		tegnHeader();
		funnetriktig=0;
		for (i=0;i<strlen(hangmanOrd[valgteOrd]);i++){
			if (tegn==hangmanOrd[valgteOrd][i] && funneteTegn[i]!= tegn){
				antallTreff++;
				funneteTegn[i]= tegn;
				funnetriktig++;
			}
		}
		if (funnetriktig==0){
			antallGaleGjett++;
			feil[antallGaleGjett]=tegn;
		}
		tegnHangman(antallGaleGjett);
		printf("\n\n\t\t  Word: %s", funneteTegn);
	printf("\t\t%sMistakes: %s\n\n", header[6],feil);
	}
	if (antallGaleGjett==7){
		printf("\n\t\t  Too bad!!    The answer was: %s\n\n", hangmanOrd[valgteOrd]);
	}
}

int main(int argc, char **argv)
{
	int spilleigjen=1, antallOrd, i;
	antallOrd = lesHangmanOrd();
	
	srand (time(NULL));
	
	while(spilleigjen && antallOrd!=-1){
		spillHangman(antallOrd);
		/*printf("Vi har ordene:\n");
		for (i=0;i<antallOrd;i++){
			printf("%i. %s\n", i+1,hangmanOrd[i]);
		}*/
		printf("\t\t  Spille igjen? 1(ja)/0(nei)");
		scanf("%i",&spilleigjen);
	}
	return 0;
}

