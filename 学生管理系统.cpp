#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct account {
	char username[50];
	char password[50];
	char cpassword[50];
}account;

typedef struct information {
	char id[10];
	int clas;
	float chinesegrade;
	float englishgrade;
	float mathgrade;
	float totalgrade;
	float averagegrade;
	struct information* next;
}grade;

void teacherPortal();
void studentPortal();
void adminPortal();
void loginFiction();
void registerFiction();
void changePassword();
grade* creatLinklist();
grade* record(grade* head);
void seek(grade* head);
grade* insert(grade* head);

int main()
{
	char r;
	printf("请问您的身份是：\n（A）老师\n（B）学生\n（C）管理员\n");
	printf("请选择‘A'，'B'，'C'\n");
	while (scanf("%c", &r) != EOF) {
		while (getchar() != '\n');
		if (r == 'A') {
			printf("现在进入教师端");
			teacherPortal();
			break;
		}
		else if (r == 'B') {
			studentPortal();
			printf("现在进入学生端");
			break;
		}
		else if (r == 'C') {
			adminPortal();
			printf("现在进入管理员端");
			break;
		}
		else {
			printf("身份有误，请重新选择！");
		}
		
	}
}

void registerFiction()
{
	account a;

	printf("请输入小于20位的用户名\n");
	scanf("%49s", a.username);
	printf("请设置8到20位的密码\n");
	scanf("%49s", a.password);
	printf("请确认密码\n");
	scanf("%49s", a.cpassword);
	while (strlen(a.username) >= 20 || strlen(a.password) > 20 || strlen(a.password) < 8 || strcmp(a.password, a.cpassword) != 0) {
		if (strlen(a.username) >= 20) {
			printf("用户名过长！\n");
		}
		if (strlen(a.password) > 20) {
			printf("密码过长！\n");
		}
		if (strlen(a.password) < 8) {
			printf("密码过短！\n");
		}
		if (strcmp(a.password, a.cpassword) != 0) {
			printf("确认密码与输入密码不一致！\n");
		}
		printf("请输入小于20位的用户名\n");
		scanf("%49s", a.username);
		printf("请设置8到20位的密码\n");
		scanf("%49s", a.password);
		printf("请确认密码\n");
		scanf("%49s", a.cpassword);
	}
	account b;
	for (int i = 0; i < strlen(a.password); i++) {
		b.password[i] = a.password[i] + 5;
	}
	b.password[strlen(a.password)] = '\0';
	FILE* che=fopen("账户.txt", "r");
	if (che != NULL) {
		account exist;
		while (fscanf(che, "%s %s", exist.username, exist.password) != EOF) {
			if (strcmp(a.username, exist.username) == 0 ) {
				printf("用户名已存在！\n");
				return;
			}
		}
	}
	fclose(che);
	FILE* p = fopen("账户.txt", "a");
	if (p == NULL) {
		printf("文件打开失败，请排除错误后重试！\n");
		return;
	}
	fprintf(p, "%s %s\n", a.username, b.password);
	fclose(p);
	printf("注册成功！\n");
	printf("请登录\n");
	loginFiction();
	return;
}

void changePassword()
{
	account login,exist;
	int userFound = 0;
	printf("请输入用户名。\n");
	scanf("%49s", login.username);
	FILE* p = fopen("账户.txt", "r");
	if (p == NULL) {
		printf("文件打开失败，请排除错误后重试！\n");
		return;
	}
	FILE* temp = fopen("临时文件.txt", "w");
		if (temp == NULL) {
			printf("临时文件创建失败！\n");
			fclose(p);
			return;
		}
		while (fscanf(p, "%s %s", exist.username, exist.password) != EOF) {
			if (strcmp(exist.username, login.username) == 0) {
				userFound = 1;
				printf("请输入新密码！\n");
				scanf("%49s", login.password);
				while (strlen(login.password) > 20 || strlen(login.password) < 8) {
					if (strlen(login.password) > 20) {
						printf("密码过长！\n");
					}
					if (strlen(login.password) < 8) {
						printf("密码过短！\n");
					}
					printf("请设置8到20位的密码\n");
					scanf("%49s", login.password);
				}
				account b;
				for (int i = 0; i < strlen(login.password); i++) {
					b.password[i] = login.password[i] + 5;
				}
				b.password[strlen(login.password)] = '\0';
				strcpy(exist.password, b.password);
			}
			fprintf(temp, "%s %s\n", exist.username, exist.password);
		}
	fclose(p);
	fclose(temp);
	if (userFound == 0) {
		printf("用户名不存在！请先注册\n");
	}
	else {
		remove("账户.txt");
		rename("临时文件.txt", "账户.txt");
		printf("密码修改成功\n");
	}
	return;
}

