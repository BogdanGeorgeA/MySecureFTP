#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#define PORT 2024

extern int errno;
char continutcurent[500]="";

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
    printf("%s\n",mesaj);
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
void cautare(char *calecurenta,char *cale,int client)
{
    struct dirent *dp;
    char full[500];
    char detrimis[500];
    struct stat attr;
    
    DIR *dir;
    if((dir = opendir(cale))==NULL)
    {
        perror("directorul nu a putut fi deschis");
    }
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, "~") != 0)
        {
            
            strcpy(full,calecurenta);
            strcat(full,"/");
            strcat(full,cale);
            strcat(full,"/");
            strcat(full,dp->d_name);
            
             
            if(stat(full, &attr)==-1)
                perror("Stat error...");
            if(S_ISREG(attr.st_mode))
            {
                //strcat(continutcurent, dp->d_name);
                strcpy(detrimis,dp->d_name);
                
            }
            if(S_ISDIR(attr.st_mode))
            {
                //strcat(continutcurent,"*");
                //strcat(continutcurent, dp->d_name);
                //strcat(continutcurent,"*");
                strcpy(detrimis,"*");
                strcat(detrimis,dp->d_name);
                strcat(detrimis,"*");
            }
                
            //strcat(continutcurent, " ");
            criptare(detrimis,2);
            
            if (write (client, detrimis, 500) <= 0)
	        {
	            perror ("[server]Eroare la write() catre client.\n");
	            continue;	
            }	/* continuam sa ascultam */
        }
    }

    closedir(dir);
}

void handler(int sig)
{
    pid_t pid;
    int status;
    while((pid=waitpid(-1,&status,WNOHANG))>0)
    {
        printf("Clientul cu PID-ul %d s-a deconectat!\n",pid);
    }
}

int main()
{
    char cwd[500];
    if (getcwd(cwd, sizeof(cwd)) == NULL)  // retinem directorul curent 
       perror("getcwd() error");
    signal(SIGCHLD, handler);
    struct sockaddr_in server;
    struct sockaddr_in from;
    char msg[500];
    char msgrasp[500]=" ";  
    int sd;
    n=prim1*prim2;   
    int phi=(prim1-1)*(prim2-1);
    e=gasiree(phi);
    d=modInverse(e,phi);
    printf("n=%d     phi=%d      e=%d     d=%d\n",n,phi,e,d);
    if((sd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }

    bzero(&server, sizeof(server));
    bzero(&from, sizeof(from));

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(PORT);

    if(bind(sd,(struct sockaddr *) &server, sizeof(struct sockaddr)) ==-1)
    {
        perror ("[server]Eroare la bind().\n");
        return errno;
    }

    if(listen(sd, 5)==-1)
    {
        perror ("[server]Eroare la listen().\n");
        return errno;
    }

    while(1)
    {
        int pid;
        int client;
        int length=sizeof(from);
        
        printf ("[server]Asteptam la portul %d...\n",PORT);
        fflush (stdout);

        client = accept (sd, (struct sockaddr *) &from, &length);

        if (client < 0)
	    {
	        perror ("[server]Eroare la accept().\n");
	        continue;
	    }
        if((pid=fork())==-1)
        {
            fprintf (stderr, "fork - 1\n");
            exit(1);
        }

        printf ("[server]Asteptam mesajul...\n");

        if(pid==0)
        {
            char calecurenta[500]=".", rezultat[500]="";
            bzero (msg, 500);
            
            fflush (stdout);
            /* citirea mesajului */
            if (read (client, msg, 500) <= 0)
	        {
	            perror ("[server]Eroare la read() de la client.\n");
	            close (client);	/* inchidem conexiunea cu clientul */
	            continue;		/* continuam sa ascultam */
	        }
            decriptare(msg,2);
            printf("%s\n",msg);
            while(strncmp(msg,"quit",4)!=0)
            {
            strcpy(continutcurent,"");
            printf("rulare\n");
            if(strncmp(msg,"ls",2)==0)
            {
                cautare(cwd,calecurenta,client);
                if (write (client, "###", 4) <= 0)
	            {
	                perror ("[server]Eroare la write() catre client.\n");
	                continue;	
                }	/* continuam sa ascultam */
            }
            bzero(rezultat,500);

            if(strncmp(msg,"cd",2)==0)
            {
                char *adresa;
                adresa=strtok(msg," \n");
                adresa=strtok(NULL," \n");
                if(adresa)
                {
                    char *folder;
                    folder=strtok(adresa,"/");
                    while (folder)
                    {
                        if(strcmp(folder,".")==0)
                            strcpy(calecurenta,".");
                        else
                        {
                            if(strcmp(folder,"..")==0)
                            {
                                if(strcmp(calecurenta,".")!=0)
                                {
                                    int j;
                                    for(j=strlen(calecurenta)-1;j>0 && calecurenta[j]=='/';--j);
                                    for(;j>0 && calecurenta[j]!='/';--j);
                                    calecurenta[j]='\0';
                                    printf("*%s*\n",calecurenta);

                                }
                            }
                            else
                            {
                                char caleposibila[500];
                                strcpy(caleposibila,calecurenta);
                                strcat(caleposibila,"/");
                                strcat(caleposibila,folder);

                                struct stat attr;
                                if(stat(caleposibila, &attr)==-1 || !(attr.st_mode & __S_IFDIR))
                                    printf("Stat error... %s nu exista sau nu este director!\n",folder);
                                else
                                {
                                    strcpy(calecurenta,caleposibila);
                                    
                                }
                                
                            }
                            
                        }
                        folder=strtok(NULL,"/");   
                    }
                    
                }
            




            strcat(rezultat,calecurenta);
            strcat(rezultat,"$");
            strcat(rezultat,continutcurent);
            //criptare(rezultat,2);
            //printf("%s\n",rezultat);
            //xdecriptare(rezultat,2);
            /* returnam mesajul clientului */
            printf("%s\n",rezultat);
            if (write (client, rezultat, 500) <= 0)
	        {
	            perror ("[server]Eroare la write() catre client.\n");
	            continue;	
            }	/* continuam sa ascultam */
	        
            
            }











            bzero (msg, 500);
            while(strcmp(msg,"")==0)
            {
            if (read (client, msg, 500) <= 0)
	        {
	            perror ("[server]Eroare la read() de la client.\n");
	            close (client);	/* inchidem conexiunea cu clientul */
	            continue;		/* continuam sa ascultam */
	        }
            }
            decriptare(msg,2);
            }
            printf("Clientul a solicitat deconectarea!\n");
                close(client);
                exit(1);
        }   
    }
}