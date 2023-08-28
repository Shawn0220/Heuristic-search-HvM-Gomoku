#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
using namespace std;

// ����λ�úͷ���
class location
{
public:
	int i = 0;      // y ����
	int j = 0;      // x ����
	int number = 0; // ����
};

// ����ÿ������
class box
{
public:
	void draw();            // ����
public:
	int x = 0;              // x ����
	int y = 0;              // y ����
	int value = -1;         // ֵ�����壺1�����壺0����λ��-1��
	int background = 0;          // ģʽ
	bool isnew = false;     // �Ƿ�ѡ��
	COLORREF color = WHITE; // ���̱���ɫ
};

box BOX[19][19];      // 19X19����
int win = -1;         // Ӯ�ң�0�����壬1�����壬2��ƽ�֣�
int playcnt = 0;
bool changeflag = false;
int whosturn = 0;      // �ֵ�˭������
int playercolor = 0;  // �����ɫ
int dx[4]{ 1,0,1,1 }; // - | \ / �����ڵ���ֵ��ʾ�������ĸ����� ������ƽ�ƣ�����ƽ�ƣ��������ƣ��������ƣ� ͬʱȡ��������չ�� 8 ������
int dy[4]{ 0,1,1,-1 };
int score[3][5] = //���ֱ�
{
	{ 0, 90, 250, 500, 500 }, // 0���з����� 0 1 2 3 4����������
	{ 0, 0,  80,  300, 450 }, // 1���з����� 0 1 2 3 4����������
	{ 0, 0,  0,  70,  400 }  // 2���з����� 0 1 2 3 4����������
};
int bestx[361];   //����x����
int besty[361];   //����y����
int bestcnt = 0; //���Ž���

// ��������
void draw();                  // ����
void init();                  // ��ʼ��
location findbestlocation(int color, int c); // Ѱ�����λ��
void isWIN();                 // �ж���Ӯ
void game();                  // ��Ϸ������

// main����
int main()
{
	initgraph(700, 700); // ��ʼ����ͼ����
	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT); // ����͸�������������

	while (1)
	{
		init(); // ��ʼ��
		game(); // ��Ϸ��ʼ
		cleardevice();
	}
}

// �ຯ������

// box��draw��������
void box::draw()
{
	COLORREF thefillcolor = getfillcolor(); // ���������ɫ
	setlinestyle(PS_SOLID, 3);              // ����ʽ����
	setfillcolor(color);                    // �����ɫ����
	solidrectangle(x, y, x + 30, y + 30);   // �����ޱ߿��������
	if (isnew)
	{
		// ��������µ�
		// ���Ʊ߿���
		setlinecolor(RED);
		line(x + 1, y + 2, x + 20, y + 2);
		line(x + 2, y + 1, x + 2, y + 20);
		line(x + 29, y + 2, x + 22, y + 2);
		line(x + 29, y + 1, x + 29, y + 20);
		line(x + 2, y + 29, x + 20, y + 29);
		line(x + 2, y + 22, x + 2, y + 29);
		line(x + 29, y + 29, x + 18, y + 29);
		line(x + 29, y + 18, x + 29, y + 29);
	}
	setlinecolor(BLACK);
	switch (background)
	{
		// �����ǲ�ͬλ�ø����ڲ����̻��Ƶ���ʽ
	case 0:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		break;
	case 1:
		line(x + 14, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
	case 2:
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
	case 3:
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
	case 4:
		line(x + 15, y, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
	case 5:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x + 15, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
	case 6:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
	case 7:
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 15, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
	case 8:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y + 15, x + 30, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
	case 9:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 4);
		break;
	}
	switch (value)
	{
	case 0: // ����
		setfillcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	case 1: // ����
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	}
	setfillcolor(thefillcolor); // ��ԭ���ɫ
}

// ������������

// ��������
void draw()
{
	int number = 0; // ���������λ��
	// ���꣨��ֵ��
	TCHAR strnum[19][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15") ,_T("16") ,_T("17"),_T("18"),_T("19") };
	// ���꣨��ĸ��
	TCHAR strabc[19][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,_T("N"),_T("O") ,_T("P") ,_T("Q"),_T("R"),_T("S") };
	LOGFONT nowstyle;
	gettextstyle(&nowstyle);
	settextstyle(0, 0, NULL);
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			BOX[i][j].draw(); // ����
			if (BOX[i][j].isnew == true)
			{
				BOX[i][j].isnew = false; // ����һ������λ�õĺڿ����
			}
		}
	}
	// ��ע����
	for (int i = 0; i < 19; i++)
	{
		outtextxy(75 + number, 35, strabc[i]);
		outtextxy(53, 55 + number, strnum[i]);
		number += 30;
	}
	settextstyle(&nowstyle);
}

