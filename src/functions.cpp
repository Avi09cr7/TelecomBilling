/***************************************************************************
 *
 * FILENAME : functions.cpp
 *
 * DESCRIPTION :  This file contains functions with their functionality
 *
 *
 *
 *
 ***************************************************************************/


/*********************************************************************************
*
*		HEADER FILES       
*
**********************************************************************************/

#include<iostream>
#include<cstdlib>
#include<string.h>
#include<fstream>
#include<header.h>

/*********************************************************************************
*
*               MACROS
*
**********************************************************************************/


#define NL_REMOVE(x) x[strlen(x)-1]='\0'
using namespace std;



/*********************************************************************************
*
*	Function Name: USER constructor
*	Function Description:  This is used to initialize the values of USER class
*
**********************************************************************************/

user::user()
{
    strcpy(user_name,"INVALID");
    strcpy(contact_no,"INVALID");
    connection_type = INVALID;
    plan_no = INVALID;
    balance = 0.0;               
}
user::user(char name[MAX_LEN_FOR_NAME] ,char tel_no[MAX_LEN_FOR_CONTACT_NO], int con_type , int pl_no , float bal)
{
	strcpy(user_name, name);
	strcpy(contact_no, tel_no);
	connection_type = con_type;
	plan_no = pl_no;	
	balance = bal;
}



/**********************************************************************************
*
*	Function Name: PLAN constructor
*	Function Description:  This is used to initialize the values of PLAN class
*
***********************************************************************************/

plan::plan()
{
    plan_no = INVALID ;
    plan_rate = INVALID ;       
}



/**********************************************************************************
*
*	Function Name: BILL constructor
*	Function Description:  This is used to initialize the values of BILL class
*
***********************************************************************************/

bill::bill()
{    
    strcpy(contact_no,"INVALID") ;       
    call_duration = 0 ;  
}




/*********************************************************************************
*
*	Function Name: get_data()
*	Function Description:  This is used to input the values from the user.
*
**********************************************************************************/

void user::get_data()
{

    cout<<"\nEnter your Name : " ;
    fgets(user_name , MAX_LEN_FOR_NAME , stdin);
    NL_REMOVE(user_name);    
    cout<< "\nEnter your contact number : " ; 
    fgets(contact_no , MAX_LEN_FOR_CONTACT_NO , stdin);
    NL_REMOVE(contact_no);    

    cout<<"\nConnection type (Prepaid -> 0 / Postpaid -> 1) : " ;
    cin>>connection_type; 
    while(getchar()!='\n'); 

    cout<<"\nEnter the plan number : " ;
    cin>> plan_no; 
    while(getchar()!='\n');
 
    if(connection_type == 0)
    {
    	cout<<"\nEnter the Balance : " ;
    	cin>> balance; 
    	while(getchar()!='\n');
    }   
    return;
}



/*******************************************************************************************
*
*       Function Name: write_data()
*       Function Description:  This is used to write the user input data onto USER_DATA file.
*
*********************************************************************************************/

void user::write_data()
{	

    user user_obj;    

    fstream outfile;
    outfile.open("../dat/user_data.txt" , ios::out | ios::binary | ios::app );
    
    user_obj.get_data();
    
    outfile.write((char *)&user_obj , sizeof(user_obj));
    outfile.flush();
    outfile.close();
  
    return;
}

/*********************************************************************************
*
*       Function Name: show_data()
*       Function Description:  This is used to display the data from the file.
*
**********************************************************************************/

void user::show_data()
{
    cout<<"\n\nName : "<<user_name;
    cout<<"\nContact Number : "<<contact_no;
    cout<<"\nConnection Type : "<<connection_type;
    cout<<"\nPlan_no : "<<plan_no;
    cout<<"\nBalance : "<<balance;
    return;
}

/*************************************************************************************************
*
*       Function Name: show_data()
*       Function Description:  This is used to read data from the file and call the show funciton.
*
***************************************************************************************************/

void user::show_object()
{
    user user_obj;

    fstream infile;
    infile.open("../dat/user_data.txt" , std::fstream::in);
    infile.seekg(0,ios::beg);
    infile.read((char*)&user_obj, sizeof(user_obj));

    while(!infile.eof())
    {
	user_obj.show_data();
	infile.read((char*)&user_obj , sizeof(user_obj));
    }

    cout<<"\n\nPress any key to continue";
    getchar();
    
    infile.close();
    return;
}

/*************************************************************************************************
*
*       Function Name: delete_data()
*       Function Description:  This is used to delete the data from the file for a particular user.
*
***************************************************************************************************/

