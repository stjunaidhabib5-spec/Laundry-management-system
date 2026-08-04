
//........................................Singly Linked List.......................................................................
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;

};
 struct node *head=NULL;

 void insertatbegin(int data)
   {
        struct node *nn = malloc(sizeof(struct node));
        nn->data=data;
        nn->next=head;
        head=nn;

   }
 void deleteatbegin()
   {
       struct node *k = head;
       head = head->next;
       free(k);
   }


 void insertatmiddle(int data,int lastvalue)
   {
       struct node *nn = malloc(sizeof(struct node));
       nn->data=data;
       struct node *temp=head;
       while (temp->data!=lastvalue)
        {
            temp=temp->next;
        }
       nn->next=temp->next;
       temp->next=nn;
   }

 void deleteatfixedposition(int value)
   {
       struct node *k;
       struct node *temp= head;
       while(temp->next->data!=value)
          {
            temp=temp->next;
          }
       k=temp->next;
       temp->next=k->next;
       free(k);
   }

 void insertatlast(int data)
   {
       struct node *nn = malloc(sizeof(struct node));
       nn->data=data;
       nn->next=NULL;
       struct node *temp=head;
       while (temp->next!=NULL)
         {
            temp=temp->next;
         }
       temp->next=nn;
   }

 void deleteatlast()
   {
       struct node *k=NULL;
       struct node *temp = head;
       while(temp->next!=NULL)
         {
             k=temp;
            temp=temp->next;
         }
       k->next=NULL;
       free(temp);
   }

void updatedlist(int oldData,int newData)
    {
        struct node *temp=head;
        struct node *temp1=NULL;
        while (temp!=NULL)
       {

            if(temp->data==oldData)
            {
              temp->data=newData;
              printf("\nUpdated data is : %d to %d \n",oldData,newData);
              temp1=temp;
              temp=NULL;
            }
            else
            {
           temp=temp->next;
            }

        }
        if(temp1==NULL)
        {
           printf("\nValue %d is not found\n",oldData);
        }

    }
void Searchlist(int key)
    {
        struct node *temp2=head;
        struct node *temp3=NULL;
        while (temp2!=NULL)
       {

            if(temp2->data==key)
            {
                printf("\nTrue\n");
                printf("\nThe search result is %d\n",key);
                temp3=temp2;
                temp2=NULL;
            }

            else
            {
                temp2= temp2->next;
            }
        }
        if(temp3==NULL)
        {
           printf("FALSE\n");
        }

    }

 void printList()
   {
       struct node *temp = head;
        while (temp!=NULL)
          {
            printf("%d ",temp->data);
            temp=temp->next;
          }
   }

int main()
{
    insertatbegin(4);
    insertatbegin(6);
    insertatbegin(8);
    insertatbegin(10);
    printf("\nAt the Beginning List: ");
    printList();
    printf("\n");

    insertatmiddle(15,10);
    insertatmiddle(16,15);
    insertatmiddle(17,16);
    insertatmiddle(18,17);
    printf("\nAt the middle List: ");
    printList();
    printf("\n");

    insertatlast(11);
    insertatlast(12);
    insertatlast(13);
    insertatlast(14);
    printf("\nAt the last List: ");
    printList();
    printf("\n");

    printf("\nThe List: ");
    printList();
    printf("\n");

    deleteatbegin();
    printf("\nThe Beginning Delete List: ");
    printList();
    printf("\n");

    deleteatlast();
    printf("\nThe Last Delete List: ");
    printList();
    printf("\n");

    deleteatfixedposition(6);
    printf("\nThe Fixed Delete List: ");
    printList();
    printf("\n");

    deleteatfixedposition(12);
    printf("\nThe Fixed Delete List: ");
    printList();
    printf("\n");

    updatedlist(18,2);
    printf("\nThe Updated List: ");
    printList();
    printf("\n");

    updatedlist(19,4);
    printf("\nThe Updated List: ");
    printList();
    printf("\n");

    Searchlist(8);
    printf("\n");

    Searchlist(5);
    printf("\n");

}

