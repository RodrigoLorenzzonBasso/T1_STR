#include <stdio.h>
#include <math.h>
#include <ctype.h>

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

  while (1) {
    // LEITURA //
    scanf("%d%d", &n_tarefas, &t);
    if (n_tarefas==0 || t==0)
       break;
    for (i=0; i<n_tarefas; ++i) {
       tarefas[i].id = 'A'+i;
       scanf("%d%d%d", &(tarefas[i].c), &(tarefas[i].p), &(tarefas[i].d) );
    }
    // SIMULACAO //

    num_preemp = 0;
    num_trocas_cont = 0;

    // declaracao de auxiliares
    int deadline_abs[n_tarefas];
    int periodo_abs[n_tarefas];
    int comp_abs[n_tarefas];
    char completa[n_tarefas];
    for(int j = 0; j < n_tarefas; j++)
      completa[j] = 0;
    int n_completas = 0;
    int menor_slack = MAX_T;
    int tarefa_menor_slack = 0;

    //execucao de cada tempo //
    for(int j = 0; j < t; j++)
    {
      // execucao para cada tarefa // 
      for(int k = 0; k < n_tarefas; k++)
      {
        // comecou a execucao, setar primeiros deadlines e periodos
        if(j == 0) 
        {
          periodo_abs[k] = tarefas[k].p;
          deadline_abs[k] = tarefas[k].d;
          comp_abs[k] = 0;
        }
        // reset do periodo, setar novos deadlines, periodos e computacoes absolutas
        else if((j % tarefas[k].p == 0) && (completa[k] == 1))
        {
          periodo_abs[k] = ((j / tarefas[k].p)+1) * tarefas[k].p;
          deadline_abs[k] = (((j / tarefas[k].p)+1) * tarefas[k].p) - (tarefas[k].p - tarefas[k].d);
          comp_abs[k] = 0;
          completa[k] = 0;
        }
        // tarefa foi completa apos o prazo
        else if((completa[k] == 1) && (deadline_abs[k] < j))
        {
          periodo_abs[k] = ((j / tarefas[k].p)+1) * tarefas[k].p;
          deadline_abs[k] = (((j / tarefas[k].p)+1) * tarefas[k].p) - (tarefas[k].p - tarefas[k].d);
          comp_abs[k] = 0;
          completa[k] = 0;
        }

        // se a tarefa ainda n foi concluida, calcular tempo de slack
        if(completa[k] == 0)
        {    
          int slack_aux = (deadline_abs[k] - j) - (tarefas[k].c - comp_abs[k]);

          if(slack_aux < menor_slack)
          {
            menor_slack = slack_aux;
            tarefa_menor_slack = k;
          }
        }
        // se foi concluida, aumenta numero de completas (se (completas == n_tarefas) entao o idle ganha o processador)
        else
        {
          n_completas++;
        }

      }

      // concluir uma computacao da tarefa com menor slack
      if(n_completas != n_tarefas)
      {
        comp_abs[tarefa_menor_slack]++;

        if((tarefas[tarefa_menor_slack].c - comp_abs[tarefa_menor_slack]) == 0)
          completa[tarefa_menor_slack] = 1;

        char id = tarefas[tarefa_menor_slack].id;

        // caso a tarefa perca o prazo, ela vai ser exibida em minuscula
        if(deadline_abs[tarefa_menor_slack] < j)
        {
          id = id + 32;
        }

        grade[j] = tarefas[tarefa_menor_slack].id;
      }
      // todas as tarefas foram concluidas
      else
      {
        grade[j] = '.';
      }
      
      menor_slack = MAX_T;
      n_completas = 0;

    }

    grade[t] = '\0';

    // RESULTADOS

    printf("%s\n%d %d\n\n", grade, num_preemp, num_trocas_cont);
  }
  return 0;
}