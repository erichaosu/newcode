#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <math.h>
#include<climits>
using namespace std;

typedef enum {
	pfib =1,
	pstrstr =2,
	prearrangestr = 3,
	pbuildtree=4,
	psubsetoffib=5,
	pstr2tree=6,
	pmaxsumofedges=7
}problem;

class Node {
  public:
    int value;
    Node* prev;
    Node* next;

    Node(int value){
        this->value = value ;
        this->prev = NULL;
        this->next = NULL;
    }
};

// Feel free to add new properties and methods to the class.
class DoublyLinkedList {
  public:
    Node* head;
    Node* tail;

    DoublyLinkedList() {
      head = NULL;
      tail = NULL;
    }

	  void insertBefore(Node* node, Node* nodeToInsert) {
      // Write your code here.
			//remove(nodeToInsert);
			if (node == head){
				nodeToInsert->next = head;
				head->prev = nodeToInsert;
				head = nodeToInsert;
			}
			else if (node == tail){
				tail->prev->next = nodeToInsert;
				nodeToInsert->prev = tail->prev;
			}
			else {
				node->prev->next = nodeToInsert;
				nodeToInsert->prev = node->prev;
				nodeToInsert->next = node;
				node->prev = nodeToInsert;
			}
    }

    void setHead(Node* node) {
      // Write your code here.
			if(head == NULL){
				head = node;
				tail = node;
				return;
			}
			insertBefore(head,node);
			
    }
#if 1
    void setTail(Node* node) {
      // Write your code here.
			if (tail == NULL){
				setHead(node);
				return;
			}
			insertAfter(tail,node);
    }


    void insertAfter(Node* node, Node* nodeToInsert) {
      // Write your code here.
			if ((nodeToInsert == head) && (nodeToInsert == tail)) return;
			remove(nodeToInsert);
			nodeToInsert->prev = node;
			nodeToInsert->next = node->next;
			if (node  == tail){
				tail = nodeToInsert;
			}else {
				node->next->prev = nodeToInsert;
			}
			node->next = nodeToInsert;
    }

    void insertAtPosition(int position, Node* nodeToInsert) {
      // Write your code here.
			if (position == 1) {
				setHead(nodeToInsert);
			}
			int currentPosition = 1;
			Node* node = head;
			while ((node != NULL) && (currentPosition != position)){
				node = node->next;
				currentPosition++;
			}
			if (node == NULL){
				setTail(node);
			}
			else {
				insertBefore(node, nodeToInsert);
			}
			
    }

    void removeNodesWithValue(int value) {
      // Write your code here.
			Node* node = head;
			while ((node != NULL) && (node->value != value)){
				node = node->next;
			}
			if (node != NULL){
				remove(node);
			}
			
    }

    void remove(Node* node) {
      // Write your code here.
			if (node == head) {
				head = head->next;
			}
			else if (node == tail) {
				tail = tail->prev;
			}
			if (node->prev != NULL) {
                node->prev->next = node->next;
            }
			if (node->next != NULL) {
                node->next->prev = node->prev;
            }
			node->prev = NULL;
			node->next = NULL;
    }

    bool containsNodeWithValue(int value) {
      // Write your code here.
			Node* node = head;
			while (node != NULL){
				if (node->value == value) return true;
				node = node->next;
			}
			return false;
    }
#endif	
};
int fib(int n, unordered_map<int,int> cache)
{
	if (cache.find(n) != cache.end()){
		return cache[n];
	}
	cache[n] = fib(n-1, cache) + fib(n-2, cache);
	return cache[n];
}
//find a subset with all fib numbers 
vector<int> findsubset(int arr[], int size)
{
	vector<int> result ={};
	vector<int> fibNum={};
	int maxEle = *max_element(arr, arr+size);
	int n = 2;
	unordered_map<int,int> cache = {{0,0},{1,1},{2,1}};
	fibNum.push_back(0);
	fibNum.push_back(1);
	do {
		n++;
		fibNum.push_back(fib(n, cache));
	}while(fibNum[n-1] <= maxEle);
	//find common set of fibNum and arr
	for(int i = 0; i < size; i++){
		for(int j =0; j<fibNum.size(); j++){
			if (arr[i] == fibNum[j]){
				result.push_back(fibNum[j]);
				break;
			}
		}
	}
	return result;	
}
struct elem{
	int data;
	elem* left;
	elem* right;
};

