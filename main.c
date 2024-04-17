/*********************************************************************************************************
This is to certify that this project is our own work, based on our personal
efforts in studying and applying the concepts learned. We have constructed the
functions and their respective algorithms and corresponding code by ourselves. The
program was run, tested, and debugged by our own efforts. We further certify that
we have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons.

Nicole Jocson & Joaquin Panganiban
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_LETTERS 20
#define MAX_PAIRS_PER_ENTRY 10
#define MAX_ENTRIES 150

/* typedef Declarations */
typedef char String20[MAX_LETTERS + 1];

struct entryTag {
	String20 strLanguage[MAX_PAIRS_PER_ENTRY + 1];		// Language string of pair
	String20 strTranslation[MAX_PAIRS_PER_ENTRY + 1];	// Translation string of pair
	int nPairsInEntry;									// Nunmber of pairs in entry
};

/* Variable Declarations */
void sort 					(struct entryTag List[], int nEntries);
void displayPairsInEntry 	(struct entryTag List[], int nEntry);
void displayAllEntries 		(struct entryTag List[], int * nEntries);
void addEntry 				(struct entryTag List[], int * nEntries);
void addTranslation 		(struct entryTag List[], int * nEntries);
void deleteEntry 			(struct entryTag List[], int * nEntries);
void deleteTranslation 		(struct entryTag List[], int * nEntries);
void searchWord 			(struct entryTag List[], int * nEntries);
void searchTranslation 		(struct entryTag List[], int * nEntries);
void translate 				(struct entryTag List[], int * nEntries);
void exportTranslations 	(struct entryTag List[], int * nEntries);
void importTranslations 	(struct entryTag List[], int * nEntries);

int
main ()
{
	/* Variable Declarations */
	FILE *loop_fp;
    String20 Lang, Trans;
    char strWord[100];
    char strFileName[30];
    char delimiter[] = {':', ' ', '\n'};
    char* token;
	
	// Precondition: User inputs are non-negative integers
	int nMainMenu;
	int nManageDataMenu;
	int nTranslateMenu;
	
	int nEntriesInitialized = 0;
	int nTerminate = 1;
    int nCount;
    int nPair;
    int tempPair;
	int	newLine;
	
	struct entryTag List[MAX_ENTRIES];
	
	// Program will continue until the user chooses to Exit Main Menu
	do
	{
		// Display Main Menu
		printf ("MAIN MENU\n");
		printf ("===========================\n");
		printf ("[1] Manage Data Menu\n");
		printf ("[2] Translate Menu\n");
		printf ("[3] Exit Main Menu\n");
		// Where to proceed from Main Menu
		printf ("Proceed: ");
		scanf ("%d", &nMainMenu);
		printf ("\n");
		
		// Check for invalid input
		while (1 > nMainMenu || nMainMenu > 3)
		{
			printf ("Invalid input! Please try again: ");
			scanf ("%d", &nMainMenu);
			printf ("\n");
		}
		
		switch (nMainMenu)
		{
			/* Manage Data Menu */
			case 1:
				do {
					// Display Manage Data Menu
					printf ("MANAGE DATA MENU\n");
					printf ("===========================\n");
					printf ("[1] Add entry\n");
					printf ("[2] Add translation\n");
					printf ("[3] Delete entry\n");
					printf ("[4] Delete translation\n");
					printf ("[5] Display all entries\n");
					printf ("[6] Search word\n");
					printf ("[7] Search translation\n");
					printf ("[8] Export\n");
					printf ("[9] Import\n");
					printf ("[10] Exit\n");
					// Where to proceed from Manage Data Menu
					printf ("Proceed: ");
					scanf ("%d", &nManageDataMenu);
					printf ("\n");
					
					// Invalid input
					while (1 > nManageDataMenu || nManageDataMenu > 10)
					{
						printf ("Invalid option! Please try again: ");
						scanf ("%d", &nManageDataMenu);
						printf ("\n");
					}
					
					// Manage Data Menu Features
					switch (nManageDataMenu)
					{
						// Add Entry
						case 1:
							addEntry (List, &nEntriesInitialized);
							break;
						// Add Translation
						case 2:
							addTranslation (List, &nEntriesInitialized);
							break;
						// Delete Entry
						case 3:
							deleteEntry (List, &nEntriesInitialized);
							break;
						// Delete Translation
						case 4:
							deleteTranslation (List, &nEntriesInitialized);
							break;
						// Display All Entries
						case 5:
							displayAllEntries (List, &nEntriesInitialized);
							break;
						// Search Word
						case 6:
							searchWord (List, &nEntriesInitialized);
							break;
						// Search Translation
						case 7:
							searchTranslation (List, &nEntriesInitialized);
							break;
						// Export
						case 8:
							exportTranslations (List, &nEntriesInitialized);
							break;
						// Import
						case 9:
							importTranslations (List, &nEntriesInitialized);
							break;
					}
					if (nManageDataMenu < 10)
						printf ("Returning to Manage Data Menu...\n\n");
				} while (nManageDataMenu < 10);
				printf ("Returning to Main Menu...\n\n");
				break;
			/* Translate Menu */
			case 2:
				// Pre-condition: The user does not indend to add more than 150 entries
				// Pre-condition: User's filename is 30 characters
				printf ("Enter file name: ");
				scanf ("%s", strFileName);
				printf ("\n");
				
				// Non-existing file 
				if ((loop_fp = fopen (strFileName, "r")) == NULL)
				    printf("File does not exist.\n");
				else
				{
					
					loop_fp = fopen (strFileName, "r");
							
					while (!feof(loop_fp))
					{
						tempPair = 0;
						newLine = 0;
						nPair = 0;
								
						while (newLine == 0)
						{
							fgets (strWord, 1024, loop_fp);
									
							if (strcmp(strWord, "\n") == 0 || feof(loop_fp))
								newLine = 1;
							else
								tempPair++;
				
							nCount = 0;
							token = strtok(strWord, delimiter);	
									
							while (token != NULL)
							{
								nCount++;
										
								if (nCount == 1)
									strcpy(Lang, token);
								else if (nCount == 2)
									strcpy(Trans, token);
											
								token = strtok (NULL, delimiter);
							}
										
							if (nPair < tempPair)
							{
								// Copy the values onto the structure
								strcpy (List[nEntriesInitialized].strLanguage[nPair], Lang);
								strcpy (List[nEntriesInitialized].strTranslation[nPair], Trans);
								List[nEntriesInitialized].nPairsInEntry++;
								nPair++;		
							}
						}	
							nEntriesInitialized++;
					}
						fclose (loop_fp);
						
					do
					{
						// Display Translate Menu
						printf ("TRANSLATE MENU\n");
			 			printf ("=================\n");
						printf ("[1] Translate\n");
						printf ("[2] Exit\n");
						// Where to proceed from Translate Menu
						printf ("Proceed: ");
						scanf ("%d", &nTranslateMenu);
						printf ("\n");
						
						// Check for invalid input
						while (1 > nTranslateMenu || nTranslateMenu > 2)
						{	
							printf ("Invalid option! Please try again: ");
							scanf ("%d", &nTranslateMenu);
							printf ("\n");
						}
							
						// Translate Menu Features
						if (nTranslateMenu == 1 && (loop_fp = fopen (strFileName, "r")) != NULL)
						{
							translate (List, &nEntriesInitialized);
							printf ("Returning to Translate Menu...\n\n");
						}
					} while (nTranslateMenu == 1);	
				}
				printf ("Returning to Main Menu...\n\n");
				break;
			/* Exit Main Menu/Terminate Program */
			case 3:
				nTerminate = 0;
				break;
		}
	} while (nTerminate == 1);
	
	return 0;
}