void user::delete_data()
{    
    char tel_no[MAX_LEN_FOR_CONTACT_NO]; 
    fstream infile, outfile;
    user user_obj;
     
    cout<<"\nEnter the contact number to be deleted";
    fgets(tel_no , MAX_LEN_FOR_CONTACT_NO , stdin);
    NL_REMOVE(tel_no);    

    outfile.open("../dat/tempfile.txt",ios::out|ios::app);
    infile.open("../dat/user_data.txt",ios::in);
    infile.read((char*)&user_obj,sizeof(user_obj));
    
    while (!infile.eof())
    {   
	if( strcmp(user_obj.contact_no , tel_no) != 0)
             outfile.write((char*)&user_obj, sizeof(user_obj));
            
        infile.read((char*)&user_obj, sizeof(user_obj));    
    }

    remove("../dat/user_data.txt");
    rename("../dat/tempfile.txt" , "../dat/user_data.txt");
    return;
}

/************************************************************************************
*
*       Function Name: modify_data()
*       Function Description:  This is used to modify the data for a particular user.
*
************************************************************************************/

void user::modify_data()
{
    char tel_no[MAX_LEN_FOR_CONTACT_NO];
    fstream infile, outfile;    
    int conn_type;
    user user_obj;

    cout<<"\nEnter the contact number to be modified";
    fgets(tel_no , MAX_LEN_FOR_CONTACT_NO , stdin); 
    NL_REMOVE(tel_no);
 
    infile.open("../dat/user_data.txt" , ios::in ); 
    outfile.open("../dat/tempfile.txt" , ios::out | ios::app);
    infile.seekg(0,ios::beg);
    infile.read((char*)&user_obj , sizeof(user_obj));

    while (!infile.eof())
    {
	if(strcmp(tel_no , user_obj.contact_no) != 0)
	{
        	outfile.write((char*)&user_obj, sizeof(user_obj));
        	infile.read( (char*)&user_obj, sizeof(user_obj));
        }
	else
        {

	    cout<<"\n Enter the name : ";
	    fgets(user_obj.user_name , MAX_LEN_FOR_NAME , stdin);
	    NL_REMOVE(user_obj.user_name);
	    
     	    cout<<"\n Enter the connection type : ";
	    cin>>conn_type;
	    while(getchar()!='\n');
	    if(user_obj.connection_type == POSTPAID && conn_type == PREPAID)
	    {
		cout<<"Connot change from postpaid to prepaid!!! Connection type will remain POSTPAID";
	 	user_obj.connection_type = POSTPAID;
	    }	    
	    else
	    {
		user_obj.connection_type = conn_type;
  	    }

	    cout<<"\nEnter the plan no : ";
	    cin>>user_obj.plan_no;
            while(getchar()!='\n');
	   
	    if(user_obj.connection_type == PREPAID) 
 	    {
		cout<<"\nEnter the updated Balance : ";
	    	cin>>user_obj.balance;            
            	while(getchar()!='\n');
	    }
	    else
		user_obj.balance = 0.0;

	    strcpy(user_obj.contact_no , tel_no);
            outfile.write( (char*)&user_obj , sizeof(user_obj));
            infile.read( (char*)&user_obj, sizeof(user_obj));
	
            outfile.flush();           
        }
    }
  
    remove("../dat/user_data.txt");
    rename("../dat/tempfile.txt","../dat/user_data.txt");

    outfile.close();
    infile.close();
}

/***************************************************************************************
*
*       Function Name: read_balance()
*       Function Description:  This is used to return the balance for a particular user.
*
****************************************************************************************/

float user::read_balance(int pos)
{
    fstream infile;
    user user_obj_local;
    infile.open("../dat/user_data.txt" , ios::in);

    infile.seekg(pos , ios::beg);
    infile.read((char*)&user_obj_local , sizeof(user_obj_local));
    
    infile.close();
    return user_obj_local.balance;    
}



/***********************************************************************************************
*
*       Function Name: read_connection_type()
*       Function Description:  This is used to return the connection type for a particular user.
*
************************************************************************************************/


int user::read_connection_type(int pos)
{
    fstream infile;
    user user_obj_local;
    infile.open("../dat/user_data.txt" , ios::in);

    infile.seekg( pos , ios::beg );
    infile.read( (char*)&user_obj_local , sizeof(user_obj_local));
    
    infile.close();
    return user_obj_local.connection_type;    
}


/***********************************************************************************************
*
*       Function Name: read_plan()
*       Function Description:  This is used to return the plan number for a particular user.
*
************************************************************************************************/

