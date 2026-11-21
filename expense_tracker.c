#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 100
#define NAME_LENGTH 50
#define INPUT_SIZE 100

/* Structure to store one expense */
struct Expense
{
    char name[NAME_LENGTH];
    int category;
    float amount;
};

/* Global data */
struct Expense expenses[MAX_EXPENSES];
int count = 0;
float budget;


/* Function declarations */
int getValidInteger(void);
float getValidFloat(void);
void getValidName(char name[]);
void getCategoryName(int category, char categoryName[]);
int amountsEqual(float a, float b);

void addExpense(void);
void viewExpenses(void);
void categorySummary(void);
void budgetAnalysis(void);


/* Reads and validates an integer */
int getValidInteger(void)
{
    char input[INPUT_SIZE];
    int value;
    char extra;

    while(1)
    {
        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            clearerr(stdin);
            printf("Input error! Please try again: ");
            continue;
        }

        if(sscanf(input, " %d %c", &value, &extra) == 1)
        {
            return value;
        }

        printf("Invalid input! Please enter a whole number only: ");
    }
}


/* Reads and validates a floating-point number */
float getValidFloat(void)
{
    char input[INPUT_SIZE];
    float value;
    char extra;

    while(1)
    {
        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            clearerr(stdin);
            printf("Input error! Please try again: ");
            continue;
        }

        if(sscanf(input, " %f %c", &value, &extra) == 1)
        {
            return value;
        }

        printf("Invalid input! Please enter a numeric value only: ");
    }
}


/* Reads and validates an expense name */
void getValidName(char name[])
{
    int length;
    int ch;

    while(1)
    {
        if(fgets(name, NAME_LENGTH, stdin) == NULL)
        {
            clearerr(stdin);
            printf("Input error! Enter expense name again: ");
            continue;
        }

        length = (int)strlen(name);

        /*
           If newline is present, the complete name
           fitted inside the array.
        */
        if(length > 0 && name[length - 1] == '\n')
        {
            name[length - 1] = '\0';
            length--;
        }
        else
        {
            /*
               Input was too long.
               Clear the remaining characters.
            */
            while((ch = getchar()) != '\n' && ch != EOF)
            {
                /* Clear remaining input */
            }

            printf("Expense name is too long!\n");
            printf("Please enter a maximum of 49 characters: ");
            continue;
        }

        if(length > 0)
        {
            return;
        }

        printf("Expense name cannot be empty!\n");
        printf("Examples: Lunch, Metro Ticket, C Programming Book\n");
        printf("Enter expense name again: ");
    }
}


/* Compares monetary values safely */
int amountsEqual(float a, float b)
{
    float difference;

    difference = a - b;

    return difference > -0.005f &&
           difference < 0.005f;
}


/* Converts category number to category name */
void getCategoryName(int category, char categoryName[])
{
    switch(category)
    {
        case 1:
            strcpy(categoryName, "Food");
            break;

        case 2:
            strcpy(categoryName, "Travel");
            break;

        case 3:
            strcpy(categoryName, "Books");
            break;

        case 4:
            strcpy(categoryName, "Entertainment");
            break;

        default:
            strcpy(categoryName, "Unknown");
    }
}


int main(void)
{
    int choice;

    printf("========================================================\n");
    printf("              PERSONAL EXPENSE TRACKER\n");
    printf("========================================================\n");

    printf("\nWelcome!\n");
    printf("This program helps you record and analyze your\n");
    printf("monthly expenses and monitor your budget.\n");

    printf("\n--------------------------------------------------------\n");
    printf("Enter your total monthly budget in Rs.\n");
    printf("Example: 10000 or 15000.50\n");
    printf("Monthly Budget: Rs. ");

    budget = getValidFloat();


    /* Validate budget */
    while(budget <= 0)
    {
        printf("\nInvalid budget! Budget must be greater than 0.\n");
        printf("Enter your monthly budget again: Rs. ");

        budget = getValidFloat();
    }


    do
    {
        printf("\n========================================================\n");
        printf("                       MAIN MENU\n");
        printf("========================================================\n");

        printf("1. Add a New Expense\n");
        printf("2. View All Recorded Expenses\n");
        printf("3. View Category-wise Summary\n");
        printf("4. View Complete Budget Analysis\n");
        printf("5. Exit Program\n");

        printf("--------------------------------------------------------\n");
        printf("Enter your choice (1-5): ");

        choice = getValidInteger();


        switch(choice)
        {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                categorySummary();
                break;

            case 4:
                budgetAnalysis();
                break;

            case 5:
                printf("\n========================================================\n");
                printf("Thank you for using Personal Expense Tracker!\n");
                printf("========================================================\n");
                break;

            default:
                printf("\nInvalid choice!\n");
                printf("Please select an option between 1 and 5.\n");
        }

    } while(choice != 5);


    return 0;
}


