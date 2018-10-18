#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>

int n,m,checkc,checkv;        //no. of candidates,no.of voters,check variables

char pass[22];                //stores password

fstream INcheckc,INcheckv,INofile;  /*INcheckc,INcheckv-objects to check   						whether been declared before or 							not.INofile-object that stores or is 						used to write voter and                						candidate details*/


void mainscrn();              //Function Prototype(defined below)
void getpassword();           //gets password from user
int checkpassword();          //checks whether password is correct or not

class Voter                   //Class definition for voters
{
   char name[35],Class[5],ch1;//ch1-checks whether a voter has voted or not
   int uid;                   //Unique Identification Number of a voter
   public:
   Voter()
   {
      ch1='n';
      uid=0;
   }

   void changech1()           //to change the value of ch1
   {
     ch1='y';
   }

   void fixvoter()
   {
     clrscr();
     cout<<"\n\nEnter name\n";
     gets(name);
     cout<<"\nEnter class\n";
     gets(Class);
     cout<<"\nEnter voter uid(THE VOTER UID MUST NOT BE FORGOTTEN)\n";
     cin>>uid;
   }

   int getuid()
   {
     return uid;
   }

   char Returnch1()
   {
     return ch1;
   }
   void showvoter()
   {
     cout<<"\nNAME : "<<name;
     cout<<"\nCLASS: "<<Class;
     cout<<"\nVOTER UID   : "<<uid;
   }
};

class Candidate               //Class definition for Candidate
{

   char name[35],Class[5],post[35];
   int id,totvot;            //id-unique identification for candidate
   public:
   Candidate()
   {
     totvot=0;
     id=0;
   }

   void fixcandidate()
   {
     clrscr();
     cout<<"\nIn the following order:-\nSchool leader post-male candidates;female candidates\n";
     cout<<"Arts leader post-male candidates;female candidates\n";
     cout<<"Sports leader post-male candidates;female candidates\n";
     cout<<"Magazine Editor post-male candidates;female candidates\n";
     cout<<"\n\nEnter name\n";
     gets(name);
     cout<<"\nEnter class\n";
     gets(Class);
     cout<<"\nEnter post\n";
     gets(post);
     cout<<"\nEnter candidate id\n";
     cin>>id;
   }

   int getid()
   {
     return id;
   }

   void showcandidate()
   {
     cout<<name<<"\t\t";
     cout<<Class<<"\t\t";
     cout<<post<<"\t\t";
     cout<<id;
   }

   void votemodify()
   {
     totvot++;
   }

   int getvote()
   {
     return totvot;
   }

};

class Initialization          //Class used to fix candidates and voters
{

   fstream INnumberfile,nvfile;  //stores the total number of candidates and voters
   Candidate c[50];
   Voter v[50];
   public:
   void initializepoll();

}I1;

