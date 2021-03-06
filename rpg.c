#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

difi = 2;

enum{ESPADA=1, CAJADO, ADAGAS};
enum{FALSE, TRUE};
typedef enum{ATACAR=1, MAGIA=2, MEDITAR=3, POCAO=4} Acao;
typedef enum{GUERREIRO, AGUA, FOGO, VENTO, TERRA, ASSASINO} Elemento;

typedef struct{
    char nome[200];
    char arma[10];
    char elem[10];
    int pv;
    int ataque;
    int defesa;
    int magia;
    int velocidade;
    int pocoes;
    int level;
    int pvmax;
    Elemento tipo;
} Lutador;

int main (int argc, char* argv[]);
void menu();
int combate(Lutador player, Lutador pc);
int danoPC (Lutador la, Lutador ld);
int danoplayer (Lutador la, Lutador ld, int turno);
int cursorsn(int op, Lutador *p1);
int cursor2(int op, Lutador *p1);
int cursor3(int op);
int cursor4(int op);
int cursorclasse(int op);
void desenhovelho();
void levelup(int xp, Lutador* p1);


int danoplayer (Lutador la, Lutador ld, int turno)
{
    Acao opcao;
    int dano, critico;
    srand(time(NULL));

    int selecionado=1;
    char key[4][16], key2, pow;

    comabatezin:

    selecionado=1;
    strcpy(key[0], "> ");
    strcpy(key[1], "  ");
    strcpy(key[2], "  ");
    strcpy(key[3], "  ");
    pow=1;


    while(pow!=13)
    {
        printf("\n-------------------------------------------------------------\n                 TURNO %d              \n-------------------------------------------------------------\n", turno);
        printf("\n------------------------------------------");
        printf("\n    %s - Level %d\n", la.nome, la.level);
        printf("    %dHP / %dHP      Possui X%d pocao\n", la.pv, la.pvmax, la.pocoes);
        printf("------------------------------------------");

        printf("\n------------------------------------------");
        printf("\n    %s - Level %d\n", ld.nome, ld.level);
        printf("    %dHP / %dHP      \n", ld.pv, ld.pvmax);
        printf("------------------------------------------\n");

        if(la.pocoes == 0)
        {
            printf("\n%s, Qual sua acao:\n", la.nome);
            printf("\n %sATACAR", key[0]);
            printf("\n %sMAGIA", key[1]);
            printf("\n %sMEDITAR", key[2]);
            printf("\n X TOMAR POCAO DE VIDA\n");

            pow = getch();
            key2= 0;
            if(pow ==-32)
            {
                key2 = getch();
            }
            else
            {
                continue;
            }
            if(key2 == 80)
            {
                selecionado++;
            }
            else if(key2 == 72)
            {
                selecionado--;
            }


            if(selecionado < 1)
            {
                selecionado = 1;
            }
            if(selecionado > 3)
            {
                selecionado = 3;
            }
            key[0][0] = ' ';
            key[1][0] = ' ';
            key[2][0] = ' ';
            key[selecionado-1][0] = '>';

            system("cls");
        }
        else
        {
            printf("\n%s, Qual sua acao:\n", la.nome);
            printf("\n %sATACAR", key[0]);
            printf("\n %sMAGIA", key[1]);
            printf("\n %sMEDITAR", key[2]);
            printf("\n %sTOMAR POCAO DE VIDA\n", key[3]);

            pow = getch();
            key2= 0;
            if(pow ==-32)
            {
                key2 = getch();
            }
            else
            {
                continue;
            }
            if(key2 == 80)
            {
                selecionado++;
            }
            else if(key2 == 72)
            {
                selecionado--;
            }


            if(selecionado < 1)
            {
                selecionado = 1;
            }
            if(selecionado > 4)
            {
                selecionado = 4;
            }
            key[0][0] = ' ';
            key[1][0] = ' ';
            key[2][0] = ' ';
            key[3][0] = ' ';
            key[selecionado-1][0] = '>';

            system("cls");
        }
    }

    opcao = selecionado;

    switch(opcao)
    {
    case ATACAR:
        dano = la.ataque - ld.defesa;
        if (dano <=0)
        {
            dano = 5;
        }
        break;
    case MAGIA:
        dano = la.magia - ld.magia;
        if (dano <=0)
        {
            dano = 5;
        }
        switch (la.tipo)
        {
        case AGUA:
            if (ld.tipo == FOGO)
            {
                dano = dano*2;
                printf("\nSuper efetivo!\n");
            }
            if (ld.tipo == TERRA)
            {
                dano = dano/2;
                printf("\nNao foi efetivo...\n");
            }
            break;
        case FOGO:
            if (ld.tipo == VENTO)
            {
                dano = dano*2;
                printf("\nSuper efetivo!\n");
            }
            if (ld.tipo == AGUA)
            {
                dano = dano/2;
                printf("\nNao foi efetivo...\n");
            }
            break;
        case VENTO:
            if (ld.tipo == TERRA)
            {
                dano = dano*2;
                printf("\nSuper efetivo!\n");
            }
            if (ld.tipo == FOGO)
            {
                dano = dano/2;
                printf("\nNao foi efetivo...\n");
            }
            break;
        case TERRA:
            if (ld.tipo == AGUA)
            {
                dano = dano*2;
                printf("\nSuper efetivo!\n");
            }
            if (ld.tipo == VENTO)
            {
                dano = dano/2;
                printf("\nNao foi efetivo...\n");
            }
            break;
        }
        break;
    case MEDITAR:
        return -1;
        break;
    case POCAO:
        return -2;
        break;
    }

    critico = rand()%10;
    if (critico == 0)
    {
        dano = dano*2;
        printf("\n--------------------------------------------------\n              ACERTO CRITICO!              \n--------------------------------------------------\n");
    }
    return dano;
}

int danoPC (Lutador la, Lutador ld)
{
    Acao opcao;
    int dano, critico, errar;

    srand(time(NULL));

    dano = la.ataque - ld.defesa;
    if (dano <=0)
    {
        dano = 5;
    }

    critico =  rand()%10;
    errar = rand()%10;
    if (critico == 0 && errar != 0)
    {
        dano = dano*2;
        printf("\n--------------------------------------------------\n              ACERTO CRITICO!              \n--------------------------------------------------\n");
    }
    if (errar == 0)
    {
        dano = 0;
    }
    return dano;
}

