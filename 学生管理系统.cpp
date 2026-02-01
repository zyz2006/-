#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct account {
	char username[50];
	char password[50];
	char cpassword[50];
	struct account* next;
}account;

typedef struct information {
	char id[10];
	int clas;
	int classSort;
	int gradeSort;
	float chinesegrade;
	float englishgrade;
	float mathgrade;
	float totalgrade;
	float averagegrade;
	struct information* next;
}grade;

void teacherPortal(grade* gradeHead, account* accountHead);
void studentPortal(grade* gradeHead, account* accountHead);
void adminPortal(grade* gradeHead, account* accountHead);
account* registerFiction(account* accountHead);
void loginFiction(account* accountHead);
account* creatAccountLinklist();
account* changePassword(account* accountHead);
void seekAccount(account* accountHead);
account* insertAccount(account* accountHead);
account* deleteAccount(account* accountHead);
grade* creatGradeLinklist();
grade* recordGrade(grade* gradeHead);
grade* changeGrade(grade* gradeHead);
void seekGrade(grade* gradeHead);
grade* insertGrade(grade* gradeHead);
grade* ascendOrderGrade(grade* gradeHead);
grade* descendOrderGrade(grade* gradeHead);
grade* deleteGrade(grade* gradeHead);

int main()
{
	grade* gradeHead= creatGradeLinklist();
	account* accountHead= creatAccountLinklist();
	char r;
	printf("请问您的身份是：\n（A）老师\n（B）学生\n（C）管理员\n");
	printf("请选择‘A'，'B'，'C'\n");
	while (scanf("%c", &r) != EOF) {
		while (getchar() != '\n');
		if (r == 'A') {
			printf("现在进入教师端\n");
			teacherPortal(gradeHead, accountHead);
			break;
		}
		else if (r == 'B') {
			studentPortal( gradeHead, accountHead);
			printf("现在进入学生端\n");
			break;
		}
		else if (r == 'C') {
			adminPortal(gradeHead, accountHead);
			printf("现在进入管理员端\n");
			break;
		}
		else {
			printf("身份有误，请重新选择！");
		}
		
	}
}

//注册
account* registerFiction(account* accountHead)
{
	account* a=(account*)malloc(sizeof(account));
	if (a == NULL) {
		printf("内存分配失败，请重试！\n");
		return accountHead;
	}
	account* head = accountHead;
	printf("请输入小于20位的用户名\n");
	scanf("%49s", a->username);
	printf("请设置8到20位的密码\n");
	scanf("%49s", a->password);
	printf("请确认密码\n");
	scanf("%49s", a->cpassword);
	while (strlen(a->username) >= 20 || strlen(a->password) > 20 || strlen(a->password) < 8 || strcmp(a->password, a->cpassword) != 0) {
		if (strlen(a->username) >= 20) {
			printf("用户名过长！\n");
		}
		account* hea = accountHead;
		while (hea != NULL) {
			if (strcmp(hea->username, a->username) == 0) {
				printf("用户名已存在\n");
				break;
			}
			hea = hea->next;
		}
		if (strlen(a->password) > 20) {
			printf("密码过长！\n");
		}
		if (strlen(a->password) < 8) {
			printf("密码过短！\n");
		}
		if (strcmp(a->password, a->cpassword) != 0) {
			printf("确认密码与输入密码不一致！\n");
		}
		printf("请输入小于20位的用户名\n");
		scanf("%49s", a->username);
		printf("请设置8到20位的密码\n");
		scanf("%49s", a->password);
		printf("请确认密码\n");
		scanf("%49s", a->cpassword);
	}
	account* b = (account*)malloc(sizeof(account));
	if (b == NULL) {
		printf("内存分配失败，请重试！\n");
		free(a);
		return accountHead;
	}
	for (int i = 0; i < strlen(a->password); i++) {
		b->password[i] = a->password[i] + 5;
	}
	b->password[strlen(a->password)] = '\0';
	strcpy(b->username, a->username);
	if (head == NULL) {
		head = b;
	}
	else if (head->next == NULL) {
		head->next = b;
	}
	else {
		while (head->next != NULL) {
			head = head->next;
		}
		head->next = b;
	}
	b->next = NULL;
	printf("注册成功！\n");
	printf("请登录\n");
	free(a);
	return head;
}

