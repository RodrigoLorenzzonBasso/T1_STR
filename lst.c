#include <stdio.h>
#include <math.h>

//Testando ssh key

#define MAX_N 26
#define MAX_T 2048

typedef struct {

  char id;
  int c;
  int p;
  int d;

} TAREFA;

int main() {

  TAREFA tarefas[MAX_N];
  int n_tarefas, t, i;
  char grade[MAX_T+1];
  int num_preemp, num_trocas_cont;

  //auxiliares
  int slack_t[MAX_N];


  while (1) {
    // LEITURA
    scanf("%d%d", &n_tarefas, &t);
    if (n_tarefas==0 || t==0)
       break;
    for (i=0; i<n_tarefas; ++i) {
       tarefas[i].id = 'A'+i;
       scanf("%d%d%d", &(tarefas[i].c), &(tarefas[i].p), &(tarefas[i].d) );
    }
    // SIMULACAO

    //extracao de dados
    num_preemp = 0;
    num_trocas_cont = 0;

    int n_execucoes[n_tarefas];
    int exec_mais_vezes = 0;

    for(int j = 0; j < n_tarefas; j++)
    {
      n_execucoes[j] = ceil((float)t/(float)tarefas[j].p);

      if(n_execucoes[j] > exec_mais_vezes)
        exec_mais_vezes = n_execucoes[j];
    }

    /*int deadlines_abs[n_tarefas][exec_mais_vezes];
    int periodos_abs[n_tarefas][exec_mais_vezes];

    for(int j = 0; j < n_tarefas; j++)
    {
      for(int k = 1; k <= n_execucoes[j]; k++)
      {
        deadlines_abs[j][k-1] = (tarefas[j].p * k) - (tarefas[j].p - tarefas[j].d);
        periodos_abs[j][k-1] = (tarefas[j].p * k);
      }
    }*/

    int deadline_abs[n_tarefas];
    int periodo_abs[n_tarefas];
    int comp_abs[n_tarefas];

    int menor_slack = MAX_T;
    int tarefa_menor_slack = 0;


    //execucao
    for(int j = 0; j < t; j++)
    {

      //printf("Tempo atual: %d\n", j);

      for(int k = 0; k < n_tarefas; k++)
      {
        if(j == 0) // comecou a execucao, setar primeiros deadlines e periodos
        {
          periodo_abs[k] = tarefas[k].p;
          deadline_abs[k] = tarefas[k].d;
          comp_abs[k] = 0;
        }
        else if(j % tarefas[k].p == 0) // reset do periodo, setar novos deadlines absolutos
        {
          periodo_abs[k] = ((j / tarefas[k].p)+1) * tarefas[k].p;
          deadline_abs[k] = (((j / tarefas[k].p)+1) * tarefas[k].p) - (tarefas[k].p - tarefas[k].d);
          comp_abs[k] = 0;
          //printf("Tarefa %d : tempo abs %d :  periodo abs %d : deadline abs %d : \n",k,j,periodo_abs[k],deadline_abs[k]);
        }

        //printf("Tarefa %d : Computacoes executadas: %d\n" ,k, comp_abs[k]);

        if(tarefas[k].c - comp_abs[k] != 0) // tarefa ainda n executou tudo
        {    
          int slack_aux = (deadline_abs[k] - j) - (tarefas[k].c - comp_abs[k]);
          
          //printf("tarefa %d : slack_aux %d \n", k,slack_aux);

          if(slack_aux < menor_slack)
          {
            menor_slack = slack_aux;
            tarefa_menor_slack = k;
          }
        }

      }

    comp_abs[tarefa_menor_slack]++;
    menor_slack = MAX_T;

    printf("%c",tarefas[tarefa_menor_slack].id);

    }

    printf("\n");







    grade[0] = tarefas[0].id;
    grade[1] = '.';
    grade[2] = '.';
    grade[3] = '\0';

    /*for(int j = 0; j < t; j++)
    {
      for(int k = 0; k < n_tarefas; k++)
      {
        slack_t[k] = d_abs[k] - t_abs - comp_restante[k];
      }
    }*/


    // ...
    // RESULTADOS

    //printf("%s\n%d %d\n\n", grade, num_preemp, num_trocas_cont);
  }
  return 0;
}

//comp_restante = computacoes - (tempo_absoluto - tempo_inicio)
// ou comp_restante = computacoes - comp_realizadas
//slack = (deadline_absoluto - tempo_absoluto - comp_restante)