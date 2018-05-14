/*
    HALIL SAFA SAGLIK * THZBR
    thzbr@windowslive.com
    KACAMAK v 0.1
    {
        hareketsiz blok modu eklendi;
        skor modulu eklendi;
    }
    KACAMAK v 0.2
    {
        hareketli blok modu eklendi;
        ayar modulu eklendi;
        karsilama mesaji modulu eklendi;
        skor modulu gelistirildi;
        ###############BUGLAR###############
        hareketli bloklarda hesaplama hatasi
        ####################################

    }
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <string.h>
//kutuphaneler

#define press_right   77
#define press_left    75
#define press_down    80
#define press_up      72
//Tanimlar

int positionX = 1;//kontrolumuzdeki imlecin baslangic konumu x koordinati
int positionY = 4;//kontrolumuzdeki imlecin baslangic konumu y koordinati
int hareketyon = press_right;//kontrolumuzdeki imlecin baslangic yonu
int barrier[35][2] = {{0}};//hareketsiz bloklarin koordinatlarini tutan dizi
int maxSkore_1 = 0;//1. modda maksimum skor
int maxSkore_2 = 0;//2. modda maksimum skor
int myScore = 0;//anlik skoru tutan degisken
int game_mod = 2;//oyun modunu tutan degisken
int movableblocks[][4] = {{5,5,1,1},{10,8,-1,2},{8,11,1,-1},{2,20,-1,2},{3,11,-2,-2},{11,20,-1,-2},{30,14,-1,1}};//hareketli blokalrin koordinat ve hareket yonunu tutan dizi
int __len = sizeof(movableblocks)/sizeof(movableblocks[0]);//hareketli bloklarin tutuldugu dizinin eleman sayisini bulan degisken
//global tam sayi degiskenler
char myScoreName_1[100] = "user";//1. mod icin skoru yapan oyuncunun adini tutan degisken
char myScoreName_2[100] = "user";//2. mod icin skoru yapan oyuncunun adini tutan degisken
char xxx=220;
//global karakter degiskenleri
const int maxX = 79;//maksimum x koordinati
const int maxY = 24;//maksimum y koordinati

//global sabitler




void movable_blocks()
{

    int x;
    int y;

    int bolge = 0;

    int i;



    for (i=0; i<__len; i++)
    {
        CursorP(movableblocks[i][0],movableblocks[i][1]);
        printf(" ");

        x = movableblocks[i][2];
        y = movableblocks[i][3];

        if (x>0 && y>0)
        {
            bolge = 4;
        }
        else if (x<0 && y>0)
        {
            bolge = 3;
        }
        else if (x<0 && y<0)
        {
            bolge = 2;
        }
        else if (x>0 && y<0)
        {
            bolge = 1;
        }

        char carpma;

        if (movableblocks[i][0]+x>maxX-1 && movableblocks[i][1]+y>maxY-1)
        {
            carpma = 'a'; // alt sağ
        }
        else if (movableblocks[i][0]+x<1 && movableblocks[i][1]+y<4)
        {
            carpma = 'b'; // ust sol
        }
        else if (movableblocks[i][0]+x>maxX-1 && movableblocks[i][1]+y<4)
        {
            carpma = 'c'; // sag ust
        }
        else if (movableblocks[i][0]+x<1 && movableblocks[i][1]+y>maxY-1)
        {
            carpma = 'd'; // sol alt
        }
        else if (movableblocks[i][0]+x<1 || movableblocks[i][0]+x>maxX-1)
        {
            carpma = 'x';
        }
        else if (movableblocks[i][1]+y<4 || movableblocks[i][1]+y>maxY-1)
        {
            carpma = 'y';
        }
        /*
        y için
        1 bölge x+ y-
        */

        if (carpma == 'y')
        {
            if (bolge==1)
            {
                if (movableblocks[i][2]<0) movableblocks[i][2]*=-1;
                if (movableblocks[i][3]<0) movableblocks[i][3]*=-1;
            }
            else if (bolge==2)
            {
                if (movableblocks[i][2]>0) movableblocks[i][2]*=-1;
                if (movableblocks[i][3]<0) movableblocks[i][3]*=-1;
            }
            else if (bolge==3)
            {
                if (movableblocks[i][2]>0) movableblocks[i][2]*=-1;
                if (movableblocks[i][3]>0) movableblocks[i][3]*=-1;
            }
            else if (bolge==4)
            {
                if (movableblocks[i][2]<0) movableblocks[i][2]*=-1;
                if (movableblocks[i][3]>0) movableblocks[i][3]*=-1;
            }
        }

        if (carpma == 'x')
        {
            if (bolge==1)
            {
                if (movableblocks[i][2]>0) movableblocks[i][2]*=-1;
                if (movableblocks[i][3]>0) movableblocks[i][3]*=-1;
            }
            else if (bolge==2)
            {
                if (movableblocks[i][2]<0) movableblocks[i][2]*=-1;
                if (movableblocks[i][3]>0) movableblocks[i][3]*=-1;
            }
            else if (bolge==3)
            {
                if (movableblocks[i][2]<0) movableblocks[i][2]*=-1;
                if (movableblocks[i][3]<0) movableblocks[i][3]*=-1;
            }
            else if (bolge==4)
            {
                if (movableblocks[i][2]>0) movableblocks[i][2]*=-1;
                if (movableblocks[i][3]<0) movableblocks[i][3]*=-1;
            }
        }

        if (carpma=='a')
        {
            if (movableblocks[i][2]>0) movableblocks[i][2]*=-1;
            if (movableblocks[i][3]>0) movableblocks[i][3]*=-1;
        }

        if (carpma=='b')
        {
            if (movableblocks[i][2]<0) movableblocks[i][2]*=-1;
            if (movableblocks[i][3]<0) movableblocks[i][3]*=-1;
        }

        if (carpma=='c')
        {
            if (movableblocks[i][2]>0) movableblocks[i][2]*=-1;
            if (movableblocks[i][3]<0) movableblocks[i][3]*=-1;
        }

        if (carpma=='d')
        {
            if (movableblocks[i][2]<0) movableblocks[i][2]*=-1;
            if (movableblocks[i][3]>0) movableblocks[i][3]*=-1;
        }

        movableblocks[i][0] += movableblocks[i][2];
        movableblocks[i][1] += movableblocks[i][3];
        CursorP(movableblocks[i][0],movableblocks[i][1]);
        printf("%c",xxx);
    }
}

