#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
typedef struct data{
    int train_no;
    char src[100];
    char des[100];
    char time[5];
    int isCancelled;
    int isWaiting;
    struct data *next;
}DATA;

typedef struct reserve{
    int train_no;
    char name[100];
    int age;
    char gender[5];
    int pnr_no;
    int ticket_price;
    int discount;
    int category;
    int class;
    char src[100];
    char des[100];
    char time[5];
    int tax;
    int isCancelled;
    int isWaiting;
    int seat_no;
    struct reserve *next;
}RESERVE;
typedef struct bstree{
    int train_no;
    char pname[100];
    int age;
    char gender[100];
    int pnr_no;
    char cgt[20];
    char class[10];
    int tprice;
    char sname[100];
    char dname[100];
    char time[100];
    int cancel;
    int seatno;
    int wlIst;
    struct bstree *left;
    struct bstree *right;
}BSTREE;

typedef struct cancel{
    int train_no;
    char name[100];
    int age;
    char gender[6];
    int pnr_no;
    char category[10];
    char class[5];
    int ticket_price;
    char src[100];
    char des[100];
    char time[5];
    int seat_no;
    int isCancelled;
    int isWaiting;

    struct cancel *next;
}CANCEL;

typedef struct modify{
    int train_no;
    char name[100];
    int age;
    char gender[60];
    int pnr_no;
    char category[100];
    char class[50];
    int ticket_price;
    char src[100];
    char des[100];
    char time[50];
    int ismodifyled;
    int isWaiting;
    int seat_no;
    struct modify *next;
}MODIFY;
MODIFY *headp=NULL;
//------------------TASK:1-----------------------------
int COUNT=0;
DATA *head=NULL;
RESERVE *head1=NULL;

DATA *insertData(DATA *data)
{
    DATA *insertNode=(DATA *)malloc(sizeof(DATA));
    insertNode->train_no=data->train_no;   
    strcpy(insertNode->src,data->src);
    strcpy(insertNode->des,data->des);
    strcpy(insertNode->time,data->time);
    insertNode->isCancelled=data->isCancelled;
    insertNode->isWaiting=data->isWaiting;


    if(head==NULL)
    {
        head=insertNode;
        head->next=NULL;
    }
    else
    {

        insertNode->next=head;
        head=insertNode;

    }

    return head;

}

//-------------------------------------------LOAD INPUT TRAINS-----------------------------------------//

DATA *load_data(FILE  *fp)
{
    int i=0,j=0,k=0,m;
    char c,A[30],name[20];
    fp=fopen("input_data.txt","r");
    DATA *data=(DATA *)malloc(sizeof(DATA));
    data->next=NULL;
    while(fscanf(fp,"%c",&c)>0)
    {

        if(k<5)
        {
            if(c!=',')
            {
                A[j++]=c;
            }
            else
            {

                switch(k){
                    case 0:
                        A[j]='\0';
                        data->train_no=atoi(A);
                        j=0;
                        k++;
                        break;

                    case 1:

                        A[j]='\0';
                        strcpy(data->src,A);
                        j=0;
                        k++;
                        break;
                    case 2:
                        A[j]='\0';
                        strcpy(data->des,A);
                        j=0;
                        k++;
                        break;
                    case 3:

                        A[j]='\0';
                        strcpy(data->time,A);
                        j=0;
                        k++;
                        break;   
                    case 4:

                        A[j]='\0';
                        data->isCancelled=atoi(A);
                        j=0;
                        k++;
                        //    printf("%d*************\n",k);
                        break;
                    case 5:

                        A[j]='\0';
                        data->isWaiting=atoi(A);
                        j=0;
                        k++;
                        break;
                }

            }
        }
        else
        {
            k=0;       
            head=insertData(data);
            DATA* data=(DATA *)malloc(sizeof(DATA));
        }
    }
    fclose(fp);
    return head;
}
//------------------FUNCTION TO VIEW AVAILABLE TRAINS-----------------------------------
void view_data(DATA *data)
{
    DATA *p=data;

    while(p!=NULL)
    {

        printf("%d  %s  %s  %s  %d  %d\n",p->train_no,p->src,p->des,p->time,p->isCancelled,p->isWaiting);
        p=p->next;
    }


}
//-----------------------ESTIMATING SEAT NUMBER------------------------------------------

int seat_no(FILE *fp1,int p)
{
    fp1=fopen("reservation.txt","r");
    char c[100],s[50];
    int c1=0,i,j,k;
    j=1;
    while(fscanf(fp1,"%s",c)>0)
    {c1++;
        for(i=0;i<5;i++)
        {
            s[i]=c[i];
        }
        s[i]='\0';

        k=atoi(s);

        if(k==p)
        {
            j++;   
        }
    }

    if(c1==0)
    {
        return 1;
    }
    else
    {
        return j;
    }
    fclose(fp1);
}

//-----------------------------APPLYING DISCOUNTS-----------------------------------
int applydiscounts(int counter,int j)
{
    int discount;


    if(counter==4)
    {
        if(j==0){
            discount=10;
        }
        else if(j==1)
        {
            discount=7;
        }
        else if(j==2)
        {
            discount=5;
        }
        else
        {
            discount=0;
        }
    }
    else if(counter==3)
    {
        if(j==0){
            discount=8;
        }
        else if(j==1){
            discount=5;
        }
        else{
            discount=0;
        }
    }
    else
    {
        discount=0;
    }
    return discount;

}
//-------------------------------ESTIMATING PRICE--------------------------------------


int estimateprice(int j)
{
    int price;       
    if(j==0)
    {
        price=500;
    }
    if(j==1)
    {
        price=450;
    }
    if(j==2)
    {
        price=400;
    }
    if(j==3)
    {
        price=350;
    }
    if(j==4)
    {
        price=300;
    }
    return price;                   
}

//-----------------------CREATING NEW BOOKING-------------------------------------