void Initialization ::initializepoll()
{
   int count=0;                      //FOR COUNTING NO. OF WRONG ATTEMPTS
   POLL_OFF_MENU:
   getpassword();
   int check=checkpassword();
   if(check==1)
   {
     char ch;
     int choice;
     SUB_MENU:
     clrscr();
     cout<<"\n\t\tWELCOME POLLING OFFICER";
     cout<<"\n\t\t------------------------";
     cout<<"\nA: FIX CANDIDATES\n";
     cout<<"\nB: FIX VOTERS\n";
     cout<<"\nC: MODIFY CANDIDATES\n";
     cout<<"\nD: INITIALIZE POLLING\n";
     cout<<"\nENTER YOUR CHOICE\n";
     cout<<"\n\n\n\n\n\n\n PRESS ESC FOR MAIN MENU";
     ch=getch();
     choice=(int)ch;  //For getting the ASCII code of the character inputted
     switch(choice)
     {
	case 97:
	case 65:FIXC:
		clrscr();
		INofile.open("cand.dat",ios::out|ios::binary|ios::app);
		INnumberfile.open("number.dat",ios::app|ios::out);
		cout<<"\n\t\tFIX CANDIDATES";
		cout<<"\n\t\t--------------\n";
		if(checkc==1)       /*To check whether candidates have been              						fixed or not*/
		{
		  cout<<"\n\nCandidates already fixed";
		  INnumberfile>>n;
		  for(int i=0;i<n;i++)
		     INofile.read((char*)&c[i],sizeof(c[i]));
		  for(i=0;i<n;i++)
		     c[i].showcandidate();
		  INnumberfile.close();
		  INofile.close();
		  INcheckc.close();
		  goto SUB_MENU;
		}
		else
		{
		  checkc=1;
		  cout<<"\nEnter no. of candidates:\n";
		  cin>>n;
		  INnumberfile<<n<<'\n';
		  for(int i=0;i<n;i++)
		  {
		     cout<<"\n\nCANDIDATE NO."<<i+1;
		     c[i].fixcandidate();
		     INofile.write((char*)&c[i],sizeof(c[i]));
		  }
		  INcheckc<<checkc<<'\n';
		}
		cout<<"\n\nALL CANDIDATES SUCCESFULLY STORED!\nPRESS ANY KEY  			TO CONTINUE";
		getch();
		INofile.close();
		INnumberfile.close();
		INcheckc.close();
		goto SUB_MENU;

	case 98:
	case 66:FIXV:
		clrscr();
		nvfile.open("voterno.dat",ios::out|ios::app);
		INofile.open("voter.dat",ios::out|ios::binary|ios::app);
		cout<<"\n\t\tFIX VOTERS";
		cout<<"\n\t\t----------\n";
		if(checkv==1)        /*To check whether voters have               							been fixed or not*/
		{
		  cout<<"\n\t\tVoters already fixed";
		  nvfile>>m;
		  for(int i=0;i<m;i++)
		    INofile.read((char*)&v[i],sizeof(v[i]));
		  for(i=0;i<m;i++)
		    v[i].showvoter();
		  nvfile.close();
		  INofile.close();
		  INcheckv.close();
		  goto SUB_MENU;
		}
		else
		{
		  checkv=1;
		  cout<<"\nEnter no. of  voters:\n";
		  cin>>m;
		  nvfile<<m<<'\n';
		  nvfile.close();
		  for(int i=0;i<m;i++)
		  {
		    cout<<"\n\nVOTER NO."<<i+1;
		    v[i].fixvoter();
		    INofile.write((char*)&v[i],sizeof(v[i]));
		  }
		  INcheckv<<checkv<<'\n';
		  cout<<"\n\nALL VOTERS SUCCESFULLY STORED!\nPRESS ANY 				KEY TO CONTINUE";
		  getch();
  INofile.close();
		  INcheckv.close();
		  goto SUB_MENU;
		}

	case 99:
	case 67: clrscr();
		 char choice;
		 int cid,pos,checkid;
		 INofile.open("cand.dat",ios::app|ios::binary);
		 if(!INofile)
		 {
		   cout<<"\n\n\aCAN'T OPEN 'Candidate.txt' FILE\a";
		   getch();
		   exit(0);
		 }
		 if(checkc==0)
		 {
cout<<"\nCandidates not yet fixed\nPress any key to fix            candidates";
getch();
		   goto FIXC;
		 }
		 MODIFY:
		 clrscr();
		 cout<<"\n\n\t\t\tMODIFY CANDIDATE\n";
		 cout<<"\t\t\t-------------------\n";
		 cout<<"\n\nDisplaying candidates stored on file";
		 cout<<"\nSl.No\t NAME\t\t CLASS\t\t POST\t ID";
		 for(int i=0;i<n;i++)
		 {
		   INofile.read((char*)&c[i],sizeof(c[i]));
		   cout<<"\n"<<i+1<<":\t";
		   c[i].showcandidate();
		 }
		 INofile.close();
		 INofile.open("cand.dat",ios::app|ios::binary);
		 do
		 {
		   for(i=0;i<n;i++)
		   {
		     cout<<"\nEnter the id of the candidate whose 					     details is to be modified\n";
		     cin>>cid;
		     if(c[i].getid()==cid)
		     {
			cout<<"\nMODIFY NOW\n";
			c[i].fixcandidate();
			INofile.write((char*)&c[i],sizeof(c[i]));
			break;
		     }
		     else
		     {
			cout<<"\nNo candidate found with id "<<cid;
			cout<<"\nPlease try again.Press any key to 						continue\n";
			getch();
			goto MODIFY;
		     }
		 }
		 cout<<"\nDo you want to continue(y or n)?\n";
		 cin>>choice;
		 }while((choice=='y')||(choice=='Y'));
		 goto SUB_MENU;


	case 100:
	case 68: clrscr();
		 cout<<"\nChecking candidates.....\n";
		 for(i=0;i<9876;i++);
		 if(checkc==1)
		    cout<<"\nCandidates found!";
		 else
		 {
		    cout<<"\n\aPlease fix candidates.Press any key\n";
		    getch();
		    goto FIXC;
		 }
		 cout<<"\nChecking voters.....\n";
		 for(i=0;i<9876;i++);
		 if(checkv==1)
		 {
		    cout<<"\nVoters found!";
		    cout<<"\n\nPress any key to continue";
		    getch();
		    mainscrn();
		 }
		 else
		 {
		     cout<<"\n\aPlease fix Voters.Press any key\n";
		     getch();
		     goto FIXV;
		 }
		 break;


	case 27: mainscrn();
		 break;

	default:cout<<"\n\aWrong Choice!!.Press any key to try 					again.";
		getch();
		goto SUB_MENU;
     }

   }
   else
   {
      if(count==3)
      {
	 cout<<"\n\n\t\t3 wrong attempts\nTERMINATING...\a\a";
	 for(int i=0;i<9435;i++);
	 exit(0);
      }
      else
      {
	 cout<<"\n\n\n\t\aWRONG PASSWORD!!TRY AGAIN";
	 ++count;
	 goto POLL_OFF_MENU;
      }
   }
}