//hareketli bloklar algoritması

void scoreRegister()
{
    //skorkaydı
}

//skor kaydı

void CursorP(int x,int y)
{
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}

//koordinat sistemi

void settings_menu()
{
    int switch_key;
    system("cls");
    CursorP(35,6);
    printf("AYARLAR");
    CursorP(35,8);
    printf("Oyun Modu");
    switch(game_mod)
    {
    case 1:
        CursorP(30,10);
        printf("[1] Hareketsiz bloklar -> AKTIF");
        CursorP(30,11);
        printf("[2] Hareketli bloklar  -> PASIF");
        break;
    case 2:
        CursorP(30,10);
        printf("[1] Hareketsiz bloklar -> PASIF");
        CursorP(30,11);
        printf("[2] Hareketli bloklar  -> AKTIF");
        break;

    }
    CursorP(22,15);
    printf("oyun modunuzu degistirmek icin 1 veya 2'ye basiniz");


    CursorP(25,20);
    printf("'e' -> Cikis || 'h' -> AnaSayfa");
    repeat:
    switch_key = getch();
    switch(switch_key)
    {
        case 'e':
        exit(0);
        break;
        case 'h':
        home_screen();
        break;
        case '1':
        game_mod=1;
        system("cls");
        settings_menu();
        break;
        case '2':
        game_mod=2;
        system("cls");
        settings_menu();
        break;
        default:
        goto repeat;
        break;
    }
}

//ayar menusu

