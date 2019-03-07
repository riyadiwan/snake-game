#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
using namespace std;
char board[40][50];
int r,c;
static int l=1,p,p1,p2=1;
struct food
{
    int x,y;
    char val;
};
struct snake
{
    int x,y;
    char val;
    snake*next;
};
struct poison
{
    int x,y;
    char val;
};
snake*head=NULL;
class linked
{
  public:
      snake*create(int a,int b,char c)
      {
          snake*temp;
          temp = new snake;
          temp->x=a;
          temp->y=b;
          temp->val=c;
          temp->next=NULL;
          return temp;
      }
      void insert(int e,int f,char c)
      {
          snake*t,*temp;
          int a,b;
          char d;
          cout<<"enter node";
          a=e;
          b=f;
          d=c;
          system("cls");
          temp = create(a,b,d);
          if(head==NULL)
          {
              head = temp;
          }
          else
          {
              t=head;
              while(t->next!=NULL)
              {
                  t=t->next;
              }
              t->next=temp;
              temp->next=NULL;
          }
      }
      void print()
      {
          system("cls");
          int i,j;
              for(i=0;i<40;i++)
            {     for(j=0;j<50;j++)
                   cout<<board[i][j];
        cout<<endl;
            }
      }
      void matrix()
      {
          int i,j;
          snake*t;
          t=head;
          while(t!=NULL)
          {
            i=t->x;
            j=t->y;
            board[i][j]=t->val;
            t=t->next;
          }
      }
      void selfattack()
      {
        snake * t;
        t=head;
        int i,j;
        i=t->x;
        j=t->y;
        t=t->next;
        while(t!=NULL)
        {
            if(t->x==i && t->y==j)
                exit(0);
            t=t->next;
        }
      }
      void move(int r, int c)
      {

          snake*t;
          int s,u;
          t=head;
          if(r==t->next->x && c==t->next->y)
            exit(0);
          s=t->x;
          u=t->y;
          t->x=r;
          t->y=c;
          board[r][c]=t->val;
          selfattack();
          match();
          match1();
          t=t->next;
          r=s;
          c=u;
          while(t!=NULL)
          {
              s=t->x;
              u=t->y;
              t->x=r;
              t->y=c;
             board[r][c]=t->val;
              r=s;
              c=u;
              t=t->next;
          }
          board[s][c]=' ';
          print();

      }
      void insert1()
      {
         /*snake*temp,*t;
          t=head;
          temp=create(l,p,'H');
          temp->next=t;
          t->val='#';
          head=temp;*/
         snake * temp,*t,*np;
          t=head;
          int i,j;
          while(t->next!=NULL)
          {
            np=t;
            t=t->next;
          }
      if(np->x==t->x)
      {
          if(np->y<t->y)
            temp=create(t->x,t->y+1,'#');
          else
              temp=create(t->x,t->y-1,'#');
      }
      else
      {
          if(np->x<t->x)
              temp=create(t->x+1,t->y,'#');
          else
              temp=create(t->x-1,t->y,'#');
      }
      t->val='#';
       t->next=temp;
        temp->val='T';
      }
      void insert2()
      {
          snake*t;
        board[p1][p2]=' ';
        t=head;
        head = t->next;
        head->val='H';
        delete t;
        int c=0;
        t=head;
        while(t!=NULL)
        {
            c++;
            t=t->next;
        }
        if(c==2)
            exit(0);

      }
      void match()
      {
          snake * t;
          t=head;
          if(t->x==l && t->y==p)
          {
             insert1();
            createfood();
          }
      }
      void match1()
      {
          snake * t;
          t=head;
          if(t->x==p1 && t->y==p2)
          {
             insert2();
             createpois();
          }
      }
      void movement()
      {
          char z;
          int i=1;
          snake* t;
          while(i==1)
         {
           z = getch();
           system("cls");
           t=head;
           r = t->x;
           c = t->y;
           if(z=='l'||z=='a')
           {
               if(c-1>=1)
                   move(r,c-1);
               else
                move(r,48);

           }
           else if(z=='r'||z=='d')
           {
               if(c+1<=48)
                move(r,c+1);
               else
                move(r,1);

           }
           else if(z=='t'||z=='w')
              { if(r-1>=1)
                move(r-1,c);
               else
                move(38,c);

              }
              else if(z=='b'||z=='s')
              {
                  if(r+1<=38)
                    move(r+1,c);
                  else
                    move(1,c);
              }
              else if(z=='q')
              {
                  system("cls");
                  char ch;
                  cout<<"DO u want to save press Y else N"<<endl;
                  ch=getch();
                  if(ch=='y'||ch=='Y')
                  {
                     filestoring();
                  }
                  else
                  {
                   system("cls");
                   exit(0);
                  }

              }
         }

      }
      void filestoring()
      {
          ofstream fout("abc.txt");
          snake *t;
          t=head;
          while(t!=NULL)
          {
              fout<<t->x;
              fout<<',';
              fout<<t->y;
              fout<<',';
              fout<<t->val;
              fout<<'!';
              t=t->next;
          }
          fout<<'*'<<'\n';
          fout<<l;
          fout<<',';
          fout<<p;
          fout<<','<<'@';
          fout<<'\n';
          fout<<p1<<','<<p2<<','<<'$';
       // exit(0);
      }
      void createfood()
      {
         l = 2*l;
         if(l>37)
         {
          if(p<36)
          l=p;
          else
            l=1;
         }
         p++;
         if(p>47)
            p=1;
         check(l,p);
      }
      void check(int l,int p)
      {
          snake*t;
          t=head;
          int f=0;
          while(t!=NULL)
          {
             if(t->x==l && t->y==p)
                { createfood();
                  f=1;
                }
             t=t->next;
          }
          if(l==p1&&p==p2)
          {
              createfood();
              f=1;
          }
          if(f==0)
            board[l][p]='@';
      }
        void check1(int p1,int p2)
      {

          snake*t;
          t=head;
          int f=0;
          while(t!=NULL)
          {
             if(t->x==p1 && t->y==p2)
                { createpois();
                  f=1;
                }
             t=t->next;
          }
           if(l==p1&&p==p2)
          {
              createfood();
              f=1;
          }
          if(f==0)
            board[p1][p2]='$';
      }
      void createpois()
      {
       p1++;
       if(p1>37)
        p1=p2;
        p2= 2*p2;
       if(p2>47)
            p2=1;
            check1(p1,p2);
     }
     //**************************************
     void resumegame(string str,int j)
     {
         int i=0;
         int a,b;
         if(j==0)
         {
             while(str[i]!='*')
             {
                 a=0;
                 b=0;
                 while(str[i]!=',')
                 {
                  a=a*10+(str[i]-'0');
                  i++;
                 }
                 i++;
                 while(str[i]!=',')
                 {
                     b=b*10+(str[i]-'0');
                     i++;
                 }
                 i++;
                 insert(a,b,str[i]);
                  i=i+2;
             }

         }
         if(j==1)
         {
             l=0,p=0;
           while(str[i]!=',')
           {
               l=l*10+(str[i]-'0');
               i++;
           }
           i++;
           while(str[i]!=',')
           {
               p=p*10+(str[i]-'0');
               i++;
           }
           i++;
           cout<<l<<p<<endl;
           board[l][p]=str[i];
         }
         if(j==2)
         {
             p1=0,p2=0;
           while(str[i]!=',')
           {
               p1=p1*10+(str[i]-'0');
               i++;
           }
           i++;
           while(str[i]!=',')
           {
               p2=p2*10+(str[i]-'0');
               i++;
           }
           i++;
           board[p1][p2]=str[i];
         }
     }
};
int main()
{
    linked l;
    system("COLOR 8B");
      int i,j;
    for(i=0;i<40;i++)
      board[i][0]='|';
    for(i=0;i<50;i++)
        board[0][i]='---';
        for(i=0;i<50;i++)
            board[38][i]='---';
            for(i=0;i<40;i++)
             board[i][49]='|';
//***************************************************************
char ch;
cout<<"do u want to play the saved game"<<endl;
ch = getch();
if(ch=='y'||ch=='Y')
{
    int i=0,j=0;
    string str;
  ifstream fin;
  fin.open("abc.txt");
  while(!fin.eof())
  {
     getline(fin,str);
     l.resumegame(str,j);
     j++;
  }
  l.matrix();
  l.print();
  l.movement();
}

//***************************************************************
else
{
system("COLOR 5F");
int a,b,n;
char n1;
system("cls");
 cout<<"Enter the length of snake"<<endl;
 cin>>n;
 system("cls");
while(n)
{
   cin>>a>>b;
   cin>>n1;
   if(n1=='h')
    n1='H';
   if(n1=='t')
    n1='T';
 l.insert(a,b,n1);
 n--;
}
l.createfood();
l.createpois();
l.matrix();
l.print();
l.movement();
}
    return 0;
}
/* 0 = Black
1 = Blue
2 = Green
3 = Aqua
4 = Red
5 = Purple
6 = Yellow
7 = White
8 = Gray
9 = Light Blue
A = Light Green
B = Light Aqua
C = Light Red
D = Light Purple
E = Light Yellow
F = Bright White*/