/*
    sort arranges List[] by ASCII value
	@param List[] - struct[] of entries
	@param nEntries - number of entries initalized by the user
*/
void
sort (struct entryTag List[],
	  int nEntries)
{
    String20 strTemp;
    int nTemp;
    int nEntryPairs;
    int min;
    int nPair;
    int i, j;
    
	for (i = 0; i < nEntries; i++)
	{
		min = i;	// Current smallest element
		
        for (j = i + 1; j < nEntries; j++)
        {
            if (strcmp (List[min].strLanguage[0], List[j].strLanguage[0]) > 0)
                min = j;
        }
        
        nPair = 0;
        
        // Get greater number of pairs between two entries that are swapping
        if (List[i].nPairsInEntry > List[min].nPairsInEntry)
        	nEntryPairs = List[i].nPairsInEntry;
        else
        	nEntryPairs = List[min].nPairsInEntry;
        
        // Swap pairs between entries
        while (nPair < nEntryPairs)
        {
        	// Swap language string
        	strcpy (strTemp, 						List[i].strLanguage[nPair]);
	        strcpy (List[i].strLanguage[nPair], 	List[min].strLanguage[nPair]);
	        strcpy (List[min].strLanguage[nPair], 	strTemp);
	        
	        // Swap translation string
	        strcpy (strTemp, 							List[i].strTranslation[nPair]);
	        strcpy (List[i].strTranslation[nPair], 		List[min].strTranslation[nPair]);
	        strcpy (List[min].strTranslation[nPair], 	strTemp);
	    	
	        nPair++;	// Next pair
		}
		
		// Swap number of pairs in entry
	    nTemp 					= List[i].nPairsInEntry;
	    List[i].nPairsInEntry 	= List[min].nPairsInEntry;
	    List[min].nPairsInEntry = nTemp;
	}
}

/*
	displayPairsInEntry displays all pairs of an entry List[nEntry]
	@param List[] - an entry containing language-translation pairs
	@param nEntry - index of entry to display pairs
*/
void
displayPairsInEntry (struct entryTag List[], int nEntry)
{
	int nPair = 0;
	int nLangLen, nTransLen;
	int i;
	
	// Print initialized pairs in entry
	while (nPair < List[nEntry].nPairsInEntry)
	{
		// Print entry
		if (nPair == 0)
			printf ("     ");
		// Print pair number
		else
		{
			printf ("| %d ", nPair);
			if (nPair < 10)
				printf (" ");
		}
		
		// Print language
		printf ("| %s", List[nEntry].strLanguage[nPair]);
		nLangLen = strlen(List[nEntry].strLanguage[nPair]);
		
		if (nLangLen < MAX_LETTERS + 1)
		{
			for (i = 0; i < MAX_LETTERS + 1 - nLangLen; i++)
				printf (" ");
		}
		
		// Print translation
		printf ("| %s", List[nEntry].strTranslation[nPair]);
		nTransLen = strlen(List[nEntry].strTranslation[nPair]);
		
		if (nTransLen < MAX_LETTERS + 1)
		{
			for (i = 0; i < MAX_LETTERS + 1 - nTransLen; i++)
				printf (" ");
			printf ("|\n");
		}
		nPair++;
	}
}