//...........................................Circular Linked List .......................................................

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;

};
 struct node *head=NULL;

 void insertatbegin(int data)// insert at beginning e last node change kora lage
   {
       struct node *nn = malloc(sizeof(struct node));
      if(nn==NULL)
        {
            exit;
       }
        else if(head==NULL)
        {
        nn->data=data;
        nn->next=nn;//connection ( making a circular )
        head=nn;

        }
        else
        {
        nn->data=data;
        nn->next = head;

        struct node *temp = head;
        while (temp->next != head)//last node khujar loop
        {
            temp = temp->next;
        }
        temp->next = nn;//connection ( 1st node address last node er next dite hobe tahole circular linked list hobe)
        head = nn;// inser begin node er code & insert last er code same but ai line just hobe nah
        }
   }

 void deleteatbegin()
   {
       struct node *k = head;

       struct node *temp = head;
        while (temp->next != head)// last node khujar loop + node khujte hobe circular maintain korar jonno
        {
            temp = temp->next;
        }
        head = head->next;
        temp->next=head;// last node e 1st node er address or head dia dite hobe naile circular thakbe nah
       free(k);
   }


 void insertatmiddle(int data,int lastvalue)// insert middle single linked list er moto
   {
       struct node *nn = malloc(sizeof(struct node));
       nn->data=data;
       struct node *temp=head;
       while (temp->data!=lastvalue)
        {
            temp=temp->next;
        }
       nn->next=temp->next;
       temp->next=nn;
   }

 void deleteatmiddle(int value) //same like Single linked list
   {
       struct node *k;
       struct node *temp= head;
       while(temp->next->data!=value)
          {
            temp=temp->next;
          }
       k=temp->next;
       temp->next=k->next;
       free(k);
   }

 void insertatlast(int data)// code same insert at begin ar moto

   {
       struct node *nn = malloc(sizeof(struct node));
      if(nn==NULL)
        {
            exit;
       }
        else if(head==NULL)
        {
        nn->data=data;
        nn->next=nn;
        head=nn;

        }
        else
        {
        nn->data=data;
        nn->next = head;

        struct node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = nn;



        }
   }
 void deleteatlast()
   {
       struct node *k=NULL;
       struct node *temp = head;
       while(temp->next!=head)
         {
             k=temp;
            temp=temp->next;
         }
       k->next=head;
       free(temp);
   }


 void printList()
   {
       if (head==NULL)
    {
        printf("List is empty!\n");
        return;
    }
    else
        {
        struct node *temp = head;
        printf("%d ",temp->data);// age head or 1st node er data print kore nite hobe
        temp=temp->next;// head or 1st node er next temp e ashbe

        while (temp!=head)// last node projonto cholbe
          {
            printf("%d ",temp->data);
            temp=temp->next;
          }
        }
   }

int main()
{
    insertatbegin(4);
    insertatbegin(6);
    insertatbegin(8);
    insertatbegin(10);
    printf("\nAt the Beginning List: ");
    printList();
    printf("\n");

    insertatmiddle(15,10);
    insertatmiddle(16,15);
    insertatmiddle(17,16);
    insertatmiddle(18,17);
    printf("\nAt the middle List: ");
    printList();
    printf("\n");

    insertatlast(11);
    insertatlast(12);
    insertatlast(13);
    insertatlast(14);
    printf("\nAt the last List: ");
    printList();
    printf("\n");

    printf("\nThe List: ");
   printList();
    printf("\n");

    deleteatbegin();
    printf("\nThe Beginning Delete List: ");
    printList();
    printf("\n");

    deleteatmiddle(6);
    printf("\nThe Middle Delete List: ");
    printList();
    printf("\n");

    deleteatmiddle(12);
    printf("\nThe Middle Delete List: ");
    printList();
    printf("\n");

    deleteatlast();
    printf("\nThe Last Delete List: ");
    printList();
    printf("\n");

}

