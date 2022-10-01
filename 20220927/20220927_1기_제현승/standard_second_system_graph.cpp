#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <windows.h>

/**
* 
* �׷����׸��� ���� ���� - ��ó : https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=viapolar&logNo=220750238890
#define PIE 3.141592

HWND hwnd;
HDC hdc;

double rad(double degree)
{
    return PIE * degree / 180.0;                 //�� �� ������ ���� ������ �ٲ۴�.
}

int main(void)
{
    int degree, x, y;
    double radian, result;

    hwnd = GetForegroundWindow();
    hdc = GetWindowDC(hwnd);

    MoveToEx(hdc, 0, 200, 0);                   //��������ġ�̵�(x�� �׸���)
        LineTo(hdc, 400, 200);                      //��������ġ���� ������ ��ǥ�� �����׸���

        MoveToEx(hdc, 30, 350, 0);                  //��������ġ�̵�(y�� �׸���)
        LineTo(hdc, 30, 0);                         //��������ġ���� ������ ��ǥ�� �����׸���

        for (degree = 0; degree <= 360; degree++)
        {
            result = sin(rad((double)degree));
            x = degree + 30;
            y = 200-(int)(100*result);           //�� sin���� 0~1���� �̹Ƿ� 100�� �����ش�.
                SetPixel(hdc, x, y, RGB(0, 0, 255));     //�� ���� ��´�.RGB(, , )���� ���� ���� �޶�����.
        }
    return 0;
}
**/

HWND hwnd;
HDC hdc;
HPEN hPen;
void print_graph(double zeta, double w_n)
{
    double time = 0.0;
    double x = 0.0;
    double y = 0.0;

    printf("�Է� ��: %lf w_n: %lf \n", zeta, w_n);

    hwnd = GetForegroundWindow();
    hdc = GetWindowDC(hwnd);
    hPen = CreatePen(PS_DOT,1,RGB(0,0,0)); //���� ����

    MoveToEx(hdc, 0, 500, 0);                   //������ġ�̵�(x�� �׸���)
    LineTo(hdc, 800, 500);                      //������ġ���� ������ ��ǥ�� �����׸���

    MoveToEx(hdc, 40, 600, 0);                  //������ġ�̵�(y�� �׸���)
    LineTo(hdc,40, 100);                         //������ġ���� ������ ��ǥ�� �����׸���

    SelectObject(hdc, hPen);  //�׸� �� ����
    MoveToEx(hdc, 40, 400, 0);                  //������ġ�̵�(y=1 �������� �׸���)
    LineTo(hdc, 800, 400);                         //������ġ���� ������ ��ǥ�� �����׸���

    if (zeta > 1)
    {
        printf("�ý��� ���� - Overdamped\n");
        for (time = 0; time < 5; time +=0.01)
        {
            y = 1 - (2 * exp(-time)) + exp(-2 * time);
            //printf("exp1- %lf ", 2*exp(-time));
            //printf("exp2- %lf ", exp(-2*time));
            //printf("1- %lf ",1-2 * exp(-time));
            //printf("+exp2- %lf ", 1 - 2 * exp(-time)+exp(-2 * time));
              //  printf("time : %lf y: %lf \n",time, y); 
            
            x = time*100 + 30; //y���� x 30���� �׷���
            y = 500 - (int)(100* y);           //�� sin���� 0~1���� �̹Ƿ� 100�� �����ش�.
           SetPixel(hdc, x, y, RGB(0, 0, 255));     //�� ���� ��´�.RGB(, , )���� ���� ���� �޶�����.
        }

    }
    else if (zeta == 1)
    {
        printf("�ý��� ���� - Critically damped\n");
        for (time = 0; time < 5; time += 0.01)
        {
            y = 1 - exp(-w_n*time) - time*exp(-w_n * time);
           //printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 27; //y���� x 30���� �׷���
            y = 500 - (int)(100 * y);           //�� sin���� 0~1���� �̹Ƿ� 100�� �����ش�.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //�� ���� ��´�.RGB(, , )���� ���� ���� �޶�����.
        }
    }
    else if ( zeta > 0 && zeta < 1)
    {
        printf("�ý��� ���� - Underdamped\n");
        for (time = 0; time < 5; time += 0.0001)
        {
            y = 1 - (1/sqrt(1-pow(zeta,2.0)))*exp(-zeta*w_n*time)*sin((w_n*sqrt(1-pow(zeta,2.0)))*time+acos(zeta));
            // printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 40; //y���� x 30���� �׷���
            y = 500 - (int)(100 * y);           //�� sin���� 0~1���� �̹Ƿ� 100�� �����ش�.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //�� ���� ��´�.RGB(, , )���� ���� ���� �޶�����.
        }
    }
    else if (zeta == 0)
    {
        printf("�ý��� �ణ �Ҿ��� - Undamped(marginally unstable)\n");
        for (time = 0; time < 5; time += 0.0001)
        {
            y = 1 - (1 / sqrt(1 - pow(zeta, 2.0))) * exp(-zeta * w_n * time) * sin((w_n * sqrt(1 - pow(zeta, 2.0))) * time + acos(zeta));
            //printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 27; //y���� x 30���� �׷���
            y = 500 - (int)(100 * y);           //�� sin���� 0~1���� �̹Ƿ� 100�� �����ش�.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //�� ���� ��´�.RGB(, , )���� ���� ���� �޶�����.
        }
    }
    else if (zeta < 0 && zeta > -1)
    {
        printf("�ý��� �Ҿ��� - Negatively damped\n");
        for (time = 0; time < 5; time += 0.0001)
        {
            y = 1 - (1 / sqrt(1 - pow(zeta, 2.0))) * exp(-zeta * w_n * time) * sin((w_n * sqrt(1 - pow(zeta, 2.0))) * time + acos(zeta));
           // printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 40; //y���� x 30���� �׷���
            y = 500 - (int)(100 * y);           //�� sin���� 0~1���� �̹Ƿ� 100�� �����ش�.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //�� ���� ��´�.RGB(, , )���� ���� ���� �޶�����.
        }
    }
    else
    {
        printf("�ý��� �Ҿ��� - Negatively damped\n"); //������ ���� c������ -inf �� �߸鼭 ����� �������׷��� �����
        for (time = 0; time < 3; time += 0.0001)
        {
            y = 1 - (1 / sqrt(1 - pow(zeta, 2.0))) * exp(-zeta * w_n * time) * sin((w_n * sqrt(1 - pow(zeta, 2.0))) * time + acos(zeta));
          //  printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 27; //y���� x 30���� �׷���
            y = 500 - (int)(100 * y);           //�� sin���� 0~1���� �̹Ƿ� 100�� �����ش�.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //�� ���� ��´�.RGB(, , )���� ���� ���� �޶�����.
        }
    }
}

int main(void)
{
    double zeta = 0.0; //damping_ratio
    double w_n = 0.0; //natural frequency

    printf("damping_ratio - zeta�� �Է����ּ���.\n");
    printf("��: ");
    scanf("%lf", &zeta);

    printf("natural frequency - w_n�� �Է����ּ���.\n");
    printf("w_n: ");
    scanf("%lf", &w_n);
    
    printf("�Էµ� zeta�� natural frequency �� ���� �ڵ����� 2�� ������ �� �׷����� ����մϴ�.\n");
    print_graph(zeta,w_n);


 //   double w = 

}