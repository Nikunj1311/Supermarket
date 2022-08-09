README for assignment submitted by 2019B3PS0343P
Practical Section No. : 03 (Tue - 1,2 Hour)
Question number attempted : 05 (Grocery Store)
##################################
TEAM:
1) Nikunj Mehadia      - 2019B3PS0343P
2) Pulkit Saini        - 2019B1PS0844P
##################################
Description for running the code submitted
1) The name of the file is 2019B3PS0343P_P3.exe.
2) The input files are:
	1)Perishable - for displaying list of perishable items
	2)Non-Perishable - for displaying list of non perishable items
	3)Login.txt - for keeping record of logged in customers  (not accessed anytime)
	4)Logout.txt - for keeping record of logged out customers (not accessed anytime)
	5)Active - for displaying list of Active customers. Once they complete their shopping and exit their names will be 	  		replaced by -------------------
	6)Waitlist - for displaying list of customers waiting in line. Once they become active their names would be 		replaced by ------------ int the waiting list. (The code runnung for waiting customers will continuously 		check for vacancy, hence solving the first come first serve issue);
	7)Details.txt - for keeping record of customer details so that they are not required to enter all the details 		everytime. the format is:
						contact number(limit 10)
						Name          (linit 20)
						Address       (limit 100)
						card number   (limit 18)
	8)selection.txt - it has been just used as a clipboard and not for any display purpose
3)Upon executing the code the window wil prompt to enter the contact number. Customer's name will be displayed if an old customer logs in. for new customers the system will prompt to enter Name, address and card number.
4)Waiting list customers will see a message and should wait till the purchase window opens.
5)For purchasing, customer should select any one of the category, further the item number the customer wishes to purchase, followed by the quantity.
6)The customer can then choose to select next item from same category or go to another category.
7)After selecting all the items the system will display the list of items selected in CART. if the cart is empty, it will display so and the code will end.
8)The customer will then be asked to verify the card number for paying the required amount. Uopn successful verification, the payment is completed and system will display expected date of delivery of items and address of delivery. if unsuccessful, the system will prompt so and the code will end.
9) For opening the Admin's window more than 1 argument should be passed while executing the code.
10) A password will be required which has already been saved as "N0343P0844".
11) Upon successful login the system will prompt various lists that the admin can view.
################################################################
Known Limitations of the code
1) The code must be saved in a particuar directory of some user ABC and it must be accessible to all other users, otherwise the Waitlist feature may not work. Multiple logins from the same user may also be done in order to overcome the issue.
################################################################
Additional Note:
The code has been successfully executed on the terminal used by students. However if the same does not happen on the checker's end kindly use one command: gcc 2019B3PS0343P_p3.c -o 2019B3PS0343P_P3.exe
################################################################
Contributions:
1) Pulkit coded module 1 and 2 and helped in module 3.
2) Nikunj coded module 3, 4, 5, 6.