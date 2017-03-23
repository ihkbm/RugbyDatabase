#pragma once

#include "Player.h"

//function prototypes for the list of players
void displayPlayers(player_t*);
void displayDetails(player_t*);
void updatePlayer(player_t*);
void deletePlayer(player_t**, int);
void generateStats(player_t*);

void populateList(player_t** head);
void addFirst(player_t**, player_t*);
void insertSorted(player_t**, player_t*);

int size(head);

int searchByIrfu(player_t*, int);
int searchByName(player_t*, char*, char*);

//TODO
void deleteFirst(player_t**);