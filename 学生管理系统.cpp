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

void teacherPortal(grade** gradeHead, account* accountHead);
void studentPortal(grade* gradeHead, account* accountHead);
void adminPortal(grade** gradeHead, account* accountHead);
account* prelogin(grade* gradeHead, account* accountHead);
account* registerFiction(account* accountHead);
account* loginFiction(account* accountHead);
account* creatAccountLinklist();
account* changePassword(account* accountHead);
void seekAccount(account* accountHead);
account* insertAccount(account* accountHead);
account* deleteAccount(account* accountHead);
grade* creatGradeLinklist();
grade* recordGrade(grade* gradeHead);
grade* changeGrade(grade* gradeHead);
void seekGrade(grade* gradeHead);
void seekClassGrade(grade* gradeHead);
void gradeAppeal();
void dealAppeal();
grade* insertGrade(grade* gradeHead);
grade* ascendOrderGrade(grade* gradeHead);
grade* descendOrderGrade(grade* gradeHead);
grade* deleteGrade(grade* gradeHead);
grade* rank(grade* gradeHead);
grade* gradeFile(grade* gradeHead);
account* accountFile(account* accountHead);

int main()
{
	grade* gradeHead= creatGradeLinklist();
	account* accountHead= creatAccountLinklist();
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	char r, tch='N';
	do {
		accountHead = prelogin(gradeHead, accountHead);
		printf("请问您的身份是：\n（A）老师\n（B）学生\n（C）管理员\n");
		printf("请选择‘A'，'B'，'C'\n");
		while (scanf("%c", &r) != EOF) {
			while (getchar() != '\n');
			if (r == 'A'||r=='a') {
				printf("现在进入教师端\n");
				teacherPortal(&gradeHead, accountHead);
				break;
			}
			else if (r == 'B'||r=='b') {
				printf("现在进入学生端\n");
				studentPortal(gradeHead, accountHead);
				break;
			}
			else if (r == 'C'||r=='c') {
				printf("现在进入管理员端\n");
				adminPortal(&gradeHead, accountHead);
				break;
			}
			else {
				printf("身份有误，请重新选择！\n");
			}
		}
		printf("是否更换账号进行其他操作(除了Y与y其他均视为不进行其他操作)\n");
		scanf("%c", &tch);
		while (getchar() != '\n');
	} while (tch == 'Y' || tch == 'y');
	gradeFile(gradeHead);
	accountFile(accountHead);
	return 0;
}

//判断是否有账户
account* prelogin(grade* gradeHead, account* accountHead)
{
	printf("您是否有账户？\n");
	printf("Y代表有，N代表没有，请输入：\n");
	char temp;
	while (scanf("%c", &temp) != EOF) {
		while (getchar() != '\n');
		if (temp == 'Y'||temp=='y') {
			printf("请登录\n");
			for (int i = 0; i < 30; i++) {
				printf("=");
			}
			printf("\n");
			accountHead=loginFiction(accountHead);
			break;
		}
		else if (temp == 'N'||temp=='n') {
			printf("请先注册再登陆\n");
			for (int i = 0; i < 30; i++) {
				printf("=");
			}
			printf("\n");
			accountHead=registerFiction(accountHead);
			break;
		}
		else {
			printf("输入有误，请重新输入！\n");
		}
	}
	return accountHead;
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
	while (getchar() != '\n');
	printf("请设置8到20位的密码\n");
	scanf("%49s", a->password);
	while (getchar() != '\n');
	printf("请确认密码\n");
	scanf("%49s", a->cpassword);
	while (getchar() != '\n');
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
		while (getchar() != '\n');
		printf("请设置8到20位的密码\n");
		scanf("%49s", a->password);
		while (getchar() != '\n');
		printf("请确认密码\n");
		scanf("%49s", a->cpassword);
		while (getchar() != '\n');
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
	else {
		account* p = head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = b;
	}
	b->next = NULL;
	printf("注册成功！\n");
	printf("请登录\n");
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	accountHead = loginFiction(head);
	free(a);
	return accountHead;
}