class Election                     //This class conducts election and decides winners
{
   Candidate c[22],winner1,winner2;
   ifstream Eifile;                //Used to store candidate details
   ofstream winofile;              //Used to store winner details

   void INIL_EL1()                 //This functions read candidate details to Eifile
   {
     Eifile.open("cand.dat",ios::app,ios::binary);
     Eifile.seekg(0);
     for(int i=0;i<22;i++)
       Eifile.read((char*)&c[i],sizeof(c[i]));
   }

   void CHECK_EL1()                /*This function checks 								whether the candidate have 							been initialized or not*/
   {
     if(c[0].getid()==0)
     {
       cout<<"\nCandidates not initialized\nFatal error\n\aPress any key\n";
       getch();
       exit(0);
     }
   }
   public:
   void Conduct_e1();              //Prototype of the function that conducts election
   void Election1()                //Links winofile with Winner.dat file in output mode
   {
      winofile.open("Winner.dat",ios::out|ios::binary);
   }

   int el1(int x,int y)            /*Conducts election for 									school leaders*/
   {
      int choice;
      cout<<"\nEnter your choice: ";
      cin>>choice;
      switch(choice)
      {
	 case 1:c[x].votemodify();
		break;

	 case 2:c[y].votemodify();
		break;

	 default:cout<<"\nInvalid Choice.\nPress Any KEY to try 					again\n\n";
		 getch();
		 return 0;
      }
      return 1;
   }

   int el2(int x,int y,int z)      /*Conducts election for 							arts,sports and magazine leaders*/
   {
      int choice;
      cout<<"\nEnter your choice: ";
      cin>>choice;
      switch(choice)
      {
	 case 1:c[x].votemodify();
		break;

	 case 2:c[y].votemodify();
		break;

	 case 3:c[z].votemodify();
		break;

	 default:cout<<"\nInvalid Choice.\nPress Any KEY to try again";
		 getch();
		 return 0;
      }
      return 1;
   }

   void win1(int x,int y)           /*Decides winners for school 							leader post*/
   {
      if(c[x].getvote()>c[y].getvote())
	    winner1=c[x];
      else
	    winner1=c[y];
      winofile.write((char*)&winner1,sizeof(winner1));
   }

