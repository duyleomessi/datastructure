#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queuelist.h"

void MENU(){
	printf("\tMENU\n");
	printf("1. DOC DU LIEU\n");
	printf("2. TIEN HANH THI DAU\n");
	printf("3. XEP HANG VO SI\n");
	printf("4. THOAT\n");
}

int readFILE(queuetype** head, queuetype** tail, FILE* f, int* n); //trả lại 1 nếu đọc file thành công, 0 nếu đọc file lỗi
                                                                   // (có 1 phần tử < 0)
void THIDAU(queuetype** head1, queuetype** tail1, queuetype** head2, queuetype** tail2, queuetype** head, queuetype** tail);
void XEPHANG(queuetype** head, queuetype** tail);

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("There should be 3 argument:\n");
		printf("1. Executed file\n");
		printf("2. Input file 1\n");
		printf("3. Input file 2\n");
		return 0;
	}

	char* file1 = argv[1];
	char* file2 = argv[2];
	FILE* f1;
	FILE* f2;
	if((f1 = fopen(file1, "r")) == NULL){
		printf("%s does not exist!\n", file1);
		return 0;
	}
	if((f2 = fopen(file2, "r")) == NULL){
		printf("%s does not exist!\n", file2);
		return 0;
	}
	int n1 = 0; //số võ sĩ môn phái 1
	int n2 = 0; // số võ sĩ môn phái 2
	int check = 0; //nếu đọc 2 file thành công, check = 1. Các MENU còn lại chỉ sử dụng được khi check = 1
	queuetype* head1 = NULL; //môn phái 1
	queuetype* tail1 = NULL;
	
	queuetype* head2 = NULL; //môn phái 2
	queuetype* tail2 = NULL;
	
	queuetype* head = NULL; //tổng hợp điểm của 2 môn phái (MENU 3)
	queuetype* tail = NULL;
	
	int choice;
	do{
		MENU();
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		getchar();

		switch (choice){
		case 1:
		    if(readFILE(&head1, &tail1, f1, &n1) == 0){
		    	printf("File du lieu %s khong hop le.\n\n", file1);
				break;
			}
			else if(readFILE(&head2, &tail2, f2, &n2) == 0){
			   	printf("File du lieu %s khong hop le.\n\n", file2);
				break;
			}
		    if(n1 != n2){
				printf("Warning: Luc luong khong can bang.\nYeu cau sua lai so lieu.\n\n");
				break;
			}
			
			printf("\nMon phai 1:\n");
			displayQueue(head1);
			printf("\n\nMon phai 2:\n");
			displayQueue(head2);
			printf("\n");			
			check = 1;
			break;
			
		case 2:
			if(check ==0){
				printf("Khong co thong tin cac vo si!\n\n");
				break;
			}
			THIDAU(&head1, &tail1, &head2, &tail2, &head, &tail);
			break;
		case 3:
				if(check ==0){
				printf("Khong co thong tin cac vo si!\n\n");
				break;
				}
				XEPHANG(&head, &tail);
			break;
		case 4: 
			break;
		default:
			printf("Invalid value!\n\n");
		}
		
	}while(choice != 4);



	return 0;
}


int readFILE(queuetype** head, queuetype** tail, FILE* f, int* n){
	freeQueue(head, tail);
	fseek(f, 0, SEEK_SET);
	char buff[30];
	int i = 0;
	int flag = 0;
	char c;
	vosi a;
	*n = 0;
	while((c = fgetc(f)) != EOF)
	{
		if(c == '\n'){
			*n = *n + 1;
			a.phongthu = atoi(buff);
			if(a.phongthu < 0) return 0;
			a.diem = 0;
			enQueue(head, tail, a);
			strcpy(buff, "");
			i = 0;
			flag = 0;
		}
		else if (c == ' ')
		{
			flag ++;
			switch(flag){
			case 1:
				strcpy(a.name, buff);
				break;
			case 2:
				a.mau = atoi(buff);
				if (a.mau < 0) return 0; 
				break;
			case 3:
				a.tancong = atoi(buff);
				if (a.tancong < 0) return 0;
				break;
			case 4:
				a.nhanhnhen = atoi(buff);
				if(a.nhanhnhen < 0) return 0;
				break;				
			}
			strcpy(buff, "");
			i = 0;
		}
		else{
			buff[i++] = c;
			buff[i] = '\0';
		}
	}
	return 1;
}