/* Adds a new expense */
void addExpense(void)
{
    char categoryName[20];

    if(count >= MAX_EXPENSES)
    {
        printf("\nExpense limit reached!\n");
        printf("No more expenses can be added.\n");
        return;
    }


    printf("\n========================================================\n");
    printf("                    ADD NEW EXPENSE\n");
    printf("========================================================\n");

    printf("\nEnter what you spent money on.\n");
    printf("Examples: Lunch, Metro Ticket, C Programming Book\n");
    printf("Expense Name: ");

    getValidName(expenses[count].name);


    printf("\nSelect the category of this expense:\n");
    printf("1. Food\n");
    printf("2. Travel\n");
    printf("3. Books\n");
    printf("4. Entertainment\n");

    printf("Enter category number (1-4): ");

    expenses[count].category = getValidInteger();


    while(expenses[count].category < 1 ||
          expenses[count].category > 4)
    {
        printf("\nInvalid category!\n");
        printf("Please choose 1 = Food, 2 = Travel, ");
        printf("3 = Books, or 4 = Entertainment.\n");
        printf("Enter category number (1-4): ");

        expenses[count].category = getValidInteger();
    }


    printf("\nEnter the amount spent in Rs.\n");
    printf("Example: 250 or 499.50\n");
    printf("Amount: Rs. ");

    expenses[count].amount = getValidFloat();


    while(expenses[count].amount <= 0)
    {
        printf("\nInvalid amount! Amount must be greater than 0.\n");
        printf("Enter amount again: Rs. ");

        expenses[count].amount = getValidFloat();
    }


    getCategoryName(expenses[count].category,
                    categoryName);


    printf("\n--------------------------------------------------------\n");
    printf("EXPENSE ADDED SUCCESSFULLY!\n");
    printf("--------------------------------------------------------\n");

    printf("Expense  : %s\n",
           expenses[count].name);

    printf("Category : %s\n",
           categoryName);

    printf("Amount   : Rs. %.2f\n",
           expenses[count].amount);

    printf("--------------------------------------------------------\n");


    count++;
}


/* Displays all recorded expenses */
void viewExpenses(void)
{
    int i;
    char categoryName[20];


    printf("\n========================================================\n");
    printf("                  ALL RECORDED EXPENSES\n");
    printf("========================================================\n");


    if(count == 0)
    {
        printf("No expenses recorded yet.\n");
        printf("Use option 1 from the Main Menu to add an expense.\n");
        return;
    }


    printf("%-5s %-25s %-18s %-12s\n",
           "No.",
           "Expense",
           "Category",
           "Amount");

    printf("----------------------------------------------------------------\n");


    for(i = 0; i < count; i++)
    {
        getCategoryName(expenses[i].category,
                        categoryName);


        printf("%-5d %-25s %-18s Rs. %-8.2f\n",
               i + 1,
               expenses[i].name,
               categoryName,
               expenses[i].amount);
    }


    printf("----------------------------------------------------------------\n");
    printf("Total number of expenses recorded: %d\n", count);
}


/* Displays category-wise summary */
void categorySummary(void)
{
    int i;

    float food = 0.0f;
    float travel = 0.0f;
    float books = 0.0f;
    float entertainment = 0.0f;

    float total = 0.0f;
    float highest;

    char highestCategory[20];


    printf("\n========================================================\n");
    printf("                  CATEGORY-WISE SUMMARY\n");
    printf("========================================================\n");


    if(count == 0)
    {
        printf("No expenses recorded yet.\n");
        printf("Add at least one expense to view the summary.\n");
        return;
    }


    for(i = 0; i < count; i++)
    {
        total = total + expenses[i].amount;


        switch(expenses[i].category)
        {
            case 1:
                food = food + expenses[i].amount;
                break;

            case 2:
                travel = travel + expenses[i].amount;
                break;

            case 3:
                books = books + expenses[i].amount;
                break;

            case 4:
                entertainment =
                    entertainment + expenses[i].amount;
                break;
        }
    }


    highest = food;
    strcpy(highestCategory, "Food");


    if(travel > highest)
    {
        highest = travel;
        strcpy(highestCategory, "Travel");
    }


    if(books > highest)
    {
        highest = books;
        strcpy(highestCategory, "Books");
    }


    if(entertainment > highest)
    {
        highest = entertainment;
        strcpy(highestCategory, "Entertainment");
    }


    printf("Food                         : Rs. %.2f\n",
           food);

    printf("Travel                       : Rs. %.2f\n",
           travel);

    printf("Books                        : Rs. %.2f\n",
           books);

    printf("Entertainment                : Rs. %.2f\n",
           entertainment);

    printf("--------------------------------------------------------\n");

    printf("Total Spending               : Rs. %.2f\n",
           total);


    if(amountsEqual(total, budget))
    {
        printf("Remaining Budget             : Rs. 0.00\n");
    }

    else if(total < budget)
    {
        printf("Remaining Budget             : Rs. %.2f\n",
               budget - total);
    }

    else
    {
        printf("Overspent By                 : Rs. %.2f\n",
               total - budget);
    }


    printf("\nHighest-Spending Category    : %s\n",
           highestCategory);

    printf("Amount Spent in This Category: Rs. %.2f\n",
           highest);

    printf("========================================================\n");
}


/* Displays complete budget analysis */
void budgetAnalysis(void)
{
    int i;

    float total = 0.0f;
    float percentage;


    for(i = 0; i < count; i++)
    {
        total = total + expenses[i].amount;
    }


    percentage = (total / budget) * 100.0f;


    printf("\n========================================================\n");
    printf("                     BUDGET ANALYSIS\n");
    printf("========================================================\n");

    printf("Monthly Budget       : Rs. %.2f\n",
           budget);

    printf("Total Spent          : Rs. %.2f\n",
           total);

    printf("Budget Used          : %.2f%%\n",
           percentage);


    if(amountsEqual(total, budget))
    {
        printf("Remaining Budget     : Rs. 0.00\n");

        printf("--------------------------------------------------------\n");
        printf("STATUS: BUDGET FULLY USED\n");
    }

    else if(total < budget)
    {
        printf("Remaining Budget     : Rs. %.2f\n",
               budget - total);

        printf("--------------------------------------------------------\n");
        printf("STATUS: WITHIN BUDGET\n");
    }

    else
    {
        printf("Overspent By         : Rs. %.2f\n",
               total - budget);

        printf("--------------------------------------------------------\n");
        printf("WARNING: MONTHLY BUDGET EXCEEDED!\n");
    }


    printf("========================================================\n");
}