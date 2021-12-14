#include <iostream>


#define COUNT 10

void print2DUtil(Node *root, int space)
{
	// Base case
	if (&src == _leaf || &src == _begin || &src == _end)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->right, space);

	// Print current node after space
	// count
	std::cout << std::endl;
	for (int i = COUNT; i < space; i++)
		std::cout<<" ";
	std::cout<<root->val.second<<"\n";

	// Process left child
	print2DUtil(root->left, space);
}

void print2D(Node *root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}