   void win2(int x,int y,int z)      /*Decides winners for other 							   posts*/
   {
      winner2 =c[x];
      for(int i=y;i<z;i++)
      if(c[i].getvote()>winner2.getvote())
	 winner2=c[i];
      winofile.write((char*)&winner2,sizeof(winner2));
   }

}E1;
void Election ::Conduct_e1()        //Function which conducts election
{
   INIL_EL1();
   CHECK_EL1();
   Election1();
   int n,checkno=1,j;               //checkno decides when the voting process should end
   ifstream numberfile("number.dat",ios::app);
   numberfile>>n;                   /*n stores number of 									candidates*/
   CANDIDATE1:                      //SCHOOL LEADER BOY
   for(int i=0;i<2;i++,checkno++)
   {
      cout<<i+1<<":";
      c[i].showcandidate();
      cout<<"\n";
   }
   int a1=el1(0,1);
   win1(0,1);
   if(a1==0)
     goto CANDIDATE1;
   checkno+=2;
   if(checkno>=n)
   {
      cout<<"\nThank you for voting\nPress any key to continue";
      getch();
      mainscrn();
   }
   CANDIDATE2:                      //SCHOOL LEADER GIRL
   for(i=2,j=1;i<4;i++,j++)
   {
      cout<<j<<":";
      c[i].showcandidate();
      cout<<"\n";
   }
   int a2=el1(2,3);
   win1(2,3);
   if(a2==0)
      goto CANDIDATE2;
   checkno+=2;
   if(checkno>=n)
   {
     cout<<"\nThank you for voting\nPress any key to continue";
     getch();
     mainscrn();
   }
   CANDIDATE3:                      //ARTS LEADER BOY
   for(i=4,j=1;i<7;i++,j++)
   {
     cout<<j<<":";
     c[i].showcandidate();
     cout<<"\n";
   }
   int a3=el2(4,5,6);
   win2(4,5,6);
   if(a3==0)
     goto CANDIDATE3;
   checkno+=3;
   if(checkno>=n)
   {
     cout<<"\nThank you for voting\nPress any key to continue";
     getch();
     mainscrn();
   }
   CANDIDATE4:                      //ARTS LEADER GIRL
   for(i=7,j=1;i<10;i++,j++)
   {
     cout<<j<<":";
     c[i].showcandidate();
     cout<<"\n";
   }
   int a4=el2(7,8,9);
   win2(7,8,9);
   if(a4==0)
      goto CANDIDATE4;
   checkno+=3;
   if(checkno>=n)
   {
      cout<<"\nThank you for voting\nPress any key to continue";
      getch();
      mainscrn();
   }
   CANDIDATE5:                      //SPORTS LEADER BOY
   for(i=10,j=1;i<13;i++,j++)
   {
      cout<<j<<":";
      c[i].showcandidate();
      cout<<"\n";
   }
   int a5=el2(10,11,12);
   win2(10,11,12);
   if(a5==0)
     goto CANDIDATE5;
   checkno+=3;
   if(checkno>=n)
   {
     cout<<"\nThank you for voting\nPress any key to continue";
     getch();
     mainscrn();
   }
   CANDIDATE6:                      //SPORTS LEADER GIRL
   for(i=13,j=1;i<16;i++,j++)
   {
     cout<<j<<":";
     c[i].showcandidate();
     cout<<"\n";
   }
   int a6=el2(13,14,15);
   win2(13,14,15);
   if(a6==0)
     goto CANDIDATE6;
   checkno+=3;
   if(checkno>=n)
   {
     cout<<"\nThank you for voting\nPress any key to continue";
     getch();
     mainscrn();
   }
   CANDIDATE7:                      //MAGAZINE EDITOR BOY
   for(i=16,j=1;i<19;i++,j++)
   {
     cout<<j<<":";
     c[i].showcandidate();
     cout<<"\n";
   }
   int a7=el2(16,17,18);
   win2(16,17,18);
   if(a7==0)
     goto CANDIDATE7;
   checkno+=3;
   if(checkno>=n)
   {
     cout<<"\nThank you for voting\nPress any key to continue";
     getch();
     mainscrn();
   }
   CANDIDATE8:                      //MAGAZINE EDITOR GIRL
   for(i=19,j=1;i<22;i++,j++)
   {
     cout<<j<<":";
     c[i].showcandidate();
     cout<<"\n";
   }
   int a8=el2(19,20,21);
   win2(19,20,21);
   if(a8==0)
     goto CANDIDATE8;
   checkno+=3;
   if(checkno>=n)
   {
     cout<<"\nThank you for voting\nPress any key to continue";
     getch();
     mainscrn();
   }
}


class Election_Result           //This class stores the winner details
{
   ifstream win;
   Candidate c[8];
   public:
   void  result()               //Function which declares the winners
   {
      win.open("Winner.dat",ios::app|ios::binary);
      for(int i=0;i<8;i++)
	 win.read((char*)&c[i],sizeof(c[i]));
      cout<<"\n\n\n\t\t\tThe Winners Are:---\n\n";
      for(i=0;i<8;i++)
      {
	c[i].showcandidate();
	cout<<"\n";
      }
   }
}R1;

void getpassword()              //Function gets the password from user
{
   int temp;
   cout<<"\n\tEnter Password (MAX-20): " ;
   for ( int i=0 ; i<21 ; i++)
   {
       pass[i] = getch ();
       temp = pass[i] ;   // Saving ASCII code to temp.
       if ( temp == 8 )
       {
	  temp = pass[0] ;
	  if ( temp == 8 )
	  {
	    i = -1 ;
	    continue ;
	  }
	  pass[i-1] = '\0' ;
	  clrscr ();
	  cout<<"\n\tEnter Password (MAX-20): ";
	  for ( int j = 0 ; j< strlen ( pass ) ; j++ )
	  cout<<"*";
	  i -= 2 ;
       }
       else if ( temp == 13 )
       {
	  pass[i] = '\0' ;
	  break ;
       }
       else if ( i == 20 )
       {
	  i = 19;
	  continue ;
       }
       else
	  cout<<"*";
   }
   pass[i] = '\0' ;
}

