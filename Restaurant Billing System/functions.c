#include "functions.h"
#include <math.h>

int choice;

void additems()
{
    strcpy(items.name[0], "Pizza");
    strcpy(items.name[1], "Momos");
    strcpy(items.name[2], "Burger");
    strcpy(items.name[3], "Sandwich");
    strcpy(items.name[4], "Maggi");
    strcpy(items.name[5], "Hakka Noodles");
    strcpy(items.name[6], "Tomato Soup");
    strcpy(items.name[7], "Fried Rice");
    strcpy(items.name[8], "Chicken Wings");
    strcpy(items.name[9], "Cold Coffee");
    strcpy(items.price[0], "125");
    strcpy(items.price[1], "80");
    strcpy(items.price[2], "110");
    strcpy(items.price[3], "125");
    strcpy(items.price[4], "90");
    strcpy(items.price[5], "180");
    strcpy(items.price[6], "200");
    strcpy(items.price[7], "250");
    strcpy(items.price[8], "225");
    strcpy(items.price[9], "120");
}

void dashboard(void)
{
    header();

    dashes();
    printf(" 1\tCreate Invoice\n");
    printf(" 2\tExit");
    dashes();
    printf("Enter Choice : ");
    scanf("%d", &choice);
    menu();
}

void dashes(void)
{
    printf("\n");
    for (int i = 1; i <= 37; i++)
    {
        printf("-");
    }
    printf("\n");
}

void items_display()
{
    int index, longest;
    system("cls");
    header();
    dashes();
    for (int i = 0; i <= sizeof(items.price) / lround(sqrt(sizeof(items.price))); i++)
    {
        if (strlen(items.name[i]) <= 1)
            break;
        else
            index = i;
    }
    longest = widthspecifier(index, 1);
    printf(" Sr Name%*cPrice", longest + (longest - 5));
    dashes();
    for (int i = 0; i <= index; i++)
    {
        if (i >= index)
        {
            break;
        }
        else
        {
            if (i >= 9)
            {
                printf("%d. %s  %*d", i + 1, items.name[i], atoi(sp.spaces[i]), atoi(items.price[i]));
                if (i <= index - 2)
                {
                    printf("\n");
                }
            }
            else
            {
                printf(" %d. %s  %*d", i + 1, items.name[i], atoi(sp.spaces[i]), atoi(items.price[i]));
                if (i <= index - 2)
                {
                    printf("\n");
                }
            }
        }
    }

    dashes();
}

void header()
{
    printf("\tDragon Restaurant\n\t");
    for (int i = 1; i <= 17; i++)
    {
        printf("-");
    }
    printf("\nDate : %s", __DATE__);
    printf("\nTime : %s", __TIME__);
}

int widthspecifier(int index, int comingfrom)
{
    int longest = 0;
    int adjuster[25];
    for (int i = 0; i <= index; i++)
        if (comingfrom == 1)
        {
            if (strlen(items.name[i]) >= longest)
                longest = strlen(items.name[i]);
        }
        else if (comingfrom == 2)
        {
            if (strlen(cart.name[i]) >= longest)
                longest = strlen(cart.name[i]);
        }

    for (int i = 0; i <= index; i++)
        if (comingfrom == 1)
        {
            adjuster[i] = ("%d\n", (longest - (strlen(items.name[i]))) + longest);
        }
        else if (comingfrom == 2)
        {
            adjuster[i] = ("%d\n", (longest - (strlen(cart.name[i]))) + longest);
        }
    for (int i = 0; i <= index - 1; i++)
    {
        itoa(adjuster[i], sp.spaces[i], 10);
    }
    return longest;
}

void menu()
{
    int select;
    int i = 1;
    int j = 0;
    switch (choice)
    {
    default:
        printf("invalid choice");
        break;
    case 2:
        exit(0);

    case 1:

        do
        {
            system("cls");
            header();
            dashes();
            items_display();
            printf("Enter item to add : ");
            scanf("%d", &select);
            strcpy(cart.name[j], items.name[select - 1]);
            strcpy(cart.price[j], items.price[select - 1]);
            printf("Enter quantity to add : ");
            fflush(stdin);
            scanf("%d", &select);
            itoa(select, cart.qty[j], 10);
            printf("%s %s %d\n", cart.name[j], cart.qty[j], (atoi(cart.qty[j]) * atoi(cart.price[j])));
            printf("Press 1 to add more & 0 to exit : ");
            scanf("%d", &i);
            if (i == 1)
                j += 1;
        } while (i == 1);
        cartdisplay();
    }
}

void cartdisplay(void)
{
    int index, longest, total = 0;
    system("cls");
    header();
    dashes();
    for (int i = 0; i <= sizeof(cart.price) / lround(sqrt(sizeof(cart.price))); i++)
    {
        if (strlen(cart.name[i]) <= 1)
            break;
        else
            index = i + 1;
    }
    longest = widthspecifier(index, 2);
    printf(" Sr Name %*cQty  Price", longest + (longest - 8));
    dashes();
    for (int i = 0; i <= index; i++)
    {
        if (i >= index)
        {
            break;
        }
        else
        {
            if (i >= 9)
            {
                if (strlen(cart.name[i]) >= 1)
                    printf("%d. %s  %*d", i + 1, cart.name[i], atoi(sp.spaces[i]), atoi(cart.price[i]));
                if (i <= index - 2)
                {
                    printf("\n");
                }
            }
            else
            {
                if (strlen(cart.name[i]) >= 1)
                    printf(" %d. %s%*d%*d", i + 1, cart.name[i], (atoi(sp.spaces[i])), atoi(cart.qty[i]), 7, atoi(cart.price[i]) * atoi(cart.qty[i]));
                if (i <= index - 2)
                {
                    printf("\n");
                }
            }
        }
    }
    dashes();
    for (int i = 0; i <= index; i++)
    {
        total += atoi(cart.price[i]) * atoi(cart.qty[i]);
    }
    printf(" Sub Total%*d", longest + (longest - 8) + 9, total);
    printf("\n CGST @9%*.f", longest + (longest - 8) + 11, round(total * 0.09));
    printf("\n SGST @9%*.f", longest + (longest - 8) + 11, round(total * 0.09));
    dashes();
    printf(" Grand Total%*.f", longest + (longest - 8) + 7, total + 2 * round(total * 0.09));
    dashes();
}