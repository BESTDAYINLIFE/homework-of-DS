#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdio.h>
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

using namespace std;

typedef struct {
	double  weight;//Ȩ��
	unsigned int parent;//˫�׽ڵ�
	unsigned int lchild;//���ӽڵ�
	unsigned int rchild;//���ӽڵ�
}HTNode, * HuffmanTree;//��̬��������洢��������
typedef char** HuffmanCode;//��̬��������洢�����������
typedef struct {
	double* w;
	char* MyChar;
	HuffmanCode MyHuffmanCode;
}Weight_Char_Code_Table;//��ʱ�洢Weight��ӦMyChar�Ķ��ձ�
typedef struct count_char {
	double countall = 0;//���ǵ����ַ�����ܴ�
	int counta = 0;
	int countb = 0;
	int countc = 0;
	int countd = 0;
	int counte = 0;
	int countf = 0;
	int countg = 0;
	int counth = 0;
	int counti = 0;
	int countj = 0;
	int countk = 0;
	int countl = 0;
	int countm = 0;
	int countn = 0;
	int counto = 0;
	int countp = 0;
	int countq = 0;
	int countr = 0;
	int counts = 0;
	int countt = 0;
	int countu = 0;
	int countv = 0;
	int countw = 0;
	int countx = 0;
	int county = 0;
	int countz = 0;
	int countA = 0;
	int countB = 0;
	int countC = 0;
	int countD = 0;
	int countE = 0;
	int countF = 0;
	int countG = 0;
	int countH = 0;
	int countI = 0;
	int countJ = 0;
	int countK = 0;
	int countL = 0;
	int countM = 0;
	int countN = 0;
	int countO = 0;
	int countP = 0;
	int countQ = 0;
	int countR = 0;
	int countS = 0;
	int countT = 0;
	int countU = 0;
	int countV = 0;
	int countW = 0;
	int countX = 0;
	int countY = 0;
	int countZ = 0;
	int count00 = 0;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	int count5 = 0;
	int count6 = 0;
	int count7 = 0;
	int count8 = 0;
	int count9 = 0;
	int countdouhao = 0;
	int countjuhao = 0;
	int countdanyinhao = 0;
	int countshuangyinhao = 0;
	int countzuokuohao = 0;
	int countyoukuohao = 0;
	int countkongge = 0;
	int counthuanhang = 0;
	int countandhao = 0;
	int counthengxian = 0;
	double frequencya = 0;
	double frequencyb = 0;
	double frequencyc = 0;
	double frequencyd = 0;
	double frequencye = 0;
	double frequencyf = 0;
	double frequencyg = 0;
	double frequencyh = 0;
	double frequencyi = 0;
	double frequencyj = 0;
	double frequencyk = 0;
	double frequencyl = 0;
	double frequencym = 0;
	double frequencyn = 0;
	double frequencyo = 0;
	double frequencyp = 0;
	double frequencyq = 0;
	double frequencyr = 0;
	double frequencys = 0;
	double frequencyt = 0;
	double frequencyu = 0;
	double frequencyv = 0;
	double frequencyw = 0;
	double frequencyx = 0;
	double frequencyy = 0;
	double frequencyz = 0;
	double frequencyA = 0;
	double frequencyB = 0;
	double frequencyC = 0;
	double frequencyD = 0;
	double frequencyE = 0;
	double frequencyF = 0;
	double frequencyG = 0;
	double frequencyH = 0;
	double frequencyI = 0;
	double frequencyJ = 0;
	double frequencyK = 0;
	double frequencyL = 0;
	double frequencyM = 0;
	double frequencyN = 0;
	double frequencyO = 0;
	double frequencyP = 0;
	double frequencyQ = 0;
	double frequencyR = 0;
	double frequencyS = 0;
	double frequencyT = 0;
	double frequencyU = 0;
	double frequencyV = 0;
	double frequencyW = 0;
	double frequencyX = 0;
	double frequencyY = 0;
	double frequencyZ = 0;
	double frequency00 = 0;
	double frequency1 = 0;
	double frequency2 = 0;
	double frequency3 = 0;
	double frequency4 = 0;
	double frequency5 = 0;
	double frequency6 = 0;
	double frequency7 = 0;
	double frequency8 = 0;
	double frequency9 = 0;
	double frequencydouhao = 0;
	double frequencydanyinhao = 0;
	double frequencyshuangyinhao = 0;
	double frequencyjuhao = 0;
	double frequencyzuokuohao = 0;
	double frequencyyoukuohao = 0;
	double frequencykongge = 0;
	double frequencyhuanhang = 0;
	double frequencyandhao = 0;
	double frequencyhengxian = 0;
	double frequencyall = 0;
};
count_char readchar;//ȫ�ֱ���ͳ��Ҫ����������ַ���Ŀ����ṹ��

//��������txt�ĵ������ַ���Ƶ�ʲ����뵽Output.txt.
void Count_All(char* Filename1, char* Filename2);

//Ϊ�˺�����ȡ���㣬�ٽ�Ȩ�����������һ������
void Output_Weight(char* Filename);

//���ļ��У������з����Ȩֵ������ʱ�ռ䲢ͳ��WeightΪ��0�ĸ�����
void Readin_Weight(char* Filename1, char* Filename2 , Weight_Char_Code_Table &Table ,int &n);

//�ҵ�Ȩֵ��С������ֵ���±꣬s1ȨֵС��s2Ȩֵ
void Select(HuffmanTree& HT, int n, int& W1, int& W2);

//��ʼ����������
void Init_Huffman(HuffmanTree& HT, int n);

//�������׷��������ļ�Output.txt.��
void Output_Huffman_File(HuffmanTree HT, int n,char*Filename);

//�����������
void Create_Huffman(HuffmanTree& HT,double* w, int n);

//�������������
void HuffmanCoding(HuffmanTree& HT, HuffmanCode&HC, int n);

//����������׷��������ļ�Output.txt.��
void Output_HuffmanCode_File(HuffmanTree HT,HuffmanCode &HC,char*Char, int n,char* Filename);

//���ñ������������ı����б�������������ļ�Encode.bin
void Output_Txt_to_CodeBin(char* Filename1, char* Filename2);

//���ñ������������ı����б�������ı��ļ�Encode.txt
void Output_Txt_to_CodeTxt(char* Filename1, char* Filename2, Weight_Char_Code_Table Table, int n);

//���ù������������������ı����б���������ı��ļ�NewInput.txt
void Output_CodeTxt_to_Txt(char* Filename1, char* Filename2, Weight_Char_Code_Table Table, int n);





