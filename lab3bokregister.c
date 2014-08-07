//
//  lab3bokregister.c
//
//  Bokregister.
//
//  Created by Kj Drougge on 2012-10-03.
//  Copyright (c) 2012 Kj Drougge. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct book {
  char author[20];
  char title[30];
  char year[5];
};

/***************************************************
/
/   _meny: Skriver ut en meny.
/
****************************************************/

void _meny()
{
  printf("\n1. Addera en bokuppgift\n");
  printf("2. Ta bort en bokupggift\n");
  printf("3. Ändra\n");
  printf("4. Sök\n");
  printf("5. Sortera\n");
  printf("6. Skriva ut register\n");
  printf("7. Avsluta\n\n");
}

/***************************************************
/
/   _printAll: Skriver ut alla böcker i listan
/   beroende på vilket antal böcker man vill visa.
/
****************************************************/

void _printAll(struct book *books ,int num_book)
{
  printf("Booknr:  Author:             Title:                        Year:\n");
  for(int i = 0; i < (num_book); i++)
    {
      printf("  %d   |  %-20s%-30s%-4s\n", i+1,books[i].author, books[i].title, books[i].year); 
    }
  printf("\n");
}

/***************************************************
/
/   _fill: flyttar böcker en position ner i arrayen
/   och tar antal böcker - 1.
/
****************************************************/

void _fill(struct book *books, int *num_book, int position)
{
  for(int i = 0; i < (*num_book) ; i++)
    {
      books[position-1] = books[position];
      position++;
    }
  (*num_book)--;
}

/***************************************************
/
/   _sort: Byter plats på de två böcker som jämförs.
/
****************************************************/

void _sort(struct book *book1, struct book *book2)
{
  char temp[30];
  strcpy(temp, book1->author);
  strcpy(book1->author, book2->author);
  strcpy(book2->author, temp);

  strcpy(temp, book1->title);
  strcpy(book1->title, book2->title);
  strcpy(book2->title, temp);

  strcpy(temp, book1->year);
  strcpy(book1->year, book2->year);
  strcpy(book2->year, temp);
}

/***************************************************
/
/   _sort_type: Frågar vad bokregistret ska sorteras av.
/
****************************************************/

void _sort_type(struct book *books, int num_book)
{
  int val;
  do{  
    printf("Sort by:\n1. Author\n2. Title\n3. Year\n(0 to return to menu)\n\n");
    scanf("%1d", &val); getchar();
  }while(val > -1 && val > 4); 

  switch(val)
    {
    case 0: return;
    case 1: 
      for(int i = 0; i < num_book; i++)
	{
	  for(int j = i + 1; j < num_book; j++)
	    {
	      if((strcasecmp(books[i].author, books[j].author)) > 0)
		{
		  _sort(&books[i], &books[j]);
		} 
	    }
	}
      break;
    case 2:    
      for(int i = 0; i < num_book; i++)
	{
	  for(int j = i + 1; j < num_book; j++)
	    {
	      if((strcasecmp(books[i].title, books[j].title)) > 0)
		{
		  _sort(&books[i], &books[j]);
		}
	    }
	}
      break;
    case 3:    
      for(int i = 0; i < num_book; i++)
	{
	  for(int j = i + 1; j < num_book; j++)
	    {
	      if((strcasecmp(books[i].year, books[j].year)) > 0)
		{
		  _sort(&books[i], &books[j]);
		}
	    }
	} 
      break;  
    default: _sort_type(books, num_book);
    }
}

/***************************************************
/
/   _delete: Frågar vilken bok som ska tas bort och
/   sätter stringen till NULL och kallar på fill för
/   att flytta upp böckerna.
/
****************************************************/

void _delete(struct book *books, int *num_book)
{
  int val;
  do{
    printf("Which booknr do you want to delete? (0 to return to menu) \n");
    scanf("%d", &val); getchar();
    if (val == 0)
      return;
  }while(val > (*num_book));

  strcpy(books[val-1].author, "\0");
  strcpy(books[val-1].title, "\0");
  strcpy(books[val-1].year, "\0");
  
  _fill(books, num_book, val);
  _printf("Booknr %d has been deleted!\n", val);
}

/***************************************************
/
/   _search: söker igenom hela bokregistret efter det
/   man vill finna. Anropar printAll för att skriva 
/   ut det man hittat och anropar _delete för att ta
/   bort en av böckerna man hittat.
/
****************************************************/