int user::read_plan(int pos)
{
    fstream infile;
    user user_obj_local;
    infile.open("../dat/user_data.txt" , ios::in);

    infile.seekg(pos , ios::beg);
    infile.read((char*)&user_obj_local , sizeof(user_obj_local));
    
    infile.close();
    return user_obj_local.plan_no;    
}


/***********************************************************************************************
*
*       Function Name: get_plan()
*       Function Description:  This is used to get the plan detaila from the user.
*
************************************************************************************************/

void plan::get_plan()
{

    cout<<"\nEnter your plan no.:" ;
    cin>>plan_no;
    while(getchar() != '\n');
    cout<< "\nEnter the Plan Rate : " ; 
    cin>>plan_rate;
    while(getchar() != '\n');

    return;
}


/***********************************************************************************************
*
*       Function Name: add_plan()
*       Function Description:  This is used add the new plan onto the file as presented by user.
*
************************************************************************************************/

void plan::add_plan()
{	

    plan plan_obj;    

    fstream outfile;
    outfile.open("../dat/plan_data.txt" , ios::out | ios::app);
    
    plan_obj.get_plan();
    
    outfile.write((char *)&plan_obj , sizeof(plan_obj));
    outfile.flush();
    outfile.close();
  
    return;
}


/***********************************************************************************************
*
*       Function Name: show_plan()
*       Function Description:  This is used to display all the plans.
*
************************************************************************************************/

void plan::show_plan()
{
    cout<<"\n\nPlan number is : " <<plan_no ;
    cout<<"\nPlan Rate (rs/min): " <<plan_rate;
}


/**************************************************************************************************
*
*       Function Name: show_object()
*       Function Description:  This is used read plan from file and call show_plan() to display it.
*
***************************************************************************************************/

void plan::show_object()
{
    fstream infile;
    plan plan_obj;
    infile.open("../dat/plan_data.txt" , ios::in);
    
    infile.read((char*)&plan_obj , sizeof(plan_obj));
    while(!infile.eof())
    {
	plan_obj.show_plan();
        infile.read((char*)&plan_obj , sizeof(plan_obj));
    }

    cout<<"\nPress any key to continue";
    getchar();
    infile.close();
}


/***********************************************************************************************
*
*       Function Name: delete_plan()
*       Function Description:  This is used to delete a particular plan.
*
************************************************************************************************/

void plan::delete_plan()
{
    fstream infile , outfile;
    plan plan_obj;
    int plan_number;
    outfile.open("../dat/tempfile.txt" , ios::out);
    infile.open("../dat/plan_data.txt"  , ios::in);
    
    cout<<"\n Enter the plan number to be deleted : ";
    cin>>plan_number;
    while(getchar()!='\n');
 
    infile.read((char*)&plan_obj , sizeof(plan_obj));
    while(!infile.eof())
    {
        if( plan_number != plan_obj.plan_no )
        {
            outfile.write((char*)&plan_obj, sizeof(plan_obj));
        }

        infile.read((char*)&plan_obj , sizeof(plan_obj));
        outfile.flush();
    }

    remove("../dat/plan_data.txt");
    rename("../dat/tempfile.txt" , "../dat/plan_data.txt");

    infile.close();
    outfile.close();
}


/***********************************************************************************************
*
*       Function Name: modify_plan()
*       Function Description:  This is used to modify a particular plan.
*
************************************************************************************************/

void plan::modify_plan()
{
    int plan_no_mod ;
    fstream infile, outfile;    
    plan plan_obj;

    cout<<"\nEnter the plan number to be modified";
    cin>>plan_no_mod; 
    while(getchar()!='\n');


    infile.open("../dat/plan_data.txt" , ios::in ); 
    outfile.open("../dat/tempfile.txt" , ios::out );
    infile.seekg(0,ios::beg);
    infile.read((char*)&plan_obj , sizeof(plan_obj));

    while (!infile.eof())
    {
        if(plan_no_mod != plan_obj.plan_no)
        {
             outfile.write( (char*)&plan_obj , sizeof(plan_obj) );
        }
        else
        {

	    cout<<"\n Enter the plan rate : ";
	    cin>>plan_obj.plan_rate;
	    while(getchar() != '\n'); 

	    plan_obj.plan_no = plan_no_mod;
            outfile.write( (char*)&plan_obj , sizeof(plan_obj) );
            outfile.flush();           
        }

        infile.read( (char*)&plan_obj, sizeof(plan_obj) );    
    }
  
    remove( "../dat/plan_data.txt" );
    rename( "../dat/tempfile.txt", "../dat/plan_data.txt");
     
    infile.close();
    outfile.close();

    return;
}


