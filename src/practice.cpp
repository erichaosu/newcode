#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <math.h>
#include <climits>
#include <stack>
using namespace std;

typedef enum {
	pfib =1,
	pstrstr =2,
	prearrangestr = 3,
	pbuildtree=4,
	psubsetoffib=5,
	pstr2tree=6,
	pmaxsumofedges=7,
	proman2int=8,
	ptripletwith0sum=9,
	pminsubset=10,
	ppalindro=11,
	pkpalindro=12,
	pprintleaf =13,
	pmaxsecwooverlap=14,
	ptriplesumnum = 15,
	ptwodiff=16,
	pstrdecode=17,
	pbirdandtree=18,
	preversesinlist=19,
	ptreemirror=20,
}problem;

class single_link{
	public:
	struct element{
		int data;
		element* next;
		element(int val, element* y=0){
			data = val;
			next = y;
		}
	};
	element* head;
	element* tail;

	single_link(){
		head = NULL;
		tail = NULL;
	}
	~single_link();
	void add_front(int val);
	void del_elem(int val);
	void display();
	void revers_singlelink(element* list);

};
void single_link::add_front(int val)
{
	element* new_elem = new element(val);
	if (this == NULL) {
		this->head = new_elem;
		this->tail = new_elem;
	}
	new_elem->next = this->head;
	this->head = new_elem;
}

void single_link::del_elem(int val)
{
	if (this == NULL) return;
	element* cur = this->head;
	if(this->head->data == val){
		this->head = this->head->next;
		delete cur;
	}
	element* tmp;
	while (cur && cur->next != NULL){
		if(cur->next->data == val){
			tmp = cur->next;
			cur->next = cur->next->next;
			delete tmp;
		}
		cur = cur->next;
	}
}

void single_link::display()
{
	element* cur = this->head;
	while(cur != NULL){
		cout<<cur->data<<"->";
		cur = cur->next;
	}
	cout<<"NULL"<<endl;
}
void single_link::revers_singlelink(element* list)
{
	if (list == NULL) return;
	if (list->next == NULL) return;
	element* t1 = NULL;
	element* t2 = list;
	element* t3;
	while (t2 != NULL){
		t3 = t2->next;
		t2->next = t1;
		t1 = t2;
		t2 = t3;
	}
	this->head = t1;
}

//double linklist
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

//input array 1 2 R 1 3 L to build binary tree
//    1
//   /  \
//  3    2 
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
//recursive get min depth of tree
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
//rearrage str sum number and sort char, input: 3A2C4B == 9ABC
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
//check if string s contain string x 
//if true, output position i in str 1 
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
//roman 2 interger
int getint(char c)
{
	if(c == 'I') return 1;
	else if(c == 'V') return 5;
	else if(c == 'X') return 10;
	else if(c == 'L') return 50;
	else if(c == 'C') return 100;
	else if(c == 'D') return 500;
	else if(c == 'M') return 1000;
	else return -1;
}
int roman2int(string rn)
{
	int res=0;
	for (int i =0; i< rn.length(); i++){
		int s1 = getint(rn[i]);
		if (i+1 < rn.length()){
			int s2 = getint(rn[i+1]);
			if (s1 < s2){
				res = res + s2-s1;
				i++;	
			}
			else {
				res = res + s1;
			}
		}
		else {
			res = res + s1; 
		}
	}
	return res;
}

vector<vector<int>> findthreesum(int* arr, int length, int t)
{
	vector<vector<int>> triplet;
	vector<int> res = {};
	sort(arr, arr+length);
	for (int i =0; i<length-2;i++){
		int left = i+1;
		int right = length-1;
		while(left <right){
			int sum = arr[i]+arr[left]+arr[right];
			if(sum == t){
				triplet.push_back({arr[i],arr[left],arr[right]});
				break;
			}
			else if (sum <t){
				left ++;
			}
			else {
				right--;
			}
		}
	}
	return triplet;
}
//smallest subarray with sum greater than num
int minsubset(int arr[], int size, int num)
{
	int min_len = size +1;
	int cur_sum = 0;
	int start = 0;
	int end = 0;
	while(end < size){
	while (cur_sum <=num && end < size){
		cur_sum +=arr[end];
		end++;
	}
	while (cur_sum >num && start <size){
		cur_sum -=arr[start];
		start ++;
		//update min_len
		if (min_len > (end-start)){
			min_len = end-start;
		}
	}
	}
	if (min_len > size) return -1;
	return min_len;
}

