#include<iostream>
#include<vector>
#include<cassert>
#include<cmath>
using namespace std;


template<typename Value>
struct GraphNode{
		Value val;
		vector<GraphNode<Value>*> childs;
		GraphNode<Value>* parent;
};

#define Nodei GraphNode<int>

int evaluteBan(Field &ban){

	int 




	return 0;		
}


//turn,depth は0スタート
int Minmax(Nodei& node,int turn,int depth,int ab_checker){
	if(depth == 3)return node.val;

	vector<Nodei*> expand_nodes = node.childs;

	int best_val = -10000000;
	

	for(auto&& n : expand_nodes){
		
		int val = Minmax(*n,turn+1,depth+1,best_val);


		if(turn % 2 == 1 ){
	
			if(val <= ab_checker && ab_checker != -10000000){
	//			cout<<"ab"<<val<<":"<<depth<<":"<<turn<<endl;
				return abs(val);
			}
			if(best_val < -val) best_val = -val;
		}
		else{
	
			if(val >= ab_checker && ab_checker != -10000000){
	//			cout<<"ab"<<val<<":"<<depth<<":"<<turn<<endl;
				return abs(val);
			}
			if(best_val < val) best_val = val;
		}

	}

	return abs(best_val);
}


int main(){
	Nodei a,b,c,d,e,f,g,h,i,j,k,l,m,n,o;
	
	a.childs.push_back(&b);
	a.childs.push_back(&c);

	b.parent = &a;
	b.childs.push_back(&d);
	b.childs.push_back(&e);

	c.parent = &a;
	c.childs.push_back(&f);
	c.childs.push_back(&g);

	d.parent = &b;
	d.childs.push_back(&h);
	d.childs.push_back(&i);

	e.parent = &b;
	e.childs.push_back(&j);
	e.childs.push_back(&k);


	f.parent = &c;
	f.childs.push_back(&l);
	f.childs.push_back(&m);
	
	g.parent = &c;
	g.childs.push_back(&n);
	g.childs.push_back(&o);


	h.parent = &d;
	h.val = 5;
	
	i.parent = &d;
	i.val = 6;

	j.parent = &e;
	j.val = 7;

	k.parent = &e;
	k.val = 8;


	l.parent = &f;
	l.val = 1;
	
	m.parent = &f;
	m.val = 2;

	n.parent = &g;
	n.val = 3;
	
	o.parent = &g;
	o.val = 4;
	
	int best = Minmax(a,0,0,-10000000);

	cout<<"best "<<best<<endl;
	return 0;
}





