#include "header.h"
int main()
{//本次作业需要操作的两个文件名
	char Filename1[] = "Input.txt";
	char Filename2[] = "Output.txt";
	char Filename3[] = "Weight.txt";
	char Filename4[] = "CharTable.txt";
	char Filename5[] = "Encode.txt";
	char Filename6[] = "Decode.txt";
	char Filename7[] = "Encode.bin";
	Count_All(Filename1, Filename2);

	Output_Weight(Filename3);
	int n = 0;//结点数初始化为0
	Weight_Char_Code_Table a;//编码表的搭建
    Readin_Weight(Filename3,Filename4,a, n);
	
	HuffmanTree MyHuffmanTree;
	Create_Huffman(MyHuffmanTree, a.w, n); //构建哈夫曼树

	Output_Huffman_File(MyHuffmanTree, n, Filename2);//将构建的哈夫曼树输出到文件中
	HuffmanCoding(MyHuffmanTree, a.MyHuffmanCode, n); //构建哈夫曼编码

	Output_HuffmanCode_File(MyHuffmanTree, a.MyHuffmanCode,a.MyChar ,n, Filename2);//将构建的哈夫曼树的编码输出到文件中

	Output_Txt_to_CodeTxt(Filename1, Filename5, a, n);//利用编码结果对所给文本进行编码输出文本文件Encode.txt

	Output_Txt_to_CodeBin(Filename5, Filename7);//用哈夫曼树对加密文件解码输出文本文件Decode.txt

	Output_CodeTxt_to_Txt(Filename5, Filename6, a, n);//利用加密文件反解码



	cout << "运行到此处已全部完成！！！" << endl;
	return 0;

}
void Select(HuffmanTree& HT, int n, int& s1, int& s2) {
    int min_1=0;//先找到第一最小值
    for (int i = 1; i <= n; i++) {
        //此循环为遍历当前还没有父结点的点的第一个索引号
        if (HT[i].parent == 0) {
            min_1 = i;
            break;
        }
    }
    for (int i = min_1 + 1; i <= n; i++) {
        //此循环为遍历第一个索引号之后还没有父结点的并且权重比之前小的点的索引号
        if (HT[i].parent == 0 && HT[i].weight < HT[min_1].weight)
            min_1 = i;
    }
    s1 = min_1;//s1拿到了最小值

    int min_2=0;//再找到第二最小值
    for (int i = 1; i <= n; i++) {
        //此循环为遍历当前还没有父结点的点的第一个索引号
        if (HT[i].parent == 0&&i!=s1/*不可为s1*/) {
            min_2 = i;
            break;
        }
    }
    for (int i = min_2 + 1; i <= n; i++) {
        //此循环为遍历第一个索引号之后还没有父结点的并且权重比之前小的点的索引号
        if (HT[i].parent == 0 && HT[i].weight < HT[min_2].weight&&i != s1/*不可为s1*/)
            min_2 = i;
    }
    s2 = min_2;
}
void Init_Huffman(HuffmanTree& HT,int n){
    for (int i = 0; i < 2 * n - 1; i++) {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    HT[2 * n - 1].parent = 0;//根结点的父结点初始为0！
    cout << "哈夫曼树初始化完毕，进入下一步......" << endl << endl << endl;
}

void Create_Huffman(HuffmanTree &HT,double *w,int n) {
    int m = 2 * n - 1;//哈夫曼树的总结点数
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//开m+1个HTNode，其中0号单元没有用
    Init_Huffman(HT, n);
    for (int i = 1; i <= n; i++) {
        
        HT[i].weight = w[i - 1];//赋权值给n个叶子结点

    }
    for (int i = n + 1; i <= m; i++) {//构建哈夫曼树
       
        int s1, s2;
        //在HT[1...i-1]选择parent为0且weight最小的两个结点，序号分别为s1和s2。
        Select(HT, i - 1, s1, s2);
        HT[i].weight = HT[s1].weight + HT[s2].weight;//i的权重是s1和s2的权重之和
        //s1和s2的父结点是i
        HT[s1].parent = i;
        HT[s2].parent = i;
        //父结点i的孩子是s1和s2
        HT[i].lchild = s1;
        HT[i].rchild = s2;

    }
    cout<<"哈夫曼树构造完毕，进入下一步......" << endl << endl << endl;
   
}
void Output_Huffman_File(HuffmanTree HT, int n, char* Filename) {
    int m = 2 * n - 1;////哈夫曼树的总结点数
    FILE* fp = NULL;
    fp = fopen(Filename, "a");
	fprintf(fp, "\n");
	fprintf(fp, "HT\n\n");
    fprintf(fp,"num     weight       parent        lchild      rchild\n");
    fprintf(fp,"0                                                                                   \n");
    for (int i = 1; i <= m; i++)
    {
       fprintf(fp,"%-4d   %-6.9lf   %-6d   %-6d   %-6d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
       fprintf(fp,"\n");
    }
    fclose(fp);
    cout << "已将哈夫曼树以表格样式追加输出到文件Output.txt，进入下一步......" << endl << endl << endl;
}

void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int n) {
    HC = (HuffmanCode)malloc(sizeof(char*) * (n + 1));//开n+1个空间
    char* code = (char*)malloc(sizeof(char) * n);
    //辅助空间，编码最长为n（最长时，前n-1个用于存储数据，最后1个用于存放'\0'）
    code[n - 1] = '\0';
    for (int i = 1; i <= n; i++) {
        int start = n - 1;//每次生成数据的哈夫曼编码之前，先将start指针指向‘\0’
        int c = i;//正在进行的第i个数据的编码
        int p = HT[c].parent;//找到该数据的父结点
        while (p != NULL) {
            //父结点为根部结点时，停止
            if (HT[p].lchild == c)
                code[--start] = '0';
            else
                code[--start] = '1';
            c = p;
            p = HT[c].parent;
        }
        HC[i] = (char*)malloc((n - start) * sizeof(char));
        strcpy(HC[i], &code[start]);
    }
    free(code);
    cout << "哈夫曼编码完毕，进入下一步......" << endl << endl << endl;
}


void Output_HuffmanCode_File(HuffmanTree HT,HuffmanCode& HC, char* Char, int n, char* Filename) {
    FILE *fp = NULL;
    fp = fopen(Filename, "a");
    fprintf(fp, "\n");
    fprintf(fp, "HC\n\n");
    for (int i = 1; i <= n; i++) //输出哈夫曼编码
    {
        fprintf(fp,"权重为%.9lf对应字符%c的编码为:%s\n", HT[i].weight,Char[i-1] ,HC[i]);
    }
    fclose(fp);
    cout << "已将哈夫曼编码追加输出到文件Output.txt，进入下一步......" << endl << endl << endl;
}
void Count_All(char* Filename1, char* Filename2) {
	cout << "正在统计字符，请稍候......\n\n\n\n\n";
	FILE* fp1 = NULL;//读文件流
	fp1 = fopen(Filename1, "r");
	while (!feof(fp1)) {
		char check[1] = { 0 };
		fread(check, sizeof(char), 1, fp1);
		switch (check[0])
		{
		case 'a':readchar.counta++; readchar.countall++; break;
		case 'b':readchar.countb++; readchar.countall++; break;
		case 'c':readchar.countc++; readchar.countall++; break;
		case 'd':readchar.countd++; readchar.countall++; break;
		case 'e':readchar.counte++; readchar.countall++; break;
		case 'f':readchar.countf++; readchar.countall++; break;
		case 'g':readchar.countg++; readchar.countall++; break;
		case 'h':readchar.counth++; readchar.countall++; break;
		case 'i':readchar.counti++; readchar.countall++; break;
		case 'j':readchar.countj++; readchar.countall++; break;
		case 'k':readchar.countk++; readchar.countall++; break;
		case 'l':readchar.countl++; readchar.countall++; break;
		case 'm':readchar.countm++; readchar.countall++; break;
		case 'n':readchar.countn++; readchar.countall++; break;
		case 'o':readchar.counto++; readchar.countall++; break;
		case 'p':readchar.countp++; readchar.countall++; break;
		case 'q':readchar.countq++; readchar.countall++; break;
		case 'r':readchar.countr++; readchar.countall++; break;
		case 's':readchar.counts++; readchar.countall++; break;
		case 't':readchar.countt++; readchar.countall++; break;
		case 'u':readchar.countu++; readchar.countall++; break;
		case 'v':readchar.countv++; readchar.countall++; break;
		case 'w':readchar.countw++; readchar.countall++; break;
		case 'x':readchar.countx++; readchar.countall++; break;
		case 'y':readchar.county++; readchar.countall++; break;
		case 'z':readchar.countz++; readchar.countall++; break;
		case 'A':readchar.countA++; readchar.countall++; break;
		case 'B':readchar.countB++; readchar.countall++; break;
		case 'C':readchar.countC++; readchar.countall++; break;
		case 'D':readchar.countD++; readchar.countall++; break;
		case 'E':readchar.countE++; readchar.countall++; break;
		case 'F':readchar.countF++; readchar.countall++; break;
		case 'G':readchar.countG++; readchar.countall++; break;
		case 'H':readchar.countH++; readchar.countall++; break;
		case 'I':readchar.countI++; readchar.countall++; break;
		case 'J':readchar.countJ++; readchar.countall++; break;
		case 'K':readchar.countK++; readchar.countall++; break;
		case 'L':readchar.countL++; readchar.countall++; break;
		case 'M':readchar.countM++; readchar.countall++; break;
		case 'N':readchar.countN++; readchar.countall++; break;
		case 'O':readchar.countO++; readchar.countall++; break;
		case 'P':readchar.countP++; readchar.countall++; break;
		case 'Q':readchar.countQ++; readchar.countall++; break;
		case 'R':readchar.countR++; readchar.countall++; break;
		case 'S':readchar.countS++; readchar.countall++; break;
		case 'T':readchar.countT++; readchar.countall++; break;
		case 'U':readchar.countU++; readchar.countall++; break;
		case 'V':readchar.countV++; readchar.countall++; break;
		case 'W':readchar.countW++; readchar.countall++; break;
		case 'X':readchar.countX++; readchar.countall++; break;
		case 'Y':readchar.countY++; readchar.countall++; break;
		case 'Z':readchar.countZ++; readchar.countall++; break;
		case '0':readchar.count00++; readchar.countall++; break;
		case '1':readchar.count1++; readchar.countall++; break;
		case '2':readchar.count2++; readchar.countall++; break;
		case '3':readchar.count3++; readchar.countall++; break;
		case '4':readchar.count4++; readchar.countall++; break;
		case '5':readchar.count5++; readchar.countall++; break;
		case '6':readchar.count6++; readchar.countall++; break;
		case '7':readchar.count7++; readchar.countall++; break;
		case '8':readchar.count8++; readchar.countall++; break;
		case '9':readchar.count9++; readchar.countall++; break;
		case '.':readchar.countjuhao++; readchar.countall++; break;
		case ',':readchar.countdouhao++; readchar.countall++; break;
		case '\'':readchar.countdanyinhao++; readchar.countall++; break;
		case '\"':readchar.countshuangyinhao++; readchar.countall++; break;
		case '(':readchar.countzuokuohao++; readchar.countall++; break;
		case ')':readchar.countyoukuohao++; readchar.countall++; break;
		case '&':readchar.countandhao++; readchar.countall++; break;
		case '-':readchar.counthengxian++; readchar.countall++; break;
		case '\n':readchar.counthuanhang++; readchar.countall++; break;
		case '\ ':readchar.countkongge++; readchar.countall++; break;
		}
	}
	fclose(fp1);
	//分别计算所有字符的频度
	readchar.frequencya = readchar.counta / readchar.countall;
	readchar.frequencyb = readchar.countb / readchar.countall;
	readchar.frequencyc = readchar.countc / readchar.countall;
	readchar.frequencyd = readchar.countd / readchar.countall;
	readchar.frequencye = readchar.counte / readchar.countall;
	readchar.frequencyf = readchar.countf / readchar.countall;
	readchar.frequencyg = readchar.countg / readchar.countall;
	readchar.frequencyh = readchar.counth / readchar.countall;
	readchar.frequencyi = readchar.counti / readchar.countall;
	readchar.frequencyj = readchar.countj / readchar.countall;
	readchar.frequencyk = readchar.countk / readchar.countall;
	readchar.frequencyl = readchar.countl / readchar.countall;
	readchar.frequencym = readchar.countm / readchar.countall;
	readchar.frequencyn = readchar.countn / readchar.countall;
	readchar.frequencyo = readchar.counto / readchar.countall;
	readchar.frequencyp = readchar.countp / readchar.countall;
	readchar.frequencyq = readchar.countq / readchar.countall;
	readchar.frequencyr = readchar.countr / readchar.countall;
	readchar.frequencys = readchar.counts / readchar.countall;
	readchar.frequencyt = readchar.countt / readchar.countall;
	readchar.frequencyu = readchar.countu / readchar.countall;
	readchar.frequencyv = readchar.countv / readchar.countall;
	readchar.frequencyw = readchar.countw / readchar.countall;
	readchar.frequencyx = readchar.countx / readchar.countall;
	readchar.frequencyy = readchar.county / readchar.countall;
	readchar.frequencyz = readchar.countz / readchar.countall;
	readchar.frequencyA = readchar.countA / readchar.countall;
	readchar.frequencyB = readchar.countB / readchar.countall;
	readchar.frequencyC = readchar.countC / readchar.countall;
	readchar.frequencyD = readchar.countD / readchar.countall;
	readchar.frequencyE = readchar.countE / readchar.countall;
	readchar.frequencyF = readchar.countF / readchar.countall;
	readchar.frequencyG = readchar.countG / readchar.countall;
	readchar.frequencyH = readchar.countH / readchar.countall;
	readchar.frequencyI = readchar.countI / readchar.countall;
	readchar.frequencyJ = readchar.countJ / readchar.countall;
	readchar.frequencyK = readchar.countK / readchar.countall;
	readchar.frequencyL = readchar.countL / readchar.countall;
	readchar.frequencyM = readchar.countM / readchar.countall;
	readchar.frequencyN = readchar.countN / readchar.countall;
	readchar.frequencyO = readchar.countO / readchar.countall;
	readchar.frequencyP = readchar.countP / readchar.countall;
	readchar.frequencyQ = readchar.countQ / readchar.countall;
	readchar.frequencyR = readchar.countR / readchar.countall;
	readchar.frequencyS = readchar.countS / readchar.countall;
	readchar.frequencyT = readchar.countT / readchar.countall;
	readchar.frequencyU = readchar.countU / readchar.countall;
	readchar.frequencyV = readchar.countV / readchar.countall;
	readchar.frequencyW = readchar.countW / readchar.countall;
	readchar.frequencyX = readchar.countX / readchar.countall;
	readchar.frequencyY = readchar.countY / readchar.countall;
	readchar.frequencyZ = readchar.countZ / readchar.countall;
	readchar.frequency1 = readchar.count1 / readchar.countall;
	readchar.frequency2 = readchar.count2 / readchar.countall;
	readchar.frequency3 = readchar.count3 / readchar.countall;
	readchar.frequency4 = readchar.count4 / readchar.countall;
	readchar.frequency5 = readchar.count5 / readchar.countall;
	readchar.frequency6 = readchar.count6 / readchar.countall;
	readchar.frequency7 = readchar.count7 / readchar.countall;
	readchar.frequency8 = readchar.count8 / readchar.countall;
	readchar.frequency9 = readchar.count9 / readchar.countall;
	readchar.frequency00 = readchar.count00 / readchar.countall;
	readchar.frequencydouhao = readchar.countdouhao / readchar.countall;
	readchar.frequencyjuhao = readchar.countjuhao / readchar.countall;
	readchar.frequencydanyinhao = readchar.countdanyinhao / readchar.countall;
	readchar.frequencyshuangyinhao = readchar.countshuangyinhao / readchar.countall;
	readchar.frequencyzuokuohao = readchar.countzuokuohao / readchar.countall;
	readchar.frequencyyoukuohao = readchar.countyoukuohao / readchar.countall;
	readchar.frequencyandhao = readchar.countandhao / readchar.countall;
	readchar.frequencyhengxian = readchar.counthengxian / readchar.countall;
	readchar.frequencyhuanhang = readchar.counthuanhang / readchar.countall;
	readchar.frequencykongge = readchar.countkongge / readchar.countall;
	readchar.frequencyall= 
	readchar.frequencya +
	readchar.frequencyb +
	readchar.frequencyc +
	readchar.frequencyd +
	readchar.frequencye +
	readchar.frequencyf +
	readchar.frequencyg +
	readchar.frequencyh +
	readchar.frequencyi + 
	readchar.frequencyj +
	readchar.frequencyk +
	readchar.frequencyl +
	readchar.frequencym +
	readchar.frequencyn +
	readchar.frequencyo +
	readchar.frequencyp +
	readchar.frequencyq +
	readchar.frequencyr +
	readchar.frequencys +
	readchar.frequencyt +
	readchar.frequencyu +
	readchar.frequencyv +
	readchar.frequencyw +
	readchar.frequencyx +
	readchar.frequencyy +
	readchar.frequencyz +
	readchar.frequencyA +
	readchar.frequencyB +
	readchar.frequencyC +
	readchar.frequencyD +
	readchar.frequencyE +
	readchar.frequencyF +
	readchar.frequencyG +
	readchar.frequencyH +
	readchar.frequencyI +
	readchar.frequencyJ +
	readchar.frequencyK +
	readchar.frequencyL +
	readchar.frequencyM +
	readchar.frequencyN +
	readchar.frequencyO +
	readchar.frequencyP +
	readchar.frequencyQ +
	readchar.frequencyR +
	readchar.frequencyS +
	readchar.frequencyT +
	readchar.frequencyU +
	readchar.frequencyV +
	readchar.frequencyW +
	readchar.frequencyX +
	readchar.frequencyY +
	readchar.frequencyZ +
	readchar.frequency1 +
	readchar.frequency2 +
	readchar.frequency3 +
	readchar.frequency4 +
	readchar.frequency5 +
	readchar.frequency6 +
	readchar.frequency7 +
	readchar.frequency8 +
	readchar.frequency9 +
	readchar.frequency00 +
	readchar.frequencydouhao +
	readchar.frequencyjuhao +
	readchar.frequencydanyinhao +
	readchar.frequencyshuangyinhao +
	readchar.frequencyzuokuohao +
	readchar.frequencyyoukuohao +
	readchar.frequencyandhao +
	readchar.frequencyhengxian +
	readchar.frequencyhuanhang +
	readchar.frequencykongge;


	FILE* fp2 = NULL;//把出现的字符极其对应频度输出到Output.txt
	fp2 = fopen(Filename2, "w");
	fprintf(fp2, "Input.txt中所有可能会出现字符个数以及对应的频度如下表:\n");
	fprintf(fp2, "字符    个数     频度   \n");
	fprintf_s(fp2, "a%9d    %.9lf\n", readchar.counta, readchar.frequencya);
	fprintf_s(fp2, "b%9d    %.9lf\n", readchar.countb, readchar.frequencyb);
	fprintf_s(fp2, "c%9d    %.9lf\n", readchar.countc, readchar.frequencyc);
	fprintf_s(fp2, "d%9d    %.9lf\n", readchar.countd, readchar.frequencyd);
	fprintf_s(fp2, "e%9d    %.9lf\n", readchar.counte, readchar.frequencye);
	fprintf_s(fp2, "f%9d    %.9lf\n", readchar.countf, readchar.frequencyf);
	fprintf_s(fp2, "g%9d    %.9lf\n", readchar.countg, readchar.frequencyg);
	fprintf_s(fp2, "h%9d    %.9lf\n", readchar.counth, readchar.frequencyh);
	fprintf_s(fp2, "i%9d    %.9lf\n", readchar.counti, readchar.frequencyi);
	fprintf_s(fp2, "j%9d    %.9lf\n", readchar.countj, readchar.frequencyj);
	fprintf_s(fp2, "k%9d    %.9lf\n", readchar.countk, readchar.frequencyk);
	fprintf_s(fp2, "l%9d    %.9lf\n", readchar.countl, readchar.frequencyl);
	fprintf_s(fp2, "m%9d    %.9lf\n", readchar.countm, readchar.frequencym);
	fprintf_s(fp2, "n%9d    %.9lf\n", readchar.countn, readchar.frequencyn);
	fprintf_s(fp2, "o%9d    %.9lf\n", readchar.counto, readchar.frequencyo);
	fprintf_s(fp2, "p%9d    %.9lf\n", readchar.countp, readchar.frequencyp);
	fprintf_s(fp2, "q%9d    %.9lf\n", readchar.countq, readchar.frequencyq);
	fprintf_s(fp2, "r%9d    %.9lf\n", readchar.countr, readchar.frequencyr);
	fprintf_s(fp2, "s%9d    %.9lf\n", readchar.counts, readchar.frequencys);
	fprintf_s(fp2, "t%9d    %.9lf\n", readchar.countt, readchar.frequencyt);
	fprintf_s(fp2, "u%9d    %.9lf\n", readchar.countu, readchar.frequencyu);
	fprintf_s(fp2, "v%9d    %.9lf\n", readchar.countv, readchar.frequencyv);
	fprintf_s(fp2, "w%9d    %.9lf\n", readchar.countw, readchar.frequencyw);
	fprintf_s(fp2, "x%9d    %.9lf\n", readchar.countx, readchar.frequencyx);
	fprintf_s(fp2, "y%9d    %.9lf\n", readchar.county, readchar.frequencyy);
	fprintf_s(fp2, "z%9d    %.9lf\n", readchar.countz, readchar.frequencyz);
	fprintf_s(fp2, "A%9d    %.9lf\n", readchar.countA, readchar.frequencyA);
	fprintf_s(fp2, "B%9d    %.9lf\n", readchar.countB, readchar.frequencyB);
	fprintf_s(fp2, "C%9d    %.9lf\n", readchar.countC, readchar.frequencyC);
	fprintf_s(fp2, "D%9d    %.9lf\n", readchar.countD, readchar.frequencyD);
	fprintf_s(fp2, "E%9d    %.9lf\n", readchar.countE, readchar.frequencyE);
	fprintf_s(fp2, "F%9d    %.9lf\n", readchar.countF, readchar.frequencyF);
	fprintf_s(fp2, "G%9d    %.9lf\n", readchar.countG, readchar.frequencyG);
	fprintf_s(fp2, "H%9d    %.9lf\n", readchar.countH, readchar.frequencyH);
	fprintf_s(fp2, "I%9d    %.9lf\n", readchar.countI, readchar.frequencyI);
	fprintf_s(fp2, "J%9d    %.9lf\n", readchar.countJ, readchar.frequencyJ);
	fprintf_s(fp2, "K%9d    %.9lf\n", readchar.countK, readchar.frequencyK);
	fprintf_s(fp2, "L%9d    %.9lf\n", readchar.countL, readchar.frequencyL);
	fprintf_s(fp2, "M%9d    %.9lf\n", readchar.countM, readchar.frequencyM);
	fprintf_s(fp2, "N%9d    %.9lf\n", readchar.countN, readchar.frequencyN);
	fprintf_s(fp2, "O%9d    %.9lf\n", readchar.countO, readchar.frequencyO);
	fprintf_s(fp2, "P%9d    %.9lf\n", readchar.countP, readchar.frequencyP);
	fprintf_s(fp2, "Q%9d    %.9lf\n", readchar.countQ, readchar.frequencyQ);
	fprintf_s(fp2, "R%9d    %.9lf\n", readchar.countR, readchar.frequencyR);
	fprintf_s(fp2, "S%9d    %.9lf\n", readchar.countS, readchar.frequencyS);
	fprintf_s(fp2, "T%9d    %.9lf\n", readchar.countT, readchar.frequencyT);
	fprintf_s(fp2, "U%9d    %.9lf\n", readchar.countU, readchar.frequencyU);
	fprintf_s(fp2, "V%9d    %.9lf\n", readchar.countV, readchar.frequencyV);
	fprintf_s(fp2, "W%9d    %.9lf\n", readchar.countW, readchar.frequencyW);
	fprintf_s(fp2, "X%9d    %.9lf\n", readchar.countX, readchar.frequencyX);
	fprintf_s(fp2, "Y%9d    %.9lf\n", readchar.countY, readchar.frequencyY);
	fprintf_s(fp2, "Z%9d    %.9lf\n", readchar.countZ, readchar.frequencyZ);
	fprintf_s(fp2, "0%9d    %.9lf\n", readchar.count00, readchar.frequency00);
	fprintf_s(fp2, "1%9d    %.9lf\n", readchar.count1, readchar.frequency1);
	fprintf_s(fp2, "2%9d    %.9lf\n", readchar.count2, readchar.frequency2);
	fprintf_s(fp2, "3%9d    %.9lf\n", readchar.count3, readchar.frequency3);
	fprintf_s(fp2, "4%9d    %.9lf\n", readchar.count4, readchar.frequency4);
	fprintf_s(fp2, "5%9d    %.9lf\n", readchar.count5, readchar.frequency5);
	fprintf_s(fp2, "6%9d    %.9lf\n", readchar.count6, readchar.frequency6);
	fprintf_s(fp2, "7%9d    %.9lf\n", readchar.count7, readchar.frequency7);
	fprintf_s(fp2, "8%9d    %.9lf\n", readchar.count8, readchar.frequency8);
	fprintf_s(fp2, "9%9d    %.9lf\n", readchar.count9, readchar.frequency9);
	fprintf_s(fp2, ",%9d    %.9lf\n", readchar.countdouhao, readchar.frequencydouhao);
	fprintf_s(fp2, ".%9d    %.9lf\n", readchar.countjuhao, readchar.frequencyjuhao);
	fprintf_s(fp2, "\'%9d    %.9lf\n", readchar.countdanyinhao, readchar.frequencydanyinhao);
	fprintf_s(fp2, "\"%9d    %.9lf\n", readchar.countshuangyinhao, readchar.frequencyshuangyinhao);
	fprintf_s(fp2, "-%9d    %.9lf\n", readchar.counthengxian, readchar.frequencyhengxian);
	fprintf_s(fp2, "&%9d    %.9lf\n", readchar.countandhao, readchar.frequencyandhao);
	fprintf_s(fp2, "(%9d    %.9lf\n", readchar.countzuokuohao, readchar.frequencyzuokuohao);
	fprintf_s(fp2, ")%9d    %.9lf\n", readchar.countyoukuohao, readchar.frequencyyoukuohao);
	fprintf_s(fp2, "Space  %d    %.9lf\n", readchar.countkongge, readchar.frequencykongge);
	fprintf_s(fp2, "Enter  %d     %.9lf\n", readchar.counthuanhang, readchar.frequencyhuanhang);
	fprintf_s(fp2, "All%9.0lf %.9lf\n", readchar.countall,readchar.frequencyall);
	fclose(fp2);
	cout << "字符统计完毕，并且输入至文件Out,txt中,进入下一步\n\n\n\n\n";
}
void Output_Weight(char* Filename) {
	FILE *fp2 = NULL;
	fp2 = fopen(Filename, "w");
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencya);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyb);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyc);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyd);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencye);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyf);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyg);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyh);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyi);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyj);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyk);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyl);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencym);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyn);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyo);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyp);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyq);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyr);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencys);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyt);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyu);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyv);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyw);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyx);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyy);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyz);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyA);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyB);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyC);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyD);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyE);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyF);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyG);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyH);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyI);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyJ);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyK);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyL);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyM);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyN);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyO);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyP);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyQ);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyR);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyS);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyT);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyU);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyV);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyW);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyX);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyY);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyZ);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency00);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency1);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency2);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency3);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency4);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency5);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency6);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency7);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency8);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequency9);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencydouhao);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyjuhao);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencydanyinhao);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyshuangyinhao);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyhengxian);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyandhao);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyzuokuohao);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencyyoukuohao);
	fprintf_s(fp2, "%.9lf\n",  readchar.frequencykongge);
	fprintf_s(fp2, "%.9lf\n", readchar.frequencyhuanhang);
	fclose(fp2);

}
void Readin_Weight(char* Filename1,char*Filename2, Weight_Char_Code_Table& Table,int &n) {
	n = 0;
	//第一次文件操作是为了统计Weight为非0的个数
	FILE* cp = NULL;
	cp = fopen(Filename1, "r");
	while (!feof(cp)) {
		double tmp = 0;
		fscanf(cp, "%lf\n", &tmp);
		if (tmp > 0) {
			n++;
		}
	}
	fclose(cp);
	//第二次文件操作是为了给double*w分配空间并且赋值
	if (Table.w == NULL)
	{
		printf("权重的储存空间分配失败\n");
		exit(-1);
	}
	Table.w = (double*)malloc(sizeof(double) * n);
	Table.MyChar = (char*)malloc(sizeof(char) * (n));
	 int j = 0;
	FILE* ip1 = NULL;
	FILE* ip2 = NULL;//使用两个文件指针一个读入weight一个读该weight下的字符
	ip1 = fopen(Filename1, "r"); 
	ip2 = fopen(Filename2, "r");
	while ((!feof(ip1)) && (!feof(ip2))) {//tmp1临时存储权重tmp2临时存储对应的字符
		double tmp1 = 0;
		char   tmp2[1] = {0};
		fscanf_s(ip1, "%lf\n", &tmp1);
		fread(tmp2, sizeof(char), 1, ip2);
		if (tmp1 > 0) {
		Table.w[j] = tmp1;
		Table.MyChar[j] = tmp2[0];
		     j++;
			}
		
	}
	//Table.MyChar[n] = '0';//最后一个字符存0表示结束
	fclose(ip1);
	
}
void Output_Txt_to_CodeBin(char* Filename1, char* Filename2) {
	FILE *ip = NULL;//读入文件流
	FILE *op = NULL;//输出文件流
	ip = fopen(Filename1, "r");
	op = fopen(Filename2, "w+b");
	while (!feof(ip)) {
		char check[9] = { 0 };
		fread(check, sizeof(char), 8, ip);
		check[8] = '\0';
		char Bit = 0;
	     for (int j = 0; j < 8; j++) {
		if (check[j] == '1') { Bit = Bit << 1; Bit |= 0x00000001; }
		if (check[j] == '0') {Bit = Bit << 1;}
		}
		 fwrite(&Bit, sizeof(char), 1, op);
	}
	fclose(ip);
	fclose(op);
	cout << "已经利用编码结果对所给文本进行编码输出文本文件Encode.txt,进入下一步......." << endl << endl << endl;
}
void Output_Txt_to_CodeTxt(char* Filename1, char* Filename2, Weight_Char_Code_Table Table, int n) {
	FILE* ip = NULL;//读入文件流
	FILE* op = NULL;//输出文件流
	ip = fopen(Filename1, "r");
	op = fopen(Filename2, "w");
	while (!feof(ip)) {
		char check[1] = { 0 };
		check[0] = fgetc(ip);//对要读文件进行逐一字节对比验证
		for (int i = 0; i < n; i++) {
			if (Table.MyChar[i] == check[0]) {
				int code_length = strlen(Table.MyHuffmanCode[i + 1]);
				for (int j = 0; j < code_length; j++) {
					fprintf(op, "%c", Table.MyHuffmanCode[i + 1][j]);
				}
			}
		}
	}
	fclose(ip);
	fclose(op);
	cout << "已经利用编码结果对所给文本进行编码输出文本文件Encode.txt,进入下一步......." << endl << endl << endl;
}
void Output_CodeTxt_to_Txt(char* Filename1, char* Filename2, Weight_Char_Code_Table Table, int n) {
	FILE* ip = NULL;//读入文件流
	FILE* op = NULL;//输出文件流
	ip = fopen(Filename1, "r");
	op = fopen(Filename2, "w");
	int i = 1;//每次解码的字节数，从1开始
	while (1) {
		bool findchar = 0;//初始化没找到
		char* check = new char[i+1];
			for (int k = 0; k < i; k++) {
				check[k] = fgetc(ip);
			}
			check[i] = '\0';
			for (int j = 0; j < n; j++) {
				if (strcmp(Table.MyHuffmanCode[j + 1], check) == 0) {
			
					fprintf(op, "%c", Table.MyChar[j]);
					findchar = 1;//找到了就变成1
					i = 1;//同时i也会初始化为1，继续从1开始
					break;
				}
			}
			if (!findchar) {//没找到就退回原来文件指针位置，开始解码长度为（i+1）的字符
				if (feof(ip)) { break; }//继续
				fseek(ip, -i, SEEK_CUR);
				i++;
			}
			delete[]check;
		}

	
	fclose(ip);
	fclose(op);
	cout << "已经利用哈夫曼树对所给加密文本进行编码输出新文本文件NewInput.txt,进入下一步......." << endl << endl << endl;
}