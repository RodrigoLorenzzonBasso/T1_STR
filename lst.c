#include <stdio.h>
#include <ctype.h>

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

    // execucao de cada tempo + 1 //
    for(int j = 0; j < t + 1; j++)
    {
      // execucao para cada tarefa // 
      for(int k = 0; k < n_tarefas; k++)
      {
        
        // Primeira execucao, resetar as informacoes absolutas das tarefas
        if(j == 0) 
        {
          periodo_abs[k] = tarefas[k].p;
          deadline_abs[k] = tarefas[k].d;
          comp_abs[k] = 0;
        }

        // Testar se a tarefa esta completa
        if(((tarefas[k].c - comp_abs[k]) == 0) && completa[k] != 1)
        {
          completa[k] = 1;
          n_completas++;
        }

        // Reset dos absolutos se a tarefa foi completa
        if((completa[k] == 1) && (j % tarefas[k].p == 0))
        {
          periodo_abs[k] = ((j / tarefas[k].p)+1) * tarefas[k].p;
          deadline_abs[k] = (((j / tarefas[k].p)+1) * tarefas[k].p) - (tarefas[k].p - tarefas[k].d);
          comp_abs[k] = 0;
          completa[k] = 0;
          n_completas--;
        }

        // se ela nao foi, calcular o slack
        if(completa[k] == 0)
        {    
          int slack_aux = (deadline_abs[k] - j) - (tarefas[k].c - comp_abs[k]);

          if(slack_aux < menor_slack)
          {
            menor_slack = slack_aux;
            tarefa_menor_slack = k;
          }
          else if(slack_aux == menor_slack)
          {
            if(k < tarefa_menor_slack)
            {
              menor_slack = slack_aux;
              tarefa_menor_slack = k;            
            }
          }
        }
      } // execucao para cada tarefa

      // concluir uma computacao da tarefa com menor slack se tiver alguma ainda nao completa
      if(n_completas != n_tarefas)
      {
        char id = tarefas[tarefa_menor_slack].id;

        // o slack da tarefa que vai executar e negativo, portanto ela perdeu o prazo
        if(menor_slack < 0)
        {
          id = tolower(id);
        }

        comp_abs[tarefa_menor_slack]++;
        grade[j] = id;
      }
      // se nao executa idle
      else
      {
        grade[j] = '.';
      }
      
      // para cada tempo exceto o primeiro, calcular se houve troca de contexto ou preempcao
      if(j != 0)
      {
        // a tarefa que estava executando mudou
        if(grade[j] != grade[j-1])
        {
          num_trocas_cont++;

          // calculo do indice da tarefa anterios
          int id_anterior = toupper(grade[j-1]) - 65;

          // se houve troca de um idle, houve preempcao
          if(grade[j-1] == '.')
          {
            num_preemp++;
          }
          // se houve troca de uma tarefa que ainda n tinha sido completa, houve preempcao
          else if((completa[id_anterior] == 0) && (j % tarefas[id_anterior].p != 0))
          {
            num_preemp++;
          }
        }
      }

      menor_slack = MAX_T;

    } // para cada tempo

    grade[t] = '\0';

    // RESULTADOS

    printf("%s\n%d %d\n\n", grade, num_trocas_cont, num_preemp);
  }
  return 0;
}