// ���̳�ʼ��
void init()
{
	win = -1;// ˭Ӯ��
	for (int i = 0, k = 0; i < 570; i += 30)
	{
		for (int j = 0, g = 0; j < 570; j += 30)
		{
			int background = 0;  // ������ʽ
			BOX[k][g].value = -1;
			BOX[k][g].color = RGB(255, 227, 132);// ���̵�ɫ
			// x��y ����
			BOX[k][g].x = 65 + j;
			BOX[k][g].y = 50 + i;
			// ������ʽ���ж�
			if (k == 0 && g == 0)
				background = 8;
			else if (k == 0 && g == 18)
				background = 7;
			else if (k == 18 && g == 18)
				background = 6;
			else if (k == 18 && g == 0)
				background = 5;
			else if (k == 0)
				background = 3;
			else if (k == 18)
				background = 4;
			else if (g == 0)
				background = 1;
			else if (g == 18)
				background = 2;
			else
				background = 0;
			BOX[k][g].background = background;
			g++;
		}
		k++;
	}
}

// ���ĺ���

// Ѱ�����λ��
location findbestlocation(int color, int c)
{
	if (c == 0)
	{
		//����ǵ�һ��
		//�������
		bestcnt = 0;
	}
	int MAXnumber = INT_MIN;    //��ѷ���
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (BOX[i][j].value == -1) { // ��λ -1
				//����ÿһ����λ��
				int length;        //��ǰ���򳤶�
				int emeny;         //��ǰ�������
				int nowi = 0;      //���ڱ�������y����
				int nowj = 0;      //���ڱ�������x����
				int thescore = 0;  //���λ�õĳ�ʼ����

				//�ж�5X5�ķ�Χ����û������
				int flag = 0;
				for (int k = 0; k < 4; k++)
				{
					nowi = i;
					nowj = j;
					nowi += dx[k];
					nowj += dy[k];
					if (nowi >= 0 && nowj >= 0&& nowi <= 18 && nowj <= 18&& BOX[nowi][nowj].value != -1) // ����ĳ��������ӣ��������ڣ��ҷǿ�
					{
						flag = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi += dx[k];
					nowj += dy[k];
					if (nowi >= 0 && nowj >= 0&& nowi <= 18 && nowj <= 18&& BOX[nowi][nowj].value != -1)
					{
						flag = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi -= dx[k];
					nowj -= dy[k];
					if (nowi >= 0 && nowj >= 0&& nowi <= 18 && nowj <= 18&& BOX[nowi][nowj].value != -1)
					{
						flag = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi -= dx[k];
					nowj -= dy[k];
					if (nowi >= 0 && nowj >= 0&& nowi <= 18 && nowj <= 18&& BOX[nowi][nowj].value != -1)
					{
						flag = 1;
						break;
					}
				}
				if (!flag)
				{
					//�����Χû�����ӣ�������һ����λ
					continue;
				}
				
				//����
				BOX[i][j].value = color; // ������������
				for (int k = 0; k < 4; k++) // ����ĸ����� �Լ����ӺͶԷ����� ������
				{
					
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color) // ��������
					{
						length++;
						nowj += dy[k];
						nowi += dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color) // �Է�����
					{
						emeny++;
					}

					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color) // ��������
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color) // �Է�����
					{
						emeny++;
					}

					length -= 2; // �жϳ��� ����2����Ϊ�Ӽ����nowi,j���������������Σ���Ҫ��length�������ӵ�ʵ�ʳ��ȣ�
					if (length > 4)
					{
						length = 4;
					}
					if (score[emeny][length] == 500) 
					{
						BOX[i][j].value = -1;
						return{ i,j,score[emeny][length] };
					}
					thescore += score[emeny][length];
					length = 0;
					emeny = 0;
				}


				//���ˣ�ԭ��ͬ�ϣ�
				BOX[i][j].value = !color;
				for (int k = 0; k < 4; k++)
				{
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj += dy[k];
						nowi += dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					length -= 2;
					if (length > 4)
					{
						length = 4;
					}
					if (score[emeny][length] == 500)
					{
						BOX[i][j].value = -1;
						return{ i,j,score[emeny][length] };
					}
					thescore += score[emeny][length];
					length = 0;
					emeny = 0;
				}

				BOX[i][j].value = -1;
				if (c < 3) // ����4�㣬ʱ��̫��������4�㣬����̫��
				{
					
					BOX[i][j].value = color; // �ö���λ��Ϊcolor���ݹ�Ѱ�ҶԷ���color�ķ���
					int nowscore = thescore - findbestlocation(!color, c + 1).number - 50*c; // �ݹ�����Է���û�д�λ�ú�ɻ�õ����ŵķ�ֵ nowscore����������-�Է��֣�
					BOX[i][j].value = -1;
					if (nowscore > MAXnumber)
					{
						MAXnumber = nowscore;
						if (c == 0)
						{
							bestcnt = 0; // ÿ��λ�õ�һ�εݹ�ʱ�������������
						}
					}
					if (c == 0)
					{
						//��һ��
						if (nowscore >= MAXnumber)
						{
							//�ѵ�ǰλ�ü�������
							bestx[bestcnt] = i;
							besty[bestcnt] = j;
							bestcnt++;
						}
					}
				}
				else {
					//����ݹ鵽�˵��Ĳ�
					if (thescore > MAXnumber)
					{
						MAXnumber = thescore;
					}
					}
			}
		}
	}
	if (MAXnumber == 500 && playcnt == 3) // ������ֺڷ����ƣ����Ծ�����������
		changeflag = true;
	if (c == 0)
	{
		int mynum = rand() % bestcnt;
		return { bestx[mynum],besty[mynum],MAXnumber };
	}
	//������
	return { 0,0,MAXnumber };
}

