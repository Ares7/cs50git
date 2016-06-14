/****************************************************************************
 * Singly Linked List
 * https://en.wikibooks.org/wiki/Data_Structures/Singly_Linked_Lists
 *
 * Copyright (c) 2016,
 * Sergey Nasonov <sergey.nasonov@tum.de>
 * All rights reserved.
 *
 * BSD 3-Clause License
 * http://www.opensource.org/licenses/BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * The name of Sergey Nasonov may not be used
 *   to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ***************************************************************************/

#include "cs50.c"
#include <stdio.h>

typedef struct list                        
{
 int data;
 
 struct list *next;
}
list;

list* create_list(int val)
{
  list* nnode = malloc(sizeof(list));

  if(nnode != NULL)
  {
    nnode->data = val;
    nnode->next = NULL;    

    return nnode;
  }
  else 
    return NULL;
}

list* destroy(list* head)
{
  /*
  //Recursive way(for short lists)
  if( head-> next != NULL)
  {
    destroy(head->next);  
  }

  free(head);
  head=NULL;
 */
  /*
  OR:
 if (head) {
    destroy(head->next);
    free(head);
  }
  */

  list* ptr = malloc(sizeof(list));  

  if(ptr != NULL)
  {
   while(head)
    {
      ptr=head->next;
      free(head);
      head=ptr;
    }
    free(ptr);

    return head;
  }
  else 
    return NULL;


}

list* add_item(list* head, int val)
{
  list* nnode = malloc(sizeof(list));

  if(nnode != NULL)
  {
  nnode->data = val;
  nnode->next = head;   

  head = nnode;

  return head;
  }
  else 
    return NULL;
}

void show_all(list* head)
{
  printf("%s\n", " \n Here is the entire List: ");
  while(head!=NULL)
  {
    printf("%i \n", head->data);
    head = head->next;
  }
}

bool find(list* head, int num)
{
  while(head!=NULL)
  {
    if(head->data == num)
      return true;
    else
    head = head->next;
  }
  return false;
}

int main(void)
{
  //list.data=2;
  
  list *head = NULL;


 while(1)
  {
    printf("%s \n",
      "\n Please choose option below: \n" 
      "1. Create List \n" 
      "2. Add element \n"
      "3. Look up element \n"
      "4. Show all List \n"
      "5. Remove element \n"
      "6. Remove all elements \n"  
      "7. Exit \n");

      int choice = GetInt();
      
      if (choice == 1)
      {   
        if(!head)  
          {
            printf("%s \n","Enter value to add into a new List: ");
            int input = GetInt();
              
            head = create_list(input);

            if(!head)
              printf("%s\n", " \n Operation failed! ");
            else 
              printf("%s\n", " \n List has been created! ");
          }
        else 
          printf("%s \n","List is already created! ");
      

        }
      if (choice == 2)
      {
          if(!head)  
          {
            printf("%s \n","List is empty, create it first!");
            continue;
          }
        else 
          {
            printf("%s \n","Enter an integer value to add: ");
            int vadd = GetInt();
            head = add_item(head, vadd);

            if(!head)
              printf("%s\n", " \n Operation failed! ");
            else 
              printf("%s\n", " \n Item has been added to the List! ");
           
              
          }        
      }
      
      if (choice == 3)
      {
          if(!head)  
          {
            printf("%s \n","List is empty, create it first!");
            continue;
          }
        else 
          {
            printf("%s \n","Enter an integer value to find: ");
            int fel = GetInt();

            if(find(head, fel) == 1)
              printf("%s \n","\n Value is in the List!");
            else 
              printf("%s \n","\n Value is missing!");
          }

       
      }
      
      if (choice == 4)
      {
        if(!head)  
         {
            printf("%s \n","List is empty, create it first!");
            continue;
          }
        else 
          {
            show_all(head);
          }

        
      }

      if (choice == 5)
      {
        printf("%s \n","Not implemented!");
        continue;
        /*
        printf("%s \n","Enter value to remove");
        int rem = GetInt();
        remove_item(rem);
        */
      }

      if (choice == 6)
      {
         if(!head)  
         {
            printf("%s \n","List is empty, create it first! ");
            continue;
          }
        else 
          {
            head=destroy(head);

            if(!head)
              printf("%s\n", " \n List has been destroyed!! ");
            else
              printf("%s\n", " \n Operation failed! ");
          }
        
      }

      if (choice == 7)
      {
       
        head=destroy(head);

        if(!head)
          {
            
            printf("%s \n","Servus!");
            break;
           }
         else
        {
          printf("%s\n", " \n Destroying of the List failed! ");
          break;
        }          
          

      }


  }

    return 0;
}