//登录
account* loginFiction(account* accountHead)
{
	account* login = (account*)malloc(sizeof(account));
	account* exist = accountHead;
	printf("请输入用户名。\n");
	scanf("%49s", login->username);
	while (getchar() != '\n');
	printf("请输入密码。\n");
	scanf("%49s", login->password);
	while (getchar() != '\n');
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
				free(login);
				return accountHead;
			}
			else {
				do {
					printf("密码错误！\n");
					printf("请重新输入密码！(输入q重新设置密码）\n");
					scanf("%49s", login->password);
					while (getchar() != '\n');
					if (strcmp(tempPassword, login->password) == 0) {
						printf("登陆成功！\n");
						for (int i = 0; i < 30; i++) {
							printf("=");
						}
						printf("\n");
						free(login);
						return accountHead;
					}
					else if (strcmp(login->password, "q") == 0) {
						for (int i = 0; i < 30; i++) {
							printf("=");
						}
						printf("\n");
						free(login);
						accountHead=changePassword(accountHead);
						return accountHead;
					}
				} while (strcmp(tempPassword, login->password) != 0);

			}
		}
		exist = exist->next;
	}
	if (userFound == 0) {
		printf("用户名不存在！请先注册\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		free(login);
		accountHead=registerFiction(accountHead);
		return accountHead;
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
			printf("原始账户数据录入成功\n"); 
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
	while (getchar() != '\n');
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
			while (getchar() != '\n');
			while (strlen(login->password) > 20 || strlen(login->password) < 8) {
				if (strlen(login->password) > 20) {
					printf("密码过长！\n");
				}
				if (strlen(login->password) < 8) {
					printf("密码过短！\n");
				}
				printf("请设置8到20位的密码\n");
				scanf("%49s", login->password);
				while (getchar() != '\n');
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
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		registerFiction(accountHead);
	}
	else {
		printf("密码修改成功\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	}
	free(login);
	return accountHead;
}

//查找账户
void seekAccount(account* accountHead)
{
	if (accountHead == NULL) {
		printf("暂无任何账户可查找！\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return;
	}
	account* head = accountHead;
	char tus[50],tempPassword[50];
	int found = 0;
	printf("请输入用户名！\n");
	scanf("%49s", tus);
	while (getchar() != '\n');
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
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return;
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
	while (getchar() != '\n');
	account* newnode = accountHead;
	while (newnode != NULL) {
		if (newnode->username == cur->username) {
			printf("账户已存在\n");
			free(cur);
			return accountHead;
		}
	}
	printf("请输入密码\n");
	scanf("%49s", cur->password);
	while (getchar() != '\n');
	printf("请输入要插入位置的前一位置账号\n");
	scanf("%49s", place);
	while (getchar() != '\n');
	cur->next = NULL;
	if (accountHead == NULL) {
		printf("插入成功\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return cur;
	}
	if (strcmp(accountHead->username, place) == 0) {
		cur->next = accountHead;
		accountHead = cur;
		printf("插入成功\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
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
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return accountHead;
}

//删除账户
account* deleteAccount(account* accountHead)
{
	if (accountHead == NULL) {
		printf("暂无账户\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
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
			while (getchar() != '\n');
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
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
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
				while (getchar() != '\n');
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
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
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
			printf("原始成绩信息录入成功\n");
			return gradeHead;
		}
	}
	else {
		char tid[15];
		int clas,classSort,gradeSort;
		float chinese, math, english, total, average;
		while (fscanf(p, "%13s %d %d %d %f %f %f %f %f", tid, &clas, &classSort,&gradeSort,&chinese,&english,&math,&total,&average) != EOF) {
			grade* cur = (grade*)malloc(sizeof(grade));
			if (cur == NULL) {
				printf("内存分配失败，请重试！\n");
				fclose(p);
				return gradeHead;
			}
			strcpy(cur->id,tid);
			cur->clas = clas;
			cur->classSort = classSort;
			cur->gradeSort = gradeSort;
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
	char choice,tt='q';
	do {
		grade* tail = gradeHead;
		while (tail != NULL && tail->next != NULL) {
			tail = tail->next;
		}
		char tid[15];
		int clas,found=0;
		float chinese, math, english, total, average;
		printf("请输入学生的学号\n");
		scanf("%14s", tid);
		while (getchar() != '\n');
		grade* cu = gradeHead;
		while (cu != NULL) {
			if (strcmp(tid, cu->id) == 0) {
				printf("该学生成绩已录入\n");
				found = 1;
				break;
			}
			cu = cu->next;
		}
		if (found == 1) {
			printf("是否录入其他人的成绩？(除了Y与y其他均视为不录入)\n");
			scanf("%c", &tt);
			while (getchar() != '\n');
			for (int i = 0; i < 30; i++) {
				printf("=");
			}
			printf("\n");
			continue;
		}
		printf("请输入学生的班级(1/2)\n");
		scanf("%d", &clas);
		while (getchar() != '\n');
		printf("请输入学生的语文成绩\n");
		scanf("%f", &chinese);
		while (getchar() != '\n');
		printf("请输入学生的数学成绩\n");
		scanf("%f", &math);
		while (getchar() != '\n');
		printf("请输入学生的英语成绩\n");
		scanf("%f", &english);
		while (getchar() != '\n');
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
		printf("是否录入下一位学生的成绩（除了Y与y其他均视为不录入）\n");
		scanf("%c", &choice);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (choice == 'Y'|| choice == 'y');
	return gradeHead;
}

//修改成绩
grade* changeGrade (grade* gradeHead)
{
	char tid[15];
	printf("请输入您要修改学生的学号\n");
	scanf("%14s", tid);
	while (getchar() != '\n');
	grade* cur = gradeHead;
	int found = 0;
	while (cur != NULL) {
		if (strcmp(cur->id, tid) == 0) {
			found = 1;
			printf("请输入要修改的科目，语文（C）英语（E）数学（M）\n");
			char tch;
			while (scanf("%c", &tch) != EOF) {
				while (getchar() != '\n');
				if (tch == 'C' || tch == 'c') {
					printf("请输入新成绩\n");
					float newgr;
					scanf("%f", &newgr);
					while (getchar() != '\n');
					cur->chinesegrade = newgr;
					cur->totalgrade = cur->chinesegrade + cur->englishgrade + cur->mathgrade;
					cur->averagegrade = cur->totalgrade / 3;
					printf("成绩修改完成\n");
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					return gradeHead;
				}
				else if (tch == 'E' || tch == 'e') {
					printf("请输入新成绩\n");
					float newgr;
					scanf("%f", &newgr);
					while (getchar() != '\n');
					cur->englishgrade = newgr;
					cur->totalgrade = cur->chinesegrade + cur->englishgrade + cur->mathgrade;
					cur->averagegrade = cur->totalgrade / 3;
					printf("成绩修改完成\n");
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					return gradeHead;
				}
				else if (tch == 'M' || tch == 'm') {
					printf("请输入新成绩\n");
					float newgr;
					scanf("%f", &newgr);
					while (getchar() != '\n');
					cur->mathgrade = newgr;
					cur->totalgrade = cur->chinesegrade + cur->englishgrade + cur->mathgrade;
					cur->averagegrade = cur->totalgrade / 3;
					printf("成绩修改完成\n");
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					return gradeHead;
				}
				else {
					printf("输入无效，请重试\n");
				}
			}
		}
		cur = cur->next;
	}
	if (found == 0) {
		printf("未找到对应学生\n");
	}
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return gradeHead;
}

//查找成绩
void seekGrade(grade* gradeHead)
{
	char tch;
	do {
		printf("请输入您要查询学生的学号\n");
		char tid[15];
		scanf("%14s", tid);
		while (getchar() != '\n');
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
			printf("班级排名：%d\n", cur->classSort);
			printf("年级排名：%d\n", cur->gradeSort);
		}
		printf("是否继续查询？(除了Y与y其他均视为不查找)\n");
		scanf("%c", &tch);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tch == 'y' || tch == 'Y');
	return;
}

//查询班级成绩
void seekClassGrade(grade* gradeHead)
{
	char tch;
	do {
		printf("请输入您要查询的班级\n");
		int clas,found=0;
		scanf("%d", &clas);
		while (getchar() != '\n');
		grade* cur = gradeHead;
		while (cur != NULL) {
			if (cur->clas == clas) {
				found = 1;
				printf("学号:%s\n", cur->id);
				printf("语文成绩：%.2f\t", cur->chinesegrade);
				printf("数学成绩：%.2f\t", cur->mathgrade);
				printf("英语成绩：%.2f\n", cur->englishgrade);
				printf("总成绩：%.2f\t", cur->totalgrade);
				printf("平均成绩：%.2f\n", cur->averagegrade);
				printf("班级排名：%d\t", cur->classSort);
				printf("年级排名：%d\n", cur->gradeSort);
			}
			cur = cur->next;
		}
		if (found == 0) {
			printf("暂无该班级成绩\n");
		}
		printf("是否继续查询？(除了Y与y其他均视为不查询)\n");
		scanf("%c", &tch);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tch == 'y' || tch == 'Y');
	return;
}

//成绩申诉
void gradeAppeal()
{
	FILE* p = fopen("申诉.txt", "a");
	if (p == NULL) {
		printf("申诉文件创建失败\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return;
	}
	char te[100],tch;
	do {
		printf("请写清申诉内容，包括,考试名称，学号和问题(90字以内）\n");
		scanf("%s", te);
		while (getchar() != '\n');
		fprintf(p, "%s\n", te);
		printf("是否还有其它问题？(y/n)\n");
		scanf("%c", &tch);
		while (getchar() != '\n');
	} while (tch == 'y' || tch == 'Y');
	printf("申诉问题已记录\n");
	fclose(p);
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return;
}

//处理申诉
void dealAppeal()
{
	char line[100];
	FILE* p = fopen("申诉.txt", "r");
	if (p == NULL) {
		printf("申诉文件打开失败\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return;
	}
	while (fgets(line, sizeof(line), p) != NULL) {
		line[strcspn(line, "\n")] = '\0';
		printf("%s\n", line);
	}
	printf("申诉问题查看完毕\n");
	fclose(p);
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return;
}
//插入成绩
grade* insertGrade(grade* gradeHead)
{
	char tid[15];
	int clas,found=0;
	float chinese, math, english, total, average;
	printf("请输入学生的学号\n");
	scanf("%14s", tid);
	while (getchar() != '\n');
	grade* cu = gradeHead;
	while (cu != NULL) {
		if (strcmp(tid, cu->id) == 0) {
			printf("该学生成绩已录入\n");
			return gradeHead;
		}
		cu = cu->next;
	}
	printf("请输入学生的班级\n");
	scanf("%d", &clas);
	while (getchar() != '\n');
	printf("请输入学生的语文成绩\n");
	scanf("%f", &chinese);
	while (getchar() != '\n');
	printf("请输入学生的数学成绩\n");
	scanf("%f", &math);
	while (getchar() != '\n');
	printf("请输入学生的英语成绩\n");
	scanf("%f", &english);
	while (getchar() != '\n');
	total = chinese + math + english;
	average = total / 3;
	grade* cur = (grade*)malloc(sizeof(grade));
	if (cur == NULL) {
		printf("内存分配失败，请重试！\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
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
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return cur;
	}
	printf("请输入您要插入位置的前一位同学的学号！(若插入第一个位置，请输入0)\n");
	char preid[15];
	scanf("%14s", preid);
	while (getchar() != '\n');
	if (strcmp(preid ,"0")==0) {
		cur->next = gradeHead;
		gradeHead = cur;
		printf("插入成功\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
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
	if (gradeHead == NULL || gradeHead->next == NULL) {
		return gradeHead;
	}
	grade* head = gradeHead;

	while (head != NULL) {
		grade* cur = head->next;
		while (cur != NULL) {
			if (head->totalgrade > cur->totalgrade) {
				grade temp;
				temp.averagegrade = head->averagegrade;
				temp.chinesegrade = head->chinesegrade;
				temp.clas = head->clas;
				temp.classSort = head->classSort;
				temp.englishgrade = head->englishgrade;
				temp.gradeSort = head->gradeSort;
				strcpy(temp.id, head->id);
				temp.mathgrade = head->mathgrade;
				temp.totalgrade = head->totalgrade;

				head->averagegrade = cur->averagegrade;
				head->chinesegrade = cur->chinesegrade;
				head->clas = cur->clas;
				head->classSort = cur->classSort;
				head->englishgrade = cur->englishgrade;
				head->gradeSort = cur->gradeSort;
				strcpy(head->id, cur->id);
				head->mathgrade = cur->mathgrade;
				head->totalgrade = cur->totalgrade;

				cur->averagegrade = temp.averagegrade;
				cur->chinesegrade = temp.chinesegrade;
				cur->clas = temp.clas;
				cur->classSort = temp.classSort;
				cur->englishgrade = temp.englishgrade;
				cur->gradeSort = temp.gradeSort;
				strcpy(cur->id, temp.id);
				cur->mathgrade = temp.mathgrade;
				cur->totalgrade = temp.totalgrade;
			}
			cur = cur->next;
		}
		head = head->next;
	}
	printf("升序排序完成\n");
	return gradeHead;
}
//降序排序
grade* descendOrderGrade(grade* gradeHead)
{
	if (gradeHead == NULL || gradeHead->next == NULL) {
		return gradeHead;
	}
	grade* head = gradeHead;

	while (head != NULL) {
		grade* cur = head->next;
		while (cur != NULL) {
			if (head->totalgrade < cur->totalgrade) {
				grade temp;
				temp.averagegrade = head->averagegrade;
				temp.chinesegrade = head->chinesegrade;
				temp.clas = head->clas;
				temp.classSort = head->classSort;
				temp.englishgrade = head->englishgrade;
				temp.gradeSort = head->gradeSort;
				strcpy(temp.id, head->id);
				temp.mathgrade = head->mathgrade;
				temp.totalgrade = head->totalgrade;

				head->averagegrade = cur->averagegrade;
				head->chinesegrade = cur->chinesegrade;
				head->clas = cur->clas;
				head->classSort = cur->classSort;
				head->englishgrade = cur->englishgrade;
				head->gradeSort = cur->gradeSort;
				strcpy(head->id, cur->id);
				head->mathgrade = cur->mathgrade;
				head->totalgrade = cur->totalgrade;

				cur->averagegrade = temp.averagegrade;
				cur->chinesegrade = temp.chinesegrade;
				cur->clas = temp.clas;
				cur->classSort = temp.classSort;
				cur->englishgrade = temp.englishgrade;
				cur->gradeSort = temp.gradeSort;
				strcpy(cur->id, temp.id);
				cur->mathgrade = temp.mathgrade;
				cur->totalgrade = temp.totalgrade;
			}
			cur = cur->next;
		}
		head = head->next;
	}
	printf("降序排序完成\n");
	return gradeHead;
}

//排名
grade* rank(grade* gradeHead)
{
	if (gradeHead == NULL) {
		printf("暂无成绩\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return gradeHead;
	}
	int i = 1, j = 1, k = 1;
	gradeHead=descendOrderGrade(gradeHead);
	grade* cur = gradeHead;
	while (cur != NULL) {
		cur->gradeSort = k;
		k++;
		if (cur->clas == 1) {
			cur->classSort = i;
			i++;
		}
		else {
			cur->classSort = j;
			j++;
		}
		cur = cur->next;
	}
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return gradeHead;
}

//删除成绩
grade* deleteGrade(grade* gradeHead)
{
	if (gradeHead == NULL) {
		printf("还未录入任何成绩\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return gradeHead;
	}
	printf("请输入要删除学生的学号\n");
	char tid[15];
	scanf("%s", tid);
	while (getchar() != '\n');
	if (strcmp(gradeHead->id, tid) == 0) {
		printf("确认删除？（Y/N）\n");
		char tch;
		while (scanf("%c", &tch) != EOF) {
			while (getchar() != '\n');
			if (tch == 'y' || tch == 'Y') {
				grade* freeHead = gradeHead;
				gradeHead = gradeHead->next;
				printf("删除成功\n");
				free(freeHead);
				for (int i = 0; i < 30; i++) {
					printf("=");
				}
				printf("\n");
				return gradeHead;
			}
			else if (tch == 'N' || tch == 'n') {
				printf("删除已撤销\n");
				for (int i = 0; i < 30; i++) {
					printf("=");
				}
				printf("\n");
				return gradeHead;
			}
			else {
				printf("输入无效，请重试\n");
				while (getchar() != '\n');
			}
		}
	}
	grade* head = gradeHead;
	grade* cur = gradeHead->next;
	int found = 0;
	while (cur != NULL) {
		if (strcmp(cur->id, tid) == 0) {
			found = 1;
			printf("确认删除？（Y/N）\n");
			char tch;
			while (scanf("%c", &tch) != EOF) {
				while (getchar() != '\n');
				if (tch == 'y' || tch == 'Y') {
					head->next = cur->next;
					printf("删除成功\n");
					free(cur);
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					gradeHead = rank(gradeHead);
					return gradeHead;
				}
				else if (tch == 'N' || tch == 'n') {
					printf("删除已撤销\n");
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					return gradeHead;
				}
				else {
					printf("输入无效，请重试\n");
					while (getchar() != '\n');
				}
			}
		}
		head = head->next;
		cur = cur->next;
	}
	if (found == 0) {
		printf("未找到对应学生\n");
	}
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return gradeHead;
}

//管理员端
void adminPortal(grade** gradeHead,account* accountHead)
{
	char tch,tc;
	do {
		printf("请选择您要进行的操作\n");
		printf("A.修改密码\tB.查找账户\tC.插入账户\tD.删除账户\tE.转入教师端\n");
		printf("F.处理申诉\n");
		scanf("%c", &tch);
		while (getchar() != '\n');
		if (tch == 'A' || tch == 'a') {
			accountHead=changePassword(accountHead);
		}
		else if (tch == 'B' || tch == 'b') {
			seekAccount(accountHead);
		}
		else if (tch == 'C' || tch == 'c') {
			accountHead = insertAccount(accountHead);
		}
		else if (tch == 'D' || tch == 'd') {
			accountHead = deleteAccount(accountHead);
		}
		else if (tch == 'E' || tch == 'e') {
			teacherPortal(gradeHead, accountHead);
		}
		else if (tch == 'F' || tch == 'f') {
			dealAppeal();
		}
		else {
			printf("输入无效\n");
		}
		printf("是否继续操作？(Y/N)\n");
		scanf("%c", &tc);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tc == 'Y' || tc == 'y');
	return;
}

void teacherPortal(grade** gradeHead, account* accountHead)
{
	char tch, tc;
	do {
		printf("请选择您要进行的操作\n");
		printf("A.录入成绩\tB.修改成绩\tC.插入成绩\tD.删除成绩\n");
		printf("E.升序排序\tF.降序排序\tG.查找个人成绩\tH.排名\tI.查询班级成绩\n");
		scanf("%c", &tch);
		while (getchar() != '\n');
		if (tch == 'A' || tch == 'a') {
			*gradeHead=recordGrade(*gradeHead);
		}
		else if (tch == 'B' || tch == 'b') {
			*gradeHead = changeGrade(*gradeHead);
			*gradeHead = rank(*gradeHead);
		}
		else if (tch == 'C' || tch == 'c') {
			*gradeHead = insertGrade(*gradeHead);
			*gradeHead = rank(*gradeHead);
		}
		else if (tch == 'D' || tch == 'd') {
			*gradeHead = deleteGrade(*gradeHead);
			*gradeHead = rank(*gradeHead);
		}
		else if (tch == 'E' || tch == 'e') {
			*gradeHead = ascendOrderGrade(*gradeHead);
		}
		else if (tch == 'F' || tch == 'f') {
			*gradeHead = descendOrderGrade(*gradeHead);
		}
		else if (tch == 'G' || tch == 'g') {
			seekGrade(*gradeHead);
		}
		else if (tch == 'H' || tch == 'h') {
			*gradeHead = rank(*gradeHead);
		}
		else if (tch == 'I' || tch == 'i') {
			seekClassGrade(*gradeHead);
		}
		else {
			printf("输入无效\n");
		}
		printf("是否继续操作？(Y/N)\n");
		scanf("%c", &tc);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tc == 'Y' || tc == 'y');
	return;
}

void studentPortal(grade* gradeHead, account* accountHead)
{
	char tch, tc;
	do {
		printf("请选择您要进行的操作\n");
		printf("A.查询个人成绩\tB.查询班级成绩\tC.成绩申诉\n");
		scanf("%c", &tch);
		while (getchar() != '\n');
		if (tch == 'A' || tch == 'a') {
			seekGrade(gradeHead);
		}
		else if (tch == 'B' || tch == 'b') {
			seekClassGrade(gradeHead);			
		}
		else if (tch == 'C' || tch == 'c') {
			gradeAppeal();
		}
		else {
			printf("输入无效\n");
		}
		printf("是否继续操作？(Y/N)\n");
		scanf("%c", &tc);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tc == 'Y' || tc == 'y');
	return;
}

//成绩导入文件
grade* gradeFile(grade* gradeHead)
{
	FILE* p = fopen("成绩信息.txt", "w");
	if (p == NULL) {
		printf("文件打开失败\n");
		return gradeHead;
	}
	grade* head = gradeHead;
	while (head != NULL) {
		fprintf(p, "%s\t", head->id);
		fprintf(p, "%d\t", head->clas);
		fprintf(p, "%d\t", head->classSort);
		fprintf(p, "%d\t", head->gradeSort);
		fprintf(p, "%.2f\t",head->chinesegrade);
		fprintf(p, "%.2f\t",head->englishgrade);
		fprintf(p, "%.2f\t",head->mathgrade);
		fprintf(p, "%.2f\t",head->totalgrade);
		fprintf(p, "%.2f\n",head->averagegrade);
		head = head->next;
	}
	fclose(p);
	printf("成绩导入文件成功\n");
	return gradeHead;
}

//账户导入文件
account* accountFile(account* accountHead)
{
	FILE* p = fopen("账户.txt", "w");
	if (p == NULL) {
		printf("文件打开失败\n");
		return accountHead;
	}
	account* head = accountHead;
	while (head != NULL) {
		fprintf(p, "%s\t", head->username);
		fprintf(p, "%s\n", head->password);
		head = head->next;
	}
	fclose(p);
	printf("账户导入文件成功\n");
	return accountHead;
}