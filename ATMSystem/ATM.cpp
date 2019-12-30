#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
void regist();//声明注册函数
void login();//声明登陆函数
void quit();//声明退出函数
//银行客户结构体
struct bank 
{
	char name[20];//用户名
	char password[7];//密码
	int account;//账号
	double money;//余额
} client;
struct bank t;
int SizeOf= sizeof(client);//sizeof为返回无符号数
//声明指针变量
FILE *fp;
//主函数
void main()
{
	int t = 1;
	char xz;
	for (int i = 0; i <= 100; i++)
	{
		printf("\n\n\n\n\t\t\t\t\t欢迎使用ATM银行系统！\n\n\n");
		printf("\t\t\t\t\t正在进入主页面，请稍等");
		for (int j = 1; j <= t; j++)
		{
			printf(".");
		}
		t++;
		if (t == 10)
			t = 1;
		printf("\n\n\t\t\t\t\t%d%%", i);//进度
		for (int m = 0; m <= 10000; m++);//延时处理
		system("cls");//清屏函数
	}
	while (1)
	{
		printf("\n\n\n\t\t\t\t\tATM银行系统正在为您服务...\n\n\n\n");
		printf("\t\t\t\t\t服务【A】：用户注册\n\n");
		printf("\t\t\t\t\t服务【B】：用户登陆\n\n");
		printf("\t\t\t\t\t服务【C】：退出系统\n\n");
		printf("\n\n\t\t\t\t\t请选择服务：");
		rewind(stdin);
		//fflush(stdin);//清除键盘缓冲区的回车符//vs2015此函数不可用
		scanf_s("%c", &xz);
		if (xz == 'a' || xz == 'A')
		{
			regist();
		}
		else if (xz == 'b' || xz == 'B')
		{
			login();
		}
		else if (xz == 'c' || xz == 'C')
		{
			quit();
		}
		else
		{
			printf("\n\n\t\t\t\t\t输入选择有误，请重新输入：");
		}
		printf("\n\n\t\t\t\t\t按任意键继续......");
		_getch();//不经过键盘缓冲区的字符
		system("cls");//清屏
	}
	system("pause");
}
//密码函数
void inputPassword(char password[])
{
	int i = 0;
	char ch;
	while (1)
	{
		ch = _getch();//设置缓存区
		if (ch != '\r')
		{
			if (ch != '\b')
			{
				password[i] = ch;
				i++;
				printf("*");
			}
			else
				//键入退格键：先输出退格，然后用空格代替，再进行退格
			{
				if (i > 0)
				{
					i--;
					printf("\b \b");//先输出退格，然后用空格代替，再进行退格
				}
			}
		}
		else {
			break;
		}
	}
	password[i] = '\0';

}
//注册函数
void regist()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t正在执行注册函数...");
	char password1[7];
	errno_t err;
	err= fopen_s(&fp,"atm.txt","ab+");
	if (err!= 0)
	{
		printf("\n\n\t\t\t\t\t打开文件失败");
		return;
	}

	printf("\n\n\n\t\t\t\t\t请输入用户名：");
	rewind(stdin);
	gets_s(client.name);
	printf("\n\t\t\t\t\t用户名为：%s", client.name);
	while (1)
	{
		while (1)
		{
			printf("\n\n\t\t\t\t\t请输入用户密码：");
			rewind(stdin);
			inputPassword(client.password);
			int length = strlen(client.password);
			if (length == 6)break;
			else
				printf("\n\n\t\t\t\t\t用户密码长度必须是六位数！");
		}
		printf("\n\n\t\t\t\t\t请再次确认密码：");
		rewind(stdin);
		inputPassword(password1);
		if (strcmp(client.password, password1) == 0)break;
		else
			printf("\n\n\t\t\t\t\t两次输入密码不一致，请重新输入：");
	}

	//printf("\n\n\t\t\t\t\t请输入用户账号：");
	//scanf_s("%d", &client[count].account);
	//自动生成账号
	rewind(fp);
	if (fread(&t, sizeof(t), 1, fp) == 1)
	{
		fseek(fp, -SizeOf, 2);
		fread(&t, sizeof(t), 1, fp);//读取最后一条记录
		client.account = t.account + 1;
	}
	else
	{
		client.account = 20190001;
	}
	client.money = 0;
	fseek(fp, 0, 2);
	fwrite(&client,sizeof(struct bank),1,fp);
	fclose(fp);

	printf("\n\n\n\t\t\t\t\t\t注册成功！\n");
	printf("\n\n\t\t\t\t\t您的账号为：%d\n", client.account);


}

