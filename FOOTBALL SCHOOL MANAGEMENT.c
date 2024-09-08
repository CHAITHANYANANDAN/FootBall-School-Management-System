#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

FILE *fp,*ft;
int j=0;

struct student
{
        char name[25];
        int player_no;
        char gender;
        int age;
        struct
        {
                int day;
                int mon;
                int year;
        }dob;
        char home_address[50];
        char school_address[50];
        char experienced_before;
        char phone[15];
        char email[20];
};

//List of function prototypes
int leap(int);
int date(int,int,int);
void login();
void add_player(FILE *fp);
void player_list(FILE *fp);
void search_player(FILE *fp);
void edit(FILE *fp);
void delete_player(FILE *fp);
void close();
void main_menu(FILE *fp);


int isDigit(char h[])
{
    for(int i=0;i<strlen(h);i++)
    {
        if(isdigit(h[i])==0)
        {
            return 0;
            break;
        }
    }
}
//Main function
void main()
{
    if((fp=fopen("file1.txt","rb+"))==NULL)
    {
        if((fp=fopen("file1.txt","wb+"))==NULL)

        printf("Cannot open the file");
        return 0;

    }
    else
    {

        login();
        main_menu(fp);
    }
}

//To validate date
int leap(int year)
{
    if (year % 400 == 0)
        return 1;
    else if (year % 100 == 0)
        return 0;
   else if (year % 4 == 0)
        return 1;
   else
        return 0;
}

