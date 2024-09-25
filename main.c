
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "nodes.h"
#include "functions.h"

#define NUM_FEATURES 6
#define PATTERN_LENGTH 50


int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
                  Any new users should be added to that linked list.
    */

    // Your solution goes here
    print_pattern(PATTERN_LENGTH, '*');
    printf("         Welcome to Text-Based Facebook");
    print_pattern(PATTERN_LENGTH, '*');
    
    int exit = 0;
    while (!exit){
        print_menu();
        unsigned short int user_inp;
        printf("\nEnter your choice: ");
	    scanf(" %hu", &user_inp);

        while (user_inp < 0 || user_inp > NUM_FEATURES){
            printf("Invalid choice. Please Try Again.\n");
            break;
        }

        switch(user_inp){
            case 1:
                char username[30];
                char password[15];
                
                printf("Enter an upto 30 characters username: ");
                scanf("%29s", username);

                printf("Enter an upto 15 characters password: ");
                scanf("%14s", password);

                users = add_user(users, username, password);

                printf("\n**** User Added! ****\n");
                  
                break;

            case 2:
                char inp_user_pass[30];
                printf("Enter a username to update their password: ");
                scanf("%29s", inp_user_pass); 

                user_t *found_user_pass = find_user(users, inp_user_pass);
                if (found_user_pass != NULL){
                    printf("Enter a new password (15 characters max): ");
                    scanf("%15s", found_user_pass->password);
                    printf("\n**** Password changed! ****\n");
                }
                break;

            case 3:
                char inp_user_posts[30];
                printf("Enter a username to manage their posts: ");
                scanf("%29s", inp_user_posts); 

                user_t *found_user_posts = find_user(users, inp_user_posts);
                while (found_user_posts != NULL){
                    
                    print_pattern(PATTERN_LENGTH, '-');
                    printf("           %s's posts", found_user_posts->username);
                    display_user_posts(found_user_posts);
                    print_pattern(PATTERN_LENGTH, '-');

                    unsigned short int post_choice;
                    printf("\n1. Add a new user post\n2. Remove a user's post\n3. Return to main menu");
                    printf("\n\nYour choice: ");
                    scanf(" %hu", &post_choice);

                    switch (post_choice) {
                        case 1:
                            char new_post_text[250];
                            printf("Enter your post content (250 characters max): ");
                            scanf(" %[^\n]s", new_post_text);
                            add_post(found_user_posts, new_post_text);
                            printf("Post added to your profile.\n");
                            break;
                            
                        case 2:
                            unsigned short int post_number;
                            printf("Which post do you want to delete? ");
                            scanf(" %hu", &post_number);
                            
                            if (delete_post(found_user_posts, post_number)) {
 
                            } else {
                                printf("Invalid post number. Try again.\n");
                            }
                            break;

                        case 3:
                            found_user_posts = NULL;

                    }                    

                }

                break;

            case 4:
                char inp_user_friends[30];
                printf("Enter a username to manage their friends: ");
                scanf("%29s", inp_user_friends); 

                user_t *found_user_friends = find_user(users, inp_user_friends);
                while (found_user_friends != NULL){
                    
                    print_pattern(PATTERN_LENGTH, '-');
                    printf("               %s's friends", found_user_friends->username);
                    print_pattern(PATTERN_LENGTH, '-');

                    unsigned short int friend_choice;
                    printf("\n1. Display all user's friends \n2. Add a new friend \n3. Delete a friend \n4. Return to main menu");
                    printf("\n\nYour choice: ");
                    scanf(" %hu", &friend_choice);    

                    switch(friend_choice){
                        case 1:
                            display_user_friends(found_user_friends);
                            break;

                        case 2:
                            char new_friend_name[30];
                            printf("Enter a new friend's name (30 characters max): ");
                            scanf(" %29s", new_friend_name);
                            add_friend(found_user_friends, new_friend_name);
                            printf("Friend added to the list.\n");   
                            break;

                        case 3:
                            display_user_friends(found_user_friends);
                            char delete_friend_name[30];
                            printf("\nEnter a friend's name to delete (30 characters max): ");
                            scanf(" %29s", &delete_friend_name);
                            
                            if (delete_friend(found_user_friends, delete_friend_name)) {
                                display_user_friends(found_user_friends);
                            } else {
                                printf("Invalid friend's name.\n");
                                display_user_friends(found_user_friends);
                            }
                            break;

                        case 4:
                            found_user_friends = NULL;

                    }
                }
            break;

            case 5:
                display_all_posts(users);
                break;

            case 6:
                print_pattern(PATTERN_LENGTH, '*');
                printf("     Thank you for using Text-Based Facebook\n");
                printf("                     Goodbye!");
                print_pattern(PATTERN_LENGTH, '*');
                teardown(users);
                exit = 1;
                
        }

    }

}
