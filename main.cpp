#include <iostream>
#include <cstring>
using namespace std;

class SuffixTreeNode
{
public:
    //array of pointers with size = 27 to store alph [a,b,c,...] + $
    SuffixTreeNode **childs;

    //start index in original string
    int startingIndex;

    //start index for each suffix (in leaf only)
    int startSuffix;

    // treeNode constructor
    SuffixTreeNode()
    {
    //declare and initialize the array (dynamic allocation)
    childs = new SuffixTreeNode*[27];
    for(int i=0; i<27; i++)
    {
    childs[i] = new SuffixTreeNode[0];
    }

    for(int i=0; i<27; i++)
    {
    childs[i] = 0;
    }

    // initialize the starting variables with -1
    startingIndex = -1;
    startSuffix = -1;
    }


};
class SuffixTree
{
private:
    // character array that carry my arrival string
    char *myString;

    // the root of the tree
    SuffixTreeNode *root;

    // the size of my string to easily use it without repeat strlen(myString)
    int sizee;

public:

    //for number of nodes , being public for trase and debug
    int numberOfNodes;

    // the constructor of the suffixTree that take a string as an input
    SuffixTree(char *myString)
    {

    // put the passing string in my variable
    this->myString = myString;
    sizee = strlen(myString);

    // we always start suffix tree with a root node that is must be not a 'null'
    root = new SuffixTreeNode();

    // tree always start with 0 nodes (root not included) ==> used for trase and debug
    numberOfNodes = 0;

    // a temp root which will point to the root and use it to add any new nodes and traverse on my tree without
    // change our original root
    SuffixTreeNode *tempRoot = 0;

    // each node has an array the index of that array will points to other nodes depend on what character will be on the edge
    // [0,1,2,3,.......,27]      0 -> 'a' if exist , 1 -> 'b' if exist and so on
    // it will be calculated later
    int alphapaticIndex = -1;

    // we will make suffix trei then compress it to make suffix tree

    // a 2 loops to traverse in my string and start to construct my suffixes and put them in the suffix trei
    for(int i=0; i<sizee; i++)
    {
    // each new insert should start from the root
    tempRoot = root;

    // lets construct our suffixes [banana$] => [banana$,anana$,nana$,ana$,na$,a$,$]
    // use '$' to make each suffix id end in leaf
    for(int j=i; j<sizee; j++)
    {
    // if 'j' not point to end of the string in each suffix [point to $ ]
    if(j != sizee-1)
    alphapaticIndex = myString[j]-'a';   // calculate the index that will point to the next child [to know what char is it exactly
    else
    alphapaticIndex = 26;    // if 'j' point to '$' make tha last index of the array point to it

    // if the index that should point to the first char in this suffix is empty
    // soo the new suffix has not a prefix of another suffix
    if(tempRoot->childs[alphapaticIndex] == 0)
    {
    // make a new node
    SuffixTreeNode *newNode = new SuffixTreeNode();

    // save the index of the first character of that suffix [in original string] to use it latter in compress
    newNode->startingIndex = j;

    // make the right index points to that node
    tempRoot->childs[alphapaticIndex]= newNode;

    // increase number of nodes by one
    numberOfNodes++;

    // if the char is '$' so it is the end of the suffix and it
    // will contain 'startSuffix = index of original string in which the suffix start from'
    if(alphapaticIndex == 26)
    tempRoot->childs[alphapaticIndex]->startSuffix = i;
    }

    tempRoot = tempRoot->childs[alphapaticIndex]; // if the new suffix has a prefix of another added suffix so
          // traverse until the end of the prefix and added the new chars after it
    }

    }

    // compress the suffix trei to get a suffix tree
    //compress2(root);
    }
    // function to print the indexes that a specific string start from it (search for subString)
    void print(SuffixTreeNode *root)
    {
    // if the passing root is save (avoid other developers mistakes)
    if(root != 0)
    // for the end char in subString until the end of all sub trees under its node
    for(int i=0; i<27; i++)
    {
    // check if the index points to other node or not
    if(root->childs[i] != 0)
    {
    //check if that node is a leaf
    if(root->childs[i]->startSuffix != -1)
    {
    // if it is a leaf node take  the id and go back
    cout<<root->childs[i]->startSuffix<<" ";
    }
    // recursive call to traverse on the all nodes in sub trees under my subString that i searched for
    print(root->childs[i]);
    }
    }
    return;

    }

