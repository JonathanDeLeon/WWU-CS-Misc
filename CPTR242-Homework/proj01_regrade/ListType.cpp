#include "ListType.h"

using namespace std;

ListType::ListType() {
    // Class constructor
    length = 0;
    listData = NULL;
}

ListType::ListType(const ListType &st) {
    // Class constructor
    length = 0;
    listData = NULL;
    currentPos = NULL;

    NodeType *iteratorPointer = st.listData;
    for (int i = 0; i < st.GetLength(); i++) {
        ItemType item = iteratorPointer->info;
        iteratorPointer = iteratorPointer->next;
        PutItem(ItemType(item));
    }
}

bool ListType::IsFull() const {
    NodeType *location;
    try {
        location = new NodeType;
        delete location;
        return false;
    } catch (std::bad_alloc exception) {
        return true;
    }
}

int ListType::GetLength() const {
    return length;
}

void ListType::MakeEmpty() {
    NodeType *tempPtr;

    while (listData != NULL) {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    length = 0;
}

ItemType ListType::GetItem(ItemType &item, bool &found) {
    bool moreToSearch;
    NodeType *location;

    location = listData;
    found = false;
    moreToSearch = (location != NULL);

    while (moreToSearch && !found) {
        switch (item.ComparedTo(location->info)) {
            case GREATER:
                location = location->next;
                moreToSearch = (location != NULL);
                break;
            case EQUAL:
                found = true;
                item = location->info;
                break;
            case LESS:
                moreToSearch = false;
                break;
        }
    }
    return item;
}

void ListType::PutItem(ItemType item) {
    NodeType *newNode;   // pointer to node being inserted
    NodeType *predLoc;   // trailing pointer
    NodeType *location;  // traveling pointer
    bool moreToSearch;

    location = listData;
    predLoc = NULL;
    moreToSearch = (location != NULL);

    // Find insertion point.
    while (moreToSearch) {
        switch (item.ComparedTo(location->info)) {
            case GREATER:
                predLoc = location;
                location = location->next;
                moreToSearch = (location != NULL);
                break;
            case LESS:
                moreToSearch = false;
                break;
            case EQUAL:
                // No operation.
                break;
        }
    }

    // Prepare node for insertion
    newNode = new NodeType;
    newNode->info = item;
    // Insert node into list.
    if (predLoc == NULL)  // Insert as first
    {
        newNode->next = listData;
        listData = newNode;
    } else {
        newNode->next = location;
        predLoc->next = newNode;
    }
    length++;
}

void ListType::InsertItem(ItemType item) {
    PutItem(item);
}

void ListType::DeleteItem(ItemType item) {
    NodeType *location = listData;
    NodeType *tempLocation;

    // Locate node to be deleted.
    if (item.ComparedTo(listData->info) == EQUAL) {
        tempLocation = location;
        listData = listData->next;  // Delete first node.
    } else {
        while (item.ComparedTo((location->next)->info) != EQUAL)
            location = location->next;

        // Delete node at location->next
        tempLocation = location->next;
        location->next = (location->next)->next;
    }
    delete tempLocation;
    length--;
}

void ListType::ResetList() {
    currentPos = NULL;
}

ItemType ListType::GetNextItem() {
    ItemType item;
    if (currentPos == NULL)
        currentPos = listData;
    item = currentPos->info;
    currentPos = currentPos->next;
    return item;
}

void ListType::GetNextItem(ItemType &item) {
    item = GetNextItem();
}

ListType::~ListType() {
    NodeType *tempPtr;

    while (listData != NULL) {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
}

void ListType::Print(ostream &dataFile) {
    // Pre:  list has been initialized.
    //       dataFile is open for writing.
    // Post: Each component in list has been written to dataFile.
    //       dataFile is still open.
    int length;
    ItemType item;
    dataFile << "PrintList: ";
    ResetList();
    length = GetLength();
    if (length == 0)
        dataFile << "List is empty.";
    else
        for (int counter = 1; counter <= length; counter++) {
            item = GetNextItem();
            item.Print(dataFile);
        }
    dataFile << endl;
}
