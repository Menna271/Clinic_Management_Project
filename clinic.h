#ifndef CLINIC_H
#define CLINIC_H

typedef struct N
{
	char gender[7];
	char slot[30];
	char name[30];
	int age;
	int id;
	struct N *next;
}patient;

static patient* CreateNode ();
int SearchID (int num);
void NewRecord();
void EditRecord();
void reserve();
int IsReserved (char* a);
void cancel();
void admin_mode();
void admin_menu ();
void view_record ();
void view_slots ();
void user_mode ();
void main_menu();

#endif