void scoreboard()
{
    system("cls");
    char sb_deger;
    if(game_mod == 1)
    {
        CursorP(30,4);
        printf("HAREKETSIZ BLOKLAR");
        CursorP(27,8);
        printf("En yuksek skor: %d p",maxSkore_1);
        CursorP(20,10);
        printf("En Yuksek Skor Sahibi: %s",myScoreName_1);
        CursorP(27,20);
        printf("'e' -> Cikis || 'h' -> AnaSayfa");
        repeat:
        sb_deger = getch();
        switch(sb_deger)
        {
            case 'e':
            break;
            case 'h':
            home_screen();
            break;
            default:
            goto repeat;
            break;
        }
    }
    else if(game_mod == 2)
    {
        CursorP(30,4);
        printf("HAREKETLI BLOKLAR");
        CursorP(27,8);
        printf("En yuksek skor: %d p",maxSkore_2);
        CursorP(20,10);
        printf("En Yuksek Skor Sahibi: %s",myScoreName_2);
        CursorP(27,20);
        printf("'e' -> Cikis || 'h' -> AnaSayfa");
        repeat2:
        sb_deger = getch();
        switch(sb_deger)
        {
            case 'e':
            break;
            case 'h':
            home_screen();
            break;
            default:
            goto repeat2;
            break;
        }
    }

}

//yuksek skor goruntuleme

void GameEnd()
{
    if(game_mod == 1)
    {
        char deger;
        system("cls");
        if(myScore>maxSkore_1)
        {
            CursorP(25,3);
            printf("EN YUKSEK SKORA ULASTINIZ TEBRIKLER");
            CursorP(30,6);
            printf("Skorunuz: %d p",myScore);
            CursorP(31,8);
            printf("Isminizi girinizi");
            CursorP(30,10);
            scanf("%s",&myScoreName_1);
            maxSkore_1 = myScore;
        }
        else
        {
            CursorP(30,6);
            printf("   Skorunuz: %d p",myScore);
            CursorP(27,8);
            printf("En yuksek skor: %d p",maxSkore_1);
            CursorP(20,10);
            printf("En Yuksek Skor Sahibi: %s",myScoreName_1);
        }
        myScore=0;
        CursorP(27,20);
        printf("'e' -> Cikis || 'h' -> AnaSayfa");
        repeat:
        deger = getch();
        switch(deger)
        {
            case 'e':
            exit(0);
            break;
            case 'h':
            home_screen();
            break;
            default:
            goto repeat;
            break;
        }
    }
    else if(game_mod == 2)
    {
        char deger;
        system("cls");
        if(myScore>maxSkore_2)
        {
            CursorP(25,3);
            printf("EN YUKSEK SKORA ULASTINIZ TEBRIKLER");
            CursorP(30,6);
            printf("Skorunuz: %d p",myScore);
            CursorP(31,8);
            printf("Isminizi girinizi");
            CursorP(30,10);
            scanf("%s",&myScoreName_2);
            maxSkore_2 = myScore;
        }
        else
        {
            CursorP(30,6);
            printf("   Skorunuz: %d p",myScore);
            CursorP(27,8);
            printf("En yuksek skor: %d p",maxSkore_2);
            CursorP(20,10);
            printf("En Yuksek Skor Sahibi: %s",myScoreName_2);
        }
        myScore=0;
        CursorP(27,20);
        printf("'e' -> Cikis || 'h' -> AnaSayfa");
        repeat3:
        deger = getch();
        switch(deger)
        {
            case 'e':
            exit(0);
            break;
            case 'h':
            home_screen();
            break;
            default:
            goto repeat3;
            break;
        }
    }


}

//oyun sonu skor

void home_screen()
{
    system("cls");
    CursorP(35,5);
    printf("KACAMAK");
    CursorP(33,10);
    printf("[n] Yeni oyun");
    CursorP(33,12);
    printf("[p] Duraklat");
    CursorP(33,14);
    printf("[k] Yuksek Skorlar");
    CursorP(33,16);
    printf("[s] Ayarlar");
    CursorP(33,18);
    printf("[h] Yardim");

    char home_deger = getch();

    switch(home_deger)
    {
        case 's':
        settings_menu();
        case 'n':
        controller();
        break;
        case 'h':
        help();
        break;
        case 'k':
        scoreboard();
        break;
        default:
        system("cls");
        home_screen();
        break;
    }


}

