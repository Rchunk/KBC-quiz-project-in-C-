#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int score = 0;

struct Question
{
    // String only takes 32 bits of storage so we are using char array
    char question[110];
    char option1[100];
    char option2[100];
    char option3[100];
    char option4[100];
    char correct_option;
};

struct Node
{
    struct Question q;
    struct Node *next;
};

struct Node *head = NULL;

void insert()
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->next = head;
    head = new_node;
}

void setQuestions()
{
    fstream new_file;
    new_file.open("questions.txt", ios::in);
    if (new_file.is_open())
    {
        string sa;
        int number_of_line = 0;
        while (getline(new_file, sa))
        {
            const char* str = sa.c_str();
            if (number_of_line % 6 == 0)
            {
                insert();
            }
            
            switch (number_of_line % 6)
            {
            case 0:
                strcpy(head->q.question,str);
                break;
            case 1:
                strcpy(head->q.option1,str);
                break;
            case 2:
                strcpy(head->q.option2,str);
                break;
            case 3:
                strcpy(head->q.option3,str);
                break;
            case 4:
                strcpy(head->q.option4,str);
                break;
            case 5:
                head->q.correct_option = str[0];
                break;
            }
            number_of_line++;
        }
        new_file.close();
    }
}

bool check_answer(char choosen_option)
{
    bool lost = 0;
    if (choosen_option == head->q.correct_option)
    {
        score++;
        cout << endl << "Your current score is " << score << endl;
        head = head->next;
    }
    else if (GetAsyncKeyState(VK_ESCAPE) || choosen_option == 'Q')
    {
        cout << "Exiting..." << endl;
        lost = 1;
    }
    else
    {
        cout << endl << "Your score was " << score << endl;
        cout << "You lost!.";
        lost = 1;
    }
    return lost;
}


int main()
{
    setQuestions();
    
    int lifelines = 3;
    int question_number = 1;
    bool lost = 0;
    char choosen_option;
    int lifelinesarr[3] = {1, 2, 3};
    cout << "Welcome to Kaun Banega Karodpati!";
    while (!lost && head != NULL)
    {
        cout << endl
             << "You have " << lifelines << " lifelines." << endl;
        cout << question_number
         << ". ";
        question_number++;
        cout << head->q.question;
        cout << endl
             << "Your options are " << endl;
        cout << "A. " << head->q.option1 << endl;
        cout << "B. " << head->q.option2 << endl;
        cout << "C. " << head->q.option3 << endl;
        cout << "D. " << head->q.option4 << endl;
        if (lifelines > 0)
        {
            cout << endl
                 << "To use a lifeline enter L.";
        }
        cout << endl
             << "To quit enter Q." << endl;

        cin >> choosen_option;
        if (choosen_option == head->q.correct_option)
        {
            score++;
            head = head->next;
        }
        else if (choosen_option == 'L' && lifelines > 0)
        {
            cout << "Your current available lifelines are:" << endl;
            int LifelineCount = 1;
            for (int i = 0; i < 3 ; i++)
            {
                cout << LifelineCount++ << " ";
                if (lifelinesarr[i] == 1)
                {
                    cout << "50 - 50" << endl;
                }
                else if (lifelinesarr[i] == 2)
                {
                    cout << "Phone a friend" << endl;
                }
                else if (lifelinesarr[i] == 3)
                {
                    cout << "Expert call" << endl;
                }
                else{
                    cout << "You have already used this lifeline...."<< endl;
                }
            }

            int choosen_lifeline = 0;
            cout << "Enter the lifeline you want to use..." << endl;
            cin >> choosen_lifeline;

            if (choosen_lifeline == 1)
            {
                cout << question_number << ". ";
                cout << head->q.question;
                cout << endl << "Your options are " << endl;

                int number_of_options = 2;
                bool incorrect_option_printed = 0;
                char c_option = head->q.correct_option;

                if (number_of_options > 0 && (!incorrect_option_printed || c_option == 'A'))
                {
                    if(c_option != 'A')
                    {
                        incorrect_option_printed = 1;
                    }
                    cout << "A. " << head->q.option1 << endl;
                    number_of_options--;
                }
                if (number_of_options > 0 && (!incorrect_option_printed || c_option == 'B'))
                {
                    if(c_option != 'B')
                    {
                        incorrect_option_printed = 1;
                    }
                    cout << "B. " << head->q.option2 << endl;
                    number_of_options--;
                }
                if (number_of_options > 0 && (!incorrect_option_printed || c_option == 'C'))
                {
                    if(c_option != 'C')
                    {
                        incorrect_option_printed = 1;
                    }
                    cout << "C. " << head->q.option3 << endl;
                    number_of_options--;
                }
                if (number_of_options > 0 && (!incorrect_option_printed || c_option == 'D'))
                {
                    if(c_option != 'D')
                    {
                        incorrect_option_printed = 1;
                    }
                    cout << "D. " << head->q.option4 << endl;
                    number_of_options--;
                }
                cout << endl
                    << "To quit enter Q." << endl;

                cin >> choosen_option;
                lost = check_answer(choosen_option);
            }
            if (choosen_lifeline == 2)
            {
                cout << endl
                     << "Call your friend!" << endl;

                cout << endl
                    << "To quit enter Q." << endl;

                cin >> choosen_option;

                lost = check_answer(choosen_option);
            }
            if (choosen_lifeline == 3)
            {
                cout << endl
                     << "Select whatever your expert is telling you!" << endl;

                cout << endl
                    << "To quit enter Q." << endl;

                cin >> choosen_option;

                lost = check_answer(choosen_option);
            }

            lifelinesarr[choosen_lifeline-1] = 0;
            lifelines--;
        }
        else if (GetAsyncKeyState(VK_ESCAPE) || choosen_option == 'Q')
        {
            cout << "Exiting..." << endl;
            exit(0);
        }
        else
        {
            cout << endl << "Your score was " << score << endl;
            cout << "You lost!.";
            lost = 1;
        }
    }
    if (head == NULL)
    {
        cout << "You won! Congratulations!!!" << endl;
        cout << "Your total score is " << score << endl;
        cout << "Thanks for playing.";
    }   
}