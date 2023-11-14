#include "clinic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 2D array of strings that hold the reservation slots for everyday
char schedule[5][30] = {
	"2pm to 2:30pm",
	"2:30pm to 3pm",
	"3pm to 3:30pm",
	"4pm to 4:30pm",
	"4:30pm to 5pm"
};

patient* head = NULL;        
patient* tail = NULL;
patient* current = NULL;         // pointer used in checking whether ID already exists
patient* current_r = NULL;       // pointer used in checking whether the slot is already taken

// the most basic function to allocate a new node
static patient* CreateNode () 
{
	patient *ptr = (patient*) malloc (sizeof(patient));
	printf ("Enter patient information: \n");
	
	printf ("Enter name: ");
	scanf ("%s",ptr->name);
	
	printf ("Enter age: ");
	scanf ("%d",&ptr->age);
	
	printf ("Enter gender: ");
	scanf ("%s",ptr->gender);
	
	printf ("Enter ID: ");
	scanf ("%d",&ptr->id);
	
	while (SearchID(ptr->id)==1)
	{
		printf ("ID already taken. Please try again: ");
		scanf ("%d",&ptr->id);
	}
	
	printf ("Record created successfully.");
	
	return ptr;
}

// iterates through all nodes to make sure that the ID is unique
int SearchID (int num) 
{
	current = head;
	while (current != NULL) 
	{
		if (current->id==num)
		{
			return 1;
		}
		current = current->next;
    }
	return 0;
}

// calls NewNode function to store a new patient record
void NewRecord () 
{
	int x;
	patient* NewNode = CreateNode();
	if (head == NULL)
		head = NewNode;
	else 
		tail -> next = NewNode;
	tail = NewNode;
	tail -> next = NULL;
	
	// after successfully creating a record the admin can either create another one or exit this window
	printf ("\nPress (1) to create another record, press (0) to go back.");
	scanf ("%d",&x);
	switch (x)
	{
		case 1:
		NewRecord();
		break;
		case 0:
		admin_menu();
		break;;
	}
}

void EditRecord ()
{
	int n,x;
	printf ("Enter the ID of the patient: ");
	scanf ("%d",&n);
	// checking if the ID is valid
	if (SearchID(n)==1)
	{
		// the admin can edit any of the four fields
		printf ("Choose the number of the field you want to edit:\n(1)Name   (2)Age   (3)Gender   (4)ID    ");
		scanf ("%d",&x);
		switch (x)
		{
			case 1:
			printf ("Enter edited name: ");
			scanf ("%s",current->name);
			printf ("Name edited successfully.");
			break;
			
			case 2:
			printf ("Enter edited age: ");
			scanf ("%d",&current->age);
			printf ("Age edited successfully.");
			break;
			
			case 3:
			printf ("Enter edited gender: ");
			scanf ("%s",current->gender);
			printf ("Gender edited successfully.");
			break;
			
			case 4:
			printf ("Enter edited ID: "); 
			int d;
			scanf ("%d",&d);
			patient* temp = head;    // a temporary pointer to loop through the nodes to check if there's a duplicate
	        while (temp != NULL)     // same logic as SearchID function 
	        {
		        if (temp->id==d)
		        {
		          	printf ("ID already taken. Please try again: ");
	            	scanf ("%d",&d);
	        	}
		        temp = temp->next;
            }
			current -> id = d;
			printf ("ID edited successfully.");
			break;
		}
	}
	else
	{
		printf ("Incorrect ID. \n");
		EditRecord();                
	}
	
	// after successfully editing a record the admin can either edit another one or exit this window
	printf ("\nPress (1) to edit another record, press (0) to go back.");
	scanf ("%d",&x);
	switch (x)
	{
		case 1:
		EditRecord();
		break;
		case 0:
		admin_menu();
		break;
	}
}

void reserve() 
{
	int n,i;
	printf ("Enter the ID of the patient: ");
	scanf ("%d",&n);
	int s = SearchID(n);    // checking ID as usual
	if (s==1)
	{
		printf ("Choose one from the available slots: \n");
	    for (i=1; i<6; i++)
	    {
			if (IsReserved(schedule[i-1])==1)                 // if the slot is reserved the loop skips this iteration
				continue;
		    printf ("(%d) %s \n",i,schedule[i-1]);
	    }
		scanf ("%d",&i);
		switch (i)
		{
			case 1:
			strcpy(current->slot,schedule[0]);
			printf ("The slot from %s is reserved for patient %s successfully.",current->slot,current->name);
			break;
			
			case 2:
		    strcpy(current->slot,schedule[1]);
			printf ("The slot from %s is reserved for patient %s successfully.",current->slot,current->name);
			break;
			
			case 3:
			strcpy(current->slot,schedule[2]);
			printf ("The slot from %s is reserved for patient %s successfully.",current->slot,current->name);
			break;
			
			case 4:
			strcpy(current->slot,schedule[3]);
			printf ("The slot from %s is reserved for patient %s successfully.",current->slot,current->name);
			break;
			
			case 5:
			strcpy(current->slot,schedule[4]);
			printf ("The slot from %s is reserved for patient %s successfully.",current->slot,current->name);
			break;
		}
    }
	else
	{
		printf ("Incorrect ID. \n");
		reserve();
	}
	
	// after successfully reserving a slot the admin can either reserve another one or exit this window
	int x;
	printf ("\nPress (1) to reserve another slot, press (0) to go back.");
	scanf ("%d",&x);
	switch (x)
	{
		case 1:
		reserve();
		break;
		case 0:
		admin_menu();
		break;
	}
}

