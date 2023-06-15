#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void pin();
void all();
void trans();
void deposit();
void withdraw();
void bal();
void bills();
void detail();
void display();
void ew();
void ph();
void transfer();
int dpin;

struct customer
{
    int account_no;
    char name[80];
    float balance;
    int pin;
};

void main()
{
int choice;
all();
}





void all()
{
int choice;
	  printf("\nAccount details entry menu:\n");
      	  printf("1.Create\n");
    	  printf("2.Transactions\n");
             printf("3.Display all records\n");
	  printf("4.Exit");
              printf("\nEnter your choice(1-4): ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                detail();
                break;

	    case 2:
		pin();
		break;

            case 3:
                display();
                break;

	    case 4:
		exit(1);
		break;

	   default:
                 printf("\nThat is an invalid option!!!\n\n"); 
	}
}
void detail()
{
	struct customer c;
	FILE *f;
	f=fopen("bank","ab");

        printf("Enter your name:");
        scanf("%s",c.name);
        printf("Enter account_no : ");
        scanf("%d",&c.account_no);
        printf("Enter a pin number for your account");
        scanf("%d",&c.pin);
        printf("Confirm your pin number"); 
        scanf("%d",&dpin);
	c.balance = 0;
	fwrite(&c,sizeof(c),1,f);
	fclose(f);
	all();
}

void display()
{   
    struct customer c;
    FILE *f;
    f=fopen("bank","rb");
    while(fread(&c,sizeof(c),1,f)==1)
     {    
printf("Account No:%d\nName:%s\n",c.account_no,c.name);    
     }
     fclose(f);
	all();  
}

void pin()
{
	int i;
	struct customer c;
	FILE *f;
	f=fopen("bank","rb");
	printf("*****| WELCOME to SBI Bank!|*****\n\n\n");
 	printf("..............................................................\n\n");
	printf("\nPin Number Verification\n");
	printf("-----------------------------------\n\n");

	printf("\n__________Enter your pin:__________\n\n");
	scanf("%d",&dpin);
 	while(fread(&c,sizeof(c),1,f)==1)
 	{ 
	   if(dpin==c.pin)
		{
		printf("Your pin is confirmed\n");
		trans();
		}
	   else
		{
		printf("Invalid pin number\n"); 
		pin();
		}
	}
	fclose(f);			
}


void trans()
{ 
	int menuOption;
            printf("Transactions\n");
            printf("------------------------------------------\n");
            printf("1)Balance\n\n2)Deposit\n\n3) Withdraw\n\n
4)Payment/transfers\n\n5) Exit\n\n");
            printf("------------------------------------------\n");
	    printf("Enter your option(1-4)\n");
            scanf("%d",&menuOption);
	do
	{
	   switch(menuOption)
		{
		    case 1:bal();
     		           break;
	
                    case 2:deposit();
	                    break;

   		    case 3:withdraw();
	                   break;

		    case 4:bills();
			   break;

                    case 5:all();
			break;

                   default:
                           printf("\nThat is an invalid option!!!\n\n"); 
	      } 
       }while(1);

}

void bal()
{
	struct customer c;
	FILE *f;
	f=fopen("bank","rb");  
printf("\n_________________Check                                                                                                                                                                   Balance_________________\n\n"); 
	while(fread(&c,sizeof(c),1,f)==1)
	{
	  if(c.pin==dpin)
	  printf("Your current balance is %f\n",c.balance);
	}	
	fclose(f);
	trans();
}

void deposit()
{
	struct customer c;
	float amount;
	FILE *f;
	int number,dpin;
	f=fopen("bank","r+b");   
	printf("\n_________________Deposit__________________\n\n");

	while(fread(&c,sizeof(c),1,f)==1)
	 {
	printf("Enter the account no\n");
	scanf("%d",&number);
	if(number==c.account_no)
	{
	printf("\n__________Enter your pin:__________\n\n");
	scanf("%d",&dpin);
	   if(c.pin==dpin)
	   {
		printf("Enter the amount to be deposited\n");
		scanf("%f",&amount);
        	c.balance+=amount;
			if(amount>c.balance)
			{
			printf("Not enough money to withdraw\n");
			}
			else
			{
		fseek(f,(-1)*sizeof(c),SEEK_CUR);
		fwrite(&c,sizeof(c),1,f);
		printf("Amount deposited successfully!\n");
      	  	printf("Your current balance=%f\n",c.balance);
	  		}
}
	}
	else
	{
	printf("The account no does not exsist\n");
	deposit();
	}
	}
	fclose(f);
	trans();

}


