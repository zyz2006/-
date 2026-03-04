#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct account {
	char username[50];
	char password[50];
	char cpassword[50];
	int role;
	struct account* next;
}account;

typedef struct information {
	char id[15];
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

int checkQuit(char input[]);
void teacherPortal(grade** gradeHead, account** accountHead);
void studentPortal(grade** gradeHead, account** accountHead);
void adminPortal(grade** gradeHead, account** accountHead);
account* prelogin(grade* gradeHead, account** accountHead,int* isLoginSuccess,int role);
account* registerFiction(account** accountHead,int* isLoginSuccess,int role);
account* loginFiction(account** accountHead, int* isLoginSuccess,int role);
account* creatAccountLinklist();
account* changePassword(account** accountHead);
void seekAccount(account** accountHead);
account* insertAccount(account** accountHead);
account* deleteAccount(account** accountHead);
grade* creatGradeLinklist();
grade* recordGrade(grade* gradeHead);
grade* changeGrade(grade* gradeHead);
grade* seekGrade(grade* gradeHead);
grade* seekClassGrade(grade* gradeHead);
void gatherProblem();
void checkProblem();
grade* insertGrade(grade* gradeHead);
grade* ascendOrderGrade(grade* gradeHead);
grade* descendOrderGrade(grade* gradeHead);
grade* deleteGrade(grade* gradeHead);
grade* rank(grade* gradeHead);
grade* gradeFile(grade* gradeHead);
account* accountFile(account* accountHead);

//返回上一层函数  
int checkQuit(char input[]) {
	if (strcmp(input, "#") == 0) {
		return 1;
	}
	return 0;
}

int main()
{
	grade* gradeHead = creatGradeLinklist();
	account* accountHead = creatAccountLinklist();
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	char r[50], tch = 'N';
	do {
		printf("请问您的身份是：\n（A）老师\n（B）学生\n（C）管理员\n");
		printf("请选择‘A'，'B'，'C'(#结束程序运行)\n");
		while (scanf("%49s", r) != EOF) {
			while (getchar() != '\n');
			if (checkQuit(r)) {
				gradeFile(gradeHead);
				accountFile(accountHead);
				return 0;
			}
			if (r[0] == 'A' || r[0] == 'a') {
				printf("现在进入教师端\n");
				teacherPortal(&gradeHead,&accountHead);
				break;
			}
			else if (r[0] == 'B' || r[0] == 'b') {
				printf("现在进入学生端\n");
				studentPortal(&gradeHead, &accountHead);
				break;
			}
			else if (r[0] == 'C' || r[0] == 'c') {
				printf("现在进入管理员端\n");
				adminPortal(&gradeHead, &accountHead);
				break;
			}
			else {
				printf("身份有误，请重新选择！\n");
				continue;
			}
		}
		printf("是否再次选择身份(除了Y与y其他均视为不进行其他操作,#结束程序运行)\n");
		scanf("%49s", r);
		while (getchar() != '\n');
		if (checkQuit(r)) {
			gradeFile(gradeHead);
			accountFile(accountHead);
			return 0;
		}
		else {
			tch = r[0];
		}
	} while (tch == 'Y' || tch == 'y');
	gradeFile(gradeHead);
	accountFile(accountHead);
	return 0;
}


//判断是否有账户
account* prelogin(grade* gradeHead, account** accountHead, int* isLoginSuccess,int role)
{
	*isLoginSuccess = 0;
	char choice;
	do {
		printf("请选择操作\n");
		printf("a:注册，b:登录，#退回到身份选择功能，请输入：\n");
		char temp[50];
		while (scanf("%49s", temp) != EOF) {
			while (getchar() != '\n');
			if (checkQuit(temp)) {
				*isLoginSuccess = 0;
				return *accountHead;
			}
			if (temp[0] == 'b' || temp[0] == 'B') {
				printf("请登录\n");
				for (int i = 0; i < 30; i++) {
					printf("=");
				}
				printf("\n");
				*accountHead = loginFiction(accountHead, isLoginSuccess,role);
				if (*isLoginSuccess == 1) {
					return *accountHead;
				}
				break;
			}
			else if (temp[0] == 'A' || temp[0] == 'a') {
				printf("请注册\n");
				for (int i = 0; i < 30; i++) {
					printf("=");
				}
				printf("\n");
				*accountHead = registerFiction(accountHead, isLoginSuccess, role);
				break;
			}
			else {
				printf("输入有误，请重新输入！\n");
			}
		}
		printf("是否再次选择操作(除了Y与y其他均视为不进行其他操作,#结束程序运行)\n");
		scanf(" %c",&choice );
		while (getchar() != '\n');
	} while (choice == 'Y' || choice == 'y');
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return *accountHead;
}

//注册
account* registerFiction(account** accountHead, int* isLoginSuccess,int role)
{
	*isLoginSuccess = 0;
	account* a = (account*)malloc(sizeof(account));
	if (a == NULL) {
		printf("内存分配失败，请重试！\n");
		return *accountHead;
	}
	memset(a, 0, sizeof(account));

	//account* head = accountHead;
	//fflush(stdin);
	printf("请输入4位账号,#退出注册功能\n");
	scanf("%49s", a->username);
	while (getchar() != '\n');
	if (checkQuit(a->username)) { 
		free(a);
		*isLoginSuccess = 0;
		return *accountHead;
	}
	//fflush(stdin);
	printf("请设置8到20位的密码,#退出注册功能\n");
	scanf("%49s", a->password);
	while (getchar() != '\n');
	if (checkQuit(a->password)) { 
		free(a);
		*isLoginSuccess = 0;
		return *accountHead;
	}
	printf("请确认密码，#退出注册功能\n");
	scanf("%49s", a->cpassword);
	while (getchar() != '\n');
	if (checkQuit(a->cpassword)) { 
		free(a);
		*isLoginSuccess = 0;
		return *accountHead;
	}
	
	while (strlen(a->username) != 4 || strlen(a->password) > 20 || strlen(a->password) < 8 || strcmp(a->password, a->cpassword) != 0) {
		if (strlen(a->username) != 4) {
			printf("账号错误！\n");
		}
		if (strlen(a->password) < 8) {
			printf("密码过短！\n");
		}
		if (strlen(a->password) > 20) {
			printf("密码过长\n");
		}
		if (strcmp(a->password, a->cpassword) != 0) {
			printf("确认密码与输入密码不一致！\n");
		}
		printf("请输入4位账号，输入#退出注册功能\n");
		scanf("%49s", a->username);
		while (getchar() != '\n');
		if (checkQuit(a->username)) {
			free(a);
			*isLoginSuccess = 0;
			return *accountHead;
		}
		printf("请设置8到20位的密码，输入#退出注册功能\n");
		scanf("%49s", a->password);
		while (getchar() != '\n');
		if (checkQuit(a->password)) {
			free(a);
			*isLoginSuccess = 0;
			return *accountHead;
		}
		printf("请确认密码，输入#退出注册功能\n");
		scanf("%49s", a->cpassword);
		while (getchar() != '\n');
		if (checkQuit(a->cpassword)) {
			free(a);
			*isLoginSuccess = 0;
			return *accountHead;
		}
	}
	account* hea = *accountHead;
	while (hea != NULL) {
		if (strcmp(hea->username, a->username) == 0) {
			printf("账号已存在，即将退出注册功能，请核查信息\n");
			free(a);
			return *accountHead;
		}
		hea = hea->next;
	}
	account* b = (account*)malloc(sizeof(account));
	if (b == NULL) {
		printf("内存分配失败，请重试！\n");
		free(a);
		return *accountHead;
	}
	memset(b, 0, sizeof(account));
	for (int i = 0; i < strlen(a->password); i++) {
		b->password[i] = a->password[i] + 5;
	}
	b->password[strlen(a->password)] = '\0';
	strcpy(b->username, a->username);
	b->role = role;
	if (*accountHead == NULL) {
		*accountHead = b;
	}
	else {
		account* p = *accountHead;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = b;
	}
	b->next = NULL;
	printf("注册成功！即将退出注册功能\n");
	/*account* test = accountHead;
	printf("当前链表中的用户：");
	while (test != NULL) {
		printf("%s ", test->username);
		test = test->next;
	}
	printf("\n");
	*/
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	free(a);
	return *accountHead;
}

//登录
account* loginFiction(account** accountHead, int* isLoginSuccess,int role)
{
	*isLoginSuccess = 0;
	account* login = (account*)malloc(sizeof(account));
	memset(login, 0, sizeof(account));
	account* exist = *accountHead;

	printf("请输入账号。输入#退出登录功能\n");
	scanf("%49s", login->username);
	while (getchar() != '\n');
	if (checkQuit(login->username)) {
		free(login);
		*isLoginSuccess = 0;
		return *accountHead; 
	}

	printf("请输入密码。输入#退出登录功能\n");
	scanf("%49s", login->password);
	while (getchar() != '\n');
	if (checkQuit(login->password)) {
		free(login);
		*isLoginSuccess = 0;
		return *accountHead; 
	}

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
			if (exist->role != role) {
				printf("身份与账号不匹配，即将退出登录功能\n");
				free(login);
				*isLoginSuccess = 0;
				return *accountHead;
			}
			if (strcmp(tempPassword, login->password) == 0&&role==exist->role) {
				printf("登陆成功！即将退出登录功能\n");
				free(login);
				*isLoginSuccess = 1;
				return *accountHead;
			}
			else {
				do {
					printf("密码错误！\n");
					printf("请重新输入密码！(输入q重新设置密码,输入#退出登录功能）\n");
					scanf("%49s", login->password);
					while (getchar() != '\n');

					if (checkQuit(login->password)) {
						free(login);
						*isLoginSuccess = 0;
						return *accountHead;
					}
					if (strcmp(tempPassword, login->password) == 0) {
						printf("登陆成功！即将退出登录功能\n");
						for (int i = 0; i < 30; i++) {
							printf("=");
						}
						printf("\n");
						free(login);
						*isLoginSuccess = 1;
						return *accountHead;
					}
					else if (strcmp(login->password, "q") == 0) {
						for (int i = 0; i < 30; i++) {
							printf("=");
						}
						printf("\n");
						free(login);
						*accountHead = changePassword(accountHead);
						*isLoginSuccess = 0;
						return *accountHead;
					}
				} while (strcmp(tempPassword, login->password) != 0);
			}
		}
		exist = exist->next;
	}
	if (userFound == 0) {
		printf("账号不存在！即将退出登录功能，请先检查账号\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		free(login);
		return *accountHead;
	}
}
//录入原始账户数据
account* creatAccountLinklist()
{
	int role;
	account* accountHead = NULL;
	FILE* p = fopen("账户.txt", "r");
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
		account* tail = NULL;
		char tus[50], tpa[50];
		while (fscanf(p, "%49s %49s %d", tus, tpa,&role) != EOF) {
			account* cur = (account*)malloc(sizeof(account));
			if (cur == NULL) {
				printf("内存分配失败，请重试！\n");
				fclose(p);
				return accountHead;
			}
			strcpy(cur->username, tus);
			strcpy(cur->password, tpa);
			cur->role = role;
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
account* changePassword(account** accountHead)
{
	int isLoginSuccess = 0;
	account* login = (account*)malloc(sizeof(account));
	account* exist = *accountHead;
	int userFound = 0;

	printf("请输入账号,输入#退出密码修改功能\n");
	scanf("%49s", login->username);
	while (getchar() != '\n');
	if (checkQuit(login->username)) { 
		free(login);
		return *accountHead;
	}
	if (exist == NULL) {
		printf("不存在任何账户！\n");
		free(login);
		return exist;
	}
	while (exist != NULL) {
		if (strcmp(exist->username, login->username) == 0) {
			userFound = 1;
			printf("请输入新密码！输入#退出密码修改功能\n");
			scanf("%49s", login->password);
			while (getchar() != '\n');
			if (checkQuit(login->password)) { 
				free(login);
				return *accountHead;
			}

			while (strlen(login->password) > 20 || strlen(login->password) < 8) {
				if (strlen(login->password) > 20) {
					printf("密码过长！\n");
				}
				if (strlen(login->password) < 8) {
					printf("密码过短！\n");
				}
				printf("请设置8到20位的密码，输入#退出密码修改功能\n");
				scanf("%49s", login->password);
				while (getchar() != '\n');
				if (checkQuit(login->password)) { 
					free(login);
					return *accountHead;
				}
			}
			account b = { 0 };
			for (int i = 0; i < strlen(login->password); i++) {
				b.password[i] = login->password[i] + 5;
			}
			b.password[strlen(login->password)] = '\0';
			strcpy(exist->password, b.password);
			break;
		}
		exist = exist->next;
	}
	if (userFound == 0) {
		printf("账号不存在！即将退出修改密码功能\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	}
	else {
		printf("密码修改成功，即将退出密码修改功能\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	}
	free(login);
	return *accountHead;
}

//查找账户
void seekAccount(account** accountHead)
{
	if (*accountHead == NULL) {
		printf("暂无任何账户可查找！\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return;
	}
	account* head = *accountHead;
	char tus[50], tempPassword[50];
	int found = 0;
	printf("请输入账号！输入#退出账号查找功能\n");
	scanf("%49s", tus);
	while (getchar() != '\n');
	if (checkQuit(tus)) { 
		return;
	}
	while (head != NULL) {
		if (strcmp(head->username, tus) == 0) {
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
		printf("账号不存在！即将退出账号查找功能\n");
	}
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return;
}

//插入账户
account* insertAccount(account** accountHead)
{
	account* cur = (account*)malloc(sizeof(account));
	int found = 0;
	if (cur == NULL) {
		printf("内存分配失败\n");
		return *accountHead;
	}
	char place[50];

	printf("请输入账号，输入#退出插入账户功能\n");
	scanf("%49s", cur->username);
	while (getchar() != '\n');
	if (checkQuit(cur->username)) { 
		free(cur);
		return *accountHead;
	}

	account* newnode = *accountHead;
	while (newnode != NULL) {
		if (strcmp(newnode->username , cur->username)==0) {
			printf("账户已存在，即将退出账户插入功能\n");
			free(cur);
			return *accountHead;
		}
		newnode = newnode->next;
	}
	printf("请输入密码，输入#退出插入账户功能\n");
	scanf("%49s", cur->password);
	while (getchar() != '\n');
	if (checkQuit(cur->password)) { 
		free(cur);
		return *accountHead;
	}
	printf("请选择账户身份：0.管理员 1.教师 2.学生\n");
	int role;
	scanf("%d", &role);
	while (getchar() != '\n');
	if (role < 0 || role > 2) {
		printf("身份无效，默认设为学生。\n");
		role = 2;
	}
	cur->role = role;
	for (int i = 0; i < strlen(cur->password); i++) {
		cur->password[i] += 5;
	}
	printf("请输入要插入位置的前一位置账号，输入#退出账户插入功能\n");
	scanf("%49s", place);
	while (getchar() != '\n');
	if (checkQuit(place)) {
		free(cur);
		return *accountHead;
	}

	cur->next = NULL;
	if (*accountHead == NULL) {
		printf("插入成功，即将退出账户插入功能\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return cur;
	}
	if (strcmp((*accountHead)->username, place) == 0) {
		cur->next = *accountHead;
		*accountHead = cur;
		printf("插入成功，即将退出账户插入功能\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return *accountHead;
	}
	account* head = *accountHead;
	while (head != NULL) {
		if (strcmp(head->username, place) == 0) {
			found = 1;
			cur->next = head->next;
			head->next = cur;
			printf("插入成功，即将退出账户插入功能\n");
			break;
		}
		head = head->next;
	}
	if (found == 0) {
		printf("未找到插入位置，默认追加到末尾，即将退出账户插入功能\n");
		account* tail = *accountHead;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = cur;
		cur->next = NULL;
	}
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return *accountHead;
}

//删除账户
account* deleteAccount(account** accountHead)
{
	if (*accountHead == NULL) {
		printf("暂无账户\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return *accountHead;
	}
	char tus[50],confirm[50];
	printf("请输入要删除的账户,#退出删除账户功能\n");
	scanf("%49s", tus);
	while (getchar() != '\n');
	if (checkQuit(tus)) { 
		return *accountHead;
	}

	if (strcmp(tus, (*accountHead)->username) == 0) {
		char tch;
		printf("已找到账户信息，确认删除？(除y外均代表不删除，#退出删除账户功能)\n");
		scanf(" %49s", confirm);
		while (getchar() != '\n');
		if (checkQuit(confirm)) {
			return *accountHead;
		}

		if (confirm[0] == 'Y' || confirm[0] == 'y') {
			account* freeHead = *accountHead;
			*accountHead = (*accountHead)->next;
			free(freeHead);
			printf("删除成功，即将退出删除账户功能\n");
		}
		else {
			printf("已撤消删除，即将退出删除账户功能\n");
		}
	}
	else {
		account* head = *accountHead;
		account* cur = (*accountHead)->next;
		int found = 0;
		while (cur != NULL) {
			if (strcmp(cur->username, tus) == 0) {
				found = 1;
				char tch;
				printf("已找到账户信息，确认删除？(除y外均代表不删除，#退出删除账户功能)\n");
				while (scanf("%49s", confirm) != EOF) {
					while (getchar() != '\n');
					if (checkQuit(confirm)) {
						return *accountHead;
					}
					if (confirm[0] == 'Y' || confirm[0] == 'y') {
						account* freeHead = cur;
						head->next = cur->next;
						free(freeHead);
						printf("删除成功，即将退出删除账户功能\n");

					}
					else {
						printf("已撤消删除，即将退出删除账户功能\n");
					}
					break;
				}
			}
			head = head->next;
			cur = cur->next;
		}
		if (found == 0) {
			printf("未找到账户，即将退出删除账户功能\n");
		}
	}
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return *accountHead;
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
		int clas, classSort, gradeSort;
		float chinese, math, english, total, average;
		while (fscanf(p, "%13s %d %d %d %f %f %f %f %f", tid, &clas, &classSort, &gradeSort, &chinese, &english, &math, &total, &average) != EOF) {
			grade* cur = (grade*)malloc(sizeof(grade));
			if (cur == NULL) {
				printf("内存分配失败，请重试！\n");
				fclose(p);
				return gradeHead;
			}
			strcpy(cur->id, tid);
			cur->clas = clas;
			cur->classSort = classSort;
			cur->gradeSort = gradeSort;
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
		}
		printf("原始成绩数据录入完成！\n");
		fclose(p);
		return gradeHead;
	}
}

//录入成绩
grade* recordGrade(grade* gradeHead)
{
	char choice[50], tt[50];
	do {
		
		grade* tail = gradeHead;
		while (tail != NULL && tail->next != NULL) {
			tail = tail->next;
		}
		char tid[15];
		int clas, found = 0;
		float chinese, math, english, total, average;
		printf("请输入学生的学号,#退出成绩录入功能\n");
		scanf("%14s", tid);
		while (getchar() != '\n');
		if (checkQuit(tid)) {
			return gradeHead;
		}
		grade* cu = gradeHead;
		while (cu != NULL) {
			if (strcmp(tid, cu->id) == 0) {
				printf("该学生成绩已录入，即将退出成绩录入功能\n");
				found = 1;
				break;
			}
			cu = cu->next;
		}
		if (found == 1) {
			printf("是否录入其他人的成绩？(除了Y与y其他均视为不录入，,输入#退出成绩录入功能)\n");
			scanf("%49s", tt);
			while (getchar() != '\n');
			if (checkQuit(tt)) { 
				return gradeHead;
			}
			else {
				choice[0] = tt[0];
			}
			for (int i = 0; i < 30; i++) {
				printf("=");
			}
			printf("\n");
			continue;
		}
		printf("请输入学生的班级(1/2)\n");
		scanf("%d", &clas);
		while (getchar() != '\n');
		if (clas != 1 && clas != 2) {
			printf("班级不存在，请重新输入，再次错误将退出\n");
			scanf("%d", &clas);
			while (getchar() != '\n');
			if (clas != 1 && clas != 2) {
				printf("班级不存在,即将退出录入成绩功能\n");
				return gradeHead;
			}
		}
		printf("请输入学生的语文成绩\n");
		scanf("%f", &chinese);
		while (getchar() != '\n');
		if (chinese<0||chinese>150) {
			printf("成绩不正确，请重新输入，再次错误将退出\n");
			scanf("%f", &chinese);
			while (getchar() != '\n');
			if (chinese < 0 || chinese>150) {
				printf("成绩不正确,即将退出录入成绩功能\n");
				return gradeHead;
			}
		}
		printf("请输入学生的数学成绩\n");
		scanf("%f", &math);
		while (getchar() != '\n');
		if (math < 0 || math>150) {
			printf("成绩不正确，请重新输入，再次错误将退出\n");
			scanf("%f", &math);
			while (getchar() != '\n');
			if (math < 0 || math>150) {
				printf("成绩不正确,即将退出录入成绩功能\n");
				return gradeHead;
			}
		}
		printf("请输入学生的英语成绩\n");
		scanf("%f", &english);
		while (getchar() != '\n');
		if (english < 0 || english>150) {
			printf("成绩不正确，请重新输入，再次错误将退出\n");
			scanf("%f", &english);
			while (getchar() != '\n');
			if (english < 0 || english>150) {
				printf("成绩不正确,即将退出录入成绩功能\n");
				return gradeHead;
			}
		}
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
		cur->classSort = 0; 
		cur->gradeSort = 0;
		cur->next = NULL;

		if (gradeHead == NULL) {
			gradeHead = cur;
			tail = cur;
		}
		else {
			tail->next = cur;
			tail = tail->next;
		}
		printf("是否录入下一位学生的成绩（除了Y与y其他均视为不录入,#退出成绩录入功能）\n");
		scanf("%49s", choice);
		while (getchar() != '\n');
		if (checkQuit(choice)) { 
			return gradeHead;
		}
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while ((choice[0] == 'Y' || choice[0] == 'y'));
	return gradeHead;
}

//修改成绩
grade* changeGrade(grade* gradeHead)
{
	char tid[15];
	printf("请输入您要修改学生的学号,#退出成绩修改功能\n");
	scanf("%14s", tid);
	while (getchar() != '\n');
	if (checkQuit(tid)) {
		return gradeHead;
	}
	grade* cur = gradeHead;
	int found = 0;
	while (cur != NULL) {
		if (strcmp(cur->id, tid) == 0) {
			found = 1;
			printf("请输入要修改的科目，语文（C）英语（E）数学（M）,按#退出成绩修改功能\n");
			char tch;
			while (scanf(" %c", &tch) != EOF) {
				while (getchar() != '\n');
				if (tch == 'C' || tch == 'c') {
					printf("请输入新成绩\n");
					float newgr;
					scanf("%f", &newgr);
					while (getchar() != '\n');
					if (newgr < 0 || newgr>150) {
						printf("成绩不正确，请重新输入，再次错误将退出\n");
						scanf("%f", &newgr);
						while (getchar() != '\n');
						if (newgr < 0 || newgr>150) {
							printf("成绩不正确,即将退出成绩修改功能\n");
							return gradeHead;
						}
					}
					cur->chinesegrade = newgr;
					cur->totalgrade = cur->chinesegrade + cur->englishgrade + cur->mathgrade;
					cur->averagegrade = cur->totalgrade / 3;
					printf("成绩修改完成，即将退出成绩修改功能\n");
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
					if (newgr < 0 || newgr>150) {
						printf("成绩不正确，请重新输入，再次错误将退出\n");
						scanf("%f", &newgr);
						while (getchar() != '\n');
						if (newgr < 0 || newgr>150) {
							printf("成绩不正确,即将退出成绩修改功能\n");
							return gradeHead;
						}
					}
					cur->englishgrade = newgr;
					cur->totalgrade = cur->chinesegrade + cur->englishgrade + cur->mathgrade;
					cur->averagegrade = cur->totalgrade / 3;
					printf("成绩修改完成，即将退出成绩修改功能\n");
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
					if (newgr < 0 || newgr>150) {
						printf("成绩不正确，请重新输入，再次错误将退出\n");
						scanf("%f", &newgr);
						while (getchar() != '\n');
						if (newgr < 0 || newgr>150) {
							printf("成绩不正确,即将退出成绩修改功能\n");
							return gradeHead;
						}
					}
					cur->mathgrade = newgr;
					cur->totalgrade = cur->chinesegrade + cur->englishgrade + cur->mathgrade;
					cur->averagegrade = cur->totalgrade / 3;
					printf("成绩修改完成，即将退出成绩修改功能\n");
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					return gradeHead;
				}
				else if (tch == '#') {
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
		printf("未找到对应学生，即将退出成绩修改功能\n");
	}
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return gradeHead;
}

//查找成绩
grade* seekGrade(grade* gradeHead)
{
	char tch;
	do {
		printf("请输入您要查询学生的学号,#退出查找成绩功能\n");
		char tid[15];
		scanf("%14s", tid);
		while (getchar() != '\n');
		if (checkQuit(tid)) {
			return  gradeHead;
		}
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
		scanf(" %c", &tch);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tch == 'y' || tch == 'Y');
	return gradeHead;
}

//查询班级成绩
grade* seekClassGrade(grade* gradeHead)
{
	char tch;
	do {
		printf("请输入您要查询的班级\n");
		int clas, found = 0;
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
		scanf(" %c", &tch);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tch == 'y' || tch == 'Y');
	return gradeHead;
}

//问题收集
void gatherProblem()
{
	FILE* p = fopen("代办.txt", "a");
	if (p == NULL) {
		printf("代办文件创建失败\n");
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
		return;
	}
	char te[100], tch;
	do {
		printf("请写清问题内容(90字以内）\n");
		printf("提示:若要修改密码或找回密码，请给出账号(和新密码);若要成绩申诉，请给出学号，科目，和新成绩\n");
		scanf("%90s", te);
		while (getchar() != '\n');
		fprintf(p, "%s\n", te);
		printf("是否还有其它问题？(y/n)\n");
		scanf(" %c", &tch);
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

//查看问题
void checkProblem()
{
	char line[100];
	FILE* p = fopen("代办.txt", "r");
	if (p == NULL) {
		printf("代办文件打开失败\n");
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
	printf("代办问题查看完毕\n");
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
	int clas, found = 0;
	float chinese, math, english, total, average;
	printf("请输入学生的学号，#退出成绩插入功能\n");
	scanf("%14s", tid);
	while (getchar() != '\n');
	if (checkQuit(tid)) {
		return gradeHead;
	}
	grade* cu = gradeHead;
	while (cu != NULL) {
		if (strcmp(tid, cu->id) == 0) {
			printf("该学生成绩已录入，即将退出成绩插入功能\n");
			return gradeHead;
		}
		cu = cu->next;
	}
	printf("请输入学生的班级\n");
	scanf("%d", &clas);
	while (getchar() != '\n');
	if (clas != 1 && clas != 2) {
		printf("班级不存在，请重新输入，再次错误将退出\n");
		scanf("%d", &clas);
		while (getchar() != '\n');
		if (clas != 1 && clas != 2) {
			printf("班级不存在,即将退出插入成绩功能\n");
			return gradeHead;
		}
	}
	printf("请输入学生的语文成绩\n");
	scanf("%f", &chinese);
	while (getchar() != '\n');
	if (chinese < 0 || chinese>150) {
		printf("成绩不正确，请重新输入，再次错误将退出\n");
		scanf("%f", &chinese);
		while (getchar() != '\n');
		if (chinese < 0 || chinese>150) {
			printf("成绩不正确,即将退出录入成绩功能\n");
			return gradeHead;
		}
	}
	printf("请输入学生的数学成绩\n");
	scanf("%f", &math);
	while (getchar() != '\n');
	if (math < 0 || math>150) {
		printf("成绩不正确，请重新输入，再次错误将退出\n");
		scanf("%f", &math);
		while (getchar() != '\n');
		if (math < 0 || math>150) {
			printf("成绩不正确,即将退出插入成绩功能\n");
			return gradeHead;
		}
	}
	printf("请输入学生的英语成绩\n");
	scanf("%f", &english);
	while (getchar() != '\n');
	if (english < 0 || english>150) {
		printf("成绩不正确，请重新输入，再次错误将退出\n");
		scanf("%f", &english);
		while (getchar() != '\n');
		if (english < 0 || english>150) {
			printf("成绩不正确,即将退出插入成绩功能\n");
			return gradeHead;
		}
	}
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
	if (strcmp(preid, "0") == 0) {
		cur->next = gradeHead;
		gradeHead = cur;
		printf("插入成功，即将退出成绩插入功能\n");
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
			printf("插入成功，即将退出成绩插入功能\n");
		}
		else {
			printf("未找到您指定的插入位置，默认追加到末尾，即将退出成绩插入功能\n");
			grade* tail = gradeHead;
			while (tail->next != NULL) {
				tail = tail->next;
			}
			tail->next = cur;
			cur->next = NULL;
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
	printf("升序排序完成,按y打印，按任意键退出\n");
	char lin;
	scanf(" %c", &lin);
	if (lin == 'y' || lin == 'Y') {
		grade* cur = gradeHead;
		while (cur != NULL) {
			printf("学号:%s\n", cur->id);
			printf("语文成绩：%.2f\t", cur->chinesegrade);
			printf("数学成绩：%.2f\t", cur->mathgrade);
			printf("英语成绩：%.2f\n", cur->englishgrade);
			printf("总成绩：%.2f\t", cur->totalgrade);
			printf("平均成绩：%.2f\n", cur->averagegrade);
			
			cur = cur->next;
		}
	}
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
	printf("降序排序完成,按y打印，按任意键退出\n");
	char lin;
	scanf(" %c", &lin);
	if (lin == 'y' || lin == 'Y') {
		grade* cur = gradeHead;
		while (cur != NULL) {
			printf("学号:%s\n", cur->id);
			printf("语文成绩：%.2f\t", cur->chinesegrade);
			printf("数学成绩：%.2f\t", cur->mathgrade);
			printf("英语成绩：%.2f\n", cur->englishgrade);
			printf("总成绩：%.2f\t", cur->totalgrade);
			printf("平均成绩：%.2f\n", cur->averagegrade);
			
			cur = cur->next;
		}
	}
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
	gradeHead = descendOrderGrade(gradeHead);
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
	printf("排名完成\n");
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
	printf("请输入要删除学生的学号,#退出成绩删除功能\n");
	char tid[15];
	scanf("%14s", tid);
	while (getchar() != '\n');
	if (checkQuit(tid)) {
		return gradeHead;
	}
	if (strcmp(gradeHead->id, tid) == 0) {
		printf("确认删除？（Y/N）\n");
		char tch;
		while (scanf(" %c", &tch) != EOF) {
			while (getchar() != '\n');
			if (tch == 'y' || tch == 'Y') {
				grade* freeHead = gradeHead;
				gradeHead = gradeHead->next;
				printf("删除成功，即将退出成绩删除功能\n");
				free(freeHead);
				for (int i = 0; i < 30; i++) {
					printf("=");
				}
				printf("\n");
				return gradeHead;
			}
			else if (tch == 'N' || tch == 'n') {
				printf("删除已撤销，即将退出成绩删除功能\n");
				for (int i = 0; i < 30; i++) {
					printf("=");
				}
				printf("\n");
				return gradeHead;
			}
			else {
				printf("输入无效，默认不删除，即将退出成绩删除功能\n");
				for (int i = 0; i < 30; i++) {
					printf("=");
				}
				printf("\n");
				return gradeHead;
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
			while (scanf(" %c", &tch) != EOF) {
				while (getchar() != '\n');
				if (tch == 'y' || tch == 'Y') {
					head->next = cur->next;
					printf("删除成功，即将退出成绩删除功能\n");
					free(cur);
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					return gradeHead;
				}
				else if (tch == 'N' || tch == 'n') {
					printf("删除已撤销，即将退出成绩删除功能\n");
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					return gradeHead;
				}
				else {
					printf("输入无效，默认不删除，即将退出成绩删除功能\n");
					for (int i = 0; i < 30; i++) {
						printf("=");
					}
					printf("\n");
					return gradeHead;
				}
			}
		}
		head = head->next;
		cur = cur->next;
	}
	if (found == 0) {
		printf("未找到对应学生，即将退出成绩删除功能\n");
	}
	for (int i = 0; i < 30; i++) {
		printf("=");
	}
	printf("\n");
	return gradeHead;
}

//管理员端
void adminPortal(grade** gradeHead, account** accountHead)
{
	int role = 0;
	int isLoginSuccess = 0;
	*accountHead = prelogin(*gradeHead, accountHead, &isLoginSuccess,role);
	if (!isLoginSuccess) {
		return;
	}
	char tch[50], tc;
	do {
		printf("请选择您要进行的操作\n");
		printf("A.修改密码\tB.查找账户\tC.插入账户\tD.删除账户\tE.转入教师端\n");
		printf("F.处理代办\n");
		scanf(" %c", &tch);
		while (getchar() != '\n');
		
		if (tch[0] == 'A' || tch[0] == 'a') {
			*accountHead = changePassword(accountHead);
		}
		else if (tch[0] == 'B' || tch[0] == 'b') {
			seekAccount(accountHead);
		}
		else if (tch[0] == 'C' || tch[0] == 'c') {
			*accountHead = insertAccount(accountHead);
		}
		else if (tch[0] == 'D' || tch[0] == 'd') {
			*accountHead = deleteAccount(accountHead);
		}
		else if (tch[0] == 'E' || tch[0] == 'e') {
			teacherPortal(gradeHead, accountHead);
		}
		else if (tch[0] == 'F' || tch[0] == 'f') {
			checkProblem();
		}
		else {
			printf("输入无效\n");
		}
		printf("是否继续操作？(Y/N)\n");
		scanf(" %c", &tc);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tc=='y'||tc=='Y');
	return;
}

//教师端
void teacherPortal(grade** gradeHead, account** accountHead)
{
	int role = 1;
	int isLoginSuccess = 0;
	*accountHead = prelogin(*gradeHead, accountHead, &isLoginSuccess,role);
	if (!isLoginSuccess) {
		return;
	}
	char tch[50],tc;
	do {
		printf("请选择您要进行的操作\n");
		printf("A.录入成绩\tB.修改成绩\tC.插入成绩\tD.删除成绩\tE.升序排序\n");
		printf("F.降序排序\tG.查找个人成绩\tH.排名\tI.查询班级成绩\tJ.账号申诉\n");
		printf("账号申诉可向管理员申请，由管理员帮助查询密码\n");
		scanf("%49s", tch);
		while (getchar() != '\n');
		
		if (tch[0] == 'A' || tch[0] == 'a') {
			*gradeHead = recordGrade(*gradeHead);
			*gradeHead = rank(*gradeHead);
		}
		else if (tch[0] == 'B' || tch[0] == 'b') {
			*gradeHead = changeGrade(*gradeHead);
			*gradeHead = rank(*gradeHead);
		}
		else if (tch[0] == 'C' || tch[0] == 'c') {
			*gradeHead = insertGrade(*gradeHead);
			*gradeHead = rank(*gradeHead);
		}
		else if (tch[0] == 'D' || tch[0] == 'd') {
			*gradeHead = deleteGrade(*gradeHead);
			*gradeHead = rank(*gradeHead);
		}
		else if (tch[0] == 'E' || tch[0] == 'e') {
			*gradeHead = ascendOrderGrade(*gradeHead);
		}
		else if (tch[0] == 'F' || tch[0] == 'f') {
			*gradeHead = descendOrderGrade(*gradeHead);
		}
		else if (tch[0] == 'G' || tch[0] == 'g') {
			*gradeHead = seekGrade(*gradeHead);
		}
		else if (tch[0] == 'H' || tch[0] == 'h') {
			*gradeHead = rank(*gradeHead);
		}
		else if (tch[0] == 'I' || tch[0] == 'i') {
			*gradeHead = seekClassGrade(*gradeHead);
		}
		else if (tch[0] == 'J' || tch[0] == 'j') {
			gatherProblem();
		}
		else {
			printf("输入无效\n");
		}
		printf("是否继续操作？(Y/N)\n");
		scanf(" %c", &tc);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tc=='y'||tc=='Y');
	return;
}

//学生端
void studentPortal(grade** gradeHead, account** accountHead)
{
	int role = 2;
	int isLoginSuccess = 0;
	*accountHead = prelogin(*gradeHead, accountHead, &isLoginSuccess,role);
	if (!isLoginSuccess) {
		return;
	}
	char tch[50],tc;
	do {
		printf("请选择您要进行的操作\n");
		printf("A.查询个人成绩\tB.查询班级成绩\tC.成绩申诉(也可进行账号申诉)\n");
		printf("账号申诉可向管理员申请，由管理员帮助查询密码\n");
		scanf("%49s", tch);
		while (getchar() != '\n');
		
		if (tch[0] == 'A' || tch[0] == 'a') {
			*gradeHead = seekGrade(*gradeHead);
		}
		else if (tch[0] == 'B' || tch[0] == 'b') {
			*gradeHead = seekClassGrade(*gradeHead);
		}
		else if (tch[0] == 'C' || tch[0] == 'c') {
			gatherProblem();
		}
		else {
			printf("输入无效\n");
		}
		printf("是否继续操作？(Y/N)\n");
		scanf(" %c", &tc);
		while (getchar() != '\n');
		for (int i = 0; i < 30; i++) {
			printf("=");
		}
		printf("\n");
	} while (tc == 'y' || tc == 'Y');
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
		fprintf(p, "%.2f\t", head->chinesegrade);
		fprintf(p, "%.2f\t", head->englishgrade);
		fprintf(p, "%.2f\t", head->mathgrade);
		fprintf(p, "%.2f\t", head->totalgrade);
		fprintf(p, "%.2f\n", head->averagegrade);
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
		fprintf(p, "%s\t", head->password);
		fprintf(p, "%d\n", head->role);
		head = head->next;
	}
	fclose(p);
	printf("账户导入文件成功\n");
	return accountHead;
}