//ana sayfa

void help()
{
    char degisken123;
    gitgidebildiginyerekadar:
    system("cls");
    CursorP(17,10);
    printf("Yardim almak istediginiz modun kodunu giriniz: \n\t\t\t\t");
    printf("Hareketsiz -> 1\n\t\t\t\t");
    printf("Hareketli  -> 2\n\t\t\t\t");
    degisken123 = getch();
    switch(degisken123)
    {
    case '1':
        MessageBox(0,"-Bu modda rastgele bloklar olusturulmaktadir.\n -Surekli hareket eden imlecin yon tuslari ile yonunu\ndegistirerek bloklardan kacmaniz gerekmektedir.\n-Kenarlardan diger tarafa gecebilmektesiniz.\n-Bu hareketiniz oyun tarafindan sizin risk almaniz\nolarak algilanir.\n-Almis oldugunuz bu riske karsilik bloklar aninda yeniden \nkonumlandirilir.\n-Ve skor hanenize 5 puan eklenir.\n\n #EGER HERSEYI ANLADIYSAN YAVRU KURT GOREVE BASLAMAK ICIN 'TAMAM' BUTONUNA TIKLA!#", "KACAMAK - HAREKETSIZ BLOKLAR - YARDIM", MB_OK );
        game_mod=1;
        controller();
        break;
    case '2':
        MessageBox(0,"-Bu modda 5 adet surekli hareket eden blok olusturulmaktadir.\n-Surekli hareket eden imlecin yon tuslari ile yonunu\ndegistirerek bloklardan kacmaniz gerekmektedir.\n-Kenarlardan diger tarafa gecebilmektesiniz.\n-Bu hareketiniz oyun tarafindan kurnazlik  olarak algilanir.\nVe skor hanenizden 3 puan dusulur.\n\n#EGER HERSEYI ANLADIYSAN YAVRU KURT GOREVE BASLAMAK ICIN 'TAMAM' BUTONUNA TIKLA!#", "KACAMAK - HARAKETLI BLOKLAR -YARDIM", MB_OK );
        game_mod=2;
        controller();
        break;
    default:
        goto gitgidebildiginyerekadar;
        break;
    }
    system("cls");
    home_screen();
}

//yardım

void settings()
{

    ShellExecute(0,"open","music.mp3",0,0, SW_HIDE);


    SetConsoleTitle("KACAMAK v 0.2 | thzbr@windowslive.com | HALIL SAFA SAGLIK");
    MessageBox(0,"Hos geldin bro, iyi vakit gecirmen dilegiyle", "KACAMAK", MB_OK );
}

//oyunun baslangic ayar kismi

void block()
{
    srand(time(NULL));
    int i;
    for (i=0; i<35; i++)
    {
        if(barrier[i][0]!=0)
        {
            CursorP(barrier[i][0],barrier[i][1]);
            printf(" ");
        }
    }


    for (i=0; i<35; i++)
    {
        barrier[i][0] = rand()%78+1;
        barrier[i][1] = rand()%20+4;

        if (abs(positionX-barrier[i][0])<3 || abs(positionY-barrier[i][1])<3) {
            barrier[i][0] = rand()%78+1;
            barrier[i][1] = rand()%20+4;
        }

        CursorP(barrier[i][0],barrier[i][1]);
        printf("%c",xxx);
    }
}

//rastgele engel ureten fonksiyon mod1 için

void collisioncontrol()
{
    int i;
    if(game_mod == 1)
    {
        for (i=0; i<35; i++)
        {
            if (barrier[i][0]==positionX && barrier[i][1]==positionY)
            {
                GameEnd();
            }
        }
    }
    else if(game_mod == 2)
    {
        for (i=0; i<__len; i++)
        {
            if (movableblocks[i][0]==positionX && movableblocks[i][1]==positionY)
            {
                GameEnd();
            }
        }
    }



}

//çarpismayi algilayan fonksiyon

