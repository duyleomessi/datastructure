#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queuelist.h"
#include "duy.h"

char getMenu();
int readFile(queue **head, queue **tail, FILE *fin, int num);
int checkValidation(elementType e);
void start(queue **head1, queue **tail1, queue **head2, queue **tail2, queue **head3, queue **tail3);
void handleDead(queue **headDead, queue **tailDead, elementType vsDead, queue **headLive, queue **tailLive, elementType vsLive, queue **head3, queue **tail3);
void checkWinner(queue **h1, queue **h2);
void rank(queue **h, queue **t);
int main(int argc, char *argv[])
{
    FILE *fptr1, *fptr2;
    char filename1[] = "monphai1.txt";
    char filename2[] = "monphai2.txt";
    fptr1 = myfopen(filename1, "r");
    fptr2 = myfopen(filename2, "r");

    queue *head1 = NULL;
    queue *tail1 = NULL;

    queue *head2 = NULL;
    queue *tail2 = NULL;

    queue *head3 = NULL;
    queue *tail3 = NULL;

    // count the number of member in each member
    int num1 = countLine(fptr1);
    rewind(fptr1);
    int num2 = countLine(fptr2);
    rewind(fptr2);

    char choice;
    do
    {
        choice = getMenu();
        switch (choice)
        {
        case '1':
            if (num1 != num2)
            {
                printf("The number of 2 team is not equal. Make sure the number of member of 2 team is equal\n");
                break;
            }
            int validation1 = readFile(&head1, &tail1, fptr1, num1);
            int validation2 = readFile(&head2, &tail2, fptr2, num2);
            if (!validation1 || !validation2)
            {
                freeQueue(&head1, &tail1);
                freeQueue(&head2, &tail2);
            }
            else
            {
                printf("%-5s%-20s%-15s%-15s%-15s%-15s\n\n", "STT", "BIET HIEU", "MAU", "TAN CONG", "NHANH NHEN", "PHONG THU");
                printf("Team 1\n");
                displayQueue(head1);
                printf("Team 2\n");
                displayQueue(head2);
            }

            break;
        case '2':
            start(&head1, &tail1, &head2, &tail2, &head3, &tail3);
            break;
        case '3':
            rank(&head3, &tail3);
            break;
        case '4':
            return 0;
        default:
            printf("Invalid input\n");
            break;
        }

    } while (choice != '4');

    fclose(fptr1);
    fclose(fptr2);
    return 0;
}

char getMenu()
{
    printf("***********************\n");
    printf("1. Read File\n");
    printf("2. Let's Fight\n");
    printf("3. Ranks\n");
    printf("4. Quit\n");
    printf("***********************\n");

    char choice;
    printf("Your choice: ");
    scanf("%c", &choice);
    myfflush();
    return choice;
}

int readFile(queue **head, queue **tail, FILE *fin, int num)
{
    elementType e[num];
    int i;
    int validation = 1;

    for (i = 0; i < num; i++)
    {
        fscanf(fin, "%s %d %d %d %d", e[i].name, &e[i].mau, &e[i].tancong, &e[i].nhanhnhen, &e[i].phongthu);
        //printf("%s %d %d %d %d \n", e[i].name, e[i].tancong, e[i].phongthu, e[i].mau, e[i].nhanhnhen);

        if (checkValidation(e[i]) == 0)
        {
            printf("Invalid information. There is negative number. Check again\n");
            validation = 0;
            break;
        }

        enQueue(head, tail, e[i]);
    }

    if (validation == 0)
        return 0;
    return 1;
}

int checkValidation(elementType e)
{
    if (e.tancong < 0 || e.phongthu < 0 || e.mau < 0 || e.nhanhnhen < 0)
    {
        return 0;
    }

    return 1;
}

