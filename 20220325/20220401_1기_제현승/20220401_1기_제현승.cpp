#include <stdio.h>
#include <math.h>
#include <iostream>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

typedef float real;
//벡터
class Vector3
{
	public:
	real x;
	real y;
	real z;
	
	private:
	real pad;
};


Vector3 vector_plus(Vector3 v1, Vector3 v2)
{
		Vector3 vt;
		vt.x = v1.x + v2.x;
		vt.y = v1.y + v2.y;
		vt.z = v1.z + v2.z;
		return vt;
}


Vector3 vector_minus(Vector3 v1, Vector3 v2)
{
		Vector3 vt;
		vt.x = v1.x - v2.x;
		vt.y = v1.y - v2.y;
		vt.z = v1.z - v2.z;
		return vt;
}

Vector3 scalar_vector(Vector3 v, int  n)
{
	v.x = v.x * n;
	v.y = v.y * n;
	v.z = v.z * n;
	return v;
}



//매트릭스
class Matrix3 // 3 x 1 행렬, 보통 3차원 공간에서의 벡터는  주로  3 x 1 행렬로 나타내며 수학적으로는 열벡터로 표현
{//판단 근거: https://luv-n-interest.tistory.com/726 
	public:
	real data[9]; //3 x 1 열벡터를 배열로 나타 내기 위해서는 해당 크기의 데이타 배열이 필요 
	
	public:
	Matrix3(){}
	Matrix3(Vector3 v)
			 {//  3 x 1 행렬이므로 아래와 같이 작성, -1..0은 값이 없다는 의미
				 data[0] = v.x; data[1] = -1.0; data[2] = -1.0;
				 data[3] = v.y; data[4] = -1.0; data[5] = -1.0;
				 data[6] = v.z; data[7] = -1.0; data[8] = -1.0;
			 }
};

Matrix3 transposed_matrix(Matrix3 m)
{
	real tmp;
	tmp = m.data[3];
	m.data[3]= -1.0;
	m.data[1] = tmp;
	tmp = m.data[6];
	m.data[6]= -1.0;
	m.data[2] = tmp;
	
	return m;
}

real inner_product(Matrix3 m1, Matrix3 m2)
{
	//이게 성립되려면 v1이 전치 되어 행벡터가 되어야함 1x3이므로 내적에는 무리 없음
	Matrix3 trans_matrix = transposed_matrix(m1);
	real result;
		//내적 계산 확인용 
    //printf("%lf %lf %lf \n",m1.data[0]*m2.data[0], m1.data[3]*m2.data[3], m1.data[6]*m2.data[6]);
	result =m1.data[0]*m2.data[0] + m1.data[3]*m2.data[3] + m1.data[6]*m2.data[6];
	//실제 수학 풀이해서 진행하여 했는 데 아래와 같은 오류가 발생하여 위와같이 작성
	//result = trans_matrix.data[0]*m2.data[0]+trans_matrix.data[1]*m2.data[3]+trans_matrix[2]*m2.data[6];
	//20220401_1기_제현승.cpp:88:89: error: no match for ‘operator[]’ (operand types are ‘Matrix3’ and ‘int’)
  //trans_matrix.data[0]*m2->data[0]+trans_matrix.data[1]*m2->data[3]+trans_matrix[2]*m2->data[6];
 //에러나서 변경
 
	return result;
}

real cross_product(Vector3 basis, Vector3 v1, Vector3 v2)
{
	
	real result;
	Matrix3 cross_matrix;
	cross_matrix.data[0] = basis.x;
	cross_matrix.data[1] = basis.y;
	cross_matrix.data[2] = basis.z;
	
	cross_matrix.data[3] = v1.x;
	cross_matrix.data[4] = v1.y;
	cross_matrix.data[5] = v1.z;
	
	cross_matrix.data[6] = v2.x;
	cross_matrix.data[7] = v2.y;
	cross_matrix.data[8] = v2.z;
	
	
	/*printf("\n%lf ",cross_matrix.data[0]*(cross_matrix.data[4]*cross_matrix.data[8]- cross_matrix.data[5]*cross_matrix.data[7]));
	printf("%lf ",cross_matrix.data[1]*(cross_matrix.data[5]*cross_matrix.data[6]- cross_matrix.data[3]*cross_matrix.data[8]));
	printf("%lf \n",cross_matrix.data[2]*(cross_matrix.data[3]*cross_matrix.data[7]- cross_matrix.data[4]*cross_matrix.data[6]));
	//외적 계산 확인용 
	*/ 
	result = cross_matrix.data[0]*(cross_matrix.data[4]*cross_matrix.data[8]- cross_matrix.data[5]*cross_matrix.data[7])+cross_matrix.data[1]*(cross_matrix.data[5]*cross_matrix.data[6]- cross_matrix.data[3]*cross_matrix.data[8]) + cross_matrix.data[2]*(cross_matrix.data[3]*cross_matrix.data[7]- cross_matrix.data[4]*cross_matrix.data[6]);
	
	return result;
}
int main() {
	srand(time(NULL));
	
	Vector3 result_v;
	real result_f;
	Vector3 basis_vector; //기저벡
	basis_vector.x = rand()%10+1;
	basis_vector.y = rand()%10+1;
	basis_vector.z = rand()%10+1;
	
	printf("기저 벡터 basis_vector: x-%lf y-%lf z-%lf \n\n",basis_vector.x,basis_vector.y,basis_vector.z);
	
	Vector3 v1;
	v1.x = rand()%10+1;
	v1.y = rand()%10+1;
	v1.z = rand()%10+1;
	
	printf("벡터 v1: x-%lf y-%lf z-%lf \n\n",v1.x,v1.y,v1.z);
	
	
	
	Vector3 v2;
	v2.x = rand()%10+1;
	v2.y = rand()%10+1;
	v2.z = rand()%10+1;
	
	printf("벡터 v2: x-%lf y-%lf z-%lf \n\n",v2.x,v2.y,v2.z);
	
	Matrix3 m1(v1);
	Matrix3 m2(v2);
	
	printf("벡터 행렬과 관련된 연산을 시작합니다. \n\n\n");
	
	result_v = vector_plus(v1,v2);
	printf("벡터 합: x-%lf y-%lf z-%lf \n",result_v.x,result_v.y,result_v.z);
	result_v = vector_minus(v1,v2);
	printf("벡터 차: x-%lf y-%lf z-%lf \n",result_v.x,result_v.y,result_v.z);
	
	result_v = scalar_vector(v1,2);
	printf("벡터 스칼라 곱: x-%lf y-%lf z-%lf \n",result_v.x,result_v.y,result_v.z);
	
	result_v = scalar_vector(v2,9);
	printf("벡터 스칼라 곱: x-%lf y-%lf z-%lf \n",result_v.x,result_v.y,result_v.z);
	
	result_f = inner_product(m1,m2);
	printf("벡터 내적의 결과: %lf",result_f);
	
	result_f = cross_product(basis_vector, v1, v2);
	printf("벡터 외적의 결과: %lf\n",result_f);
	return 0;
}
