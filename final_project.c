#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
//===========================  STRUCTURE DECLARATION  =========================

struct Data
{
  char name[35];
  long int number;
  char sex[8];
  char email[100];
};

//===========================  FUNCTION PROTOTYPE DECLARATION  ================

void Menu();
void start();
void back();
void addrecord();
void listrecord();
void modifyrecord();
void deleterecord();
void searchrecord();

//===========================  START OF THE PROGRAM ===========================

int main()
{
  system("color F0");
  start();
  return 0;
}

void start()
{
  Menu();
}

void back()
{
  start();
}

//===============================  WELCOME MENU  ===============================

void Menu()
{
  system("cls");
  printf("\n\t<><><><><>  WELCOME TO PHONEBOOK  <><><><><>\n");
  printf("\t____________________________________________");
  printf("\n\t\t\t  MENU\t\t\n\n");
  printf("\t1.Add New   \t 2.List   \t  3.Modify  \n\t4.Search \t 5.Delete\t  6.Exit");
  printf("\n\t____________________________________________");
  printf("\n\n\tEnter Key (1 to 6) : ");
  switch (getch())
  {
  case '1':
    addrecord();
    break;
  case '2':
    listrecord();
    break;
  case '3':
    modifyrecord();
    break;
  case '4':
    searchrecord();
    break;
  case '5':
    deleterecord();
    break;
  case '6':
    exit(0);
    break;
  default:
    system("cls");
    printf("\nPlease Enter a Valid Number !!");
    printf("\n(Enter any key to Go Back)");
    getch();
    Menu();
  }
}

//=============================  ADDING CONTACTS ==============================

void addrecord()
{
  system("cls");
  FILE *f;
  struct Data p;
  printf("\n\tAdding a new contact.\n\tPlease add the information.\n\n");
  printf("\t=========================================\n");
  f = fopen("mini-project.txt", "ab+");
  printf("\n\t Enter name : ");
  scanf("%s", &p.name);
  printf("\t Enter phone no : ");
  scanf("%ld", &p.number);
  printf("\t Enter sex : ");
  scanf("%s", &p.sex);
  printf("\t Enter E-email : ");
  scanf("%s", &p.email);
  fwrite(&p, sizeof(p), 1, f);
  printf("\n\t=========================================");
  fflush(stdin);
  printf("\n\n\tRecord Successfully Saved :)");
  fclose(f);
  printf("\n\t(Enter any key to Go Back)");
  getch();
  system("cls");
  Menu();
}

//=======================  DISPLAYING THE CONTACT LIST  =======================

void listrecord()
{
  struct Data p;
  FILE *f;
  int h = 1;
  f = fopen("mini-project.txt", "rb");
  if (f == NULL)
  {
    system("cls");
    printf("\nThere is nothing in the file to Display :( ");
    printf("\n(Enter any key to Go Back)");
    getch();
    Menu();
  }
  system("cls");
  printf("\n\n\n\tCONTACT-LIST : \n\n ");
  while (fread(&p, sizeof(p), 1, f) == 1)
  {
    printf("\t[%d]=========================================", h);
    printf("\n\t   Name=%s\n\t   Mobile no=%ld\n\t   Sex=%s\n\t   E-mail=%s\n", p.name, p.number, p.sex, p.email);
    printf("\t   =========================================\n\n");
    h++;
    getch();
  }
  fclose(f);
  printf("\n\t(Enter any key to Go Back)");
  getch();
  system("cls");
  Menu();
}

//======================  MODIFYING THE CONATACT LIST  =======================

