#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <windows.h>

/**
* 
* 그래프그리기 참고 예제 - 출처 : https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=viapolar&logNo=220750238890
#define PIE 3.141592

HWND hwnd;
HDC hdc;

double rad(double degree)
{
    return PIE * degree / 180.0;                 //← 도 단위를 라디안 단위로 바꾼다.
}

int main(void)
{
    int degree, x, y;
    double radian, result;

    hwnd = GetForegroundWindow();
    hdc = GetWindowDC(hwnd);

    MoveToEx(hdc, 0, 200, 0);                   //←현재위치이동(x축 그리기)
        LineTo(hdc, 400, 200);                      //←현재위치에서 지정된 좌표로 직선그리기

        MoveToEx(hdc, 30, 350, 0);                  //←현재위치이동(y축 그리기)
        LineTo(hdc, 30, 0);                         //←현재위치에서 지정된 좌표로 직선그리기

        for (degree = 0; degree <= 360; degree++)
        {
            result = sin(rad((double)degree));
            x = degree + 30;
            y = 200-(int)(100*result);           //← sin값은 0~1사이 이므로 100을 곱해준다.
                SetPixel(hdc, x, y, RGB(0, 0, 255));     //← 점을 찍는다.RGB(, , )값에 따라 색이 달라진다.
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

    printf("입력 ζ: %lf w_n: %lf \n", zeta, w_n);

    hwnd = GetForegroundWindow();
    hdc = GetWindowDC(hwnd);
    hPen = CreatePen(PS_DOT,1,RGB(0,0,0)); //점선 설정

    MoveToEx(hdc, 0, 500, 0);                   //현재위치이동(x축 그리기)
    LineTo(hdc, 800, 500);                      //현재위치에서 지정된 좌표로 직선그리기

    MoveToEx(hdc, 40, 600, 0);                  //현재위치이동(y축 그리기)
    LineTo(hdc,40, 100);                         //현재위치에서 지정된 좌표로 직선그리기

    SelectObject(hdc, hPen);  //그릴 펜 선택
    MoveToEx(hdc, 40, 400, 0);                  //현재위치이동(y=1 점선으로 그리기)
    LineTo(hdc, 800, 400);                         //현재위치에서 지정된 좌표로 직선그리기

    if (zeta > 1)
    {
        printf("시스템 안정 - Overdamped\n");
        for (time = 0; time < 5; time +=0.01)
        {
            y = 1 - (2 * exp(-time)) + exp(-2 * time);
            //printf("exp1- %lf ", 2*exp(-time));
            //printf("exp2- %lf ", exp(-2*time));
            //printf("1- %lf ",1-2 * exp(-time));
            //printf("+exp2- %lf ", 1 - 2 * exp(-time)+exp(-2 * time));
              //  printf("time : %lf y: %lf \n",time, y); 
            
            x = time*100 + 30; //y축이 x 30에서 그려짐
            y = 500 - (int)(100* y);           //← sin값은 0~1사이 이므로 100을 곱해준다.
           SetPixel(hdc, x, y, RGB(0, 0, 255));     //← 점을 찍는다.RGB(, , )값에 따라 색이 달라진다.
        }

    }
    else if (zeta == 1)
    {
        printf("시스템 안정 - Critically damped\n");
        for (time = 0; time < 5; time += 0.01)
        {
            y = 1 - exp(-w_n*time) - time*exp(-w_n * time);
           //printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 27; //y축이 x 30에서 그려짐
            y = 500 - (int)(100 * y);           //← sin값은 0~1사이 이므로 100을 곱해준다.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //← 점을 찍는다.RGB(, , )값에 따라 색이 달라진다.
        }
    }
    else if ( zeta > 0 && zeta < 1)
    {
        printf("시스템 안정 - Underdamped\n");
        for (time = 0; time < 5; time += 0.0001)
        {
            y = 1 - (1/sqrt(1-pow(zeta,2.0)))*exp(-zeta*w_n*time)*sin((w_n*sqrt(1-pow(zeta,2.0)))*time+acos(zeta));
            // printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 40; //y축이 x 30에서 그려짐
            y = 500 - (int)(100 * y);           //← sin값은 0~1사이 이므로 100을 곱해준다.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //← 점을 찍는다.RGB(, , )값에 따라 색이 달라진다.
        }
    }
    else if (zeta == 0)
    {
        printf("시스템 약간 불안정 - Undamped(marginally unstable)\n");
        for (time = 0; time < 5; time += 0.0001)
        {
            y = 1 - (1 / sqrt(1 - pow(zeta, 2.0))) * exp(-zeta * w_n * time) * sin((w_n * sqrt(1 - pow(zeta, 2.0))) * time + acos(zeta));
            //printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 27; //y축이 x 30에서 그려짐
            y = 500 - (int)(100 * y);           //← sin값은 0~1사이 이므로 100을 곱해준다.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //← 점을 찍는다.RGB(, , )값에 따라 색이 달라진다.
        }
    }
    else if (zeta < 0 && zeta > -1)
    {
        printf("시스템 불안정 - Negatively damped\n");
        for (time = 0; time < 5; time += 0.0001)
        {
            y = 1 - (1 / sqrt(1 - pow(zeta, 2.0))) * exp(-zeta * w_n * time) * sin((w_n * sqrt(1 - pow(zeta, 2.0))) * time + acos(zeta));
           // printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 40; //y축이 x 30에서 그려짐
            y = 500 - (int)(100 * y);           //← sin값은 0~1사이 이므로 100을 곱해준다.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //← 점을 찍는다.RGB(, , )값에 따라 색이 달라진다.
        }
    }
    else
    {
        printf("시스템 불안정 - Negatively damped\n"); //무제한 증가 c에서는 -inf 값 뜨면서 계산이 정상적그래프 미출력
        for (time = 0; time < 3; time += 0.0001)
        {
            y = 1 - (1 / sqrt(1 - pow(zeta, 2.0))) * exp(-zeta * w_n * time) * sin((w_n * sqrt(1 - pow(zeta, 2.0))) * time + acos(zeta));
          //  printf("time : %lf y: %lf \n", time, y);
            x = time * 100 + 27; //y축이 x 30에서 그려짐
            y = 500 - (int)(100 * y);           //← sin값은 0~1사이 이므로 100을 곱해준다.
            SetPixel(hdc, x, y, RGB(0, 0, 255));     //← 점을 찍는다.RGB(, , )값에 따라 색이 달라진다.
        }
    }
}

int main(void)
{
    double zeta = 0.0; //damping_ratio
    double w_n = 0.0; //natural frequency

    printf("damping_ratio - zeta를 입력해주세요.\n");
    printf("ζ: ");
    scanf("%lf", &zeta);

    printf("natural frequency - w_n를 입력해주세요.\n");
    printf("w_n: ");
    scanf("%lf", &w_n);
    
    printf("입력된 zeta와 natural frequency 에 따른 자동제어 2차 방정식 모델 그래프를 출력합니다.\n");
    print_graph(zeta,w_n);


 //   double w = 

}