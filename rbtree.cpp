#ifdef _RBTREE_H_
// TAJ MADE A CHANGE
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
		inserted_node = BSTInsert(item);
		inserted_node->is_black = false;
		//FIXME
	}

	return flag;
	

}

template <typename T>
bool RBTree<T>::Remove(T item){
	return false; //FIXME
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
void RBTree<T>::RBRemoveFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild){} //FIXME

template <typename T>
int RBTree<T>::ComputeHeight(Node<T>* node) const {
	return 0; //FIXME
}





#endif
