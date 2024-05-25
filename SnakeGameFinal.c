#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define height 27
#define width 156
#define xspacing 15
#define yspacing 5
void draw();
void Register();
void Login();
void delay(long long);

typedef struct setup
{
    char name[50];
    char email[30];
    char password[20];
    int number;
} reg;

int main()
{
    printf("\n\t<===================== WELCOME TO WARM ZONE ========================>\n");
    printf("\n\n\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\n\n\t\t\t1.SIGN UP\t\t2.LOGIN");
    printf("\n\n\t\t\tEnter your choice:\t");
    int n;
    scanf("%d", &n);

    switch (n)
    {
    case 1:
        system("cls");
        Register();
        break; // Don't forget to break after each case
    case 2:
        system("cls");
        Login();
        break;
    default:
        printf("\nInvalid choice\n");
    }
}

void delay(long long j)
{
    int i;
    long long k;
    for (i = 0; i < j; i++)
    {
        k = i;
    }
}

void draw()
{
    int i, j;
    // system("color E0");
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            if (j == yspacing && i >= xspacing)
            {
                printf("*"); // top border
            }
            else
                printf(" ");
        }
        if (j == yspacing && i == width)
        {
            break;
        }
        printf("\n");
    }
    printf("\n");
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            if (i == xspacing) // left border
                printf("*");
            else if (i == width - 1)
                printf("*"); // right border
            else
                printf(" ");
        }
        printf("\n");
    }
    for (i = 0; i < width; i++)
    {
        if (i >= xspacing)
            printf("*");
        else
            printf(" ");
    }
    getch();
}

void Register()
{
    reg set;
    FILE *reg_file;
    int i = 0, n;
    reg_file = fopen("login_register.txt", "a+");
    printf("\n\n\t\t\t WELCOME TO REGISTER ZONE");
    printf("\n\t\t\t _________________________\n");
    fflush(stdin);
    printf("\n\t\t\tEnter your full name:\t");
    gets(set.name);
    printf("\n\t\t\tEnter your email:\t");
    gets(set.email);
    printf("\n\t\t\tEnter a backup pin:\t");
    scanf("%d", &set.number);
    fflush(stdin);
    printf("\n\t\t\tEnter 8 to 12 Strong Alphanumeric password:\t");

    // Read password character by character until ENTER is pressed or space is encountered
    while (1)
    {
        set.password[i] = getch();
        if ((int)set.password[i] == 13) // 13 is ascii code of enter key
        {
            set.password[i] = '\0';
            break;
        }
        else if (set.password[i] == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            set.password[i++] = set.password[i];
            printf("* \b");
        }
    }

    fwrite(&set, sizeof(set), 1, reg_file);
    fclose(reg_file); // Close the file when done
    printf("\n\n\t\t\tPress 'Enter' key to confirm registration");
    if (getchar() == '\n')
        ;
    {
        system("cls");
        printf("\n\n\n\t\t\tYou are registered successfully");
        printf("\n\n\t\t\tDo you want to login into your account??\n\n");
        printf("\n\t\t\t>>PRESS 1 FOR YES \t>>PRESS 2 FOR NO\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            system("cls");
            Login();
            break;
        case 2:
            system("cls");
            printf("\n\n\t\tTHANK YOU FOR REGISTERING");
            for (i = 0; i < 3; i++)
            {
                printf(".");
                delay(20000);
            }
            break;
        }
    }
}

void Login()
{
    FILE *login;
    reg set;
    char email_id[30], paswd[20];
    int number, i = 0;
    int check_email, check_paswd;
    login = fopen("login_register.txt", "rb");
    printf("\n\n\t\t\tWELCOME TO LOGIN ZONE");
    printf("\n\n\t\t\t~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\n\t\t\tEnter your email:\t");
    scanf("%s", email_id);
    printf("\n\n\t\tPress space key after typing the password");
    printf("\n\n\t\t\tENTER YOUR PASSWORD:\t");

    while (1)
    {
        paswd[i] = getch();
        if (paswd[i] == '\n' || paswd[i] == ' ')
        {
            paswd[i] = '\0';
            break;
        }
        else if (paswd[i] == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            paswd[i++] = paswd[i];
            printf("* \b");
        }

        while (!feof(login))
        {
            fread(&set, sizeof(set), 1, login);
            check_email = strcmp(email_id, set.email);
            check_paswd = strcmp(paswd, set.password);

            if (check_email == 0 && check_paswd == 0)
            {
                system("cls");
                printf("\n\n\t\t\tLOGIN SUCCESSFULLY...!!");
                printf("\n\n\t\t\tWELCOME TO HUNGRY-SNAKE");
            }
            else if (check_email == 0 && check_paswd != 0)
            {
                system("cls");
                printf("\n\n\t\t\tPassword you enter is incorrect");
                printf("\n\n\t\t\t> Press 'y' for re-login");
                if (getch() == 'y' || getch() == 'Y')
                {
                    system("cls");
                }
            }
        }
    }
}