// �ж���Ӯ
void isWIN()
{
	bool isfull = true; // �����Ƿ�����
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (BOX[i][j].value != -1)
			{
				// ����ÿ�����ܵ�λ��
				int nowcolor = BOX[i][j].value; // ���ڱ���������ɫ
				int length[4] = { 0,0,0,0 };    // �ĸ�����ĳ���
				for (int k = 0; k < 4; k++)
				{
					// ԭ��ͬѰ�����λ��
					int nowi = i;
					int nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == nowcolor)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == 1 - nowcolor)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
				}
				for (int k = 0; k < 4; k++)
				{
					if (length[k] >= 5) {
						// ���������
						if (nowcolor == playercolor)
						{
							win = playercolor; // ���ʤ
						}
						if (nowcolor == 1 - playercolor)
						{
							win = 1 - playercolor; // ����ʤ
						}
					}
				}
			}
			else
			{
				//���Ϊ��
				isfull = false;//����û��
			}
		}
	}
	if (isfull)
	{
		// �����������
		win = 2; // ƽ��
	}
}

// ��Ϸ������
void game()
{
	bool isinit;
	// ��һ�����ͣ������
	int oldi = 0;
	int oldj = 0;

	playercolor = 1;
	// ���Ʊ���
	setfillcolor(RGB(255, 227, 132));
	solidrectangle(40, 25, 645, 630);
	// ����������ʽ
	settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);
	settextcolor(BLACK);
	// �����ʾ��
	if (playercolor == 0)
	{
		isinit = 1;
		outtextxy(150, 650, _T("���ִ�׺��У�����ִ������"));
		whosturn = 1;
	}
	else
	{
		isinit = 0;
		outtextxy(150, 650, _T("���ִ�����У�����ִ�׺���"));
		whosturn = 0;
	}
	draw(); // ����
	while (1)
	{
	NEXTPLAYER:
		// �������
		if (whosturn == 0)
		{
			MOUSEMSG mouse = GetMouseMsg(); // ��ȡ�����Ϣ
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 19; j++)
				{
					if (mouse.x > BOX[i][j].x && mouse.x<BOX[i][j].x + 30//�ж�x����
						&& mouse.y>BOX[i][j].y && mouse.y < BOX[i][j].y + 30//�ж�y����
						&& BOX[i][j].value == -1)//�ж��Ƿ��ǿ�λ��
					{
						// ���ͣ��ĳһ����λ������
						if (mouse.mkLButton)
						{
							// ���������
							BOX[i][j].value = playercolor; // ����
							BOX[i][j].isnew = true;        // ��λ�ø���
							oldi = -1;
							oldj = -1;
							// ��һ�����
							whosturn = 1;
							goto DRAW;
						}
						// ����ѡ���
						BOX[oldi][oldj].isnew = false;
						BOX[oldi][oldj].draw();
						BOX[i][j].isnew = true;
						BOX[i][j].draw();
						oldi = i;
						oldj = j;
					}
				}
			}
		}
		// ��������
		else
		{
			if (isinit)
			{
				// �������
				isinit = 0;
				int drawi = 9;
				int drawj = 9;
				while (BOX[drawi][drawj].value != -1)
				{
					drawi--;
					drawj++;
				}
				BOX[drawi][drawj].value = 1 - playercolor;
				BOX[drawi][drawj].isnew = true;
			}
			else
			{
				location best;
				best = findbestlocation(1 - playercolor, 0); // Ѱ�����λ��
				if (changeflag)
					break;
				BOX[best.i][best.j].value = 1 - playercolor;//�������λ��
				BOX[best.i][best.j].isnew = true;
			}
			whosturn = 0;
			goto DRAW; // �ֵ���һ��
		}
	}
