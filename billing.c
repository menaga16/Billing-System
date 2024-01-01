#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

 void input();
 void writefile();
 void search();
 void output();
 struct product
 {
     char name[100];
     int price;
 };
 struct product c[5]={{"scale",10},{"rubber",5},{"small_note",25},{"long_note",35},{"pen",15}};
 struct date{
	   int month;
	   int day;
	   int year;
	   };

  struct account {
	int number;
	char name[100];
	int acct_no;
	//int mobile_no;
	char street[100];
	char city[100];
	char acct_type;
	float oldbalance;
	float newbalance;
	float payment;
	struct date lastpayment;
  }customer;
  int tl,sl,ts;
 void main()
	{
	  int i,n;
	  char ch;
      struct product c[5]={{"scale",10},{"rubber",5},{"small_note",25},{"long_note",35},{"pen",15}};
      //_setcursortype(_NOCURSOR);
      printf("             WELCOME TO MAR STATIONARY SHOP\n");
      printf("      products available in our company\n");
      printf("1. scale 10\n");
      printf("2. rubber 5\n");
      printf("3. small_note 25\n");
      printf("4. long_note 30\n");
      printf("5. pen 15\n");

	  printf("   CUSTOMER BILLING SYSTEM:\n\n");
	  printf("===============================\n");
	  printf("\n1:    to calculate bill on shopping\n");
	  printf("2:    to search customer account\n");
	  printf("3:    exit\n");
	  printf("\n================================\n");
	  do{
	       printf("\nselect what do you want to do?");
	       ch=getche();
	  }while(ch<='0' || ch>'3');
	  switch(ch){
		case '1':
			printf("\nhow many customer accounts?");
			scanf("%d",&n);
			for(i=0;i<n;i++){
				input();
				if(customer.payment>0)
					customer.acct_type=(customer.payment<0.1*customer.oldbalance)? 'O': 'D';
				else
					customer.acct_type=(customer.oldbalance>0)?'D' : 'C';
				customer.newbalance=customer.oldbalance + customer.payment;
				writefile();
			}
			main();
		case '2':
			printf("search by what?\n");
			printf("\n1 --- search by customer number\n");
			printf("2 --- search by customer name\n");
			search();
			ch=getche();
			main();
		case '3':
			exit(1);
	  }
 }


   void input()
	{
	  int n,i,j;
	  float gst=0.18,amt;
	  int pr[10],qt[100],sub[100],total=0;
	  char item[10][100];
	  FILE *fp=fopen("jpms.dat","rb+");
	  fseek (fp,0,SEEK_END);
	  tl=ftell(fp);
	  sl=sizeof(customer);
	  ts=tl/sl;
	  fseek(fp,(ts-1)*sl,SEEK_SET);
	  fread(&customer,sizeof(customer),1,fp);
	  printf("\ncustomer no:%d\n",++customer.number);
	  fclose(fp);
	  printf("         Account number:");
	  scanf("%d",&customer.acct_no);
	  printf("\n       Name:");
	  scanf("%s",customer.name);
	  //printf("\n       mobile no:");
	  //scanf("%d",&customer.mobile_no);
	  printf("         Street:");
	  scanf("%s",customer.street);
	  printf("         City:");
	  scanf("%s",customer.city);
	  printf("enter number of items purchased :");
	  scanf("%d",&n);
	  for(i=0;i<n;i++)
      {
          printf("enter item name: ");
          scanf("%s",item[i]);
          printf("enter quantity:");
          scanf("%d",&qt[i]);
      }
      for(i=0;i<n;i++)
      {
          for(j=0;j<5;j++)
          {
              if(strcmp(item[i],c[j].name)==0)
              {
                  pr[i]=c[j].price;
              }
          }
      }
      for(i=0;i<n;i++)
      {
          sub[i]=pr[i]*qt[i];
          total+=sub[i];
      }
      amt=total*gst+total;

	  printf("         Previous balance:");
	  scanf("%f",&customer.oldbalance);

	  //printf("         Current payment:");
	  customer.payment=amt;
	  //scanf("%f",&customer.payment);
	  printf("         Payment date(mm/dd/yyyy):");
	  scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
	  printf("\n \n");
	  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	  printf("%50s\n","MAR stationary shop");
	  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	  printf("ncustomer no:%d\n Account number:%d\n Street:%s\n City:%s\n",customer.number,customer.acct_no,customer.street,customer.city);
      printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
      printf("%-14s %-7s %-7s %-7s \n","item name","price","quantity","subtotal");
      for(i=0;i<n;i++)
      {
          printf("%-8s \t%d\t %d\t %d\t\n",item[i],pr[i],qt[i],sub[i]);
      }
      printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
      printf("%31s: %d\n","total",total);
      printf("%31s: 0.18\n","GST");
      printf("%31s: %.2f\n","amt",amt);
      printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	  printf("\n \n \n");
	  return;
   }

   void writefile()
   {
	  FILE *fp;
	  fp=fopen("jpms.dat","ab+");
	  fwrite(&customer,sizeof(customer),1,fp);
	  fclose(fp);
	  return;
   }

   void search()
   {
	 char ch;
	 char nam[100];
	 int n,i,m=1;
	 FILE *fp;
	 fp=fopen("jpms.dat","rb+");
	 do{
		printf("\nenter your choice:");
		ch=getche();
	 }while(ch!='1' && ch!='2');
	 switch(ch){
	      case '1':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    do{
			printf("\nchoose customer number:");
			scanf("%d",&n);
			if(n<=0 || n>ts)
			printf("\nenter correct\n");
			else{
			    fseek(fp,(n-1)*sl,SEEK_SET);
			    fread(&customer,sl,1,fp);
			    output();
			}
			printf("\n\nagain?(y/n)");
			ch=getche();
		    }while(ch=='y');
		    fclose(fp);
		    break;
	      case '2':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    fseek(fp,(ts-1)*sl,SEEK_SET);
		    fread(&customer,sizeof(customer),1,fp);
		    n=customer.number;

		    do{
			printf("\nenter the name:");
			scanf("%s",nam);
			fseek(fp,0,SEEK_SET);
			for(i=1;i<=n;i++)
			{
			     fread(&customer,sizeof(customer),1,fp);
			     if(strcmp(customer.name,nam)==0)
			     {
				output();
				m=0;
				break;
			     }
			}
			if(m!=0)
			printf("\n\ndoesn't exist\n");
			printf("\nanother?(y/n)");
			ch=getche();
		    }while(ch=='y');
		    fclose(fp);
	      }
	      return;
	 }



   void output()
	 {
	   printf("\n\n    Customer no    :%d\n",customer.number);
	   printf("    Name 	   :%s\n",customer.name);
	   //printf("    Mobile no      :%.f\n",customer.mobile_no);
	   printf("    Account number :%d\n",customer.acct_no);
	   printf("    Street         :%s\n",customer.street);
	   printf("    City           :%s\n",customer.city);
	   printf("    Old balance    :%.2f\n",customer.oldbalance);
	   printf("    Current payment:%.2f\n",customer.payment);
	   printf("    New balance    :%.2f\n",customer.newbalance);
	   printf("    Payment date   :%d/%d/%d\n\n",customer.lastpayment.month,customer.lastpayment.day,customer.lastpayment.year);
	   printf("    Account status :");
	   //textcolor(128+RED);
	   switch(customer.acct_type)
	      {
	      case 'C':
		 printf("CURRENT\n\n");
		 break;
	      case 'O':
		 printf("OVERDUE\n\n");
		 break;
	      case 'D':
		 printf("DELINQUENT\n\n");
		 break;
	      default:
		 printf("ERROR\\n\n");
	      }
	      //textcolor(WHITE);
	      return;
	   }
