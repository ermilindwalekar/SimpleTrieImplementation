#include <iostream>
#include <map>

using namespace std;

//Supporting only lower or upper case
struct TrieNode{
    bool isEndOfWord;
    TrieNode* children[26];

    /*
        map<char, TrieNode> children;

    */
};

TrieNode* getNode(){
    TrieNode* temp = new TrieNode();
    temp->isEndOfWord = false;
    for(int i = 0; i< 26; i++){
        temp->children[i] = NULL;
    }
    return temp;
}

//a->0 b->1 c->2 ... z->25
void insertWord(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
bool searchWord(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

bool isEmpty(TrieNode* root){
    if(root == NULL)
        return false;

    for(int i = 0; i< 26; ++i){
        if(root->children[i])
            return false;
    }
    return true;
}
TrieNode* removeWord(TrieNode* root, string key, int idx = 0){
    //Empty Tree
    if(root == NULL)
        return NULL;

    int index = key[idx] - 'a';
    root->children[index] = removeWord(root->children[index], key, idx + 1);

    //Check if something is last character of  the string!!
    if(idx == key.length()){
        if(root->isEndOfWord){
            root->isEndOfWord = false;
        }
        //Check if any other word is attached to this
        if(isEmpty(root)){
            delete(root);
            root = NULL;
        }
    }
    if(isEmpty(root) && root->isEndOfWord == false){
        delete(root);
        root = NULL;
    }

    return root;
}

int main()
{
    string keys[] = {"hello", "world", "how", "are", "you"};
    int length = 5;

    //Construct a trie;
    TrieNode* root = getNode();

    for(int i = 0; i<length; i++){
        insertWord(root, keys[i]);
    }

    searchWord(root, "you")? cout << "Yes\n" :
                           cout << "No\n";

    removeWord(root, "you");

    searchWord(root, "you")? cout << "Yes\n" :
                           cout << "No\n";

    return 0;
}
