/* Autor....: Tiago Martins
   Data.....: 24/11/2023
   Objetivo.: Fazer o jogo Show do milhao
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

typedef struct
{
    int  id_questao;
    char ds_pergunta[100];
    char ds_alternativa1[100];
    char ds_alternativa2[100];
    char ds_alternativa3[100];
    char ds_alternativa4[100];
    int  nivel_pergunta;
    int  resp_ok;
    int  pergunta_feita;
} reg_questoes;

typedef struct TipoItem *TipoApontador;

typedef struct TipoItem
{
    TipoApontador anterior;
    reg_questoes conteudo;
    TipoApontador proximo;
} TipoItem;

typedef struct
{
    TipoApontador Primeiro;
    TipoApontador Ultimo;
} TipoLista;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void tela()
{
    int t;
    system("cls");
    gotoxy(01, 01);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(01, 02);
    printf("| UNICV");
    gotoxy(60, 02);
    printf("Estrutura de Dados |");
    gotoxy(01, 03);
    printf("|");
    gotoxy(20, 02);
    printf("SHOW DO MILHAO");
    gotoxy(79, 03);
    printf("|");
    gotoxy(01, 04);
    printf("+-----------------------------------------------------------------------------+");
    for (t = 5; t < 24; t++)
    {
        gotoxy(01, t);
        printf("|");
        gotoxy(79, t);
        printf("|");
    }
    gotoxy(01, 22);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 23);
    printf("MSG.:");
    gotoxy(01, 24);
    printf("+-----------------------------------------------------------------------------+");
}

void tela_pergunta()
{
    tela();
    gotoxy(07, 05);
    printf("   Codigo da Pergunta....: ");
    gotoxy(07, 07);
    printf("1- Descricao da Pergunta.: ");
    gotoxy(07, 9);
    printf("2- Primeira Alternativa..: ");
    gotoxy(07, 11);
    printf("3- Segunda Alternativa...: ");
    gotoxy(07, 13);
    printf("4- Terceira Alternativa..: ");
    gotoxy(07, 15);
    printf("5- Quarta Alternativa....: ");
    gotoxy(07, 17);
    printf("6- Nivel da Pergunta.....: ");
    gotoxy(07, 19);
    printf("7- Resposta Correta......: ");
}

void limpa_tela()
{
    int lin;
    int col;
    for (lin = 7; lin < 22; lin++)
    {
        for (col = 2; col < 79; col++)
        {
            gotoxy(col, lin);
            printf(" ");
        }
    }
}

TipoApontador pesquisa(TipoLista *L, int codigo)
{
    TipoApontador aux;
    aux = L->Primeiro;
    while (aux != NULL)
    {
        if (aux->conteudo.id_questao == codigo)
        {
            break;
        }
        aux = aux->proximo;
    }
    return aux;
}

int conta_elementos(TipoLista *L)
{
    int cont;
    TipoApontador aux;
    aux = L->Primeiro;
    cont = 0;
    while (aux != NULL)
    {
        cont = cont + 1;
        aux = aux->proximo;
    }
    return cont;
}

void ordena_codigo(TipoLista *L)
{
    int i;
    int j;
    int qtde;
    reg_questoes reg;
    TipoApontador aux1;
    TipoApontador aux2;

    qtde = conta_elementos(L);
    aux1 = L->Primeiro;
    aux2 = aux1->proximo;
    for (i = 1; i <= qtde - 1; i++)
    {
        for (j = i + 1; j <= qtde; j++)
        {
            if (aux1->conteudo.id_questao > aux2->conteudo.id_questao)
            {
                reg = aux1->conteudo;
                aux1->conteudo = aux2->conteudo;
                aux2->conteudo = reg;
            }
            aux2 = aux2->proximo;
        }
        aux1 = aux1->proximo;
        aux2 = aux1->proximo;
    }
}

void ordena_desc(TipoLista *L)
{
    int i;
    int j;
    int qtde;
    int result;
    reg_questoes reg;
    TipoApontador aux1;
    TipoApontador aux2;

    qtde = conta_elementos(L);
    aux1 = L->Primeiro;
    aux2 = aux1->proximo;
    for (i = 1; i <= qtde - 1; i++)
    {
        for (j = i + 1; j <= qtde; j++)
        {
            result = strcmp(aux1->conteudo.ds_pergunta, aux2->conteudo.ds_pergunta);
            if (result > 0)
            {

                reg = aux1->conteudo;
                aux1->conteudo = aux2->conteudo;
                aux2->conteudo = reg;
            }

            aux2 = aux2->proximo;
        }
        aux1 = aux1->proximo;
        aux2 = aux1->proximo;
    }
}

char *le_ds_pergunta()
{
    char *ds_pergunta;
    ds_pergunta = malloc(sizeof(char) * 100);
    do
    {
        gotoxy(34, 07);
        printf("                                               ");
        gotoxy(34, 07);
        fgets(ds_pergunta, 100, stdin);

        if ((strlen(ds_pergunta) == 1) && (strcmp(ds_pergunta, "0") == -1))
        {
            gotoxy(07, 23);
            printf("A descricao da pergunta e obrigatoria");
            getch();
            gotoxy(07, 23);
            printf("                              ");
        }
    } while ((strlen(ds_pergunta) == 1) && (strcmp(ds_pergunta, "0") == -1));
    return ds_pergunta;
}

char *le_ds_alternativa(int linha)
{
    char *ds_alternativa;
    ds_alternativa = malloc(sizeof(char) * 100);
    do
    {
        gotoxy(34, linha);
        printf("                                               ");
        gotoxy(34, linha);
        fgets(ds_alternativa, 100, stdin);

        if ((strlen(ds_alternativa) == 1) && (strcmp(ds_alternativa, "0") == -1))
        {
            gotoxy(07, 23);
            printf("A descricao da alternativa e obrigatoria");
            getch();
            gotoxy(07, 23);
            printf("                              ");
        }
    } while ((strlen(ds_alternativa) == 1) && (strcmp(ds_alternativa, "0") == -1));
    return ds_alternativa;
}

int le_nivel_pergunta()
{
    int nivel_pergunta;
    do
    {
        gotoxy(34, 17);
        printf("                                               ");
        gotoxy(34, 17);
        scanf("%d", &nivel_pergunta);
        getchar();
        if (nivel_pergunta == 0)
        {
            gotoxy(07, 23);
            printf("O nivel da pergunta e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                             ");
        }
    } while (nivel_pergunta <= 0 && nivel_pergunta > 3);
    return nivel_pergunta;
}

int le_resp_ok()
{
    int resp_ok;
    do
    {
        gotoxy(34, 19);
        printf("                                               ");
        gotoxy(34, 19);
        scanf("%d", &resp_ok);
        getchar();
        if (resp_ok == 0)
        {
            gotoxy(07, 23);
            printf("E obrigatorio informar a alternativa correta");
            getch();
            gotoxy(07, 23);
            printf("                                             ");
        }
    } while (resp_ok <= 0 && resp_ok > 4);
    return resp_ok;
}

void leitura(reg_questoes *reg_quest)
{
    strcpy(reg_quest->ds_pergunta, le_ds_pergunta());
    strcpy(reg_quest->ds_alternativa1, le_ds_alternativa(9));
    strcpy(reg_quest->ds_alternativa2, le_ds_alternativa(11));
    strcpy(reg_quest->ds_alternativa3, le_ds_alternativa(13));
    strcpy(reg_quest->ds_alternativa4, le_ds_alternativa(15));
    reg_quest->nivel_pergunta = le_nivel_pergunta();
    reg_quest->resp_ok = le_resp_ok();
}

void mostra_pergunta(reg_questoes reg_quest)
{
    gotoxy(34, 05);
    printf("%d", reg_quest.id_questao);
    gotoxy(34, 07);
    printf("%s", reg_quest.ds_pergunta);
    gotoxy(34, 9);
    printf("%s", reg_quest.ds_alternativa1);
    gotoxy(34, 11);
    printf("%s", reg_quest.ds_alternativa2);
    gotoxy(34, 13);
    printf("%s", reg_quest.ds_alternativa3);
    gotoxy(34, 15);
    printf("%s", reg_quest.ds_alternativa4);
    gotoxy(34, 17);
    printf("%d", reg_quest.nivel_pergunta);
    gotoxy(34, 19);
    printf("%d", reg_quest.resp_ok);
}

void cad_fim(TipoLista *L)
{
    TipoApontador p;
    TipoApontador aux1;
    int resp;
    reg_questoes reg_quest;
    tela_pergunta();
    gotoxy(35, 03);
    printf("CADASTRAR PERGUNTA");
    do
    {
        gotoxy(34, 05);
        printf("           ");
        gotoxy(34, 05);
        scanf("%d", &reg_quest.id_questao);
        getchar();
        aux1 = pesquisa(L, reg_quest.id_questao);
        if (aux1 != NULL)
        {
            gotoxy(07, 23);
            printf("                                            ");
            gotoxy(07, 23);
            printf("Codigo Ja Cadastrado..");
            getch();
            gotoxy(07, 23);
            printf("                                            ");
        }
    } while (aux1 != NULL);

    leitura(&reg_quest);

    gotoxy(07, 23);
    printf("Deseja gravar os dados (1-Sim; 2-Nao).:");
    scanf("%d", &resp);
    if (resp == 1)
    {
        p = (TipoApontador)malloc(sizeof(TipoItem));
        p->conteudo = reg_quest;
        p->anterior = NULL;
        p->proximo = NULL;

        if (L->Primeiro == NULL)
        {
            L->Primeiro = p;
            L->Ultimo = p;
        }
        else
        {
            L->Ultimo->proximo = p;
            p->anterior = L->Ultimo;
            L->Ultimo = p;
        }
    }
}

void consultar_pergunta(TipoLista *L)
{
    TipoApontador p;
    int codigo;
    int qtde;
    p = L->Primeiro;
    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("LISTA VAZIA...");
        getch();
    }
    else
    {
        do
        {
            tela();
            tela_pergunta();
            gotoxy(25, 03);
            printf("CONSULTAR PERGUNTA ESPECIFICA");
            gotoxy(60, 03);
            qtde = conta_elementos(L);
            printf("Total Perguntas.: %d", qtde);
            gotoxy(34, 05);
            scanf("%d", &codigo);
            p = pesquisa(L, codigo);
            if (p == NULL)
            {
                gotoxy(07, 23);
                printf("Pergunta Nao Cadastrada...");
                getch();
            }
        } while (p == NULL);

        mostra_pergunta(p->conteudo);

        gotoxy(10, 23);
        system("pause");
    }
}

void consultar(TipoLista *L)
{
    TipoApontador p;
    p = L->Primeiro;
    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("LISTA VAZIA...");
        getchar();
    }
    else
    {
        tela();
        while (p != NULL)
        {
            tela_pergunta();
            gotoxy(35, 03);
            printf("CONSULTAR PERGUNTA");

            mostra_pergunta(p->conteudo);

            gotoxy(10, 23);
            system("pause");
            p = p->proximo;
        }
    }
}

void cad_inicio(TipoLista *L)
{
    int resp;
    TipoApontador p;
    TipoApontador aux1;
    reg_questoes reg_quest;
    tela_pergunta();
    gotoxy(25, 03);
    printf("CADASTRAR PERGUNTA NO INICIO");

    do
    {
        gotoxy(34, 05);
        printf("           ");
        gotoxy(34, 05);
        scanf("%d", &reg_quest.id_questao);
        getchar();
        aux1 = pesquisa(L, reg_quest.id_questao);
        if (aux1 != NULL)
        {
            gotoxy(07, 23);
            printf("                                            ");
            gotoxy(07, 23);
            printf("Codigo Ja Cadastrado..");
            getch();
            gotoxy(07, 23);
            printf("                                            ");
        }
    } while (aux1 != NULL);

    leitura(&reg_quest);

    gotoxy(07, 23);
    printf("Deseja gravar os dados (1-Sim; 2-Nao).:");
    scanf("%d", &resp);
    if (resp == 1) {
    p = (TipoApontador)malloc(sizeof(TipoItem));
    p->proximo = L->Primeiro;
    p->anterior = NULL;

    if (L->Primeiro != NULL) {
        L->Primeiro->anterior = p;
    } else {
        L->Ultimo = p;
    }

    L->Primeiro = p;

    if (L->Ultimo == NULL) {
        L->Ultimo = L->Primeiro;
        L->Ultimo->proximo = NULL;
    }

    L->Primeiro->conteudo = reg_quest;
    }
}

void cad_posicao(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    TipoApontador aux1;
    reg_questoes reg_quest;
    int resp;
    int Posicao;
    int cont;
    int qtde;
    do
    {
        tela_pergunta();
        gotoxy(20, 03);
        printf("CADASTRAR PERGUNTA EM UMA POSICAO");
        gotoxy(60, 03);
        qtde = conta_elementos(L);
        printf("Total Perguntas.: %d", qtde);

        gotoxy(8, 23);
        printf("Deseja cadastrar em qual Posicao.: ");
        scanf("%d", &Posicao);
        if (Posicao > qtde)
        {
            gotoxy(07, 23);
            printf("                                                    ");
            gotoxy(8, 23);
            printf("Posicao Maior que Qtde Elementos..");
            getch();
        }
    } while (Posicao != 0 && Posicao > qtde);

    if (Posicao > 0)
    {
        do
        {
            gotoxy(34, 05);
            printf("           ");
            gotoxy(34, 05);
            scanf("%d", &reg_quest.id_questao);
            getchar();
            aux1 = pesquisa(L, reg_quest.id_questao);
            if (aux1 != NULL)
            {
                gotoxy(07, 23);
                printf("                                            ");
                gotoxy(07, 23);
                printf("Codigo Ja Cadastrado..");
                getch();
                gotoxy(07, 23);
                printf("                                            ");
            }
        } while (aux1 != NULL);

        leitura(&reg_quest);

        gotoxy(07, 23);
        printf("Deseja gravar os dados (1-Sim; 2-Nao).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            r = (TipoApontador)malloc(sizeof(TipoItem));

            r->conteudo = reg_quest;
            r->anterior = NULL;
            r->proximo = NULL;

            p = L->Primeiro;
            for (cont = 1; cont <= Posicao - 2; cont++)
            {
                p = p->proximo;
            }
            if (Posicao == 1)
            {
                L->Primeiro->anterior = r;
                r->proximo = L->Primeiro;
                L->Primeiro = r;
            }
            else
            {
                r->proximo = p->proximo;
                p->proximo = r;
            }
        }
    }
}

void remove_final(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    p = L->Ultimo;
    int resp;

    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("LISTA VAZIA..");
        getch();
    }
    else
    {
        tela_pergunta();
        gotoxy(30, 03);
        printf("REMOVER PERGUNTA FINAL");

        mostra_pergunta(p->conteudo);

        gotoxy(07, 23);
        printf("Deseja Remover a Pergunta no Final (1=Sim; 2-Nao).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            if (L->Primeiro->proximo == NULL)
            {
                free(p);
                L->Primeiro = NULL;
                L->Ultimo = NULL;
            }
            else
            {
                L->Ultimo = L->Ultimo->anterior;
                L->Ultimo->proximo = NULL;
                free(p);
            }
            gotoxy(07, 23);
            printf("                                                       ");
            gotoxy(07, 23);
            printf("Registro Removido com Sucesso.");
            getch();
        }
    }
}

void remove_posicao(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    int resp;
    int Posicao;
    int cont;
    int qtde;
    do
    {
        tela_pergunta();
        gotoxy(20, 03);
        printf("CADASTRAR PERGUNTA EM UMA POSICAO");
        gotoxy(60, 03);
        qtde = conta_elementos(L);
        printf("Total Perguntas.: %d", qtde);

        gotoxy(8, 23);
        printf("Deseja remover em qual Posicao.: ");
        scanf("%d", &Posicao);
        if (Posicao > qtde)
        {
            gotoxy(07, 23);
            printf("                                                    ");
            gotoxy(8, 23);
            printf("Posicao Maior que Qtde Elementos..");
            getch();
        }
    } while (Posicao != 0 && Posicao > qtde);

    if (Posicao > 0)
    {
        if (Posicao == 1)
        {
            r = L->Primeiro;
            p = r;
        }
        else
        {
            r = L->Primeiro;
            p = r->proximo;
            cont = 1;
            while (cont < Posicao - 1)
            {
                cont = cont + 1;
                p = p->proximo;
                r = r->proximo;
            }
        }

        tela_pergunta();
        gotoxy(34, 03);
        printf("REMOVER PERGUNTA POSICAO");

        mostra_pergunta(p->conteudo);

        gotoxy(07, 23);
        printf("Deseja Remover a Pergunta na Posicao [%d] (1=Sim; 2-Nao).:", Posicao);
        scanf("%d", &resp);
        if (resp == 1)
        {
            if (Posicao == 1)
            {
                L->Primeiro = p->proximo;
                L->Primeiro->anterior = NULL;
                free(p);
            }
            else
            {
                p->proximo->anterior = r;
                r->proximo = p->proximo;
                free(p);
            }
        }
    }
}

void remove_inicio(TipoLista *L)
{
    TipoApontador p;
    p = L->Primeiro;
    int resp;

    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("LISTA VAZIA..");
        getch();
    }
    else
    {
        tela_pergunta();
        gotoxy(30, 03);
        printf("REMOVER PERGUNTA INICIO");

        mostra_pergunta(p->conteudo);

        gotoxy(07, 23);
        printf("Deseja Remover a Pergunta no inicio? (1=Sim; 2-Nao).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            if (p->proximo == NULL)
            {
                free(p);
                L->Primeiro = NULL;
                L->Ultimo = NULL;
            }
            else
            {
                L->Primeiro = p->proximo;
                L->Primeiro->anterior = NULL;
                free(p);
            }
            gotoxy(07, 23);
            printf("                                                       ");
            gotoxy(07, 23);
            printf("Registro Removido com Sucesso.");
            getch();
        }
    }
}

void consulta_todos(TipoLista *L, char msg[40])
{
    TipoApontador p;
    int lin;
    tela();
    gotoxy(22, 03);
    printf("%s", msg);
    lin = 7;
    gotoxy(02, 05);
    printf("Cd Descricao                                                                 ");
    gotoxy(02, 06);
    printf("-- --------------------------------------------------------------------------");
    p = L->Primeiro;
    if (p == NULL)
    {
        gotoxy(07, 23);
        printf("LISTA VAZIA..");
        getch();
    }
    else
    {
        while (p != NULL)
        {
            gotoxy(02, lin);
            printf("%d", p->conteudo.id_questao);
            gotoxy(05, lin);
            printf("%s", p->conteudo.ds_pergunta);
            lin++;
            if (lin > 21)
            {
                gotoxy(07, 23);
                system("pause");
                limpa_tela();
                lin = 7;
            }
            p = p->proximo;
        }
        gotoxy(07, 23);
        system("pause");
    }
}

void altera_pergunta(TipoLista *L)
{
    TipoApontador p;
    reg_questoes reg_quest;
    int codigo;
    int qtde;
    int campo;
    int resp;
    p = L->Primeiro;
    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("LISTA VAZIA...");
        getch();
    }
    else
    {
        do
        {
            tela();
            tela_pergunta();
            gotoxy(25, 03);
            printf("ALTERACAO DADOS DA PERGUNTA");
            gotoxy(60, 03);
            qtde = conta_elementos(L);
            printf("Total Perguntas.: %d", qtde);
            gotoxy(34, 05);
            scanf("%d", &codigo);
            p = pesquisa(L, codigo);
            if (p == NULL)
            {
                gotoxy(07, 23);
                printf("Pergunta Nao Cadastrada..");
                getch();
            }
        } while (p == NULL);

        mostra_pergunta(p->conteudo);
        reg_quest = p->conteudo;
        do
        {
            gotoxy(07, 23);
            printf("                                               ");
            gotoxy(07, 23);
            printf("Digite o Campo a ser Alterado (0=Sair).: ");
            scanf("%d", &campo);
            getchar();
            if (campo > 7)
            {
                gotoxy(07, 23);
                printf("                                           ");
                gotoxy(07, 23);
                printf("Campo invalido..");
                getch();
            }
            switch (campo)
            {
            case 1:
                strcpy(reg_quest.ds_pergunta, le_ds_pergunta());
                break;
            case 2:
                strcpy(reg_quest.ds_alternativa1, le_ds_alternativa(9));
                break;
            case 3:
                strcpy(reg_quest.ds_alternativa2, le_ds_alternativa(11));
                break;
            case 4:
                strcpy(reg_quest.ds_alternativa3, le_ds_alternativa(13));
                break;
            case 5:
                strcpy(reg_quest.ds_alternativa4, le_ds_alternativa(15));
                break;
            case 6:
                reg_quest.nivel_pergunta = le_nivel_pergunta();
                break;
            case 7:
                reg_quest.resp_ok = le_resp_ok();
                break;
            default:
                break;
            }
        } while ((campo != 0));
        gotoxy(07, 23);
        printf("                                             ");
        gotoxy(07, 23);
        printf("Confirma a Alteracao dos Dados (1-Sim;2-Nao).: ");
        scanf("%d", &resp);
        if (resp == 1)
        {
            p->conteudo = reg_quest;
        }
    }
}

void ajuda()
{
    int opc;
    gotoxy(01, 20);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 21);
    printf("1 - Universitarios | 2 - Placas | 3 - Cartas | 4 - Pulos");
    gotoxy(07, 23);
    printf("Escolha uma alternativa.: ");
    scanf("%d", &opc);
}
int conta_elemento_nivel (TipoLista *L, int nivel) {
    TipoApontador p;
    int cont=0;
    p = L->Primeiro;
    while (p != NULL) {
        if (p->conteudo.nivel_pergunta == nivel) {
             cont++;
        }
        p = p->proximo;
    }
    return cont;
}

TipoApontador get_pergunta(TipoLista *L, int pergunta)
{
    TipoApontador p;
    int nivel=0;
    int questao_sort = 0;
    int cont;
        if (pergunta <=5)
        {
            nivel = 1;
        } else
        {
          if (pergunta <= 10) {
            nivel = 2;
          } else {
            nivel = 3;
          }
        }
    do
    {
        srand(time(NULL));
        questao_sort = 1+ rand() % conta_elemento_nivel(L,nivel);

        gotoxy(03,17);
        cont = 0;
        p = L->Primeiro;
        while (p != NULL) {
             if (p->conteudo.nivel_pergunta == nivel)  {
                cont++;
                if (cont  == questao_sort) {
                    break;
                }
             }
              p = p->proximo;
        }
    } while (p->conteudo.pergunta_feita == 1);
    p->conteudo.pergunta_feita = 1;
    return p;
}

void  tela_show_milhao(char nome_participante[100])
{
    tela();
    int t;
    system("cls");
    gotoxy(01, 01);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(01, 02);
    printf("| UNICV");
    gotoxy(60, 02);
    printf("Estrutura de Dados |");
    gotoxy(01, 03);
    printf("|");
    gotoxy(20, 02);
    printf("JOGO SHOW DO MILHAO");
    gotoxy(79, 03);
    printf("|");
    gotoxy(01, 04);
    printf("+-----------------------------------------------------------------------------+");
    for (t = 5; t < 24; t++)
    {
        gotoxy(01, t);
        printf("|");
        gotoxy(79, t);
        printf("|");
    }
    gotoxy(15,10);
    printf("SSS H H OOO W   W  D D  OOO  M   M I L   H H AAA OOO\n");
    gotoxy(15,11);
    printf("S   H H O O W   W  D  D O O  MM MM I L   H H A A O O\n");
    gotoxy(15,12);
    printf("SSS HHH O O W W W  D  D O O  M M M I L   HHH AAA O O\n");
    gotoxy(15,13);
    printf("  S H H O O WW WW  D  D O O  M   M I L   H H A A O O\n");
    gotoxy(15,14);
    printf("SSS H H OOO W   W  D D  OOO  M   M I LLL H H A A OOO\n");
    gotoxy(30,18);
    printf("Atencao %s",nome_participante);
    gotoxy(16,19);
    printf("Vai comecar o show do milhao, deseja continuar?");
    gotoxy(30,20);
    printf("1 - Sim | 0 - Não");
    gotoxy(01, 22);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 23);
    printf("MSG.:");
    gotoxy(01, 24);
    printf("+-----------------------------------------------------------------------------+");
}

void tela_valor_pergunta(char nome_participante[100], float valor_pergunta, int pergunta){
    tela();
    gotoxy(30,18);
    printf("Atencao %s",nome_participante);
    gotoxy(20,19);
    printf("%d - Pergunta no valor de %.2f reais",pergunta,valor_pergunta);
    gotoxy(10,23);
    system("pause");
}

void tela_parar(float total_premio, char nome_participante[100]){
    tela();
    gotoxy(30,15);
    printf("Que pena que voce parou %s",nome_participante);
    gotoxy(30,16);
    printf("Seu premio foi de R$ %.2f reais",total_premio);
    gotoxy(10,23);
    system("pause");
}

void imprimir_carta(int coluna, int linha){
    gotoxy(coluna,linha);
    printf("=========");
    gotoxy(coluna,linha + 1);
    printf("=========");
    gotoxy(coluna,linha + 2);
    printf("=========");
    gotoxy(coluna,linha + 3);
    printf("=========");
    gotoxy(coluna,linha + 4);
    printf("=========");
}

void tela_escolha_cartas(){
    tela();
    gotoxy(25,5);
    printf("Digite a carta que deseja de 1 a 4: ");
    imprimir_carta(30,8);
    imprimir_carta(30,15);
    imprimir_carta(50,8);
    imprimir_carta(50,15);
}

void tela_ganhador(float total_premio, char nome_participante[100]){
    tela();
    gotoxy(03,10);
    printf("Parabens %s",nome_participante);
    gotoxy(03,11);
    printf("Voce acertou todas as perguntas do jogo do milhao!!!!",nome_participante);
    gotoxy(03,12);
    printf("Premio final: %.2f reais",total_premio);
    gotoxy(10,23);
    system("pause");
}


int responder(int resposta, TipoApontador questao){
    if(questao->conteudo.resp_ok == resposta){
        return 1;
    }else {
        return 0;
    }
}

void tela_errou(float total_premio, char nome_participante[100]){
    tela();
    gotoxy(30,15);
    printf("Que pena que voce errou %s",nome_participante);
    gotoxy(30,16);
    printf("Seu premio foi de R$ %.2f reais",total_premio);
    gotoxy(10,23);
    system("pause");
    main();
}

void tela_placas(){
    int count;
    int qtde_pessoas = 50;
    int resposta;
    int resp_1 = 0,resp_2 = 0, resp_3 = 0, resp_4 = 0;
    for(count = 0; count < qtde_pessoas; count++){
        resposta =  1+ rand() % 4;
        switch (resposta)
        {
        case 1:
            resp_1++;
            break;
        case 2:
            resp_2++;
            break;
        case 3:
            resp_3++;
            break;
        case 4:
            resp_4++;
            break;
        }
    }


    float porc_resp_1 = resp_1 * 100 / qtde_pessoas;
    float porc_resp_2 = resp_2 * 100 / qtde_pessoas;
    float porc_resp_3 = resp_3 * 100 / qtde_pessoas;
    float porc_resp_4 = resp_4 * 100 / qtde_pessoas;
    gotoxy(05,9);
    printf("Placas - %d pessoas",qtde_pessoas);

    gotoxy(02,10);
    printf("----------------------------");


    gotoxy(02,12);
    printf("----------------------------");

    gotoxy(2,11);
    printf("  1  ");
    gotoxy(2,13);
    printf("%.1f%%",porc_resp_1);

    int linha;
    for(linha = 10; linha < 15; linha++){
        gotoxy(8,linha);
        printf("|");
    }

    gotoxy(10,11);
    printf("   2   ");
    gotoxy(10,13);
    printf("%.1f%%",porc_resp_2);

    for(linha = 10; linha < 15; linha++){
        gotoxy(17,linha);
        printf("|");
    }

    gotoxy(18,11);
    printf("   3   ");
    gotoxy(18,13);
    printf("%.1f%%",porc_resp_3);

    for(linha = 10; linha < 15; linha++){
        gotoxy(22,linha);
        printf("|");
    }

    gotoxy(23,11);
    printf("   4  ");
    gotoxy(24,13);
    printf("%.1f%%",porc_resp_4);

    gotoxy(02,15);
    printf("----------------------------");

    gotoxy(10,24);
}


void tela_universitarios(TipoApontador questao, int *opcoes_escolha){
    int uni_1 = 1+ rand() % 4;
    int uni_2 = 1+ rand() % 4;
    int uni_3 = 1+ rand() % 4;
    int uni_4 = 1+ rand() % 4;

    gotoxy(10,9);
    printf("Universitarios: ");

    gotoxy(05,13);
    printf("Uni-1");
    gotoxy(05,14);
    printf("Resp: %d",uni_1);

    gotoxy(20,13);
    printf("Uni-2");
    gotoxy(20,14);
    printf("Resp: %d",uni_2);

    int linha;
    for(linha = 13; linha <= 17; linha++){
        gotoxy(16,linha);
        printf("|");
    }

    gotoxy(01,15);
    printf("--------------------------");

    gotoxy(05,16);
    printf("Uni-3");
    gotoxy(05,17);
    printf("Resp: %d",uni_3);

    gotoxy(20,16);
    printf("Uni-4");
    gotoxy(20,17);
    printf("Resp: %d",uni_4);
}


void definir_valor_perguntas(int pergunta, float *valor_acertar, float *valor_errar,float *valor_parar){
    if(pergunta == 1){
        *valor_acertar = 1000;
        *valor_errar = 0;
        *valor_parar = 0;
    }else if( pergunta > 1 && pergunta <= 5) {
        *valor_acertar = 1000; // 2000
        *valor_acertar = *valor_acertar * pergunta;
        *valor_parar = *valor_acertar  - 1000;
        *valor_errar = *valor_parar / 2;
    }else if(pergunta == 6){
        *valor_acertar = 10000;
        *valor_parar = *valor_acertar / 2;
        *valor_errar = *valor_parar / 2;
    } else if(pergunta > 6 && pergunta <= 10){
        *valor_parar = *valor_acertar;
        *valor_acertar += 10000;
        *valor_errar = *valor_parar / 2;
    }else if(pergunta == 11){
        *valor_acertar = 100000;
        *valor_parar = *valor_acertar / 2;
        *valor_errar = *valor_parar / 2;
    }else if(pergunta > 11 && pergunta <= 15){
        *valor_parar = *valor_acertar;
        *valor_acertar += 100000;
        *valor_errar = *valor_parar / 2;
    }else if(pergunta == 16){
        *valor_acertar = 1000000;
        *valor_parar = *valor_acertar / 2;
        *valor_errar = 0;
    }
}

void tela_jogo(TipoLista *L, char nome_participante[100])
{
    TipoApontador questao;
    int pergunta;
    int opc;
    do {
        tela_show_milhao(nome_participante);
        gotoxy(06,23);
        scanf("%d",&opc);
    }while(opc > 1 && opc < 0);

    if(opc == 0){
        main();
    }else {
        tela();
        int resposta;
        float valor_errar;
        float valor_parar;
        float valor_acertar;


        int qtde_pulos = 3;
        int qtde_universitarios = 2;
        int qtde_cartas = 2;
        int qtde_placas = 2;
        int opc_pergunta;

        for (pergunta = 1; pergunta <= 16; pergunta++){
            definir_valor_perguntas(pergunta,&valor_acertar,&valor_errar,&valor_parar);
            resposta = -1;
            questao = get_pergunta(L, pergunta);
            tela_valor_pergunta(nome_participante,valor_acertar,pergunta);
            do {
                gotoxy(34,04);
                tela_questao();
                mostra_questao(pergunta,questao->conteudo);
                mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                opcoes_escolha(qtde_pulos,qtde_cartas,qtde_universitarios,qtde_placas);
                scanf("%d",&opc_pergunta);
            }while((opc_pergunta < 0 && opc_pergunta > 5) || (qtde_cartas == 0 && opc_pergunta == 3)
                || (qtde_universitarios == 0 && opc_pergunta == 4) || (qtde_placas == 0 && opc_pergunta == 5)
            );
            switch (opc_pergunta)
            {
                case 0:
                    tela_parar(valor_parar,nome_participante);
                    break;
                case 1:
                    do {
                        tela_questao();
                        mostra_questao(pergunta,questao->conteudo);
                        mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                        gotoxy(01,23);
                        printf("Qual e a resposta certa? ");
                        scanf("%d",&resposta);
                    }
                    while(resposta < 0 && resposta > 4);
                    int acertou = responder(resposta,questao);
                    if(acertou == 1){
                        tela_questao();
                        mostra_questao(pergunta,questao->conteudo);
                        mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                        gotoxy(30,23);
                        printf("Acertou!");
                        gotoxy(01,25);
                        system("pause");
                        if(pergunta == 16){
                            tela_ganhador(valor_acertar,nome_participante);
                        }
                    }else {
                        tela_questao();
                        mostra_questao(pergunta,questao->conteudo);
                        mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                        gotoxy(30,23);
                        printf("Voce errou!");
                        gotoxy(01,25);
                        system("pause");
                        tela_errou(valor_errar,nome_participante);
                    }
                    break;
                case 2:
                    if(qtde_pulos > 0){
                        tela_questao();
                        mostra_questao(pergunta,questao->conteudo);
                        mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                        gotoxy(30,23);
                        printf("Pulou a pergunta");
                        gotoxy(01,25);
                        system("pause");
                        pergunta--;
                        qtde_pulos--;
                    }

                    break;
                case 3:
                    if(qtde_cartas > 0){
                        qtde_cartas--;
                        int carta_com_rei = rand() % 4;
                        int carta_escolhida;
                        do {
                            tela_escolha_cartas();
                            gotoxy(10,23);
                            printf("Escolha a carta: ");
                            scanf("%d",&carta_escolhida);
                        }while(carta_escolhida < 1 && carta_escolhida > 4);

                        tela_escolha_cartas();
                        if(carta_escolhida == carta_com_rei){
                            gotoxy(10,23);
                            printf("Achou o rei");
                            gotoxy(10,25);
                            system("pause");
                            if(pergunta == 16){
                                tela_ganhador(valor_acertar,nome_participante);
                            }
                        }else {
                            gotoxy(30,23);
                            printf("Voce errou!");
                            gotoxy(01,25);
                            system("pause");
                            tela_errou(valor_errar,nome_participante);
                        }

                    }
                    break;
                case 4:
                    if(qtde_universitarios > 0){
                        qtde_universitarios--;
                        do {
                            tela_questao();
                            mostra_questao(pergunta,questao->conteudo);
                            mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                            tela_universitarios(questao,&resposta);
                            gotoxy(01,23);
                            printf("Qual e a resposta certa? ");
                            scanf("%d",&resposta);
                        }
                        while(resposta < 0 && resposta > 4);
                        int acertou = responder(resposta,questao);
                        if(acertou == 1){
                            tela_questao();
                            mostra_questao(pergunta,questao->conteudo);
                            mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                            gotoxy(30,23);
                            printf("Acertou!");
                            gotoxy(01,25);
                            system("pause");
                            if(pergunta == 16){
                                tela_ganhador(valor_acertar,nome_participante);
                            }
                        }else {
                            tela_questao();
                            mostra_questao(pergunta,questao->conteudo);
                            mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                            gotoxy(30,23);
                            printf("Voce errou!");
                            gotoxy(01,25);
                            system("pause");
                            tela_errou(valor_errar,nome_participante);
                        }
                    }
                    break;

                case 5:
                    if(qtde_placas > 0){
                        qtde_placas--;
                                                do {
                            tela_questao();
                            mostra_questao(pergunta,questao->conteudo);
                            mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                            tela_placas();
                            gotoxy(01,23);
                            printf("Qual e a resposta certa? ");
                            scanf("%d",&resposta);
                        }
                        while(resposta < 0 && resposta > 4);
                        int acertou = responder(resposta,questao);
                        if(acertou == 1){
                            tela_questao();
                            mostra_questao(pergunta,questao->conteudo);
                            mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                            gotoxy(30,23);
                            printf("Acertou!");
                            gotoxy(01,25);
                            system("pause");
                            if(pergunta == 16){
                                tela_ganhador(valor_acertar,nome_participante);
                            }
                        }else {
                            tela_questao();
                            mostra_questao(pergunta,questao->conteudo);
                            mostra_menu_pergunta(&valor_errar,&valor_parar,&valor_acertar);
                            gotoxy(30,23);
                            printf("Voce errou!");
                            gotoxy(01,25);
                            system("pause");
                            tela_errou(valor_errar,nome_participante);
                        }
                    }
                    break;
            }
            if(opc_pergunta == 0){
                break;
            }
        }
        main();
    }

}

void tela_questao()
{
    tela();
    gotoxy(30, 05);
    printf("Pergunta....: ");
    gotoxy(30, 9);
    printf("1-");
    gotoxy(30, 11);
    printf("2-");
    gotoxy(30, 13);
    printf("3-");
    gotoxy(30, 15);
    printf("4-");
}

void mostra_menu_pergunta(float *valor_errar, float *valor_parar, float *valor_acertar){
    gotoxy(10,19);
    printf("Errar");
    gotoxy(30,19);
    printf("|");
    gotoxy(35,19);
    printf("Parar");
    gotoxy(50,19);
    printf("|");
    gotoxy(55,19);
    printf("Acertar");
    gotoxy(01,20);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(10,21);
    printf("%.2f",*valor_errar);
    gotoxy(30,21);
    printf("|");
    gotoxy(35,21);
    printf("%.2f",*valor_parar);
    gotoxy(50,21);
    printf("|");
    gotoxy(55,21);
    printf("%.2f",*valor_acertar);
}

void opcoes_escolha(int qtde_pulos,int qtde_cartas,int qtde_universitarios, int qtde_placas){
    gotoxy(02,23);
    printf("0- Parar |");
    printf("1- Responder |");
    if(qtde_pulos > 0){
        printf("2- Pular |");
    }
    if(qtde_cartas > 0){
        printf("3- Cartas |");
    }
    if(qtde_universitarios > 0){
        printf("4- Universitarios |");
    }
    if(qtde_placas > 0){
        printf("5- Placas");
    }
    printf(":");
    gotoxy(78,23);
}
void mostra_questao(int pergunta, reg_questoes reg_quest)
{
    gotoxy(45, 05);
    printf("%d", pergunta);
    gotoxy(01,06);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(16, 07);
    printf("%s", reg_quest.ds_pergunta);
    gotoxy(01,8);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(34, 9);
    printf("%s", reg_quest.ds_alternativa1);
    gotoxy(34, 11);
    printf("%s", reg_quest.ds_alternativa2);
    gotoxy(34, 13);
    printf("%s", reg_quest.ds_alternativa3);
    gotoxy(34, 15);
    printf("%s", reg_quest.ds_alternativa4);
    gotoxy(01,18);
    printf("+-----------------------------------------------------------------------------+");
}

void jogar(TipoLista *L)
{
    TipoApontador p;
    char nome[100];
    p = L->Primeiro;
    if (conta_elementos(L) < 0)
    {
        tela();
        gotoxy(8, 23);
        printf("NAO HA PERGUNTAS SUFICIENTES...");
        getch();
    }
    else
    {

        tela();
        gotoxy(07, 23);
        printf("Digite o Seu Nome.: ");
        getchar();
        fgets(nome, 100, stdin);
        tela_jogo(L, nome);
    }
}

void le_arquivo(TipoLista *L)
{
    FILE *ptr;
    char *filename = "Perguntas.dat";
    char *modo_gravacao = "rb";
    reg_questoes reg_quest;
    TipoApontador p;
    L->Primeiro = NULL;
    L->Ultimo = NULL;
    tela();
    gotoxy(25, 03);
    printf("CARREGA DADOS DO ARQUIVO PARA A LISTA");

    ptr = fopen(filename, modo_gravacao);
    if (ptr == NULL)
    {
        gotoxy(07, 23);
        printf("Erro ao Abrir o Arquivo");
        getch();
    }
    else
    {
        gotoxy(01, 05);
        while (!feof(ptr))
        {
            if (fread(&reg_quest, sizeof(reg_quest), 1, ptr) != 0)
            {
                if (L->Primeiro == NULL)
                {
                    p = (TipoApontador)malloc(sizeof(TipoItem));
                    p->conteudo = reg_quest;
                    p->proximo = NULL;
                    L->Primeiro = p;
                    L->Ultimo = p;
                }
                else
                {
                    p->proximo = (TipoApontador)malloc(sizeof(TipoItem));
                    p = p->proximo;
                    p->conteudo = reg_quest;
                    p->proximo = NULL;
                    L->Ultimo = p;
                }
            }
        }
        fclose(ptr);
        gotoxy(07, 23);
        printf("Dados lidos com Sucesso");
        getch();
    }
}

void gravar(TipoLista *L)
{
    FILE *ptr;
    char *filename = "Perguntas.dat";
    char *modo_gravacao = "wb";
    reg_questoes reg_quest;
    TipoApontador p;
    p = L->Primeiro;
    tela();
    gotoxy(25, 03);
    printf("GRAVA DADOS DA LISTA NO ARQUIVO EM DISCO");
    if (p == NULL)
    {
        gotoxy(07, 23);
        printf("LISTA VAZIA..");
        getch();
    }
    else
    {
        if ((ptr = fopen(filename, modo_gravacao)) == NULL)
        {
            gotoxy(07, 23);
            printf("Erro ao Abrir o Arquivo");
            getch();
        }
        else
        {
            while (p != NULL)
            {
                reg_quest = p->conteudo;
                fwrite(&reg_quest, sizeof(reg_quest), 1, ptr);
                p = p->proximo;
            }
            fclose(ptr);
            gotoxy(07, 23);
            printf("Dados Gravados com Sucesso");
            getch();
        }
    }
}

void menu_consultar(TipoLista *L)
{
    int opc;
    do
    {
        tela();
        gotoxy(30, 03);
        printf("SUBMENU CONSULTA");
        gotoxy(25, 8);
        printf("1 - Consultar Todas as Perguntas");
        gotoxy(25, 10);
        printf("2 - Consultar em Ordem de Codigo");
        gotoxy(25, 12);
        printf("3 - Consultar em Ordem Alfabetica");
        gotoxy(25, 14);
        printf("4 - Consultar o Codigo Especifico");
        gotoxy(25, 16);
        printf("5 - Retornar Menu Principal");
        gotoxy(8, 23);
        printf("Digite sua opcao.: ");
        gotoxy(28, 23);
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            consultar(L);
            break;
        case 2:
            ordena_codigo(L);
            consulta_todos(L, "CONSULTA LISTA PERGUNTAS - ORDEM DE CODIGO");
            break;
        case 3:
            ordena_desc(L);
            consulta_todos(L, "CONSULTA LISTA CLIENTES - ORDEM ALFABETICA");
            break;
        case 4:
            consultar_pergunta(L);
            break;
        default:
            break;
        }

    } while (opc != 5);
}

int main()
{
    TipoLista L;
    L.Primeiro = NULL;
    L.Ultimo = NULL;
    int opc;
    system("color 1F");
    setlocale(LC_ALL, "portuguese-brazilian");
    le_arquivo(&L);
    do
    {
        tela();
        gotoxy(30, 03);
        printf("MENU PRINCIPAL");
        gotoxy(20, 8);
        printf("1 - Cadatrar Pergunta no Inicio");
        gotoxy(20, 9);
        printf("2 - Cadastrar Pergunta no Final");
        gotoxy(20, 10);
        printf("3 - Cadastrar Pergunta em uma Posicao");
        gotoxy(20, 11);
        printf("4 - Remover Pergunta no Inicio");
        gotoxy(20, 12);
        printf("5 - Remover Pergunta no Final");
        gotoxy(20, 13);
        printf("6 - Remover Pergunta em uma Posicao");
        gotoxy(20, 14);
        printf("7 - Consultar Cadastro das Perguntas");
        gotoxy(20, 15);
        printf("8 - Alterar uma Pergunta");
        gotoxy(20, 16);
        printf("9 - Jogar SHOW DO MILHAO");
        gotoxy(20, 17);
        printf("10 - Finalizar Programa");
        gotoxy(8, 23);
        printf("Digite sua opcao.: ");
        gotoxy(28, 23);
        scanf("%d", &opc);
        switch (opc)
        {
            case 1:
            {
                cad_inicio(&L);
                break;
            }

            case 2:
            {
                cad_fim(&L);
                break;
            }
            case 3:
            {
                cad_posicao(&L);
                break;
            }
            case 4:
            {
                remove_inicio(&L);
                break;
            }
            case 5:
            {
                remove_final(&L);
                break;
            }
            case 6:
            {
                remove_posicao(&L);
                break;
            }
            case 7:
            {
                menu_consultar(&L);
                break;
            }
            case 8:
            {
                altera_pergunta(&L);
                break;
            }
            case 9:
            {
                jogar(&L);
                break;
            }
        }
    } while (opc < 9);
    gravar(&L);
    return 0;
}