RESERVE *load_bookings(DATA *data)
{
    char name[25],src[25],des[25],gender[6];
    char g[6]="Female";
    int age,counter,i,j,k,l,discount,c=0,z,price;
    //fp1=fopen("reservation.txt","r");
    DATA *p=data;
    int count=0;
    int pnrr;
    RESERVE *reserve=(RESERVE *)malloc(sizeof(RESERVE));
    srand((unsigned int)time NULL);
    printf("ENTER YOUR SOURCE STATION:\n");
    scanf("%s",src);
    printf("ENTER YOUR DESTINATION STATION:\n");
    scanf("%s",des);
       // gets();
    while(p!=NULL)
    {
        if(strcmp(p->src,src)==0 && strcmp(p->des,des)==0)
        {


            c++;
            printf("HOW MANY TICKETS YOU REQUIRE:\n");
            printf("YOU CAN HAVE MAXIMUM OF 4\n");
            scanf("%d",&counter);
            if(counter<=4)
            {
                for(k=0;k<counter;k++)
                {
                    printf("ENTER YOUR NAME:\n");
                    scanf("%s",name);
                    printf("ENTER YOUR AGE:\n");
                    scanf("%d",&age);
                    printf("ENTER GENDER:F/M\n");
                    scanf("%s",gender);
                    reserve->train_no=p->train_no;
                    //pnrr=reserve->train_no;
                    strcpy(reserve->name,name);
                    reserve->age=age;
                    strcpy(reserve->gender,gender);
                    l=rand()%1000000;
                    reserve->pnr_no=l;
                    i=rand()%(2-0)+0;
                    j=rand()%(5-0)+0;

                    if(strcmp(g,reserve->gender)==0)
                    {
                        reserve->category=2;
                    }
                    else{
                        reserve->category=i;
                    }
                    reserve->class=j;   

                    

                    price=estimateprice(j);
                 
                    discount=applydiscounts(counter,j);
                    reserve->ticket_price=price;
                    reserve->discount=discount;
                    strcpy(reserve->src,src);
                    strcpy(reserve->des,des);
                    strcpy(reserve->time,p->time);
                    reserve->tax=2;
                    reserve->isCancelled=0;
                    reserve->isWaiting=0;

                    reserve->next=NULL;

                    if(head1==NULL)
                    {
                        head1=reserve;
                        head1->next=NULL;
                        reserve=(RESERVE *)malloc(sizeof(RESERVE));
                    }
                    else
                    {

                        reserve->next=head1;
                        head1=reserve;
                        reserve=(RESERVE *)malloc(sizeof(RESERVE));
                    }

                }

                break;
            }

            else
            {
                printf("YOU CAN HAVE ONLY MAXIMUM OF 4 TICKETS\n");
            }

        }
        p=p->next;
    }
    if(c==0)
    {
        printf("THERE IS NO TRAIN BETWEEN THESE STATIONS\n");
    }

    return head1;
}

//------------------------- ESTIMATE FINAL BOOKING PRICE-------------------------------------------

int final_booking_price(int i,int j,int l)
{
    int k;
    k=i-((j*i)/100)+((l*i)/100);
    return k;
}
//-------------------------WAITING LIST-----------------------------------------------
int waitinglist(FILE *fp,int pnr)
{
    fp=fopen("reservation.txt","r");
    char s[100],c[10],f[10][20],temp[30];
    int i,k,j,count=0,q=0,o,r=0;
    while(fscanf(fp,"%s",s)>0)
    {
        for(i=0;i<5;i++)
        {
            c[i]=s[i];
        }
        c[i]='\0';
        k=atoi(c);
        //i=0;
        if(k==pnr)
        {
        for(j=0;j<strlen(s);j++)
        {
            if(s[j]==',')
            {
                count++;
            }
            if(count==12 && s[j]!=',')
            {
                    f[q][r]=s[j];
                    r++;
                    printf("%c  \n",s[j]);
            }
        }
        f[q][r]='\0';
        q++;
        r=0;
        count=0;
        //printf("%s************************\n",f);
        //q=0;
        //o=atoi(f);
       
                }
           }
           fclose(fp);
               /* for(i=0;i<q;i++){
        printf("%s?$\n",f[i]);
        }*/
    for(i=0;i<q;i++)
    {
            for(j=i;j<q;j++)
            {
                    if(strcmp(f[i],f[j])==0)
                    {
                            strcpy(temp,f[i]);
                            strcpy(f[i],f[j]);
                            strcpy(f[j],temp);
                    }
             }
     }
     o=atoi(f[q-1]);
     return o+1;
       
       
}
//--------------------------FUNCTION TO VIEW BOOKINGS-----------------------------------------------
void view_reserved(RESERVE *reserve,FILE *fp1)
{
    char s[2],a[7];
    int i,z,counter=0,count=0;   
    fp1=fopen("reservation.txt","a+");
    while(reserve!=NULL)
    {
        //counter++;
        fprintf(fp1,"%d",reserve->pnr_no);
        fprintf(fp1,",");
        fprintf(fp1,"%s",reserve->name);
        fprintf(fp1,",");
        fprintf(fp1,"%d",reserve->age);
        fprintf(fp1,",");
        fprintf(fp1,"%s",reserve->gender);
        fprintf(fp1,",");
        fprintf(fp1,"%d",reserve->train_no);
        fprintf(fp1,",");
        i=final_booking_price(reserve->ticket_price,reserve->discount,reserve->tax);
        if(reserve->category==1)
        {
            fprintf(fp1,"%s","Tatkal");
        }
        else if(reserve->category==0)
        {
            fprintf(fp1,"%s","General");
        }
        else if(reserve->category==2)
        {
            fprintf(fp1,"%s","Ladies");
        }
        fprintf(fp1,",");
        if(reserve->class==0)
        {
            fprintf(fp1,"%s","SL");
        }
        else if(reserve->class==1)
        {
            fprintf(fp1,"%s","1A");
        }
        else if(reserve->class==2)
        {
            fprintf(fp1,"%s","2A");
        }
        else if(reserve->class=3)
        {
            fprintf(fp1,"%s","3A");
        }
        else if(reserve->class=4)
        {
            fprintf(fp1,"%s","CC");
        }

        fprintf(fp1,",");

        fprintf(fp1,"%d",i);
        fprintf(fp1,",");   
        fprintf(fp1,"%s",reserve->src);       
        fprintf(fp1,",");
        fprintf(fp1,"%s",reserve->des);
        fprintf(fp1,",");
        fprintf(fp1,"%s",reserve->time);
        fprintf(fp1,",");
        z=seat_no(fp1,reserve->train_no);
        z+=counter;
        if(z>5)
        {
            reserve->isWaiting=count+waitinglist(fp1,reserve->train_no);
            count++;
            z=0;
           
        }
        fprintf(fp1,"%d",reserve->isCancelled);
        fprintf(fp1,",");
        fprintf(fp1,"%d",reserve->isWaiting);       
        fprintf(fp1,",");
        fprintf(fp1,"%d",z);       
        fprintf(fp1,",");
        fprintf(fp1,"\n");
        printf("\n");
        printf("The actual ticket price is: %d\n",reserve->ticket_price);
        printf("The discount given by us is: %d percentage\n",reserve->discount);
        printf("The tax on the ticket is %d\n",reserve->tax);
        printf("The Final booking price is %d\n",i);
        printf("\n");
        //printf("%d %s %d %s %d %d %d %d %s %s %s %d %d %d\n",reserve->train_no,reserve->name,reserve->age,reserve->gender,reserve->ticket_no,reserve->category,reserve->class,i,reserve->src,reserve->des,reserve->time,reserve->isCancelled,reserve->isWaiting,z);
        printf("\n");
        reserve=reserve->next;
        counter++;
    }
    fclose(fp1);
//    waitinglist(fp1);
}
//---------------FUNCTION TO VIEW FROM RESERVATION FILE------------------------------------

