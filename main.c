#include<stdlib.h>
#include<stdio.h>
#define UNVISITED 0
#define VISITED 1
#define CLOSED 3

typedef struct list{
	int id;
    struct list * next;
}*list;

list stack_S = NULL;
int * G_s;
void Push (int ID);
int Pop();
list Insere(list head, int ID);
list New_share(list head, int ID);
void DFS_Visit (list * Graph, int id);
list Kosaraju(list * Graph, list * Graph_t, int N);

int main(){

    int i, id1, id2, N, P, scans, group_counter=0, group_size=0, max_group=0, ponto3=0, size, size2, j;
    scans = scanf("%d %d", &N, &P);
    if (scans != 2) exit(0);
    list G[N+1], G_t[N+1], aux=NULL, groups=NULL;
    G_s = calloc (N+1,sizeof(int));

	for (i=1; i<=N; i++){
        G[i] = NULL;
        G_t[i] = NULL;
        G_s[i] = UNVISITED;
    }

    for (i=1; i<=P; i++){
        scans = scanf("%d %d", &id1, &id2);
        if (scans != 2) exit(0);
        G[id1] = New_share(G[id1], id2);
        G_t[id2] = New_share(G_t[id2], id1);
    }

    groups = Kosaraju(G, G_t, N);
    aux = groups;

    while (aux != NULL){
        if (aux->id == -1) {
                group_counter++;
                if (group_size>max_group) max_group = group_size;
                group_size=0;
        }
        else group_size++;
        aux = aux->next;
    }

    for (i=1; i<=group_counter; i++){
        size=1;
        size2=0;
        while (groups->next->id != -1){
            size++;
            groups=groups->next;
        }
        stack_S = NULL;
        for (j=1; j<=N; j++) G_s[j] = UNVISITED;
        DFS_Visit(G, groups->id);
        while (stack_S!=NULL){
            size2++;
            Pop();
        }
        if (size2==size) ponto3++;
        groups=groups->next->next;
    }

    printf("%d\n%d\n%d\n", group_counter, max_group, ponto3);

    return 0;
}

list Kosaraju(list * Graph, list * Graph_t, int N){
    int i;
    list temp_S;

    for (i=1; i<=N; i++){
        if (G_s[i]==UNVISITED){
            DFS_Visit(Graph, i);
        }
    }

    temp_S = stack_S;
    stack_S = NULL;
    for (i=1; i<=N; i++){
        G_s[i] = UNVISITED;
    }
    Push(-1);

    while (temp_S!=NULL){
        i=temp_S->id;
        temp_S=temp_S->next;
        if (G_s[i]==UNVISITED){
            DFS_Visit(Graph_t, i);
            Push(-1);
        }
    }

    Pop();
    return stack_S;
}

list Insere(list head, int ID){
    list temp;
    temp = malloc(sizeof(struct list));
    temp->id = ID;
    temp->next = head;
    return temp;
}

list New_share(list head, int ID){
    return Insere(head, ID);
}

void Push (int ID){
    stack_S = Insere(stack_S, ID);
}

int Pop (){
    int temp;
    if (stack_S != NULL) {
            temp = stack_S->id;
            stack_S = stack_S->next;
            return temp;
    }
    else return -1;
}

void DFS_Visit (list * Graph, int id){
    list next = Graph[id];
    G_s[id] = VISITED;

    while (next!=NULL){
        if (G_s[next->id]==UNVISITED) DFS_Visit(Graph, next->id);
        next = next->next;
    }
    Push(id);
    G_s[id] = CLOSED;
}
