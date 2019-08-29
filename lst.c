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
    num_preemp = 0;
    num_trocas_cont = 0;

    int n_execucoes[n_tarefas];

    for(int j = 0; j < n_tarefas; j++)
    {
      n_execucoes[j] = ceil((float)t/(float)tarefas[j].p);
    }

    





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
    printf("%s\n%d %d\n\n", grade, num_preemp, num_trocas_cont);
  }
  return 0;
}

//comp_restante = computacoes - (tempo_absoluto - tempo_inicio)
// ou comp_restante = computacoes - comp_realizadas
//slack = (deadline_absoluto - tempo_absoluto - comp_restante)