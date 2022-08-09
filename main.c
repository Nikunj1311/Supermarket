#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
////////////////////////     FUNCTION CALLS   ///////////////////
void data();                                                            //list of items available in the store
void payment(void);                                                     // for payment
void Customer(void);                                                    //for login of customer
void purchase(void );                                                   //for selecting items for purchase
void expire(FILE *ptr);                                                 //for expiry date of perishable items
void login(char name[] );                                               //details of logged in customers
void Initialize(void);                                                  //for initializing append mode files
void admin(void);                                                       //details to be viewed by admin
////////////////////////    VARIABLES-DATA TYPES  /////////////////
typedef struct item {                                                   //user defined structure for items selected for purchase, i.e. cart details
        char name[35];
        int quantity;
        int price;
        int amount;
        char expiry[30], account[20];
        struct item *next;                                              //for creating linked list
        } n;
int day, month, year;                                                   //for expiry date
char c, no[4];
struct item *current;
time_t now, today;
FILE *fp, *ptr;                                                         //file pointer for checking and updating records
int i, quant, j=0, cost, total=0, d, m =0;
char item[40], address[100], card[20], blank[20] = "-----------------\n";
char contact[12], details[150], account[20];
struct item *head;                                                      //for linked list of selected items
//////////////////////////////////////////////////////
//                      MAIN                        //
//////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
system("clear");
////////////////  MODULE 6    //////////////////////////////////
if (argc >= 2)
{
        admin();
        return 0;
}
time(&now);
time(&today);
head = malloc(sizeof(struct item));
current = malloc(sizeof(struct item));
data();
Initialize();
printf("\t\t\t-------------------------------------------- \n\n");
printf("\t\t\t\tWELCOME TO THE PULNIK STORE!!!!\n\n");
printf("\t\t\t-------------------------------------------- \n\n");
/////////////////////////////   MODULE 1   ///////////////////////////////
Customer();
m = 0;
ptr = fopen("Active","r+");                                             // for showing the admin name of active customer
while ((c  != EOF) && (c != '-') )
{
        c = fgetc(ptr);
        if ( c == '\n')
                m++;
}
fputs(details, ptr);
fclose(ptr);
/////////////////////////////   MODULE 2   //////////////////////////////
purchase();                                                                     //select items for purchase
current->next = NULL;
current = head->next;
printf("\t\tCART\n");
printf("NO. Item\t\tPrice\tQuantity Amount\tBest Before\n");
if(head->next->next == NULL)
{
        printf("\tCART is empty\n");                                    //if no items selected
        ptr = fopen("Logout.txt","a");
        fprintf(ptr,"%s ", details);
        fclose(ptr);
        ptr = fopen("Active","r+");
        while (m>0)
        {
                fgets(details, 20, ptr);
                m--;
        }
        fputs(blank, ptr);
        fclose(ptr);
        return 0;
}
else
{
        i=1;
        while( current->next != NULL)                                   //display list of items selected along with price and quantity
        {
                printf("%d) %s\t%d\t%d\t  %d\t%s\n", i, current->name, current->price, current->quantity, current->amount, current->expiry);
                total = total + current->amount;
                current = current->next;
                i++;
        }
}
printf("\n\n\t\tTotal amount: %d\n\n", total);
today = now + 172800;
printf("NOTE: Items not available for more than 5 quantity due to limited stocks\nFresh stocks would be available by %s\n\n", ctime(&today));
printf("press ENTER to continue\n");
scanf("%c", &c);
scanf("%c", &c);
////////////////////////   MODULE 3   ///////////////////////////////
payment();
if (i == 0)
        return 0;
////////////////////   MODULE 5   /////////////////////////
today = now + 345600;
printf("Your order would be delivered to %s before %s\n", address, ctime(&today));              //delivery location and date
printf("\t\tThankyou for shopping!!!!!\n\n");
scanf("%c", &c);
system("clear");
time(&now);
ptr = fopen("Logout.txt","a");
fprintf(ptr,"%s ", details);
fclose(ptr);
ptr = fopen("Active","r+");
while (m>0)
{
        fgets(details, 20, ptr);
        m--;
}
fputs(blank, ptr);
fclose(ptr);
free(head);
free(current);
return 0;
}
//////////////////////////////////////////////////////////
//                                                      //
//                      END OF MAIN                     //
//                                                      //
//////////////////////////////////////////////////////////