int combate(Lutador player, Lutador pc)
{
    int resultado;
    int vida_antes, dif, turno = 1;

    player.pocoes=5;

    while(player.pv >0 && pc.pv >0)
    {

        if (player.velocidade > pc.velocidade)
        {
            resultado = danoplayer(player,pc, turno);
            if (resultado >= 0)
            {
                pc.pv = pc.pv - resultado;
                printf("\n> %s causou %d de dano em %s\n", player.nome, resultado, pc.nome);
            }
            if (resultado == -1)
            {
                if (player.tipo == GUERREIRO)
                {
                    player.ataque = player.ataque + 5;
                }
                if (player.tipo == ASSASINO)
                {
                    player.ataque = player.ataque + 2;
                }
                else
                {
                    player.magia == player.magia + 5;
                }
                printf("\n> %s esta ficando mais forte...\n", player.nome);
            }
            if (resultado == -2)
            {
                vida_antes = player.pv;
                player.pv = player.pv + 100;
                dif = 100;

                if (player.pv>player.pvmax)
                {
                    player.pv = player.pvmax;
                    dif = player.pvmax-vida_antes;
                }

                player.pocoes = player.pocoes-1;
                printf("\n> %d de vida recuperado, agora voce tem X%d pocao\n", dif, player.pocoes);
            }
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");

            if(player.pv<=0 || pc.pv<=0)
            {
                return player.pv;
            }

            if(player.tipo == ASSASINO)
            {
                printf("\n\n -- %s como assassino, pode agir novamente --\n\n", player.nome);
                printf("\nPressione ENTER para continuar...\n");
                getch();
                system("cls");
                resultado = danoplayer(player,pc, turno);
                if (resultado >= 0)
                {
                    pc.pv = pc.pv - resultado;
                    printf("\n> %s causou %d de dano em %s\n", player.nome, resultado, pc.nome);
                }
                if (resultado == -1)
                {
                    player.ataque = player.ataque + 2;
                    printf("\n> %s esta ficando mais forte...\n", player.nome);
                }
                if (resultado == -2)
                {
                    vida_antes = player.pv;
                    player.pv = player.pv + 100;
                    dif = 100;
                    if (player.pv>player.pvmax)
                    {
                        player.pv = player.pvmax;
                        dif = player.pvmax-vida_antes;
                    }
                    player.pocoes = player.pocoes-1;
                    printf("\n> %d de vida recuperado, agora voce tem X%d pocao\n", dif, player.pocoes);
                }

                printf("\nPressione ENTER para continuar...\n");
                getch();
                system("cls");

                if(player.pv<=0 || pc.pv<=0)
                {
                    return player.pv;
                }
            }

            if(player.pv<=0 || pc.pv<=0)
            {
                return player.pv;
            }

            printf("\n-------------------------------------------------------------\n                 TURNO %d              \n-------------------------------------------------------------\n", turno);
            printf("\n------------------------------------------");
            printf("\n    %s - Level %d\n", player.nome, player.level);
            printf("    %dHP / %dHP      Possui X%d pocao\n", player.pv, player.pvmax, player.pocoes);
            printf("------------------------------------------");

            printf("\n------------------------------------------");
            printf("\n    %s - Level %d\n", pc.nome, pc.level);
            printf("    %dHP / %dHP      \n", pc.pv, pc.pvmax);
            printf("------------------------------------------\n");

            resultado = danoPC(pc,player);

            if (resultado > 0)
            {
                player.pv = player.pv - resultado;
                printf("\n> %s causou %d de dano em %s\n", pc.nome, resultado, player.nome);
            }
            if(resultado==0)
            {
                printf("\n> Oops... %s errou o ataque em %s\n", pc.nome, player.nome);
            }
            if (resultado == -1)
            {
                if (pc.tipo == GUERREIRO)
                {
                    pc.ataque = pc.ataque+5;
                }
                if (player.tipo == ASSASINO)
                {
                    player.ataque = player.ataque + 2;
                }
                else
                {
                    pc.magia = pc.magia+5;
                }
                printf("\n> %s esta ficando mais forte...\n", pc.nome);
            }

            printf("\n-----------------------------------------------------------\n             FIM DO TURNO %d              \n-----------------------------------------------------------\n", turno);
            turno = turno +1;
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");

            if(player.pv<=0 || pc.pv<=0)
            {
                return player.pv;
            }
        }

        if (pc.velocidade > player.velocidade)
        {
            printf("\n-------------------------------------------------------------\n                 TURNO %d              \n-------------------------------------------------------------\n", turno);

            printf("\n------------------------------------------");
            printf("\n    %s - Level %d\n", player.nome, player.level);
            printf("    %dHP / %dHP      Possui X%d pocao\n", player.pv, player.pvmax, player.pocoes);
            printf("------------------------------------------");

            printf("\n------------------------------------------");
            printf("\n    %s - Level %d\n", pc.nome, pc.level);
            printf("    %dHP / %dHP      \n", pc.pv, pc.pvmax);
            printf("------------------------------------------\n");

            resultado = danoPC(pc,player);

            if (resultado > 0)
            {
                player.pv = player.pv - resultado;
                printf("\n> %s causou %d de dano em %s\n", pc.nome, resultado, player.nome);
            }
            if(resultado==0)
            {
                printf("\n> Oops... %s errou o ataque em %s\n", pc.nome, player.nome);
            }

            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");

            if(player.pv<=0 || pc.pv<=0)
            {
                return player.pv;
            }

            resultado = danoplayer(player,pc, turno);

            if (resultado >= 0)
            {
                pc.pv = pc.pv - resultado;
                printf("\n> %s causou %d de dano em %s\n", player.nome, resultado, pc.nome);
            }
            if (resultado == -1)
            {
                if (player.tipo == GUERREIRO)
                {
                    player.ataque = player.ataque + 5;
                }
                if (player.tipo == ASSASINO)
                {
                    player.ataque = player.ataque + 2;
                }
                else
                {
                    player.magia == player.magia + 5;
                }
                printf("\n> %s esta ficando mais forte...\n", player.nome);
            }
            if (resultado == -2)
            {
                vida_antes = player.pv;
                player.pv = player.pv + 100;
                dif = 100;

                if (player.pv>player.pvmax)
                {
                    player.pv = player.pvmax;
                    dif = player.pvmax-vida_antes;
                }

                player.pocoes = player.pocoes-1;
                printf("\n> %d de vida recuperado, agora voce tem X%d pocao\n", dif, player.pocoes);
            }

            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");

            if(player.pv<=0 || pc.pv<=0)
            {
                return player.pv;
            }

            if(player.tipo == ASSASINO)
            {
                printf("\n\n -- %s como assassino, pode agir novamente --\n\n", player.nome);
                printf("\nPressione ENTER para continuar...\n");
                getch();
                system("cls");
                resultado = danoplayer(player,pc, turno);
                if (resultado >= 0)
                {
                    pc.pv = pc.pv - resultado;
                    printf("\n> %s causou %d de dano em %s\n", player.nome, resultado, pc.nome);
                }
                if (resultado == -1)
                {
                    player.ataque = player.ataque + 2;
                    printf("\n> %s esta ficando mais forte...\n", player.nome);
                }
                if (resultado == -2)
                {
                    vida_antes = player.pv;
                    player.pv = player.pv + 100;
                    dif = 100;
                    if (player.pv>player.pvmax)
                    {
                        player.pv = player.pvmax;
                        dif = player.pvmax-vida_antes;
                    }
                    player.pocoes = player.pocoes-1;
                    printf("\n> %d de vida recuperado, agora voce tem X%d pocao\n", dif, player.pocoes);
                }

                if(player.pv<=0 || pc.pv<=0)
                {
                    return player.pv;
                }
            }

            printf("\n-----------------------------------------------------------\n             FIM DO TURNO %d              \n-----------------------------------------------------------\n", turno);
            turno = turno +1;
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");

            if(player.pv<=0 || pc.pv<=0)
            {
                return player.pv;
            }
        }
    }
}

void menu()
{
    int menu, coiso, difinova, selecionado=1, selecionado2=1;
    char key[4][16], key2, pow, pow2, key3, keyy[4][16];

    menuzao:
    selecionado=1;
    strcpy(key[0], "> ");
    strcpy(key[1], "  ");
    strcpy(key[2], "  ");
    pow=1;

    coiso = 0;

    while(pow != 13)
    {
        system("cls");
        printf("\n\n      __  __   ______   _   _   _    _          \n");
        printf("     |  \\/  | |  ____| | \\ | | | |  | |        \n");
        printf("     | \\  / | | |__    |  \\| | | |  | |        \n");
        printf("     | |\\/| | |  __|   |     | | |  | |        \n");
        printf("     | |  | | | |____  | |\\  | | |__| |        \n");
        printf("     |_|  |_| |______| |_| \\_|  \\____/         \n");


        if(difi ==1)
        {
            printf("\n              MODO: FACIL");
        }

        if(difi ==2)
        {
            printf("\n              MODO: NORMAL");
        }

        if(difi ==3)
        {
            printf("\n              MODO: DIFICL");
        }

        printf("\n\n         %s INICIAR", key[0]);
        printf("\n         %s REGRAS", key[1]);
        printf("\n         %s ALTERAR DIFICULDADE\n", key[2]);

        pow = getch();
        key2 = 0;
        if(pow ==-32)
        {
            key2 = getch();
        }
        else
        {
            continue;
        }
        if(key2 == 80)
        {
            selecionado++;
        }
        else if(key2 == 72)
        {
            selecionado--;
        }


        if(selecionado < 1)
        {
            selecionado = 1;
        }
        if(selecionado > 3)
        {
            selecionado = 3;
        }
        key[0][0] = ' ';
        key[1][0] = ' ';
        key[2][0] = ' ';
        key[selecionado-1][0] = '>';

    }

    if(selecionado ==2)
    {
        system("cls");
        dificultin:
        printf("\nREGRAS:\n\nFaca suas escolhas e baseadas nelas o jogo se desenvolvera.\n\nNao ultilize espacos no nome, o jogo ira bugar.\n\n\n");
        printf("\nCOMBATE:\n\nBatalhas em turnos, o mais rapido comeca, assassinos agem duas vezes, pocoes curam ate 100 de HP.\n\nAo meditar, seus atributos sao melhorados SOMENTE durante aquele combate!\nSua vida e ferimentos sao totalmente recuperada ao final do combate se vitorioso.\n\nCaso voce seja surpreendido, seu inimigo comecara o combate, e vice-versa\n\nCada fim de combate voce upa de level e pode melhorar seus atributos.\n");
        printf("\n\n\nElementos possuem vantagens sobre outros:\n");
        printf("\nTERRA > AGUA > FOGO > AR > TERRA\n");
        printf("\n\n\nPressione ENTER para VOLTAR\n");
        getch();
        goto menuzao;
    }
    if(selecionado ==3)
    {
        selecionado2=1;
        strcpy(keyy[0], "> ");
        strcpy(keyy[1], "  ");
        strcpy(keyy[2], "  ");
        pow2=1;

        while(pow2 != 13)
        {
            system("cls");
            printf("\n      Escolha a dificuldade:\n");
            printf("\n       %sFACIL", keyy[0]);
            if(difi ==1)
            {
                printf(" (escolhida)");
            }
            printf("\n       %sNORMAL", keyy[1]);
            if(difi ==2)
            {
                printf(" (escolhida)");
            }
            printf("\n       %sDIFICL", keyy[2]);
            if(difi ==3)
            {
                printf(" (escolhida)");
            }
            printf("\n");

            pow2 = getch();
            key3 = 0;
            if(pow2 ==-32)
            {
                key3 = getch();
            }
            else
            {
                continue;
            }
            if(key3 == 80)
            {
                selecionado2++;
            }
            else if(key3 == 72)
            {
                selecionado2--;
            }


            if(selecionado2 < 1)
            {
                selecionado2 = 1;
            }
            if(selecionado2 > 3)
            {
                selecionado2 = 3;
            }
            keyy[0][0] = ' ';
            keyy[1][0] = ' ';
            keyy[2][0] = ' ';
            keyy[selecionado2-1][0] = '>';
        }

        switch(selecionado2)
        {
        case 1:
            difi = 1;
            break;
        case 2:
            difi = 2;
            break;
        case 3:
            difi = 3;
            break;
        }
        goto menuzao;
    }
    system("cls");
}


