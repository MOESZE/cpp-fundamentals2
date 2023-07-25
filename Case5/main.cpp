#include<iostream>
#include<fstream>
using namespace std;

struct node
{
   string seq;
   int freq;
   node *leftChild, *rightChild;
   node(string s, int f)
   {
       seq = s, freq = f;
       leftChild = rightChild = NULL;
   }
};

node* binaryTreeInsert(node* root, string s)
{
   if(root == NULL) // create new node
       return new node(s, 1);
  
   if(root->seq > s) // insert in left child
       root->leftChild = binaryTreeInsert(root->leftChild, s);
   else if(root->seq < s) // insert in right child
       root->rightChild = binaryTreeInsert(root->rightChild, s);
   else // root->seq == s
       root->freq ++;
  
   return root;
}

void inorderTraversal(node *root)
{
   if(!root)
       return;
   inorderTraversal(root->leftChild); // traverse left child
   cout<<root->seq<<": "<<root->freq<<endl;
   inorderTraversal(root->rightChild); // traverse right child
}

int main()
{
   char file[20];
   cout<<"Enter file name : ";
   cin>>file;
  
   // Open file
   ifstream inputFile;
   inputFile.open(file);
   if(!inputFile)
   {
       cout<<"Failed to open "<<file<<" file\n";
       return 0;
   }
  
   // Input k
   int k;
   cout<<"Enter the value of k :";
   cin>>k;
  
   // Initialize root of BST
   node* root = NULL;
   char ch;
  
   for(int freq=1; freq<=k; freq++)
   {
       string seq;
       int i = 1;
       while(i < freq)
       {
           if(inputFile>>ch)// check if EOF
           {
               if(ch>='A' && ch<='Z') // Capital letter
                   ch += 'a'-'A';
               if(ch>='a' && ch<='z') // Small letter
               {
                   seq.push_back(ch); // seq = seq+ch
                   i++;
               }
           }
           else
               break;
       }
       if(i < freq) // EOF i.e. less than freq alphabets in file
           break;
      
       while(inputFile>>ch)
       {
           if(ch>='A' && ch<='Z') // Capital letter
               ch += 'a'-'A';

           if(ch>='a' && ch<='z') // Small letter
           {
               seq.push_back(ch); // seq = seq+ch
               root = binaryTreeInsert(root, seq);
               seq.erase(seq.begin()); // remove first character of string
           }
       }
  
       inputFile.clear(); // Reset EOF flag
       inputFile.seekg(0, ios::beg); // Seek the pointer to beginning of file
   }
  
   // Do inorder traversal of BST
   inorderTraversal(root);
  
   return 0;
}