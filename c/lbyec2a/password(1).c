#include<stdio.h>
#include<string.h>
int checkPass = 1;
int checkUser = 1;
int prices[] = {
	280, 320, 250, 480, 370, 340, 270, 290, 220, 230, 250, 280, 420, 460, 620, 700, 575, 1200, 70, 130
};
const char * login[][2]= {
	{"Arvin","montoya"}, 
	{"leonard","armas"},
	{"ronald","reagan"}
};
char * menu[][3]= {
		{"011","California Maki","280"}, 
		{"022","Spicy Tuna Roll","320"},
		{"033","Dragon Roll","350"},
		{"044","Salmon Cheese Roll","480"},
		{"055","Rainbow Roll","370"},
		{"066","Ebi Tempura Roll","340"}, 
		{"077","Dynamite Roll","270"},
		{"088","Volcano Roll","290"},
		{"099","Salmon Nigiri","220"},
		{"100","Tuna Nigiri","230"},
		{"111","Ebi Nigiri","250"}, 
		{"122","Unagi Nigiri","280"},
		{"133","Salmon Sashimi","420"},
		{"144","Tuna Sashimi","460"},
		{"155","Chirashi Don","620"},
		{"166","Unagi Don","700"},
		{"177","Tempura Bento","575"},
		{"188","Sushi Platter","1200"},
		{"199","Miso Soup","70"},
		{"200","Matcha Milk Latte","130"}
	};
int clear(int spaces){
	for(int yes=0; yes<spaces; yes++){
		printf("\n");
	}
}
void entrance(){
	char user[50], pass[50];	
	printf("Enter Username: ");
	scanf("%s", user);
	printf("Enter Password: ");
	scanf("%s", pass);
		
	for(int i=0; i<3; i++){  
		checkUser = strcmp(user, login[i][0]);
		checkPass = strcmp(pass, login[i][1]);
		if((checkUser==0)&&(checkPass==0)){
			printf("\nCorrect login\n");
			break;
		}
	}
}
void order_list(){
		printf("				Menu		\n");
		for(int x=0; x<10; x++){
		printf("%s %20s %5s", menu[x][0], menu[x][1], menu[x][2]);
		printf(" 		%s %20s	%5s\n", menu[x+10][0], menu[x+10][1], menu[x+10][2]);
	};
}
void ordering(){
	order_list();
	char item_code[50][1];
	char* bill[50][3];
	int item_price[50][2]; 
	char order_control;
	int code_checker, item_number=0, total_bill=0, item_match;
	int total =0;
	int discount=0;
	int final_total = 0;
	int issued_money, change=0;
do{
	printf("\nEnter Item Code:");
	scanf(" %s", &item_code[item_number]);
	
	for(int i=0; i<20; i++){
		item_match = strcmp(item_code[item_number], menu[i][0]);
			if(item_match ==0){
				bill[item_number][0] = menu[i][0]; //gets item number
				bill[item_number][1] = menu[i][1]; //gets item name
				item_price[item_number][0] = prices[i];	//gets item price			
				break;
			}
		}
					printf("Quantity? ");
					scanf(" %d", &item_price[item_number][1]); //gets quantity
					int product = item_price[item_number][0]*item_price[item_number][1];
					total += product;
					printf("Total: %d\n", total);
					
					printf("Order another Item (y/n)? ");
					scanf(" %c", &order_control);
					item_number++;			
			} while((order_control =='y')||(order_control=='Y')&& item_number>50);
			
	printf("\nItem no.	item name [code]		unit price	qty	price\n");
	int j = 1;
	int i=0;
	int limit = item_number+1;
		for(i=0; i<limit; i++){
		int product = item_price[i][0]*item_price[i][1];
	
		printf("%3d	%20s [%s]		%5d		%d	%d\n", j, bill[i][1], bill[i][0], item_price[i][0], item_price[i][1], product);
		j++;
		if (j > item_number){
			printf("								Total: %5d",total);
			break;
		}
	}
		printf("\nDiscounted? ");
	printf("(0 - none, 1 - Senior(20%), 2- others (30%) ) ");
	scanf(" %d", &discount);
	
	switch(discount){
		case 0:{
			final_total = total;
			break;
		}
		case 1:{
			final_total = total-(0.2*total);
			break;
		}
		case 2: {
			final_total = total-(0.3*total);
			break;
		}
		default: {
			final_total = total;
			break;
		}
	}
	
	printf("\nFinal Total Amount: %d", final_total);
	do{
		printf("\nCash Issued: ");
		scanf(" %d", &issued_money);
		change = issued_money - final_total;
		if(change<0){
			printf("\nIssuficient funds. Request for correct amount.");
		}
	} while(change<0);
	
	printf("\nYour change for this transaction is %d php", change);
	printf("\nThank you for your purchase!!.");	
	return;
}


void Options(){
	int choice = 1;
	int var = 1;
	while(1){
		printf("\nOptions:\n");
		printf("1. Back to Menu\n");
		printf("2. Take Order\n");
		printf("3. Exit\n");
		printf("Options: ");
		var = scanf("%d", &choice);
		if(var == 0){
			printf("Invalid Input!");
			break;
		}
		switch(choice){
			case 1:{
				clear(6);
				order_list();
				clear(13);
				break;
			}
				case 2:{
					ordering();
					break;
				}
					case 3:{
						
						return;
					}
		}
	}
}
int main(){
	while(1){
		while((checkPass!=0)&&(checkUser!=0)){
		entrance();
		}
		clear(6);
		order_list();
		clear(10);
		Options();
		break;	
	}
	return 0;
}
	
		