//查询余额
void selectMoney()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t正在查询余额...");
	printf("\n\n\n\n\t\t\t\t\t您的账户余额为：%.2lf", t.money);
}
//存款
void saveMoney()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t正在存款...");
	int mm;
	printf("\n\n\n\n\t\t\t\t\t请输入存款金额：");
	scanf_s("%d", &mm);
	t.money += mm;
	fseek(fp, -SizeOf, 1);//偏移指针
	fwrite(&t, sizeof(t), 1, fp);//写入数据
	printf("\n\n\n\t\t\t\t\t存款成功！");
}
//取款
void getMoney()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t正在取款...");
	int mm;
	printf("\n\n\n\n\t\t\t\t\t请输入取款金额：");
	scanf_s("%d", &mm);

	if(mm > t.money)
	{
		printf("\n\n\t\t\t\t\t余额不足！");

	}
	else
	{
		t.money -= mm;
		fseek(fp, -SizeOf, 1);
		fwrite(&t, sizeof(t), 1, fp);
		printf("\n\n\t\t\t\t\t取款成功！");
	}
}

//转账
void transfer()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t正在转账...");
	int account1,flag=0,mm;
	int n = ftell(fp);
	struct bank temp;
	printf("\n\n\n\n\t\t\t\t\t请输入对方账号：");
	scanf_s("%d", &account1);
	rewind(fp);

	while(fread(&temp,sizeof(temp),1,fp)==1)	
	{
		if (account1 == temp.account)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		printf("\n\t\t\t\t\t请输入转账金额：");
		scanf_s("%d", &mm);
		if (mm <= t.money)
		{
			t.money -= mm;
			temp.money += mm;
			//修改文件数据
			fseek(fp, -SizeOf, 1);
			fwrite(&temp, sizeof(temp), 1, fp);
			fseek(fp, n - sizeof(t), 0);
			fwrite(&t, sizeof(t), 1, fp);
			printf("\n\n\t\t\t\t\t转账成功！");
		}
		else
		{
			printf("\n\n\t\t\t\t\t余额不足！");
		}
	}
	else 
	{
		printf("\n\n\t\t\t\t\t不存在要转账的账号！");
	}
}
//修改密码
void updatePassword()
{
	system("cls");
	int i;
	char password2[7], password3[7], password4[7];
	printf("\n\n\n\n\t\t\t\t\t正在修改密码...");
	for ( i= 0; i < 3; i++)
	{
		printf("\n\n\n\n\t\t\t\t\t请输入旧密码：");
		rewind(stdin);
		inputPassword(password2);
		if (strcmp(password2, t.password) == 0)
		{
			break;
		}
		else
		{
			printf("\n\n\t\t\t\t\t旧密码输入有误，请重新输入");
		}
	}
	if (i < 3)
	{
		while (1)
		{
			printf("\n\t\t\t\t\t请输入新密码：");
			rewind(stdin);
			inputPassword(password3);
			printf("\n\t\t\t\t\t请确认新密码：");
			rewind(stdin);
			inputPassword(password4);
			if (strcmp(password3, password4) == 0)
			{
				strcpy_s(t.password, password3);
				fseek(fp, -SizeOf, 1);//调整指针
				fwrite(&t, sizeof(t), 1, fp);//修改文件
				printf("\n\n\t\t\t\t\t密码修改成功！");
				break;
			}
			else
			{
				printf("\n\n\t\t\t\t\t两次密码输入不一致，请重新输入");
			}
		}

	}
	else
	{
		printf("\n\n\t\t\t\t\t三次密码输入错误，吞卡....");
	}
}
//注销
int logout()
{
	system("cls");
	char x;
	int zx=0;
	printf("\n\n\n\n\t\t\t\t\t正在注销...");
	printf("\n\n\n\n\t\t\t\t\t您要注销的客户账号是：%d\n", t.account);
	printf("\n\n\t\t\t\t\t是否真的要注销?注销【Y】，不注销【N】：");
	rewind(stdin);
	scanf_s("%c", &x);
	if (x == 'Y' || x == 'y')
	{
		printf("\n\n\t\t\t\t\t已注销账号：%d",t.account);
		zx = 1;
	}
	else 
	{
		printf("\n\n\t\t\t\t\t不注销，返回服务页面！");
	}
	return zx;
}
//服务界面函数
void service()
{
	while (1)
	{
		system("cls");
		char xz;
		printf("\n\n\n\n\t\t\t\t\t正在使用服务功能...");
		printf("\n\n\n\n\t\t\t\t\t【A】查询");
		printf("\n\n\t\t\t\t\t【B】存款");
		printf("\n\n\t\t\t\t\t【C】取款");
		printf("\n\n\t\t\t\t\t【D】转账");
		printf("\n\n\t\t\t\t\t【E】修改密码");
		printf("\n\n\t\t\t\t\t【F】注销");
		printf("\n\n\t\t\t\t\t【G】退出系统");
		printf("\n\n\n\t\t\t\t\t请选择服务种类：");
		rewind(stdin);
		scanf_s("%c", &xz);
		switch (xz)
		{
		case 'a':
		case 'A':selectMoney(); break;
		case 'b':
		case 'B':saveMoney(); break;
		case 'c':
		case 'C':getMoney(); break;
		case 'd':
		case 'D':transfer(); break;
		case 'e':
		case 'E':updatePassword(); break;
		case 'f':
		case 'F':if (logout() == 1)return; break;
		case 'g':
		case 'G':quit(); break;
		}
		printf("\n\n\n\n\t\t\t\t\t按任意键继续....");
		_getch();
	}
}
//登陆函数
void login()
{
	system("cls");
	errno_t err;
	err = fopen_s(&fp, "atm.txt", "rb+");
	if (err != 0)
	{
		printf("\n\n\t\t\t\t\t打开失败!\n");
		return;
	}
	printf("\n\n\n\n\t\t\t\t\t正在执行登陆函数...");
	int account1, i, flag = 0;
	char password2[7];
	printf("\n\n\n\n\t\t\t\t\t请输入您的账号：");
	//rewind(stdin);
	scanf_s("%d", &account1);

	while(fread(&t,sizeof(t),1,fp)==1)
	{
		if (account1 == t.account)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		int j;
		for ( j=0;j<3;j++)
		{
			printf("\n\t\t\t\t\t请输入密码：");
			inputPassword(password2);
			if (strcmp(password2, t.password) == 0)
			{
				printf("\n\n\n\t\t\t\t\t\t登陆成功！");
				service();
				break;
			}
		}
		if (j == 3)
		{
			printf("\n\n\t\t\t\t\t三次密码验证都不成功,吞卡中...");
		}

	}
	else 
	{
		printf("\n\n\t\t\t\t\t没有找到此账号");
	}
	fclose(fp);
}
//退出系统
void quit()
{
	system("cls");
	int t = 1;
	for (int i = 0; i <= 100; i++)
	{
		printf("\n\n\n\t\t\t\t\tATM银行系统正在退出，请稍等");
		for (int j = 1; j <= t; j++)
		{
			printf(".");
		}
		t++;
		if (t == 10)
			t = 1;
		printf("\n\n\t\t\t\t\t%d%%", i);//进度
		for (int m = 0; m <= 1000; m++);//延时处理
		system("cls");//清屏函数
	}
	exit(0);//退出函数
}