int checkpassword()            /*Checks the password enterd by                 						the user is correct or not*/
{
   if(strcmp(pass,"POLLING")==0)
       return 1;
   else
       return 0;
}

void mainscrn()                  //FOR MAIN MENU DISPLAY
{
  MAINMENU:
  clrscr();
  int ch;
  cout<<"\n\t\t\t\tCYBER POLLING\n";
  cout<<"\t\t\t\t-------------";
  cout<<"\n1.Initialize Polling(Only available to polling 			officer)\n";
  cout<<"\n2.Voting\n";
  cout<<"\n3.Result Declaration(Only available to polling 			officer)\n";
  cout<<"\n4.Exit from program\n";
  cout<<"\nEnter your choice:  ";
  cin>>ch;
  int flag=0;
  switch(ch)
  {
      case 1:I1.initializepoll();
	     break;

      case 2:VOTER:
	     INofile.close();
	     Voter v[50];
	     ifstream file("voter.dat",ios::app);
	     int vid,vno,count=0;
	     if(!file)
	     {
	       cout<<"\nCannot find voter.dat\nFatal error\n\aPress 				any key\n";
	       getch();
	       exit(0);
	     }
	     clrscr();
	     for(int i=0;i<m;i++)
		file.read((char*)&v[i],sizeof(v[i]));
	     file.close();
	     cout<<"\n\t\t\tVOTING";
	     cout<<"\n\t\t\t--------";
	     cout<<"\n\nEnter voter id\n";
	     cin>>vid;
	     for(i=0;i<m;i++)
	     {
	       if(v[i].Returnch1()=='y')
	       {
		  cout<<"\nAlready voted\n\a";
		  getch();
		  mainscrn();
	       }
	     }
	     for(i=0;i<m;i++)
	     {
	       if(vid==v[i].getuid())
	       {
		 clrscr();
		 cout<<"\n\nVOTER DETAILS";
		 v[i].showvoter();
		 v[i].changech1();
		 cout<<"\n\n";
		 E1.Conduct_e1();

	       }
	     }
	     cout<<"\nINVALID VOTER ID.\n\aPress Enter to try 					again\n";
	     getch();
	     count++;
	     if(count==2)
	     {
	       cout<<"\nMany Wrong attempts\n\aTerminating";
	       getch();
	       mainscrn();
	     }
	     goto VOTER;

      case 3:int countwrg=0;
	     RESULT:
	     clrscr();
	     int checkpswd;       /*Stores the value returned by 							checkpassword()*/
	     cout<<"\n\t\t\t\tRESULT DECLARATION";
	     cout<<"\n\t\t\t\t-------------------";
	     getpassword();
	     checkpswd=checkpassword();
	     if(checkpswd==0)
	     {
		cout<<"\nWrong Password!!\a";
		cout<<"\nPress Any key to try again.";
		getch();
		countwrg++;
		if(countwrg==3)
		{
		   cout<<"\n\n\t\t3 WRONG ATTEMPTS
                     a\a...\n\t\tTerminating...";
		   getch();
		   exit(0);
		}
		goto RESULT;
	     }
	     R1.result();
	     break;

      case 4:clrscr();
	     textattr(2);
	     textcolor(1);
	     cout<<"\n\n\n\tThank you for using.Press any key to              				quit\n\n\n";
	     cout<<"\n\n\n\n\n\n\t\t\t\tALL RIGHTS RESERVED";
	     getch();
	     exit(0);

      default:cout<<"\nWrong Entry.";
	      flag=1;


  }
  if(flag==1)
  {
     cout<<"Press any key to try again";
     getch();
     goto MAINMENU;
  }
}

void main()                       //main function
{
   clrscr();
   INcheckc.open("check1.dat",ios::nocreate);
   if(INcheckc)
   {
      checkc=1;
      INcheckc<<checkc<<'\n';
   }
   if(!INcheckc)
   {
      fstream INcheckc("check1.dat",ios::app);
      INcheckc<<0<<'\n';
      INcheckc.close();
   }
   INcheckc>>checkc;
   INcheckv.open("check2.dat",ios::nocreate);
   if(INcheckv)
   {
      checkv=1;
      INcheckv<<checkv<<'\n';
   }
   if(!INcheckv)
   {
      fstream INcheckv("check2.dat",ios::app);
      INcheckv<<0<<'\n';
      INcheckv.close();
   }
   INcheckv>>checkv;
   mainscrn();
   getch();
}