/*
	displayAllEntries displays each entry and all its information one by one
	@param List[] - struct[] of entries
	@param nEntries - number of entries initalized by the user
*/
void
displayAllEntries (struct entryTag List[],
				   int * nEntries)
{
	char cPage = 'A';						// User input where to proceed next
	int nEntryIndex = 0;					// Equivalent to the page number - 1
	
	// Sort entries
	sort (List, *nEntries);
	
	while (nEntryIndex < *nEntries &&		// Program does not go past last initalized entry
		   (cPage != 'X' && cPage != 'x'))	// User does not prompt to exit feature
	{
		// Display entry
		printf ("ENTRY %d\n", nEntryIndex + 1);
		printf ("====================================================\n");
		displayPairsInEntry (List, nEntryIndex);
		printf ("\n");
			
		// Ask user where to proceed next
		if (nEntryIndex > 0)
			printf ("[P] Previous Entry\n");
		if (nEntryIndex < *nEntries - 1)
			printf ("[N] Next Entry\n");
		printf ("[X] Exit\n");
		printf ("Proceed: ");
		scanf (" %c", &cPage);
		printf ("\n");
		
		// Check for invalid input
		while ((cPage != 'P' && cPage != 'p' &&
			    cPage != 'N' && cPage != 'n' &&
			    cPage != 'X' && cPage != 'x') ||
			   (nEntryIndex == 0 && (cPage == 'P' || cPage == 'p')) ||
			   (nEntryIndex == *nEntries - 1 && (cPage == 'N' || cPage == 'n')))
		{
			printf ("Invalid input! Please try again: ");
			scanf (" %c", &cPage);
			printf ("\n");
		}
		
		// Modify nEntryIndex or page number
		if (cPage == 'P' || cPage == 'p')
			nEntryIndex--;
		else if (cPage == 'N' || cPage == 'n')
			nEntryIndex++;
	}
    
    // No entries initalized
    if (*nEntries == 0)
    	printf ("No entries initalized.\n");	
}

/*
	addEntry allows the user to add a new valid entry
	@param List[] - struct[] of entries
	@param nEntries - number of entries initalized by the user
	Pre-condition: User's inputs contain no typographical error
    			   cNewEntry is a character of the alphabet
*/
void
addEntry (struct entryTag List[],
		  int * nEntries)
{
	String20 strAddLang = "", strAddTrans = "";	// User input
	char cNewEntry;								// Used when the user wants to duplicate an entry
	int nExistingEntry;         				// Used to check if the user input is an existing entry
	int nEntryIndex;
	int nEntry;
	
	do
	{
		// Ask user for entry
		printf ("Input <language> <translation> pair: ");
		scanf ("%20s %20s", strAddLang, strAddTrans);
		printf ("\n");
		
		// Check if there are already maximum entries
 		if (*nEntries == MAX_ENTRIES)
			printf ("Maximum entries reached!\n");
 		else
		{
			// Check if user's input has at least one character
			if (strlen(strAddLang) > 0 && strlen(strAddTrans) > 0)
			{
				nExistingEntry = 0;
				nEntry = 0;
				
				// Check for existing entry
				while (nEntry < *nEntries)
				{
					if (strcmp(strAddLang, List[nEntry].strLanguage[0]) == 0 && 
						strcmp(strAddTrans, List[nEntry].strTranslation[0]) == 0)
					{
						nExistingEntry = 1;
						nEntryIndex = nEntry;
					}
					nEntry++;
				}
				
				// Input is an existing entry
				if (nExistingEntry == 1)
				{
					// Display all information of input
					printf ("ENTRY INFORMATION\n");
					printf ("====================================================\n");
					displayPairsInEntry (List, nEntryIndex);
					printf ("\n");
					
					do
					{
						printf ("%s %s is an existing entry. Create a new entry? ", strAddLang, strAddTrans);
						printf ("[Y]es or [N]o: ");
						scanf (" %c", &cNewEntry);
						printf ("\n");
						
						// Invalid input
						if (cNewEntry != 'Y' && cNewEntry != 'y' &&
							cNewEntry != 'N' && cNewEntry != 'n')
						{
							printf ("Invalid input! Please try again.\n");
							scanf (" %c", &cNewEntry);
						}
					} while (cNewEntry != 'Y' && cNewEntry != 'y' &&
							 cNewEntry != 'N' && cNewEntry != 'n');
				}
                    
				// Create new entry	if
				if (nExistingEntry == 0 ||					// (1) the input does not exist or
                    cNewEntry == 'Y' || cNewEntry == 'y')	// (2) input is an existing entry, but the user wants to create a new entry
				{
					// Create new entry
					strcpy (List[*nEntries].strLanguage[0], strAddLang);
					strcpy (List[*nEntries].strTranslation[0], strAddTrans);
					
					// Add to initalized entires and pairs count
					*nEntries += 1;
					List[nEntry].nPairsInEntry = 1;
					printf ("Entry added!\n");
					
					// Ask user: encode another entry
					do {
						printf ("Encode new entry?\n");
						printf ("[Y]es or [N]o: ");
						scanf (" %c", &cNewEntry);
						printf ("\n");
						
						// Invalid input
						if (cNewEntry != 'Y' && cNewEntry != 'y' &&
							cNewEntry != 'N' && cNewEntry != 'n')
							printf ("Invalid input!\n\n");
						
					} while (cNewEntry != 'Y' && cNewEntry != 'y' &&
							 cNewEntry != 'N' && cNewEntry != 'n');
				}
			} else
				printf ("Invalid input! Input must at least be one character.\n");
		}  
	} while (cNewEntry == 'Y' || cNewEntry == 'y');
}

