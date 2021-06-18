#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
  
void createTable(char tableName, char col)
{
    FILE *fp;
    printf("DUAARRR");
    fp = fopen(tableName,"w+");
    char *com= strtok(col," ");

    while(com)
    {
        fprintf(fp,"%s ",com);
        com = strtok(NULL," ");
    }

    fclose(fp);
}

void dropTable(char tableName)
{
    if(remove(tableName) == 0)
    {
        printf("The file is deleted successfully.");
    }
    else
    {
        printf("The file is not deleted.");
    }
}

void insertInto(char tableName, char data)
{
    FILE *fp;
    fp = fopen(tableName,"w");
    char *com= strtok(data," ");

    while(com)
    {
        fprintf(fp,"%s ",com);
        com = strtok(NULL," ");
    }

    fclose(fp);
}

void dropColumn(char data)
{
    int result;
    char *colName = strtok(data," ");
    char *table = strtok(data," ");
    
    //Search until we get the table and column name in which string
    for(int i=0;i<2;i++)
    {
        colName = strtok(NULL," ");
    }
    for(int i=0;i<4;i++)
    {
        table = strtok(NULL," ");
    }

    result = Search_in_File(table, colName);
    if(result == -1)
    {
        printf("GA ADA TABLE");
    }
}

int Search_in_File(char *fname, char *str) 
{
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	
	if((fp = fopen(fname, "r")) == NULL) 
    {
		return(-1);
	}

	while(fgets(temp, 512, fp) != NULL) 
    {
		if((strstr(temp, str)) != NULL) 
        {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) 
    {
		printf("\ncouldn't find a match.\n");
	}
	
	//Close the file if still open.
	if(fp) 
    {
		fclose(fp);
	}

    return(0);
}

//Function designed for chat between client and server
void func(int sockfd)
{
    char buff[MAX];
    int n;
    //Infinite loop for chat
    for (;;) 
    {
        bzero(buff, MAX);
  
        //Read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));

        //Print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;

        //Copy server message in the buffer
        while((buff[n++] = getchar()) != '\n')
            ;
  
        //And send that buffer to client
        write(sockfd, buff, sizeof(buff));
  
        //If message contains "Exit" then server exit and chat ended
        char buf1[50], buf2[50], tableName[50];
        char *tmp;

        tmp = strtok(buff," ");
        strncpy(buf1,tmp,sizeof(buf1));

        tmp = strtok(NULL," ");
        strncpy(buf2,tmp,sizeof(buf2));

        tmp = strtok(buff," ");
        strcat(tableName, ".txt");

        if(strncmp("exit", buff, 4) == 0) 
        {
            printf("Server Exit...\n");
            break;
        }
        else if(strcmp("CREATE", buf1) == 0 && strcmp("TABLE", buf2) == 0)
        {
            createTable(tmp, buff);
        }
        else if(strcmp("DROP", buf1) == 0 && strcmp("TABLE", buf2) == 0)
        {
            dropTable(tmp);
        }
        else if(strcmp("INSERT", buf1) == 0 && strcmp("INTO", buf2) == 0)
        {
            insertInto(tmp, buff);
        }
        else if(strcmp("DROP", buf1) == 0 && strcmp("COLUMN", buf2) == 0)
        {
            dropColumn(buff);
        }
    }
}
  
//Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
  
    //Socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }
    bzero(&servaddr, sizeof(servaddr));
  
    //Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
  
    //Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }
    //Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }
    len = sizeof(cli);
  
    //Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
    {
        printf("server acccept the client...\n");
    }
    //Function for chatting between client and server
    func(connfd);
  
    //After chatting close the socket
    close(sockfd);
}       