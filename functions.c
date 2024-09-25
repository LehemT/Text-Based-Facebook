
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "nodes.h"
#include "functions.h"

#define NUM_FEATURES 6
#define PATTERN_LENGTH 50

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   // create a new user node
   user_t *new_user = malloc(sizeof(user_t));
   assert(new_user != NULL);
   new_user->posts = NULL;
   new_user->friends = NULL;
   strcpy(new_user->username, username);
   strcpy(new_user->password, password);
   new_user->next = NULL;

   // if the linked list is empty or the new user should be added at the beginning
   if (users == NULL || strcmp(username, users->username) < 0){
      new_user->next = users;
      return new_user;
   }

   // traverse the list to find the correct position for the new user (ascending order)
   user_t *current = users;
   while (current->next != NULL && strcmp(username, current->next->username) >= 0){
      current = current->next;
   }

   // add new user in the middle or at the end
   new_user->next = current->next;
   current->next = new_user;
   
   return users;
}


/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username) 
{
   user_t *current = users;
   while (current != NULL)
   {
      if (strcmp(current->username, username) == 0)
      {
         // user found
         return current;
      }
      current = current->next;
   }
   // user not found
   print_pattern(PATTERN_LENGTH, '-');
   printf("                 User not found.");
   print_pattern(PATTERN_LENGTH, '-');
   return NULL;

}


/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *new_friend = malloc(sizeof(post_t));
   assert(new_friend != NULL);
   strcpy(new_friend->username, username);
   new_friend->next = NULL;
   return new_friend;
}


/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *new_friend = create_friend(friend);

   if (user->friends == NULL || strcmp(friend, user->friends->username) < 0) {
      new_friend->next = user->friends;
      user->friends = new_friend;
   } else {
      friend_t *current = user->friends;
      while (current->next != NULL && strcmp(friend, current->next->username) > 0) {
         current = current->next;
      }

      new_friend->next = current->next;
      current->next = new_friend;
   }
}


/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   friend_t *current = user->friends;
   friend_t *previous = NULL;

   // traverse the linked list to find the friend to delete
   while (current != NULL && strcmp(current->username, friend_name) != 0) {
      previous = current;
      current = current->next;
   }

   // friend found
   if (current != NULL) {
      if (previous != NULL) {
         previous->next = current->next;
      } else {
         user->friends = current->next;
      }

      // free the memory of the deleted friend
      free(current);
      return 1; // true, friend deleted
   }

   return 0; // false, friend not found
}


/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *new_post = malloc(sizeof(post_t));
   assert(new_post != NULL);
   strcpy(new_post->content, text);
   new_post->next = NULL;
   return new_post; 
}


/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   post_t *new_post = create_post(text);
   new_post->next = user->posts;
   user->posts =  new_post;
}


/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   post_t *current = user->posts;
   post_t *previous = NULL;
   int current_position = 1;

   while (current != NULL && current_position != number){
      previous = current;
      current = current->next;
      current_position++;
   }

   if (current != NULL) {
      // post found
      if (previous != NULL) {
         previous->next = current->next;
      } else {
         user->posts = current->next;
      }

      // free the memory of the deleted post
      free(current);
      printf("Post %d was deleted successfully!", number);
      return 1; // true, post deleted
   }
   return 0; // false, post not found
}


/*
   Function that displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   // check if the user has any posts
   post_t* current = user->posts;
   if (current == NULL) {
      printf("\nNo posts available for %s.", user->username);
      return;
   }

   // iterate through the linked list and print each post
   for (int i = 1; current != NULL; current = current->next, i++) {
      printf("\n%d- %s: %s", i, user->username, current->content);
   }  
   
}


/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   // check if the user has any friends
   friend_t* current = user->friends;
   printf("\nList of %s's friends:\n", user->username);

   if (current == NULL) {
      printf("No friends available for %s.\n", user->username);
      return;
   }

   // iterate through the linked list and print each friend
   for (int i = 1; current != NULL; current = current->next, i++) {
      printf("%d- %s\n", i, current->username);
   }  

}


/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   user_t *current = users;

   while (current != NULL) {
      
      // display posts of the current user
      display_user_posts(current);

      // move to the next user
      current = current->next;

      if (current != NULL) {
         // display posts of the next user
         display_user_posts(current);

         char choice;
         printf("\n\nDo you want to display next 2 users posts? (Y/N): ");
         scanf(" %c", &choice);

         if (choice == 'n' || choice == 'N') {
            return;
         }

         // move to the next user
         current = current->next;
      }
   }   
}


/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   user_t *current = users;
   while (current != NULL) {
      user_t *next_user = current->next;

      // free friends linked list memory
      friend_t *current_friend = current->friends;
      while (current_friend != NULL) {        
         friend_t *next_friend = current_friend->next;
         free(current_friend);
         current_friend = next_friend;
      }

      // free posts linked list memory
      post_t *current_post = current->posts;
      while (current_post != NULL) {         
         post_t *next_post = current_post->next;
         free(current_post);
         current_post = next_post;
      }
      
      free(current);  // free current user's memory
      current = next_user;  // move to the next user
   }    
}


/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   char* app_features[NUM_FEATURES] = {
        "1. Register a new user",
        "2. Manage a user's profile (change password)",
        "3. Manage a user's posts (display/add/remove)",
        "4. Manage a user's friends (display/add/remove)",
        "5. Display all posts",
        "6. Exit"
    };
   
   print_pattern(PATTERN_LENGTH, '*');
   printf("                   MAIN MENU:");
   print_pattern(PATTERN_LENGTH, '*');
   
   for (int i = 0; i < NUM_FEATURES; i++){
      printf("%s",app_features[i]);
      printf("\n");
   }


}


// prints a pattern of chosen length and character
void print_pattern(unsigned int length, char character){
   printf("\n");
   for(int i = 0; i < length; i++){
      printf("%c", character);
   }
   printf("\n");
}


/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
 