void Customer(void )
{
printf("Enter your contact number\n");
        fgets(contact, 11, stdin);
fp = fopen("Details.txt","a+");
i=0;
while(fgets(details, 100, fp) != NULL)
{
        i++;
}
rewind(fp);
for (int a=0;a<i;a++)
{
        fgets(details, 11, fp);
        if (strcmp (contact, details) == 0)                                     //contact available in records if old customer
        {
                c = fgetc(fp);
                fgets(details, 149, fp);                                        //retrieve all other details from records
                printf("Hello %s \n", details);
                i = 0;
                fgets(address, 99, fp);
                fgets(account, 19, fp);
                break;
        }
}
if (i != 0)                                                                     //details of new customer
{
        char t = '\n';
        fputc(t, fp);
        printf("Welcome new customer!\n");
        fputs(contact, fp);
        //scanf("%c", &c);
        printf("Enter your Name\n");
        scanf("%s", details);
        fputc(t, fp);
        scanf("%c", &c);
        fputs(details, fp);
        printf("Enter address(<100 characters)\n");
        fgets(address, 99, stdin);
        fputc(t, fp);
        fputs(address, fp);
        printf("Enter credit/debit card no.\n");
        fgets(account, 17, stdin);
        fputs(account, fp);
}
fclose(fp);
ptr = fopen("Login.txt","a");
fprintf(ptr,"%s", details);
fclose(ptr);
login(details);
}
//////////////////////////////////////////////////
void purchase(void )
{
head = malloc(sizeof(struct item));
current = malloc(sizeof(struct item));
head->next =current;
for (int z=0;;z++)                                                      //Display items available for purchase
{
        printf("Select category of products you wish to buy\n");
        printf("(1) Perishable Items \t (2) Non-Perishable Items\n");
        for (int y=0;;y++)
        {
                scanf("%d", &i);
                 d=i;
                if(i == 1)
                {
                        fp = fopen("Perishable","r");
                        i =29 ;                                                 //i = no. of items in perishable
                        break;
                }
                else if(i ==2)
                {
                        fp = fopen("Non-Perishable","r");
                        i = 11;                                                 //i = no. of items in non-perishable
                        break;
                }
                else
                        printf("Enter valid option (1 or 2)\n");
        }
        for( j=0; j<i;j++)                                                      //display list of items
        {
                fgets(item, 39, fp);
                fputs(item, stdout);
        }
        j=0;
        rewind(fp);
        printf("\n");
        for (int z = 0;;z++)                                                    //selection of items
        {
                printf("Enter item number\n");
                scanf("%s", no);
                no[2] = ')';
                no[3] = '\0';
                printf("Enter Quantity\n");
                scanf("%d", &quant);
                scanf("%c", &c);
                for (int y=0;y<i;y++)
                {
                        fgets(item, 40, fp);
                        if (strstr(item, no))                                   //check item no. entered
                        {
                                struct item *p;
                                p = malloc(sizeof(struct item));
                                current->next = p;
                                p->next = NULL;
                                ptr = fopen("selection.txt","w");
                                fputs(item, ptr);
                                fclose(ptr);
                                ptr = fopen("selection.txt","r");
                                fgets(item, 4, ptr);
                                fgets(item, 20, ptr);                           //Retrieve item details of no. entered
                                for(int a=0; a<=20;a++)
                                {
                                        current->name[a] = item[a];
                                }
                                fscanf(ptr,"%d", &cost);
                                fclose(ptr);
                                if (quant>5)
                                        quant = 5;
                                current->quantity = quant;
                                current->price = cost;
                                current->amount = (quant*cost);
                                ptr  = fopen("selection.txt","w+");
                                if ( d == 1)                                    //expiry date of perishable items
                                        expire(ptr);
                                else                                            //for non perishable items
                                {
                                        fputs("  N.A.  ", ptr);
                                        rewind(ptr);
                                        fgets(current->expiry, 8, ptr);
                                }
                                fclose(ptr);
                                current = current->next;
                                break;
                        }
                        else
                                continue;
                }
                if ((c = fgetc(fp)) == '#')                                             //if no. not found in records
                        printf("Item not found\n");
                printf("Press any key for next item or C to continue\n");
                scanf("%c", &c);
                if (c == 'C')
                {
                        fclose(fp);
                        break;
                }
                else
                        rewind(fp);

        }
        scanf("%c", &c);
        printf("Enter 'C' to view cart/any other key for another category\n");
        scanf("%c", &c);
        if (c == 'C')
                break;
        else
                continue;
}
}
/////////////////////////////////////////////////////////
void payment(void )
{
for(d=2;d>=0 ;d--)
{
        printf("Verify your card no. for Payment of Rs.%d \n", total);                  //verification of customer details
        fgets(card, 17, stdin);
        if (strcmp(account,card) == 0)
        {
                printf("Payment successful\n");
                i=1;
                current = head;
                ptr = fopen("Sale.txt","a");
                fputs("\n", ptr);
                while( current->next != NULL)                           //display list of items selected along with price and quantity
                {
                        fprintf(ptr,"%s\t%d\t%d\t  %d\t%s\n\n", current->name, current->price, current->quantity, current->amount, current->expiry);
                        current = current->next;
                        i++;
                }
                fclose(ptr);
                break;
        }
        else
        {
                printf("card no. does not match the records\n");
                printf("%d retries left\n", d);
        }
}
if (d<0)
{
        printf("\n\t\tSORRY Payment unsuccessful\n\t\tPlease login and order again\n\n");       //if card no. does not match
        ptr = fopen("Logout.txt","a");
        fprintf(ptr,"%s ", details);
        fclose(ptr);
        ptr = fopen("Active","r+");
        while (m>0)
        {
                fgets(details, 20, ptr);
                m--;
        }
        fputs(blank, ptr);
        fclose(ptr);
        free(head);
        free(current);
        i = 0;
}
}
///////////////////////////////////////////////////////
void data (void )                                                       //function for details of items in store
{
FILE *fp;
fp = fopen("Perishable","w");
fputs("No. Item               Price(Rs.)\n", fp);
fputs("01) flour/1kg           50\n", fp);
fputs("02) rice/1kg            100\n", fp);
fputs("03) tur dal/1kg         90\n", fp);
fputs("04) chana dal/1kg       120\n", fp);
fputs("05) cooking oil/1L      99\n", fp);
fputs("06) chili powder/100gm  28\n", fp);
fputs("07) jeera/100gm         30\n", fp);
fputs("08) chat masala/100gm   54\n", fp);
fputs("09) garam masala/100gm  50\n", fp);
fputs("10) sugar/1kg           40\n", fp);
fputs("11) salt/5kg            90\n", fp);
fputs("12) tea leaves/500gm    270\n", fp);
fputs("13) coffee/100gm        180\n", fp);
fputs("14) Bathing soap        45\n", fp);
fputs("15) Washing soap        10\n", fp);
fputs("16) shampoo/200mL       75\n", fp);
fputs("17) toothpaste/50gm     50\n", fp);
fputs("18) toothbrush          40\n", fp);
fputs("19) handwash/150mL      80\n", fp);
fputs("20) cold cream          66\n", fp);
fputs("21) hair oil            50\n", fp);
fputs("22) Shaving foam        200\n", fp);
fputs("23) biscuits/pack       50\n", fp);
fputs("24) Wafers              20\n", fp);
fputs("25) Maggi               12\n", fp);
fputs("26) cheese cube         17\n", fp);
fputs("27) Butter/100gm        60\n", fp);
fputs("28) frozen food/100gm   100\n", fp);
fputs("##########\n", fp);
fclose(fp);
fp = fopen("Non-Perishable","w");
fputs("NO. Item             Price(Rs.)\n", fp);
fputs("01) Glasses/dozen       600\n", fp);
fputs("02) Cup-Saucer set      650\n", fp);
fputs("03) Cotton Shirt        500\n", fp);
fputs("04) Denim Jeans         999\n", fp);
fputs("05) Sports Shoes        2999\n", fp);
fputs("06) Accessories set     1500\n", fp);
fputs("07) Container/1Kg       30\n", fp);
fputs("08) Container/5Kg       120\n", fp);
fputs("09) Container/20Kg      300\n", fp);
fputs("10) Cutlery Set         499\n", fp);
fputs("##########\n", fp);
fclose(fp);
}
/////////////////////////////////////////////////////////////
void expire(FILE *ptr)                                                          //for expiry date of perishable items
{
                if (strstr("01) 02) 03) 04) 05)", no))
                        {
                                c = '/';
                                today = now + 47304000;
                                struct tm *local = localtime(&today);
                                day = local->tm_mday;
                                month = local->tm_mon + 1;
                                year = local->tm_year +1900;
                                fprintf(ptr,"%d", day);
                                fprintf(ptr,"%c", c);
                                fprintf(ptr,"%d", month);
                                fprintf(ptr,"%c", c);
                                fprintf(ptr,"%d", year);
                                rewind(ptr);
                                fgets(current->expiry, 11, ptr);
                                fclose(ptr);
                        }
                else if (strstr("06) 07) 08) 09)", no))
                {
                        c = '/';
                        today = now + 63072000;
                        struct tm *local = localtime(&today);
                        day = local->tm_mday;
                        month = local->tm_mon + 1;
                        year = local->tm_year +1900;
                        fprintf(ptr,"%d", day);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", month);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", year);
                        rewind(ptr);
                        fgets(current->expiry, 11, ptr);
                        fclose(ptr);
                }
                else if (strstr("10) 11)", no))
                {
                        c = '/';
                        today = now + 31536000;
                        struct tm *local = localtime(&today);
                        day = local->tm_mday;
                        month = local->tm_mon + 1;
                        year = local->tm_year +1900;
                        fprintf(ptr,"%d", day);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", month);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", year);
                        rewind(ptr);
                        fgets(current->expiry, 11, ptr);
                        fclose(ptr);
                }
                else if (strstr("12) 13)", no))
                {
                        c = '/';
                        today = now + 15768000;
                        struct tm *local = localtime(&today);
                        day = local->tm_mday;
                        month = local->tm_mon + 1;
                        year = local->tm_year +1900;
                        fprintf(ptr,"%d", day);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", month);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", year);
                        rewind(ptr);
                        fgets(current->expiry, 11, ptr);
                        fclose(ptr);
                }
                else if(strstr("14) 15) 16) 17) 18)", no))
                {
                        c = '/';
                        today = now + 63072000;
                        struct tm *local = localtime(&today);
                        day = local->tm_mday;
                        month = local->tm_mon + 1;
                        year = local->tm_year +1900;
                        fprintf(ptr,"%d", day);
                        fprintf(ptr,"%c", c);                        fprintf(ptr,"%d", month);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", year);
                        rewind(ptr);
                        fgets(current->expiry, 11, ptr);
                        fclose(ptr);
                }
                else if(strstr("19) 20) 21) 22)", no))
                {
                        c = '/';
                        today = now + 31536000;
                        struct tm *local = localtime(&today);
                        day = local->tm_mday;
                        month = local->tm_mon + 1;
                        year = local->tm_year +1900;
                        fprintf(ptr,"%d", day);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", month);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", year);
                        rewind(ptr);
                        fgets(current->expiry, 11, ptr);
                        fclose(ptr);
                }
                else if(strstr("23) 24) 25)", no))
                {
                        c = '/';
                        today = now + 47304000;
                        struct tm *local = localtime(&today);
                        day = local->tm_mday;
                        month = local->tm_mon + 1;
                        year = local->tm_year +1900;
                        fprintf(ptr,"%d", day);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", month);
                        fprintf(ptr,"%c", c);
                        fprintf(ptr,"%d", year);
                        rewind(ptr);
                        fgets(current->expiry, 11, ptr);
                        fclose(ptr);
                }
                else;
}
//////////////////////////////////////////////////////
void login(char name[30])                                               //for satisfyintg conditions in MODULE 4
{
FILE *li, *lo, *fp;
char line[50], c;
li = fopen("Login.txt","r");
lo = fopen("Logout.txt","r");
int z, i, j, r, k=0;
for (z=0;;z++)
{
        i=0;
        j=0;
        li = fopen("Login.txt","r");
        lo = fopen("Logout.txt","r");
        while (fgets(line, 49, li) != NULL)
                i++;
        while (fgets(line, 49, lo) != NULL)
                j++;
        if ( i-j < 5)
        {
                if(z>0)
                {
                        fp = fopen("Waitlist","r+");
                        while (k != 0 )
                        {
                                fgets(line, 49, fp);
                                k--;
                        }
                        fputs("-----------------\n", fp);
                        fclose(fp);
                }
               break;
        }
        else
        {
                if (z==0)
                {
                        printf("Too many customers are currently logged in\nPlease wait for some time\n");
                        fp = fopen("Waitlist","r+");
                        while (( c != EOF) && (c != '-'))
                        {
                                c = fgetc(fp);
                                if (c == '\n')
                                        k++;
                        }
                        fputs(name, fp);
                        fclose(fp);
                }
                for ( r=0;r<1000;r++);
        }
        fclose(lo);
        fclose(li);
}
}
/////////////////////////////////////////////////////
void admin(void )                                                               //for login as admin
{
        FILE *fp;
        int c;
        char t, pass[] = "N0343P0844";
        char w, string[100];
        printf("\t\t\tWELCOME ADMIN\n\n");
        printf("Enter password\n");
        scanf("%s", string);
        if (strcmp(string, pass) ==0);
        else
        {
                printf("Incorrect Password\n");
                return;
        }
        for (int h=0;;h++)
        {
        printf("Enter the list you wish to view\n");
        printf("1) Sale\n2) Active Customers\n3)Waiting List\n4)Stock\n5) 0 to exit\n");
        scanf("%d", &c);
                if ( c == 1)
                {
                        fp = fopen("Sale.txt","r");
                        while (fgets(string, 99, fp) != NULL)
                                fputs(string, stdout);
                        printf("\n");
                        fclose(fp);
                }
                else if (c == 2)
                {
                        fp = fopen("Active","r");
                        while(fgets(string, 99, fp) != NULL)
                                fputs(string, stdout);
                        fclose(fp);
                }
                else if (c==3)
                {
                        fp = fopen("Waitlist","r");
                        while(fgets(string, 99, fp) != NULL)
                                fputs(string, stdout);
                        fclose(fp);
                }
                else if (c == 4)
                {
                        fp = fopen("Perishable","r");
                        while(fgets(string, 99, fp) != NULL)
                                fputs(string, stdout);
                        fclose(fp);
                        fp = fopen("Non-Perishable","r");
                        while(fgets(string, 99, fp) != NULL)
                                fputs(string, stdout);
                        fclose(fp);
                        printf("All above items are available in stock and will be refilled as soon as they are purchased\n");
                }
                else if (c ==0 )
                        break;
                else
                        printf("Enter Valid Option \n");
        }
}
////////////////////////////////////////////////////
void Initialize(void )
{
FILE *fp;
fp = fopen("Details.txt","r+");
fputs("\t\tCustomer Details\n", fp);
fclose(fp);
fp = fopen("Login.txt","r+");
fputs("Logged In Customers\n", fp);
fclose(fp);
fp = fopen("Logout.txt","r+");
fputs("Logged Out Customers\n", fp);
fclose(fp);
fp = fopen("Sale.txt","r+");
fputs("\t\tSALE OF ITEMS\n", fp);
fputs("Item\t\t\tPrice\tQuantity Amount\tBest Before\n", fp);
fclose(fp);
fp = fopen("Active","r+");
fputs("Active Customers\n", fp);
fclose(fp);
}