void frame()
{
    char p_Blocks ='|';
    char p_Blocks2 ='-';
    int i,j;
    for(j=0;j<80;j++)
    {
        CursorP(j,3);
        printf("%c",p_Blocks2);
        CursorP(j,0);
        printf("%c",p_Blocks2);
        CursorP(j,24);
        printf("%c",p_Blocks2);
    }
    for(i=0;i<24;i++)
    {
        CursorP(0,i);
        printf("%c",p_Blocks);
        CursorP(79,i);
        printf("%c",p_Blocks);
    }
    CursorP(30,1);
    printf("KACAMAK");
    return;
}

//oyun sabit ekranini yazdırma

void clearOld()
{
    CursorP(positionX,positionY);
    printf(" ");
}

//cursor onceki koordinatini silen fonksiyon

void controllerCall(int press)
{
    CursorP(positionX,positionY);
    clearOld();
    hareketyon = press;
    switch (press)
    {
    case press_right:
        if (positionX+1 < maxX)
        {
           ++positionX;
        }
        else
        {
            positionX = 1;

            if(game_mod == 1)
            {
                block();
                myScore+=5;
                CursorP(50,1);
                printf("            ");
                printf("SKOR: %d",myScore);
            }
            else
            {
                myScore-=3;
                CursorP(50,1);
                printf("            ");
                printf("SKOR: %d",myScore);
            }

        };
        break;
    case press_down:
        if (positionY+1 < maxY)
        {
            ++positionY;
        }
        else
        {
            positionY = 4;
            if(game_mod==1)
            {
                block();
                myScore+=5;
                CursorP(50,1);
                printf("            ");
                printf("SKOR: %d",myScore);
            }
            else
            {
                myScore-=3;
                CursorP(50,1);
                printf("            ");
                printf("SKOR: %d",myScore);
            }

        };
        break;
    case press_left:
        if ((positionX-1) >= 1)
        {
            --positionX;
        }
        else
        {
            positionX = maxX-1;
            if(game_mod==1)
            {
                block();
                myScore+=5;
                CursorP(50,1);
                printf("            ");
                printf("SKOR: %d",myScore);
            }
            else
            {
                myScore-=3;
                CursorP(50,1);
                printf("            ");
                printf("SKOR: %d",myScore);
            }

        };
        break;
    case press_up:
        if ((positionY-1) >= 4)
        {
            --positionY;
        }
        else
        {
            positionY = 23;
            if(game_mod==1)
            {
                block();
                myScore+=5;
                CursorP(50,1);
                printf("            ");
                printf("SKOR: %d",myScore);
            }
            else
            {
                myScore-=3;
                CursorP(50,1);
                printf("            ");
                printf("SKOR: %d",myScore);
            }

        };
        break;
    }
    CursorP(positionX,positionY);
    printf("O");
    collisioncontrol();
}

//tuslara basınca ne olacagini kontrol eden fonksiyon

void controller()
{

    system("cls");
    frame();
    CursorP(positionX,positionY);
    printf("O");
    time_t now;
    struct tm *tm;

    while(1)
    {
    now = time(0);
    tm = localtime(&now);

    if(_kbhit())
        {
        char press;
        press = getch();

            if (press==-32)
            {
                press = getch();
                if (press==press_left || press==press_down || press==press_right || press==press_up)
                {
                    controllerCall(press);
                }
            } else if (press=='p') {
                getch();
            }
        }
        else
        {
            controllerCall(hareketyon);
            if(game_mod==1)
            {
                if (tm->tm_sec%5==0)
                {
                    block();
                    myScore+=2;
                    CursorP(50,1);
                    printf("              ");
                    printf("SKOR: %d",myScore);

                }
            }
            else if(game_mod==2)
            {
                movable_blocks();
                collisioncontrol();
                myScore+=1;
                CursorP(50,1);
                printf("              ");
                printf("SKOR: %d",myScore);



            }
            Sleep(75);

        }
    }
}

//anlik kontrol yapan fonsiyon

int main()
{
    settings();
    home_screen();

    return 0;
}

//ana fonksiyon