elem* buildtree(elem* root, int arr[])
{
	if (!root) return NULL;
	elem* cur = new elem();
	cur->data = arr[1];
	if (arr[2] == 'l'-'a') root->left = cur;
	else if (arr[2] == 'r'-'a') root->right = cur;
}
elem* findelem(elem* root, int t)
{
	elem* cur = root;
	elem* result;
	if (cur ==NULL) return NULL;
	if (cur->data == t) {
		return cur;
	}
	result = findelem(cur->left,t); 
	if (result) return result;
	result = findelem(cur->right,t); 
	if (result) return result; 
}
//facebook 1
struct node{
	char data;
	node* left;
	node* right;
};
void printtree(node* t)
{
	//preorder
	if (!t) return;
	if (t->left) printtree(t->left);
	
	cout<<t->data<<" ";
	
	if (t->right) printtree(t->right);
}
template <class T>
void outtree(T* t, int space)
{
	if (!t) return;
	space +=10;
	if (t->right){
		outtree(t->right, space);
	}
	cout<<setw(space)<<t->data<<endl;
	if(t->left){
		outtree(t->left, space);
	}
}

node* convertExpressionHelp(string str, int& idx)
{
	node* cur = new node();
	cur->data = str[idx];
	if (idx == str.length()-1){
		return cur;
	}
	idx ++;
	if (str[idx] == '?'){
		idx++;
		cur->left = convertExpressionHelp(str, idx);
	
		idx++;
		cur->right = convertExpressionHelp(str, idx);
		return cur;
	}		
	
	return cur;
}
node* convertExpression(string str, int i)
{
	return convertExpressionHelp(str, i);
}
void insertnode(node* parent, char t[])
{
	node* cur = new node();
	cur->data = t[1];
	if (t[2] == 'L'){
		parent->left = cur;
	}
	else if (t[2]=='R'){
		parent->right = cur;
	}
}
node* findnode(node* root, char t[])
{
	char val = t[0];
	node* cur = root;
	if (cur->data == val) return cur;
	if (cur->left){
		findnode(cur->left, t);
	}
	else if (cur->right){
		findnode(cur->right, t);
	}
}

int mindepth(node* t)
{
	if(!t) return 0;
	if (t->left == NULL && t->right == NULL){
		return 1;
	}
	else if (!t->left && t->right != NULL){
		return 1 + mindepth(t->right);
	}
	else if (!t->right && t->left != NULL){
		return 1 + mindepth(t->left);
	}
	else{
		return 1 + min(mindepth(t->left), mindepth(t->right));
	} 
}

string sortstr(string &s)
{
	string res ="";
	//init array to 26 char with 0
	char arr[26] = {0};
	for(int i = 0; i <s.length();i++){
		//increase each char in string by 1
		arr[s[i]-'A']++;
	}
	for(int j =0; j < 26; j++){
		char ch = (char)('A' + j);
		while(arr[j]--){
			res += ch;
		}
	}
	return res;

}
string reverse(string s)
{
	int len = s.length();
	char tmp;
	int i=0;
	int j = len -1;
	while (i<len/2){
		tmp = s[i];
		s[i] = s[j];
		s[j]=tmp;
		i++;
		j--;
	}
	return s;
}

string int2str(int t)
{
	string s = "";
	while (t){
		int rem= t%10;
		s +=rem+'0';
		t = t/10;
	}
	//reverse s
	return reverse(s);
}

string rearrange(string s)
{
	string output = "";
	int sum = 0;
	for(int i = 0; i < s.length(); i++){
		if (s[i] >= 'A'){
			output += s[i];
		}
		else{
			sum +=s[i]-'0';
		}
	}
	
	//sort(output.begin(),output.end());
	cout<<output<<endl;
	output = sortstr(output);
	output +=to_string(sum);;
	return output;
}
#if 1
int strstr(string s, string x)
{
	int i,j;
	int n = s.length();
	int m = x.length();
	for (i =0; i <=(n-m); i++){
		bool contain = true;
		for(j =0; j <m; j++){
			if (s[i+j]!=x[j]){
				contain = false;
			}
		}
		if(contain) return i;
	}
	return -1;
}
#else