bool ispalindro(string str)
{
	int left = 0;
	int right = str.length() -1;
		while (left < right){
			if (str[left] == ' '){
				left ++;
			}
			if (str[right] == ' '){
				right --;
			}
			if (str[left] != str[right]){
				return false;
			}
			left ++;
			right--;
		}
	return true;
}
int numofdel(string str, int m, string rstr, int n)
{
	//if pne str le = 0, all char of other str should be deleted
	if (m == 0) return n;
	if (n == 0) return m;

	if (str[m-1] == str[n-1]){
		return numofdel(str, m-1, rstr, n-1);
	}
	return 1+ min(numofdel(str, m-1, rstr, n),
			      numofdel(str, m, rstr, n-1));			
}
bool iskpalindro(string str, int k)
{
	string rstr = str;
	reverse(rstr.begin(), rstr.end());
	int len = str.length();
	if (numofdel(str, len, rstr, len)<= 2*k){
		return true;
	}
	else {
		return false;
	}
}
struct BST{
	int value;
	BST* left;
	BST* right;
};
void insertbst(BST* &root, int val)
{
	BST* cur = new BST();
	cur->value = val;
	if (root == NULL){
		root = cur;
		return;
	}
	if (val < root->value){
		insertbst(root->left, val);
	}
	else {
		insertbst(root->right, val);
	}
}
void printleaf(BST* bst)
{
	BST* cur= bst;
	if (cur->left ==NULL && cur->right ==NULL){
		cout<<cur->value<<"\t";
	}
	if (cur->left) printleaf(cur->left);
	if (cur->right) printleaf(cur->right);
}

int  maxsecwooverlap(vector<int> &start, vector<int> &end, int numofnodes)
{
	int maxnoneoverlap = 0;
	// sort both array
	sort(start.begin(), start.end());
	sort(end.begin(), end.end());
	//assume first sec is ine of result
	maxnoneoverlap++;
	int j = 0;
	for (int i = 1; i< numofnodes; i++){
		if (start[i] >= end[j]){
			maxnoneoverlap++;
			j = i;
		}
	}
	return maxnoneoverlap;
}

int triplesumnum(vector<int> arr, int numofnodes, int t)
{
	vector<vector<int>> res;
	int sum;
	sort(arr.begin(), arr.end());
	for (int i = 0; i < numofnodes; i++){
		int left = i+1;
		int right = numofnodes-1;
		while(left < right){
			sum = arr[i] + arr[left] +arr[right];
			if(sum == t){
				res.push_back({arr[i],arr[left],arr[right]});
				break;
			}
			else if (sum < t){
				left++;
			} 
			else {
				right --;
			}
		}
	}
	return res.end() - res.begin();
}

int twodiff(vector<int> arr, int size, int t)
{
	int res =0;
	sort(arr.begin(), arr.end());
	int left=0;
	int right =1;
	while(right < size){
		if(arr[right]-arr[left]== t){
			res++;
			left++;
			right++;
		}
		else if (arr[right]-arr[left] <t){
			right++;
		}
		else {
			left ++;
		}
	}
	return res;
}

