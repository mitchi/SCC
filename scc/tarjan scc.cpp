#include <iostream>
#include <stack>
#include <vector>
using namespace std;


struct node
{
	int index; //numbers a node in the order in which it was discovered.
	int lowlink;
	int visited; //0 = not visited, 1 = visited
	char name;
	vector<node*> adjlist;
};

node a,b,c,d,e,f,g,h; //zero

struct tarjan_scc {

//Globals
int index;
//Create the test graph
//this is the graph in CLRS page 

stack<node*> S;


void init()
{
	index = 1;
	initgraph();

	a.name = 'a'; b.name = 'b'; c.name = 'c'; d.name = 'd'; e.name = 'e'; f.name = 'f'; g.name = 'g'; h.name = 'h';


}

void initgraph(void)
{
	a.adjlist.push_back(&e);

	b.adjlist.push_back(&a);

	c.adjlist.push_back(&b);
	c.adjlist.push_back(&d);

	d.adjlist.push_back(&c);

	e.adjlist.push_back(&b);

	f.adjlist.push_back(&b);
	f.adjlist.push_back(&e);
	f.adjlist.push_back(&g);

	g.adjlist.push_back(&c);
	g.adjlist.push_back(&f);

	h.adjlist.push_back(&d);
	h.adjlist.push_back(&g);
	h.adjlist.push_back(&h);


}

void strongconnect(node * nn )
{
	node * next;

	nn->index = index;   //node takes next index (index = order visited)
	nn->lowlink = index;
	index++;

	S.push(nn);
	nn->visited = 1;

	//Successors of nn
	for (int i = 0; i < nn->adjlist.size() ; i++) 
	{
		
		next = nn->adjlist[i];
		if (next->visited == 0) { //if next is not visited, recursivity on it
			strongconnect(next);
			nn->lowlink = min(nn->lowlink, next->lowlink);

		}
		else if (next->visited == 1) { //if neighbor is already in stack, it is a part of the SCC
	
			nn->lowlink = min(nn->lowlink, next->index);  //lowlink takes index of next guy most of the time
		}
	}

	//Si nn est une root node, on pop la stack pour générer un SCC
	if (nn->lowlink == nn->index) {
		//New SCC
		printf("\n scc\n");

		while (1) {
			
			node * temp = S.top();
			S.pop();
			printf("%c", temp->name);
			
			//Mark the node as "out of reach" for other SCCs
			temp->visited = 2;

			if (temp == nn) break;


		}
	}


}


}; //fin struct



int main(void)
{

	tarjan_scc t;
	t.init();

	vector<node*> s;

	vector<node*> v;
	v.push_back(&a);v.push_back(&b);v.push_back(&c);v.push_back(&d);v.push_back(&e);v.push_back(&f);v.push_back(&g);v.push_back(&h);

	
	//Algorithme de Tarjan
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->visited == 0) {

			t.strongconnect(v[i]);

		}
	}


	return 0;

}