#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
	int flag;
	struct Trie *children[26]; 
} Trie;

void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);

void insert(struct Trie **ppTrie, char *word) {
	if (*ppTrie == NULL) return;
	
	int len = strlen(word);
	int index;
	
	Trie *temp = *ppTrie;
	for (int i = 0; i < len; i++) {
		index = word[i] - 'a';
		if (temp->children[index] == NULL)
			temp->children[index] =	 calloc(1, sizeof(Trie));
		temp = temp->children[index];
	}
	temp->flag++;
}	

int numberOfOccurances(struct Trie *pTrie, char *word) {
	if (pTrie == NULL) return 0;
	
	int len = strlen(word);
	int index;
	
	for (int i = 0; i < len; i++) {
		index = word[i] - 'a'; // ex. 'b' - 'a' = 98 - 97 = 1
		if (pTrie->children[index] == NULL) return 0;
		pTrie = pTrie->children[index];
	}
	
	return pTrie->flag;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
	if (pTrie == NULL) return NULL; // its already NULL, run!
	
	Trie *temp = pTrie;
	for (int i = 0; i < 26; i++)
		if (pTrie->children[i] != NULL)
			deallocateTrie(pTrie->children[i]);
		
	free(pTrie);
	return NULL;
}

int main(void)
{
	// read the number of the words in the dictionary
	// parse line by line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	
	Trie *trie = calloc(1, sizeof(Trie));
	
	for (int i=0;i<5;i++) 
	{
		insert(&trie, pWords[i]);
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
	}
	trie = deallocateTrie(trie);
	if (trie != NULL)
		printf("There is an error in this program\n");
	return 0;
}