void loginFiction()
{
	account login;
	printf("请输入用户名。\n");
	scanf("%49s", login.username);
	printf("请输入密码。\n");
	scanf("%49s", login.password);
	
	FILE* che = fopen("账户.txt", "r");
	if (che == NULL) {
		printf("文件打开失败，请排除错误后重试！\n");
		return;
	}
	account exist;
	int userFound = 0;
	//比对用户名和密码
	while (fscanf(che, "%s %s", exist.username, exist.password) != EOF) {
		char tempPassword[50];
		for (int i = 0; i < strlen(exist.password); i++) {
			tempPassword[i] = exist.password[i] - 5;
		}
		tempPassword[strlen(exist.password)] = '\0';
		if (strcmp(exist.username, login.username) == 0) {
			userFound = 1;
			if (strcmp(tempPassword, login.password) == 0) {
				printf("登陆成功！\n");
				fclose(che);
				return;
			}
			else {
				do {
					printf("密码错误！\n");
					printf("请重新输入密码！(输入q重新设置密码）\n");
					scanf("%49s", login.password);
					if (strcmp(tempPassword, login.password) == 0) {
						printf("登陆成功！\n");
						fclose(che);
						return;
					}
					else if (login.password == "q") {
						changePassword();
					}
				} while (strcmp(tempPassword, login.password) != 0);
			
			}
		}		
	}
	if (userFound == 0) {
		printf("用户名不存在！请先注册\n");
		return;
	}
	
	fclose(che);
}

grade* creatLinklist()
{
	grade* head = NULL;
	grade* tail = NULL;
	FILE* p = fopen("成绩信息.txt", "r");
	if (p == NULL) {
		p = fopen("成绩信息.txt", "w");
		if (p == NULL) {
			printf("文件创建失败，请排除故障后重试！\n");
			return NULL;
		}
		else {
			fclose(p);
			return head;
		}
	}
	else {
		char tid[15];
		int clas;
		float chinese, math, english, total, average;
		while (fscanf(p, "%13s %d %f %f %f %f %f", tid, &clas, &chinese,&english,&math,&total,&average) != EOF) {
			grade* cur = (grade*)malloc(sizeof(grade));
			if (cur == NULL) {
				printf("内存分配失败，请重试！\n");
				fclose(p);
				return head;
			}
			strcpy(cur->id,tid);
			cur->clas = clas;
			cur->chinesegrade=chinese;
			cur->englishgrade=english;
			cur->mathgrade=math;
			cur->totalgrade=total;
			cur->averagegrade=average;
			cur->next = NULL;
			if (head == NULL) {
				head = cur;
				tail = cur;
			}
			else {
				tail->next = cur;
				tail = tail->next;
			}
		}
		printf("原始数据录入完成！\n");
		fclose(p);
		return head;
	}
}

grade* record(grade* head)
{
	char choice;
	do {
		grade* tail = head;
		while (tail != NULL && tail->next != NULL) {
			tail = tail->next;
		}
		char tid[15];
		int clas;
		float chinese, math, english, total, average;
		printf("请输入学生的学号\n");
		scanf("%s", tid);
		printf("请输入学生的班级\n");
		scanf("%d", &clas);
		printf("请输入学生的语文成绩\n");
		scanf("%f", &chinese);
		printf("请输入学生的数学成绩\n");
		scanf("%f", &math);
		printf("请输入学生的英语成绩\n");
		scanf("%f", &english);
		total = chinese + math + english;
		average = total / 3;
		grade* cur = (grade*)malloc(sizeof(grade));
		if (cur == NULL) {
			printf("内存分配失败，请重试！\n");
			return head;
		}
		strcpy(cur->id, tid);
		cur->clas=clas
		cur->chinesegrade = chinese;
		cur->englishgrade = english;
		cur->mathgrade = math;
		cur->totalgrade = total;
		cur->averagegrade = average;
		cur->next = NULL;

		if (head == NULL) {
			head = cur;
			tail = cur;
		}
		else {
			tail->next = cur;
			tail = tail->next;
		}
		printf("是否录入下一位学生的成绩（Y/N）\n");
		while(getchar()!='\n');
		scanf("%c", &choice);
	} while (choice == 'Y'|| choice == 'y');
	return head;
}

