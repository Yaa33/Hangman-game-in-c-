/*
 * File: hangman.c
 * Author: YAYA
 * Date: 2024-08-20
 * my first c project
 */


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//Defenition of Node in the linked list
typedef struct Node
{
    char wrd[10];          // word stored in the node  
    struct Node* next;     // pionter to the next node
    int key;               // key to identify the node
}Node;

//Functions prototypes


void create_alinkedlist(Node **root, char *str);     //create a singly linked list where it will store the words nedded for the game
void store_the_words(Node **root);                  // reading the file word.txt and storing the words in the list
void select_randomly(Node**root);                  // generate a number randomly to choose the word using the key
void display(char *str);                          // display the word for the game
void printing_the_hangman(int ncase) ;            // printing the hang man

 //main function
int main(){


   Node*root=NULL;     //Initialize the pointer to NULL
 

store_the_words(&root);   
srand(time(NULL));              // Seed the random number generato
select_randomly(&root);     
    return 0;
}

 

void create_alinkedlist(Node **root, char *str){  // pionter to pionter of the head node of the list which is root and  pionter to the word str         
  
  static  int value=1;
    Node* newnode;                      // create a new node
   
    newnode=malloc(sizeof(Node));          // allocate memory for the new node
      
      if(newnode==NULL){                   // check if the allocation was successful
        printf("failed allocation");        
        exit(1);
      }
  
    strcpy(newnode->wrd,str);                      // store the word in  the new node word
    newnode->next=NULL;                            // set the next pointer of the new node to NULL
    newnode->key=value;                            // store the value in new node key 
   
    if(*root==NULL){                                 // if the list is empty set the root to point new node
         *root=newnode;                            // head node points to the adress of the new node
    }else{
       Node* curr=*root;                          
      while(curr->next!=NULL){               
        
        curr=curr->next;

      }
     
     curr->next=newnode;
  
    }
    
   
   value++;                 //increment the value every node creation


}


void store_the_words(Node **root){
   

   FILE* read=fopen("words.txt", "r");             // open words.txt in read mode
     char  word[10];                              // buffer to store each  word
    
  if(read==NULL){
        printf("failed to open the read file");    // inform the user if the file couldn't be  accessed 
        exit(2);

   }

  while(fgets(word,10 ,read)!=NULL){              // read  each lines  in word.txt 

   word[strcspn(word, "\n")] = '\0';             // remove the newline from the words
     create_alinkedlist(root, word);             // store the words in the singly linked list
  }

fclose(read);                                    // close the file 
}

void select_randomly(Node**root){


 int count_list=0;                             
  
  Node*curr=*root;                              // assign  the head node to the current pointer 


  while(curr!=NULL){                            // count the number of words stored in the list 
    count_list++;
    curr=curr->next;
  }

 int value=rand()%count_list+1;                // generate the random number between 1 and count_list


curr=*root;                                    //reassign the head node to the current pointer 

while(curr!=NULL){                            
if(curr->key==value){                            // return the word to display function if it match the random value 
  display(curr->wrd);                            // pass the word to the display function
   return;                                       // exit the loop after finding the matching word 
}
curr=curr->next;
}

}

void display(char *str){                        // str a pointer parameter to the randomly picked word

   
    char ch;                                     
    int l=strlen(str),i=0;                      //l=length of the word  nedeed in  loops 
     char arr[10];                              //arr represent the evolution of the guessed word throughout the game

    int max_guess=6,numguess=0;
                  
    for(int j=0; j<l; j++){                        
      arr[j]='$';                                 // initialize arr with '$' 
    }
    arr[l]='\0';
while (max_guess>0){                           // while the number of guesses higher than 0 continue the game
printf("%s\n", arr);
printf("input a letter\n");
scanf(" %c", &ch);

    numguess=0;
 for (int i=0; i<l; i++){                       
  
   
   if(ch==str[i]){                            // check if  input character matches a character in the original word 
     arr[i]=ch;                               // replace the '$' with the matching character
     numguess=1;                              // change the numguess value if a character matches  
   }
   }
    
   if(numguess){                                 //if numguess is 1 correct letter
    printf("correct letter\t");
      
   }else{
    printing_the_hangman(max_guess);                                       // if numguess is 0 wrong letter
    printf("wrong letter\t");
    max_guess--;                                // decreace the number of max guess after wrong guesses
   } 

   
 if(strcmp(str,arr)==0){                                 //compare the two words if there is no difference that mean the word had been guessed
    printf("congrats you guessed\n the word was %s", str);
    return;
   }

 }  


       printf("try again you didn't guess\n the word was:%s", str);         //after consuming all possible guesses, GAME OVER
   
}




void printing_the_hangman(int ncase){                  // printing the hangman body parts based on the numbr of incorrect guesses
        

  switch (ncase)
  {
  case 6: 

printf("           ____  \n"
       "           |  |  \n"           // the head obviously :)
       "           |  0  \n"               
       "           |     \n"              
       "                 \n");


    break;


  
   case 5: 
    printf("           ____  \n"
           "           |  |  \n"           // body
           "           |  0  \n"               
           "           |  |  \n"              
           "                 \n");

    break;
     case 4: 

 printf("            ____   \n"
        "            |  |   \n"           // left arm
        "            |  0 / \n"               
        "            |  |   \n"              
        "                   \n");

    break;
  
  
     case 3: 
     
    printf("          ____     \n"
           "          |  |     \n"           // right arm
           "          |\\ 0 /  \n"               
           "          |  |     \n"              
           "                   \n");

    break;
  
       case 2: 

  printf("            ____     \n"
         "            |  |     \n"           // left leg
         "            |\\ 0 /  \n"               
         "            |  |     \n"              
         "                \\   \n");


    break;  

     case 1: 


  printf("            ____     \n"
         "            |  |     \n"           // right leg
         "            |\\ 0 /  \n"               
         "            |  |     \n"              
         "              / \\   \n");

    break;
  
  default:

    printf("Invalid number\n");
        
    break;
  }




}
