/*********************************************************************************
 *
 * FILENAME : functions.h
 *
 * DESCRIPTION :  This file contains the extern function of USER, PLAN and BILL class
 *
 * AUTHOR :  EPAP dev TEAM
 *
 * DATE : 02-02-2018
 *
 * COPYRIGHT @ Aricent Technologies (Holdings) Ltd.
 *
 **********************************************************************************/


#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/****************************************************************
*
*               USER CLASS FUNCTIONS
*
*****************************************************************/

extern void get_data();
extern void write_data();
extern void show_data();
extern void show_object();
extern void delete_data();
extern void modify_data();
extern int search_user(char tel_no[]);
extern float read_balance(int pos);
extern int read_connection_type(int pos);
extern int read_plan(int pos);
extern void update_balance(char tel_no[] , float balance);
extern char* get_contact_no();

/****************************************************************
*
*               PLAN CLASS FUNCTIONS
*
*****************************************************************/

extern void get_plan();
extern void add_plan();
extern void show_plan();
extern void show_object();
extern void delete_plan();
extern void modify_plan();
extern void search_plan(int plan_no_mod);
extern float get_plan_rate(int plan_num);


/****************************************************************
*
*               BILL CLASS FUNCTIONS
*
*****************************************************************/

extern void generate_bill(char tel_no[]);
extern void place_call(int connection_type , int plan_no , float balance);


#endif