void start(queue **head1, queue **tail1, queue **head2, queue **tail2, queue **head3, queue **tail3)
{
    int maumat;
    int turn;
    elementType vsphai1;
    elementType vsphai2;
    while (!isEmptyQueue(*head1) && !isEmptyQueue(*head2))
    {
        vsphai1 = deQueue(head1, tail1);
        vsphai2 = deQueue(head2, tail2);

        printf("MP1 Vo si %s %d %d %d %d vs MP2 vo si %s %d %d %d %d\n", vsphai1.name, vsphai1.mau, vsphai1.tancong, vsphai1.nhanhnhen, vsphai1.phongthu, vsphai2.name, vsphai2.mau, vsphai2.tancong, vsphai2.nhanhnhen, vsphai2.phongthu);
        if (vsphai1.nhanhnhen > vsphai2.nhanhnhen)
        {
            printf("%s(mau %d tan cong %d) tan cong %s(mau %d tan cong %d) ", vsphai1.name, vsphai1.mau, vsphai1.tancong, vsphai2.name, vsphai2.mau, vsphai2.tancong);
            if (vsphai1.tancong > vsphai2.phongthu)
            {
                maumat = vsphai1.tancong - vsphai2.phongthu;
                vsphai2.mau -= maumat;

                if (vsphai2.mau <= 0)
                {
                    printf("%s bi loai \n", vsphai2.name);
                    vsphai1.diem + -3;
                }
            }
            else
            {
                maumat = 0;
            }
            if (vsphai2.mau > 0)
            {
                vsphai1.diem += 1;
                printf("%s mat %d mau\n", vsphai2.name, maumat);
            }
            turn = 2;
        }
        else
        {
            printf("%s(mau %d tan cong %d) tan cong %s(mau %d tan cong %d) ", vsphai2.name, vsphai2.mau, vsphai2.tancong, vsphai1.name, vsphai1.mau, vsphai1.tancong);
            if (vsphai2.tancong > vsphai1.phongthu)
            {
                maumat = vsphai2.tancong - vsphai1.phongthu;
                vsphai1.mau -= maumat;
                if (vsphai1.mau <= 0)
                {
                    printf("%s bi loai \n", vsphai1.name);
                }
            }
            else
            {
                maumat = 0;
            }

            if (vsphai1.mau > 0)
            {
                vsphai1.diem += 1;
                printf("%s mat %d mau\n", vsphai1.name, maumat);
            }

            turn = 1;
        }

        while (vsphai1.mau > 0 && vsphai2.mau > 0)
        {
            if (turn == 1)
            {
                printf("%s(mau %d tan cong %d) tan cong %s(mau %d tan cong %d) ", vsphai1.name, vsphai1.mau, vsphai1.tancong, vsphai2.name, vsphai2.mau, vsphai2.tancong);
                if (vsphai1.tancong > vsphai2.phongthu)
                {
                    maumat = vsphai1.tancong - vsphai2.phongthu;
                    vsphai2.mau -= maumat;
                }
                else
                {
                    maumat = 0;
                }
                printf("%s mat %d\n", vsphai2.name, maumat);
                vsphai1.diem += 1;
                turn = 2;
            }
            else if (turn == 2)
            {
                printf("%s(mau %d tan cong %d) tan cong %s(mau %d tan cong %d) ", vsphai2.name, vsphai2.mau, vsphai2.tancong, vsphai1.name, vsphai1.mau, vsphai1.tancong);
                if (vsphai2.tancong > vsphai1.phongthu)
                {
                    maumat = vsphai2.tancong - vsphai1.phongthu;
                    vsphai1.mau -= maumat;
                }
                else
                {
                    maumat = 0;
                }
                printf("%s mat %d\n", vsphai1.name, maumat);
                vsphai2.diem += 1;
                turn = 1;
            }
        }

        // if one of two figter die
        if (vsphai1.mau <= 0)
        {
            handleDead(head1, tail1, vsphai1, head2, tail2, vsphai2, head3, tail3);
        }
        if (vsphai2.mau <= 0)
        {
            handleDead(head2, tail2, vsphai2, head1, tail1, vsphai1, head3, tail3);
        }
    }

    checkWinner(head1, head2);

    while (!isEmptyQueue(*head1))
    {
        elementType vsLive = deQueue(head1, tail1);
        enQueue(head3, tail3, vsLive);
    }
    while (!isEmptyQueue(*head2))
    {
        elementType vsLive = deQueue(head2, tail2);
        enQueue(head3, tail3, vsLive);
    }
}

void handleDead(queue **headDead, queue **tailDead, elementType vsDead, queue **headLive, queue **tailLive, elementType vsLive, queue **head3, queue **tail3)
{
    enQueue(head3, tail3, vsDead);
    insertAtHeadQueue(headLive, headLive, tailLive, vsLive);
    printf("%s bi loai\n\n", vsDead.name);
}

void checkWinner(queue **h1, queue **h2)
{
    if (isEmptyQueue(*h1))
    {
        printf("Team 2 win\n\n");
    }
    else
    {
        printf("Team 1 win\n\n");
    }
}

void rank(queue **h, queue **t)
{
    elementType tmp;
    for (queue *p = *h; p != NULL; p = p->next)
        for (queue *ptr = p->next; ptr != NULL; ptr = ptr->next)
            if (p->e.diem < ptr->e.diem)
            {
                tmp = p->e;
                p->e = ptr->e;
                ptr->e = tmp;
            }

    printf("\n\tBANG XEP HANG:\n\n");
    int i = 1;
    printf("%-5s%-20s%-15s\n\n", "STT", "BIET HIEU", "DIEM");
    for (queue *p = *h; p != NULL; p = p->next)
        printf("%-5d%-20s%-15d\n", i++, p->e.name, p->e.diem);
    printf("\n");
}