int date(int dd,int mm,int yy)
{
    if(yy>=1900 && yy<=9999)
    {
        if(mm>=1 && mm<=12)
        {
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                return 1;
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                return 1;
            else if((dd>=1 && dd<=28) && (mm==2))
                return 1;
            else if(dd==29 && mm==2 && (leap(yy)==1))
                return 1;
            else
                return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -2;
    }
}


//To add player data
void add_player(FILE *fp)
{
    char another='y',ch;
    int tempno;
    struct student s;
    int i,flag=0;
    int a[3];

    fseek(fp,0,SEEK_END);
    while(another=='y'||another=='Y')
    {
        printf("\n\n");


        printf("\t\t\tEnter Registration number: ");
        scanf("%d",&s.player_no);
        tempno=s.player_no;
        fseek(fp,0,SEEK_SET);
        while((fread(&s,sizeof(s),1,fp))==1)
        {
            if(tempno==s.player_no)
            {
                printf("\t\t\tRegistration no. matches with existing data\n\t\t\tEnter appropriate registration no.\n\t\t\t");
                scanf("%d",&s.player_no);
                tempno=s.player_no;
                continue;
            }
        }
        fseek(fp,0,SEEK_END);

        printf("\t\t\tEnter Full Name of Student : ");
        scanf("%s",s.name);
        for(i=0;i<strlen(s.name);i++)
        {
            ch=s.name[i];
            if(!(isalpha(ch))&&(ch!=32&&ch!='.'))
            {
                do
                {
                    printf("\t\t\tEnter appropriate name\n");
                    printf("\t\t\tEnter name: ");
                    scanf("%s",s.name);
                    ch=s.name[i];
                }
                while(!(isalpha(ch))&&(ch!=32&&ch!='.'));

            }
        }

        printf("\t\t\tEnter the gender[Female - F/ Male - M]: ");
        getchar();
        scanf("%c",&s.gender);
        fflush(stdin);
        if(s.gender!='f'&&s.gender!='F'&&s.gender!='M'&&s.gender!='m')
        {
            do
            {
                printf("\t\t\tEnter appropriate characters");
                printf("\t\t\tEnter the gender[Female - F/ Male - M]: ");
                s.gender=getchar();
                fflush(stdin);
            }
            while(s.gender!='f'&&s.gender!='F'&&s.gender!='M'&&s.gender!='m');
        }
        fflush(stdin);

        printf("\t\t\tEnter age: ");
        scanf("%d",&s.age);


        printf("\t\t\tEnter date of birth (DD/MM/YYYY): ");
        scanf("%d",&s.dob.day);
        scanf("%d",&s.dob.mon);
        scanf("%d",&s.dob.year);
        if(date(s.dob.day,s.dob.mon,s.dob.year)==0||date(s.dob.day,s.dob.mon,s.dob.year)==-1||date(s.dob.day,s.dob.mon,s.dob.year)==-2)
        {
            do
            {
                printf("\t\t\tEnter valid date\n\t\t\t");
                scanf("%d",&s.dob.day);
                scanf("%d",&s.dob.mon);
                scanf("%d",&s.dob.year);
            }
            while(date(s.dob.day,s.dob.mon,s.dob.year)==0||date(s.dob.day,s.dob.mon,s.dob.year)==-1||date(s.dob.day,s.dob.mon,s.dob.year)==-2);
        }
        fflush(stdin);

        printf("\t\t\tEnter Home address: ");
        fgets(s.home_address,55,stdin);
        fflush(stdin);

        printf("\t\t\tEnter Institution address: ");
        fgets(s.school_address,55,stdin);
        fflush(stdin);

        printf("\t\t\tDo you have prior experience[Yes - Y/ No - N]: ");
        scanf(" %c",&s.experienced_before);
        if(s.experienced_before!='y'&&s.experienced_before!='Y'&&s.experienced_before!='N'&&s.experienced_before!='n')
        {
            do
            {
                printf("\t\t\tEnter appropriate characters");
                printf("\t\t\tDo you have prior experience[Yes - Y/ No - N]: ");
                scanf(" %c",&s.experienced_before);
            }
            while(s.experienced_before!='y'&&s.experienced_before!='Y'&&s.experienced_before!='N'&&s.experienced_before!='n');
        }


        printf("\t\t\tEnter contact number: ");
        scanf("%s",s.phone);
        i=0;
        if((strlen(s.phone)!=10)||(s.phone[0]!='6'&&s.phone[0]!='7'&&s.phone[0]!='8'&&s.phone[0]!='9')||(isDigit(s.phone)==0))
        {
            do
            {
                printf("\t\t\tInvalid Number\n\t\t\tEnter contact number: ");
                scanf("%s",s.phone);
                i=0;
            }
            while((strlen(s.phone)!=10)||(s.phone[0]!='6'&&s.phone[0]!='7'&&s.phone[0]!='8'&&s.phone[0]!='9')||(isDigit(s.phone)==0));
        }

        printf("\t\t\tEnter mail id: ");
        fflush(stdin);
        fgets(s.email,25,stdin);

        fwrite(&s,sizeof(s),1,fp);

        printf("\n\n\t\t\tAdd another student?(Y/N)?");
        fflush(stdin);
        another=getchar();
        if(another!='y'&&another!='Y'&&another!='n'&&another!='N')
                    {
                        do
                        {
                            printf("\t\t\tEnter appropriate characters");
                            printf("\n\t\t\tAdd another student?(Y/N)\n\t\t\t");
                            fflush(stdin);
                            another=getchar();
                        }
                        while(another!='y'&&another!='Y'&&another!='n'&&another!='N');
                    }
    }
    main_menu(fp);
}


//To view list of players
void player_list(FILE *fp)
{
    struct student s;
    int i=0,siz=sizeof(s);

    rewind(fp);
    printf("\n\n");
    while((fread(&s,siz,1,fp))==1)
    {

        printf("\t\t\t%d. REGISTRATION NUMBER : %d",++i,s.player_no);
        printf("\t\t\tNAME : %s\t\t\t",s.name);
        printf("\n");
    }
    printf("\t\t\t");
    system("pause");
    main_menu(fp);
}

//To view a particular player data
void search_player(FILE *fp)
{
    int flag,siz,i;
    struct student s;
    char another='y';
    int tempno;

    siz=sizeof(s);

    while(another=='y'||another=='Y')
    {
        printf("\n\n");
        printf("\t\t\tEnter Registration Number: ");
        scanf("%d",&tempno);

        rewind(fp);

        while((fread(&s,siz,1,fp))==1)
        {
            if(s.player_no==tempno)
            {
                flag=1;
                break;
            }
        }

        if(flag==1)
        {
            printf("\t\t\tREGISTRATION NUMBER : %d\n",s.player_no);
            printf("\t\t\tNAME : %s\n",s.name);
            printf("\t\t\tGENDER : %c\n",s.gender);
            printf("\t\t\tAGE : %d\n",s.age);
            printf("\t\t\tDATE OF BIRTH : %d/%d/%d\n",s.dob.day,s.dob.mon,s.dob.year);
            printf("\t\t\tHOME ADDRESS : %s\n",s.home_address);
            printf("\t\t\tINSTITUTION ADDRESS:  %s\n",s.school_address);
            printf("\t\t\tPRIOR EXPERIENCE : %c\n",s.experienced_before);
            printf("\t\t\tMOBILE NO. : %s\n",s.phone);
            printf("\t\t\tMAIL ID : %s\n",s.email);
        }
        else
        {
            printf("\t\t\tPlayer Details Not Found");
            printf("\n");
        }


        printf("\t\t\tDo you want to see another student information? (Y/N)?");
        fflush(stdin);
        another=getchar();
        if(another!='y'&&another!='Y'&&another!='n'&&another!='N')
                    {
                        do
                        {
                            printf("\t\t\tEnter appropriate characters");
                            printf("\n\t\t\tDo you want to see another student information[Y/N]\n\t\t\t");
                            fflush(stdin);
                            another=getchar();
                        }
                        while(another!='y'&&another!='Y'&&another!='n'&&another!='N');
                    }

    }
    main_menu(fp);
}

//To update player data
void edit(FILE *fp)
{
    struct student s;
    char ch;
    char another='y';
    int i,flag=0,siz=sizeof(s),n;
    int tempno;

    printf("\n\n");
    printf("\n\n\t\t\tEnter Registration number of Student to edit the details : ");
    scanf("%d",&tempno);

    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        if(tempno==s.player_no)
        {
            flag=1;
            break;
        }
    }

    if(flag==1)
    {
        fseek(fp,-siz,SEEK_CUR);
        printf("\t\t\tRecord Found\n");
        printf("\t\t\tREGISTRATION NUMBER : %d\n",s.player_no);
        printf("\t\t\tNAME : %s\n",s.name);
        printf("\t\t\tGENDER : %c\n",s.gender);
        printf("\t\t\tAGE : %d\n",s.age);
        printf("\t\t\tDATE OF BIRTH : %d/%d/%d\n",s.dob.day,s.dob.mon,s.dob.year);
        printf("\t\t\tHOME ADDRESS : %s\n",s.home_address);
        printf("\t\t\tINSTITUTION ADDRESS :  %s\n",s.school_address);
        printf("\t\t\tPRIOR EXPERIENCE : %c\n",s.experienced_before);
        printf("\t\t\tMOBILE NO. : %s\n",s.phone);
        printf("\t\t\tMAIL ID : %s\n",s.email);


        while(another=='y'||another=='Y')
        {
            printf("\n\n");
            printf("\t\t\tLIST OF DETAILS\n");
            printf("\t\t\t(1)NAME\n\t\t\t(2)GENDER\n\t\t\t(3)AGE\n\t\t\t(4)DATE OF BIRTH\n\t\t\t(5)HOME ADDRESS\n\t\t\t(6)INSTITUTION ADDRESS\n\t\t\t(7)PRIOR EXPERIENCE\n\t\t\t(8)CONTACT NO.\n\t\t\t(9)MAIL ID\n");
            printf("\t\t\tEnter the appropriate number to edit the details\n\t\t\t");
            scanf("%d",&n);
                    switch(n)
                    {
                        case 1:
                        {
                            printf("\t\t\tEnter new name : ");
                            scanf("%s",s.name);
                            for(i=0;i<strlen(s.name);i++)
                            {
                                ch=s.name[i];
                                if(!(isalpha(ch))&&(ch!=32&&ch!='.'))
                                {
                                    do
                                    {
                                        printf("\t\t\tEnter appropriate name\n");
                                        printf("\t\t\tEnter name: ");
                                        scanf("%s",s.name);
                                        ch=s.name[i];
                                    }
                                    while(!(isalpha(ch))&&(ch!=32&&ch!='.'));
                                }
                            }
                            fflush(stdin);
                            break;
                        }
                        case 2:
                        {
                            printf("\t\t\tEnter the right gender[Female - F / Male - M]: ");
                            fflush(stdin);
                            scanf("%c",&s.gender);
                            if(s.gender!='f'&&s.gender!='F'&&s.gender!='M'&&s.gender!='m')
                            {
                                do
                                {
                                    printf("\t\t\tEnter appropriate characters");
                                    printf("\t\t\tEnter the gender[Female - F/ Male - M]: ");
                                    s.gender=getchar();
                                    fflush(stdin);
                                }
                                while(s.gender!='f'&&s.gender!='F'&&s.gender!='M'&&s.gender!='m');
                            }
                            break;
                        }
                        case 3:
                        {
                            printf("\t\t\tEnter right age: ");
                            scanf("%d",&s.age);

                            break;
                        }
                        case 4:
                        {
                            printf("\t\t\tEnter the right date of birth(DD/MM/YYYY): ");
                            scanf("%d",&s.dob.day);
                            scanf("%d",&s.dob.mon);
                            scanf("%d",&s.dob.year);
                            if(date(s.dob.day,s.dob.mon,s.dob.year)==0||date(s.dob.day,s.dob.mon,s.dob.year)==-1||date(s.dob.day,s.dob.mon,s.dob.year)==-2)
                            {
                                do
                                {
                                    printf("\t\t\tEnter valid date\n\t\t\t");
                                    scanf("%d",&s.dob.day);
                                    scanf("%d",&s.dob.mon);
                                    scanf("%d",&s.dob.year);
                                }
                                while(date(s.dob.day,s.dob.mon,s.dob.year)==0||date(s.dob.day,s.dob.mon,s.dob.year)==-1||date(s.dob.day,s.dob.mon,s.dob.year)==-2);
                            }
                            fflush(stdin);
                            break;
                        }
                        case 5:
                        {
                            printf("\t\t\tEnter new Home address: ");
                            fflush(stdin);
                            fgets(s.home_address,55,stdin);
                            break;
                        }
                        case 6:
                        {
                            printf("\t\t\tEnter Institution address: ");
                            fflush(stdin);
                            fgets(s.school_address,55,stdin);
                            break;
                        }
                        case 7:
                        {
                            printf("\t\t\tDo you have prior experience[Yes - Y/ No - N]: ");
                            scanf(" %c",&s.experienced_before);
                            if(s.experienced_before!='y'&&s.experienced_before!='Y'&&s.experienced_before!='N'&&s.experienced_before!='n')
                            {
                                do
                                {
                                    printf("\t\t\tEnter appropriate characters");
                                    printf("\t\t\tDo you have prior experience[Yes - Y/ No - N]: ");
                                    scanf(" %c",&s.experienced_before);
                                }
                                while(s.experienced_before!='y'&&s.experienced_before!='Y'&&s.experienced_before!='N'&&s.experienced_before!='n');
                            }
                            break;
                        }
                        case 8:
                        {
                            printf("\t\t\tEnter mobile number: ");
                            scanf("%s",s.phone);
                            i=0;
                            if((strlen(s.phone)!=10)||(s.phone[0]!='6'&&s.phone[0]!='7'&&s.phone[0]!='8'&&s.phone[0]!='9')||(isDigit(s.phone)==0))
                            {
                                do
                                {
                                    printf("\t\t\tInvalid Number\n\t\t\tEnter contact number: ");
                                    scanf("%s",s.phone);
                                    i=0;
                                }
                                while((strlen(s.phone)!=10)||(s.phone[0]!='6'&&s.phone[0]!='7'&&s.phone[0]!='8'&&s.phone[0]!='9')||(isDigit(s.phone)==0));
                            }
                            break;
                        }
                        case 9:
                        {
                            printf("\t\t\tEnter mail id: ");
                            fflush(stdin);
                            fgets(s.email,25,stdin);
                            break;
                        }
                        default:
                        {
                            printf("\t\t\tEnter appropriate numbers to edit details of the player");
                            break;
                        }
                    }
                    printf("\t\t\tDo you want to edit another detail[Y/N] ");
                    fflush(stdin);
                    another=getchar();
                    if(another!='y'&&another!='Y'&&another!='n'&&another!='N')
                    {
                        do
                        {
                            printf("\t\t\tEnter appropriate characters");
                            printf("\n\t\t\tDo you want to edit another detail[Y/N]\n\t\t\t");
                            fflush(stdin);
                            another=getchar();
                        }
                        while(another!='y'&&another!='Y'&&another!='n'&&another!='N');
                    }
        }

                fwrite(&s,sizeof(s),1,fp);
                printf("\t\t\tDo you want to edit any other player detail?[Y/N] ");
                fflush(stdin);
                another=getchar();
                if(another!='y'&&another!='Y'&&another!='n'&&another!='N')
                    {
                        do
                        {
                            printf("\t\t\tEnter appropriate characters");
                            printf("\n\t\t\tDo you want to edit another player detail[Y/N]\n\t\t\t");
                            fflush(stdin);
                            another=getchar();
                        }
                        while(another!='y'&&another!='Y'&&another!='n'&&another!='N');
                    }
                if(another=='Y'||another=='y')
                    edit(fp);


    }

    else
        printf("\t\t\tPlayer details not found\n");

    main_menu(fp);
}

