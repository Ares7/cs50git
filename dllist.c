#include "cs50.c"
#include <stdio.h>

typedef struct list                        
{
 int data;
 
 struct list *next;
 struct list *prev;
}
list;

list* create_list(int val)
{
  list* nnode = malloc(sizeof(list));

  if(nnode != NULL)
  {
    nnode->data = val;
    nnode->next = NULL;    
    nnode->prev = NULL;
    return nnode;
  }
  else 
    return NULL;
}

list* destroy(list* head)
{
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

list* remove_item(list* head, int vrem)
{
  list* ptr = malloc(sizeof(list));
  ptr = head;

  while(ptr!=NULL)
  {
    if(ptr->data == vrem)
    {
      if(ptr->prev == NULL)
      {
        //begin case++
        if (ptr->next == NULL)
        {
          //last elem
          free(ptr);
          printf("%s\n", " \n Element has been deleted!! ");

          return NULL;
        }
        else
        {
          ptr = ptr->next;
          free(ptr->prev);
          ptr->prev = NULL;
          printf("%s\n", " \n Element has been deleted!! ");

          return ptr;
        }
      }       
      
      if(ptr->prev != NULL && ptr->next != NULL )
      {
        //middle case
        //chk for one el only
       ptr->prev->next = ptr->next;
       ptr->next->prev = ptr->prev;

       free(ptr);
       printf("%s\n", " \n Element has been deleted!! ");
       
       return head; 

      }

      if(ptr->next == NULL)
      {
        //end case
        ptr = ptr->prev;
        free(ptr->next);
        ptr->next=NULL;

        printf("%s\n", " \n Element has been deleted!! ");
        return head;  

      }


    }
    else
    {
      ptr=ptr->next;  
    }
    
    
    
  }

  if (ptr==NULL)
    printf("%s \n","\n Value is missing!");
  
  return head;
}

list* add_item(list* head, int val)
{
  list* nnode = malloc(sizeof(list));

  if(nnode != NULL)
  {
  nnode->data = val;
  nnode->next = head;   
  head->prev = nnode;

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
        if(!head)  
         {
            printf("%s \n","List is empty, create it first! ");
            continue;
          }
        else 
          {            
            printf("%s \n","Enter value to remove");
            int vrem = GetInt();
            head = remove_item(head, vrem);
           
         }        
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