#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define OCZKO 21
#define SIZE 52
#define MAX_CARDS 10
#define KRUPIER_MAX 17

int losowanie (void);
void kolejka_gracza (int*,int*,int*);
void kolejka_krupiera(int*,int*,int*);
void dobranie(int*,int,int*,int*);
void wygrany (int*,int*);
int jaka_karta (int);
void rozdanie(int*,int*,int*,int*);
int sprawdzenie(void);



int main()
{   printf("Michal Kucharski\tgrupa J2i1\ngra karciana blackajck\n");
    int choice =1;
    srand(time(0));

    while(1){
        printf("NOWA GRA - 1   ZAKONCZ - 2\n");
        choice = sprawdzenie();
        system("cls");

            if(choice == 1 ){//nowa gra
                int karty_gracza[MAX_CARDS],karty_krupiera[MAX_CARDS];
                int suma_gracza = 0,suma_krupiera = 0;
                int *gracz_ptr = &suma_gracza, *krupier_ptr = &suma_krupiera;

                rozdanie(karty_gracza,karty_krupiera,gracz_ptr,krupier_ptr);
                printf("\nKOLEJKA GRACZA");
                kolejka_gracza(karty_gracza,gracz_ptr,karty_krupiera);

                if(*gracz_ptr < OCZKO){

                    printf("\nKOLEJKA KRUPIERA\n");
                    kolejka_krupiera(karty_krupiera,krupier_ptr,karty_gracza);
                }
                wygrany(gracz_ptr,krupier_ptr);
            }
            if (choice == 2) break;//koniec gry
    }
return 0;
}
int losowanie(){//wylosowanie liczby za zakresu 0-52

    return rand()%SIZE;
}

void kolejka_gracza (int *karty_gracza,int* suma_gracza,int*karty_krupiera){
        int choice,i;

        for(i = 2; i < MAX_CARDS ; i++){
            printf("\nDobierz - 1     Czekaj - 2\n");
            choice = sprawdzenie();

            if(choice == 1){
                printf("dobrana przez ciebie karta to : ");

                dobranie(karty_gracza,i,suma_gracza,karty_krupiera);//dobranie karty
            }
            if(choice == 2) break;//spasowanie

            if (*suma_gracza > OCZKO){

                if(karty_gracza[i]%13 == 12) (*suma_gracza)-=10;//odjecie 10 w razie wylosowannia asa

                else {
                    printf("\nMASZ PONAD 21, KONIEC KOLEJKI\n");//koniec kolejki po przekroczeniu 21
                    break;
                }
            }
        }
}

void kolejka_krupiera(int* karty_krupiera, int* suma_krupiera,int* karty_gracza){
    int i;
        for(i = 1; i < MAX_CARDS ; i++){
                getchar();

            if(*suma_krupiera < KRUPIER_MAX){
                printf("dobrana karta przez krupiera to : ");

                dobranie(karty_krupiera,i,suma_krupiera,karty_gracza); //dobranie karty
            }

            if (*suma_krupiera > OCZKO && karty_krupiera[i]%13 == 12)//odjecie 10 jesli suma przekroczona i wylosowany as
                (*suma_krupiera)-=10;

            if(*suma_krupiera >= KRUPIER_MAX){//zakonczenie rundy krupiera jesli suma punktow przekroczy 17
                printf("\nkoniec kolejki krupiera\n");
                break;
            }
        }
}


void dobranie(int * karty_gracza,int ktory_ruch,int* suma_gracza, int* karty_krupiera){//dobranie karty
    int i;
    while(1){
        int powtorzenie = 0;
        karty_gracza[ktory_ruch] = losowanie();//przypisanie do tablicy kart gracza wylosowanej liczby
        for(i = 0 ; i < ktory_ruch ; i++)
            if(karty_gracza[i]==karty_gracza[ktory_ruch]|| karty_krupiera[i] == karty_gracza[ktory_ruch]) powtorzenie = 1;//sprawdzenie czy dana karta nie zostala juz wylosowana

            if(powtorzenie != 1) break;
    }
    *suma_gracza += jaka_karta(karty_gracza[ktory_ruch]);//dodanie wartosci karty do uma danego gracza
}



void wygrany (int* suma_gracza,int* suma_krupiera){//okreslenie kto wygral

    if(*suma_gracza == *suma_krupiera) printf("\nremis\n\n");

    else if(*suma_gracza > *suma_krupiera &&  *suma_gracza <= OCZKO ) printf("\nWYGRAL GRACZ\n\n");

    else printf("\nWYGRAL KRUPIER\n\n");

}


int jaka_karta (int karta){//sprawdzenie na jaka karte przelicza sie wylosowana liczba

    int moc;

    switch(karta%13){//okreslenie jaka karta zostala wylosowana

            case 0 : printf("dwojka"); moc = 2 ; break;

            case 1 : printf("trojka"); moc = 3 ; break;

            case 2 : printf("czworka"); moc = 4 ;  break;

            case 3 : printf("piatka"); moc = 5 ;break;

            case 4 : printf("szostka"); moc = 6 ;break;

            case 5 : printf("siodemka"); moc = 7 ;break;

            case 6 : printf("osemka");  moc = 8 ;break;

            case 7 : printf("dziewiatka"); moc = 9 ;break;

            case 8 : printf("dziesiatka"); moc = 10 ;break;

            case 9 : printf("walet"); moc = 10 ;break;

            case 10 : printf("dama");   moc = 10 ;break;

            case 11 : printf("krol"); moc = 10 ;break;

            case 12 : printf("as");moc = 11;break;
        }

        switch(karta/13){//okreslenie jaki dana karta ma symbol

            case 0 : printf(" pik "); break;

            case 1 : printf(" trefl "); break;

            case 2 : printf(" karo ");  break;

            case 3 : printf(" kier "); break;

        }
    return moc;//zwrocenie punktow jakie przyslufuja za dorbanie danej karty
}

void rozdanie(int*karty_gracza,int*karty_krupiera,int*gracz_ptr,int*krupier_ptr){ // rozdanie dwoch kart dla gracza i jednej dla krupiera

        printf("Wylosowales nastepujace karty: "); dobranie(karty_gracza,0,gracz_ptr,karty_krupiera);

        printf(" oraz "); dobranie(karty_gracza,1,gracz_ptr,karty_krupiera);

        printf("\nkarta krupiera, to: "); dobranie(karty_krupiera,0,krupier_ptr,karty_gracza);


        }

int sprawdzenie() //sprawdzanie  poprawnosci wprowadzonych danych
{
    int zmienna;
    while(scanf("%d", &zmienna) != 1 || (zmienna!=2 && zmienna!=1) )
    {
      printf("Wprowadz liczbe 1 lub 2 \n");
      int c;
      while((c = getchar()) != '\n' && c != EOF);
    }
    return zmienna;
}