//To remove player data
void delete_player(FILE *fp)
{
    struct student s;
    int flag=0,siz=sizeof(s);
    int tempno;

    if((ft=fopen("temp.txt","wb+"))==NULL)
    {
        printf("\t\t\tUnable to complete the deletion process");
        return fp;
    }

    printf("\n\n");
    printf("\t\t\tEnter Registration number of Student to Delete the Record\n");
    printf("\t\t\tRegistration number : ");
    scanf("%d",&tempno);

    rewind(fp);


    while((fread(&s,siz,1,fp))==1)
    {
        if(tempno==s.player_no)
        {
            flag=1;
            printf("\n\n");
            printf("\t\t\tRecord Deleted for");
            printf("\n\t\t\t%s\n\t\t\t%d\n",s.name,s.player_no);
            continue;
        }

        fwrite(&s,siz,1,ft);
    }


    fclose(fp);
    fclose(ft);

    remove("file1.txt");
    rename("temp.txt","file1.txt");

    if((fp=fopen("file1.txt","rb+"))==NULL)
    {
        printf("\t\t\tERROR");
    }

    if(flag==0)
        printf("\t\t\tPLAYER DATA DOESN'T EXIST");

    printf("\n\t\t\t");
    system("pause");
    main_menu(fp);

}

//To exit the system
void close()
{
    int option;
    printf("\a");
    printf("\n\n");
    printf("\t\t\tAre you sure you want to exit? (Enter appropriate number to make your decision)\n");
    printf("\t\t\t\t(1)Yes       (2)No\n\t\t\t");
    scanf("%d",&option);
    if(option==1)
    {
        printf("\n\n");
        printf("\t\t\tThank You !");
        printf("\a");
    }
    else if(option==2)
    {
        system("cls");
        main_menu(fp);
    }
    else
    {
        printf("\t\t\tEnter valid numbers\n");
        close();
    }
}

