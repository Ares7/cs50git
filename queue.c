#include "cs50.c"
#include <stdio.h>

typedef struct queue                        
{
 int data;
 
 struct queue *next;
 struct queue *prev;
 
}
queue;

queue* create_queue(int val)
{
  queue* nnode = malloc(sizeof(queue));

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

queue* destroy(queue* head)
{
  queue* ptr = malloc(sizeof(queue));  

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

queue* pop(queue* head, int vrem)
{
  queue* ptr = malloc(sizeof(queue));
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

queue* push(queue* head, int val)
{
  queue* nnode = malloc(sizeof(queue));

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

void show_all(queue* head)
{
  printf("%s\n", " \n Here is the entire queue: ");
  while(head!=NULL)
  {
    printf("%i \n", head->data);
    head = head->next;
  }
}

bool find(queue* head, int num)
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
  queue *head = NULL;
  queue *tail = NULL;

  while(1)
  {
    printf("%s \n",
      "\n Please, choose an option below: \n" 
      "1. Create queue \n" 
      "2. Add elem  ent \n"
      "3. Look up element \n"
      "4. Show all queue \n"
      "5. Extract First added element \n"
      "6. Remove all elements \n"  
      "7. Exit \n"
          "Your choice:");

      int choice = GetInt();
      
      if (choice == 1)
      {   
        if(!head)  
          {
            printf("%s \n","Enter value to add into a new queue: ");
            int input = GetInt();
              
            head = create_queue(input);
            tail = head;
            if(!head)
              printf("%s\n", " \n Operation failed! ");
            else 
              printf("%s\n", " \n queue has been created! ");
          }
        else 
          printf("%s \n","queue is already created! ");
      

        }
      if (choice == 2)
      {
          if(!head)  
          {
            printf("%s \n","queue is empty, create it first!");
            continue;
          }
        else 
          {
            printf("%s \n","Enter an integer value to add: ");
            int vadd = GetInt();
            head = push(head, vadd);

            if(!head)
              printf("%s\n", " \n Operation failed! ");
            else 
              printf("%s\n", " \n Item has been added to the queue! ");
           
              
          }        
      }
      
      if (choice == 3)
      {
          if(!head)  
          {
            printf("%s \n","queue is empty, create it first!");
            continue;
          }
        else 
          {
            printf("%s \n","Enter an integer value to find: ");
            int fel = GetInt();

            if(find(head, fel) == 1)
              printf("%s \n","\n Value is in the queue!");
            else 
              printf("%s \n","\n Value is missing!");
          }

       
      }
      
      if (choice == 4)
      {
        if(!head)  
         {
            printf("%s \n","queue is empty, create it first!");
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
            printf("%s \n","queue is empty, create it first! ");
            continue;
          }
        else 
          {            
            printf("%s \n","Enter value to remove");
            int vrem = GetInt();
            head = pop(head, vrem);
           
         }        
      }

      if (choice == 6)
      {
         if(!head)  
         {
            printf("%s \n","queue is empty, create it first! ");
            continue;
          }
        else 
          {
            head=destroy(head);

            if(!head)
              printf("%s\n", " \n queue has been destroyed!! ");
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
          printf("%s\n", " \n Destroying of the queue failed! ");
          break;
        }          
          

      }


  }

    return 0;
}