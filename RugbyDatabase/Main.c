#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "Main.h"
#include "Menu.h"
#include "Player.h"
#include "PlayerList.h"
#include "PlayerListUtil.h"


void main() {

	int choice;
	int irfu;
	player_t* newPlayer;
	player_t* list = NULL;
	
	printf("\nWelcome to the Rugby Player Database!");

	//verify user
	while (!displayStartMenu());
	
	//get existing records from file
	populateList(&list);

	//display user menu
	choice = displayMainMenu();

	while (choice != 9) {

		switch (choice)
		{
		case 1:
			newPlayer = createPlayer(list);
			insertSorted(&list, newPlayer);
			break;
		case 2:
			displayPlayers(list, stdout);
			printf("\n");
			break;
		case 3:
			displayDetails(list);
			break;
		case 4:
			updatePlayer(&list);
			break;
		case 5:			
			deletePlayer(&list);
			break;
		case 6:
			generateStats(list, stdout);
			break;
		case 7:
			printReportToFile(list);
			break;
		case 8:
			displayInOrder(list);
			break;
		default:
			break;
		}
		choice = displayMainMenu();
	};

	//print linked list to file
	printListToFile(list);

	//free dynamically allocated memory
	freeLinkedList(list);

	printf("Goodbye!");

	_getch();
}


//function to write the players database to file
void printListToFile(player_t* head) {

	//temporary head node copy
	player_t* tmp = head;

	//attempt to open database file
	FILE* out = fopen("Rugby.txt", "w");

	//if file is open write every record in the list to the file
	if (out != NULL) {
		while (tmp != NULL) {
			fprintf(out, "%d ", tmp->irfu);
			fprintf(out, "%s ", tmp->firstName);
			fprintf(out, "%s ", tmp->lastName);
			fprintf(out, "%d ", tmp->age);
			fprintf(out, "%f ", tmp->height);
			fprintf(out, "%f ", tmp->weight);
			fprintf(out, "%s ", tmp->club);
			fprintf(out, "%s ", tmp->email);
			fprintf(out, "%d ", tmp->position + 1);
			fprintf(out, "%d ", tmp->tackles + 1);
			fprintf(out, "%d ", tmp->metres + 1);
			fprintf(out, "\n");
			tmp = tmp->next;
		}
		//close the file
		fclose(out);
	}
	else {
		//file couldn't be opened
		printf("Couldn't write to file");
		return;
	}
}

//function that prints all players information as well as the statistics to the file 'StatsReport.txt'
void printReportToFile(player_t* head) {

	FILE* report = fopen("StatsReport.txt", "w");

	if (report != NULL) {

		//print the players' details to the report file
		fprintf(report, "\nRugby Players Database: ");
		displayPlayers(head, report);

		//print the statistics to the file
		fprintf(report, "\n\nRugby Player Statistics Report");
		generateStats(head, report);

		printf("\nPrinted database and report to the file \"StatsReport.txt\" \n");

		fclose(report);
	}
	else {
		printf("\nCouldn't save report to file");
	}
}