//.....................................................Double Linked List..................................................................................

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
    struct node *pre;

};
 struct node *head=NULL;//Global variable call ;it can access from anywhere .

 //joining new node in begin.
 void insertatbegin(int data)
   {
        struct node *nn = malloc(sizeof(struct node));
        if(nn==NULL)
        {
            exit;   // if the Memory Allocation fails then exit command starts working
        }
        else if (head==NULL) // works only the 1ST node of the list
        {
        nn->data=data;
        nn->pre=NULL; // putting NULL in the previous(*pre) pointer of new node
        // connection
        nn->next=head; // putting head address in the next(*next) pointer of new node or 1st node address in the new node next
        head=nn; //connection ( now, new node become 1st node)
         }
         else // works after making 1st node of the list
         {
        nn->data=data;
        nn->pre=NULL;
        nn->next=head;
        head->pre=nn;//connection ( 1st node er previous(*pre) pointer e new node address)
        head=nn;//connection ( now, new node become 1st node)
         }
   }

 //joining new node in middle
void insertatmiddle(int data,int After_Node)
   {
       struct node *nn = malloc(sizeof(struct node));
       nn->data=data;
       struct node *temp=head;

       while (temp->data!=After_Node) //loop find for the given value node er ager node
        {
           temp=temp->next;
        }
            nn->pre=temp; // putting the address of temp in new node er previous
            nn->next=temp->next;//putting the address of temp er next in the new node er next
            temp->next=nn;//putting the address of new node in temp er next
            temp->next->pre=nn;//putting the address of new node in the last node er previous

   }

// Joining new node in the end
void insertatlast(int data)
   {
       struct node *nn = malloc(sizeof(struct node));
       nn->data=data;
       nn->next=NULL;
       struct node *temp=head;
       while (temp->next!=NULL)
         {
            temp=temp->next;
         }
       nn->pre=temp; //putting the address of temp in the new node er previous
       temp->next=nn; //putting the address of new node in the temp er next

   }
   // ..............................From here all BANGLISH .............................................................
   // Deleting new node in the begin
void deleteatbegin()
    {
       struct node *k = head;
       head = head->next; // 2nd node er address putting in the head
       head->next->pre=NULL;// 2nd node er previous ke NULL kora hoise
       free(k);// 1st node ke free kora hoise or delete kora hoise
    }

 //Deleting new node in the Middle
void deleteatmiddle(int Aftervalue) // middle jonno always akta value\ name etc nite or pathaite hobe or question e bola thakbe
  {
    struct node *k;// akta kidnapper or pointer nite hobe
    struct node *temp = head;// loop callanor jonno akta pointer nite hobe & head address dia dite hobe pointer ke
       while(temp->next->data!=Aftervalue) //loop er condition
          {
            temp=temp->next;
          }
       k=temp->next;//temp e jei address ase oi node er next er address [K] ke dia dite hobe
       temp->next=k->next;//connection( K er next e jei address ase oita temp->next jabe or boshbe.)

       temp->next->next->pre=temp;//connection(delete korar node er pore node er previous e delete korar ager node er address dite hobe
      // k->next->pre=k->pre;//( akta use korle hobe, same duita)
       free(k);
  }

//Deleting new node in the Last
void deleteatlast()
   {
       struct node *k;
       struct node *temp = head;
       while(temp->next!=NULL)
         {
             k=temp; // temp e jah pabo tah K te copy kore nibo
             temp=temp->next;
         }
        temp->pre=NULL;//last node er preious ke null korte hobe
        temp->next=NULL;// last node er next ke null korte hobe
       k->next=NULL;//last node er ager node er next ke null korte hobe
       free(temp);// kidnapper ke free or pointer ke free kore dite hobe
   }

//display
 void printList()
   {
       struct node *temp = head;
        while (temp!=NULL)
          {
            printf("%d ",temp->data);
            temp=temp->next;
          }

   }

