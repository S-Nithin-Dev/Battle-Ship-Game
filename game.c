#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int score;
    char *grid[10];
    char *hit[10];
}game;
void getinput(char *p[10],int,int);
void showgrid(char *q[10],int);
void sink(char *r[10],char *s[10],int);

int main()
{
    game player[2];
    int n,i,j,x,k,chance=0;
    FILE *fp=fopen("output.txt","w");
    do{
        printf("Battle ground size\n");
        scanf("%d",&n);
    }while(n<=2);
    for(i=0;i<n;i++){
        player[0].grid[i]=(char *)malloc(n*sizeof(char));
        player[0].hit[i]=(char *)malloc(n*sizeof(char));
        player[1].grid[i]=(char *)malloc(n*sizeof(char));
        player[1].hit[i]=(char *)malloc(n*sizeof(char));

    }
    getinput(player[0].grid,n,1);
    getinput(player[1].grid,n,2);
    player[0].score=0;
    player[1].score=0;
    for(i=0;i<2;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                *(*(player[i].hit+j)+k)='_';
            }
        }
    }
    while(chance<10){
        if(player[0].score==6||player[1].score==6){
            if(player[0].score==6){
                fprintf(fp,"Congratulations player1!!You win!");
                printf("\nCongratulations player1!!\nYou win!\n");
                break;
            }
            else{
                fprintf(fp,"Congratulations player2!!You win!");
                printf("\nCongratulations player2!!\nYou win!\n");
                break;
            }
        }

        else{
            int r1,r2,c1,c2;
            printf("\nPlayer1's turn\n");
            showgrid(player[0].hit,n);
            printf("Row value:");
            scanf("%d",&r1);
            r1=r1-1;
            printf("Column  value:");
            scanf("%d",&c1);
            c1=c1-1;

            if(player[1].grid[r1][c1]=='d'||player[1].grid[r1][c1]=='s'||player[1].grid[r1][c1]=='t'){
                printf("It was a hit!\n");
                *(*(player[0].hit+r1)+c1)=*(*(player[1].grid+r1)+c1);
                ++player[0].score;
                fprintf(fp,"%s= %d\n","player 1 score",player[0].score);
                sink(player[1].grid,player[0].hit,n);
            }
            else{
                printf("It was a miss\n");
    	        *(*(player[0].hit+r1)+c1)='m';
            }
            printf("\nPlayer2 will play\n");
            showgrid(player[1].hit,n);
            printf("Row value:");
            scanf("%d",&r2);
            r2=r2-1;
            printf("Column  value:");
            scanf("%d",&c2);
            c2=c2-1;

            if(player[0].grid[r2][c2]=='d'||player[0].grid[r2][c2]=='s'||player[0].grid[r2][c2]=='t'){
                printf("It was a hit!\n");
                *(*(player[1].hit+r2)+c2)= *(*(player[0].grid+r2)+c2);
                player[1].score++;
                fprintf(fp,"%s= %d\n","player 2 score",player[1].score);
                sink(player[0].grid,player[1].hit,n);
            }
            else{
                printf("it was a miss\n");
                *(*(player[1].hit+r2)+c2)='m';
            }
            chance=chance+1;
        }
    }
    if(chance==10){
        printf("It's a draw\n");
        fprintf(fp,"It's a draw");
    }
    fclose(fp);
    return 0;
}
void getinput(char *grid[10],int n,int p){
    int i,j,row,col;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            *(*(grid+i)+j)='_';
        }
    }
    char align;
    printf("Player %d can play\n\n",p);
    printf("There are 3 ships named as Destroyer, Swift, Titanic\n");
    for(i=1;i<=3;i++){
        printf("Size of ship:%d\n",i);
        if(i==1){
            printf("Destroyer ship\nRow number:");
            scanf("%d",&row);
            printf("Enter column:");
            scanf("%d",&col);
            row-=1;col-=1;
            *(*(grid+row)+col)='d';
        }
        else{
            if(i==2) printf("Swift ship\n");
            else printf("Titanic ship\n");
            do{
                printf("Specify the alignment:");
                scanf("\n");
                scanf("%c",&align);
            }
            while(align!='h' && align!='v');
           do{
                printf("Row number:");
                scanf("%d",&row);
                printf("Enter column:");
                scanf("%d",&col);
                row-=1;col-=1;

            }
            while(*(*(grid+row)+col)=='d'||*(*(grid+row)+col)=='s'||*(*(grid+row)+col)=='t');
            if(align=='h'){
                if(i==2){
                    *(*(grid+row)+col)='s';
                    *(*(grid+row)+col+1)='s';
                }
                else{
                    *(*(grid+row)+col)='t';
                    *(*(grid+row)+col+1)='t';
                    *(*(grid+row)+col+2)='t';

                }
            }
            else{
                if(i==2){
                    *(*(grid+row)+col)='s';
                    *(*(grid+row+1)+col)='s';
                }
                else{
                    *(*(grid+row)+col)='t';
                    *(*(grid+row+1)+col)='t';
                    *(*(grid+row+2)+col)='t';

                }

            }

        }
        showgrid(grid,n);


    }
}
void showgrid(char *grid[10],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf(" %c ",*(*(grid+i)+j));
        }printf("\n");
    }

}
void sink(char *grid[10],char *hit[10],int n){
    int i,j,s=0,t=0,d=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(*(*(hit+i)+j)=='d' && d==0){
                d++;
                printf("destroyer ship was sunk\n");
            }
            else if(*(*(hit+i)+j)=='s' && s<2){
                s++;
                if(s==2)
                printf("swift ship was sunk\n");
            }
            else if(*(*(hit+i)+j)=='t' && t<3){
                t++;
                if(t==3)
                printf("titanic ship was sunk\n");
            }
        }
    }
}