void _search(struct book *books, int *num_book)
{
  int i = 0, j = 0;
  char searchStr[20];
  struct book *book_pointer[MAX_BOOKS];
  struct book tempbooks[MAX_BOOKS];
  int book_position_array[MAX_BOOKS];
  printf("Searching for: ");
  gets(searchStr);
  
  for(i = 0; i < (*num_book); i++)
    {
      if(strcasestr(books[i].author, searchStr))
	{
	  book_position_array[j] = i;
	  j++;
	}
      else if(strcasestr(books[i].title, searchStr))
	{
	  book_position_array[j] = i; 
	  j++;
	}
      else if(strstr(books[i].year, searchStr))
	{
	  book_position_array[j] = i;
	  j++;
	}
    }

  for(int k = 0; k < j; k++) 
    { 
      book_pointer[k] = &books[book_position_array[k]];
      tempbooks[k] = books[book_position_array[k]];
    } 
  
  if(j == 0)
    printf("Book does not exist\n");
  else
    {

      _printAll(tempbooks, j);
      _delete((*book_pointer), num_book);    
    }
}

/***************************************************
/
/   _adjust: Frågar vilket boknr man ska ändra och 
/   sedan vad man vill ändra. 
/
****************************************************/

void _adjust(struct book *books, int *num_book)
{
  int val1, val2;
  do{
  printf("Which booknr do you want to adjust? (0 to return to menu) \n");
  scanf("%d", &val1); getchar();
  if (val1 == 0)
    return;

  }while(val1 > (*num_book));

    printf("Author: %s\n", books[val1-1].author);
    printf("Title: %s\n", books[val1-1].title);
    printf("Year: %s\n\n", books[val1-1].year);

  do{
    printf("1. Author\n2. Title\n3. Year\n");
    printf("(0 to return to menu)\n\n");
    scanf("%1d", &val2); getchar();
    if (val2 == 0)
      return;

    switch(val2)
      {
          case 1: printf("Author: "); gets(books[val1-1].author); break;
          case 2: printf("Title: "); gets(books[val1-1].title); break;
          case 3: printf("Year: "); gets(books[val1-1].year); break;
          default: printf("Error");
      }
    printf("\n");
  }while (val2 < 0 && val2 > 4);
}

/***************************************************
/
/   _add: Lägger till en bok i registret.
/
****************************************************/

void _add(struct book *books, int *num_book)
{
  if(*num_book == MAX_BOOKS)
    {
        printf("Register is full.\n");
        return;
    }

  printf("Author: ");
  gets(books[*num_book].author);
  printf("Title: ");
  gets(books[*num_book].title);
  printf("Year: ");
  gets(books[*num_book].year);

  (*num_book)++;
}

/***************************************************
/
/   _save_to_file: Sparar nummer av böcker och registret
/   i en binär fil.
/
****************************************************/

void _save_to_file(struct book *books, int *num_book, char filename[])
{
  FILE *file;
  file = fopen(filename, "wb");
  fwrite(num_book, sizeof(int), 1, file);
  fwrite(books, (sizeof(struct book) * (*num_book)), MAX_BOOKS, file);
  fclose(file);
}

/***************************************************
/
/   _load_to_file: Frågar om man vill öppna existerande
/   register eller skapa ett nytt. Om filnamnet finns
/   öppnas den, om det inte finns skapas filen och 
/   öppnas.
/
****************************************************/

void _load_from_file(struct book *books, int *num_book, char filename[])
{
  printf("Enter existing register or create new register: ");
  gets(filename);
  FILE *file;
  file = fopen(filename, "a+");
  fread(num_book, sizeof(int), 1, file);
  fread(books, sizeof(*books), MAX_BOOKS, file);
  fclose(file);
}

/***************************************************
/
/   main: Deklarerar variabler som skickas runt till
/   funktionerna. En oändlig for-loop med meny-valen
/
****************************************************/

int main()
{
  int num_books = 0;
  char filename[30];
  char choice;
  struct book bookReg[MAX_BOOKS];

  _load_from_file(bookReg, &num_books, filename);

  for(;;)
    {
      meny();
      scanf("%c", &choice);
      while (getchar() != '\n');
      switch(choice)
        {
            case '1': _add(bookReg, &num_books); break;
            case '2': _printAll(bookReg, num_books); _delete(bookReg, &num_books); break;
            case '3': _printAll(bookReg, num_books); _adjust(bookReg, &num_books); break;
            case '4': _search(bookReg, &num_books); break;
            case '5': _sort_type(bookReg, num_books); break;
            case '6': _printAll(bookReg, num_books); break;
            case '7': _save_to_file(bookReg, &num_books, filename); exit(0);
            default: printf("Valet finns ej\n"); meny();
        }
    }
  
  return 0;
}
