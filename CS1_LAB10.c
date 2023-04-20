// The following program utilizes a trie to organize a list of data.
// ----------------------------------------------------------------------------------------------------
// A trie (pronounced try) is a tree-based abstract data type.
// Each node in a trie tpyically has two main values.
// One is something to signify if the given node is the last letter of a word.
// In this case, that value belongs to endsWord, where it is true (1) if it completes a word.
// The other is a pointer to possible branches, which in this case represents possible letters.

// For example, if the word "the" is inserted into the trie, e.endsWord == 1 as it ends the word.
// If the word "themes" was then added to the trie, s.endsWord == 1 as well.
// Keep in mind, however, that e.endsWord will still remain 1.

// Now, when searching to see if "the" is a word, the trie will recognize that that "e" is the end
// of one word, but it also has branches, indicating it is a part of a bigger word as well.
// This logic is essential when writing a function that deletes certain words from a trie.

// So, if one wanted to delete "the" from the trie, all that would need to happen 
// is to set e.endsWord = 0, and it would no longer be seen as the end of a word.
// ----------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Trie{
    int endsWord;
    struct Trie *children[26];
};

struct Trie* init() {
    // Create the struct, not a word.
    struct Trie* myTree = malloc(sizeof(struct Trie));
    myTree->endsWord = 0;
    // Set each pointer to NULL.
    int i;
    for (i=0; i<26; i++)
        myTree->children[i] = NULL;
    // Return a pointer to the new root.
    return myTree;
}

void insert(struct Trie **ppTrie, char *word)
{
    int wordLen = strlen(word);
    if (wordLen == 0) 
    {
        ppTrie[0]->endsWord = 1;
        return;
    }

    struct Trie* tracker = *ppTrie;

    for (int i = 0; i < wordLen; i++)
    {
        int index = word[0] - 'a';
        if (tracker->children[index] == NULL)
        {
            tracker->children[index] = init();
        }
        tracker = tracker->children[index];
    }

    tracker->endsWord = 1;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int wordLen = strlen(word);
    struct Trie* tracker = pTrie;
    int index = word[0] - 'a';

    for (int i = 0; i < wordLen; i++)
    {
        int index = word[0] - 'a';
        tracker = tracker->children[index];
    }
    
    return tracker->endsWord;
}

// Frees all memory allocated by the trie
struct Trie *deallocateTree(struct Trie *pTrie)
{
    for (int i=0; i<26; i++)
    {
        if (pTrie->children[i] != NULL)
            deallocateTree(pTrie->children[i]);        
    }
    free(pTrie);
    pTrie = NULL;
    return pTrie;
}

int main(void)
{
    // Create the struct
    struct Trie* myTrie = init();
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg", "joey"};
    
    for (int i=0; i<5; i++)
    {
        insert(&myTrie, pWords[i]);
    }    

    // Read the number of the words in the dictionary
    // Parse line  by line, and insert each word to the trie data structure
    for (int i=0; i<5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(myTrie, pWords[i]));
    }
    myTrie = deallocateTree(myTrie);
    if (myTrie != NULL)
       printf("There is an error in this program\n");
    return 0;
}