string strdecode(string str)
{
	stack<int> intstack;
	stack<char> charstack;
	string res;
	for (int i =0; i < str.length(); i++){
		//check if it's a num
		if (str[i] >='0' && str[i] <= '9'){
			int intnum =0;
			while (str[i] >='0' && str[i] <= '9'){
				intnum = intnum*10 + (str[i]-'0');
				i++; 
			}
			i--;
			intstack.push(intnum); 
		}
		else if (str[i] == '['){
			charstack.push(str[i]);
			if(i==0&&!(str[i-1] >='0' && str[i-1] <= '9')){
				intstack.push(1);
			}
		}
		else if (str[i] == ']'){
			string temp = "";
			int count= 0;
			//pop int stack to get count of char
			if (!intstack.empty()){
				count = intstack.top();
				intstack.pop();
			}
			//assemble all chars before '['
			while (!charstack.empty() && charstack.top() != '['){
				temp =charstack.top()+temp;
				charstack.pop();
			} 
			//pop '['
			while (!charstack.empty() && charstack.top() == '['){
				charstack.pop();
			}
			//assemble chars with count
			for (int i =0; i <count; i++){
				res +=temp;
			}
			//push res* count backin
			for(int j =0; j <res.length(); j++){
				charstack.push(res[j]);
			}
			res = "";
		}
		else{
			charstack.push(str[i]);
		}
	}
	while(!charstack.empty()){
		res =charstack.top() + res;
		charstack.pop();
	}
	return res;
}

 int maxTreeSum(int a[], int size, int windowsize)
{
   int max_so_far = 0, max_wind_start = -1;
   int i,j,sum=0;
   int w = windowsize;
   int n = size;
   for(i=0;i<n;i++){
       for(j=0;j<w;j++){
           sum=sum+a[(j+i)%n];
       }
       if(max_so_far < sum){ max_wind_start=i ;max_so_far = sum; }
       sum=0;

   }
   printf("Max sum resulting window");
   j=max_wind_start;
   
   while(w--){
        printf(" %d",a[j%n]);
        j++;
    }
    printf("\n");
   return max_so_far;
}