void levelup(int xp, Lutador* p1)
{

    int bomba, i, b, c, d; //LETRAS SERVEM PRA RECUPERAR ATRIBUTOS
    char respostinha=2;
    int selecionado, selecionado2;
    char key[5][16], key2, pow;
    char key3[5][16], key4, pow2;


    b=p1->defesa;
    c=p1->ataque;
    d=p1->magia;
    p1->level = p1->level + xp;


    while(respostinha==2)
    {

        strcpy(key[0], "> ");
        strcpy(key[1], "  ");
        strcpy(key[2], "  ");

        pow=1;
        selecionado=1;

        p1->defesa=b;
        p1->ataque=c;
        p1->magia=d;

        for(i=0;i<xp;i++)
        {
            strcpy(key[0], "> ");
            strcpy(key[1], "  ");
            strcpy(key[2], "  ");

            pow=1;
            selecionado=1;

            while(pow != 13)
            {
                printf("\n  Voce ganhou %d level(s)!", xp);
                printf("\n\n        Escolha um atributo para aumentar em 5:\n", xp);
                printf("        %sATAQUE: %d\n",  key[0], p1->ataque);
                printf("        %sDEFESA: %d\n",  key[1], p1->defesa);
                printf("        %sMAGIA: %d\n", key[2], p1->magia);

                pow = getch();

                key2 = 0;
                if(pow ==-32)
                {
                key2 = getch();
                }
                else
                {
                    system("cls");
                    continue;
                }
                if(key2 == 80)
                {
                    selecionado++;
                }
                else if(key2 == 72)
                {
                    selecionado--;
                }

                if(selecionado < 1)
                {
                    selecionado = 1;
                }
                if(selecionado > 3)
                {
                    selecionado = 3;
                }

                key[0][0] = ' ';
                key[1][0] = ' ';
                key[2][0] = ' ';
                key[selecionado-1][0] = '>';

                system("cls");
            }

            bomba=selecionado;

            switch(bomba)
            {
            case 1:
                p1->ataque = p1->ataque + 5;
                break;
            case 2:
                p1->defesa = p1->defesa + 5;
                break;
            case 3:
                p1->magia = p1->magia + 5;
                break;
            }
        }

        strcpy(key3[0], "> ");
        strcpy(key3[1], "  ");

        pow2=1;
        selecionado2=1;

        while(pow2 != 13)
            {
                printf("\n  Novos atributos:\n\n");
                printf("        LEVEL: %d\n", p1->level);
                printf("        ATAQUE: %d\n", p1->ataque);
                printf("        DEFESA: %d\n", p1->defesa);
                printf("        MAGIA: %d\n", p1->magia);

                printf("\nConfirma?\n");
                printf("\n   -------------------------------------------\n");
                printf("   |       %sSIM             %sNAO           |", key3[0], key3[1]);
                printf("\n   -------------------------------------------\n");

                pow2 = getch();

                key4 = 0;
                if(pow2 ==-32)
                {
                key4 = getch();
                }
                else
                {
                    system("cls");
                    continue;
                }
                if(key4 == 77)
                {
                    selecionado2++;
                }
                else if(key4 == 75)
                {
                    selecionado2--;
                }

                if(selecionado2 < 1)
                {
                    selecionado2 = 1;
                }
                if(selecionado2 > 2)
                {
                    selecionado2 = 2;
                }

                key3[0][0] = ' ';
                key3[1][0] = ' ';
                key3[selecionado2-1][0] = '>';

                system("cls");
            }

        respostinha = selecionado2;

        system("cls");
    }
}

void desenhovelho()
{
    printf("\n+---------------------------------------------------------------+\n                     O VELHO ESTRANHO              \n+---------------------------------------------------------------+\n");
    printf("\n              ---,_          ,\n");
    printf("                _>   `'-.  .--'/\n");
    printf("           .--'` ._      `/   <_\n");
    printf("            >,-' ._'.. ..__ . ' '-.\n");
    printf("          .-'   .'`         `'. '.\n");
    printf("          \\    / >`-.     .-'< \\,'._\ \n");
    printf("          /    ; '-._>   <_.-' ;'._>\n");
    printf("          `>  ,/  /___\\ /___\\ \\_  /\n");
    printf("          `.-|(|  \\o_/  \\o_/  |)|`\n");
    printf("               \\;        \\    ;/\n");
    printf("                \\  .-,   )-.  /\n");
    printf("                 /`  .'-'. `\\ \n");
    printf("                ;_.-`.___.'-.;\n\n");
}


int cursor3(int op)
{
    int selecionado;
    char key[3][16], key2, pow;

    strcpy(key[0], "> ");
    strcpy(key[1], "  ");
    strcpy(key[2], "  ");
    strcpy(key[3], "  ");

    pow=1;
    selecionado=1;

    while(pow != 13)
    {
        if(op==1)
        {
            printf("\nInterrompendo a conversa, um guarda aparece com uma caixa lotada de cantis de agua. Ele da alguns para os prisioneiros que mortos de sede bebem e passam o cantil para outros.\n\n - BEBAM TUDO, NAO TERAO MAIS PRESENTES DEPOIS QUE A VIAGEM COMECAR!!!\n");
            printf("\nSua vez chega, voce bebe a agua?");
            printf("\n   ------------------------------------------------------------------------\n");
            printf("   |     %sBEBER            %sNEGAR          %sCUSPIR NO GUARDA           |", key[0], key[1], key[2]);
            printf("\n   ------------------------------------------------------------------------\n");
        }
        if(op==2)
        {
            printf("\nVoce acorda, sentidos retomados... nao sabe onde esta, so se lembra de apagar no barco. Paredes te cercam, parece ser uma sala... ha um bau no canto da sala.\n");

            printf("\nO que voce faz?");

            printf("\n   ------------------------------------------------------------------------\n");
            printf("   |     %sESPERAR            %sABRIR BAU          %sCHUTAR BAU           |", key[0], key[1], key[2]);
            printf("\n   ------------------------------------------------------------------------\n");
        }
        if(op==3)
        {
            printf("\nVoce segue caminho para a passagem a sua frente e da de cara com uma escadaria. Voce sobe ela e agora parece estar em um tipo de Torre completamente fechada.\nNo topo ha uma sala redonda e nela voce acha um bau\n");
            printf("\nO que deseja fazer:\n");

            printf("\n   ---------------------------------------------------------------------------\n");
            printf("   |       %sABRIR BAU           %sVOLTAR           %sDESARMAR ARMADILHA     |", key[0], key[1], key[2]);
            printf("\n   ---------------------------------------------------------------------------\n");
        }
        if(op==4)
        {
            desenhovelho();

            printf("\n - O mago os transforma em monstros e os coloca para batalhar com todos os outros prisioneiros, um por um!");
            printf("\n\n - Como eu descobri tudo ele me prendeu aqui. Mas idai, voce e o primeiro a me achar!! Hehehe, parece que tem mesmo algo de especial, talvez ate consiga sair daqui.\n");

            printf("\n   ---------------------------------------------------------------------------------------------\n");
            printf("   |       %s - COMO SAIO DAQUI?          %s - SAIR          %s - COMO VOCE DESCOBRIU?         |", key[0], key[1], key[2]);
            printf("\n   ---------------------------------------------------------------------------------------------\n");
        }
        if(op==5)
        {
            desenhovelho();

            printf("\n - Felizmente eu achei este cajado de magia de AGUA!! Que coveniente nao?... Posso te dar, e voce vira um mago de agua! O mago malvado nao vai ter chances... Hehehe\n");

            printf("\n - O que acha, quer? Ein? Aceita vai...\n");
            printf("\n   ---------------------------------------------------------------------------------------------------------------\n");
            printf("   |       %s - ACEITAR CAJADO (VIRAR MAGO)         %s - NEGAR CAJADO         %s - ONDE ARRANJOU UM CAJADO?      |", key[0], key[1], key[2]);
            printf("\n   ---------------------------------------------------------------------------------------------------------------\n");
        }
        if(op==6)
        {
            printf("\nDe repente, voce encosta em algo que com certeza nao era uma parede, nao era dura, mas sim, macia... e aspera...\n");
            printf("Tudo esta muito escuro e voce nao consegue dissernir o que era aquilo.\n");
            printf("\nO que gostaria de fazer?\n");

            printf("\n   ---------------------------------------------------------------------------------------------\n");
            printf("   |       %sATACAR A COISA          %sANALISAR A COISA           %sPERGUNTAR AO VELHO         |", key[0], key[1], key[2]);
            printf("\n   ---------------------------------------------------------------------------------------------\n");
        }

        pow = getch();
        key2 = 0;
        if(pow ==-32)
        {
            key2 = getch();
        }
        else
        {
            system("cls");
            continue;
        }
        if(key2 == 77)
        {
            selecionado++;
        }
        else if(key2 == 75)
        {
            selecionado--;
        }


        if(selecionado < 1)
        {
            selecionado = 1;
        }
        if(selecionado > 3)
        {
            selecionado = 3;
        }
        key[0][0] = ' ';
        key[1][0] = ' ';
        key[2][0] = ' ';
        key[selecionado-1][0] = '>';
        system("cls");
    }
    return selecionado;
}



int cursorclasse(int op)
{
    int selecionado;
    char key[3][16], key2, pow;

    strcpy(key[0], "> ");
    strcpy(key[1], "  ");
    strcpy(key[2], "  ");
    strcpy(key[3], "  ");

    pow=1;
    selecionado=1;

    while(pow != 13)
    {
        printf("\nAo abrir o bau voce encontra varios equipamentos e um bilhete em cima de tudo...\n\nO bilhete dizia: Voce foi escolhido como guerreiro da dungeon, pegue uma arma para sair da sala.\n");
        printf("\nVoce ve 3 armas, elas decidiram sua classe\n");

        printf("\nQual voce escolhe?\n");

        printf("\n %sESPADA -> GUERREIRO\n %sCAJADO -> MAGO\n %sADAGAS -> ASSASINO\n", key[0], key[1], key[2]);

        pow = getch();

        key2 = 0;
        if(pow ==-32)
        {
            key2 = getch();
        }
        else
        {
            system("cls");
            continue;
        }
        if(key2 == 80)
        {
            selecionado++;
        }
        else if(key2 == 72)
        {
            selecionado--;
        }


        if(selecionado < 1)
        {
            selecionado = 1;
        }
        if(selecionado > op)
        {
            selecionado = op;
        }
        key[0][0] = ' ';
        key[1][0] = ' ';
        key[2][0] = ' ';
        key[selecionado-1][0] = '>';
        system("cls");
    }
    return selecionado;
}



