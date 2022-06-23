#include <iostream>
#include "polyb.h"
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
	for (int i = 0; i < p.terms; i++){
		if (p.termArray[i].exp == 0)    break;
		if (p.termArray[i].coef > 0){
			if (p.termArray[i].coef == 1){
				if (i == 0)     os << "x" << '^' << p.termArray[i].exp << ' ';
				else    os << '+' << "x" << '^' << p.termArray[i].exp << ' ';
			}
			else{
                if (i == 0)     os << p.termArray[i].coef << "x" << '^' << p.termArray[i].exp << ' ';
				else    os << '+' << p.termArray[i].coef << "x" << '^' << p.termArray[i].exp << ' ';
			}
		}
		else{
            if (p.termArray[i].coef == -1)      os << "-x" << '^' << p.termArray[i].exp << ' ';
			else    os << p.termArray[i].coef << "x" << '^' << p.termArray[i].exp << ' ';
		}
	}
	
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

Polynomial::Polynomial() : capacity(1), terms(0){
	termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoeff, const int theExp){
	if (terms == capacity){
		capacity *= 2;
		Term* temp = new Term[capacity]();
		copy(termArray, termArray + terms, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms].exp = theExp;
	terms++;
}

Polynomial Polynomial::operator+(Polynomial& b){
	Polynomial c;
	int apos = 0, bpos = 0;
	while ((apos < terms) && (bpos < b.terms)){
		
        if (termArray[apos].exp == b.termArray[bpos].exp){
			float t = termArray[apos].coef + b.termArray[bpos].coef;
			if (t) c.NewTerm(t, termArray[apos].exp);
			apos++, bpos++;
		}

		else if (termArray[apos].exp > b.termArray[bpos].exp){
			c.NewTerm(termArray[apos].coef, termArray[apos].exp);
			apos++;
		}

		else{
			c.NewTerm(b.termArray[bpos].coef, termArray[bpos].exp);
			bpos++;
		}
	}
	for (; apos < terms; apos++)    c.NewTerm(termArray[apos].coef, termArray[apos].exp);
	for (; bpos < terms; bpos++)    c.NewTerm(termArray[bpos].coef, termArray[bpos].exp);
	return c;
}

Polynomial Polynomial::operator*(Polynomial& b){
	Polynomial c;
	c.NewTerm(0, 0);
	for (int i = 0; i < terms; i++){
		Polynomial temp;
		for (int j = 0; j < b.terms; j++){
			temp.NewTerm(termArray[i].coef * b.termArray[j].coef, termArray[i].exp + b.termArray[j].exp);
		}
		c = c + temp;
	}
	return c;
}