    // function search that take subString and return all the start index of it in my original string
    void search(char *StringToSearch)
    {
    // character variable that store the character the index of the array point to
    char ch;

    // a temp root to traverse on my tree and find the fist occurance of this substring
    SuffixTreeNode *temproot = root;

    // move in the sub string and take char by char to compare it by the characters in the tree
    for(int i=0; i<strlen(StringToSearch); i++)
    {
    // traverse on each array in  node that has a edge with this character points to it
    for(int j=0; j<27; j++)
    {

    // check the index of the array that points to other nodes (starting from root)
    if(temproot->childs[j] != 0)
    {
    // know what the char that index points to
    ch = j+'a';

    //compare that char with char in the substring
    if(StringToSearch[i] == ch)
    {
    // if the same compare the next char by keep movement on the path on the tree
    temproot = temproot->childs[j];
    break;
    }
    }
    }
    }
    // pass the last node we reach and go to print the id's
    print(temproot);
    }

    // function to compress the suffix trei and get the suffix tree
    void compress2(SuffixTreeNode *root)
    {
    // counter to check the number of childerns for current  node
    int cnt = 0;

    // a temp node to use it in add the child node to the parent and make them as one node (if its the only child for its parent)
    SuffixTreeNode *tempNode = 0;

    // a loop to count the childerns
    for(int i=0; i<27; i++)
    {
    if(root->childs[i] != 0)
    {
    cnt++;
    }
    }


    // if leaf return and do nothing
    if(root->startSuffix != -1 )
    {
    return;
    }

    else
    {
    // traverse on the array for the current node
    for(int i=0; i<27; i++)
    {
    // get the child of that node
    if(root->childs[i] != 0)
    {
    // recursive call for my function to keep traverse on all the tree
    compress2(root->childs[i]);

    // if the node has one child
    if(cnt == 1 )
    {
    // replace the array of the parent by the array of the child to keep all the nodes under this child attached to parent
    tempNode = root->childs[i];
    tempNode->childs[i] = root->childs[i];
    root->childs = tempNode->childs;

    // keep also the id's from child to parent to prevent lossing the information in which this suffix end
    root->startSuffix = tempNode->startSuffix;

    // delete the child
    delete root->childs[i];
    }


    }
    }

    }

    }
};


int main()
{

    SuffixTree t0("bananabanaba$");
    t0.search("ana");
    cout<<endl;
    SuffixTree t1("banana$");
    t1.search("an");
    cout<<endl;
    SuffixTree t2("pappat$");
    t2.search("pat");
    cout<<endl;
    SuffixTree t3("abchhhca$");
    t3.search("ca");
    cout<<endl;
    SuffixTree t4("apple$");
    t4.search("pp");
    cout<<endl;
    SuffixTree t5("ghggdfe$");
    t5.search("g");
    cout<<endl;
    SuffixTree t6("woordd$");
    t6.search("oo");
    cout<<endl;
    SuffixTree t7("tesst$");
    t7.search("s");
    cout<<endl;
    SuffixTree t8("suffixx$");
    t8.search("ix");
    cout<<endl;
    SuffixTree t9("congratulations$");
    t9.search("gra");
    cout<<endl;
    SuffixTree t10("pollssp$");
    t10.search("p");
    cout<<endl;
    SuffixTree t11("armihigharmibeyarmishayarmicrayverybeastfeastcrest$");
    t11.search("armi");
    t11.search("y");
    cout<<endl;

}
