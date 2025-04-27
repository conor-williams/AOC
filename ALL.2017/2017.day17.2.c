#include <iostream>
#include <memory>

//CharlieYJH on reddit
using namespace std;

struct node {
	int val;
	shared_ptr<struct node> next;
};

int main(int argc, char const* argv[])
{
	printf("		2017 Day 17 Part 2\n");
	const int step = 354;
	shared_ptr<struct node> head = make_shared<struct node>();
	shared_ptr<struct node> curr = head;
	head->val = 0;
	head->next = head;

	/*
	for (int i = 1; i <= 2017; i++) {

		for (int j = 0; j < step; j++)
			curr = curr->next;

		shared_ptr<struct node> temp = curr->next;
		shared_ptr<struct node> new_node = make_shared<struct node>();
		new_node->val = i;
		curr->next = new_node;
		new_node->next = temp;
		curr = new_node;
	}

	cout << curr->next->val << endl;
	*/

	int answer_pt2 = 0;

	for (int i = 1, idx = 0; i <= 50000000; i++) {
		idx = (idx + 1 + step) % i;
		if (idx == 0) {answer_pt2 = i;}
	}

	//cout << answer_pt2 << endl;
	printf("**ans: %d\n", answer_pt2);

	return 0;
}