/*
	addTranslation allows the user to input up to 10 language-translation pairs under one entry
	@param List[] - struct[] of entries
    @param nEntries - number of entries initalized by the user
	Pre-condition: User's inputs contain no typographical error
*/
void
addTranslation (struct entryTag List[],
				int * nEntries)
{
	String20 strEntryLang = "", strEntryTrans = "";	// Language-translation pair of entry to modify
	String20 strAddLang = "", strAddTrans = "";		// Language-translation pair of translation to add
	char cMoreTrans = 'Y';							// User input to add more translations under same entry
	int nEntryIndex[] = {0};						// Store the index of existing entries in case of multiple existing entries
	int nStore = 0;
	int nExistingCount = 0;							// Count existing entries
	int nMultiEntries;								// User input for which entry to add translation to
	int nEntry = 0;
	int i;
	
	// Ask user which entry to modify
	printf ("Under which entry would you like to input a translation to? ");
	scanf ("%20s %20s", strEntryLang, strEntryTrans);
	printf ("\n");
	
	// Check if user's input has at least one character
	if (strlen(strEntryLang) > 0 && strlen(strEntryTrans) > 0)
	{
		// (1) Check how many existing entries there are and 
		// (2) which index of List[] those entries are
		while (nEntry < *nEntries)
		{
			// Check for existing entry
			if (strcmp(strEntryLang, List[nEntry].strLanguage[0]) == 0 &&
				strcmp(strEntryTrans, List[nEntry].strTranslation[0]) == 0)
			{
				nExistingCount++;				// Count exsiting entries
				nEntryIndex[nStore] = nEntry;	// Note index of existing entries
				nStore++;
			}
			nEntry++;
		}
		
		// There is an existing entry
		if (nExistingCount > 0)
		{
			// One existing entry
			if (nExistingCount == 1)
			{
				while (cMoreTrans == 'Y' || cMoreTrans == 'y')
				{
					// Display all info of existing entry
					printf ("ENTRY INFORMATION\n");
					printf ("====================================================\n");
					displayPairsInEntry (List, nEntryIndex[0]);
					printf ("\n");
					
					// Check if the entry already has 10 translations
					if (List[nEntryIndex[0]].nPairsInEntry == MAX_PAIRS_PER_ENTRY + 1)
					{
						printf ("Maximum translations reached for entry %s %s!\n", strEntryLang, strEntryTrans);
						cMoreTrans = 'N';
					}
					else
					{
						// Ask user for language-translation pair
						printf ("Input <language> <translation> pair: ");
						scanf ("%20s %20s", strAddLang, strAddTrans);
						printf ("\n");
						
						// Add translation to entry
						strcpy (List[nEntryIndex[0]].strLanguage[List[nEntryIndex[0]].nPairsInEntry], strAddLang);
						strcpy (List[nEntryIndex[0]].strTranslation[List[nEntryIndex[0]].nPairsInEntry], strAddTrans);
						List[nEntryIndex[0]].nPairsInEntry++;
						printf ("Translation added to entry %s %s!\n\n", strEntryLang, strEntryTrans);
					}
					
					// Ask user for continuation
					if (cMoreTrans == 'Y' || cMoreTrans == 'y')
					{
						printf ("Would you like to input more translations to entry %s %s?\n", strEntryLang, strEntryTrans);
						printf ("[Y]es or [N]o: ");
						scanf (" %c", &cMoreTrans);
						printf ("\n");
					}
						                    
					// Check for invalid input
					while (cMoreTrans != 'Y' && cMoreTrans != 'y' &&
						   cMoreTrans != 'N' && cMoreTrans != 'n')
					{
						printf ("Invalid input! Please try again: ");
						scanf (" %c", &cMoreTrans);
						printf ("\n");
					}
				}
			// More than one existing entries
			} else 
			{
				i = 0;
				// Display all info of existing entries
				while (i < nExistingCount)
				{
					printf ("ENTRY %d\n", i + 1);
					printf ("====================================================\n");
					displayPairsInEntry (List, nEntryIndex[i]);
					printf ("\n");
					i++;
				}
				
				// Ask user which entry to add translation to
				printf ("There are %d existing entries.\n", nExistingCount);
				printf ("Which entry would you like to add a translation to? ");
				scanf ("%d", &nMultiEntries);
				printf ("\n");
				    
				// Check for invalid input
				while (1 > nMultiEntries || nMultiEntries > nExistingCount)
				{
					printf ("Invalid entry! Please try again: ");
					scanf ("%d", &nMultiEntries);
					printf ("\n");
				}
				
				nMultiEntries--;
				
				// While user wants to add translations
				while (cMoreTrans == 'Y' || cMoreTrans == 'y')
				{
					// Check if the entry already has 10 translations
					if (List[nEntryIndex[nMultiEntries]].nPairsInEntry == MAX_PAIRS_PER_ENTRY + 1)
					{
						printf ("Maximum translations reached for entry %s %s!\n", strEntryLang, strEntryTrans);
						cMoreTrans = 'N';
					}
					else
					{
						// Display entry information
						printf ("ENTRY %d\n", nMultiEntries + 1);
						printf ("====================================================\n");
						displayPairsInEntry (List, nEntryIndex[nMultiEntries]);
						printf ("\n");
						
						// Ask user for language-translation pair
						printf ("Input <language> <translation> pair: ");
						scanf ("%20s %20s", strAddLang, strAddTrans);
						printf ("\n");
						        
						// Add translation to entry
						strcpy (List[nEntryIndex[nMultiEntries]].strLanguage[List[nEntryIndex[nMultiEntries]].nPairsInEntry],
								strAddLang);
						strcpy (List[nEntryIndex[nMultiEntries]].strTranslation[List[nEntryIndex[nMultiEntries]].nPairsInEntry],
								strAddTrans);	
						List[nEntryIndex[nMultiEntries]].nPairsInEntry++;
						printf ("Translation added to entry %s %s!\n\n", strEntryLang, strEntryTrans);
						
						// Ask user for continuation
						if (cMoreTrans == 'Y' || cMoreTrans == 'y')
						{
							printf ("Would you like to input more translations to entry %s %s?\n", strEntryLang, strEntryTrans);
							printf ("[Y]es or [N]o: ");
							scanf (" %c", &cMoreTrans);
							printf ("\n");
						}
						
						// Check for invalid input
						while (cMoreTrans != 'Y' && cMoreTrans != 'y' &&
							   cMoreTrans != 'N' && cMoreTrans != 'n')
						{
							printf ("Invalid input! Please try again: ");
							scanf (" %c", &cMoreTrans);
							printf ("\n");
						}
					}
				}
			}
		// Non-existing entry
		} else
		{
			printf ("%s %s is not an entry.\n", strEntryLang, strEntryTrans);
			printf ("Please use the Add Entry feature first.\n");
		}
	// Invalid entry
	} else
		printf ("Invalid input! Input must at least be one character.\n");
}

