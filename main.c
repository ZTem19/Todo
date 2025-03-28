#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

enum Column {
	TITLE = 1,
	DESCRIPTION = 2, 
};

//Prints all the rows returned from the database after a command is run on it 
int printRows(void *notused, int argc, char **argv, char **columnName);

//Update an exsisting record in the table
int updateRecord(int id, int col, char* newValue );

//Parse input string and remove any special characters like !@#$%^&*()...
int escapeString(char *ogStr, char *newStr);

//Exec different commands on the database
int execDB(char* sqlCommand);

int getInStr(char *buff);

const char *databasePath = "./todo.db";

int main(int argc, char **argv)
{
	printf("This is your todo list. Make sure to work on your goals!\n");
	execDB("select * from todo;");

	int shouldQuit = 0;
	char inputRaw[20];
	char filteredInput[20];
	while (!shouldQuit)
	{
		printf(">>>");
		fgets(inputRaw, sizeof(inputRaw), stdin);

		escapeString(inputRaw, filteredInput);

		switch (filteredInput[0]) {
		case 'a':
			
			break;
		
		default:
			break;
		}



		if(filteredInput[0] == 'q'){
			shouldQuit = 1;
		}
	}
	

	return 0;
}

int execDB(char* sqlCommand){
	sqlite3 *db;
	char *errorMsg;
	int rc;

	rc = sqlite3_open(databasePath, &db);
	if (rc)
	{
		printf("%s %s\n", "Unable to open database at path: ", databasePath);
		return -1;
	}
	rc = sqlite3_exec(db, sqlCommand, printRows, 0, &errorMsg);
	if (rc)
	{
		printf("Sql error: %s\n", sqlite3_errmsg(db));
		return -2;
	}
	sqlite3_close(db);
	return 0;
}

int updateRecord(int id, int col, char* newValue ){
	char *column;
	switch(col){
		case TITLE:
			column = "TITLE";
			break;

		case DESCRIPTION:
			column = "DESCRIPTION";
			break;

		default:
			printf("Bad Value for column to be updated!");
			return -1;
	}

	char* sqlInput;
	sprintf(sqlInput, "UPDATE todo SET %s = '%s' WHERE id = %d", column, newValue, id);
}

int printRows(void *notused, int argc, char **argv, char **columnName)
{
	for (int i = 0; i < argc; i++)
	{
		printf("| %s = %s ", columnName[i], argv[i]);
	}
	printf("|\n");
	return 0;
}

int escapeString(char *ogStr, char *newStr){
	int length = strlen(ogStr);
	if (sizeof(ogStr) < sizeof(newStr)){
		printf("Error in escapeString, new string buffer in shorter than original string");
		return 1;
	}

	memset(newStr, 0, sizeof(newStr));

	int indexCounter = 0;
	for(int i = 0; i < length; i++){
		int value = (int) ogStr[i];
		// Omit character if it is not a-z A-Z 0-9
		if( (value <= 'Z' && value >= 'A') || (value <= 'z' && value >= 'a') || (value == ' ') || (value >= '0' && value <= '9')){
			newStr[indexCounter++] = ogStr[i];
		}
	}

	return 0;
}
