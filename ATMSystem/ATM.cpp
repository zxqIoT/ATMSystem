#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
void regist();//����ע�ắ��
void login();//������½����
void quit();//�����˳�����
//���пͻ��ṹ��
struct bank 
{
	char name[20];//�û���
	char password[7];//����
	int account;//�˺�
	double money;//���
} client;
struct bank t;
int SizeOf= sizeof(client);//sizeofΪ�����޷�����
//����ָ�����
FILE *fp;
//������
void main()
{
	int t = 1;
	char xz;
	for (int i = 0; i <= 100; i++)
	{
		printf("\n\n\n\n\t\t\t\t\t��ӭʹ��ATM����ϵͳ��\n\n\n");
		printf("\t\t\t\t\t���ڽ�����ҳ�棬���Ե�");
		for (int j = 1; j <= t; j++)
		{
			printf(".");
		}
		t++;
		if (t == 10)
			t = 1;
		printf("\n\n\t\t\t\t\t%d%%", i);//����
		for (int m = 0; m <= 10000; m++);//��ʱ����
		system("cls");//��������
	}
	while (1)
	{
		printf("\n\n\n\t\t\t\t\tATM����ϵͳ����Ϊ������...\n\n\n\n");
		printf("\t\t\t\t\t����A�����û�ע��\n\n");
		printf("\t\t\t\t\t����B�����û���½\n\n");
		printf("\t\t\t\t\t����C�����˳�ϵͳ\n\n");
		printf("\n\n\t\t\t\t\t��ѡ�����");
		rewind(stdin);
		//fflush(stdin);//������̻������Ļس���//vs2015�˺���������
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
			printf("\n\n\t\t\t\t\t����ѡ���������������룺");
		}
		printf("\n\n\t\t\t\t\t�����������......");
		_getch();//���������̻��������ַ�
		system("cls");//����
	}
	system("pause");
}
//���뺯��
void inputPassword(char password[])
{
	int i = 0;
	char ch;
	while (1)
	{
		ch = _getch();//���û�����
		if (ch != '\r')
		{
			if (ch != '\b')
			{
				password[i] = ch;
				i++;
				printf("*");
			}
			else
				//�����˸����������˸�Ȼ���ÿո���棬�ٽ����˸�
			{
				if (i > 0)
				{
					i--;
					printf("\b \b");//������˸�Ȼ���ÿո���棬�ٽ����˸�
				}
			}
		}
		else {
			break;
		}
	}
	password[i] = '\0';

}
//ע�ắ��
void regist()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t����ִ��ע�ắ��...");
	char password1[7];
	errno_t err;
	err= fopen_s(&fp,"atm.txt","ab+");
	if (err!= 0)
	{
		printf("\n\n\t\t\t\t\t���ļ�ʧ��");
		return;
	}

	printf("\n\n\n\t\t\t\t\t�������û�����");
	rewind(stdin);
	gets_s(client.name);
	printf("\n\t\t\t\t\t�û���Ϊ��%s", client.name);
	while (1)
	{
		while (1)
		{
			printf("\n\n\t\t\t\t\t�������û����룺");
			rewind(stdin);
			inputPassword(client.password);
			int length = strlen(client.password);
			if (length == 6)break;
			else
				printf("\n\n\t\t\t\t\t�û����볤�ȱ�������λ����");
		}
		printf("\n\n\t\t\t\t\t���ٴ�ȷ�����룺");
		rewind(stdin);
		inputPassword(password1);
		if (strcmp(client.password, password1) == 0)break;
		else
			printf("\n\n\t\t\t\t\t�����������벻һ�£����������룺");
	}

	//printf("\n\n\t\t\t\t\t�������û��˺ţ�");
	//scanf_s("%d", &client[count].account);
	//�Զ������˺�
	rewind(fp);
	if (fread(&t, sizeof(t), 1, fp) == 1)
	{
		fseek(fp, -SizeOf, 2);
		fread(&t, sizeof(t), 1, fp);//��ȡ���һ����¼
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

	printf("\n\n\n\t\t\t\t\t\tע��ɹ���\n");
	printf("\n\n\t\t\t\t\t�����˺�Ϊ��%d\n", client.account);


}

//��ѯ���
void selectMoney()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t���ڲ�ѯ���...");
	printf("\n\n\n\n\t\t\t\t\t�����˻����Ϊ��%.2lf", t.money);
}
//���
void saveMoney()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t���ڴ��...");
	int mm;
	printf("\n\n\n\n\t\t\t\t\t���������");
	scanf_s("%d", &mm);
	t.money += mm;
	fseek(fp, -SizeOf, 1);//ƫ��ָ��
	fwrite(&t, sizeof(t), 1, fp);//д������
	printf("\n\n\n\t\t\t\t\t���ɹ���");
}
//ȡ��
void getMoney()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t����ȡ��...");
	int mm;
	printf("\n\n\n\n\t\t\t\t\t������ȡ���");
	scanf_s("%d", &mm);

	if(mm > t.money)
	{
		printf("\n\n\t\t\t\t\t���㣡");

	}
	else
	{
		t.money -= mm;
		fseek(fp, -SizeOf, 1);
		fwrite(&t, sizeof(t), 1, fp);
		printf("\n\n\t\t\t\t\tȡ��ɹ���");
	}
}