void modifyrecord()
{
  int c;
  FILE *f, *fp;
  int flag = 0;
  struct Data p, s;
  char name[50];
  f = fopen("mini-project.txt", "rb+");
  fp = fopen("Modifying-Contact.txt", "w");
  if (f == NULL)
  {
    printf("No Contact Data available to modify :(");
    printf("(Enter any key to Go Back)");
    getch();
    Menu();
  }
  else
  {
    system("cls");
    printf("\n\tModifying Contact Information.\n");
    printf("\n\tEnter the Name of the Contact you want to modify : \n\t");
    scanf("%s", &name);
    while (fread(&p, sizeof(p), 1, f) == 1)
    {
      if (stricmp(name, p.name) != 0)
        fwrite(&p, sizeof(p), 1, fp);
    }
    printf("\n\t=========================================\n");
    printf("\n\tEnter name:");
    scanf("%s", &s.name);
    printf("\tEnter phone no:");
    scanf("%ld", &s.number);
    printf("\tEnter sex:");
    scanf("%s", &s.sex);
    printf("\tEnter e-mail:");
    scanf("%s", &s.email);
    printf("\n\t=========================================\n");
    fwrite(&s, sizeof(s), 1, fp);
    fflush(stdin);
    fclose(f);
    fclose(fp);
    remove("mini-project.txt");
    rename("Modifying-Contact.txt", "mini-project.txt");
  }
  printf("\n\t(Enter any key to Go Back)");
  getch();
  system("cls");
  Menu();
}

//=======================SEARCHING FROM CONTACT LIST  =======================

void searchrecord()
{
  struct Data p;
  FILE *f;
  int d;
  char name[100];
  f = fopen("mini-project.txt", "rb");
  if (f == NULL)
  {
    system("cls");
    printf("\nNo Contacts have been saved yet.\n");
    printf("(Enter any key to Go Back)");
    getch();
    Menu();
  }
  system("cls");
  printf("\n\tSearching Contacts...");
  printf("\n\tEnter Name of the Data to Search\n\t");
  scanf("%s", &name);
  while (fread(&p, sizeof(p), 1, f) == 1)
  {
    if (stricmp(p.name, name) == 0)
    {
      printf("\n\n\tDetail Information About %s ;", name);
      printf("\n\t=========================================\n");
      printf("\tName : %s\n\tMobile no : %ld\n\tsex : %s\n\tE-mail : %s\n", p.name, p.number, p.sex, p.email);
      printf("\t=========================================\n");
      d = 1;
    }
  }
  if (d == 1)
    printf("\n\tYour Record is displayed.");
  else
    printf("\n\tFile not Found !!");
  fclose(f);
  printf("\n\t(Enter any key to Go Back)");
  getch();
  system("cls");
  Menu();
}

//=======================  DELETING FROM CONTACT LIST =======================

void deleterecord()
{
  struct Data p;
  FILE *f, *ft;
  int flag = 0;
  char name[100];
  char ques[100];
  printf("\n\n\tDo You want to delete the entire Contact list ?\n\t(Yes or No)  ");
  scanf("%s", &ques);
  if ((stricmp(ques, "Yes") == 0))
  {
    printf("\n\tAre you Sure ?\n\t(Data cannot be retrieved.) ");
    scanf("%s", &ques);
    if ((stricmp(ques, "Yes") == 0))
    {
      remove("mini-project.txt");
      printf("\n\tData Erased Successfully.");
      printf("\n\t(Enter any key to go back)");
      getch();
      Menu();
    }
    else
    {
      system("cls");
      printf("\n(Enter any key to Go Back)");
      getch();
      Menu();
    }
  }
  else
  {
    f = fopen("mini-project.txt", "rb");
    if (f == NULL)
    {
      printf("\n\tNo Contacts have been added yet :(");
    }
    else
    {
      ft = fopen("temp.txt", "wb+");
      if (ft == NULL)
        printf("\n\tNo Contacts to display :(");
      else
      {
        printf("\n\tEnter Name of the Contact to be deleted : \n\t");
        scanf("%s", &name);
        fflush(stdin);
        while (fread(&p, sizeof(p), 1, f) == 1)
        {
          if (stricmp(p.name, name) != 0)
            fwrite(&p, sizeof(p), 1, ft);
          if (stricmp(p.name, name) == 0)
            flag = 1;
        }
        fclose(f);
        fclose(ft);
        if (flag == 1)
        {
          remove("mini-project.txt");
          rename("temp.txt", "mini-project.txt");
          printf("\n\tContact has been deleted successfully.");
        }
        else
        {
          printf("\n\tNo such Contact exist");
          remove("temp.txt");
        }
      }
    }
  }
  printf("\n\t(Enter any key to Go Back)");
  getch();
  system("cls");
  Menu();
}

//===========================  END OF THE PROGRAM  ===========================