/*
	deleteEntry allows the user to delete an entry and all its information
	@param List[] - struct[] of entries
    @param nEntries - number of entries initalized by the user
	Pre-condition: nDelete is a non-negative integer
*/
void
deleteEntry (struct entryTag List[],
			 int * nEntries)
{
	int nDelete;
	int i, j;
	
	// Display all entries and their information
	displayAllEntries (List, nEntries);
	
	// One or more initalized entries
	if (*nEntries > 0)
	{
		printf ("Number of entry to delete: ");
		scanf ("%d", &nDelete);
		printf ("\n");
		
		// Invalid entry
		if (1 > nDelete || nDelete > *nEntries)
			printf ("Invalid entry! There are %d initialized entries.\n", *nEntries);
		// Valid entry
		else
		{
			// Delete the entry and move the entries following it
			for (i = nDelete - 1; i < *nEntries; i++)
			{
				for (j = 0; j < MAX_PAIRS_PER_ENTRY + 1; j++)
				{
					strcpy (List[i].strLanguage[j], List[i + 1].strLanguage[j]);
					strcpy (List[i].strTranslation[j], List[i + 1].strTranslation[j]);
				}
				List[i].nPairsInEntry = List[i + 1].nPairsInEntry;
			}
			*nEntries -= 1;
			printf ("Entry deleted!\n");
		}
	// No initalized entries
	} else
		printf ("Please use the Add Entry feature first.\n");
}