/***********************************************************************************************
*
*       Function Name: search_user()
*       Function Description:  This is used to search a particular user to place a call.
*
************************************************************************************************/

int user::search_user(char tel_no[])
{
    fstream infile , infile1;
    user user_obj;
    int pos = -1 ,
	count = 0;
    infile.open("../dat/user_data.txt" , ios::in);
    infile1.open("../dat/user_data.txt" , ios::in);

    infile.read((char*)&user_obj , sizeof(user_obj));

    while(!infile.eof())
    {
	if(strcmp(user_obj.contact_no , tel_no) == 0)
	{
	    if(count == 0)
	    	pos = 0;
	    else
		pos = infile1.tellg();

	}
	count++;
	infile1.read((char*)&user_obj , sizeof(user_obj));
    	infile.read((char*)&user_obj , sizeof(user_obj));
    }


    infile.close();
    infile1.close();
    return pos;
}




/***********************************************************************************************
*
*       Function Name: get_plan_rate()
*       Function Description:  This is used to return the plan rate to calculate amount of 
*				the call placed.
*
************************************************************************************************/

float plan::get_plan_rate( int plan_num)
{
    fstream infile;
    plan plan_obj;
    infile.open("../dat/plan_data.txt" , ios::in);

    infile.read((char*)&plan_obj , sizeof(plan_obj));

    while(!infile.eof())
    {
	if(plan_obj.plan_no == plan_num)
		return plan_obj.plan_rate;
	
	infile.read((char*)&plan_obj , sizeof(plan_obj));

    }

    infile.close();
    return INVALID;
}



/***********************************************************************************************
*
*       Function Name: place_call()
*       Function Description:  This is used to place a call and calculate amount of that
*				 particular call.
*
************************************************************************************************/

float bill::place_call( int connection_type , int plan_no , float amount )
{ 
    int duration = INVALID ;
    float balance = 0.0;
    bill bill_obj;
    plan plan_obj;

    cout<<"\n Enter the call duration (in minutes)" ;
    cin>>duration; 
    while(getchar()!='\n');

    if(connection_type == POSTPAID)
    {  
        duration = -1 * duration;
    }
    if(plan_no == INVALID)
    {
        cout<< "\n This plan does not exist... ";
    } 
    else
    {
	if(amount - (duration * plan_obj.get_plan_rate(plan_no)) < 0)
	        cout<< "\n This call cannot be completed" ;
        else
                balance = amount - ( duration * plan_obj.get_plan_rate(plan_no));
    }
 
    return balance;

}



/***********************************************************************************************
*
*       Function Name: update_balance()
*       Function Description:  This is used to update the balance for a particular user
*				who has made a call.
*
************************************************************************************************/

void user::update_balance( char tel_no[] , float balance )
{
    user user_obj;
    fstream infile,outfile;    
    
    infile.open("../dat/user_data.txt",ios::in);
    outfile.open("../dat/tempfile.txt",ios::out);
    infile.read( (char*)&user_obj , sizeof(user_obj) );
    
    while(!infile.eof())
    {   
        if(strcmp(user_obj.contact_no , tel_no) == 0)
        { 
            user_obj.balance = balance;
        }   
        
        outfile.write( (char*)&user_obj , sizeof(user_obj) );        
	infile.read( (char*)&user_obj , sizeof(user_obj) );
    }
    remove("../dat/user_data.txt");
    rename("../dat/tempfile.txt" , "../dat/user_data.txt");
    infile.close();
    outfile.close();
    return;
	      
}



/***********************************************************************************************
*
*       Function Name: get_contact_no()
*       Function Description:  This is used to return contact numer for a particular user
*				who has placed a call.
*
************************************************************************************************/

char* user::get_contact_no()
{
    return contact_no;
}



/***********************************************************************************************
*
*       Function Name: generate_bill()
*       Function Description:  This is used to display the total bill of a particular user.
*
************************************************************************************************/

void bill::generate_bill( char tel_no[] )
{
    fstream infile;
    user user_obj;
    infile.open("../dat/user_data.txt" , ios::in);

    infile.read((char*)&user_obj , sizeof(user_obj));
    while(!infile.eof())
    {
        if(strcmp(user_obj.get_contact_no() , tel_no)==0)
        {
            if( user_obj.get_connection_type() == POSTPAID )
                cout<<"\n Your total bill is : "<<user_obj.get_balance() ;

            else
                cout<<"\n Your remaining balance is : "<<user_obj.get_balance() ;
        }
	
        infile.read((char*)&user_obj , sizeof(user_obj));
    }

    cout<<"\n\nPress any key to continue !!!";
    getchar();
    
    infile.close();
} 


