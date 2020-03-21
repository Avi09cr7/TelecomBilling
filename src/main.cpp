/***********************************************************************************
 *
 * FILENAME : main.c
 * 
 * DESCRIPTION : presents menu to user and then calls the appropriate function
 *
 * 
 *
 ***********************************************************************************/

/****************************************************************
*
*               HEADER FILES
*
*****************************************************************/

#include<cstdlib>
#include<iostream>
#include<fstream>
#include<header.h>
#include<iomanip>
#include<cstring>

/****************************************************************
*
*               MACROS
*
*****************************************************************/


#define CREATE_NEW_USER 1
#define SHOW_ALL 2
#define DELETE_A_USER 3
#define ADD_PLAN 4
#define SHOW_PLANS 5
#define DELETE_PLAN 6
#define EDIT_USER_INFO 7
#define EDIT_PLAN_INFO 8
#define PLACE_A_CALL 9
#define GENERATE_BILL 10
#define EXIT 11



#define NL_REMOVE(x) x[strlen(x)-1]='\0'
using namespace std;

user user_obj;
plan plan_obj;
bill bill_obj;


/****************************************************************
*
*               MAIN FUNCITON
*
*****************************************************************/


int main()
{    
    int ch = INVALID,
        pos = INVALID ;    
    char tel_no[MAX_LEN_FOR_CONTACT_NO] = {INVALID}, 
         reciever_no[MAX_LEN_FOR_CONTACT_NO] = {INVALID};
    float balance = 0.0;
    int plan_no = INVALID;
    int connection_type = PREPAID;


/****************************************************************
*
*               MENU FOR THE USER
*
*****************************************************************/

    
    do
    {
        system("clear");
	
	cout<<"\n***********************************************************************";
        cout<<"\n	            		MAIN MENU 					     ";  
	cout<<"\n***********************************************************************";

        cout<<"\n1.  CREATE NEW USER";
	cout<<"\n2.  SHOW ALL USERS";    
        cout<<"\n3.  DELETE A USER";
	cout<<"\n4.  ADD PLANS";
        cout<<"\n5.  SHOW PLANS";   
        cout<<"\n6.  DELETE PLAN";
        cout<<"\n7.  EDIT USER INFO";
        cout<<"\n8.  EDIT PLAN INFO";
        cout<<"\n9.  PLACE A CALL";
        cout<<"\n10. GENERATE BILL";
        cout<<"\n11. EXIT";
	cout<<"\n***********************************************************************";
        cout<<"\n ENTER YOUR CHOICE : ";	
	cin>>ch; 
        while(getchar()!='\n');
	cout<<"\n***********************************************************************";
        
	switch (ch)
        {    
            case CREATE_NEW_USER:
                user_obj.write_data();  				//FUNCTION CALL TO ADD USER               
                break;
      
            case DELETE_A_USER:
                user_obj.delete_data();					//FUNCTION CALL TO DELETE A USER
                break;
            
            case SHOW_PLANS:
                plan_obj.show_object();					//FUNCTION CALL TO SHOW ALL PLANS
                break;
               
            case DELETE_PLAN:
                plan_obj.delete_plan();					//FUNCITON CALL TO DELETE A PLAN
                break;

            case PLACE_A_CALL:
                cout<< "\n Enter your contact number : ";
                fgets(tel_no , MAX_LEN_FOR_CONTACT_NO , stdin);
		NL_REMOVE(tel_no);
		cout<< "\n Enter the reciever's numbers : ";
                fgets(reciever_no , MAX_LEN_FOR_CONTACT_NO , stdin);
		NL_REMOVE(reciever_no);

		cout<<"Searching number in the directory !!!";
                pos = user_obj.search_user(tel_no);			//FUNCTION CALL TO SEARCH NUMBER IN LIST
                if(pos == -1)
		{
			cout<<"\nNumber is not registered !!!";
			break;
		}
		else
		{
			cout<<"\nNumber is registered";
		}
		balance = bill_obj.read_balance(pos);
                connection_type = bill_obj.read_connection_type(pos);
                plan_no = bill_obj.read_plan(pos);
                balance = bill_obj.place_call(connection_type , plan_no , balance);	//FUNCTION CALL TO PLACE A CALL
                
                user_obj.update_balance(tel_no , balance);		//FUNCTION CALL TO UPDATE BALANCE
                
                break;
  
            case EDIT_USER_INFO:
                user_obj.modify_data();          			//FUNCTION CALL TO MODIFY USER DATA
                break;
        
            case EDIT_PLAN_INFO:
                plan_obj.modify_plan();					//FUNCTION CALL TO MODIFY PLANS
                break;
       
            case GENERATE_BILL:  
                cout<< "\n Enter your contact number : ";
                cin>> tel_no;
		while(getchar() != '\n');
                bill_obj.generate_bill(tel_no);				//FUNTION TO GENERATE BILL
                break;
    
	   
	    case SHOW_ALL:
		user_obj.show_object();					//FUNCTION CALL TO DISPLAY ALL USERS
		break;

	    case ADD_PLAN:
		plan_obj.add_plan();					//FUNCTION CALL TO ADD PLANS
	    	break;

	    case EXIT:
		cout<<"\nExitting main !!!";			//EXIT MENU
		getchar();
		break;

	    default:							//DEFAULT CASE
                std::cout<<"\n Wrong choice entered\n"; 
                break;
        
        }
    } while(ch != EXIT);
    
    return SUCCESS;
}
