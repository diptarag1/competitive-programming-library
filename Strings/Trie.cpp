const int MAXC = 2;

struct TrieNode 
{ 
    struct TrieNode *children[MAXC]; 
    bool isEndOfWord; 
    int size;
}; 

struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode =  new TrieNode; 
    pNode->isEndOfWord = false; 
    for (int i = 0; i < MAXC; i++) pNode->children[i] = NULL; 
    pNode->size = 0;
    return pNode; 
} 

void insert(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - '0'; 
        if (pCrawl->children[index] == NULL) { pCrawl->children[index] = getNode(); }
        pCrawl = pCrawl->children[index]; 
        pCrawl->size++;
    } 
    pCrawl->isEndOfWord = true; 
} 