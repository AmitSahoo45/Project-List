// Assignment #1
// File: LinkedList.h
// Name: Caden Scharpf
// ASU Email Address: cscharpf@asu.edu

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings

using namespace std;

//struct Project represents some project information
struct Project
{
    string projectName;
    int numberOfParticipants;
    struct Project * next;
};//end struct Project

class LinkedList
{
    private:
        struct Project * head;

        bool isEmpty();
        void garbageAccumulator(Project **head, int *count);

    public:
        LinkedList();
        ~LinkedList();

        bool addProject(string projectName, int numberOfParticipants);
        bool removeProject(string projectName);
        bool changeParticipantNumber(string projectName, int newNumberOfParticipants);

    void printList();
};//end class LinkedList

/**
 * @brief Construct a new Linked List:: Linked List object
 * 
 */
LinkedList::LinkedList()
{
    head = NULL;
}

/**
 * @brief Destroy the Linked List:: Linked List object
 * 
 */
LinkedList::~LinkedList()
{
    int x = 0;
    garbageAccumulator(&head, &x);
    cout << "The number of deleted projects is: " << x << endl;
}

/**
 * @brief Attempts to add a new project data into the linked list using the parameter values - project name, 
 *        and the number of participants. If there is no memory left to create a new object or if a project 
 *        with the same project name already exists in the linked list, the function will return 0. 
 *        Otherwise returns 1.
 * 
 * @param newProjectName Name of the project to be added
 * @param newNumberOfParticipants Number of participants
 * @return true 
 * @return false 
 */
bool LinkedList::addProject(string newProjectName, int newNumberOfParticipants)
 {
    Project **current = &head;
    while((*current))// Find pos. in list
    {
        if(newProjectName.compare((*current)->projectName) <= 0)
        {
            break;
        }
        current = & (*current)->next;
    }

    if((*current) != NULL)
    {
        if((*current)->projectName == newProjectName) // Check for project w/ same name
        {
            return 0;
        }
    }

    Project * newProject = new (nothrow) Project;
    if(newProject == 0) //check for memory err
    {
        return 0;
    }
    
    newProject->projectName = newProjectName;
    newProject->numberOfParticipants = newNumberOfParticipants;
    newProject->next = *current;
    *current = newProject;

    //projectAddedMsg(newProjectName);
    return 1;
 }//end method addProject

/**
 * @brief Attempts to remove the project with the parameter project name value.
 *        Returns true if it can find and remove the project information.
 *        Otherwise returns false.
 * 
 * @param projectName Name of the project to be removed
 * @return true 
 * @return false 
 */
bool LinkedList::removeProject(string projectName)
 {
    Project **curr = &head;
    while((*curr))
    {
        if((*curr)->projectName == projectName)
        {
            Project * unlinked = (*curr);
            *curr = (*curr)->next;
            delete(unlinked);
            return 1;
        }
        curr = & (*curr)->next;
    }
    return 0;
 }
 
/**
 * @brief Attempts to change the number of participants with the parameter project name value.
 *        Return's true if it can find and update the project information, otherwise returns false.
 * 
 * @param projectName Name of the project to be added
 * @param newNumberOfParticipants Number of participants
 * @return true 
 * @return false 
 */
bool LinkedList::changeParticipantNumber(string projectName, int newNumberOfParticipants)
{
    Project **curr = &head;
    while((*curr))
    {
        if((*curr)->projectName == projectName)
        {
            (*curr)->numberOfParticipants = newNumberOfParticipants;
            return 1;
        }
        curr = & (*curr)->next;
    }
    return 0;
}

/**
 * @brief Prints all entries in the linked list in the following format:
 *       ' Project Name: projectName, Number of Participants: numberOfParticipants '
 */
void LinkedList::printList()
{
    if(head == NULL) {
        cout << "The list is empty" << endl;
        return;
    }
    Project **current = &head;
    for(; *current; current = & (*current)->next)
    {
        cout << "Project Name: " << (*current)->projectName << ", ";
        cout << "Number of Participants: " << (*current)->numberOfParticipants << endl;
    }
}//end method printList

/**
 * @brief Accumulator subroutine for the destructor.Recursively 
 *        navigates to the end of the list and Deletes each
 *        project as it propigates back down the stack
 * 
 * @param head pointer to the head
 * @param count initialize to 0
 */
void LinkedList::garbageAccumulator(Project **head, int *count)
{   
    if(*head == NULL) {return;} 
    garbageAccumulator(&(*head)->next, count);
    delete(*head);
    *count = (*count)+1;
}