//ת��
void transfer()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t����ת��...");
	int account1,flag=0,mm;
	int n = ftell(fp);
	struct bank temp;
	printf("\n\n\n\n\t\t\t\t\t������Է��˺ţ�");
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
		printf("\n\t\t\t\t\t������ת�˽�");
		scanf_s("%d", &mm);
		if (mm <= t.money)
		{
			t.money -= mm;
			temp.money += mm;
			//�޸��ļ�����
			fseek(fp, -SizeOf, 1);
			fwrite(&temp, sizeof(temp), 1, fp);
			fseek(fp, n - sizeof(t), 0);
			fwrite(&t, sizeof(t), 1, fp);
			printf("\n\n\t\t\t\t\tת�˳ɹ���");
		}
		else
		{
			printf("\n\n\t\t\t\t\t���㣡");
		}
	}
	else 
	{
		printf("\n\n\t\t\t\t\t������Ҫת�˵��˺ţ�");
	}
}
//�޸�����
void updatePassword()
{
	system("cls");
	int i;
	char password2[7], password3[7], password4[7];
	printf("\n\n\n\n\t\t\t\t\t�����޸�����...");
	for ( i= 0; i < 3; i++)
	{
		printf("\n\n\n\n\t\t\t\t\t����������룺");
		rewind(stdin);
		inputPassword(password2);
		if (strcmp(password2, t.password) == 0)
		{
			break;
		}
		else
		{
			printf("\n\n\t\t\t\t\t������������������������");
		}
	}
	if (i < 3)
	{
		while (1)
		{
			printf("\n\t\t\t\t\t�����������룺");
			rewind(stdin);
			inputPassword(password3);
			printf("\n\t\t\t\t\t��ȷ�������룺");
			rewind(stdin);
			inputPassword(password4);
			if (strcmp(password3, password4) == 0)
			{
				strcpy_s(t.password, password3);
				fseek(fp, -SizeOf, 1);//����ָ��
				fwrite(&t, sizeof(t), 1, fp);//�޸��ļ�
				printf("\n\n\t\t\t\t\t�����޸ĳɹ���");
				break;
			}
			else
			{
				printf("\n\n\t\t\t\t\t�����������벻һ�£�����������");
			}
		}

	}
	else
	{
		printf("\n\n\t\t\t\t\t����������������̿�....");
	}
}
//ע��
int logout()
{
	system("cls");
	char x;
	int zx=0;
	printf("\n\n\n\n\t\t\t\t\t����ע��...");
	printf("\n\n\n\n\t\t\t\t\t��Ҫע���Ŀͻ��˺��ǣ�%d\n", t.account);
	printf("\n\n\t\t\t\t\t�Ƿ����Ҫע��?ע����Y������ע����N����");
	rewind(stdin);
	scanf_s("%c", &x);
	if (x == 'Y' || x == 'y')
	{
		printf("\n\n\t\t\t\t\t��ע���˺ţ�%d",t.account);
		zx = 1;
	}
	else 
	{
		printf("\n\n\t\t\t\t\t��ע�������ط���ҳ�棡");
	}
	return zx;
}
//������溯��
void service()
{
	while (1)
	{
		system("cls");
		char xz;
		printf("\n\n\n\n\t\t\t\t\t����ʹ�÷�����...");
		printf("\n\n\n\n\t\t\t\t\t��A����ѯ");
		printf("\n\n\t\t\t\t\t��B�����");
		printf("\n\n\t\t\t\t\t��C��ȡ��");
		printf("\n\n\t\t\t\t\t��D��ת��");
		printf("\n\n\t\t\t\t\t��E���޸�����");
		printf("\n\n\t\t\t\t\t��F��ע��");
		printf("\n\n\t\t\t\t\t��G���˳�ϵͳ");
		printf("\n\n\n\t\t\t\t\t��ѡ��������ࣺ");
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
		printf("\n\n\n\n\t\t\t\t\t�����������....");
		_getch();
	}
}
//��½����
void login()
{
	system("cls");
	errno_t err;
	err = fopen_s(&fp, "atm.txt", "rb+");
	if (err != 0)
	{
		printf("\n\n\t\t\t\t\t��ʧ��!\n");
		return;
	}
	printf("\n\n\n\n\t\t\t\t\t����ִ�е�½����...");
	int account1, i, flag = 0;
	char password2[7];
	printf("\n\n\n\n\t\t\t\t\t�����������˺ţ�");
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
			printf("\n\t\t\t\t\t���������룺");
			inputPassword(password2);
			if (strcmp(password2, t.password) == 0)
			{
				printf("\n\n\n\t\t\t\t\t\t��½�ɹ���");
				service();
				break;
			}
		}
		if (j == 3)
		{
			printf("\n\n\t\t\t\t\t����������֤�����ɹ�,�̿���...");
		}

	}
	else 
	{
		printf("\n\n\t\t\t\t\tû���ҵ����˺�");
	}
	fclose(fp);
}
//�˳�ϵͳ
void quit()
{
	system("cls");
	int t = 1;
	for (int i = 0; i <= 100; i++)
	{
		printf("\n\n\n\t\t\t\t\tATM����ϵͳ�����˳������Ե�");
		for (int j = 1; j <= t; j++)
		{
			printf(".");
		}
		t++;
		if (t == 10)
			t = 1;
		printf("\n\n\t\t\t\t\t%d%%", i);//����
		for (int m = 0; m <= 1000; m++);//��ʱ����
		system("cls");//��������
	}
	exit(0);//�˳�����
}
