#include <stdio.h>

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
  int n, t, i;
  char grade[MAX_T+1];
  int num_preemp, num_trocas_cont;

  while (1) {
    // LEITURA
    scanf("%d%d", &n, &t);
    if (n==0 || t==0)
       break;
    for (i=0; i<n; ++i) {
       tarefas[i].id = 'A'+i;
       scanf("%d%d%d", &(tarefas[i].c), &(tarefas[i].p), &(tarefas[i].d) );
    }
    // SIMULACAO
    num_preemp = 0;
    num_trocas_cont = 0;
    grade[0] = '.';
    grade[1] = '.';
    grade[2] = '.';
    grade[3] = '\0';
    // ...
    // RESULTADOS
    printf("%s\n%d %d\n\n", grade, num_preemp, num_trocas_cont);
  }
  return 0;
}