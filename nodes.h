/**
 * @file nodes.h
 * @author Lehem Temesgen
 * @version 12/01/2023
 * @brief A text-based simulation of basic Facebook functionalities.
 * 
 * This header file defines the data structures that the functions in 
 * the program use. These structs are used to organize and store information 
 * related to the users' profiles, their posts, and their friends.
 */

#ifndef __A2_NODES_H__
#define __A2_NODES_H__

// Structure to represent a linked list of users
typedef struct user
{
    char username[30];
    char password[15];
    struct friend *friends;
    struct post *posts;
    struct user *next;
} user_t;

// Structure to represent linked list of a user's friends
typedef struct friend
{
    char username[30];
    struct friend *next;
} friend_t;

// Structure to represent linked list of a user's posts
typedef struct post
{
    char content[250];
    struct post *next;
} post_t;


#endif