void withdraw()
{
	int dpin,number;
	struct customer c;
	float amount;
	FILE *f;
	f=fopen("bank","r+b");  
	printf("\n_________________Withdraw_________________\n\n"); 
	while(fread(&c,sizeof(c),1,f)==1)
	 {
		printf("Enter the account no\n");
		scanf("%d",&number);
		if(number==c.account_no)
		{
		printf("\n__________Enter your pin:__________\n\n");
		scanf("%d",&dpin);
	  	 if(c.pin==dpin)
	 	   {
		 	printf("Enter the amount to be withdrawn\n");
		 	scanf("%f",&amount);
       			c.balance-=amount;
			if(amount>c.balance)
			{
			printf("Not enough money to withdraw\n");
			}
			else
			{
			fseek(f,(-1)*sizeof(c),SEEK_CUR);
			fwrite(&c,sizeof(c),1,f);
			printf("Amount deposited successfully!\n");
       	                printf("Your current balance=%f\n",c.balance);
			}
		  }
	       }
		else
		printf("The account no does not exsist\n");
	}
	fclose(f);
	trans();
}

void bills()
{
	int dpin,no,option;
	float amount;
	printf("\n_______________Pay bills_______________\n\n"); 

	 printf("1) Electricity bill\n\n2) Water bill\n\n3) Phone bill\n\n4)Online tranfer\n\n5) Exit\n\n");
            printf("------------------------------------------\n");
	    printf("Enter your option(1-4)\n");
            scanf("%d",&option);

	do
	{
	   switch(option)
		{
		    case 1:ew();
    		      	  break;			 
			
	
                    case 2:ew();
    		      	  break;

   		    case 3:ph();						
     		          break;

		    case 4:transfer();
			   break;

                    case 5:
			trans();			
                        break;

                   default:
                           printf("\nThat is an invalid option!!!\n\n"); 
	      } 
       }while(1);
	
}

void ew()
{
int dpin,number,no;
	struct customer c;
	float amount;
	FILE *f;
	f=fopen("bank","r+b");  
printf("\n_________________Electricity/Water Bill                   Payment_________________\n\n"); 
	while(fread(&c,sizeof(c),1,f)==1)
	 {
		printf("Enter the account no\n");
		scanf("%d",&number);
		if(number==c.account_no)
		{
		printf("\n__________Enter your pin:__________\n\n");
		scanf("%d",&dpin);
	  	 if(c.pin==dpin)
	 	   	{
			printf("Enter the consumer number\n");
			scanf("%d",&no);
			printf("Enter the amount to be paid\n");
			scanf("%f",&amount);
			c.balance-=amount;
			if(amount>c.balance)
			{
			printf("Not enough money to withdraw\n");
			}
			else
			{
			fseek(f,(-1)*sizeof(c),SEEK_CUR);
			fwrite(&c,sizeof(c),1,f);
			printf("Bill paid sucessfully!\n");
			printf("Your current balance=%f\n",c.balance);			
			}
		}
		else
		printf("The account no does not exsist\n");
	}
	fclose(f);
	trans();
}
}
void ph()
{
int dpin,number,no;
	struct customer c;
	float amo;
	FILE *f;
	f=fopen("bank","r+b");  
	printf("\n_________________Phone bill payment_________________\n\n"); 
	while(fread(&c,sizeof(c),1,f)==1)
	 {
		printf("Enter the account no\n");
		scanf("%d",&number);
		if(number==c.account_no)
		{
		printf("\n__________Enter your pin:__________\n\n");
		scanf("%d",&dpin);
	  	 if(c.pin==dpin)
	 	  {
			printf("Enter the phone number\n");
			scanf("%d",&no);
			printf("Enter the amount to be paid\n");
			scanf("%f",&amo);
        		c.balance-=amo;
			if(amo>c.balance)
			{
			printf("Not enough money to withdraw\n");
			}
			else
			{
			fseek(f,(-1)*sizeof(c),SEEK_CUR);
			fwrite(&c,sizeof(c),1,f);
			printf("Bill paid sucessfully!\n");
			printf("Your current balance=%f\n",c.balance);				
			}
		}
		else
		printf("The account no does not exsist\n");
		}
	}
	fclose(f);
	trans();
}


void transfer()
{
int dpin,number,no;
	struct customer c;
	float amount;
	FILE *f;
	f=fopen("bank","r+b");  
	printf("\n________________Transfer Amount_________________\n\n"); 
	while(fread(&c,sizeof(c),1,f)==1)
	 {
		printf("Enter the account no\n");
		scanf("%d",&number);
		if(number==c.account_no)
		{
		printf("\n__________Enter your pin:__________\n\n");
		scanf("%d",&dpin);
	  	 if(c.pin==dpin)
	 	  {
			printf("Enter the account number to which you want to transfer amount\n");
			scanf("%d",&no);
			printf("Enter the amount to be transfered\n");
			scanf("%f",&amount);
        		c.balance-=amount;
			if(amount>c.balance)
			{
			printf("Not enough money to withdraw\n");
			}
			else
			{
			fseek(f,(-1)*sizeof(c),SEEK_CUR);
			fwrite(&c,sizeof(c),1,f);
			printf("Transfer sucessfull!\n");
			printf("Your current balance=%f\n",c.balance);				
			}
		}
}
		else
		printf("The account no does not exsist\n");

		}
	fclose(f);
	trans();

}
