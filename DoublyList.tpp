template <typename T>
DoublyList<T>::DoublyList()
: header(new Node), trailer(new Node) {
    header->next  = trailer;
    trailer->prev = header;
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& copyObj)
: header(new Node), trailer(new Node) {
    copy(copyObj);
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
DoublyList<T>::~DoublyList() {
    clear();
    delete header;
    delete trailer;
    header = trailer = nullptr;
}

template <typename T>
void DoublyList<T>::append(const T& elem) {
    // TODO: Implement the code for the append
    Node* n = new Node(elem);

    if (head == nullptr) {
        head = n;
    }
    else {
        Node* curr = head;

        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = n;
        n->prev = curr;
    }

    this->length++;

}

template <typename T>
void DoublyList<T>::clear() {
    for (Node* curr = nullptr; header->next != trailer; ) {
        curr = header->next->next;
        delete header->next;
        header->next = curr;
    }

    trailer->prev = header;
    this->length  = 0;
}

template <typename T>
void DoublyList<T>::copy(const DoublyList<T>& copyObj) {
    this->length   = copyObj.length;
    Node* myCurr   = header;
    Node* copyCurr = copyObj.header->next;

    while (copyCurr != copyObj.trailer) {
        Node* n      = new Node(copyCurr->value);
        myCurr->next = n;
        n->prev      = myCurr;
        myCurr       = n;
        copyCurr     = copyCurr->next;
    }

    myCurr->next  = trailer;
    trailer->prev = myCurr;
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
    // TO DO: Implent code for getElement at position
}

template <typename T>
int DoublyList<T>::getLength() const {
    return this->length;
}


template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
    // TODO: Implement code to insert an element to list

    if(position < 0 || this->length < position){
        throw string ("Error insert: position out of bounds");
    } 

    Node* ins = new Node;
    ins->value = elem;

    if(position == 0){
        ins->next = head;
        head = ins;
    }
    else{
        Node* p = head;
        for (int i = 0; i < position - 1; ++i) {
            p = prev->next;  // safe because position <= length
        }
        ins->next = p->next;
        p->next = ins;
        ins->prev = p;
        ins->next->prev = ins;
    }

    this->length += 1;
}

template <typename T>
bool DoublyList<T>::isEmpty() const {
    return this->length  == 0
        && header->next  == trailer
        && trailer->prev == header;
}

template <typename T>
void DoublyList<T>::remove(int position) {
    // TODO: Implement code to remove element at given position

    if(head == nullptr && position >= 0){
        throw string ("Error remove: Linked List empty");
    } 
    else if(position < 0){
        throw string ("Error remove: position out of bounds");
    }

    if(position == 0){
        Node* del = head;
        head = head->next;
        delete del;
        return;
    }

    //creates a ptr and makes if go the node before position
    Node* p = head;
    for(int i = 0; i < position - 1; ++i){
        if(p->next == nullptr){
            throw string ("Error remove: position out of bounds");
        }
        p = p->next;
    }

    if(p->next == nullptr){
        throw string ("Error remove: position out of bounds");
    }

    Node * del = p->next;
    delete del;

    p->next = nullptr;
    
}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    // TODO: Implement code to search for element

    bool ret = false;
    Node* ptr = head;

    if(head->val == elem) return true;

    while(!ret && ptr->next != nullptr){
        if (ptr->val == elem){
            ret = true;
        }
        else{
            ptr = next->ptr;
        }
    }
    return false;
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    // TODO: Add code for replace method

    Node* ptr = head;

    for(int i = 0; i < position; ++i){
       ptr = ptr->next; 
    }

    ptr->val = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const DoublyList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename DoublyList<T>::Node* curr = myObj.header->next;
        while (curr != myObj.trailer) {
            outStream << curr->value;
            if (curr->next != myObj.trailer) {
                outStream << " <--> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}
