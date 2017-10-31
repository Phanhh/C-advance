#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Library/libfdr/jrb.c"

typedef struct{
  char IP[16];
  char domain[100];
}DNS;

void Menu(){
  printf("*************************\n");
  printf("1. Read and Display text file.\n");
  printf("2. Add new IP and domain.\n");
  printf("3. Find an IP address.\n");
  printf("4. Find a domain.\n");
  printf("5. Exit.\n");
  printf("\n");
}

JRB importDB(FILE *fin){
  JRB dns = make_jrb();
  int count = 0;
  char total_str[5];
  int total;
  DNS tmp;
  while(!feof(fin)){
    if(count == 0){
      fprintf(fin,"%s\n",total_str);
      total = atoi(total_str);
      if(total >5){
	return NULL;
      }
    }else{
      do{
	fprintf(fin,"%s\n%s\n",tmp.domain, tmp.IP);
	count++;
	jrb_insert_str(dns,strdup(tmp.domain), new_jval_s(tmp.IP));
      }while(count <= total);
    }
  }
  return dns;
}

void addEntry(JRB dns){
  char domain[100];
  char IP[16];
  printf("Domain: ");
  while(getchar()!='\n');
  scanf("%[^\n]", domain);
  printf("IP: ");
  scanf("%s", IP);
  if (jrb_find_str(dns,domain) != NULL) {
    printf("Entry existed \n");
  } else {
    jrb_insert_str(dns, strdup(domain),new_jval_s(IP));
    printf("Added entry \n");
  }
}

void searchIP(JRB dns){
  char domain[100];
  printf("Domain: ");
  while(getchar()!='\n');
  scanf("%[^\n]", domain);
  JRB ptr;
  jrb_traverse(ptr, dns){
    JRB node = jrb_find_str(ptr,domain);
    if(node == NULL){
      printf("Domain not existed.\n");
    } else 
      printf("Domain: %s - IP: %s\n",jval_s(node->key), jval_s(node->val));
     
    }
  }

void searchDomain(JRB dns){
  char domain[100];
  char IP[16];
  printf("IP: ");
  while(getchar()!='\n');
  scanf("%[^\n]", IP);
  JRB ptr;
  jrb_traverse(ptr, dns){
    JRB node = jrb_find_str(ptr,domain);
    if(strcmp(jval_s(node->val),IP) == 0){
	printf("Domain: %s - IP: %s\n",jval_s(node->key), jval_s(node->val));
    } else 
       printf("IP not existed.\n");
     
    }
}

int main(){
  FILE *fin;
  if((fin = fopen("dns.txt", "r")) == NULL){
    printf("Cannot open file dns.txt\n");
    return 1;
  }
  JRB dns = importDB(fin);
  fclose(fin);
  if( dns == NULL){
    printf("File not valid.\n");
    return 1;
  }
  
  JRB node;
  
  int menu = 0;

  
  do{
    Menu();
    printf("Selection: ");
      scanf("%d", &menu);
      switch(menu) {
      case 1:
	jrb_traverse(node, dns) {
	  printf("%s\t%s\n", jval_s(node->key), jval_s(node->val));
	}
	break;
      case 2:
	addEntry(dns);
	break;
      case 3:
	searchIP(dns);
	break;
      case 4:
	searchDomain(dns);
	break;
      case 5:
	break;
      default:
	printf("Invalid selection.\n");
	break;
      }
  }while(menu != 5);
  return 0;
}