//登录
void loginFiction(account* accountHead)
{
	account* login = (account*)malloc(sizeof(account));
	account* exist = accountHead;
	printf("请输入用户名。\n");
	scanf("%49s", login->username);
	printf("请输入密码。\n");
	scanf("%49s", login->password);
	//比对用户名和密码
	int userFound = 0;
	while (exist != NULL) {
		char tempPassword[50];
		for (int i = 0; i < strlen(exist->password); i++) {
			tempPassword[i] = exist->password[i] - 5;
		}
		tempPassword[strlen(exist->password)] = '\0';
		if (strcmp(exist->username, login->username) == 0) {
			userFound = 1;
			if (strcmp(tempPassword, login->password) == 0) {
				printf("登陆成功！\n");
				return;
			}
			else {
				do {
					printf("密码错误！\n");
					printf("请重新输入密码！(输入q重新设置密码）\n");
					scanf("%49s", login->password);
					if (strcmp(tempPassword, login->password) == 0) {
						printf("登陆成功！\n");
						return;
					}
					else if (strcmp(login->password, "q") == 0) {
						changePassword(accountHead);
					}
				} while (strcmp(tempPassword, login->password) != 0);

			}
		}
	}
	if (userFound == 0) {
		printf("用户名不存在！请先注册\n");
		return;
	}
}
//录入原始账户数据
account* creatAccountLinklist()
{
	account* accountHead = NULL;
	FILE * p = fopen("账户.txt","r");
	if (p == NULL) {
		p = fopen("账户.txt", "w");
		if (p == NULL) {
			printf("文件创建失败，请排除故障后重试！\n");
			return NULL;
		}
		else {
			fclose(p);
			printf("原始账户数据录入成功\n"); p = fopen("成绩信息.txt", "w");
			if (p == NULL) {
				printf("文件创建失败，请排除故障后重试！\n");
				return NULL;
			}
			else {
				fclose(p);
				return accountHead;
			}
			return accountHead;
		}
	}
	else {
		account* accountHead = NULL;
		account* tail = NULL;
		char tus[50], tpa[50];
		while (fscanf(p,"%49s %49s", tus, tpa) != EOF) {
			account* cur = (account*)malloc(sizeof(account));
			if (cur == NULL) {
				printf("内存分配失败，请重试！\n");
				fclose(p);
				return accountHead;
			}
			strcpy(cur->username, tus);
			strcpy(cur->password, tpa);
			cur->next = NULL;
			if (accountHead == NULL) {
				accountHead = cur;
				tail = cur;
			}
			else {
				tail->next = cur;
				tail = tail->next;
			}
		}
		fclose(p);
		printf("初始账户信息录入完成！\n");
		return accountHead;
	}
}

//修改密码
account* changePassword(account* accountHead)
{
	account* login = (account*)malloc(sizeof(account));
	account* exist = accountHead;
	int userFound = 0;
	printf("请输入用户名。\n");
	scanf("%49s", login->username);
	if (exist == NULL) {
		printf("不存在任何账户！\n");
		free(login);
		return exist;
	}
	while (exist != NULL) {
		if (strcmp(exist->username, login->username) == 0) {
			userFound = 1;
			printf("请输入新密码！\n");
			scanf("%49s", login->password);
			while (strlen(login->password) > 20 || strlen(login->password) < 8) {
				if (strlen(login->password) > 20) {
					printf("密码过长！\n");
				}
				if (strlen(login->password) < 8) {
					printf("密码过短！\n");
				}
				printf("请设置8到20位的密码\n");
				scanf("%49s", login->password);
			}
			account b = { 0 };
			for (int i = 0; i < strlen(login->password); i++) {
				b.password[i] = login->password[i] + 5;
			}
			b.password[strlen(login->password)] = '\0';
			strcpy(exist->password, b.password);
		}
		exist = exist->next;
	}
	if (userFound == 0) {
		printf("用户名不存在！请先注册\n");
	}
	else {
		printf("密码修改成功\n");
	}
	free(login);
	return accountHead;
}