void view_bookings(FILE *fp)
{
    fp=fopen("reservation.txt","r");
    char c[100];
    while(fscanf(fp,"%s",c)>0)
    {
        printf("%s\n",c);
    }
    fclose(fp);
}
//--------------------FUNCTION TO VERIFY BOOKING-------------------------
void confirm_booking(FILE *fp,int pnr_no)
{
        char s[100],n[10],n1[5];
        fp=fopen("reservation.txt","r");
    int counter=0,l,i,k=0,m,m1,j=0,count=0;
    while(fscanf(fp,"%s",s)>0)
    {
    //printf("%s\n",s);
            l=strlen(s);
            for(i=0;i<l;i++)
            {
                    if(s[i]==',')
                    {
                            counter++;
                    }
                    if(s[i]!=',' && counter==0)
                    {
                            n[k]=s[i];
                            k++;
                    }
                    if(s[i]!=',' && counter==12)
                    {
                            n1[j]=s[i];
                            j++;
                    }
                  
            }
            m=atoi(n);
             m1=atoi(n1);
           // printf("%d %d",m,m1);
          
            if(m==pnr_no && m1==0)
            {
                    count++;
                   
                    printf("THE BOOKING IS CONFIRMED\n");

            }
                k=0;
                j=0;
               counter=0;
    }
    if(count==0)
    {
            printf("THE BOOKING IS NOT CONFIRMED\n");
 
    }
    fclose(fp);
}

//-----------------------TASK:4------------------------------------------------


CANCEL *headc1=NULL;
CANCEL *headc2=NULL;
CANCEL *insertdata1(CANCEL *cancel)
{

    CANCEL *insertNode=(CANCEL *)malloc(sizeof(CANCEL));
    insertNode->train_no=cancel->train_no;
    strcpy(insertNode->name,cancel->name);
    insertNode->age=cancel->age;
    strcpy(insertNode->gender,cancel->gender);
    insertNode->pnr_no=cancel->pnr_no;
    strcpy(insertNode->category,cancel->category);
    strcpy(insertNode->class,cancel->class);
    insertNode->ticket_price=cancel->ticket_price;
    strcpy(insertNode->src,cancel->src);
    strcpy(insertNode->des,cancel->des);
    strcpy(insertNode->time,cancel->time);
    insertNode->isCancelled=cancel->isCancelled;
    insertNode->isWaiting=cancel->isWaiting;
    insertNode->seat_no=cancel->seat_no;

    if(headc1==NULL)
    {
        headc1=insertNode;
        headc1->next=NULL;
    }
    else
    {

        insertNode->next=headc1;
        headc1=insertNode;

    }

    return headc1;

}

//---------------------------THIS FUNCTION IS TO LOAD THE DATA FROM RESERVATION FILE-------------------------------------------

CANCEL *load_reserved(FILE *fp)
{    int i=0,j=0,k=0,m;
    char c,A[100];
    fp=fopen("reservation.txt","r");
    CANCEL *cancel=(CANCEL *)malloc(sizeof(CANCEL));
    cancel->next=NULL;
    while(fscanf(fp,"%c",&c)>0)
    {
        if(k<14)
        {
            if(c!=',')
            {
                A[j++]=c;
            }
            else
            {

                switch(k){
                    case 0:
                        A[j]='\0';
                        cancel->pnr_no=atoi(A);
                        j=0;
                        k++;
                        break;

                    case 1:

                        A[j]='\0';
                        strcpy(cancel->name,A);
                        j=0;
                        k++;
                        break;
                    case 2:
                        A[j]='\0';
                        cancel->age=atoi(A);
                        j=0;
                        k++;
                        break;
                    case 3:

                        A[j]='\0';
                        strcpy(cancel->gender,A);
                        j=0;
                        k++;
                        break;   
                    case 4:

                        A[j]='\0';
                        cancel->train_no=atoi(A);
                        j=0;
                        k++;
                        break;
                    case 5:

                        A[j]='\0';
                        strcpy(cancel->category,A);
                        j=0;
                        k++;
                        break;


                    case 6:

                        A[j]='\0';
                        strcpy(cancel->class,A);
                        j=0;
                        k++;
                        break;


                    case 7:

                        A[j]='\0';   
                        cancel->ticket_price=atoi(A);   
                        j=0;
                        k++;
                        break;


                    case 8:

                        A[j]='\0';
                        strcpy(cancel->src,A);   
                        j=0;
                        k++;
                        break;


                    case 9:

                        A[j]='\0';
                        strcpy(cancel->des,A);   
                        j=0;
                        k++;
                        break;



                    case 10:

                        A[j]='\0';
                        strcpy(cancel->time,A);   
                        j=0;
                        k++;
                        break;


                    case 11:

                        A[j]='\0';
                        cancel->isCancelled=atoi(A);   
                        j=0;
                        k++;
                        break;


                    case 12:

                        A[j]='\0';
                   
                        cancel->isWaiting=atoi(A);   
                        j=0;
                        k++;
                       
                        break;

                    case 13:

                        A[j]='\0';
                        cancel->seat_no=atoi(A);   
                        j=0;
                        k++;
                        break;   
                }

            }
        }
        else
        {
            k=0;       
            headc1=insertdata1(cancel);
            CANCEL* cancel=(CANCEL *)malloc(sizeof(CANCEL));
        }
    }
    fclose(fp);
    return headc1;



}

//-----------------------------TO VIEW THE RESERVED TICKETS------------------------------------------

void view_reservedtickets(CANCEL *cancel)
{
    CANCEL *p=cancel;
        printf("THE RESERVED TICKETS ARE:\n");
    while(p!=NULL)
    {

        printf("%d  %s  %d  %s  %d  %s  %s  %d  %s  %s  %s  %d  %d %d\n",p->pnr_no,p->name,p->age,p->gender,p->train_no,p->category,p->class,p->ticket_price,p->src,p->des,p->time,p->isCancelled,p->isWaiting,p->seat_no);
        p=p->next;
    }


}