void THIDAU(queuetype** head1, queuetype** tail1, queuetype** head2, queuetype** tail2, queuetype** head, queuetype** tail){
	vosi vosi1;
	vosi vosi2;
	int flag; //flag = 2 -> lượt võ sĩ 2 đánh, flag = 1 -> lượt võ sĩ 1 đánh  
	int i = 1; //thứ tự trận đấu 
	
	printf("\nLOI DAI BAT DAU\n");
	
	while(!isEmptyQueue(*head1) && !isEmptyQueue(*head2)){ //khi một trong 2 môn phái hết võ sĩ 
		vosi1 = deQueue(head1, tail1);
		vosi2 = deQueue(head2, tail2);

		printf("\n==========================================================================================================\n");
		printf("%50s %d\n", "TRAN", i++);
		printf("%s (MAU: %d TANCONG: %d NHANHNHEN: %d PHONGTHU: %d) vs %s (MAU: %d TANCONG: %d NHANHNHEN: %d PHONGTHU: %d)\n\n", vosi1.name, vosi1.mau, vosi1.tancong, vosi1.nhanhnhen, vosi1.phongthu, vosi2.name, vosi2.mau, vosi2.tancong, vosi2.nhanhnhen, vosi2.phongthu);

		//kiểm tra xem ai tấn công trước và thực hiện lượt đánh đầu tiên
		if(vosi1.nhanhnhen >= vosi2.nhanhnhen)
		{
			if(vosi1.tancong > vosi2.phongthu){
				printf("- %s (MAU %d, TANCONG %d) tan cong %s (MAU %d, PHONGTHU %d). %s mat %d mau.\n", vosi1.name, vosi1.mau, vosi1.tancong, vosi2.name, vosi2.mau, vosi2.phongthu, vosi2.name, vosi1.tancong - vosi2.phongthu);

				vosi2.mau -= (vosi1.tancong - vosi2.phongthu);
			}
			else{				
				printf("- %s (MAU %d, TANCONG %d) tan cong %s (MAU %d, PHONGTHU %d). %s mat %d mau.\n", vosi1.name, vosi1.mau, vosi1.tancong, vosi2.name, vosi2.mau, vosi2.phongthu, vosi1.name, vosi2.phongthu - vosi1.tancong);

				vosi1.mau -= (vosi2.phongthu - vosi1.tancong);
			}
			if(vosi1.mau <= 0){
	    		vosi2.diem += 3;
				//vosi1.diem += 1;
			}
			else if(vosi2.mau <= 0){
	    		vosi1.diem += 3;
			}
			else vosi1.diem += 1;
			flag = 2; // tiếp theo võ sĩ 2 tấn công 
		}
		else{
			if(vosi2.tancong > vosi1.phongthu){				
				printf("- %s (MAU %d, TANCONG %d) tan cong %s (MAU %d, PHONGTHU %d). %s mat %d mau.\n", vosi2.name, vosi2.mau, vosi2.tancong, vosi1.name, vosi1.mau, vosi1.phongthu, vosi1.name, vosi2.tancong - vosi1.phongthu);
				vosi1.mau -= (vosi2.tancong - vosi1.phongthu);
			}
			else{
				printf("- %s (MAU %d, TANCONG %d) tan cong %s (MAU %d, PHONGTHU %d). %s mat %d mau.\n", vosi2.name, vosi2.mau, vosi2.tancong, vosi1.name, vosi1.mau, vosi1.phongthu, vosi2.name, vosi1.phongthu - vosi2.tancong);
				vosi2.mau -= (vosi1.phongthu - vosi2.tancong);
			}
			if(vosi2.mau <= 0){
				vosi1.diem += 3;
				vosi2.diem += 1;
			}
			if(vosi1.mau <= 0){
				vosi2.diem += 3;
			}
			else vosi2.diem += 1;
			flag = 1; //tiếp theo võ sĩ 1 tấn công 
		}

		//thực hiện các lượt đánh còn lại 
		while(vosi1.mau > 0 && vosi2.mau > 0){
			switch(flag){
			case 1:
				if(vosi1.tancong > vosi2.phongthu){					
					printf("- %s (MAU %d, TANCONG %d) tan cong %s (MAU %d, PHONGTHU %d). %s mat %d mau.\n", vosi1.name, vosi1.mau, vosi1.tancong, vosi2.name, vosi2.mau, vosi2.phongthu, vosi2.name, vosi1.tancong - vosi2.phongthu);
					vosi2.mau -= (vosi1.tancong - vosi2.phongthu);
				}
				else{					
					printf("- %s (MAU %d, TANCONG %d) tan cong %s (MAU %d, PHONGTHU %d). %s mat %d mau.\n", vosi1.name, vosi1.mau, vosi1.tancong, vosi2.name, vosi2.mau, vosi2.phongthu, vosi1.name, vosi2.phongthu - vosi1.tancong);
					vosi1.mau -= (vosi2.phongthu - vosi1.tancong);
				}
					vosi1.diem += 1;
				flag = 2;
				break;
			case 2:
				if(vosi2.tancong > vosi1.phongthu){				 
					printf("- %s (MAU %d, TANCONG %d) tan cong %s (MAU %d, PHONGTHU %d). %s mat %d mau.\n", vosi2.name, vosi2.mau, vosi2.tancong, vosi1.name, vosi1.mau, vosi1.phongthu, vosi1.name, vosi2.tancong - vosi1.phongthu);
					vosi1.mau -= (vosi2.tancong - vosi1.phongthu);
				}
				else{					
					printf("- %s (MAU %d, TANCONG %d) tan cong %s (MAU %d, PHONGTHU %d). %s mat %d mau.\n", vosi2.name, vosi2.mau, vosi2.tancong, vosi1.name, vosi1.mau, vosi1.phongthu, vosi2.name, vosi1.phongthu - vosi2.tancong);
					vosi2.mau -= (vosi1.phongthu - vosi2.tancong);
				}
				vosi2.diem += 1;					
				flag = 1;
				break;
			}
		}
			
		if(vosi1.mau <= 0){ //võ sĩ 1 hi sinh 
			enQueue(head, tail, vosi1);
			insertAtHeadQueue(head2, head2, tail2, vosi2);
			printf("========================================= %s BI LOAI ================================================\n\n", vosi1.name);
		}
		else{ //võ sĩ 2 hi sinh 
			enQueue(head, tail, vosi2); 
			insertAtHeadQueue(head1, head1, tail1, vosi1);
			printf("========================================= %s BI LOAI ================================================\n\n", vosi2.name);		
		}
	}		

	//cho các võ sĩ còn sống vào trong queue chứa điểm 
	while(!isEmptyQueue(*head1))
		enQueue(head, tail, deQueue(head1, tail1));
	while(!isEmptyQueue(*head2))
		enQueue(head, tail, deQueue(head2, tail2));
	
	printf("\nKET QUA: ");
	if(isEmptyQueue(*head1))
		printf("Mon phai 1 THUA.\n\n");
	else printf("Mon phai 2 THUA.\n\n");
}

void XEPHANG(queuetype** head, queuetype** tail){
	//sort
	vosi tmp;
	for(queuetype* p = *head; p != NULL; p = p->next)
		for(queuetype* ptr = p->next; ptr != NULL; ptr = ptr->next)
			if(p->info.diem < ptr->info.diem){
				tmp = p->info;
				p->info = ptr->info;
				ptr->info = tmp;					
			}

	printf("\n\tBANG XEP HANG:\n\n");
	int i = 1;
	printf("%-5s%-20s%-15s\n\n", "STT", "BIET HIEU", "DIEM");
	for(queuetype* p = *head; p != NULL; p = p->next)
		printf("%-5d%-20s%-15d\n", i++, p->info.name, p->info.diem);
	printf("\n");
}
