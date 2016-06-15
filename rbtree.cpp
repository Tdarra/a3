#ifdef _RBTREE_H_

template <typename T>
RBTree<T>::RBTree() : size(0), root(NULL){}

template <typename T>
RBTree<T>::RBTree(const RBTree<T>& rbtree) : size(0) {
	// CopyTree(rbtree, rbtree.p);
}

template <typename T>
RBTree<T>::~RBTree(){
	RemoveAll(); //FIXME
}

template <typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& rbtree){
	// if (this != NULL)
	// 	CopyTree(rbtree, rbtree.p);
	return *this;
}

template <typename T>
bool RBTree<T>::Insert(T item){
	bool flag = false;
	Node<T>* inserted_node = NULL;
	if (!Contains(item)){
		flag = true;
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
			else {
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
	}

	return flag;
	

}

template <typename T>
bool RBTree<T>::Remove(T item){
	bool flag = false;
	if (Contains(item)){
		flag = true;
		Node<T>* kill_node = Find(item);
		Node<T>* tempy = NULL;
		Node<T>* tempx
		if(kill_node->right == NULL || kill_node->left == NULL)
			tempy = kill_node;
		else
			tempy = Predecessor(kill_node);
		if(tempy->left != NULL)
			tempx = tempy->left;
		else
			tempx = tempy->right;
		tempx->p = tempy->p;
		if (tempy->p == NULL)
			root = tempx;
		else if (tempy == tempy->p->left)
			tempy->p->left = tempx;
		else
			tempy->p->right = tempx;
		if(tempy != kill_node)
			kill_node->data = tempy->data;
		if(tempy->is_black)
			bool is_left_child = tempx == tempx->p->left;
			RBRemoveFixUp(tempx,tempx->p, is_left_child);
	}
	return flag;
}

template <typename T>
void RBTree<T>::RemoveAll(){
	RemoveAll(root);
}

template <typename T>
int RBTree<T>::Size() const {return size;}

template <typename T>
int RBTree<T>::Height() const {
	ComputeHeight(root);
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
	return NULL; //FIXME
}
template <typename T>
void RBTree<T>::RemoveAll(Node<T>* node){} //FIXME

template <typename T>
void RBTree<T>::RBRemoveFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild){
	Node<T>* w = NULL;

	while(x != root && x->is_black){
		while (xisleftchild){ // might need to be replaced with if instead...
			w = xparent->right;
			if (!w->is_black){
				w->is_black = true;
				xparent->is_black = false;
				RotateLeft(x->p);
				w = xparent->right;
				}
			if (w->left->is_black && w->right->is_black){
				w->is_black = false;
				x = xparent;
				
				if (w->right->is_black){
					w->left->is_black = true;
					w->is_black = false;
					RotateRight(w);
					w = xparent->right;
				}
			
				w->is_black = xparent->is_black;
				xparent->is_black = true;
				w->right->is_black = true;
				RotateLeft(xparent);
				x = root;
			}


			}
			while (!xisleftchild){ // might need to be replaced with if...
				w = xparent->left;
				if (!w->is_black){
				w->is_black = true;
				xparent->is_black = false;
				RotateRight(xparent);
				w = xparent->left;
				}
			if (w->right->is_black && w->left->is_black){
				w->is_black = false;
				x = xparent;
				
				if (w->left->is_black){
					w->right->is_black = true;
					w->is_black = false;
					RotateLeft(w);
					w = xparent->left;
				}
			
				w->is_black = xparent->is_black;
				xparent->is_black = true;
				w->left->is_black = true;
				RotateRight(xparent);
				x = root;
			}

			}

		}
	}

} //FIXME

template <typename T>
int RBTree<T>::ComputeHeight(Node<T>* node) const {
	return 0; //FIXME
}





#endif