int strstr(string s, string x)
{
	
	int pos = -1;
	int i,j;
	int n = s.length();
	int m = x.length();
	for (i =0; i <=(n-m); i++){
		if (s[i] == x[0]){
			pos = i;	
			i++;
			for(j=1; j<x.length(); j++){
				if(s[i] != x[j]){
					pos =-1;
					//i--;
					break;
				}
				i++;
			}
			if(j == x.length()){
				return pos;
			}
		}
		else{
			continue;
		}
	}
	return pos;
}
#endif
#if 1
int fib(int n)
{
	int m[2];
	int result;
	m[0] = 1;
	m[1] =1;
	if (n<=2) return 1;
	for (int i =3 ; i<=n; i++){
		result = m[0] + m[1];
		m[0] = m[1];
		m[1] = result;
	}
	return result;
}
#else
// use array
int fib(int n)
{
	int m[n+1];
	int i;
	m[1] = 1;
	m[2] = 1;
	for (i =3; i <=n; i++){
		m[i]=m[i-1]+ m[i-2];
	}
	return m[n];
}
#endif
int max(int a, int b)
{
	return a>=b?a:b;
}
int maxsumofedges(elem* root, int & res)
{	
	if (!root) return 0;
	if (!root->left && !root->right) return root->data;
	int ls = maxsumofedges(root->left, res);
	int rs = maxsumofedges(root->right, res);
	if (root->left && root->right){
		res = max(res, ls+rs+root->data);
		return max(ls,rs)+ root->data;
	}
	return (!root->left)?rs+root->data:
					 ls+root->data;
	
}
int maxsumbetweenedges(elem* root)
{
	int res = INT_MIN;
	maxsumofedges(root, res);
	return res;
}

int main()
{
	int testcase;
	int pr;
    DoublyLinkedList* linkedList = new DoublyLinkedList();
    Node listnode(1);

    linkedList->setHead(&listnode);
    linkedList->remove(&listnode);
	cout<<"input problem index "<<endl;
	cin>>pr;
	switch (pr) {
	
	// fib(8)
	case pfib:
	cout<<fib(8)<<endl;
	break;
	
	// strstr
	case pstrstr: {
	string s1 = "aaaaaaaaaaaaaab";
	string x ="aaaab";
	cout<<strstr(s1,x)<<endl;
	}
	break;

    //rearrange str
	case prearrangestr: {
	string s;
	cin>>testcase;
	while(testcase --){
    	cin>>s;
		cout<<rearrange(s)<<endl;
	}
	}
	break;
	//build tree
	case pbuildtree:{
	int edges;
	char edge[3];
	node* rt;
	cout<<"input testcases "<<endl;
	cin>>testcase;
	while(testcase --){
		cout<<"input number of edges"<<endl;
		cin>>edges;
		for(int i =0; i <edges; i++){
			for (int k =0; k <3; k++){
				cin>>edge[k];
			}
			if (i == 0){
				rt = new node();
				rt->data = edge[0];
	 			insertnode(rt, edge);
			}else {
				// find the parent node
				node* parent = findnode(rt, edge);
				insertnode(parent, edge);
			}
		}
		outtree(rt, 5);
		cout<<"mindepth = "<<mindepth(rt)<<endl;
	}
	}
	break;
	////find a subset with all fib numbers
	case psubsetoffib:
	cin>>testcase;
	while(testcase --){
		int arrNum;
		cin>>arrNum;
		int arr[arrNum];
		for(int i=0; i<arrNum; i++){
			cin>>arr[i];
		}
		vector<int> result;
		result = findsubset(arr, arrNum);
		for (int j=0; j <result.size(); j++){
				cout<<result[j]<<"\t";
		}
	}
	cout<<endl;
	break;
	case pstr2tree:{
	//convert str2tree
	string str = "a?b?c:d:e";
	node* root;
	root = convertExpression(str, 0);
	//printtree(root);
	outtree(root, 0);
	}
	break;
	case pmaxsumofedges:{
	int edges;
	int edge[3];
	elem* rt;
	cout<<"input testcases "<<endl;
	cin>>testcase;
	while(testcase --){
		cout<<"input number of edges"<<endl;
		cin>>edges;
		for(int i =0; i <edges; i++){
			for (int k =0; k <3; k++){
				cin>>edge[k];
			}
			if (i == 0){
				rt = new elem();
				rt->data = edge[0];
				buildtree(rt, edge);
			}
			else {
				elem* parent = findelem(rt, edge[0]);
				buildtree(parent, edge);
			}
			
		}
		outtree(rt, 5);
		cout<<"max sum "<<maxsumbetweenedges(rt)<<endl;
	}
	}
	break;
	default:
		break;
	}

    exit(0);
}