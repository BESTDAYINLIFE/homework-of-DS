#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

int main() {
	srand(time(NULL));//ͨ��ѧϰ�˽⵽��ʱ����Ϊ���Ӳ�����α�����
	                  //�������������Ч��
	 int num[5] = { 0 };//���������������������
	 cout << "���ɵ���������಻�ظ��������Ϊ��\n";
	 for (int i = 0; i < 5; i++) {
		 while(1) {//ʹ��ѭ����֤������������ظ�
		 int a = rand() % 9 + 1;//�������1-10֮��������
		 int round = 0;
		 num[i] = a;//�����������������������
		 for (int j = 0; j < i; j++) {
			 if (num[j] == a) {
				 round = 1; break;
			 }
		 }
			 if (round == 0) {
				 num[i] = a;
				 break;
			 
		 }
		 }cout  << num[i] << endl;//�������
	 } 
	//�����������������
	 cout << "�����������Ӵ�С����Ϊ��\n";
	 for (int i = 0; i < 5; i++) {
		 for (int j = 1; j < 5; j++) {
			 if (num[j] > num[j-1]) {
				 int temp = num[j];
				 num[j] = num[j-1];
				 num[j-1] = temp;
				 temp = 0;
			 }
		 }
	 }for (int i = 0; i < 5; i++) {
		 cout << num[i] << endl;//�������
	 }
	 //����һ�������������λ��
	 int x = 10000 * num[0] + 1000 * num[1] + 
		 100 * num[2] + 10 * num[3] + num[4];
	 cout <<"�����λ��Ϊ��" << x << endl;//�������
	
	 //д���ļ�����
	 FILE *fp1;
	 fp1 = fopen("output.txt","wt");
	 if (fp1==NULL) {
		 cout << "�ļ���ʧ��" << endl;
		 exit(-1);
	 }
		 fprintf(fp1, "%d\n",x);
		 fclose(fp1);


		 //�����������׷��д���ļ�����
		 FILE* fp2;
		 fp2 = fopen("output.txt", "a+t");
		 if (fp2 == NULL) {
			 cout << "�ļ���ʧ��" << endl;
			 exit(-1);
		 }
		 int  y;
		 while(x!=0)
		 { y = x % 10; 
		 x = x / 10;
		 fprintf(fp2,"%d", y);
		 }
		 fclose(fp2);

}