/*
	deleteTranslation allows the user to delete a translation under an entry
	@param List[] - struct[] of entries
    @param nEntries - number of entries initalized by the user
	Pre-condition: The entry to modify has language-translation pairs initialized
				   nEntry and nDelete are non-negative integers
				   cContDel is a letter of the alphabet
*/
void
deleteTranslation (struct entryTag List[],
				   int * nEntries)
{
	String20 strDelLang, strDelTrans;
	char cContDel = 'Y';
	int nDelete, nEntry, nPair;
	int nDelEntry = 0;
	int i, j;
	
	// Display all entries and their information
	displayAllEntries (List, nEntries);
	
	// One or more initalized entries
	if (*nEntries > 0)
	{
		printf ("Number of entry to modify: ");
		scanf ("%d", &nEntry);
		printf ("\n");
		
		// Invalid entry
		if (1 > nEntry || nEntry > *nEntries)
			printf ("Invalid entry! There are only %d entries.\n", *nEntries);
		// Valid entry
		else
		{
			nEntry--;
			while (nDelEntry == 0 &&
				   (cContDel == 'Y' || cContDel == 'y'))
			{
				// Display entry information
				printf ("ENTRY INFORMATION\n");
				printf ("====================================================\n");
				displayPairsInEntry (List, nEntry);
				printf ("\n");
				
				// Ask user which translation to delete
				printf ("Number of language-translation pair to delete: ");
				scanf ("%d", &nDelete);
				printf ("\n");
				
				// Check for invalid translation
				if (1 > nDelete || nDelete > List[nEntry].nPairsInEntry - 1)
				{
					printf ("Invalid option!\n");
					printf ("Would you like to proceed to delete a translation?\n");
					printf ("[Y]es or [N]o: ");
					scanf (" %c", &cContDel);
					printf ("\n");
					
				// Valid translation input
				} else
				{
					// Note string of language-translation pair to delete
					strcpy (strDelLang, List[nEntry].strLanguage[nDelete]);
					strcpy (strDelTrans, List[nEntry].strTranslation[nDelete]);
					
					// Delete translation and move the following translations
					for (nPair = nDelete; nPair < List[nEntry].nPairsInEntry; nPair++)
					{
						strcpy (List[nEntry].strLanguage[nPair], List[nEntry].strLanguage[nPair + 1]);
						strcpy (List[nEntry].strTranslation[nPair], List[nEntry].strTranslation[nPair + 1]);
					}
					
					// Modify pairs count in entry
					List[nEntry].nPairsInEntry--;
					printf ("Language-translation pair deleted!\n");
					
					// Check if user is deleting the only translation in the entry
					if (List[nEntry].nPairsInEntry == 1)
					{
						// Delete the entry and move the entries following it
						for (i = nEntry; i < *nEntries; i++)
						{
							for (j = 0; j < MAX_PAIRS_PER_ENTRY + 1; j++)
							{
								strcpy (List[i].strLanguage[j], List[i + 1].strLanguage[j]);
								strcpy (List[i].strTranslation[j], List[i + 1].strTranslation[j]);
							}
							List[i].nPairsInEntry = List[i + 1].nPairsInEntry;
						}
						*nEntries -= 1;
						nDelEntry = 1;
						printf ("%s %s is the only pair in the entry. Entry deleted.\n", strDelLang,
																						 strDelTrans);
					}
					
					// Ask user for continuation if entry is not deleted
					if (nDelEntry == 0)
					{
						printf ("Delete another translation in this entry?\n");
						printf ("[Y]es or [N]o? ");
						scanf (" %c", &cContDel);
					}
				}
			}
		}
	// No initialized entries
	} else
		printf ("Please use the Add Entry feature first.\n");
}

/*
	searchWord displays all entries with the string the user inputs
	@param List[] - struct[] of entries
	@param nEntries - entries initialized by the user
	Pre-condition: User's inputs contain no typographical error
*/
void
searchWord (struct entryTag List[],
			int * nEntries)
{
	String20 strSearch;
	char cPage = 'A';
	int nEntryIndex[] = {0};	// Store the index of existing entries
	int nStore = 0;
	int nEntry = 0, nPair;
	
	printf ("Search word: ");
	scanf ("%20s", strSearch);
	printf ("\n");
	
	// Look for entries with instances strSearch
	while (nEntry < *nEntries)
	{
		for (nPair = 0; nPair < List[nEntry].nPairsInEntry; nPair++)
		{
			if (strcmp(strSearch, List[nEntry].strTranslation[nPair]) == 0)
			{
				nEntryIndex[nStore] = nEntry;
				nStore++;
				nPair = List[nEntry].nPairsInEntry;
			}
		}
		nEntry++;
	}
	
	if (nStore == 0)
		printf ("Word not found.\n");
	else
	{
		nEntry = 0;
		
		while (cPage != 'X' && cPage != 'x')	// User does not prompt to exit feature
		{
			sort (List, *nEntries);
			// Display entry
			printf ("ENTRY %d\n", nEntry + 1);
			printf ("====================================================\n");
			displayPairsInEntry (List, nEntryIndex[nEntry]);
			printf ("\n");
				
			// Ask user where to proceed next
			if (nEntry > 0)
				printf ("[P] Previous Entry\n");
			if (nEntry < nStore - 1)
				printf ("[N] Next Entry\n");
				
			printf ("[X] Exit\n");
			printf ("Proceed: ");
			scanf (" %c", &cPage);
			printf ("\n");
			
			// Check for invalid input
			while ((cPage != 'P' && cPage != 'p' &&
				    cPage != 'N' && cPage != 'n' &&
				    cPage != 'X' && cPage != 'x' ) ||
				   (nEntry == 0 && (cPage == 'P' || cPage == 'p')) ||
				   (nEntry == nStore - 1 && (cPage == 'N' || cPage == 'n')))
			{
				printf ("Invalid input! Please try again: ");
				scanf (" %c", &cPage);
				printf ("\n");
			}
			
			if (cPage == 'P' || cPage == 'p')
				nEntry--;
			else if (cPage == 'N' || cPage == 'n')
				nEntry++;
		}
	}
}

