#include <iostream>
#include "polya.h"
using namespace std;

istream& operator>>(istream& is, Polynomial& p){
	int noofterms;
	float coef;
	int exp;
	is >> noofterms;
	for (int i = 0; i < noofterms; i++){
		is >> coef >> exp;
		p.NewTerm(coef, exp);
	}
	return is;
}


ostream& operator<<(ostream& os, Polynomial& p){
    // term 의 개수만큼 반복
	for (int i = 0; i < p.terms; i++) {

		// 종결조건: 지수가 0이면 마지막 항이므로 끝내버리기
        if (p.termArray[i].exp == 0)    break;

        // 계수가 양수일때
		if (p.termArray[i].coef > 0){
            // 계수 = 1 일때
			if (p.termArray[i].coef == 1){
				if (i == 0)     os << "x" << '^' << p.termArray[i].exp << ' ';
				else    os << '+' << "x" << '^' << p.termArray[i].exp << ' ';
			}
            // 계수 != 1일때
			else{
                if (i == 0)     os << p.termArray[i].coef << "x" << '^' << p.termArray[i].exp << ' ';
				else        os << '+' << p.termArray[i].coef << "x" << '^' << p.termArray[i].exp << ' ';
			}
		}
        // 계수가 음수일때
		else{
            if (p.termArray[i].coef == -1)      os << "-x" << '^' << p.termArray[i].exp << ' ';
			else        os << p.termArray[i].coef << "x" << '^' << p.termArray[i].exp << ' ';
		}
	}
    // 마지막 항 처리 과정
	for (int i = 0; i < p.terms; i++){
		if ((p.termArray[i].exp == 0) && (p.termArray[i].coef > 0)){
			os << "+" << p.termArray[i].coef << ' ';
			break;
		}
		else if ((p.termArray[i].exp == 0) && (p.termArray[i].coef < 0)){
			os << p.termArray[i].coef << ' ';
			break;
		}
	}
	os << endl;
	return os;
}