//查找账户
void seekAccount(account* accountHead)
{
	if (accountHead == NULL) {
		printf("暂无任何账户可查找！\n");
		return;
	}
	account* head = accountHead;
	char tus[50],tempPassword[50];
	int found = 0;
	printf("请输入用户名！\n");
	scanf("%49s", tus);
	while (head != NULL) {
		if (strcmp(head->username,tus)==0) {
			found = 1;
			for (int i = 0; i < strlen(head->password); i++) {
				tempPassword[i] = head->password[i] - 5;
			}
			tempPassword[strlen(head->password)] = '\0';
			printf("密码为：%s\n", tempPassword);
			break;
		}
			head = head->next;
		
	}
	if (found == 0) {
		printf("用户不存在！\n");
	}
}

//插入账户
account* insertAccount(account* accountHead)
{
	account* cur = (account*)malloc(sizeof(account));
	int found = 0;
	if (cur == NULL) {
		printf("内存分配失败\n");
		return accountHead;
	}
	char place[50];
	printf("请输入账号\n");
	scanf("%49s", cur->username);
	printf("请输入密码\n");
	scanf("%49s", cur->password);
	printf("请输入要插入位置的前一位置账号\n");
	scanf("%49s", place);
	cur->next = NULL;
	if (accountHead == NULL) {
		printf("插入成功\n");
		return cur;
	}
	if (strcmp(accountHead->username, place) == 0) {
		cur->next = accountHead;
		accountHead = cur;
		printf("插入成功\n");
		return accountHead;
	}
	account* head = accountHead;
	while (head != NULL) {
		if (strcmp(head->username, place) == 0) {
			found = 1;
			cur->next = head->next;
			head->next = cur;
			printf("插入成功\n");
			break;
		}
		head = head->next;
	}
	if (found == 0) {
		printf("未找到插入位置\n");
		free(cur);
	}
	return accountHead;
}

//删除账户
account* deleteAccount(account* accountHead)
{
	if (accountHead == NULL) {
		printf("暂无账户\n");
		return accountHead;
	}
	char tus[50];
	printf("请输入要删除的账户名\n");
	scanf("%49s", tus);
	while (getchar() != '\n');
	if (strcmp(tus, accountHead->username) == 0) {
		char tch;
		printf("已找到账户信息，确认删除？(y/n)\n");
		while (scanf("%c", &tch) != EOF) {
			if (tch == 'Y' || tch == 'y') {
				account* freeHead = accountHead;
				accountHead = accountHead->next;
				free(freeHead);
				printf("删除成功\n");
				break;
			}
			else if (tch == 'N' || tch == 'n') {
				printf("已撤消删除\n");
				break;
			}
			else {
				printf("输入无效，请重试\n");
			}
		}
		return accountHead;
	}
	account* head = accountHead;
	account* cur = accountHead->next;
	int found = 0;
	while (cur != NULL) {
		if (strcmp(cur->username, tus) == 0) {
			found = 1;
			char tch;
			printf("已找到账户信息，确认删除？(y/n)\n");
			while (scanf("%c", &tch) != EOF) {
				if (tch == 'Y' || tch == 'y') {
					account* freeHead = cur;
					head->next = cur->next;
					free(freeHead);
					printf("删除成功\n");
					return accountHead;
				}
				else if (tch == 'N' || tch == 'n') {
					printf("已撤消删除\n");
					return accountHead;
				}
				else {
					printf("输入无效，请重试\n");
				}
			}
		}
		head = head->next;
		cur = cur->next;
	}
	if (found == 0) {
		printf("未找到账户\n");
	}
	return accountHead;
}

//录入原始成绩数据
grade* creatGradeLinklist()
{
	grade* gradeHead = NULL;
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
			return gradeHead;
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
				return gradeHead;
			}
			strcpy(cur->id,tid);
			cur->clas = clas;
			cur->chinesegrade=chinese;
			cur->englishgrade=english;
			cur->mathgrade=math;
			cur->totalgrade=total;
			cur->averagegrade=average;
			cur->next = NULL;
			if (gradeHead == NULL) {
				gradeHead = cur;
				tail = cur;
			}
			else {
				tail->next = cur;
				tail = tail->next;
			}
		}
		printf("原始成绩数据录入完成！\n");
		fclose(p);
		return gradeHead;
	}
}