/*
	sortTranslation allows the user to search for a language-translation pair
	@param List[] - struct[] of entries
	@param nEntries - number of entries initalized by the user
    Pre-condition: User's inputs contain no typographical error
*/
void
searchTranslation (struct entryTag List[],
				   int * nEntries)
{
	String20 strLang, strWord; 
	char cPage;
	int nEntry = 0, nPair = 0;
	int nEntryIndex[] = {0};	// Store the index of existing entries
	int nStore = 0;
	
	printf("Search <language> <translation>: "); 		
	scanf("%20s %20s", strLang, strWord);
	
	// Look for entries with instances of user input
	while (nEntry < *nEntries)
	{
		for (nPair = 0; nPair < List[nEntry].nPairsInEntry; nPair++)
		{
			if (strcmp(strLang, List[nEntry].strLanguage[nPair]) == 0 && 
				strcmp(strWord, List[nEntry].strTranslation[nPair]) == 0)
			{
				nEntryIndex[nStore] = nEntry;
				nStore++;
				nPair = List[nEntry].nPairsInEntry;
			}
		}
		nEntry++;
	}
	
	if (nStore == 0)
		printf ("Word not found.\n");
	else
	{
		nEntry = 0;
		
		while (cPage != 'X' && cPage != 'x')	// User does not prompt to exit feature
		{
			sort (List, *nEntries);
			// Display entry
			printf ("ENTRY %d\n", nEntry + 1);
			printf ("====================================================\n");
			displayPairsInEntry (List, nEntryIndex[nEntry]);
			printf ("\n");
				
			// Ask user where to proceed next
			if (nEntry > 0)
				printf ("[P] Previous Entry\n");
			if (nEntry < nStore - 1)
				printf ("[N] Next Entry\n");
				
			printf ("[X] Exit\n");
			printf ("Proceed: ");
			scanf (" %c", &cPage);
			printf ("\n");
			
			// Check for invalid input
			while ((cPage != 'P' && cPage != 'p' &&
				    cPage != 'N' && cPage != 'n' &&
				    cPage != 'X' && cPage != 'x' ) ||
				   (nEntry == 0 && (cPage == 'P' || cPage == 'p')) ||
				   (nEntry == nStore - 1 && (cPage == 'N' || cPage == 'n')))
			{
				printf ("Invalid input! Please try again: ");
				scanf (" %c", &cPage);
				printf ("\n");
			}
			
			if (cPage == 'P' || cPage == 'p')
				nEntry--;
			else if (cPage == 'N' || cPage == 'n')
				nEntry++;
		}
	}
}

/*
	translate allows the user to translate a sentence containing a word to translate from one language to another
	@param List[] - struct[] of entries
	@param nEntries - number of entries initalized by the user
    Pre-condition: User's inputs contain no typographical error
    			   User inputs valid entries and translations
    			   The user has entries and pairs initialized
*/
void
translate (struct entryTag List[], int * nEntries)
{
	String20 strSourceLang, strLang;
	char strTranslate[151], strTranslate2[151];
	char translateTokens[151][151];
	char delimiter[] = {'.', '?', '!', ':', ';',
                      '-', '(', ')', '[', ']',
                      ',', '"', '/', ' '};
    char* token;
	char cNewText = 'A';
	int nEntryIndex, nPairIndex, nTransIndex;
	int nEntry = 0, nPair = 0;
	int token_num = 0;
	int i;
    
    printf ("What language is your text? ");
    scanf ("%20s", strSourceLang);
    
 	getchar();										//removes newline for strTranslate
 	
  	printf ("Please input text to be translated: ");	
	scanf ("%[^\n]s", strTranslate);				//take input until newline is encountered
	strcpy(strTranslate2, strTranslate);			//save sentence for output
	
    printf ("What language would you like to translate this to? ");
    scanf ("%20s", strLang);
    printf ("\n");
    
    token = strtok(strTranslate, delimiter);
	while (token != NULL)
	{
		strcpy(translateTokens[token_num], token);
		token_num++;
		token = strtok(NULL, delimiter);
	}
	
    // Look for index of entry of source language
	while (nEntry < *nEntries)
	{
		// Matching source language and entry
		if (strcmp(strSourceLang, List[nEntry].strLanguage[0]) == 0)
		{
			nEntryIndex = nEntry;	// Note index of entry
			
			// Look for index of translation of langauge to translate text to
			while (nPair < List[nEntry].nPairsInEntry)
			{
				if (strcmp(strLang, List[nEntry].strLanguage[nPair]) == 0)
					nPairIndex = nPair;	// Note index of translated text
				nPair++;
			}
		}
		nEntry++;
	}
	
	nEntry = 0;
	nPair = 0;
	
	// Loop all the words in the input sentence
	for(i = 0; i < token_num; i++)
	{
		// Look for a valid translation in the input sentence
		while (nPair < List[nEntryIndex].nPairsInEntry)
		{
			if (strcmp(translateTokens[i], List[nEntryIndex].strLanguage[nPair]) == 0)
				nTransIndex = nPair;				// Note index of the valid translation
			
			nPair++;
		}
	
		if (strcmp(List[nEntryIndex].strTranslation[nTransIndex], translateTokens[i]) == 0)
			strcpy(translateTokens[i], List[nEntryIndex].strTranslation[nPairIndex]);
	}
	
    while (cNewText != 'N' && cNewText != 'n')
	{
		// Print output
		printf ("Translated input: %s\n", strTranslate2);
		printf ("Translated output: ");
		for (i = 0; i < token_num; i++)
			printf ("%s ", translateTokens[i]);
		printf ("\n\n");
	    
	    printf ("Translate another text from %s to %s?\n", strSourceLang, strLang);
	    printf ("[Y]es or [N]o: ");
		scanf (" %c", &cNewText);
		printf ("\n");
		
		// Check for invalid input
		while (cNewText != 'Y' && cNewText != 'y' &&
			   cNewText != 'N' && cNewText != 'n')
		{
		    printf ("Invalid option! Please try again: ");
		    scanf (" %c", &cNewText);
		}
	}	
}