void seek(grade* head)
{
	printf("请输入您要查询学生的学号\n");
	char tid[15];
	scanf("%14s", tid);
	grade* cur = head;
	int found = 0;
	while (cur != NULL) {
		if (strcmp(cur->id, tid) == 0) {
			found = 1;
			break;
		}
			cur = cur->next;
	}
	if (found == 0) {
		printf("未查询到成绩，请重试！\n");
	}
	else {
		printf("语文成绩：%.2f\n数学成绩：%.2f\n英语成绩：%.2f\n总成绩：%.2f\n平均成绩：%.2f\n", cur->chinesegrade, cur->mathgrade, cur->englishgrade, cur->totalgrade, cur->averagegrade);
	}
	return;
}

grade* insert(grade* head)
{
	char tid[15];
	int clas;
	float chinese, math, english, total, average;
	printf("请输入学生的学号\n");
	scanf("%14s", tid);
	printf("请输入学生的班级\n");
	scanf("%d", &clas);
	printf("请输入学生的语文成绩\n");
	scanf("%f", &chinese);
	printf("请输入学生的数学成绩\n");
	scanf("%f", &math);
	printf("请输入学生的英语成绩\n");
	scanf("%f", &english);
	total = chinese + math + english;
	average = total / 3;
	grade* cur = (grade*)malloc(sizeof(grade));
	if (cur == NULL) {
		printf("内存分配失败，请重试！\n");
		return head;
	}
	strcpy(cur->id, tid);
	cur->clas = clas;
	cur->chinesegrade = chinese;
	cur->englishgrade = english;
	cur->mathgrade = math;
	cur->totalgrade = total;
	cur->averagegrade = average;
	cur->next = NULL;
	if (head == NULL) {
		printf("还未录入学生成绩，已将此同学成绩作为第一位\n");
		return cur;
	}
	printf("请输入您要插入位置的前一位同学的学号！(若插入第一个位置，请输入0)\n");
	char preid[15];
	scanf("%14s", preid);
	if (strcmp(preid ,"0")==0) {
		cur->next = head;
		head = cur;
		return head;
	}
	else {
		grade* temp = head;
		int found = 0;
		while (temp != NULL) {
			if (strcmp(temp->id, preid) == 0) {
				found = 1;
				break;
			}
			temp = temp->next;
		}
		if (found == 1) {
			cur->next = temp->next;
			temp->next = cur;
		}
		else {
			printf("未找到您指定的插入位置\n");
			free(cur);
		}
		return head;
	}
}

void adminPortal()
{
	printf("您是否有账户？\n");
	printf("Y代表有，N代表没有，请输入：\n");
	char temp;
	while (scanf("%c", &temp) != EOF) {
		while (getchar() != '\n');
		if (temp == 'Y') {
			printf("请登录\n");
			loginFiction();
			break;
		}
		else if (temp == 'N') {
			printf("请先注册在登陆\n");
			registerFiction();
			break;
		}
		else {
			printf("输入有误，请重新输入！\n");
		}
	}
	return;
}

void teacherPortal()
{
	printf("您是否有账户？\n");
	printf("Y代表有，N代表没有，请输入：\n");
	char temp;
	while (scanf("%c", &temp) != EOF) {
		while (getchar() != '\n');
		if (temp == 'Y') {
			printf("请登录\n");
			loginFiction();
			break;
		}
		else if (temp == 'N') {
			printf("请先注册在登陆\n");
			registerFiction();
			break;
		}
		else {
			printf("输入有误，请重新输入！\n");
		}
	}
	return;
}

void studentPortal()
{
	printf("您是否有账户？\n");
	printf("Y代表有，N代表没有，请输入：\n");
	char temp;
	while (scanf("%c", &temp) != EOF) {
		while (getchar() != '\n');
		if (temp == 'Y') {
			printf("请登录\n");
			loginFiction();
			break;
		}
		else if (temp == 'N') {
			printf("请先注册在登陆\n");
			registerFiction();
			break;
		}
		else {
			printf("输入有误，请重新输入！\n");
		}
	}
	return;
}