//--------------------------------------FUNCTION TO VIEW DELETED HISTORY---------------------------------------------

void view_deletehistory(FILE *fp)
{
    fp=fopen("cancel.txt","r");
    char c;
    while(fscanf(fp,"%c",&c)>0)
    {
        printf("%c",c);
    }
    fclose(fp);
}
//----------------------------------FUNCTION TO CANCEL THE TICKET--------------------------------
void deletenode(CANCEL *cancel,int n)
{
    CANCEL *p=cancel;
    FILE *fp2=fopen("cancel.txt","a+");
    CANCEL *r=(CANCEL *)malloc(sizeof(CANCEL));
    char c;
    int pos=0,i,c1=0;
    while(cancel!=NULL)
    {

        if(cancel->pnr_no==n)
        {
            c1++;
            break;
        }
        pos++;

        cancel=cancel->next;   

    }
    if(c1==0)
    {
        printf("THE TICKET NUMBER YOU ENTERED IS INVALID\n");
    }
    else
    {
        if(pos==0)
        {
            r=p;
            p=p->next;   
        }
        else
        {
            for(i=0;i<pos-1;i++)
            {
                p=p->next;
            }

            r=p->next;
            p->next=p->next->next;       
        }
                   
        fprintf(fp2,"%d",r->pnr_no);
        fprintf(fp2,",");
        fprintf(fp2,"%s",r->name);
        fprintf(fp2,",");
        fprintf(fp2,"%d",r->age);
        fprintf(fp2,",");
        fprintf(fp2,"%s",r->gender);
        fprintf(fp2,",");
        fprintf(fp2,"%d",r->train_no);
        fprintf(fp2,",");
        fprintf(fp2,"%s",r->category);
        fprintf(fp2,",");
        fprintf(fp2,"%s",r->class);
        fprintf(fp2,",");
        fprintf(fp2,"%d",r->ticket_price);
        fprintf(fp2,",");   
        fprintf(fp2,"%s",r->src);       
        fprintf(fp2,",");
        fprintf(fp2,"%s",r->des);
        fprintf(fp2,",");
        fprintf(fp2,"%s",r->time);
        fprintf(fp2,",");
        r->isCancelled=1;
        fprintf(fp2,"%d",r->isCancelled);
        fprintf(fp2,",");
        fprintf(fp2,"%d",r->isWaiting);
        fprintf(fp2,",");
        fprintf(fp2,"%d",r->seat_no);
        fprintf(fp2,",");
        fprintf(fp2,"\n");

                free(r);
    }
    fclose(fp2);
   
}


//-----------------------------------FUNCTION TO CONFIRM CANCELLATION----------------------------

void confirmcancellation(FILE *fp3,char n[])
{
    int i,j=0,count,count1=0;
    char A[100],s[20];
    while(fscanf(fp3,"%s",A)>0)
    {

        int l=strlen(A);
        count=0;j=0;
        for(i=0;i<l;i++)
        {
            if(A[i]==','){
                count++;
            }
            if(count==0 && A[i]!=','){
                s[j]=A[i];
                j++;
            }
            s[j]='\0';
        }
        if(strcmp(s,n)==0)
        {
            count1++;
            printf("Cancellation is confirmed\n");
            break;   
        }
    }
    if(count1==0)
    {
        printf("Cancellation is not confirmed\n");
    }
}

//--------------------------------------FUNCTION TO DELETE DATA FROM HISTORY BASED ON PNR-----------------------------------------------
void deletehist_pnr(FILE *fp,char pnr[])
{
    char s[100],A[50][100],c[10];
    int i=0,l,count=0,Q[100],q=0;
    fp=fopen("cancel.txt","r");
    while(fscanf(fp,"%s",s)>0)
    {
    	l=strlen(s);
        for(i=0;i<l;i++)
        {
        	if(s[i]==',')
        	{
        		break;
        	}
        	else
        	{
            		c[i]=s[i];
            	}
        }
        c[i]='\0';
        if(strcmp(pnr,c)==0)
        {
            count++;           
        }
        else
        {
        strcpy(A[q],s);
        q++;
        }
    }
    fclose(fp);
    if(count==0)
    {
        printf("THERE IS NO HISTORY WITH THAT PNR\n");
    }
    else
    {
        FILE *fp1=fopen("cancel.txt","w");
        for(i=0;i<q;i++)
        {
            fprintf(fp1,"%s",A[i]);
            fprintf(fp1,"\n");
        }
        fclose(fp1);   
        printf("THE TICKET HAVING PNR %s IS DELETED IN HISTORY\n",pnr);
   
    }
       
}
//---------------------------FUNCTION TO UPDATE THE RESERVATION FILE AFTER CANCELLING THE TICKETS----------------

void updatethefile(CANCEL *cancel,FILE *fp,int n)
{
    fp=fopen("reservation.txt","w");
    while(cancel!=NULL)
    {
        if(cancel->pnr_no!=n)
        {
            fprintf(fp,"%d",cancel->pnr_no);
            fprintf(fp,",");
            fprintf(fp,"%s",cancel->name);
            fprintf(fp,",");
            fprintf(fp,"%d",cancel->age);
            fprintf(fp,",");
            fprintf(fp,"%s",cancel->gender);
            fprintf(fp,",");
            fprintf(fp,"%d",cancel->train_no);
            fprintf(fp,",");
            fprintf(fp,"%s",cancel->category);
            fprintf(fp,",");
            fprintf(fp,"%s",cancel->class);
            fprintf(fp,",");
            fprintf(fp,"%d",cancel->ticket_price);
            fprintf(fp,",");   
            fprintf(fp,"%s",cancel->src);       
            fprintf(fp,",");
            fprintf(fp,"%s",cancel->des);
            fprintf(fp,",");
            fprintf(fp,"%s",cancel->time);
            fprintf(fp,",");
            fprintf(fp,"%d",cancel->isCancelled);
            fprintf(fp,",");
            fprintf(fp,"%d",cancel->isWaiting);
            fprintf(fp,",");
            fprintf(fp,"%d",cancel->seat_no);
            fprintf(fp,",");       
            fprintf(fp,"\n");
        }
        cancel=cancel->next;   
    }
    fclose(fp);
}

//--------------------------------------------------------------------------------------

