#ifdef _RBTREE_H_

template <typename T>
RBTree<T>::RBTree() : size(0), root(NULL){}

template <typename T>
RBTree<T>::RBTree(const RBTree<T>& rbtree) : size(0) {
    root = CopyTree(rbtree.GetRoot(), NULL);
	size = rbtree.Size();
}

template <typename T>
RBTree<T>::~RBTree(){
	if (size > 0) {
		RemoveAll();
	}
}

template <typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& rbtree){
	RemoveAll();
	root = CopyTree(rbtree.GetRoot(), NULL);
	size = rbtree.Size();
	return *this;
}

template <typename T>
bool RBTree<T>::Insert(T item){
	bool flag = false;
	Node<T>* inserted_node = NULL;
	if (!Contains(item)){
		inserted_node = BSTInsert(item); // normal BST insertion method
		inserted_node->is_black = false;
		while (inserted_node != root && !inserted_node->p->is_black){ // iterates until root or black parent is reached
			if (inserted_node->p == inserted_node->p->p->left){
				Node<T>* uncle = inserted_node->p->p->right; // node's uncle
				if(!uncle->is_black){
					inserted_node->p->is_black = true;
					uncle->is_black = true;
					inserted_node->p->p->is_black = false;
					inserted_node = inserted_node->p->p;

				}
				else {//uncle is black yo
					if (inserted_node == inserted_node->p->right){
						inserted_node = inserted_node->p;
						RotateLeft(inserted_node);
					}
					inserted_node->p->is_black = true;
					inserted_node->p->p->is_black = false;
					RotateRight(inserted_node->p->p);
				}
			}
			if (inserted_node->p == inserted_node->p->p->right) {
				Node<T>* aunt = inserted_node->p->p->left;
				if(!aunt->is_black){
					inserted_node->p->is_black = true;
					aunt->is_black = true;
					inserted_node->p->p->is_black = false;
					inserted_node = inserted_node->p->p;
				}
				else{
					if(inserted_node == inserted_node->p->left){
						inserted_node = inserted_node->p;
						RotateRight(inserted_node);
					}
					inserted_node->p->is_black = true;
					inserted_node->p->p->is_black = false;
					RotateLeft(inserted_node->p->p);
				}
			}
		}
		root->is_black = true;//FIXME
		flag = true;
		size++;

	}

	return flag;


}

template <typename T>
bool RBTree<T>::Remove(T item){// Unable to find item
	if (size == 0 || !Contains(item)) {
		return false;
	}

	// Only node (root) node data does not match
	else if (size == 1 && root->data != item) {
		return false;
	}

	Node<T>* delete_this = root;
	// Finding the node for deletion
	while (delete_this != NULL) {
		if (item == delete_this->data) {
			break;
		}

		// Right
		else if (item > delete_this->data) {
			delete_this = delete_this->right;
		}

		//left
		else if (item < delete_this->data) {
			delete_this = delete_this->left;
		}
	}

	// Following algortihm taken from Lecture Slide
	Node<T>* y;
	Node<T>* x;

	// Both children are empty. Able to delete
	if (delete_this->left == NULL && delete_this->right == NULL) {
		delete delete_this;
		size--;
		delete_this = NULL; // setting empty pointer to NULL
		return true;
	}

	// There is at least one child
	if (delete_this->left == NULL || delete_this->right == NULL) {
		y = delete_this;
	}

	// delete_this has two children
	else {
		y = Predecessor(delete_this);
	}

	if (y->left != NULL) {
		x = y->left;
	}

	else {
		x = y->right;
	}

	x->p = y->p; // Detach x from y (if x is no NULL)

	// Delete node is root
	if (x->p == NULL) {
		root = x;
	}

	else {
		// Attach x to y's parent
		if (y == y->p->left) { // left child
			y->p->left = x;
		}

		else {
			y->p->right = x;
		}
	}

	if (y != delete_this) {
		delete_this->data = y->data; // y is the predessor
	}

	if (y->is_black) {
		RBRemoveFixUp(x, x->p, x == x->p->left); // x could be NULL
	}

	delete delete_this;
	delete_this = NULL; // Set empty pointer to NULL
	size--;
}

template <typename T>
void RBTree<T>::RemoveAll(){
	RemoveAll(root);
}

template <typename T>
int RBTree<T>::Size() const {return size;}

template <typename T>
int RBTree<T>::Height() const {
	return ComputeHeight(root);
}

// template <typename T>
// Node<T>* RBTree<T>::GetRoot() const {return root;}

/*
*
* HELPER FUNCTIONS
*
*/

template <typename T>
Node<T>* RBTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode){
    if (sourcenode == NULL) {
		return NULL;
	}

	Node<T>* new_node = new Node<T>(sourcenode->data);
	new_node->p = parentnode;
	new_node->left = CopyTree(sourcenode->left, new_node);
	new_node->right = CopyTree(sourcenode->right, new_node);

	return new_node;
}
template <typename T>
void RBTree<T>::RemoveAll(Node<T>* node){
if (node != NULL) {
		RemoveAll(node->left);
		RemoveAll(node->right);
		delete node;
		node = NULL;
	}
}

template <typename T>
void RBTree<T>::RBRemoveFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild){
	Node<T>* xsibling;


	while (x != root && x->is_black && x != NULL) {
		if (xisleftchild) {
			xsibling = xparent->right;

			// Red sibling to x
			if (!xsibling->is_black) {
				xsibling->is_black = true;
				xparent->is_black = false; // x's parent must have been black
				RotateLeft(xparent);
				xsibling = xparent->right;
			}

			if (xsibling->is_black && xparent->is_black) {
				xsibling->is_black = false;
				x = xparent;
			}

			else {
				if (xsibling->right->is_black) {
					xsibling->left->is_black = true;
					xsibling->is_black = true;
					RotateRight(xsibling);
					xsibling = xparent->right;
				}

				xsibling->is_black = xparent->is_black;
				xparent->is_black = true;
				xsibling->right->is_black = true;
				RotateLeft(xparent);
				x = root;
			}
		}

		// Symmetric to if
		else {
			xsibling = xparent->left;

			// Red sibling to x
			if (!xsibling->is_black) {
				xsibling->is_black = true;
				xparent->is_black = false; // x's parent must have been black
				RotateRight(xparent);
				xsibling = xparent->left;
			}

			if (xsibling->is_black && xparent->is_black) {
				xsibling->is_black = false;
				x = xparent;
			}

			else {
				if (xsibling->left->is_black) {
					xsibling->right->is_black = true;
					xsibling->is_black = true;
					RotateLeft(xsibling);
					xsibling = xparent->left;
				}

				xsibling->is_black = xparent->is_black;
				xparent->is_black = true;
				xsibling->left->is_black = true;
				RotateRight(xparent);
				x = root;
			}
		}
	} // end of while loop
	x->is_black = true;
	}



template <typename T>
int RBTree<T>::ComputeHeight(Node<T>* node) const
{
	if (root == NULL)
		return 0;
	else if (root!= NULL && root->left == NULL && root->right == NULL)
		return 1;
	else
		return (ComputeHeight(root->left) > ComputeHeight(root->right) ? ComputeHeight(root->left) : ComputeHeight(root->right))+1;
}







#endif