int main()
{
    insertatbegin(4);
    insertatbegin(6);
    insertatbegin(8);
    insertatbegin(10);
    insertatbegin(11);
    insertatbegin(12);
    printf("\nAt the Beginning List: ");
    printList();
    printf("\n");

    // (13 is the Data & 8 is the After_Node)
    insertatmiddle(13,8);
    insertatmiddle(14,13);
    insertatmiddle(15,14);
    insertatmiddle(16,15);
    insertatmiddle(17,16);
    insertatmiddle(18,17);
    printf("\nAt the MIddle List: ");
    printList();
    printf("\n");

    insertatlast(20);
    insertatlast(21);
    insertatlast(22);
    insertatlast(23);
    insertatlast(24);
    insertatlast(25);
    printf("\nAt the Last List: ");
    printList();
    printf("\n");

    printf("\nThe List: ");
    printList();
    printf("\n");

    deleteatbegin();
    printf("\nThe deleted at Begin List: ");
    printList();
    printf("\n");

    deleteatmiddle(20);
    printf("\nThe deleted at Middle List: ");
    printList();
    printf("\n");

    deleteatlast();
    printf("\nThe deleted at Last List: ");
    printList();
    printf("\n");
}

//................................................Double Linked List String........................................................

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    char data[1000];
    struct node *next;
    struct node *pre;

};
 struct node *head=NULL;//Global variable call ;it can access from anywhere .

 //joining new node in begin.
 void insertatbegin(char data[1000])
   {
        struct node *nn = malloc(sizeof(struct node));
        if(nn==NULL)
           {
                printf("Memory Allocate failed");
                 return;
           }

        else if (head==NULL)
        {
           strcpy(nn->data, data);
           nn->pre=NULL;
           nn->next=head;
           head=nn;
         }
         else
         {
           strcpy(nn->data,data);
           nn->pre=NULL;
           nn->next=head;
           head->pre=nn;
           head=nn;
         }
   }

 //joining new node in middle
void insertatmiddle(char data[1000],char After_Node[1000])
   {
       struct node *nn = malloc(sizeof(struct node));
       if(nn==NULL)
       {

            printf("Memory Allocate failed");
            return;
       }

       else
       {

       strcpy(nn->data,data);// string e data input dite hobe strcpy use korte hoi .likhar niom strcpy( jei khane rakhbo, jah rakhbo)
       struct node *temp=head;

       while (strcmp(temp->next->data, After_Node)!=0) // string use korle while loop e compare string use korte hobe .
        {
           temp=temp->next;
        }


            nn->pre=temp;
            nn->next=temp->next;
            temp->next=nn;
            temp->next->pre=nn;
        }
   }
// Joining new node in the end
void insertatlast(char data[1000])
   {
       struct node *nn = malloc(sizeof(struct node));
       if(nn==NULL)
       {

            printf("Memory Allocate failed");
            return;
       }

       else
       {
       strcpy(nn->data,data);
       nn->next=NULL;
       struct node *temp=head;
       while (temp->next!=NULL)
         {
            temp=temp->next;
         }
       nn->pre=temp;
       temp->next=nn;
       }
   }
 // Deleting new node in the begin
void deleteatbegin()
    {
       struct node *k = head;
       head = head->next;
       head->next->pre=NULL;
       free(k);
    }

 //Deleting new node in the Middle
void deleteatmiddle(char value[1000])
  {
    struct node *k;
    struct node *temp = head;
     while (strcmp(temp->next->data,value)!=0)

          {
            temp=temp->next;
          }
       k=temp->next;
       temp->next=k->next;

       temp->next->next->pre=temp;

       free(k);
  }

//Deleting new node in the Last
void deleteatlast()
   {
       struct node *k;
       struct node *temp = head;
       while(temp->next!=NULL)
         {
             k=temp;
             temp=temp->next;
         }
        temp->pre=NULL;
        temp->next=NULL;
       k->next=NULL;
       free(temp);
   }

