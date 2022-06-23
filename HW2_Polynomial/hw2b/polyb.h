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
	    Polynomial operator*(Polynomial&);
	    void NewTerm(const float, const int);
	    friend ostream& operator<<(ostream&, Polynomial&);
	    friend istream& operator>>(istream&, Polynomial&);
    private:
	    Term* termArray; // term 배열
	    int capacity; // 용량
	    int terms; // term 개수
};
#endif