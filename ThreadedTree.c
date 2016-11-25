/*******************************************************************************************************************************************
 * Joshua Van Deren
 * General Programming
 * Program ThreadedTree v2
 *
 * Program that creates a binary search tree comprised of threads.
 * Note that there will be no indicator (or flag) for what a thread is; rather, this will be executed with recursive functions.
*/

/******************* #include DIRECTIVES **************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>  /* Used to change malloc() and free() */

/******************* Structure Declarations ***********************************************************************************************/
/*!
 * @struct       BinarySearchTreeNode
 * @abstract     Holds a key value, while pointing to it's left and right sides, in order to create a binary search tree.
 *
 * @field        left           Left side of binary search tree node.
 * @field        right          Right side of binary search tree node.
 * @field        keyValue       Character value representing a binary search tree node.
*/
typedef struct BinarySearchTreeNode {
    struct BinarySearchTreeNode *left, *right;
    char keyValue;
} BSTN;

/******************* Function Prototypes **************************************************************************************************/
BSTN* createNode(void);
void insert2BST(BSTN **ptr2Root, BSTN *newNode);

void inOrderTraversal(BSTN *currentNode, BSTN *possibleSuccessor);
void preOrderTraversal(BSTN *currentNode, BSTN *possibleSuccessor);

/******************************************************************************************************************************************/

int main(void)
/*!
 * @function     main
 * @abstract     Allows the user to both insert into the binary search tree and quit.
*/
 {
     BSTN *root = NULL;
     int done = 0;
     char userChoice;

     while (!done)
      {
          printf("Enter choice (lower case is also acceptable) --- [I]nsert or [Q]uit: ");
          scanf(" %c", &userChoice);
          while(getchar() != '\n');              /* Clears keystroke buffer. */

          switch (userChoice)
           {
               case ('I'): case ('i'):                /* Insert here. */
                   insert2BST(&root, createNode());
                   break;

               case ('Q'): case ('q'):                /* Quit here. */
                   done = 1;
                   break;

               default:
                   printf("\nIncorrect input entered\n");
                   break;
           }

          printf("\n");
      }

     return(0);
}

BSTN* createNode(void)
/*!
 * @function     insert2BST
 * @abstract     Creates a new binary search tree node.
 *
 * @result       A new binary search tree node with left and right sides pointing to NULL.
*/
 {
     BSTN *newNode = malloc(sizeof(BSTN));     /* Creates a node, whose left and right sides point to NULL. */
     newNode->left = NULL;
     newNode->right = NULL;

     return newNode;
 }

void insert2BST(BSTN **ptr2Root, BSTN *newNode)
/*!
 * @function     insert2BST
 * @abstract     Insert a node in the correct spot in a binary search tree.
 * @discussion   An ancestor will point to a possible successor for a thread to point to.
 *
 * @param        ptr2Root       A pointer of a pointer to the root of a binary search tree.
 * @param        newNode        A newly created Binary Search Tree Node.
*/
 {
     BSTN *insPtr = *ptr2Root, *ancestor = *ptr2Root;
     int searching = 1;

     printf("\nEnter new node's key value: ");
     scanf(" %c", &(newNode->keyValue));
     while(getchar() != '\n');                   /* Clears keystroke buffer. */

     if (*ptr2Root == NULL)                           /* Empty Binary Search Tree. */
         *ptr2Root = newNode;

     else                                             /* Non-empty Binary Search Tree. */
         while (searching)
          {
              if (newNode->keyValue < insPtr->keyValue)              /* Check node on the left. */
               {
                   if (insPtr->left == NULL)               /* Found a spot. Insert node on the left. */
                    {
                        insPtr->left = newNode;
                        newNode->right = insPtr;
                        searching = 0;
                    }

                   else                                    /* Didn't find a spot. Move on. */
                    {
                        ancestor = insPtr;
                        insPtr = insPtr->left;
                    }
               }

              else if (newNode->keyValue > insPtr->keyValue)         /* Check node towards the right. */
               {
                   if (insPtr->right == NULL)              /* Reached end of tree. */
                    {
                        insPtr->right = newNode;
                        searching = 0;
                    }


                   else if (insPtr->right == ancestor)     /* Found a spot. Insert node on the right. */
                    {
                        newNode->right = ancestor;
                        insPtr->right = newNode;
                        searching = 0;
                    }

                   else                                    /* Didn't find a spot. Move on. */
                       insPtr = insPtr->right;
               }

              else /* (newNode->keyValue == insPtr->keyValue) */     /* Node already exists. Nothing can be done. */
               {
                   printf("\nThat key value of %c has already been used.\n", newNode->keyValue);
                   free(newNode);
                   searching = 0;
               }
          }

     printf("\nIn-order: ");
     inOrderTraversal(*ptr2Root, NULL);     /* The root has no ancestor. Ergo, ancestor = NULL. */

     printf("\nPre-order: ");
     preOrderTraversal(*ptr2Root, NULL);

     printf("\n");
     return;
 }

void inOrderTraversal(BSTN *currentNode, BSTN *possibleSuccessor)
/*!
 * @function     inOrderTraversal
 * @abstract     Recursively in-order traverse a binary tree.
 * @discussion   An ancestor will point to a 'possible' successor for a thread to point to. Therefore, the ancestor will not always be the
 *               true successor to the current node.
 *
 * @param        currentNode    Any binary search tree node that is currently being visited.
 * @param        possibleSuccessor       A binary search tree node located above the currentNode.
*/
 {
     if (currentNode->left != NULL)                         /* Slice left from currentNode. */
         inOrderTraversal(currentNode->left, currentNode);

     printf("%c", currentNode->keyValue);                   /* Print key after slicing left. */

     if (currentNode->right != possibleSuccessor)                    /* Determine if the current node's right pointer points to it's successor. */
         inOrderTraversal(currentNode->right, possibleSuccessor);    /* If not, traverse it's right child. */

     return;                                                /* Go back up a function and start over until traversal is complete. */
 }

void preOrderTraversal(BSTN *currentNode, BSTN *possibleSuccessor)
/*!
 * @function     preOrderTraversal
 * @abstract     Recursively pre-order traverse a binary tree.
 * @discussion   An ancestor will point to a 'possible' successor for a thread to point to. Therefore, the ancestor will not always be the
 *               true successor to the current node.
 *
 * @param        currentNode    Any binary search tree node that is currently being visited.
 * @param        possibleSuccessor       A binary search tree node located above the currentNode.
*/
 {
     printf("%c", currentNode->keyValue);                   /* Print key before slicing left. */

     if (currentNode->left != NULL)                         /* Slice left from currentNode. */
         preOrderTraversal(currentNode->left, currentNode);

     if (currentNode->right != possibleSuccessor)                    /* Determine if the current node's right pointer points to it's successor. */
         preOrderTraversal(currentNode->right, possibleSuccessor);   /* If not, traverse it's right child. */

     return;                                                /* Go back up a function and start over until traversal is complete. */
 }
