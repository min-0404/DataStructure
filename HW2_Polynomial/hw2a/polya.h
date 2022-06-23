#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
using namespace std;

class Polynomial;

class Term{
    friend class Polynomial;
	friend ostream& operator<<(ostream&, Polynomial&);
	friend istream& operator>>(istream&, Polynomial&);
    private:
        float coef; // 계수
	    int exp; // 지수
};

class Polynomial{
    public:
        Polynomial();
	    Polynomial operator+(Polynomial&);
	    void NewTerm(const float, const int);
	    friend ostream& operator<<(ostream&, Polynomial&);
	    friend istream& operator>>(istream&, Polynomial&);
    private:
	    Term* termArray;  // term 들을 줄줄이 나타내는 배열, 즉 다항식 그 자체
	    int capacity; // term 들어갈 수 있는 용량
	    int terms; // term 의 개수
};
#endif