//display
 void printList()
   {
       struct node *temp = head;
        while (temp!=NULL)
          {
            printf("%s ", temp->data);
            temp=temp->next;
          }
   }

int main()
{
    insertatbegin("4");// string use korle in [ " ___" ] use korte hoi. nahole kaj korbe nah
    insertatbegin("6");
    insertatbegin("8");
    insertatbegin("10");
    insertatbegin("11");
    insertatbegin("12");
    printf("\nAt the Beginning List: ");
    printList();
    printf("\n");

    // (Bangladesh is the Data & 8 is the After_Node)
    insertatmiddle("Bangladesh" , "8");
    insertatmiddle("14" , "Bangladesh");
    insertatmiddle("15", "14");
    insertatmiddle("India", "15");
    insertatmiddle("17" , "India");
    insertatmiddle("18" , "17");
    printf("\nAt the Middle List: ");
    printList();
    printf("\n");

    printf("\nThe List: ");
    printList();
    printf("\n");

    deleteatbegin();
    printf("\nThe deleted at Begin List: ");
    printList();
    printf("\n");

    deleteatmiddle("India");
    printf("\nThe deleted at Middle List: ");
    printList();
    printf("\n");

    deleteatlast();
    printf("\nThe deleted at Last List: ");
    printList();
    printf("\n");
}

//.............................................Stack.........................................

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct stack  // stack bole stack likhte hoi
{
    int data;
    struct stack *next;

};
 struct stack *Top=NULL; // head jygai Top likhte hoi.
 void printList()
 {
     struct stack *nn = Top;
     while (nn!=NULL)
     {
         printf("%d ",nn->data);
            nn=nn->next;
     }
 }
// Push Function
 void Push (int data) //  Push = single linked list er insert at the beginning
 {
   struct stack *nn = malloc(sizeof(struct stack));
        nn->data=data;
        nn->next=Top;
        Top=nn;
 }
//Pop Function
 void Pop() //  Pop = single linked list er delete at the beginning
 {


     struct stack *k = Top;
    Top = Top->next;
    free(k);

 }
 int main()
 {
     Push(7);
    Push(8);
    Push(9);
     Pop();
printList();
 }

//.....................................Queue............................

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure Declaration
struct queue
{
    int data;
    struct queue *next;

};

// Global variable Declaration for Front & Rear
struct queue *front=NULL,*rear=NULL;

// Enqueue Function
void Enqueue(int data) // Enqueue = Single Linked List er insert from the Last + enqueue data pass korte hoi
 {
     if(front==NULL && rear==NULL) //  sobar ager node korar jonno mane 1st node jonno aita
     {
        struct queue *nn = malloc(sizeof(struct queue));
        nn->data=data;
        nn->next=NULL;
        front=nn;
        rear=nn;
      }
 else   // 1st node porar node er jonno
      {
     struct queue *nn = malloc(sizeof(struct queue));
        nn->data=data;
        nn->next=NULL;
        rear->next=nn;
        rear=nn;
      }
 }

 // Dequeue Function
 void Dequeue() // Dequeue = Single Linked List er Delete from the Beginning + dequeue data pass korte hoi nah
 {
  if(front==NULL&&rear==NULL)
        {
            exit;
        }
  else if (front==rear) // same hoile list or node ase akta
        {
             struct queue *k=front;
             front=rear=NULL;
             free(k);
        }
  else
        {
             struct queue *k1 = front;
             front = front->next;
             free(k1);
        }
 }
 void printList()
 {
     struct queue *temp = front;
     while(temp!=NULL)
     {
         printf("%d ",temp->data);

         temp=temp->next;
     }
     printf("\n");
 }



 int main()
   {
        Enqueue(8);
        Enqueue(10);
        Enqueue(12);
        printList();

        Dequeue();
        printList();

        Enqueue(6);
        Enqueue(7);
        printList();

    }

















