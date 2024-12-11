
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct
{
    int DA; //Date Arrive
    int TE; //Temps exuction
    int pr;  //priority
    int temfin; //Temps fin
    int TR;  //Temps de Reponse
    int TA;  //Temps Attende
    int file; //fichier (1 = F1, 2 = F2, 3 = F3)

    int reste;
    int executed;
    int arrived;
    int turn;

}process;

int main()
{
    //Variables
    int i,j,nb = 6;
    int k = 0;
    int s = -1;

    process* proc;

    proc =( process *)malloc(sizeof( process )*nb);

    proc[0].DA = 3;
    proc[0].pr = 6;
    proc[0].TE = 4;

    proc[1].DA = 5;
    proc[1].pr = 1;
    proc[1].TE = 5;

    proc[2].DA = 2;
    proc[2].pr = 2;
    proc[2].TE = 8;

    proc[3].DA = 2;
    proc[3].pr = 5;
    proc[3].TE = 2;

    proc[4].DA = 4;
    proc[4].pr = 8;
    proc[4].TE = 7;

    proc[5].DA = 0;
    proc[5].pr = 4;
    proc[5].TE = 3;

    printf("\n");
    printf("Processus \t DA\t Pr\t TE\n");

    for(i = 0; i < nb;i++)
    {
        printf("p(%d)\t\t %dms \t %dms \t %dms\n",i+1, proc[i].DA, proc[i].pr, proc[i].TE);

        if(proc[i].TE >= 1 && proc[i].TE <= 3)
        {
            proc[i].file = 1;
        }
        else if(proc[i].TE >= 4 && proc[i].TE <= 6)
        {
            proc[i].file = 2;
        }
        else if(proc[i].TE >= 7 && proc[i].TE <= 10)
        {
            proc[i].file = 3;
        }

        proc[i].reste = 0;
        proc[i].executed = 0;
        proc[i].arrived = 0;
        proc[i].turn = 0;
        k = k + proc[i].TE;
    }
    printf("\n");

    printf("k = %d\n",k);

    int currentFile = 1;
    i = 0;

    while(i < k)
    {

        for(j = 0; j < nb; j++)
        {

            if(proc[j].arrived == 0 && proc[j].DA <= i)
            {
                proc[j].arrived = 1;
                proc[j].reste = 1;
            }
            

            if(proc[j].reste == 1 && proc[j].file == currentFile)
            {
                if(s != -1)
                {
                    if(proc[j].turn == 0 && proc[s].turn == 1)
                    {
                        proc[j].turn = 1;
                        proc[s].turn = 0;
                        s = j;
                    }
                    else if(proc[j].turn == 1 && proc[s].turn == 0)
                    {
                        proc[j].turn = 0;
                        proc[s].turn = 1;
                    }
                    else
                    {
                        if(proc[j].pr < proc[s].pr)
                        {
                            s = j;
                        }
                    }
                }
                else
                {
                    s = j;
                }
            }
        }
        
        proc[s].turn = 1;
        
        if(s != -1)
        {
            int counter = 0;

            while(proc[s].executed != proc[s].TE && counter < currentFile)
            {
                counter++;
                proc[s].executed++;
            }
                
            if(proc[s].executed == proc[s].TE)
            {
                proc[s].temfin = i + counter;
                proc[s].reste = 2;
            }

            if(currentFile < 3)
            {
                currentFile++;
            }
            else
            {
                currentFile = 1;
            }

            s = -1;
            i = i + counter;
            
        }
        else
        {
            if(currentFile < 3)
            {
                currentFile++;
            }
            else
            {
                currentFile = 1;
            }
        }

    }

    printf("TEMPS FIN DE PROCESSUS: \n");

    for(j = 0; j < nb; j++)
    {
        printf("proc[%d] = %d \n", j + 1, proc[j].temfin);
    }

    printf("TEMPS DE REPONSE DE PROCESSUS: \n");

    for(j = 0; j < nb; j++)
    {
        proc[j].TR = proc[j].temfin - proc[j].DA;
        printf("proc[%d] = %d \n", j + 1, proc[j].TR);
    }

    printf("TEMPS D'ATTENDE DE PROCESSUS: \n");

    for(j = 0; j < nb; j++)
    {
        proc[j].TA = proc[j].TR - proc[j].TE;
        printf("proc[%d] = %d \n", j + 1, proc[j].TA);
    }

}