/*
	exportTranslations allows the user to export the entries and translations to a .txt file
	@param List[] - struct[] of entries
	@param nEntries - number of entries initalized by the user
    Pre-condition: User's inputs contain no typographical error
*/
void
exportTranslations (struct entryTag List[],
					int * nEntries)
{
    FILE *loop_fp;
    char strFileName[30];
    int nEntry, nPair;
    
    printf ("What would you like to name the file? ");
    scanf ("%30s", strFileName);

    // Non-existing file
    if ((loop_fp = fopen (strFileName, "r")) == NULL)
    {
    	loop_fp = fopen (strFileName, "w");
    	
    	// Access entries
		for (nEntry = 0; nEntry < *nEntries; nEntry++)
	    {
	    	// Access pairs
	    	for (nPair = 0; nPair <= List[nEntry].nPairsInEntry; nPair++)
	    	{
		    	fprintf (loop_fp, "%s", List[nEntry].strLanguage[nPair]);
		    	if (strcmp(List[nEntry].strLanguage[nPair], "\0") != 0)
		    		fprintf (loop_fp, ": ");
		        fprintf (loop_fp, "%s\n", List[nEntry].strTranslation[nPair]);
			}
	    }
	// Existing file
	} else
	{
		// Overwrite info in file
		loop_fp = fopen (strFileName, "w+");
		
		// Access entries
		for (nEntry = 0; nEntry < *nEntries; nEntry++)
	    {
	    	// Access pairs
	    	for (nPair = 0; nPair <= List[nEntry].nPairsInEntry; nPair++)
	    	{
		    	fprintf (loop_fp, "%s", List[nEntry].strLanguage[nPair]);
		    	if (strcmp(List[nEntry].strLanguage[nPair], "\0") != 0)
		    		fprintf (loop_fp, ": ");
		        fprintf (loop_fp, "%s\n", List[nEntry].strTranslation[nPair]);
			}
		}
	}
    fclose (loop_fp);
}
/*
    importTranslation imports entries and translations from a .txt file
	@param List[] - struct[] of entries
	@param nEntries - number of entries initalized by the user
	Pre-condition: User's contain no typographical error / is a letter of the alphabet (for char)
				   User creates less than or equal to 150 entries
				   User does not create an entry in the .txt file with more than 10 language-transation pairs
				   File follows format
*/
void
importTranslations (struct entryTag List[],
					int * nEntries)
{
    FILE *loop_fp;
    String20 Lang, Trans;
    char strWord[100];
    char strFileName[30];
    char delimiter[] = {':', ' ', '\n'};
    char* token;
    char cExist;
    int nCount;
    int newLine;
	int tempPair;
    int nPair;

    printf ("Enter file name: ");
    scanf ("%30s", strFileName);
    
	loop_fp = fopen (strFileName, "r");
	
	// Non-existing file 
	if ((loop_fp = fopen (strFileName, "r")) == NULL)
    	printf("File does not exist.\n");
	else
	{
		// Loop while it's not the end of file
	    while (!feof(loop_fp))
		{
			tempPair = 0;
			newLine = 0;
			nPair = 0;
			
			// Prints each 1 entry at a time
			while (newLine == 0)
			{
				fgets (strWord, 1024, loop_fp);
				
				if (strcmp(strWord, "\n") == 0 || feof(loop_fp))
					newLine = 1;
				else
				{
					printf ("%s", strWord);
					tempPair++;
				}
				
				// Separates the 2 strings (language and translation) in each line
				nCount = 0;
				token = strtok(strWord, delimiter);
				
				while (token != NULL)
				{
					nCount++;
					
					if (nCount == 1)
						strcpy(Lang, token);
					else if (nCount == 2)
						strcpy(Trans, token);
						
					token = strtok (NULL, delimiter);
				}
				
				// Copy the values onto the structure
				if (nPair < tempPair)
				{
					strcpy (List[*nEntries].strLanguage[nPair], Lang);
					strcpy (List[*nEntries].strTranslation[nPair], Trans);
					List[*nEntries].nPairsInEntry++;
					nPair++;
				}
			}
			
			// Asks if they want to add the entry
			do
			{
				printf("Add this entry to import [Y]es [N]o? ");
				scanf(" %c", &cExist);
				printf ("\n");
				
				if (cExist != 'Y' && cExist != 'y' &&
				    cExist != 'N' && cExist != 'n')
					printf ("Invalid input!\n");
					
			} while (cExist != 'Y' && cExist != 'y' &&
					 cExist != 'N' && cExist != 'n');
			
			if (cExist == 'Y' || cExist == 'y')					// User chooses to add entry
			{	
				*nEntries += 1;
				printf ("Added Entry!\n\n");
			} else if (cExist == 'N' || cExist == 'n')			// User chooses to not add
			{
				while (nPair > 0)
				{
					List[*nEntries].nPairsInEntry--;
					nPair--;
				}
				printf("Entry skipped!\n\n");
			}
		}
	}
	fclose (loop_fp);
}