DRAW: // ����
	isWIN(); // �����Ӯ
	draw();
	oldi = 0;
	oldj = 0;
	if (win == -1)
	{
		// ���û����ʤ��
		Sleep(500);
		playcnt = playcnt + 1; /////////////////////////////////////////////////////////////////////////////////
		if (changeflag) { // ���ֽ���
			playercolor = 0;
			whosturn = 0;
			setfillcolor(RGB(255, 255, 255));
			fillrectangle(000, 650, 700, 680);
			setfillcolor(RGB(255, 227, 132));
			outtextxy(115, 650, _T("����ѡ�����ֽ����������ִ����"));
		}
		changeflag = false;
		goto NEXTPLAYER; // ǰ����һ�����
	}
	// ʤ������
	settextcolor(RGB(0, 255, 0));
	Sleep(1000);
	if (win == 0)
	{
		fillrectangle(000, 650, 700, 680);
		setfillcolor(RGB(255, 227, 132));
		settextcolor(BLACK);
		outtextxy(320, 650, _T("��ʤ"));
	}
	if (win == 1)
	{
		fillrectangle(000, 650, 700, 680);
		setfillcolor(RGB(255, 227, 132));
		settextcolor(BLACK);
		outtextxy(320, 650, _T("��ʤ"));
	}
	if (win == 2)
	{
		fillrectangle(000, 650, 700, 680);
		setfillcolor(RGB(255, 227, 132));
		settextcolor(BLACK);
		outtextxy(320, 650, _T("ƽ��"));
	}
	// ����Ӧʱ��
	Sleep(50000);
	return;
}