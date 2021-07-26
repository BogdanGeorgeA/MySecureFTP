#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
extern int errno;
int port;


int prim1=733;
int prim2=691;
int e,d;
int n;
int euclid(int a, int b)
{
    int c;
    while (b) 
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}
int gasiree(int phi)
{
    int e=2;
    while(euclid(e,phi)!=1) { ++e; }
    return e;
}

// C function for extended Euclidean Algorithm 
int gcdExtended(int a, int b, int *x, int *y) 
{ 
	// Base Case 
	if (a == 0) 
	{ 
		*x = 0, *y = 1; 
		return b; 
	} 

	int x1, y1; // To store results of recursive call 
	int gcd = gcdExtended(b%a, a, &x1, &y1); 

	// Update x and y using results of recursive 
	// call 
	*x = y1 - (b/a) * x1; 
	*y = x1; 

	return gcd; 
}
int modInverse(int a, int m) 
{ 
	int x, y; 
	int g = gcdExtended(a, m, &x, &y); 
	
		// m is added to handle negative x 
		int res = (x%m + m) % m; 
		return res;
	
} 
int fputere(long long x, int la, long long mod)
{
    int p=x;
    if(la==0) return 1;
    --la;
    while(la)
    {
        x*=p;
        if(mod)
            x%=mod;
        --la;
    }
    return x;
}
void decriptare(char mesaj[],int dimbloc)
{
    int i,x,j,p;
    char mesajdecriptat[100]="",c[2];
    for(i=0;i<strlen(mesaj)-dimbloc*2;i+=dimbloc*3)
    {
        p=fputere(10,3*(dimbloc-1),0);
        x=0;
        for(j=i;j<=i+dimbloc*3-1;++j)
        {
            x*=10;
            x+=mesaj[j]-'0';
        }
        x=fputere(x,d,n);
        while (p)
        {
            strcpy(c,"0");
            c[0]=(char)(x/p);
            strcat(mesajdecriptat,c);
            x%=p;
            p/=1000;
        }
        
    }
    while(mesajdecriptat[strlen(mesajdecriptat)-1]==' ' || mesajdecriptat[strlen(mesajdecriptat)-1]=='\n')
        mesajdecriptat[strlen(mesajdecriptat)-1]='\0';
    strcpy(mesaj,mesajdecriptat);
}
void criptare(char mesaj[],int dimbloc)
{
    int i,j,putere=1000;
    char bloccriptat[100];
    char mesajcriptat[100]="";
    while(strlen(mesaj)%dimbloc!=0)
        strcat(mesaj," ");
    for(i=0;i<strlen(mesaj)-1;i+=dimbloc)
    {
        int x=(int)(mesaj[i]);
        for(j=i+1;j<=i+dimbloc-1;++j)
            x=x*putere+(int)(mesaj[j]);
        x=fputere(x,e,n);
        sprintf(bloccriptat,"%d",x);
        int l=0;
        while((l+strlen(bloccriptat))%3!=0)
            strcat(mesajcriptat,"0"),++l;
        strcat(mesajcriptat,bloccriptat);
        //printf("%s\n",bloccriptat);
    }
    strcpy(mesaj,mesajcriptat);
}
int main(int argc, char *argv[])
{
    int sd;
    struct sockaddr_in server;
    char msg[500];
    char raspuns[500];
    char calecurenta[500]=".";
    char detrimis[500];
    char respunsprelucrat[500];
    char *q;
    n=prim1*prim2;   
    int phi=(prim1-1)*(prim2-1);
    e=gasiree(phi);
    d=modInverse(e,phi);
    if(argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

    port=atoi(argv[2]);

    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons (port);

    if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }
    while(1)
    {
    bzero (msg, 500);
    bzero (raspuns, 500);
    bzero (respunsprelucrat, 500);
    printf ("\033[32;1mMFTR \033[0m");
    printf ("\033[1;34mhome%s\033[0m",calecurenta+1);
    printf ("\033[32;1m >> \033[0m");
    fflush (stdout);
    read (0, msg, 500);
    strcpy(detrimis,msg);
    criptare(detrimis,2);
    if (write (sd, detrimis, 500) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
    if(strcmp(msg,"quit\n")==0)
    {
        printf("Deconectare...\n");
        close (sd);
        break;
    }
    /* citirea raspunsului dat de server 
     (apel blocant pina cind serverul raspunde) */
    
    
    if(strncmp(msg,"ls",2)==0)
    {
      while(strcmp(raspuns,"###")!=0)
    {
      if (read (sd, raspuns, 500) < 0)
      {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
      }
      if(strcmp(raspuns,"###")!=0)
        decriptare(raspuns,2);
      if(raspuns[0]=='*' && raspuns[strlen(raspuns)-1]=='*')
      {
        for(int prin=1; prin<strlen(raspuns)-1;++prin)
         printf ("\033[1;34m%c\033[0m",raspuns[prin]); 
      }
      else
      printf("%s",raspuns);
      printf(" ");
    }
    
      printf("\n");
    }
    if(strncmp(msg,"cd",2)==0)
    {
      char *q;
      if (read (sd, raspuns, 500) < 0)
      {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
      }
      q=strtok(raspuns,"$");
      strcpy(calecurenta,q);
    }
   
    
    
    /* afisam mesajul primit */
    //printf ("%s\n", msg);

    /* inchidem conexiunea, am terminat */
    }
}