int cursor4(int op)
{
    int selecionado;
    char key[4][16], key2, pow;

    strcpy(key[0], "> ");
    strcpy(key[1], "  ");
    strcpy(key[2], "  ");
    strcpy(key[3], "  ");

    pow=1;
    selecionado=1;

    while(pow != 13)
    {
        if(op==1)
        {
            printf("\nAgora voce se encontra no meio da grande sala com o corpo do Minotauro e seu machado estendido no chao. Voce ve corpos espalhados nos cantos da sala...\n");
            printf("E claro, as passagens para a direita e outra a sua frente.\n");

            printf("\nO que quer fazer?\n");
            printf("\n   -------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("   |     %sSEGUIR PARA A PORTA DA FRENTE     %sVASCULHAR MINOTAURO      %sVASCULHAR OS CORPOS       %sSEGUIR PARA A PORTA DA DIREITA         |", key[0], key[1], key[2], key[3]);
            printf("\n   -------------------------------------------------------------------------------------------------------------------------------------------\n");
        }
        if(op==2)
        {
            printf("\nDe repente, voce encosta em algo que com certeza nao era uma parede, nao era dura, mas sim, macia... e aspera...\n");
            printf("Tudo esta muito escuro e voce nao consegue dissernir o que era aquilo.\n");
            printf("\nO que gostaria de fazer?\n");

            printf("\n   ---------------------------------------------------------------------------------------------------------------------\n");
            printf("   |       %sATACAR A COISA          %sANALISAR A COISA            %sVOLTAR AO VELHO              %sACENDER TOCHA      |", key[0], key[1], key[2], key[3]);
            printf("\n   ---------------------------------------------------------------------------------------------------------------------\n");
        }
        if(op==3)
        {
            system("cls");
            printf("\n\n                                           ____     \n");
            printf("   _____________________________________ //--- \\     \n");
            printf("  |_____/_____/_____/_____/_____/_____/_{----  |     \n");
            printf("                                         \\\\____/       \n\n");
            printf("\n\nVoce escolheu o cajado de mago, sabedoria e poder juntos.\n");
            printf("\nEscolha agora seu elemento de conjuracao:\n");

            printf("\n   --------------------------------------------------------------------------\n");
            printf("   |       %sAGUA          %sFOGO            %sAR              %sTERRA      |", key[0], key[1], key[2], key[3]);
            printf("\n   --------------------------------------------------------------------------\n");
        }

        pow = getch();

        key2 = 0;
        if(pow ==-32)
        {
            key2 = getch();
        }
        else
        {
            system("cls");
            continue;
        }
        if(key2 == 77)
        {
            selecionado++;
        }
        else if(key2 == 75)
        {
            selecionado--;
        }


        if(selecionado < 1)
        {
            selecionado = 1;
        }
        if(selecionado > 4)
        {
            selecionado = 4;
        }
        key[0][0] = ' ';
        key[1][0] = ' ';
        key[2][0] = ' ';
        key[3][0] = ' ';
        key[selecionado-1][0] = '>';
        system("cls");
    }
    return selecionado;
}

int cursorsn(int op, Lutador *p1)
{

    int selecionado;
    char key[3][16], key2, pow;

    strcpy(key[0], "> ");
    strcpy(key[1], "  ");
    strcpy(key[2], "  ");
    strcpy(key[3], "  ");

    pow=1;
    selecionado=1;

    while(pow != 13)
    {
        if(op==0)
        {
            printf("\n\n           />_________________________________\n");
            printf("  [########[]_________________________________>\n");
            printf("           \\>\n\n");
            printf("\n\nVoce escolheu a espada, alma e arma de um guerreiro.\n");
            printf("\nSeus atributos sao:\n");
            printf("ARMA: %s\n", p1->arma);
            printf("VIDA: %dHP\n", p1->pv);
            printf("ATAQUE: %d\n", p1->ataque);
            printf("DEFESA: %d\n", p1->defesa);
            printf("MAGIA: %d\n", p1->magia);
            printf("VELOCIDADE: %d\n", p1->velocidade);

            printf("\nConfirma?\n");
            printf("\n   -------------------------------------------\n");
            printf("   |       %sSIM             %sNAO           |", key[0], key[1]);
            printf("\n   -------------------------------------------\n");
        }
        if(op==1)
        {
            printf("\nSeus atributos sao:\n");
            printf("ARMA: %s\n", p1->arma);
            printf("VIDA: %dHP\n", p1->pv);
            printf("ATAQUE: %d\n", p1->ataque);
            printf("DEFESA: %d\n", p1->defesa);
            printf("MAGIA: %d\n", p1->magia);
            printf("ELEMENTO: %s\n", p1->elem);
            printf("VELOCIDADE: %d\n", p1->velocidade);

            printf("\nConfirma?\n");
            printf("\n   -------------------------------------------\n");
            printf("   |       %sSIM             %sNAO           |", key[0], key[1]);
            printf("\n   -------------------------------------------\n");
        }
        if(op==2)
        {
            printf("\n\n       /|_________     _________|\\       \n");
            printf("  [####{|________/     \\________|}####]   \n");
            printf("       \\|                       |/  \n\n");
            printf("\n\nVoce escolheu as adagas de um assassino, furtivas e letais.\n");
            printf("\nSeus atributos sao:\n");
            printf("ARMA: %s\n", p1->arma);
            printf("VIDA: %dHP\n", p1->pv);
            printf("ATAQUE: %d\n", p1->ataque);
            printf("DEFESA: %d\n", p1->defesa);
            printf("MAGIA: %d\n", p1->magia);
            printf("VELOCIDADE: %d\n", p1->velocidade);
            printf("Habilidade extra: ACAO DUPLA\n");

            printf("\nConfirma?\n");
            printf("\n   -------------------------------------------\n");
            printf("   |       %sSIM             %sNAO           |", key[0], key[1]);
            printf("\n   -------------------------------------------\n");
        }

        pow = getch();
        key2 = 0;
        if(pow ==-32)
        {
                key2 = getch();
        }
        else
        {
            system("cls");
            continue;
        }
        if(key2 == 77)
        {
            selecionado++;
        }
        else if(key2 == 75)
        {
            selecionado--;
        }
        if(selecionado < 1)
        {
            selecionado = 1;
        }
        if(selecionado > 2)
        {
            selecionado = 2;
        }
        key[0][0] = ' ';
        key[1][0] = ' ';
        key[selecionado-1][0] = '>';
        system("cls");
    }
    return selecionado;
}


int cursor2(int op, Lutador *p1)
{
    int selecionado;
    char key[3][16], key2, pow;

    strcpy(key[0], "> ");
    strcpy(key[1], "  ");
    strcpy(key[2], "  ");
    strcpy(key[3], "  ");

    pow=1;
    selecionado=1;

    system("cls");

    while(pow != 13)
    {
        if(op==1)
        {
            printf("\nAgora armado voce sai da sala, uma parede de pedra e formada na porta que voce saiu... nao ha como voltar.\n\nVoce segue por um corredor e segue o unico caminho para a esquerda e depois segue novamente o unico caminho a direita.");
            printf("\n\nAo chegar no fim do corredor, voce entra em uma grande sala, com o chao todo rachado e algumas manchas de sangue... \nVoce tambem ve duas saidas, uma do outro lado da sala, e uma a sua direita\n");

            printf("\nPara onde voce vai?");
            printf("\n   ------------------------------------------------------------------\n");
            printf("   |       %sPORTA OUTRO LADO          %sPORTA DA DIREITA           |", key[0], key[1]);
            printf("\n   ------------------------------------------------------------------\n");
        }
        if(op==2)
        {
            printf("\nVoce segue caminho para a passagem a sua frente e da de cara com uma escadaria. Voce sobe ela e agora parece estar em um tipo de Torre completamente fechada.\nNo topo ha uma sala redonda e nela voce acha um bau\n");
            printf("\nO que deseja fazer:\n");

            printf("\n   ------------------------------------------------\n");
            printf("   |       %sABRIR BAU           %sVOLTAR          |", key[0], key[1]);
            printf("\n   ------------------------------------------------\n");
        }
        if(op==3)
        {
            printf("\nVasculhando o minotauro voce nao acha nada de util, mas seu machado esta em perfeito estado.\nOque quer fazer?\n");

            printf("\n   --------------------------------------------------------------\n");
            printf("   |       %sPEGAR MACHADO          %sIGNORAR MACHADO           |", key[0], key[1]);
            printf("\n   --------------------------------------------------------------\n");
        }
        if(op==4)
        {
            printf("\nQuando voce chega mais ou menos no meio desse corredor, voce sente uma presenca estranha, um incomodo, parece que ha algo de estranho nas paredes ao seu redor.\n");
            printf("\nO que gostaria de fazer?\n");
            printf("\n   --------------------------------------------------------------\n");
            printf("   |       %sSEGUIR EM FRENTE         %sTOCAR PAREDES           |", key[0], key[1]);
            printf("\n   --------------------------------------------------------------\n");
        }
        if(op==5)
        {
            desenhovelho();
            printf("\n - Ah sim... voce! %s, estou correto? Hehehe que coincidencia, queria te contar uma coisa!\n\n - Gostaria de saber porque esta aqui, %s? Pois bem, eu descobri tudo!\n", p1->nome, p1->nome);
            printf("\n   -----------------------------------------------------------------------\n");
            printf("   |      %s - QUERO SABER!       %s - VOCE E LOUCO, SO FALA BOBAGEM!    |", key[0], key[1]);
            printf("\n   -----------------------------------------------------------------------\n");
        }
        if(op==6)
        {
            desenhovelho();
            printf("\n - Sim sim... Eu sei... O velho mago! Ele e o culpado de tudo, isso aqui e um campo de testes dele, e estes monstros... eles sao na verdade outros prisioneiros!\n");

            printf("\n   ---------------------------------------------------------\n");
            printf("   |        %s - QUE MAGO E ESSE?        %s - SAIR         |", key[0], key[1]);
            printf("\n   ---------------------------------------------------------\n");
        }
        if(op==7)
        {
            desenhovelho();

            printf("\n - A saida que voce procura nao existe ela e uma armadilha, os prisioneiros que chegam la sao esmagados por espinhos gigantes.");
            printf("\n\n - Voce deve seguir para sala do mago E DERROTA-LO!! Hehehehehehe... So assim vai escapar daqui... eu acho...\n");

            printf("\n   ----------------------------------------------------------\n");
            printf("   |      %s - COMO DERROTO O MAGO?        %s - SAIR        |", key[0], key[1]);
            printf("\n   ----------------------------------------------------------\n");
        }
        if(op==8)
        {
            desenhovelho();
            printf("\n - Voce questiona demais... Quer ou nao?\n");

            printf("\n   ---------------------------------------------------------------------------\n");
            printf("   |       %s - ACEITAR CAJADO (VIRAR MAGO)        %s - NEGAR CAJADO         |", key[0], key[1]);
            printf("\n   ---------------------------------------------------------------------------\n");
        }
        if(op==9)
        {
            printf("\nDe repente, voce encosta em algo que com certeza nao era uma parede, nao era dura, mas sim, macia... e aspera...\n");
            printf("Tudo esta muito escuro e voce nao consegue dissernir o que era aquilo.\n");
            printf("\nO que gostaria de fazer?\n");

            printf("\n   ---------------------------------------------------------------\n");
            printf("   |       %sATACAR A COISA          %sANALISAR A COISA          |", key[0], key[1]);
            printf("\n   ---------------------------------------------------------------\n");
        }
        if(op==10)
        {
            desenhovelho();
            printf("\n - Ah voce de novo... %s, estou correto? Hehehe O quer comigo...?\n", p1->nome, p1->nome);
            printf("\n   -----------------------------------------------------------------------\n");
            printf("   |      %s - O QUE SABE SOBRE A PAREDE ESTRANHA?          %sVOLTAR     |", key[0], key[1]);
            printf("\n   -----------------------------------------------------------------------\n");
        }

        pow = getch();
        key2 = 0;
        if(pow ==-32)
        {
                key2 = getch();
        }
        else
        {
            system("cls");
            continue;
        }
        if(key2 == 77)
        {
            selecionado++;
        }
        else if(key2 == 75)
        {
            selecionado--;
        }
        if(selecionado < 1)
        {
            selecionado = 1;
        }
        if(selecionado > 2)
        {
            selecionado = 2;
        }
        key[0][0] = ' ';
        key[1][0] = ' ';
        key[2][0] = ' ';
        key[selecionado-1][0] = '>';
        system("cls");
    }
    return selecionado;
}

int main (int argc, char* argv[])
{

    char nome;
    char resp = 2;
    int resultado, classe, vida_nova;
    int vida_antes, dif, agua, bau, bau2, salamino;
    int bilhete = FALSE, machado, minomorto;
    int minomorto1 = FALSE, minomorto2 = FALSE, minomorto3 = FALSE, minomorto4 = FALSE;
    int paredes;
    int esperar=0, chutar=0, dedoquebrado=FALSE, socoforte=FALSE, socofraco=FALSE;
    int resposta1, resposta2, resposta3, resposta4, resposta5;
    int derrotarmago=FALSE, ciclopefogo=FALSE;;
    int barriga, falouvelho=FALSE, analisar=FALSE, falouvelho2=FALSE, falouvelho3=FALSE, falouvelho4=FALSE, cusaovelho=FALSE;
    int resposta11;

    menu();
    printf("\nVoce esta acorrentado, um prisioneiro de guerra, nao sabe como chegou neste ponto, mas nao parece poder piorar...\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    printf("\n - EI VOCE! Andando prisoneiro, cabeca baixa! EM FILA SEUS MERDAS!!!\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    printf("\nSem muita opcao voce segue a fila, varios prisioneiros andam num sol escaldente em direcao a um gigantesco navio, voce de longe ve um mago ao lado de um oficial, mas nada parece fazer mais sentido...\nVoce entra no navio e os guardas te colocam sentado junto aos outros prisioneiros.\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");
    printf("\nSentado ao seu lado um velho estranho te cutuca e pergunta:\n");
    printf("\n              ---,_          ,\n");
    printf("                _>   `'-.  .--'/\n");
    printf("           .--'` ._      `/   <_\n");
    printf("            >,-' ._'.. ..__ . ' '-.\n");
    printf("          .-'   .'`         `'. '.\n");
    printf("          \\    / >`-.     .-'< \\,'._\ \n");
    printf("          /    ; '-._>   <_.-' ;'._>\n");
    printf("          `>  ,/  /___\\ /___\\ \\_  /\n");
    printf("          `.-|(|  \\o_/  \\o_/  |)|`\n");
    printf("               \\;        \\    ;/\n");
    printf("                \\  .-,   )-.  /\n");
    printf("                 /`  .'-'. `\\ \n");
    printf("                ;_.-`.___.'-.;\n\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    printf("\n - E voce esquisitao, parece cabispaixo hehehe... ");


    Lutador p1;

    printf("Qual seu nome? ");
    scanf("%s", &p1.nome);
    printf("\n - Como se eu fosse me lembrar! Hehehe... Bem %s, parece que vamos morrer, nao e mesmo jovem? Hehehe...\n", p1.nome);
    printf("\nPressione ENTER para continuar...\n");
    getch();

    system("cls");

    agua = cursor3(1); // o q fazer cmo copa de agua

    switch(agua)
    {
    case 1:
        printf("\nVoce bebe a agua, nao tinha nada a perder, sua garganta estava realmente muito seca, o sentimento de alivio era gigantesco e rejuvenescente.\n\nMas... voce comeca a se sentir estranho...\n\nOs outros prisioneiros comecam a apagar e cair.\n\nO guarda ri e exala:\n\n - HAHAHA DURMAM VERMES!!\n");
        printf("\nVoce apaga...\n");
        break;
    case 2:
        printf("\nVoce nao bebe a agua, sua garganta estava realmente muito seca, mas voce estava com mau pressentimento, sabia que tinha algo errado. Os outros prisioneiros de repente comecam a apagar e cair, so sobrou voce.\n\nO guarda ri e exala:\n\n - HAHAHA ESPERTINHO, DA PROXIMA VEZ QUE NAO OBEDECER VAI MORRER!!\n");
        printf("\nO guarda te acerta um soco em cheio\n\nVoce apaga...\n");
        socofraco=TRUE;
        break;
    case 3:
        printf("\nVoce nao bebe a agua, sua garganta estava realmente muito seca, mas voce com um lapso de loucura, cospe na cara do guarda.\n\nO guarda grita de raiva:\n\n - SEU MEEEERDAAA MORRRA!!\n");
        printf("\nO guarda te acerta um soco muito forte em cheio\n\nVoce apaga...\n");
        socoforte=TRUE;
        break;
    }
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");
    printf("\nTudo esta preto...\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");

bauzin:

    bau = cursor3(2); // esperar/abrir/chutar

    if(bau == 1)
    {
        if(esperar<2)
        {
            system("cls");
            printf("\nNada Acontece...\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            esperar=esperar+1;
            goto bauzin;
        }
        if(esperar>=2)
        {
            system("cls");
            printf("\nVoce nao cansa de esperar nao?\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            esperar=esperar+1;
            goto bauzin;
        }
    }
    if(bau == 3)
    {
        if(chutar<2)
        {
            system("cls");
            printf("\nVoce parece um retardado chutando um bau...\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            chutar=chutar+1;
            goto bauzin;
        }
        if(chutar==2)
        {
            printf("\nSeu dedo QUEBRA de tanto voce chutar o bau, voce toma 20 DE DANO e PERDE 10 DE VELOCIDADE.\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            dedoquebrado=TRUE;
            chutar=chutar+1;
            goto bauzin;
        }
        if(chutar>2)
        {
            system("cls");
            printf("\nVoce ja nao consegue mais chutar, seu dedo doi.\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            goto bauzin;
        }
    }

    system("cls");

    p1.level=1;

    while(resp == 2)
    {

        classe = cursorclasse(3);

        switch(classe)
        {
        case ESPADA:
            p1.tipo = GUERREIRO;

            strcpy(p1.arma , "Espada");
            strcpy(p1.elem , "Guerreiro");
            p1.pv = 500;
            p1.pvmax = 500;
            p1.ataque = 75;
            p1.defesa = 45;
            p1.magia = 15;
            p1.velocidade = 10;
            system("cls");

            resp = cursorsn(0, &p1);

            break;
        case CAJADO:

            p1.tipo = cursor4(3);

            switch (p1.tipo)
            {
            case AGUA:
                strcpy(p1.elem , "Mago de agua");
                break;
            case FOGO:
                strcpy(p1.elem , "Mago de fogo");
                break;
            case VENTO:
                strcpy(p1.elem , "Mago de ar");
                break;
            case TERRA:
                strcpy(p1.elem , "Mago de terra");
                break;
            }

            strcpy(p1.arma , "Cajado");

            p1.pv = 400;
            p1.pvmax = 400;
            p1.ataque = 25;
            p1.defesa = 30;
            p1.magia = 75;
            p1.velocidade = 30;

            resp = cursorsn(1, &p1);

            break;
        case ADAGAS:
            p1.tipo = ASSASINO;

            strcpy(p1.arma , "Adagas");
            strcpy(p1.elem , "Assassino");

            p1.pv = 400;
            p1.pvmax = 400;
            p1.ataque = 4000;
            p1.defesa = 30;
            p1.magia = 20;
            p1.velocidade = 50;
            system("cls");

            resp = cursorsn(2, &p1);

            break;
        }
        system("cls");
    }


    if(socoforte==TRUE)
    {
        printf("\nPor causa do soco muito forte que levou ao cuspir a agua no guarda, voce tomou 50 de dano...\n");
        p1.pv = p1.pv - 50;
        printf("\nPontos de vida - 50 = %d\n\n", p1.pv);
    }
    if (socofraco==TRUE)
    {
        printf("\n\nPor causa do soco que levou do guarda ao negar a agua, voce tomou 20 de dano...\n");
        p1.pv = p1.pv - 20;
        printf("\nPontos de vida - 20 = %d\n\n", p1.pv);
    }
    if(dedoquebrado==TRUE)
    {
        printf("\n\nComo voce quebrou seu dedo, voce tomou 20 de dano e perdeu 10 pontos de velocidade...\n");
        p1.pv = p1.pv - 20;
        p1.velocidade=p1.velocidade-10;
        printf("\nPontos de vida - 20 = %d\n", p1.pv);
        printf("\nPontos de velocidade - 10 = %d\n", p1.velocidade);
    }
    printf("\nPortanto este e voce:\n\n");
    printf("NOME: %s\n", p1.nome);
    printf("LEVEL: %d\n", p1.level);
    printf("CLASSE: %s\n", p1.elem);
    printf("ARMA: %s\n", p1.arma);
    printf("VIDA: %dHP\n", p1.pv);
    printf("ATAQUE: %d\n", p1.ataque);
    printf("DEFESA: %d\n", p1.defesa);
    printf("MAGIA: %d\n", p1.magia);
    printf("VELOCIDADE: %d\n", p1.velocidade);
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");

    //porta direita ou esquerda
    salamino = cursor2(1, &p1);

    Lutador minotauro;

    switch(salamino)
    {
    case 1:
        printf("\nVoce anda em direcao a porta e no momento que pisa dentro da sala voce ouve um grande estrondo e um urro muito alto...\n\nDe dentro da parede a sua esquerda, sai UM MINOTAURO GIGANTESCO quebrando tudo e parte descontroladamente em sua direcao.\n\n");
        minotauro.ataque= 70;
        minotauro.defesa =20;
        minotauro.magia=0;
        minotauro.pv=300*difi;
        minotauro.pvmax=300*difi;
        minotauro.velocidade=-50;
        minotauro.tipo=GUERREIRO;
        minotauro.level=1*difi;
        strcpy(minotauro.nome , "Minotauro");
        break;
    case 2:
        printf("\nVoce anda em direcao a porta e no momento que chega perto dela voce ouve um grande estrondo e um urro muito alto:\n\n - UUUUUUUOOOOOOOORRRRR!!!!\n\nDe dentro da parede atras de voce, sai UM MINOTAURO GIGANTESO quebrando tudo e parte descontroladamente em sua direcao.\n\nVoce foi surpreendido!\n\n");
        minotauro.ataque= 70;
        minotauro.defesa =20;
        minotauro.magia=0;
        minotauro.pv=300*difi;
        minotauro.pvmax=300*difi;
        minotauro.velocidade=300;
        minotauro.tipo=GUERREIRO;
        minotauro.level=1*difi;
        strcpy(minotauro.nome , "Minotauro");
        break;
    }
    printf("              (     ( \n");
    printf("              \\\\    \\\\\n");
    printf("              ((((()))\n");
    printf("              |o\\ /o)|\n");
    printf("              ( (..)_')\n");
    printf("               (VVVV /\\_\n");
    printf("              ,\\___,/ ' ')\n");
    printf(" ____       (              )\n");
    printf(" \\   \\     ( '.    . )(    )\n");
    printf("  \\   \\    \\.  _.__ ____( .)\n");
    printf("   \\  /\\   .(   .'  /\\  '.  )\n");
    printf("    \\(  \\.-' ( /    \\/    \\)\n");
    printf("     '  ()) _'.-|/\\/\\/\\/\\/\\|\n");
    printf("         '\\ .( |\\/\\/\\/\\/\\/|\n");
    printf("           '((  \\    /\\    /\n");
    printf("           ((((  '.__\\/__.')\n");
    printf("            ((,) /   ((()   )\n");
    printf("              ..-,  (()()   / \n");
    printf("              _//.   ((() ./\n");
    printf("      _____ //,/_____ ((( ', ___\n");
    printf("                       ((  )\n");
    printf("                        / /\n");
    printf("                      _/,/'\n");
    printf("                    /,/,/\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");
    //////COBATE
    vida_nova = combate(p1, minotauro);
    p1.pv = vida_nova;
    if(vida_nova<=0)
    {
        printf("\n\nVoce foi derrotado pelo %s...\n\n", minotauro.nome);
        printf("\n\n                                                                  _               \n");
        printf("                                                                _( (~\\            \n");
        printf("       _ _                        /                            ( \\> > \\       \n");
        printf("   -/~/ / ~\\                     :;                 \\        _  > /(~\\/           \n");
        printf("  || | | /\\ ;\\                   |l      ______     |;      ( \\/    > >           \n");
        printf("  _\\\\)\\)\\)/ ;;;                  `8o __/       \\   d|        \\      //            \n");
        printf(" ///(())(__/~;;\\                   88p;. O\\  _O \\_;oP        (_._/ /         \n");
        printf("(((__   __ \\\\   \\                    `>,% (\\  (\\./)8          ;:'  i          \n");
        printf(")))--`.'-- (( ;,8 \\                 ,;%%%:  ./V^^^V'          ;.   ;.         \n");
        printf("((\\   |   /)) .,88  `: ..,,;;;;,-::::::'_::\\    ||\\         ;[8:   ;         \n");
        printf(" )|  ~-~  |(|(888; ..``'::::888       .  :\\`^^^/,,~--._    |88::  |                 \n");
        printf(" |\\ -===- /|  \\8;; ``:.      oo.            (((          Oo;:;:'  |             \n");
        printf(" |_~-___-~_|   `-\\.   `        `o`           ))         8P""'     ;             \n");
        printf(" ; ~~~~;~~          `--_`.       b`          (         8  ..::;-'          \n");
        printf("   ;      ;              ~ -....  b`                 8. .:;;;''         \n");
        printf("      ;    ;                 `:::. `:::OOO:::::::.`OO' ;;;''                \n");
        printf(" :       ;                     `.       ``::::::''    .'                    \n");
        printf("    ;                           `.   \\_              /              \n");
        printf("  ;       ;                       +:   ~~--  `:'  -';                   \n");
        printf("                                   `:         : .::/                \n");
        printf("      ;                            ;;+_  :::. :..;;;                \n");
        printf("                                   ;;;;;;,;;;;;;;;,;                \n\n");

        printf("\n\n _____   ___  ___  ___ _____   _____  _   _  _____ ______      \n");
        printf("|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | ||  ___|| ___ \\     \n");
        printf("| |  \\// /_\\ \\| .  . || |__   | | | || | | || |__  | |_/ /     \n");
        printf("| | __ |  _  || |\\/| ||  __|  | | | || | | ||  __| |    /      \n");
        printf("| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ /| |___ | |\\ \\      \n");
        printf(" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/ \\____/ \\_| \\_|     \n\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        return 0;
    }
    else
    {
        printf("\nO minotauro foi morto!!!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        levelup(2, &p1);
        printf("\nSua vida maxima aumentou em 100:");

        p1.pv = p1.pvmax+100;
        p1.pvmax = p1.pvmax+100;

        printf("\nVIDA: %dHP\n", p1.pv);
    }
    printf("\nPressione ENTER para continuar...\n");
    getch();

    system("cls");
/////FINAL DO COMABTE


    sala:

    minomorto = cursor4(1); // porta a frente/vasculhar mino/ vasculhar corpos/ porta a direita

    if(minomorto == 1 && minomorto3==TRUE)
    {
        system("cls");
        printf("\nVoce ja fez isso\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        goto sala;
    }
    if(minomorto == 2 && minomorto2==TRUE)
    {
        system("cls");
        printf("\nVoce ja vasculhou o minotauro\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        goto sala;
    }
    if(minomorto == 3 && minomorto1==TRUE)
    {
        system("cls");
        printf("\nVoce ja vasculhou os corpos\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        goto sala;
    }

    switch(minomorto)
    {
    case 1:
        if(bilhete == FALSE)
        {
            bau2 = cursor2(2, &p1); //abrir bau ou voltar

            switch(bau2)
            {
                case 1:
                    printf("\nQuando abre o bau, voce ouve um barulho:\n\n*CLANK*\n");

                    printf("\nQuatro buracos se abrem nas paredes da sala circular da Torre e varios dardos sao atirados em sua direcao, felizmente os dardos ja nao tinham mais veneno Mas voce sofreu dano.\n");
                    p1.pv = p1.pv - 50;
                    printf("\nPontos de vida - 50 = %d\n", p1.pv);
                    printf("\nVoce ate tenta abrir o bau novamente mas como a armadilha foi ativada, o bau foi trancado.\n");
                    printf("\nPressione ENTER para continuar...\n");
                    getch();
                    system("cls");
                    minomorto3 = TRUE;
                    break;
                case 2:
                    system("cls");
                    minomorto4 = TRUE;
                    break;
            }
        }
        if(bilhete == TRUE)
        {
            printf("\n - Talvez seja este o bau que foi mencionado no bilhete...\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");

            bau2 = cursor3(3); // abrir/ voltar/ desarmar

            switch(bau2)
            {
                case 1:
                    printf("\nQuando abre o bau, voce ouve um barulho\n\n*CLANK*\n");
                    printf("\nQuatro buracos se abrem nas paredes da sala circular da Torre e varios dardos sao atirados em sua direcao, felizmente os dardos ja nao tinham mais veneno Mas voce sofreu dano.\n");
                    p1.pv = p1.pv - 50;
                    printf("\nPontos de vida - 50 = %d\n", p1.pv);
                    printf("\n\nVoce se pegunta porque nao desarmou a armadilha que o bilhete havia avisado...\nVoce ate tenta abrir o bau novamente mas como a armadilha foi ativada, o bau foi trancado.\n");
                    printf("\nPressione ENTER para continuar...\n");
                    getch();
                    system("cls");
                    minomorto3 = TRUE;
                    break;
                case 2:
                    system("cls");
                    minomorto4 = TRUE;
                    break;
                case 3:
                    printf("\nComo voce viu no bilhete, desconfia que este seja o bau que o homem morto escreveu, portanto procura por uma alavanca ou botao para desativar a armadilha\n");
                    printf("Atras do bau voce encontra uma alavanca, ao aciona-la voce ouvi um barulho\n\n*CLANK*\n\nParece que a armadilha foi desativada\n");
                    printf("\nPressione ENTER para continuar...\n");
                    getch();
                    printf("\nNo bau voce acha uma armadura de couro, esta lhe dara um bonus de 20 de defesa.\n");
                    p1.defesa = p1.defesa + 20;
                    printf("\nPontos de defesa + 20 = %d\n", p1.defesa);
                    printf("\nPressione ENTER para continuar...\n");
                    getch();
                    system("cls");
                    minomorto3 = TRUE;
                    break;
            }
        }
        printf("\nVoce esta de volta a sala...\n");
        goto sala;
        break;
    case 2:

        machado = cursor2(3, &p1); //pegar machado ou ignorar

        switch(machado)
        {
        case 1:
            if(p1.tipo == GUERREIRO)
            {
                printf("\nVoce consegue usar perfeitamente o machado, e voce se sente mais forte so de empunha-lo.\n");
                p1.ataque = p1.ataque + 20;
                printf("\nPontos de ataque + 20 = %d\n", p1.ataque);
                printf("\nPressione ENTER para continuar...\n");
                getch();
                system("cls");
            }
            else
            {
                printf("\nO machado dele parece ser muito forte, mas e grande demais para voce segurar, voce nao consegue nem arrasta-lo pelo chao.\n");
                printf("\nPressione ENTER para continuar...\n");
                getch();
                system("cls");
            }
            minomorto2 = TRUE;
            break;
        case 2:
            system("cls");
            break;
        }
        printf("\nVoce ainda esta na sala...\n");
        goto sala;
        break;
    case 3:
        printf("\nAo vasculhar os corpos voce achou um corpo que estava com dardos no pescoco... E em sua mao havia um bilhete que parecia ter sido escrito antes de sua morte.\n");
        printf("\nNo bilhete dizia: O BAU E UMA ARMADILHA\n");
        bilhete = TRUE;
        minomorto1 = TRUE;
        if(minomorto4==TRUE && minomorto3==FALSE)
        {
            printf("\n - Talvez isso tenha haver com o  bau naquela sala, vou voltar la...\n");
        }
        if(minomorto3==TRUE)
        {
            printf("\n - Devia ter vasculhado os corpos antes...\n");
        }
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        printf("\nVoce ainda esta na sala...\n");
        goto sala;
        break;
    case 4:
        system("cls");
        break;
    }

    printf("\nVoce vai em direcao a porta da direita... Ao passar dela uma parede de pedra e formada atras de voce, nao ha como voltar...");
    printf("\nVoce segue o caminho no corredor estreito que acaba de entrar, as paredes estao cobertas de musgos mas ao mesmo tempo nao parecem muito umidas... estao secas.\n");
    printf("\n - Que tipo de lugar e esse?...\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();


    paredes = cursor2(4, &p1); // seguir em frente ou tocar paredes

    switch(paredes)
    {
    case 1:
        system("cls");
        printf("\n - Melhor nao tocar em nada...\n");
        goto naotocouparede;
        break;
    case 2:
        falouvelho = TRUE;
        printf("\nAo tocar em uma das paredes a sua esquerda, ela se transforma aos poucas em fumaca e comeca a desaparecer... era uma ilusao! A ilusao revela uma pequena sala, onde havia somente um velho no canto.\n");
        printf("\n - Nao acredito...\n");
        break;
    }
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");
    printf("\nEra uma figura conhecida... era o velho que voce conheceu no barco.\n");
    printf("\n              ---,_          ,\n");
    printf("   Z            _>   `'-.  .--'/\n");
    printf("     Z     .--'` ._      `/   <_\n");
    printf("       Z    >,-' ._'.. ..__ . ' '-.\n");
    printf("          .-'   .'`         `'. '.\n");
    printf("          \\    / >`-.     .-'< \\,'._\ \n");
    printf("          /    ; '-._>   <_.-' ;'._>\n");
    printf("          `>  ,/  /   \\ /   \\ \\_  /\n");
    printf("          `.-|(|  \\__/  \\__/  |)|`\n");
    printf("               \\;        \\    ;/\n");
    printf("                \\  .-,   )-.  /\n");
    printf("                 /`  .'-'. `\\ \n");
    printf("                ;_.-`.___.'-.;\n\n");
    printf("\nPressione para acordar o velho...\n");
    getch();
    system("cls");

    desenhovelho();

    printf("\n - OH! Voce me acordou... quem esta ai...?\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");

    resposta1 = cursor2(5, &p1); //qro saber/vc e louco

    system("cls");

    velhin2:

    if(resposta1==1)
    {
        resposta2= cursor2(6, &p1); // que mago/sair

        if(resposta2==1)
        {
            system("cls");
            velhin4:
            resposta3=cursor3(4); //como saio/s/como descobriu

            if(resposta3==1)
            {
                system("cls");

                resposta4=cursor2(7, &p1); // como derroto ele/sair

                if(resposta4==1)
                {
                    derrotarmago=TRUE;
                }
                if(resposta4==2)
                {
                    goto sairvelho;
                }
            }
            if(resposta3==2)
            {
                goto sairvelho;
            }
            if(resposta3==3)
            {
                system("cls");
                desenhovelho();
                printf("\n - NAO E DA SUA CONTA! Hehehe\n");
                printf("\nPressione ENTER para continuar...\n");
                getch();
                system("cls");
                goto velhin4;
            }
        }
        if(resposta2==2)
        {
            goto sairvelho;
        }
    }
    if(resposta1==2)
    {
        desenhovelho();
        printf("\n - Ora ora se nao quer saber entao va! Louco e voce seu... seu... seu bananao! HIHIHI... Morra entao, vamos todos morrer mesmo nao e %s...\n", p1.nome);
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        cusaovelho = TRUE;
        goto naotocouparede;
    }

    sairvelho:

    system("cls");

    desenhovelho();

    if(derrotarmago==FALSE)
    {
        printf("\n - EI EI EI, se nao vai perguntar eu te falo mesmo assim! Hehehe...\n");
    }
    printf("\n - Pra sair daqui voce tem que derrotar o terrivel malignio asqueroso mago... Eu descobri que ele e um mago de fogo, de FOGO!! OU SEJA... SUA FRAQUEZA E AGUA!\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();

    system("cls");

    if(p1.tipo==1)
    {
        desenhovelho();
        printf("\n - Oh... vejo que ja domina a arte da agua... Pois bem, entao nao temos mais o que discutir, va matar aquele mago maldito!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
    }
    else
    {
        resposta5=cursor3(5); // aceitar/negar/onde arranjou o cajado?
    }

tal:
    if(resposta5==1)
    {
        system("cls");
        printf("\n\n                                           ____     \n");
        printf("   _____________________________________ //~~~ \\     \n");
        printf("  |_____/_____/_____/_____/_____/_____/_{~~~~  |     \n");
        printf("                                         \\\\____/       \n\n");
        printf("\nVoce recebeu o CAJADO DE AGUA, agora voce e um mago de agua.\nSeus atributos mudaram, menos sua vida.\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();

        strcpy(p1.elem , "Agua");
        p1.tipo=AGUA;
        p1.ataque = 25;
        p1.defesa = 30;
        p1.magia = 75;
        p1.velocidade=30;
        strcpy(p1.arma , "Cajado");

        printf("\nSeus atributos novos sao:\n");
        printf("ARMA: %s\n", p1.arma);
        printf("VIDA: %dHP\n", p1.pv);
        printf("ATAQUE: %d\n", p1.ataque);
        printf("DEFESA: %d\n", p1.defesa);
        printf("MAGIA: %d\n", p1.magia);
        printf("ELEMENTO: %s\n", p1.elem);
        printf("TIPO 1: %d\n", p1.tipo);
        printf("VELOCIDADE: %d\n", p1.velocidade);
        printf("\nPressione ENTER para continuar...\n");
        getch();

        system("cls");
        desenhovelho();
        printf("\n - Oooh... Ficou bem em voce %s, ou devo lhe chamar de... MAGO %s... Hehehe...\n\n - AGORA ADEUS!\n", p1.nome, p1.nome);
        printf("\nPressione ENTER para continuar...\n");
        getch();
    }
    if(resposta5==2)
    {
        system("cls");
        desenhovelho();
        printf("\n - O que... vo...voce nao quer?! Ehh o...o...ok, ok entao! Hehehe... Boa sorte...\n\n - ADEUS!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
    }
    if(resposta5==3)
    {
        system("cls");
        resposta5=cursor2(8, &p1); //aceitar cajado/negar
        goto tal;
    }
    system("cls");
    printf("\nDepois de terminar de conversar com o velho, voce volta ao corredor e vira a esquerda indo na direcao contraria da sala do Minotauro.\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();

    naotocouparede:

    printf("\nVoce continua em direcao ao final do corredor...\n\n");
    printf("Quanto mais voce anda mais escuro fica, voce nao enxerga mais nada, e so segue em frente. Para se localizar voce anda com suas maos palpando tudo em sua volta, as paredes continuam rugosas e secas.\n");
    printf("A escuridao e total e a unica luz que voce ve e a da sala onde encontrou o velho.\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");

barriguinha:

    if(falouvelho2==FALSE)
    {
        barriga = cursor2(9, &p1); // atacar/analisar
    }
    if(falouvelho2==TRUE && falouvelho3==FALSE)
    {
        barriga = cursor3(6); // atacra/analisar/perguntar ao velho
    }
    if(falouvelho3==TRUE)
    {
        barriga=cursor4(2); // atacra/analisar/velho/tocha
    }

    switch(barriga)
    {
    case 1:
        system("cls");
        printf("\nVoce nao sabe ao certo o que fazer, mas sabe que nao gostou daquela coisa mole... A unica coisa que vem a sua mente e ATACAR!!\n\nVoce mesmo portando uma arma, decide dar um soco ma coisa.");
        printf("\nVoce se concentra, e da um super soco na coisa com toda sua forca. Seu braco afunda naquele monte banhas asquerosa e na mesma hora voce escuta um urro muito alto:\n");
        printf("\n - AAAAAAAAAAAARRRRRRRRRRRRGHH!!!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        printf("\nA coisa que bloqueva a passagem vai para frente liberando o caminho e revela uma sala completamente iluminada, o brilho cega seus olhos por alguns segundos e aos poucos voce consegue ver uma leve silhueta...\n");
        printf("\nA iluminacao depois mostra o que era silhueta...\n");
        if(falouvelho3==TRUE)
        {
            printf("\n - Oh merda... Devia ter acendido a tocha...\n");
        }
        else
        {
            printf("\n - Oh merda... Nao devia ter feito isso...\n");
        }
        printf("\nVoce foi surpreendido!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();

        goto combateciclope;

        break;
    case 2:
        if(analisar==TRUE)
        {
            system("cls");
            printf("\nVoce ja analisou a parede\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            goto barriguinha;
        }

        printf("\nVoce chega perto da coisa, encosta nela e tem novamente as mesmas sensacoes, algo macio e rugoso...\n\n");
        printf("Mas voce sente algo diferente dessa vez, uma repeticao periodica de movimentos, um vai e vem, semelhnte a uma respiracao...\n\n - Parece algo vivo...\n");
        analisar = TRUE;

        if(falouvelho==TRUE)
        {
            printf("\n - Talvez o velho saiba de alguma coisa...\n");
            falouvelho2=TRUE;
            printf("\nPressione ENTER para continuar...\n");
            getch();
        }
        else
        {
            printf("\nPressione ENTER para continuar...\n");
            getch();
        }
        system("cls");
        goto barriguinha;
        break;
    case 3:
        if(falouvelho3==TRUE)
        {
            system("cls");
            printf("\nVoce ja falou com o velho...\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            goto barriguinha;
        }

        if(falouvelho4==TRUE)
        {
            system("cls");
            printf("\nO velho nao quer falar com voce...\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            goto barriguinha;
        }

        system("cls");
        printf("\nVoce volta para a sala onde encontrou o velho, e la estava ele, novamente dormindo...\n");
        printf("\n              ---,_          ,\n");
        printf("   Z            _>   `'-.  .--'/\n");
        printf("     Z     .--'` ._      `/   <_\n");
        printf("       Z    >,-' ._'.. ..__ . ' '-.\n");
        printf("          .-'   .'`         `'. '.\n");
        printf("          \\    / >`-.     .-'< \\,'._\ \n");
        printf("          /    ; '-._>   <_.-' ;'._>\n");
        printf("          `>  ,/  /   \\ /   \\ \\_  /\n");
        printf("          `.-|(|  \\__/  \\__/  |)|`\n");
        printf("               \\;        \\    ;/\n");
        printf("                \\  .-,   )-.  /\n");
        printf("                 /`  .'-'. `\\ \n");
        printf("                ;_.-`.___.'-.;\n\n");
        printf("\nPressione para acordar o velho...\n");
        getch();
        system("cls");

        desenhovelho();

        printf("\n - OH! Voce me acordou... quem esta ai...?\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();

        system("cls");
velhin45:
        desenhovelho();

        if(cusaovelho==TRUE)
        {
            falouvelho4 = TRUE;
            printf("\n - Ah voce de novo... veio me xingar de novo? Vai embora, nao vou te ajudar!\n", p1.nome);
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            printf("Voce voltou para o fim do corredor...\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            goto barriguinha;
        }

        resposta11 = cursor2(10, &p1); //o q sabe sore a parede?

        if(resposta11==1)
        {
            falouvelho3 = TRUE;
            system("cls");
            desenhovelho();
            printf("\n - Ahhh, parede? Hehehe... Nao e parede seu tolo, na verdade e um terrivel ciclope!! Deve ter dormido... Talvez os prisioneiors todos morreram e ele se entediou... Hehehe\n");
            printf("\n - Antes que voce pergunte, use fogo, eles morrem de medo... pelo menos a maioria... Hehehe...\n\n - Tem uma tora de madeira com oleo e um acendedor ali no canto, pode pegar. Agora sai daqui, quero dormir!\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            printf("Voce voltou para o fim do corredor...\n");
            goto barriguinha;
        }
        if(resposta11==2)
        {
            system("cls");
            desenhovelho();
            printf("\n - Oh... tudo bem entao...\n");
            printf("\nPressione ENTER para continuar...\n");
            getch();
            system("cls");
            printf("Voce voltou para o fim do corredor...\n");
            goto barriguinha;
        }
        break;
    case 4:
        system("cls");
        printf("\nMesmo o velho estranho parecer louco, ele parece saber das coisas, e voce acredita nao ter muita opcao. Voce acende a tocha, tudo se ilumina, e a suposta parede e na verdade branca.\n");
        printf("\n - Parece mesmo as costas de um ciclope... E bom aquele velho estar certo!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        printf("\nAos poucos voce se aproxima do suposto ciclope, tentando nao fazer barulho. O corredor comeca a esquentar... Voce se aproxima mais um pouco e por causa do calor a coisa se mexe e solta um resmungo.\n");
        printf("\n - E agora ou nunca...\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        printf("\nVoce se aproxima mais e quando estava bem proximo, ateia fogo na grande parede branca asquerosa, o fogo se espalha e um grito de dor horrendo e escutado:\n");
        printf("\n - AAAAAAAAAAAAAAAAAAHHHHHHHHHHHHRRRRRRRRRRRR!!!!!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        printf("\nO monstro se levanta imediamente, sai correndo pegando fogo, liberando a passagem bloqueda para uma sala toda iluminada.\n");
        printf("\nA sala possui grandes janelas cobertas por uma cortina giante, mesas e moveis velhos e quadros rasgados, parece um palacio abandonado...\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        printf("\nMas nao acaba ai, o monstro, assustado, gritando e ainda pegando fogo, se enrola nas cortinas para apagar as chamas, mas ao tentar se soltar delas acaba tropecando e cai, batento a cabeca no chao...\n");
        printf("\nRecuperado, o monstro se levanta e tira as cortinas de cima de si... Olha pra voce e grita:\n");
        printf("\n - AHHHHHHHHHHH BARG ESMAGA!! BARG MATA!! BARG COM FOOOOOOMEEEE!!!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        ciclopefogo=TRUE;
        goto combateciclope;
        break;
    }

    combateciclope:

    system("cls");
    printf("\nCom toda a certeza do mundo era um ciclope.\n");
    printf("\n           _.............._                               \n");
    printf("        .-''               `-.                               \n");
    printf("      .'                      `.                              \n");
    printf("      /      ___       ___      \\                           \n");
    printf("     |      /   `-...-`   \\      \\                           \n");
    printf("     |      ```-..___..-```      |                           \n");
    printf("     |       _..- .-. -.._       |                           \n");
    printf("  .-.'      `.   ((@))   .'      '.-.                           \n");
    printf(" ( ^ \\        `--.._..-'         / ^ )                           \n");
    printf("  \\  /           .   .           \\  /                           \n");
    printf("  /            .'     '.            \\                           \n");
    printf(" (   \\        (_`-._.-'_)        /   )                           \n");
    printf("  `-' \\       .--.              / `-'                           \n");
    printf("      |      /|__| `-._.'\\      |                           \n");
    printf("      |     |       |__| |     /-.._                           \n");
    printf("  _..-\\     `.--.______.'     |    ``--..__                      \n");
    printf("       \\         .....        |                           \n");
    printf("        `     .'      `.      /                           \n");
    printf("          \\               .'                           \n");
    printf("             `-..___..-`                           \n");
    Lutador Ciclope;
    if(ciclopefogo == TRUE)
    {
        printf("\nEle estava bem queimado e machucado, voce tera que enfrentalo de qualquer jeito, mas aparentemente sera mais facil.\n");
        Ciclope.ataque= 80;
        Ciclope.defesa =30;
        Ciclope.magia=15;
        Ciclope.pv=350*difi;
        Ciclope.pvmax=450*difi;
        Ciclope.velocidade=-50;
        Ciclope.tipo=TERRA;
        Ciclope.level=3*difi;
        strcpy(Ciclope.nome , "Barg, o ciclope");
    }
    else
    {
        printf("\nO ciclope estava furioso, e o soco que voce deu parece ter deixado ele ainda mais bravo...\n");
        Ciclope.ataque= 80;
        Ciclope.defesa =30;
        Ciclope.magia=15;
        Ciclope.pv=450*difi;
        Ciclope.pvmax=450*difi;
        Ciclope.velocidade=1000;
        Ciclope.tipo=TERRA;
        Ciclope.level=3*difi;
        strcpy(Ciclope.nome , "Barg, o ciclope");
    }
    printf("\nPressione ENTER para continuar...\n");
    getch();

    //COMBATE
    system("cls");
    vida_nova = combate(p1, Ciclope);
    p1.pv = vida_nova;
    if(vida_nova<=0)
    {
        printf("\n\nVoce foi derrotado pelo %s...\n", Ciclope.nome);

        printf("\n\n _____   ___  ___  ___ _____   _____  _   _  _____ ______      \n");
        printf("|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | ||  ___|| ___ \\     \n");
        printf("| |  \\// /_\\ \\| .  . || |__   | | | || | | || |__  | |_/ /     \n");
        printf("| | __ |  _  || |\\/| ||  __|  | | | || | | ||  __| |    /      \n");
        printf("| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ /| |___ | |\\ \\      \n");
        printf(" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/ \\____/ \\_| \\_|     \n\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        return 0;
    }
    else
    {
        printf("\nO Ciclope foi morto!!!\n");
        printf("\nPressione ENTER para continuar...\n");
        getch();
        system("cls");
        levelup(2, &p1);
        printf("\nSua vida maxima aumentou em 100:");
        p1.pv = p1.pvmax+100;
        p1.pvmax = p1.pvmax+100;

        printf("\nVIDA: %dHP\n", p1.pv);
    }

    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");
    //FIM DO COMBATE

    printf("\nNo momento que o ciclope cai no chao, morto, voce fica aliviado... mas quando as coisas ja estvama ficando mais calmas, o copro do ciclope comece a tremer e chacoalhar descontroladamente\n");
    printf("\nO monstro comeca a inchar e ficando vermhlo aso poucos, seu tamanho comeca a aumetar e suas roupas estouraram. ELE VAI EXPLODIR\n");
    printf("\nVoce so tem uma opcao, CORRER!\n");
    printf("\nPressione ENTER para continuar...\n");
    getch();
    system("cls");
    printf("\nUma explosao gigantesca de carne, gorduras e sangue varre toda a sala. Uma onda de restos de ciclope te varre e com o impacto te joga em direcao a unica saida, logo atras de onde voce estava.\n");
    printf("\nQuando voce atravessa a porta, uma parede de pedra e instantaneamente erguida e fecha o acesso a sala inundada de restos mortais do monstro, o impacto da parede com o teto certamente teria te matado...\n");
    printf("\nVoce se levanta e percebe que esta novamente em um corredor...\n E segue o unico caminho ate uma pequena sala com uma unica porta, uma porta alta e elegante, como um port�o para um grande sal�o...\n");


return 0;
}