CANCEL *insertdata2(CANCEL *cancel)
{
   
    CANCEL *insertNode=(CANCEL *)malloc(sizeof(CANCEL));
    insertNode->train_no=cancel->train_no;
    strcpy(insertNode->name,cancel->name);
    insertNode->age=cancel->age;
    strcpy(insertNode->gender,cancel->gender);
    insertNode->pnr_no=cancel->pnr_no;
    strcpy(insertNode->category,cancel->category);
    strcpy(insertNode->class,cancel->class);
    insertNode->ticket_price=cancel->ticket_price;
    strcpy(insertNode->src,cancel->src);
    strcpy(insertNode->des,cancel->des);
    strcpy(insertNode->time,cancel->time);
    insertNode->isCancelled=cancel->isCancelled;
    insertNode->isWaiting=cancel->isWaiting;
    insertNode->seat_no=cancel->seat_no;
   
    if(headc2==NULL)
    {
    headc2=insertNode;
    headc2->next=NULL;
    }
    else
    {
       
        insertNode->next=headc2;
        headc2=insertNode;
   
    }
   
    return headc2;
   
}

//------------------------------FUNCTION TO LOAD DATA FROM RESERVATION FILE TO UPDATE THE FILE------------------------------

CANCEL *deleteinfile(FILE *fp)
{    int i=0,j=0,k=0,m;
    char c,A[100];
    fp=fopen("reservation.txt","r");
    CANCEL *cancel=(CANCEL *)malloc(sizeof(CANCEL));
    cancel->next=NULL;
    while(fscanf(fp,"%c",&c)>0)
    {
        if(k<14)
        {
            if(c!=',')
            {
                A[j++]=c;
            }
            else
            {
               
                switch(k){
                case 0:
                    A[j]='\0';
                    cancel->pnr_no=atoi(A);
                    j=0;
                    k++;
                    break;
               
                case 1:
           
                    A[j]='\0';
                    strcpy(cancel->name,A);
                    j=0;
                    k++;
                    break;
                case 2:
                    A[j]='\0';
                    cancel->age=atoi(A);
                    j=0;
                    k++;
                    break;
                case 3:
           
                    A[j]='\0';
                    strcpy(cancel->gender,A);
                    j=0;
                    k++;
                    break;   
                case 4:
           
                    A[j]='\0';
                    cancel->train_no=atoi(A);
                    j=0;
                    k++;
                    break;
                case 5:
           
                    A[j]='\0';
                    strcpy(cancel->category,A);
                    j=0;
                    k++;
                    break;

               
                case 6:
                   
                    A[j]='\0';
                    strcpy(cancel->class,A);
                    j=0;
                    k++;
                    break;
   
               
                case 7:
                   
                    A[j]='\0';   
                    cancel->ticket_price=atoi(A);   
                    j=0;
                    k++;
                    break;

               
                case 8:
                   
                    A[j]='\0';
                    strcpy(cancel->src,A);   
                    j=0;
                    k++;
                    break;

               
                case 9:
                   
                    A[j]='\0';
                    strcpy(cancel->des,A);   
                    j=0;
                    k++;
                    break;


               
                case 10:
                   
                    A[j]='\0';
                    strcpy(cancel->time,A);   
                    j=0;
                    k++;
                    break;
   
               
                case 11:
                   
                    A[j]='\0';
                    cancel->isCancelled=atoi(A);   
                    j=0;
                    k++;
                    break;
       
               
                case 12:
                   
                    A[j]='\0';
                    //    printf("%s\n",A);
                    cancel->isWaiting=atoi(A);   
                    j=0;
                    k++;
                    break;   
                   
                case 13:
                   
                    A[j]='\0';
                      //  printf("%s\n",A);
                    cancel->seat_no=atoi(A);
                //    printf("%d\n",cancel->seat_no);
                    j=0;
                    k++;
                    break;
            }
            }   
        }
       
        else
        {
            k=0;
           
            headc2=insertdata2(cancel);
       
            CANCEL* cancel=(CANCEL *)malloc(sizeof(CANCEL));
        }
    }
    fclose(fp);
    return headc2;
   


}
//Inserting each line from file in Binary Search Tree using ticket number as key
BSTREE *genreservationDataset (BSTREE *bstree, FILE *fp){              
    int t;
    BSTREE *a,*b;
        BSTREE *temp;
    char c,s[30];
    fp=fopen("reservation.txt","r");
    int j=0,k=0,i=0;
    temp=(BSTREE *)malloc(sizeof(BSTREE));
        while(fscanf(fp,"%c",&c)>0){
                if(k<14)
          {
           if(c!=',')
             {
            s[j++]=c;
             }
           else
                    {
                                switch(k){
                    case 0:
                                                s[j]='\0';
                        temp->train_no=atoi(s);
                       
                        j=0;
                        k++;
                        break;

                    case 1:
                                                s[j]='\0';
                        strcpy(temp->pname,s);
                        j=0;
                        k++;
                        break;
                    case 2:
                        s[j]='\0';
                        temp->age=atoi(s);
                        j=0;
                        k++;
                        break;
                                        case 3:
                                                s[j]='\0';
                        strcpy(temp->gender,s);
                        j=0;
                        k++;
                        break;
                                        case 4:
                        s[j]='\0';
                        temp->pnr_no=atoi(s);
                        t=temp->pnr_no;
                        j=0;
                        k++;
                        break;
                                        case 5:
                        s[j]='\0';
                        strcpy(temp->cgt,s);
                        j=0;
                        k++;
                        break;
                                        case 6:
                        s[j]='\0';
                        strcpy(temp->class,s);
                        j=0;
                        k++;
                        break;
                    case 7:
                        s[j]='\0';
                        temp->tprice=atoi(s);
                        j=0;
                        k++;
                        break;   
                                        case 8:
                                                s[j]='\0';
                        strcpy(temp->sname,s);
                        j=0;
                        k++;
                        break;
                                        case 9:
                                                s[j]='\0';
                        strcpy(temp->dname,s);
                        j=0;
                        k++;
                        break;
                                        case 10:
                                                s[j]='\0';
                        strcpy(temp->time,s);
                        j=0;
                        k++;
                        break;
                                        case 11:
                        s[j]='\0';
                        temp->cancel=atoi(s);
                        j=0;
                        k++;
                        break;
                                        case 12:
                        s[j]='\0';
                        temp->wlIst=atoi(s);
                                                j=0;
                        k++;
                        break;
                    case 13:
                                                s[j]='\0';
                        temp->seatno=atoi(s);
                        temp->left=NULL;
                        temp->right=NULL;
                        j=0;
                        k++;
                        break;   
               }
            }       
                }
        else
        {
                    k=0;       
                        if(bstree!=NULL)
              {
                     a=bstree;
                while(a!=NULL){
                        if(t<=a->pnr_no)
                    {
                        b=a;
                        a=a->left;
                                        }
                    else if(t>a->pnr_no)
                    {
                        b=a;
                        a=a->right;
                                        }
                                }
                                if(t>b->pnr_no)
                {
                    b->right=temp;
                }               
                else
                {
                    b->left=temp;
                }               
            }
                        if(bstree==NULL)
            {
                bstree=temp;

            }
            temp=(BSTREE *)malloc(sizeof(BSTREE));
        }
    }
    return bstree;
}
int P=0,Q=0,R=0,S=0,T=0;
void searchbytnum(BSTREE *bstree,int p){         //search by train number
        if(bstree!=NULL)
      {
            if(bstree->train_no==p)
         {
                        if(bstree->wlIst==0)
            {     
                printf("**********************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSeatNo.:%d\nSource:%s\nDestination: %s\nTime:%s\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->seatno,bstree->sname,bstree->dname,bstree->time);
            }
            else
            {
                printf("************************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSource:%s\nDestination: %s\nTime:%s\nWaitinglist:%d\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->sname,bstree->dname,bstree->time,bstree->wlIst);
                        }
            P++;
        }
        searchbytnum(bstree->left,p);
        searchbytnum(bstree->right,p);
    }
}
void searchbypnr(BSTREE *bstree,int p){                //search by pnr number
        if(bstree!=NULL)
     {
            if(bstree->pnr_no==p)
         {
                        if(bstree->wlIst==0)
            {     
                printf("**********************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSeatNo.:%d\nSource:%s\nDestination: %s\nTime:%s\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->seatno,bstree->sname,bstree->dname,bstree->time);
            }
            else
            {
                printf("************************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSource:%s\nDestination: %s\nTime:%s\nWaitinglist:%d\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->sname,bstree->dname,bstree->time,bstree->wlIst);
                        }
                        Q++;
        }
        searchbypnr(bstree->left,p);
        searchbypnr(bstree->right,p);
    }
}
void searchbyname(BSTREE *bstree,char *n){              //search by passenger name
        if(bstree!=NULL)
     {
            if(strcmp(bstree->pname,n)==0)
         {
                        if(bstree->wlIst==0)
            {     
                printf("**********************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSeatNo.:%d\nSource:%s\nDestination: %s\nTime:%s\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->seatno,bstree->sname,bstree->dname,bstree->time);
            }
            else
            {
                printf("************************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSource:%s\nDestination: %s\nTime:%s\nWaitinglist:%d\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->sname,bstree->dname,bstree->time,bstree->wlIst);
                        }
                        R++;
                }
        searchbyname(bstree->left,n);
        searchbyname(bstree->right,n);
    }
}
void searchbysourcename(BSTREE *bstree,char *n){                //search by source name
        if(bstree!=NULL)
      {
             if(strcmp(bstree->sname,n)==0)
         {
                if(bstree->wlIst==0)
            {     
                printf("**********************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSeatNo.:%d\nSource:%s\nDestination: %s\nTime:%s\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->seatno,bstree->sname,bstree->dname,bstree->time);
            }
            else
            {
                printf("************************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSource:%s\nDestination: %s\nTime:%s\nWaitinglist:%d\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->sname,bstree->dname,bstree->time,bstree->wlIst);
                        }
            S++;
                }
        searchbysourcename(bstree->left,n);
        searchbysourcename(bstree->right,n);
    }
}
void searchbydestname(BSTREE *bstree,char *n){                  //search by destination name
        if(bstree!=NULL)
      {
             if(strcmp(bstree->dname,n)==0)
         {
            if(bstree->wlIst==0)
            {     
                printf("**********************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSeatNo.:%d\nSource:%s\nDestination: %s\nTime:%s\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->seatno,bstree->sname,bstree->dname,bstree->time);
            }
            else
            {
                printf("************************************************************************\n");
                printf("Trainnumber:%d\nPassenger Name:%s\nAge:%d\nGender:%s\nPNR numumber:%d\nCatgeory:%s\nClass:%s\nTicketprice:%d\nSource:%s\nDestination: %s\nTime:%s\nWaitinglist:%d\n",bstree->train_no,bstree->pname,bstree->age,bstree->gender,bstree->pnr_no,bstree->cgt,bstree->class,bstree->tprice,bstree->sname,bstree->dname,bstree->time,bstree->wlIst);
                        }

            T++;
                }
        searchbydestname(bstree->left,n);
        searchbydestname(bstree->right,n);
    }
}
//--------------------------------------------------------------------------------------
MODIFY *insertingData(MODIFY *modify)
{

    MODIFY *insertNode=(MODIFY *)malloc(sizeof(MODIFY));
    insertNode->train_no=modify->train_no;
    strcpy(insertNode->name,modify->name);
    insertNode->age=modify->age;
    strcpy(insertNode->gender,modify->gender);
    insertNode->pnr_no=modify->pnr_no;
    strcpy(insertNode->category,modify->category);

    strcpy(insertNode->class,modify->class);

    insertNode->ticket_price=modify->ticket_price;
    strcpy(insertNode->src,modify->src);
    strcpy(insertNode->des,modify->des);
    strcpy(insertNode->time,modify->time);
    insertNode->ismodifyled=modify->ismodifyled;
    insertNode->isWaiting=modify->isWaiting;
    insertNode->seat_no=modify->seat_no;

    if(headp==NULL)
    {
        headp=insertNode;
        headp->next=NULL;
    }
    else
    {

        insertNode->next=headp;
        headp=insertNode;

    }

    return headp;

}
//---------------------FUNCTION TO INSERT DATA FROM RESERVATION FILE---------------------------------------------------
MODIFY *modifylation(FILE *fp)
{    int i=0,j=0,k=0,m;
    char c,A[100],name[100];
    fp=fopen("reservation.txt","r");
    MODIFY *modify=(MODIFY *)malloc(sizeof(MODIFY));
    modify->next=NULL;
    while(fscanf(fp,"%c",&c)>0)
    {


        if(k<14)
        {
            if(c!=',')
            {
                A[j++]=c;
            }
            else
            {

                switch(k){
                    case 0:
                        A[j]='\0';
                        modify->train_no=atoi(A);
                        j=0;
                        k++;
                        break;

                    case 1:

                        A[j]='\0';
                        strcpy(modify->name,A);
                        j=0;
                        k++;
                        break;
                    case 2:
                        A[j]='\0';
                        modify->age=atoi(A);
                        j=0;
                        k++;
                        break;
                    case 3:

                        A[j]='\0';
                        strcpy(modify->gender,A);
                        j=0;
                        k++;
                        break;   
                    case 4:

                        A[j]='\0';
                        modify->pnr_no=atoi(A);
                        j=0;
                        k++;
                        break;
                    case 5:

                        A[j]='\0';
                        strcpy(modify->category,A);

                        j=0;
                        k++;
                        break;


                    case 6:

                        A[j]='\0';

                        strcpy(modify->class,A);

                        j=0;
                        k++;
                        break;


                    case 7:

                        A[j]='\0';

                        modify->ticket_price=atoi(A);   
                        j=0;
                        k++;
                        break;


                    case 8:

                        A[j]='\0';
                        strcpy(modify->src,A);   
                        j=0;
                        k++;
                        break;


                    case 9:

                        A[j]='\0';
                        strcpy(modify->des,A);   
                        j=0;
                        k++;
                        break;



                    case 10:

                        A[j]='\0';
                        strcpy(modify->time,A);   
                        j=0;
                        k++;
                        break;


                    case 11:

                        A[j]='\0';
                        modify->ismodifyled=atoi(A);   
                        j=0;
                        k++;
                        break;


                    case 12:

                        A[j]='\0';
                        modify->isWaiting=atoi(A);   
                        j=0;
                        k++;
                        break;   
                    case 13:

                        A[j]='\0';
                        modify->seat_no=atoi(A);   
                        j=0;
                        k++;
                        break;
                }

            }
        }
        else
        {
            k=0;COUNT++;

            headp=insertingData(modify);
            MODIFY* modify=(MODIFY *)malloc(sizeof(MODIFY));
        }


    }
    fclose(fp);
    return headp;



}
//------------------------------FUNCTION TO PRINT BOOKINGS-------------------------------------
void view_modifylation(MODIFY *modify)
{
    MODIFY *p=modify;
    //printf("%d =======",COUNT);
    while(p!=NULL)
    {

        printf("%d  %s  %d  %s  %d  %s  %s  %d  %s  %s  %s  %d  %d %d\n",p->train_no,p->name,p->age,p->gender,p->pnr_no,p->category,p->class,p->ticket_price,p->src,p->des,p->time,p->ismodifyled,p->isWaiting,p->seat_no);
        p=p->next;
    }

}
//--------------------------FUNCTION TO MODIFY PASSENGERS NAME----------------------------------
void view_upadates(MODIFY *modify,int n1,char *n2)
{
    MODIFY *p=modify;
    int k=0;
    while(p!=NULL)
    {    k++;
        if(p->pnr_no==n1)
        {   

            strcpy(p->name,n2);
            break;
        }
        p=p->next;
    }



    int MAX=256;

    FILE *fptr1, *fptr2;
    int lno, linectr = 0;
    char str[MAX],fname[MAX];       
    char newln[MAX], temp[] = "temp.txt";

    printf("\n\n Replace a specific line in a text file with a new text :\n");
    printf("-------------------------------------------------------------\n");
    //fname=fopen("reservation.txt","r");
    fptr1 = fopen("reservation.txt", "r");
    if (!fptr1)
    {
        printf("Unable to open the input file!!\n");
        // return 0;
    }
    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr1);
        //return 0;
    }
    lno=(COUNT+1)-k;
    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1))
        {
            linectr++;
            if (linectr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
            else
            {
                fprintf(fptr2, "%d,%s,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,\n",p->train_no,p->name,p->age,p->gender,p->pnr_no,p->category,p->class,p->ticket_price,p->src,p->des,p->time,p->ismodifyled,p->isWaiting,p->seat_no);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove("reservation.txt");
    rename(temp, "reservation.txt");


}
//-------------------FUNCTION TO VIEW DETAILS OF THE TICKET------------------------------------------------
void view_booking(MODIFY *modify,int t)
{
    MODIFY *p=modify;

    while(p!=NULL)
    {
        if(p->pnr_no==t)
        {
            printf("%d  %s  %d  %s  %d  %s  %s  %d  %s  %s  %s  %d  %d  %d\n",p->train_no,p->name,p->age,p->gender,p->pnr_no,p->category,p->class,p->ticket_price,p->src,p->des,p->time,p->ismodifyled,p->isWaiting,p->seat_no);

        }
        p=p->next;
    }

}
//----------------------------FUNCTION TO MODIFY SOURCE AND DESTINATION---------------------------------------
void travelling_Way(MODIFY *modify,int N,char *SS,char *D,DATA *data)
{   
       
        MODIFY *p=modify;
        int k=0,m,l=0,w=0;
       
       
        while(data!=NULL)
        {
            if( (strcmp(data->src,SS)==0) && (strcmp(data->des,D)==0))
            {   
                w=data->train_no;
                break;
            }
                data=data->next;
        }
       
       
        while(p!=NULL)
        {    k++;
           
           
            if(l<p->seat_no)
            {
                l=p->seat_no;
                //printf("*********");
            }
           
            if(p->pnr_no==N)
            {
                //printf("$$$$\n");   
                p->train_no=w;
                strcpy(p->src,SS);
                strcpy(p->des,D);
                m=(10*p->ticket_price)/100;p->seat_no=l+3;
                p->ticket_price=(p->ticket_price)+m;
                break;
            }
           
               
                p=p->next;
        }
           
       
       
        int MAX=256;
   
        FILE *fptr1, *fptr2;
        int lno, linectr = 0;
        char str[MAX],fname[MAX];       
        char newln[MAX], temp[] = "temp.txt";
       
        //printf("\n\n Replacing a specific line in a text file with a new text :\n");
        printf("-------------------------------------------------------------\n");
        //fname=fopen("reservation.txt","r");
        fptr1 = fopen("reservation.txt", "r");
        if (!fptr1)
        {
                printf("Unable to open the input file!!\n");
               // return 0;
        }
        fptr2 = fopen(temp, "w");
        if (!fptr2)
        {
                printf("Unable to open a temporary file to write!!\n");
                fclose(fptr1);
                //return 0;
        }
         lno=(COUNT+1)-k;
       while (!feof(fptr1))
        {
            strcpy(str, "\0");
            fgets(str, MAX, fptr1);
            if (!feof(fptr1))
            {
                linectr++;
                if (linectr != lno)
                    {
                        fprintf(fptr2, "%s", str);
                       // fprintf(fptr2,",");
                    }
                    else
                    {
                        fprintf(fptr2, "%d,%s,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,\n",p->train_no,p->name,p->age,p->gender,p->pnr_no,p->category,p->class,p->ticket_price,p->src,p->des,p->time,p->ismodifyled,p->isWaiting,p->seat_no);
                    }
            }
        }
       
        fclose(fptr1);
        fclose(fptr2);
        remove("reservation.txt");
        rename(temp, "reservation.txt");
     
}
void print(RESERVE *reserve)
{
        while(reserve!=NULL)
        {
                printf("*********%d\n",reserve->pnr_no);
                reserve=reserve->next;
        }

}
//MAIN FUNCTION STARTS HERE----------------------------------------

int main()
{
    int i,j,opcode,n1,s;
    MODIFY *modify=NULL;
    char n11[100],n2[100],X[100],SS[100],DD[100],N[100],n3[6],ss[100],dd[100],name[100];
    int a,nn,number;
    char n[100];
    CANCEL *cancel=NULL,*cancel1=NULL;
    int x,y;
    char p[30],q[30],d[30],c,ch;
    BSTREE *bstree=NULL;
    DATA *data;
    RESERVE *reserve;
    FILE *fp,*fp1,*fp2,*fp3,*fp5,*fp6;
    fp=fopen("input_data.txt","r+");
    fp1=fopen("reservation.txt","a+");
    printf("PRESS 1 TO RESERVE AND VIEW THE BOOKINGS\n");
    printf("PRESS 2 TO SEARCH THE BOOKINGS\n");
    printf("PRESS 3 TO MODIFY THE BOOKINGS\n");
    printf("PRESS 4 TO CANCEL THE TICKET\n");
    scanf("%d",&opcode);
    switch(opcode){
        case 1:
            data=load_data(fp);
            view_data(data);
            reserve=load_bookings(data);
            view_reserved(reserve,fp1);
            printf("------------------------------------------------------------\n");
            printf("THE BOOKINGS\n");
            printf("\n");
            view_bookings(fp1);
            int tkt_no;
            printf("Enter the pnr number to confirm\n");
            scanf("%d",&tkt_no);
            fp1=fopen("reservation.txt","r");
            confirm_booking(fp1,tkt_no);
            fclose(fp1);
            //free(data);
            free(reserve);
            break;

        case 2:       
            fp3 =fopen("reservation.txt", "r");
            bstree=genreservationDataset (bstree,fp3);
                        printf("Press 1 to search by PNR number\n");
            printf("Press 2 to search by Train number\n");
            printf("Press 3 to search by Passenger name\n");
            printf("Press 4 to search by Source name\n");
            printf("Press 5 to search by Destination name\n");
            scanf("%d",&s);
            if(s==1)
            {
                printf("Input Your PNRnumber:\n");
                                scanf("%d",&x);
                searchbypnr(bstree,x);
                printf("************************************************************************\n");
                if(Q==0)
                {
                    printf("Sorry!There Is No Train With PNRnumber-");
                    printf("%d\n",x);
                }
            }
            if(s==2)
            {
                int y;
                printf("Input Your Trainnumber:\n");
                scanf("%d",&y);
                searchbytnum(bstree,y);
                printf("************************************************************************\n");
                if(P==0)
                {

                    printf("Sorry!There Is No such Ticket No.\n");
                }

            }
            if(s==3)
            {
                char p[100];
                printf("Input Passenger Name:\n");
                scanf("%s",p);
                searchbyname(bstree,p);
                printf("************************************************************************\n");
                if(R==0)
                {
                    printf("Sorry!There Is No Passenger With Name-");
                    printf("%s\n",p);
                }
            }
            if(s==4)
            {
                char q[100];
                printf("Input Source Name:\n");
                scanf("%s",q);
                searchbysourcename(bstree,q);
                printf("************************************************************************\n");
                if(S==0)
                {
                    printf("Sorry!There Is No Train From Source-");
                    printf("%s\n",q);
                }
            }
            if(s==5)
            {
                char d[100];
                printf("Input Destination Name:\n");
                scanf("%s",d);
                searchbydestname(bstree,d);
                if(T==0){
                    printf("Sorry!There Is No Train To Destination-");
                    printf("%s\n",d);
                }
            }
            fclose(fp3);
            free(bstree);
            break;
                  case 3:
                       // fp2=fopen("reservation.txt","r+");
            fp=fopen("input_data.txt","r+");
            fp2=fopen("reservation.txt","r+");
    modify=modifylation(fp2);
    view_modifylation(modify);
    printf("\n");
    printf("enter 1 if you want to change name or 2 if you want to change source and destination\n");
    scanf("%d",&number);
    if(number==1)
    {
    printf("Enter the pnr number that you have to modify in the above list\n");
    int h;
    scanf("%d",&h);
    printf("Write modified name\n");
    scanf("%s",n2);
    printf("Now your name in the list get modified\n");
    view_upadates(modify,h,n2);
    printf("\n");
    view_modifylation(modify);
    printf("\n");
    }
    if(number==2)
    {
        data=load_data(fp);
       
        printf("Enter pnr number \n");
       
        int j;
        scanf("%d",&j);
        printf("Enter new Source and  Destination\n");
       
        scanf("%s",SS);
        scanf("%s",DD);
        printf("\n");
        printf("*************************************************\n");
        printf("Your ticket price will get changed\n");
        printf("*************************************************\n");
        travelling_Way(modify,j,SS,DD,data);
       
        printf("\n");
        view_modifylation(modify);
    }
    printf("\n");
   
    int t;
    printf("\n");
    printf("Enter pnr number to view details");
    scanf("%d",&t);
    view_booking(modify,t);
   
            break;
                case 4:
                        fp2=fopen("reservation.txt","r");
            cancel=load_reserved(fp2);
            fclose(fp2);
            view_reservedtickets(cancel);
            printf("-----------------------------------------\n");
            printf("THE HISTORY OF CANCELLED TICKETS\n");
            fp=fopen("cancel.txt","r");
            view_deletehistory(fp);
            fclose(fp);
            printf("-----------------------------------------\n");
            printf("INPUT THE PNR TO DELETE HISTORY OF THAT PNR\n");
            scanf("%s",n2);
            fp6=fopen("cancel.txt","r");
            deletehist_pnr(fp6,n2);
            fclose(fp6);
            printf("-----------------------------------------\n");       
                    printf("Give the ticket number which you want to cancel\n");
                scanf("%d",&n1);
            deletenode(cancel,n1);
                    printf("-----------------------------------------\n");
                printf("Give a ticket number to check whether a ticket is cancelled or not\n");
                scanf("%s",n);
                fp3=fopen("cancel.txt","r");
                confirmcancellation(fp3,n);
                fclose(fp3);
                printf("-----------------------------------------\n");
            fp1=fopen("reservation.txt","r");
            cancel1=deleteinfile(fp1);
            fclose(fp1);
            fp5=fopen("reservation.txt","w");
            updatethefile(cancel1,fp5,n1);
            fclose(fp5);
            free(cancel);
            break;
        }
    return 0;
}