//To login to the system
void login()
{
        int i;
        char ch;
        char user[10];
        char pass[10];
        printf("\n\t\t\t\t\t\tLOGIN\n\n");
        printf("\t\tUSERNAME : ");
        scanf("%s",user);
        printf("\t\tPASSWORD : ");
        for(i=0;i<6;i++)
        {
            pass[i]=getch();
            putchar('*');
        }
        if((strcmp(user,"admin")==0)&&(strcmp(pass,"admin1")!=0))
        {
                do
                {
                    printf("\n\n\t\tIncorrect Password\n\t\t\t");
                    system("pause");
                    system("cls");
                    printf("\n\t\t\t\t\t\tLOGIN\n\n");
                    printf("\t\tUSERNAME : ");
                    scanf("%s",user);
                    printf("\t\tPASSWORD : ");
                    for(i=0;i<6;i++)
                    {
                        pass[i]=getch();
                        putchar('*');
                    }
                }
                while((strcmp(user,"admin")==0)&&(strcmp(pass,"admin1")!=0));

        }
        if((strcmp(user,"admin")!=0)&&(strcmp(pass,"admin1")!=0))

        {
                do
                {
                    printf("\n\n\t\tInvalid user\n\t\t\t");
                    system("pause");
                    system("cls");
                    printf("\n\t\t\t\t\t\tLOGIN\n\n");
                    printf("\t\tUSERNAME : ");
                    scanf("%s",user);
                    printf("\t\tPASSWORD : ");
                    for(i=0;i<6;i++)
                    {
                        pass[i]=getch();
                        putchar('*');
                    }
                }
                while((strcmp(user,"admin")!=0)&&(strcmp(pass,"admin1")!=0));
        }
}

