//bankers algorithm for deadlock avoidance
#include<stdio.h>
#include<stdlib.h>

int n,m;
int alloc[10][10],max[10][10],need[10][10],avail[10];
int finish[10],work[10];

int safe_sequence()
{
    int i,j,k;
    int ans[10];
    for(i=0;i<n;i++)
        finish[i]=0;
    for(i=0;i<m;i++)
        work[i]=avail[i];
    int flag=1;
    int count=0;
    while(flag)
    {
        flag=0;
        for(i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                for(j=0;j<m;j++)
                    if(need[i][j]>work[j])
                        break;
                if(j==m)
                {
                    ans[count]=i;
                    finish[i]=1;
                    flag=1;
                    for(k=0;k<m;k++)
                        work[k]+=alloc[i][k];
                }
                if(finish[i]==1)
                    count++;
            }
        }
    }
    for(i=0;i<n;i++){
        if(finish[i]==0){
            printf("No Safe Sequence");
            return 0;
        }
    }
    for(i=0;i<n;i++){
        printf("P%d ",ans[i]);
    }
    return 1;
}

void resource_request(int p,int req[])
{
    int i,j,k;

    for(i=0;i<m;i++)
        if(req[i]>need[p][i])
            break;

    if(i!=m)
    {
        printf("Error\n");
        return ;
    }

    for(i=0;i<m;i++)
        if(req[i]>avail[i])
            break;

    if(i!=m)
    {
        printf("Resources not available\n");
        return ;
    }

    for(i=0;i<m;i++)
    {
        avail[i]-=req[i];
        alloc[p][i]+=req[i];
        need[p][i]-=req[i];
    }
    if(safe_sequence())
        return;
    else{
        avail[i]+=req[i];
        alloc[p][i]-=req[i];
        need[p][i]+=req[i];
    }

    

}

int main()
{
    int i,j,ans;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("Enter number of resources: ");
    scanf("%d",&m);

    printf("Enter allocation matrix: ");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter max matrix: ");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&max[i][j]);

    printf("Enter available resources: ");
    for(i=0;i<m;i++)
        scanf("%d",&avail[i]);

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            need[i][j]=max[i][j]-alloc[i][j];

    while(1)
    {
        int ch,p;
        int req[10];
        printf("\n1.Safe sequence\n2.Resource request\n3.Exit\nEnter choice : ");
        scanf("%d",&ch);
        if(ch==1)
            ans = safe_sequence();
        else if(ch==2)
        {
            printf("Enter process number : ");
            scanf("%d",&p);
            printf("Enter request : ");
            for(i=0;i<m;i++)
                scanf("%d",&req[i]);
            resource_request(p,req);
        }
        else
            break;
    }

}