//录入成绩
grade* recordGrade(grade* gradeHead)
{
	char choice;
	do {
		grade* tail = gradeHead;
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
			return gradeHead;
		}
		strcpy(cur->id, tid);
		cur->clas = clas;
		cur->chinesegrade = chinese;
		cur->englishgrade = english;
		cur->mathgrade = math;
		cur->totalgrade = total;
		cur->averagegrade = average;
		cur->next = NULL;

		if (gradeHead == NULL) {
			gradeHead = cur;
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
	return gradeHead;
}

//修改成绩
grade* changeGrade (grade* gradeHead)
{
	return gradeHead;
}

//查找成绩
void seekGrade(grade* gradeHead)
{
	printf("请输入您要查询学生的学号\n");
	char tid[15];
	scanf("%14s", tid);
	grade* cur = gradeHead;
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
		printf("语文成绩：%.2f\n", cur->chinesegrade);
		printf("数学成绩：%.2f\n", cur->mathgrade);
		printf("英语成绩：%.2f\n", cur->englishgrade);
		printf("总成绩：%.2f\n", cur->totalgrade);
		printf("平均成绩：%.2f\n", cur->averagegrade);
	}
	return;
}
//插入成绩
grade* insertGrade(grade* gradeHead)
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
		return gradeHead;
	}
	strcpy(cur->id, tid);
	cur->clas = clas;
	cur->chinesegrade = chinese;
	cur->englishgrade = english;
	cur->mathgrade = math;
	cur->totalgrade = total;
	cur->averagegrade = average;
	cur->next = NULL;
	if (gradeHead == NULL) {
		printf("还未录入学生成绩，已将此同学成绩作为第一位\n");
		return cur;
	}
	printf("请输入您要插入位置的前一位同学的学号！(若插入第一个位置，请输入0)\n");
	char preid[15];
	scanf("%14s", preid);
	if (strcmp(preid ,"0")==0) {
		cur->next = gradeHead;
		gradeHead = cur;
		printf("插入成功\n");
		return gradeHead;
	}
	else {
		grade* temp = gradeHead;
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
			printf("插入成功\n");
		}
		else {
			printf("未找到您指定的插入位置\n");
			free(cur);
		}
		return gradeHead;
	}
}

//升序排序
grade* ascendOrderGrade(grade* gradeHead)
{
	return gradeHead;
}

//降序排序
grade* descendOrderGrade(grade* gradeHead)
{
	return gradeHead;
}

//删除成绩
grade* deleteGrade(grade* gradeHead)
{
	return gradeHead;
}

void adminPortal(grade* gradeHead,account* accountHead)
{
	printf("您是否有账户？\n");
	printf("Y代表有，N代表没有，请输入：\n");
	char temp;
	while (scanf("%c", &temp) != EOF) {
		while (getchar() != '\n');
		if (temp == 'Y') {
			printf("请登录\n");
			loginFiction(accountHead);
			break;
		}
		else if (temp == 'N') {
			printf("请先注册在登陆\n");
			registerFiction(accountHead);
			break;
		}
		else {
			printf("输入有误，请重新输入！\n");
		}
	}
	return;
}

void teacherPortal(grade* gradeHead, account* accountHead)
{
	printf("您是否有账户？\n");
	printf("Y代表有，N代表没有，请输入：\n");
	char temp;
	while (scanf("%c", &temp) != EOF) {
		while (getchar() != '\n');
		if (temp == 'Y') {
			printf("请登录\n");
			loginFiction(accountHead);
			break;
		}
		else if (temp == 'N') {
			printf("请先注册在登陆\n");
			registerFiction(accountHead);
			break;
		}
		else {
			printf("输入有误，请重新输入！\n");
		}
	}
	return;
}

void studentPortal(grade* gradeHead, account* accountHead)
{
	printf("您是否有账户？\n");
	printf("Y代表有，N代表没有，请输入：\n");
	char temp;
	while (scanf("%c", &temp) != EOF) {
		while (getchar() != '\n');
		if (temp == 'Y') {
			printf("请登录\n");
			loginFiction(accountHead);
			break;
		}
		else if (temp == 'N') {
			printf("请先注册在登陆\n");
			registerFiction(accountHead);
			break;
		}
		else {
			printf("输入有误，请重新输入！\n");
		}
	}
	return;
}