//Main menu of the system
void main_menu(FILE *fp)
{
        int choice;
        system("cls");
        printf("\n\t\t\t\tWELCOME TO 'AC' FOOTBALL SCHOOL\n\n\t\t\t       Student Profile Management System\n\n");
        printf("\t\t\t\t\t  Main Menu\n");
        printf("\t\t\t----------------------------------------------\n");
        printf("\t\t\t(1)Add a new player\n");
        printf("\t\t\t(2)List of all players\n");
        printf("\t\t\t(3)Search for a player\n");
        printf("\t\t\t(4)Edit player details\n");
        printf("\t\t\t(5)Delete a profile\n");
        printf("\t\t\t(6)Exit\n");
        printf("\t\t\t-----------------------------------------------\n");
        printf("\t\t\tEnter an appropriate number to select an option \n");
        printf("\t\t\t");
        scanf("%d",&choice);
        switch(choice)
        {
                case 1:
                {
                        system("cls");
                        add_player(fp);
                        break;
                }
                case 2:
                {
                        system("cls");
                        player_list(fp);
                        break;
                }
                case 3:
                {
                        system("cls");
                        search_player(fp);
                        break;
                }
                case 4:
                {
                        system("cls");
                        edit(fp);
                        break;
                }
                case 5:
                {
                        system("cls");
                        delete_player(fp);
                        break;
                }
                case 6:
                {
                        system("cls");
                        close();
                        break;
                }
                default:
                {
                        printf("Ensure that a number in the list is entered\n");
                        break;
                }
        }
}
