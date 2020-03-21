/*********************************************************************************
 *
 * FILENAME : header.h
 *
 * DESCRIPTION :  This file contains the class defination of USER, PLAN and BILL
 * 
 * AUTHOR :  EPAP dev TEAM
 *
 * DATE : 02-02-2018
 *
 * COPYRIGHT @ Aricent Technoogies (Holdings) Ltd.
 *
 **********************************************************************************/

#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>

#define SUCCESS 0
#define FAILURE 1 

#define PREPAID 0
#define POSTPAID 1 
#define INVALID -1

#define MAX_LEN_FOR_NAME 30
#define MAX_LEN_FOR_CONTACT_NO 12
#define MAX_LEN_FOR_PLAN_DESC 60


/****************************************************************
*
*		USER CLASS
*
*****************************************************************/

class user
{
    private:
        char user_name[MAX_LEN_FOR_NAME];
        char contact_no[MAX_LEN_FOR_CONTACT_NO];
        int connection_type;
        int plan_no;
        float balance;

   public:
	
	user();
	user(char name[MAX_LEN_FOR_NAME], char tel_no[MAX_LEN_FOR_CONTACT_NO], int con_type , int pl_no , float bal);
	
	int get_connection_type()
	{
		return connection_type;
	}
	float get_balance()
	{
		return balance;
	}	
	void get_data();
        void write_data();
	void show_data();
	void show_object();
        void delete_data();
        void modify_data();  
        int search_user( char tel_no[] );
        float read_balance(int pos);
        int read_connection_type(int pos);
        int read_plan(int pos);
        void update_balance(char tel_no[] , float balance);
	char* get_contact_no();
};

/****************************************************************
*
*		PLAN CLASS
*
****************************************************************/



class plan
{
    private:
        float plan_rate;
        int plan_no;

    public:
	plan();
	void get_plan();
	void add_plan();
        void show_plan();
	void show_object();
        void delete_plan();
        void modify_plan();
        int search_plan(int plan_no);
	float get_plan_rate(int plan_num);
};



/****************************************************************
*
*		BILL CLASS
*
****************************************************************/



class bill : public user
{
    private:
        char contact_no[MAX_LEN_FOR_CONTACT_NO];
        unsigned long call_duration;
        float amount;
       
    public:
	bill();
        void generate_bill( char tel_no[] );
        float place_call( int connection_type , int plan_no, float balance );

};