// a function to check if the slot is already taken	
int IsReserved (char* a)
{
	current_r = head;
	while (current_r != NULL) 
	{
		if (strcmp(current_r->slot, a)==0)
		{
			return 1;
		}
		current_r = current_r->next;
    }
	return 0;
}

// a function to cancel reservations
void cancel ()
{
	int n;
	printf ("Enter the ID of the patient: ");
	scanf ("%d",&n);
	if (SearchID(n)==1)
	{
		strcpy(current->slot,"empty");         // overwriting the appointment is the patient's slot with the strin 'empty'
		printf ("Reservation for patient %s is cancelled.",current->name);
	}
	else
	{
		printf ("Incorrect ID. \n");
		cancel();
	}
	
	// after cancelling a reservation the admin can either cancel another one or exit this window
	int x;
	printf ("\nPress (1) to cancel another reservation, press (0) to go back.");
	scanf ("%d",&x);
	switch (x)
	{
		case 1:
		cancel();
		break;
		case 0:
		admin_menu();
		break;
	}
}

void admin_mode ()
{
	int i,p;
	printf ("Enter password: ");
	scanf ("%d",&p);
	for (i=1; i<3; i++)            // the user can try to enter the password only 3 times
	{
		if (p==1234)
			break;
		else 
		{
			printf ("Incorrect password. Please try again: ");
	        scanf ("%d",&p);
		}
	}
	if (i==3)         // when the number of trials exceeds 3 the program shuts down
		exit(0);
	else
		admin_menu();
}

// a function that contains the four main features of admin mode and can also allow to go back and switch to user
void admin_menu ()
{
	int x;
	printf ("Choose an option from the following: \n");
	printf ("(1) Add new patient record \n");
	printf ("(2) Edit patient record \n");
	printf ("(3) Reserve a slot with the doctor \n");
	printf ("(4) Cancel reservation \n");
	printf ("(5) Go back to main menu \n");
	scanf ("%d",&x);
	
	switch (x)
	{
		case 1 :
		NewRecord();
		break;
		case 2 :
		EditRecord();
		break;
		case 3 :
		reserve();
		break;
		case 4 :
		cancel();
		break;
		case 5 :
		main_menu();
		break;
	}
}

// displays the patient's info upon entering a valid ID
void view_record ()
{
	int n;
	printf ("Enter the ID of the patient: ");
	scanf ("%d",&n);
	if (SearchID(n)==1)
	{
		printf ("Name: %s\n",current->name);
		printf ("Agee: %d\n",current->age);
		printf ("Gender: %s\n",current->gender);
		printf ("ID: %d\n",current->id);	
	}
	else
	{
		printf ("Incorrect ID. \n");
		view_record();
	}
	
	int x;
	printf ("\nPress (1) to view another patient record, press (0) to go back.");
	scanf ("%d",&x);
	switch (x)
	{
		case 1:
		view_record();
		break;
		case 0:
		user_mode();
		break;
	}
}

// a function to view today's reservations with the ID of the patient who reserved the slot
void view_slots ()
{
	for (int i=0; i<5; i++)
	{
		if(IsReserved(schedule[i])==1)
			printf ("The slot from %s is reserved for patient %d \n",schedule[i],current_r->id);
		else
			printf ("The slot from %s is not reserved \n",schedule[i]);
	}
	int x;
	printf ("\nPress (0) to go back.");
	scanf ("%d",&x);
	switch (x)
	{
		case 0:
		user_mode();
		break;
	}
}

// a function that contains the two main features of user mode and can also allow to go back and switch to admin
void user_mode ()
{
	int x;
	printf ("Choose an option from the following: \n");
	printf ("(1) View patient record \n");
	printf ("(2) View today's reservations \n");
	printf ("(3) Go back to main menu \n");
	scanf ("%d",&x);
	
	switch (x)
	{
		case 1 :
		view_record();
		break;
		case 2 :
		view_slots();
		break;
		case 3 :
		main_menu();
		break;
	}
}

// the function that holds everything together and the only function in the main file
void main_menu ()
{
	int x;
	printf ("Choose an option from the following: \n");
	printf ("(1) Admin mode \n");
	printf ("(2) User mode \n");
	printf ("(3) Exit \n");
	scanf ("%d",&x);
	
	switch (x)
	{
		case 1 :
		admin_mode();
		break;
		case 2 :
		user_mode();
		break;
		case 3 :
		exit(0);
	}
}