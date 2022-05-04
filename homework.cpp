#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

int main() {
	srand(time(NULL));//通过学习了解到以时间作为种子产生的伪随机数
	                  //可以启到随机数效果
	 int num[5] = { 0 };//定义容纳五个整数的数组
	 cout << "生成的这五个互相不重复的随机数为：\n";
	 for (int i = 0; i < 5; i++) {
		 while(1) {//使用循环保证随机数产生不重复
		 int a = rand() % 9 + 1;//随机产生1-10之间的随机数
		 int round = 0;
		 num[i] = a;//将产生的随机数存于数组中
		 for (int j = 0; j < i; j++) {
			 if (num[j] == a) {
				 round = 1; break;
			 }
		 }
			 if (round == 0) {
				 num[i] = a;
				 break;
			 
		 }
		 }cout  << num[i] << endl;//输出调试
	 } 
	//将这五个数进行排序
	 cout << "这五个随机数从大到小排序为：\n";
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
		 cout << num[i] << endl;//输出调试
	 }
	 //生成一个满足题意的五位数
	 int x = 10000 * num[0] + 1000 * num[1] + 
		 100 * num[2] + 10 * num[3] + num[4];
	 cout <<"这个五位数为：" << x << endl;//输出调试
	
	 //写入文件操作
	 FILE *fp1;
	 fp1 = fopen("output.txt","wt");
	 if (fp1==NULL) {
		 cout << "文件打开失败" << endl;
		 exit(-1);
	 }
		 fprintf(fp1, "%d\n",x);
		 fclose(fp1);


		 //逆序操作并且追加写入文件操作
		 FILE* fp2;
		 fp2 = fopen("output.txt", "a+t");
		 if (fp2 == NULL) {
			 cout << "文件打开失败" << endl;
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