int main()
{
	string name;
	int testcase;
	int pr;
    DoublyLinkedList* linkedList = new DoublyLinkedList();
    Node listnode(1);

    linkedList->setHead(&listnode);
    linkedList->remove(&listnode);
	cout<<"input problem index "<<endl;
	cin>>pr;
	switch (pr) {
	
	// fib(8)  get fibnacci number using O(n) time O(1) space two number array        1
	case pfib:
	cout<<fib(8)<<endl;
	break;
	
	// strstr   if str1 contain str2, return position of str1               2
	case pstrstr: {
	string s1 = "aaaaaaaaaaaaaab";
	string x ="aaaab";
	cout<<strstr(s1,x)<<endl;
	}
	break;

    //rearrange str sum number and sort char, input: 3A2C4B == 9ABC         3
	case prearrangestr: {
	string s;
	cin>>testcase;
	while(testcase --){
    	cin>>s;
		cout<<rearrange(s)<<endl;
	}
	}
	break;
	//build tree and find min depth of tree                                 4

	//input array 1 2 R 1 3 L to build binary tree
	//    1
	//   /  \
	//  3    2
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
	////find a subset with all fib numbers              5
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
	//convert str2tree                                 6
	//tenary expression to build tree
	// a?b?c:d:e build tree 
	//        a
	//      b   e
	//    c   d
	string str = "a?b?c:d:e";
	node* root;
	root = convertExpression(str, 0);
	//printtree(root);
	outtree(root, 0);
	}
	break;
	// max sum of edges                                          7
	//use 12L13R build tree then get the max sum between two edges
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
	// roman number to int                            8
	case proman2int:{
		int digits;
		string rn;
		cout<<"inout testcase: "<<endl;
		cin>>testcase;
		while(testcase--){
			cout<<"input roman number: "<<endl;
			
			cin>>rn;
			
			cout<<rn<<" = "<<roman2int(rn)<<endl;
		}
	}
	break;
	//triple sum equal to 0                          9
	case ptripletwith0sum:{
		int size;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		while(testcase --){
			cout<<"input array size "<<endl;
			cin>>size;
			int arr[size];
			for (int i =0; i<size;i++){
				cin>>arr[i];
			}
			vector<vector<int>> triplet = findthreesum(arr, size, 0);
			
			for (vector<int> m:triplet){
				cout<<"{";
				for(int i: m){
					cout<<i<<",";
				}
				cout<<"}, ";
			}
			vector<vector<int>> test(1);
			test[0].push_back(1);
			cout<<test[0][0]<<endl;
		}
	}
	break;
	//smallest subarray with sum greater than num                10
	case pminsubset:{
		int size,num;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		while(testcase --){
			cout<<"input array size "<<endl;
			cin>>size;
			cout<<"input number "<<endl;
			cin>>num;
			int arr[size];
			for (int i =0; i<size;i++){
				cin>>arr[i];
			}
			cout<<minsubset(arr, size, num)<<endl;
		}
	}
	break;
	//check if str is palinedrom                           11
	case ppalindro:{
		
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		cin.ignore();
		while(testcase --){
			cout<<"input string "<<endl;
			
			getline (cin,name);
			if (ispalindro(name)){
				cout<<" Yes "<<endl;				
			}
			else {
				cout<<" NO "<<endl;	
			}
			
		}
	}
	break;
	// k palindrom                          12
	//check if a str become palindrom after removing k char
	case pkpalindro:{
		int k;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		cin>>k;
		cin.ignore();
		while(testcase --){
			cout<<"input string "<<endl;
			
			getline (cin,name);
			if (iskpalindro(name, k)){
				cout<<" Yes "<<endl;				
			}
			else {
				cout<<" NO "<<endl;	
			}
			
		}
	}
	break;
	//print bst leaves inorder                  13
	case pprintleaf:{
		int numofnodes;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		cout<<"input num nodes"<<endl;
		cin>>numofnodes;
		vector<int> nodes;
		int n;
		while(testcase --){
			cout<<"input data "<<endl;
			BST* bst = NULL;
			for(int i=0; i <numofnodes; i++){
				cin>>n;
				nodes.push_back(n);
				insertbst(bst, nodes[i]);
				
			}
			printleaf(bst);
		}
	}
	break;
	//max number of sequence number without overlap       14
	case pmaxsecwooverlap:{
		int numofnodes;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		
		vector<int> start;
		vector<int> end;
		int n;
		while(testcase --){
			cout<<"input num activity"<<endl;
			cin>>numofnodes;
			cout<<"input data "<<endl;
			for(int i=0; i <numofnodes; i++){
				cin>>n;
				start.push_back(n);
			}
			for(int i=0; i <numofnodes; i++){
				cin>>n;
				end.push_back(n);
			}
			cout<<maxsecwooverlap(start, end, numofnodes)<<endl;;
		}
	}
	break;
	//triple sum equal to target number                15
	case ptriplesumnum: {
		int numofnodes;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		
		vector<int> arr;
		int n,t;
		while(testcase --){
			cout<<"input num nodes"<<endl;
			cin>>numofnodes>>t;
			cout<<"input node data "<<endl;
			for(int i=0; i <numofnodes; i++){
				cin>>n;
				arr.push_back(n);
			}
			cout<<triplesumnum(arr, numofnodes, t)<<endl;
		}
	}
	break;
	//similar to twosum but twodiff equal to target num  16
	case ptwodiff: {
		int numofnodes;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		
		vector<int> arr;
		int n,t;
		while(testcase --){
			cout<<"input num nodes"<<endl;
			cin>>numofnodes;
			cout<<"input node data "<<endl;
			for(int i=0; i <numofnodes; i++){
				cin>>n;
				arr.push_back(n);
			}
			cin>>t;
			cout<<twodiff(arr, numofnodes, t)<<endl;
		}
	}
	break;
	//decode str [b2[ca]] == bcaca                17
	case pstrdecode: {
		int numofnodes;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		string str;
		while(testcase --){
			cout<<"input node data "<<endl;
			cin>>str;
			cout<<strdecode(str)<<endl;
		}
	}
	break;
	//bird and tree bird input: numoftree, total seconds
	// array of fruit on each tree, output maxfruit bird can get 
	// within that sec                                   18
	case pbirdandtree: {
		int numofnodes;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		int numtree, sec;
		while(testcase --){
			cout<<"num of tree "<<endl;
			cin>>numtree;
			cin>>sec;
			int a[numtree];
			for(int i =0; i <numtree; i++){
				cin>>a[i];
			}
			cout<<maxTreeSum(a, numtree, sec)<<endl;
		}
	}
	break;
	//build single list, reverse list                     19
	case preversesinlist: {
		int numofnodes;
		cout<<"input testcase  "<<endl;
		cin>>testcase;
		int numtree, sec;
		while(testcase --){
			cout<<"num of elem "<<endl;
			cin>>numtree;
			int a[numtree];
			single_link* sinlist = new single_link();
			for(int i =0; i <numtree; i++){
				cin>>a[i];
				sinlist->add_front(a[i]);
			}
			sinlist->display();
			sinlist->revers_singlelink(sinlist->head);
			sinlist->display();
			cout<<"delete element :"<<endl;
			cin>>sec;
			sinlist->del_elem(sec);
			sinlist->display();
		}
	}
	break;
	default:
		break;
	}

    exit(0);
}
